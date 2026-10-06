import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('scene_shared',ROOT/'scripts/verify-scene-shared-value-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)

class SceneSharedValueTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.plan=json.loads((ROOT/V.EVIDENCE).read_text())
        cls.c=V.module('shared_test_target','compare-coff-function.py')
        cls.flow=V.module('shared_test_flow','sdk_image_carriers.py')

    def test_whole_manifest_and_retained_inputs(self):
        V.verify_plan(self.plan)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        for p,h in self.plan['retained_sha256'].items():self.assertEqual(V.digest((ROOT/p).read_bytes()),h,p)

    def test_whole_independent_game_state_and_guarded_table(self):
        p=self.plan['parent']
        self.assertEqual((p['address'],p['size'],p['cfg']),('0x0043B610',4764,[1,158]))
        self.assertEqual(len(p['direct_switches']),1)
        self.assertEqual(p['tables'][0]['size'],60)
        self.assertEqual(len(p['tables'][0]['words']),15)
        self.assertEqual(V.consumer_address(p['instructions']),0x671628)

    def test_source_type_ambiguity_and_full_emission(self):
        c=self.plan['public_control'];m=c['methods']
        self.assertEqual([r['size'] for r in m],[21,21,10])
        self.assertEqual(m[0]['sha256'],m[1]['sha256'])
        self.assertNotEqual(m[0]['fields'][0]['symbol'],m[1]['fields'][0]['symbol'])
        self.assertTrue(all(r['whole_native_byte_equal'] for r in m[:2]))
        self.assertEqual(m[0]['linked_flow'],m[1]['linked_flow'])
        self.assertFalse(m[2]['fields'])
        self.assertEqual(sum(r['size'] for r in c['emission']),64)
        self.assertEqual(c['layout_values'],[1,4,4])
        self.assertEqual(c['headers'],{})

    def test_no_original_source_abi_or_exact_credit(self):
        r=self.plan['functions'][0];f=r['accepted_function']
        self.assertEqual((r['address'],r['size']),('0x004557E0',21))
        self.assertEqual(f['current_name'],r['original_function']['current_name'])
        self.assertEqual((f['status'],f['match_percent']),('unclassified','0.00'))
        for k in ['source_file','signature','calling_convention']:self.assertFalse(f[k])
        self.assertEqual(r['instructions'][-1]['operands'],'4')

    def test_unrelated_receiver_policies_remain_unknown(self):
        self.assertEqual([(r['address'],r['size']) for r in self.plan['held']],
                         [('0x00454C00',24),('0x00454F70',31)])
        for r in self.plan['held']:
            self.assertEqual(r['origin']['origin'],'unknown');self.assertFalse(r['function']['owner'])
        self.assertEqual(self.plan['historical_snapshots'],[])
        self.assertEqual((self.plan['boundaries'][0]['address'],self.plan['boundaries'][0]['size']),('0x004557F5',11))

    def test_complete_native_data_and_cfg(self):
        V.verify_native(self.plan,self.c.verified_target(),self.c,self.flow)
        self.assertEqual([r['permissions'] for r in self.plan['data']],[0xc0000000,0x40000000,0x40000000])
        self.assertEqual(self.plan['data'][1]['value'],0.0)
        self.assertAlmostEqual(self.plan['data'][2]['value'],0.01)

    def test_consumer_missing_writer_or_decay_is_rejected(self):
        instructions=copy.deepcopy(self.plan['parent']['instructions'])
        for offset in [4400,4394,4425]:
            bad=[r for r in instructions if r['offset']!=offset]
            with self.assertRaises(ValueError):V.consumer_address(bad)

    def test_cropped_parent_or_promoted_type_cannot_earn_credit(self):
        for key in ['parent','functions','public_control']:
            bad=copy.deepcopy(self.plan)
            if key=='parent':bad[key]['size']=4406
            elif key=='functions':bad[key][0]['accepted_function']['signature']='void Set(float)'
            else:bad[key]['methods'].pop(0)
            with self.assertRaises(ValueError):V.verify_plan(bad)

if __name__=='__main__':unittest.main()
