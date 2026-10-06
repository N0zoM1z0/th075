import copy
import importlib.util
import json
from pathlib import Path
import struct
import unittest

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('background_cycles',ROOT/'scripts/verify-background-cycle-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)


class BackgroundCycleTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.plan=json.loads((ROOT/V.EVIDENCE).read_text())
        cls.flow=V.module('test_cycle_flow','sdk_image_carriers.py')
        cls.c=V.module('test_cycle_target','compare-coff-function.py')
        cls.auth=V.module('test_cycle_cfg','verify-authored-origins.py')

    def test_immutable_complete_plan_and_retained_inputs(self):
        V.verify_plan(self.plan)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        for p,h in self.plan['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT/p).read_bytes()),h,p)

    def test_only_six_origins_and_whole_extents(self):
        self.assertEqual({r['address']:r['size'] for r in self.plan['functions']},V.WHOLE)
        self.assertEqual(sum(r['size'] for r in self.plan['functions']),314)
        self.assertEqual([r['cfg'] for r in self.plan['functions']],[[1,1]]*6)
        for r in self.plan['functions']:
            self.assertEqual(r['instructions'][-1]['mnemonic'],'ret')
            self.assertEqual(r['instructions'][-1]['operands'],'')
            self.assertEqual(r['original_function']['size'],r['accepted_function']['size'])
            self.assertEqual(r['original_function']['current_name'],r['accepted_function']['current_name'])

    def test_no_source_private_abi_mapping_or_exact_credit(self):
        for r in self.plan['functions']:
            f=r['accepted_function']
            self.assertEqual(f['status'],'unclassified')
            self.assertEqual(f['match_percent'],'0.00')
            for k in ['source_file','signature','calling_convention']:self.assertFalse(f[k])
        self.assertIn('No authored CSV row or old evidence is rewritten',self.plan['interpretation'])

    def test_each_callback_has_independent_asset_table_and_renderer(self):
        self.assertEqual([c['asset_witness']['asset_path'].rsplit('\\',1)[-1] for c in self.plan['contexts']],
                         ['BG02a.dat','BG02b.dat','BG02c.dat','BG04a.dat','BG07a.dat','BG08a.dat'])
        for ctx in self.plan['contexts']:
            self.assertEqual(ctx['table']['size'],24)
            self.assertEqual(len(ctx['table']['words']),6)
            self.assertEqual(ctx['table']['words'][1],int(ctx['callback'],16))
            self.assertEqual(ctx['table']['words'][4],int(ctx['renderer'],16))
            self.assertTrue(ctx['counter_readers'])
            owners={r['address']:r for r in ctx['owners']}
            self.assertEqual(owners[ctx['constructor']]['instructions'][0]['mnemonic'],'push')
            self.assertIsNotNone(owners[ctx['constructor']]['authored_record'])
            self.assertIsNotNone(owners[ctx['renderer']]['authored_record'])

    def test_two_whole_double_owners_are_distinct(self):
        self.assertEqual([(r['address'],r['size'],r['value']) for r in self.plan['constants']],
                         [('0x00658960',8,2500.0),('0x00658CA8',8,15360.0)])
        self.assertEqual(len({r['sha256'] for r in self.plan['constants']}),2)

    def test_all_six_complete_instruction_policies_have_ordinary_controls(self):
        controls={r['symbol']:r for r in self.plan['public_control']['methods'] if r['role']=='ordinary-policy-alternative'}
        self.assertEqual([r['size'] for r in controls.values()],[44,51,51,58])
        for r in self.plan['functions']:
            control=controls[r['ordinary_symbol']]
            self.assertEqual(r['policy'],control['policy'])
            self.assertNotEqual(r['size'],control['size'])
            self.assertNotEqual(r['body_sha256'],control['sha256'])

    def test_signed_threshold_and_distinct_x87_status_predicates(self):
        roots=self.plan['functions']
        for r in roots[:3]:
            self.assertIn(['cmp',[['mem',4,'eax',None,1,'counter'],['imm',360]]],r['policy'])
        self.assertIn(['test',[['reg','ah'],['imm',65]]],roots[3]['policy'])
        self.assertIn(['test',[['reg','ah'],['imm',1]]],roots[4]['policy'])
        self.assertNotEqual(roots[3]['policy'],roots[4]['policy'])

    def test_paired_counter_keeps_primary_unreset(self):
        policy=self.plan['functions'][-1]['policy']
        self.assertEqual(sum(i[0]=='add' for i in policy),2)
        self.assertIn(['cmp',[['mem',4,'eax',None,1,'frame'],['imm',71]]],policy)
        zero_stores=[i for i in policy if i[0]=='mov' and i[1][-1]==['imm',0]]
        self.assertEqual(zero_stores,[['mov',[['mem',4,'ecx',None,1,'frame'],['imm',0]]]])

    def test_implicit_copy_alternatives_do_not_select_callbacks(self):
        controls=[r for r in self.plan['public_control']['methods'] if r['role']=='implicit-copy-alternative']
        self.assertEqual([r['size'] for r in controls],[24,13])
        for r in controls:
            self.assertFalse(r['fields'])
            self.assertEqual(r['cfg'],[1,0])
            self.assertFalse(any(i['mnemonic'] in ['add','cmp','fcomp','test'] for i in r['instructions']))

    def test_whole_ordinary_emission_and_compact_layout(self):
        control=self.plan['public_control']
        self.assertEqual(len(control['methods']),6)
        self.assertEqual(sum(r['size'] for r in control['methods']),241)
        self.assertEqual(control['layout_values'],[8,8,4,8])
        self.assertEqual(sum(len(r['fields']) for r in control['emission']),2)
        self.assertIn('/Od',control['profile'])
        self.assertEqual(control['headers'],{})

    def test_old_snapshots_and_unrelated_records_stay_literal(self):
        self.assertEqual(self.plan['historical_snapshots'],[])
        self.assertEqual(len(self.plan['unselected_sha256']),2)
        self.assertIn('config/authored-origin-evidence.csv',self.plan['retained_sha256'])
        keys={r['function']['address'] for r in self.plan['canonical']}
        self.assertTrue(set(V.WHOLE)<=keys)
        self.assertGreater(len(keys),30)

    def test_alignment_is_outside_selected_whole_bodies(self):
        self.assertEqual([r['size'] for r in self.plan['boundaries']],[0,0,0,9,9,4])
        for r,b in zip(self.plan['functions'],self.plan['boundaries']):
            self.assertEqual(int(b['address'],16),int(r['address'],16)+r['size'])
            self.assertEqual(bytes.fromhex(b['hex']),b'\xcc'*b['size'])

    def test_native_full_proof_and_receiver_filter(self):
        target=self.c.verified_target()
        V.verify_native(self.plan,target,self.c,self.flow)
        ctx=self.plan['contexts'][3]
        renderer=next(r for r in ctx['owners'] if r['address']==ctx['renderer'])
        a=int(renderer['address'],16);raw=self.c.pe_bytes_at(target,a,renderer['size'])
        readers=V.receiver_uses(raw,a,self.flow)
        self.assertEqual(len(readers),6)
        self.assertFalse(any('[ebp ' in r['operands'] for r in readers))

    def test_whole_cfg_rejects_truncation_and_status_change(self):
        target=self.c.verified_target();r=self.plan['functions'][3];a=int(r['address'],16)
        raw=self.c.pe_bytes_at(target,a,r['size'])
        with self.assertRaises(ValueError):self.auth.verify_body(raw[:-1],a)
        changed=bytearray(raw)
        instruction=next(i for i in self.flow.instructions(raw,a,len(raw)) if i.mnemonic=='test')
        changed[instruction.address-a+instruction.size-1]=1
        constants={int(q['address'],16):q['value'] for q in self.plan['constants']}
        self.assertNotEqual(V.normalized_policy(changed,a,self.flow,0x68,0x6c,constants),r['policy'])
        bad=copy.deepcopy(self.plan);bad['constants'][0]['value']=15360.0
        with self.assertRaises(ValueError):V.verify_plan(bad)


if __name__=='__main__':unittest.main()
