import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('scene_texture',ROOT/'scripts/verify-scene-texture-cleanup-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)

class SceneTextureCleanupTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.plan=json.loads((ROOT/V.EVIDENCE).read_text())
        cls.c=V.module('texture_test_target','compare-coff-function.py')
        cls.flow=V.module('texture_test_flow','sdk_image_carriers.py')

    def test_complete_immutable_plan_and_retained_inputs(self):
        V.verify_plan(self.plan)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        for p,h in self.plan['retained_sha256'].items():self.assertEqual(V.digest((ROOT/p).read_bytes()),h,p)

    def test_only_one_full_origin_without_private_interface_or_exact_credit(self):
        r=self.plan['functions'][0];f=r['accepted_function']
        self.assertEqual((r['address'],r['size'],r['cfg']),('0x00428E60',154,[1,4]))
        self.assertEqual(f['current_name'],r['original_function']['current_name'])
        self.assertEqual((f['status'],f['match_percent']),('unclassified','0.00'))
        for k in ['source_file','signature','calling_convention']:self.assertFalse(f[k])
        pairs=[(i['mnemonic'],i['operands']) for i in r['instructions']]
        self.assertIn(('cmp','dword ptr [edx + 0xc], 0'),pairs)
        self.assertIn(('call','dword ptr [ecx + 8]'),pairs)

    def test_real_options_asset_and_independent_full_texture_producers(self):
        ctx=self.plan['contexts'][0]
        self.assertEqual(ctx['strings'][1]['text'],'data\\system\\option.dat')
        anchors={r['address']:r for r in self.plan['anchors']}
        self.assertEqual(anchors['0x00428D60']['size'],251)
        self.assertEqual(anchors['0x00401C20']['size'],340)
        self.assertEqual(anchors['0x00605B61']['size'],102)
        p=anchors['0x00401C20']['instructions']
        self.assertEqual(sum(i['mnemonic']=='call' and i['operands']=='0x605b61' for i in p),2)
        self.assertIn('config/sdk-graphics-origin-evidence.json',self.plan['retained_sha256'])

    def test_complete_cold_public_header_and_source_emission(self):
        c=self.plan['public_control']
        self.assertEqual(len(c['headers']),73)
        self.assertTrue(any(p.lower().endswith('/d3d8.h') for p in c['headers']))
        self.assertTrue(any(p.lower().endswith('/unknwn.h') for p in c['headers']))
        self.assertEqual(len(c['sections']),15)
        self.assertEqual(sum(r['size'] for r in c['emission']),522)
        self.assertEqual(sum(len(r['fields']) for r in c['sections']),30)
        self.assertEqual(len(c['weak_references']),3)

    def test_complete_unmasked_code_and_exception_bindings(self):
        c=self.plan['public_control']
        self.assertEqual([r['size'] for r in c['comparisons']],[154,44,18,36,44])
        self.assertEqual(sum(r['size'] for r in c['comparisons']),296)
        self.assertEqual(c['comparisons'][2]['roots'],[0,8])
        self.assertEqual(c['comparisons'][3]['roots'],[])
        self.assertEqual(sorted(c['alternatives'].values()),[19,154])

    def test_whole_native_context_and_retained_unknown_base(self):
        V.verify_native(self.plan,self.c.verified_target(),self.c,self.flow)
        self.assertEqual(len(self.plan['anchors']),15)
        self.assertEqual(sum(r['size'] for r in self.plan['anchors']),5385)
        pairs={r['function']['address']:r for r in self.plan['canonical']}
        self.assertEqual(pairs['0x004251C0']['origin']['origin'],'unknown')
        self.assertEqual(self.plan['historical_snapshots'],[])
        b=self.plan['contexts'][0]['boundaries'][0]
        self.assertEqual((b['address'],b['size']),('0x00428EFA',6))

    def test_cropped_extent_or_promoted_private_type_is_rejected(self):
        for key in ['functions','public_control']:
            bad=copy.deepcopy(self.plan)
            if key=='functions':bad[key][0]['accepted_function']['signature']='IDirect3DTexture8*'
            else:bad[key]['comparisons'][0]['size']=127
            with self.assertRaises(ValueError):V.verify_plan(bad)

    def test_virtual_slot_mutation_breaks_whole_native_proof(self):
        bad=copy.deepcopy(self.plan);r=bad['functions'][0]
        call=next(i for i in r['instructions'] if i['mnemonic']=='call' and i['operands']=='dword ptr [ecx + 8]')
        call['operands']='dword ptr [ecx + 4]'
        with self.assertRaises(ValueError):V.verify_native(bad,self.c.verified_target(),self.c,self.flow)

if __name__=='__main__':unittest.main()
