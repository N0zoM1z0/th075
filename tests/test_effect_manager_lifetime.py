import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('effect_lifetime',ROOT/'scripts/verify-effect-manager-lifetime-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)


class EffectManagerLifetimeTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.plan=json.loads((ROOT/V.EVIDENCE).read_text())
        cls.c=V.module('effect_lifetime_test_target','compare-coff-function.py')
        cls.flow=V.module('effect_lifetime_test_flow','sdk_image_carriers.py')

    def test_all_immutable_inputs_and_only_one_complete_authored_transition(self):
        V.verify_plan(self.plan)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        for p,h in self.plan['retained_sha256'].items():self.assertEqual(V.digest((ROOT/p).read_bytes()),h,p)
        self.assertEqual({r['address']:r['size'] for r in self.plan['functions']},{'0x0045B9B0':85})
        self.assertEqual(self.plan['historical_snapshots'],[])

    def test_whole_game_cleanup_is_before_automatic_member_array_destruction(self):
        V.verify_native(self.plan,self.c.verified_target(),self.c,self.flow)
        r=self.plan['functions'][0];ins={i['offset']:i['operands'] for i in r['instructions']}
        self.assertEqual([ins[i] for i in [28,38,43,50,55,57,62,66]],
            ['dword ptr [ebp - 4], 0','0x45ba30','dword ptr [ebp - 4], 0xffffffff',
             '0x45bf30','4','0x14','eax, 4','0x641d4a'])
        anchors={r['address']:r for r in self.plan['anchors']}
        self.assertEqual((anchors['0x0045BA30']['size'],anchors['0x0045BA30']['authored_record']['evidence_id']),(221,'R109'))
        self.assertEqual((len(anchors),sum(r['size'] for r in anchors.values())),(18,2207))

    def test_paired_deleting_wrapper_calls_the_same_full_destructor_and_scalar_delete(self):
        r=next(r for r in self.plan['anchors'] if r['address']=='0x00458740');ins={i['offset']:i['operands'] for i in r['instructions']}
        self.assertEqual([ins[i] for i in [10,18,27,41]],['0x45b9b0','eax, 1','0x640f15','4'])
        selected=[r for r in self.plan['public_control']['comparisons'] if r['address']=='0x00458740']
        self.assertEqual([r['source_size'] for r in selected],[44])
        self.assertEqual([b['target'] for b in selected[0]['bindings']],['0x0045B9B0','0x00640F15'])

    def test_cleanup_handler_and_metadata_are_full_shared_defining_sections(self):
        comparisons=self.plan['public_control']['comparisons'];eh=next(r for r in comparisons if r['address']=='0x006563C0');data=next(r for r in comparisons if r['address']=='0x00669C78')
        self.assertEqual((eh['source_size'],eh['roots'],eh['source_definition']['offset']),(32,[0,22],22))
        self.assertEqual((data['source_size'],data['roots'],data['source_definition']['offset']),(36,[],8))
        self.assertEqual([b['target'] for b in data['bindings']],['0x006563C0','0x00669C78'])
        self.assertEqual(len(self.plan['context']['frames']),3)
        bad=copy.deepcopy(self.plan);bad['public_control']['comparisons'][1]['source_size']=22
        with self.assertRaisesRegex(ValueError,'immutable'):V.verify_plan(bad)

    def test_implicit_and_empty_explicit_alternatives_retain_all_target_tail_differences(self):
        negatives=[r for r in self.plan['public_control']['comparisons'] if r['role']=='negative']
        self.assertEqual([(r['source_size'],r['target_size']) for r in negatives],[(32,85),(32,85)])
        for r in negatives:
            self.assertEqual([d['offset'] for d in r['differences'] if d['source'] is None],list(range(32,85)))
            self.assertTrue(all(d['target'] is not None for d in r['differences']))
        r=copy.deepcopy(negatives[0]);r['differences'].pop()
        raw=self.c.pe_bytes_at(self.c.verified_target(),0x45b9b0,85)
        with self.assertRaisesRegex(ValueError,'differences'):V.compare_whole(r,b'\xcc'*32,raw)

    def test_no_abi_layout_source_or_exact_credit_and_geometry_stays_unknown(self):
        r=self.plan['functions'][0];f=r['accepted_function'];old=r['original_function']
        self.assertEqual([f[k] for k in ['current_name','size','span_end']],[old[k] for k in ['current_name','size','span_end']])
        self.assertFalse(any(f[k] for k in ['source_file','calling_convention','signature']))
        self.assertEqual(f['match_percent'],'0.00')
        canonical={r['function']['address']:r for r in self.plan['canonical']}
        for a in ['0x0040D980','0x0040D9F0']:self.assertEqual(canonical[a]['origin']['origin'],'unknown')
        self.assertEqual(self.plan['public_control']['layouts'][0]['values'],[20,20,84,84,40,4,4,12,20,84,84,84,20])

    def test_full_current_emission_fields_and_real_weak_aliases(self):
        ctl=self.plan['public_control']
        self.assertEqual((len(ctl['emission']),sum(r['size'] for r in ctl['emission']),sum(len(r['fields']) for r in ctl['sections'])),(155,7060,343))
        self.assertEqual((len(ctl['headers']),len(ctl['weak_references'])),(30,2))
        self.assertEqual((len(ctl['comparisons']),sum(r['source_size'] for r in ctl['comparisons']),sum(len(r['bindings']) for r in ctl['comparisons'])),(7,280,20))

    def test_scalar_delete_preserves_bound_free_tail_and_entire_free_owner(self):
        anchors={r['address']:r for r in self.plan['anchors']};r=anchors['0x00640F15']
        self.assertEqual((r['size'],r['instructions'][0]['mnemonic'],r['instructions'][0]['operands']),(5,'jmp','0x642a61'))
        self.assertEqual(anchors['0x00642A61']['size'],113)
        bad=copy.deepcopy(self.plan);bad['anchors']=[r for r in bad['anchors'] if r['address']!='0x00642A61']
        with self.assertRaisesRegex(ValueError,'free tail'):V.verify_native(bad,self.c.verified_target(),self.c,self.flow)

    def test_history_projection_requires_all_twelve_exact_successors(self):
        scope=self.plan['retained_replays']['scopes'][0];transitions=V.retained_transitions(self.plan,scope)
        self.assertEqual(len(transitions),12);self.assertNotIn('0x0045B9B0',transitions)
        old=json.loads((ROOT/scope['path']).read_text())
        for r in scope['transitions']:self.assertEqual(r['snapshot'],old['snapshots'][r['snapshot_index']])
        bad=copy.deepcopy(V.rows('functions.csv'));next(r for r in bad if r['address']=='0x0045B880')['notes']='unapproved'
        with self.assertRaisesRegex(ValueError,'unapproved'):V.project_rows('functions.csv',bad,transitions)

    def test_selected_native_policy_or_member_stride_change_is_rejected(self):
        for offset,value in [('38',['call','0x45c0e0']),('57',['push','0x10'])]:
            bad=copy.deepcopy(self.plan);bad['context']['witnesses']['0x0045B9B0'][offset]=value
            with self.assertRaises(ValueError):V.verify_native(bad,self.c.verified_target(),self.c,self.flow)


if __name__=='__main__':unittest.main()
