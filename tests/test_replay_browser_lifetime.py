import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('browser_lifetime',ROOT/'scripts/verify-replay-browser-lifetime-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)


class ReplayBrowserLifetimeTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.plan=json.loads((ROOT/V.EVIDENCE).read_text())
        cls.c=V.module('browser_test_target','compare-coff-function.py')
        cls.flow=V.module('browser_test_flow','sdk_image_carriers.py')
        cls.native={r['address']:r for r in cls.plan['functions']+cls.plan['anchors']}

    def test_one_immutable_whole_authored_transition_and_all_retained_inputs(self):
        V.verify_plan(self.plan)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        for p,h in self.plan['retained_sha256'].items():self.assertEqual(V.digest((ROOT/p).read_bytes()),h,p)
        self.assertEqual({r['address']:r['size'] for r in self.plan['functions']},{'0x0042C560':265})
        self.assertEqual(self.plan['historical_snapshots'],[])
        self.assertEqual(self.plan['cold_dependencies'],[['scripts/verify-vendor-deque-destructor-origins.py']])

    def test_whole_policy_closes_saved_selection_array_child_and_all_members(self):
        V.verify_native(self.plan,self.c.verified_target(),self.c,self.flow)
        ins={i['offset']:i['operands'] for i in self.native['0x0042C560']['instructions']}
        self.assertEqual([ins[i] for i in [53,84,104,118,134,174,201,216,231,246]],
            ['word ptr [0x67162c], dx','0x41dd50','0x41ddc0','0x64169d','0x41df50','0x425460','0x4143b0','0x42db80','0x420420','0x431f40'])
        self.assertEqual(self.native['0x0042C560']['cfg'],[1,6])
        bad=copy.deepcopy(self.plan);bad['context']['witnesses']['0x0042C560']['118']=['call','0x640f15']
        with self.assertRaises(ValueError):V.verify_native(bad,self.c.verified_target(),self.c,self.flow)

    def test_real_array_and_scalar_delete_entries_retain_the_complete_bound_chain(self):
        for a,destination in [('0x0064169D','0x640f15'),('0x00640F15','0x642a61')]:
            r=self.native[a];self.assertEqual((r['size'],r['instructions'][0]['mnemonic'],r['instructions'][0]['operands']),(5,'jmp',destination))
        self.assertEqual(self.native['0x00642A61']['size'],113)
        bad=copy.deepcopy(self.plan);bad['anchors']=[r for r in bad['anchors'] if r['address']!='0x00640F15']
        with self.assertRaisesRegex(ValueError,'bound tail'):V.verify_native(bad,self.c.verified_target(),self.c,self.flow)

    def test_independent_filename_production_is_same_deque_and_true_new_array(self):
        r=self.native['0x0042D470'];self.assertEqual((r['size'],r['authored_record']['evidence_id']),(613,'R040'))
        ins={i['offset']:i['operands'] for i in r['instructions']}
        self.assertEqual([ins[i] for i in [30,35,77,85,90,110,124,199,244,249,283,356]],
            ['0x657fd8','dword ptr [0x657068]','ecx, 0xc','0x104','0x6416a2','ecx, 0xc','dword ptr [eax], edx','dword ptr [0x657064]','0x104','0x6416a2','dword ptr [eax], ecx','dword ptr [0x657060]'])
        self.assertEqual(self.plan['context']['strings'][0]['text'],'replay\\*.rep')
        self.assertEqual([r['name'] for r in self.plan['context']['imports'][:3]],['FindFirstFileA','FindNextFileA','FindClose'])
        self.assertEqual(self.native['0x006416A2']['instructions'][0]['operands'],'0x64159d')

    def test_saved_selection_initialization_and_actual_texture_cleanup_provider(self):
        ins={i['offset']:i['operands'] for i in self.native['0x0042C3D0']['instructions']}
        self.assertEqual(ins[353],'dx, word ptr [0x67162c]')
        self.assertEqual(ins[346],'byte ptr [eax + 0x51], 0')
        r=self.native['0x00425460'];self.assertEqual(r['instructions'][5]['operands'],'0x40ae40')
        self.assertEqual((self.native['0x0040AE40']['size'],self.native['0x0040AE40']['authored_record']['evidence_id']),(434,'R017'))
        self.assertNotIn('0x00425490',self.native)

    def test_full_shared_eh_and_metadata_have_all_real_roots_and_offsets(self):
        comparisons=self.plan['public_control']['comparisons'];eh=next(r for r in comparisons if r['address']=='0x0065596E');data=next(r for r in comparisons if r['address']=='0x00668D58')
        self.assertEqual((eh['source_size'],eh['roots'],eh['source_definition']['offset']),(51,[0,8,19,30,41],41))
        self.assertEqual((data['source_size'],data['roots'],data['source_definition']['offset']),(60,[],32))
        self.assertEqual(len(self.plan['context']['frames']),1)
        bad=copy.deepcopy(self.plan);bad['public_control']['comparisons'][1]['source_size']=41
        with self.assertRaisesRegex(ValueError,'immutable'):V.verify_plan(bad)

    def test_whole_observed_table_uses_real_weak_fallback_and_full_callbacks(self):
        ctl=self.plan['public_control'];table=next(r for r in ctl['comparisons'] if r['address']=='0x00658008')
        self.assertEqual(table['source_size'],12)
        self.assertEqual([b['target'] for b in table['bindings']],['0x0042DAC0','0x0042C670','0x0042CA60'])
        alias=ctl['weak_references'][0]
        self.assertEqual((alias['source_definition']['section'],alias['source_definition']['storage'],alias['search_characteristics']),(0,105,2))
        self.assertEqual(alias['fallback_definition']['section'],10)
        self.assertEqual([self.native[a]['size'] for a in ['0x0042C670','0x0042CA60']],[1005,2246])
        bad=copy.deepcopy(self.plan);next(r for r in bad['public_control']['comparisons'] if r['address']=='0x00658008')['source_size']=8
        with self.assertRaisesRegex(ValueError,'immutable'):V.verify_plan(bad)

    def test_genuine_implicit_and_empty_controls_keep_every_missing_target_tail_byte(self):
        negatives=[r for r in self.plan['public_control']['comparisons'] if r['role']=='negative']
        self.assertEqual([(r['source_size'],r['target_size']) for r in negatives],[(114,265),(105,265)])
        self.assertIn('??1ImplicitReplayBrowserLifetimeObservation',negatives[1]['source_definition']['symbol'])
        for r in negatives:
            self.assertEqual([d['offset'] for d in r['differences'] if d['source'] is None],list(range(r['source_size'],265)))
            self.assertTrue(all(d['target'] is not None for d in r['differences']))
        bad=copy.deepcopy(self.plan);bad['public_control']['comparisons'][-1]['differences'].pop()
        with self.assertRaisesRegex(ValueError,'immutable'):V.verify_plan(bad)

    def test_complete_sdk_index_graph_and_full_current_source_emission(self):
        ctl=self.plan['public_control']
        self.assertEqual((len(ctl['emission']),sum(r['size'] for r in ctl['emission']),sum(len(r['fields']) for r in ctl['sections'])),(82,3855,173))
        self.assertEqual((len(ctl['comparisons']),sum(r['source_size'] for r in ctl['comparisons']),sum(len(r['bindings']) for r in ctl['comparisons'])),(21,1133,61))
        self.assertEqual((len(ctl['headers']),len(ctl['weak_references'])),(27,4))
        original=json.loads((ROOT/self.plan['context']['index_proof']['path']).read_text())
        self.assertEqual(self.plan['context']['index_proof']['sections'],[r for r in original['sections'] if r['group']==2])
        self.assertEqual(len(self.plan['context']['index_proof']['sections']),8)

    def test_generic_layout_and_names_do_not_gain_original_private_or_exact_credit(self):
        r=self.plan['functions'][0];f=r['accepted_function'];old=r['original_function']
        self.assertEqual([f[k] for k in ['current_name','size','span_end']],[old[k] for k in ['current_name','size','span_end']])
        self.assertFalse(any(f[k] for k in ['source_file','calling_convention','signature']))
        self.assertEqual(f['match_percent'],'0.00')
        self.assertEqual(self.plan['public_control']['layouts'][0]['values'],[8,4,76,20,20,20])
        providers={r['symbol']:r for r in self.plan['public_control']['providers']}
        self.assertNotEqual(providers['??_V@YAXPAX@Z']['address'],providers['??3@YAXPAX@Z']['address'])
        bad=copy.deepcopy(self.plan);bad['functions'][0]['accepted_function']['source_file']='src/replay.cpp'
        with self.assertRaises(ValueError):V.verify_plan(bad)


if __name__=='__main__':unittest.main()
