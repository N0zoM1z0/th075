import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('reverse_cycle',ROOT/'scripts/verify-background-reverse-cycle-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)


class BackgroundReverseCycleTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.plan=json.loads((ROOT/V.EVIDENCE).read_text())
        cls.c=V.module('reverse_test_target','compare-coff-function.py')
        cls.flow=V.module('reverse_test_flow','sdk_image_carriers.py')

    def test_immutable_whole_plan_and_all_retained_inputs(self):
        V.verify_plan(self.plan)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        for p,h in self.plan['retained_sha256'].items():self.assertEqual(V.digest((ROOT/p).read_bytes()),h,p)

    def test_only_one_full_origin_with_no_source_or_abi_credit(self):
        self.assertEqual({r['address']:r['size'] for r in self.plan['functions']},{'0x0044E3A0':45})
        r=self.plan['functions'][0];f=r['accepted_function']
        self.assertEqual(r['cfg'],[1,1]);self.assertEqual(r['instructions'][-1]['operands'],'')
        self.assertEqual(r['original_function']['current_name'],f['current_name'])
        self.assertEqual(f['status'],'unclassified');self.assertEqual(f['match_percent'],'0.00')
        for k in ['source_file','signature','calling_convention']:self.assertFalse(f[k])

    def test_signed_decrement_reset_and_reachable_counter_cycle(self):
        r=self.plan['functions'][0];pairs=[(i['mnemonic'],i['operands']) for i in r['instructions']]
        self.assertIn(('sub','ecx, 1'),pairs)
        self.assertIn(('cmp','dword ptr [eax + 0x68], 0'),pairs)
        self.assertIn(('mov','dword ptr [ecx + 0x68], 0xf00'),pairs)
        self.assertEqual(sum(mn=='jge' for mn,_ in pairs),1)
        value=0;values=[]
        for _ in range(3841):
            value-=1
            if value<0:value=3840
            values.append(value)
        self.assertEqual(values[0],3840);self.assertEqual(values[-1],0)
        self.assertEqual(set(values),set(range(3841)))

    def test_same_game_asset_table_initialization_and_renderer(self):
        ctx=self.plan['contexts'][0]
        self.assertEqual(ctx['asset_witness']['asset_path'],'data\\background\\BG05a.dat')
        self.assertEqual(ctx['constructor'],'0x0044E2F0')
        self.assertEqual(ctx['renderer'],'0x0044E3D0')
        self.assertEqual(ctx['table']['words'],[0x44e7c0,0x44e3a0,0x44e750,0x44e740,0x44e3d0,0x44e760])
        self.assertEqual(len(ctx['owners']),7);self.assertEqual(sum(r['size'] for r in ctx['owners']),1235)
        self.assertEqual([r['offset'] for r in ctx['counter_readers']],[270,444,656])
        self.assertTrue(all(r['mnemonic']=='fild' for r in ctx['counter_readers']))

    def test_complete_compact_source_and_implicit_copy_are_distinct(self):
        c=self.plan['public_control'];methods=c['methods']
        self.assertEqual([r['size'] for r in methods],[41,10])
        self.assertEqual(self.plan['functions'][0]['policy'],methods[0]['policy'])
        self.assertNotEqual(self.plan['functions'][0]['body_sha256'],methods[0]['sha256'])
        self.assertEqual(len(c['emission']),3);self.assertEqual(sum(r['size'] for r in c['emission']),63)
        self.assertFalse(any(r['fields'] for r in c['emission']))
        self.assertEqual(c['layout_values'],[4,4,4]);self.assertEqual(c['headers'],{})
        self.assertEqual(methods[1]['cfg'],[1,0])
        self.assertFalse(any(i['mnemonic'] in ['sub','cmp','jge'] for i in methods[1]['instructions']))

    def test_literal_prior_evidence_and_external_alignment(self):
        self.assertEqual(self.plan['historical_snapshots'],[])
        self.assertEqual(self.plan['constants'],[])
        self.assertIn('config/paired-clear-policy-origin-evidence.json',self.plan['retained_sha256'])
        self.assertEqual(len(self.plan['canonical']),7)
        b=self.plan['boundaries'][0];self.assertEqual((b['address'],b['size'],b['hex']),('0x0044E3CD',3,'cccccc'))

    def test_native_complete_proof_and_wrong_branch_rejected(self):
        target=self.c.verified_target();V.verify_native(self.plan,target,self.c,self.flow)
        r=self.plan['functions'][0];a=int(r['address'],16);raw=self.c.pe_bytes_at(target,a,45)
        bad=bytearray(raw);branch=next(i for i in self.flow.instructions(raw,a,45) if i.mnemonic=='jge')
        bad[branch.address-a]=0x7f
        self.assertNotEqual(V.normalized_policy(bad,a,self.flow,0x68,0x6c,{}),r['policy'])

    def test_extent_or_layout_mutation_cannot_earn_credit(self):
        bad=copy.deepcopy(self.plan);bad['functions'][0]['size']=41
        with self.assertRaises(ValueError):V.verify_plan(bad)
        bad=copy.deepcopy(self.plan);bad['public_control']['layout_values']=[0x6c,0x6c,4]
        with self.assertRaises(ValueError):V.verify_plan(bad)


if __name__=='__main__':unittest.main()
