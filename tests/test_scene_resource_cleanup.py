import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('scene_cleanup',ROOT/'scripts/verify-scene-resource-cleanup-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)

class SceneResourceCleanupTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.plan=json.loads((ROOT/V.EVIDENCE).read_text())
        cls.c=V.module('cleanup_test_target','compare-coff-function.py')
        cls.flow=V.module('cleanup_test_flow','sdk_image_carriers.py')

    def test_full_immutable_plan_and_retained_inputs(self):
        V.verify_plan(self.plan)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        for p,h in self.plan['retained_sha256'].items():self.assertEqual(V.digest((ROOT/p).read_bytes()),h,p)

    def test_only_five_complete_game_origins_without_private_abi_credit(self):
        self.assertEqual({r['address']:r['size'] for r in self.plan['functions']},V.WHOLE)
        for r in self.plan['functions']:
            f=r['accepted_function'];self.assertEqual(r['cfg'],[1,3])
            self.assertEqual(f['current_name'],r['original_function']['current_name'])
            self.assertEqual((f['status'],f['match_percent']),('unclassified','0.00'))
            for k in ['source_file','signature','calling_convention']:self.assertFalse(f[k])

    def test_same_asset_initialization_and_observed_paired_tables(self):
        contexts=self.plan['contexts']
        self.assertEqual([r['strings'][1]['text'] for r in contexts],[
            'data\\system\\load.dat','data\\system\\logo.dat','data\\system\\replay.dat',
            'data\\system\\replay.dat','data\\system\\result.dat'])
        self.assertEqual(contexts[3]['strings'][0]['text'],'datab')
        for ctx in contexts:
            self.assertEqual(ctx['table']['size'],12);self.assertEqual(len(ctx['table']['words']),3)
            self.assertEqual(ctx['boundaries'][0]['size'],1)

    def test_complete_exception_and_unmasked_source_graph(self):
        c=self.plan['public_control']
        self.assertEqual(len(c['comparisons']),21)
        self.assertEqual(sum(r['size'] for r in c['comparisons']),1169)
        self.assertEqual(sum(r['roots']==[0,8] for r in c['comparisons']),5)
        self.assertEqual(sum(r['roots']==[] for r in c['comparisons']),5)
        self.assertEqual(len(c['weak_references']),4)
        self.assertEqual(len(c['sections']),24)
        self.assertEqual(sum(r['size'] for r in c['emission']),809)
        self.assertEqual(c['headers'],{})

    def test_raw_pointer_and_owned_member_implicit_controls_remain_distinct(self):
        a=self.plan['public_control']['alternatives']
        self.assertEqual(a['??1ExplicitSceneObservation@@UAE@XZ'],127)
        self.assertEqual(a['??1ImplicitSceneObservation@@UAE@XZ'],19)
        self.assertEqual(a['??1ImplicitOwningSceneObservation@@UAE@XZ'],75)
        self.assertEqual(a['??1OwnedResourceObservation@@QAE@XZ'],63)

    def test_full_native_lifetime_and_all_previous_scoped_decisions(self):
        V.verify_native(self.plan,self.c.verified_target(),self.c,self.flow)
        self.assertEqual(len(self.plan['anchors']),29)
        self.assertEqual(sum(r['size'] for r in self.plan['anchors']),10482)
        pairs={r['function']['address']:r for r in self.plan['canonical']}
        self.assertEqual(pairs['0x004251C0']['origin']['origin'],'unknown')
        self.assertEqual(pairs['0x004251C0']['origin']['evidence_id'],'R108')
        self.assertEqual(self.plan['historical_snapshots'],[])

    def test_missing_actual_field_or_changed_type_cannot_bind(self):
        r=self.plan['public_control']['comparisons'][0]
        source=next(q for q in self.plan['public_control']['sections'] if q['section']==r['section'])
        for fields in [source['fields'][:-1],[dict(f,type='DIR32') if f['offset']==82 else f for f in source['fields']]]:
            with self.assertRaises(ValueError):V.bind(bytes(127),fields,int(r['address'],16),r['bindings'],self.flow,[0])

    def test_cropped_exception_or_guessed_private_layout_cannot_earn_credit(self):
        for key in ['contexts','public_control','functions']:
            bad=copy.deepcopy(self.plan)
            if key=='contexts':bad[key][0]['exception_parts'][1]['size']=28
            elif key=='public_control':bad[key]['alternatives']['??1ImplicitSceneObservation@@UAE@XZ']=127
            else:bad[key][0]['accepted_function']['signature']='~LoadingScene()'
            with self.assertRaises(ValueError):V.verify_plan(bad)

if __name__=='__main__':unittest.main()
