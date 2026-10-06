import copy
import importlib.util
import json
from pathlib import Path
import unittest
from unittest.mock import patch

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('background_blends',ROOT/'scripts/verify-background-blend-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)


class BackgroundBlendTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.plan=json.loads((ROOT/V.EVIDENCE).read_text())
        cls.c=V.module('blend_test_target','compare-coff-function.py')
        cls.coff=V.module('blend_test_coff','coff_data.py')
        cls.flow=V.module('blend_test_flow','sdk_image_carriers.py')

    def test_whole_immutable_plan_and_all_retained_inputs(self):
        V.verify_plan(self.plan)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        for p,h in self.plan['retained_sha256'].items():self.assertEqual(V.digest((ROOT/p).read_bytes()),h,p)

    def test_bounded_three_origins_preserve_extents_names_and_source_state(self):
        self.assertEqual({r['address']:r['size'] for r in self.plan['functions']},V.WHOLE)
        for r in self.plan['functions']:
            self.assertEqual(r['cfg'],[1,0])
            self.assertEqual(r['original_function']['current_name'],r['accepted_function']['current_name'])
            self.assertEqual(r['original_function']['size'],r['accepted_function']['size'])
            f=r['accepted_function'];self.assertEqual(f['status'],'unclassified');self.assertEqual(f['match_percent'],'0.00')
            for k in ['source_file','signature','calling_convention']:self.assertFalse(f[k])

    def test_native_calculations_keep_both_unused_results(self):
        for r in self.plan['functions']:
            pairs=[(i['mnemonic'],i['operands']) for i in r['instructions']]
            self.assertEqual(len(pairs),18)
            self.assertEqual([op for mn,op in pairs if mn=='call'],['0x6406ac','0x6406ac','0x40c7f0'])
            self.assertIn(('mov','dword ptr [ebp - 8], eax'),pairs)
            self.assertIn(('mov','dword ptr [ebp - 4], eax'),pairs)
            self.assertEqual(pairs[11:15],[('push','0'),('mov','ecx, dword ptr [ebp - 0xc]'),('add','ecx, 0x18'),('call','0x40c7f0')])

    def test_independent_complete_camera_and_mode_owners(self):
        owners=self.plan['owners']
        self.assertEqual([(r['address'],r['size']) for r in owners],[('0x0040C7F0',65),('0x00412660',96),('0x00412CF0',146)])
        self.assertEqual(sum(r['size'] for r in owners),307)
        for r in owners:self.assertIsNotNone(r['authored_record'])
        for r in owners[1:]:
            pairs=[(i['mnemonic'],i['operands']) for i in r['instructions']]
            self.assertIn(('fstp','dword ptr [0x6713c4]'),pairs)
            self.assertTrue(any(mn=='mov' and op.startswith('dword ptr [0x671404],') for mn,op in pairs))

    def test_readonly_offset_and_two_writable_inputs_remain_distinct(self):
        self.assertEqual([(r['address'],r['size'],r['permissions']) for r in self.plan['data']],
                         [('0x00671404',4,0xc0000000),('0x006713C4',4,0xc0000000),('0x00657834',4,0x40000000)])

    def test_complete_original_crt_owner_and_real_aux_extent(self):
        r=self.plan['runtime']
        self.assertEqual((r['record']['coff_symbol'],r['record']['size'],r['record']['relocation_count']),('__ftol2','117','0'))
        self.assertFalse(r['fields'])
        self.assertIn('__ftol2',[d['symbol'] for d in r['source']['definitions']])
        target=self.c.verified_target();V.verify_runtime(self.plan,target,self.c,self.coff,self.flow)
        bad=copy.deepcopy(self.plan);bad['runtime']['record']['size']='116'
        with self.assertRaises(ValueError):V.verify_runtime(bad,target,self.c,self.coff,self.flow)

    def test_three_literal_retained_unknown_snapshots(self):
        snapshots=self.plan['historical_snapshots']
        self.assertEqual(len(snapshots),3)
        self.assertEqual({r['record']['function']['address'] for r in snapshots},set(V.WHOLE))
        for r in snapshots:
            old=json.loads((ROOT/r['path']).read_text())
            for k in r['trail']:old=old[k]
            self.assertEqual(old,r['record'])
            self.assertEqual(old['origin']['origin'],'unknown')

    def test_whole_r230_source_and_three_real_slot_two_contexts(self):
        cp=self.plan['retained_checkpoint'];prior=json.loads((ROOT/cp['path']).read_text())
        old=V.module('blend_test_prior','verify-background-cycle-origins.py');old.verify_plan(prior)
        self.assertEqual(V.metadata_digest(prior),cp['plan_sha256'])
        self.assertEqual(sum(r['size'] for r in prior['functions']),314)
        for ctx in cp['contexts']:
            r=prior['contexts'][ctx['index']]
            self.assertEqual(V.metadata_digest(r),ctx['sha256'])
            self.assertEqual(r['table']['words'][2],int(ctx['callback'],16))

    def test_current_view_projects_only_checked_whole_pairs_and_restores_reader(self):
        old=V.module('blend_test_projection','verify-background-cycle-origins.py');reader=old.rows
        actual={r['address']:r for r in V.rows('function-origins.csv')}
        original=actual[self.plan['functions'][0]['address']]['origin']=='unknown'
        called=[]
        def replay(prior,evidence_only):
            called.append(prior)
            old.verify_canonical(prior,False)
            projected={r['address']:r for r in old.rows('function-origins.csv')}
            for r in self.plan['functions']:self.assertEqual(projected[r['address']],r['original_origin'])
            for a,r in actual.items():
                if a not in V.WHOLE:self.assertEqual(projected[a],r)
        with patch.object(V,'module',return_value=old),patch.object(old,'replay',side_effect=replay):
            V.replay_retained(self.plan,original)
        self.assertEqual(len(called),1);self.assertIs(old.rows,reader)

    def test_current_view_rejects_unapproved_row_and_restores_reader(self):
        old=V.module('blend_test_bad_projection','verify-background-cycle-origins.py');reader=old.rows
        actual={r['address']:r for r in V.rows('function-origins.csv')};original=actual[self.plan['functions'][0]['address']]['origin']=='unknown'
        def changed(name):
            values=reader(name)
            if name=='functions.csv':
                values=copy.deepcopy(values)
                next(r for r in values if r['address']=='0x0044B980')['size']='59'
            return values
        old.rows=changed
        with patch.object(V,'module',return_value=old),patch.object(old,'replay',side_effect=lambda m,e:old.rows('functions.csv')):
            with self.assertRaises(ValueError):V.replay_retained(self.plan,original)
        self.assertIs(old.rows,changed)

    def test_full_ordinary_emission_and_all_real_routes(self):
        c=self.plan['public_control']
        self.assertEqual([r['size'] for r in c['methods']],[22,16,21,21,10])
        self.assertEqual(len(c['emission']),7)
        self.assertEqual(sum(r['size'] for r in c['emission']),110)
        self.assertEqual(sum(len(r['fields']) for r in c['emission']),7)
        self.assertEqual(c['layout_values'],[1,1,4,4]);self.assertEqual(c['headers'],{})
        self.assertEqual(c['independent_routes']['__ftol2'],'0x006406AC')
        self.assertEqual(c['independent_routes']['?SetBlendMode@TextureObservation@@QAEXH@Z'],'0x0040C7F0')
        for r in c['methods']:self.assertEqual(r['linked_flow']['reachable_instruction_count'],r['linked_flow']['instruction_count'])

    def test_natural_controls_have_meaningful_returns_without_inert_locals(self):
        source=(ROOT/self.plan['public_control']['probe']).read_text()
        self.assertIn('return static_cast<int>(ObservedBackgroundX + 160.0f)',source)
        self.assertIn('return static_cast<int>(ObservedBackgroundY)',source)
        self.assertNotIn('padding',source)
        methods=self.plan['public_control']['methods']
        self.assertEqual(methods[-1]['fields'],[])
        self.assertFalse(any(i['mnemonic']=='call' for i in methods[-1]['instructions']))
        zero,one=methods[2:4]
        self.assertEqual(zero['instructions'][4]['operands'],'0')
        self.assertEqual(one['instructions'][4]['operands'],'1')

    def test_native_whole_proof_and_wrong_float_rejected(self):
        target=self.c.verified_target();V.verify_native(self.plan,target,self.c,self.flow)
        bad=copy.deepcopy(self.plan);bad['data'][2]['sha256']=bad['data'][0]['sha256']
        with self.assertRaises(ValueError):V.verify_native(bad,target,self.c,self.flow)

    def test_external_alignment_and_prior_scope_are_preserved(self):
        self.assertEqual([r['size'] for r in self.plan['boundaries']],[4,4,4])
        self.assertEqual(len(self.plan['canonical']),48)
        for r,b in zip(self.plan['functions'],self.plan['boundaries']):
            self.assertEqual(int(b['address'],16),int(r['address'],16)+60)
            self.assertEqual(bytes.fromhex(b['hex']),b'\xcc'*4)


if __name__=='__main__':unittest.main()
