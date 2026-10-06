import copy
import importlib.util
import json
from pathlib import Path
import unittest
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('catalog_use',ROOT/'scripts/verify-archive-catalog-use-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)

class ArchiveCatalogUseTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.plan=json.loads((ROOT/V.EVIDENCE).read_text())
        cls.c=V.module('catalog_test_target','compare-coff-function.py')
        cls.flow=V.module('catalog_test_flow','sdk_image_carriers.py')

    def test_whole_immutable_plan_and_every_retained_source_input(self):
        V.verify_plan(self.plan)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        for p,h in self.plan['retained_sha256'].items():self.assertEqual(V.digest((ROOT/p).read_bytes()),h,p)

    def test_only_one_full_origin_without_source_abi_mapping_exact_credit(self):
        self.assertEqual({r['address']:r['size'] for r in self.plan['functions']},V.WHOLE)
        r=self.plan['functions'][0];f=r['accepted_function']
        self.assertEqual(r['cfg'],[1,1])
        self.assertEqual(f['current_name'],r['original_function']['current_name'])
        self.assertEqual((f['status'],f['match_percent']),('unclassified','0.00'))
        self.assertFalse(any(f[k] for k in ['source_file','signature','calling_convention']))

    def test_complete_independent_game_and_vendor_owner_context(self):
        V.verify_native(self.plan,self.c.verified_target(),self.c,self.flow)
        self.assertEqual((len(self.plan['anchors']),sum(r['size'] for r in self.plan['anchors'])),(28,5466))
        self.assertEqual(len(self.plan['canonical']),29)
        self.assertEqual([r['text'] for r in self.plan['context']['strings']],['data','th075.dat','sound','th075bgm.dat','datab','th075b.dat'])
        self.assertEqual([r['name'] for r in self.plan['context']['imports']],['CloseHandle','CreateFileA','ReadFile'])

    def test_whole_public_emission_and_every_actual_field(self):
        c=self.plan['public_control']
        self.assertEqual((len(c['emission']),sum(r['size'] for r in c['emission'])),(50,2045))
        self.assertEqual(sum(len(r['fields']) for r in c['sections']),88)
        self.assertEqual(len(c['headers']),27)
        self.assertEqual(c['weak_references'],[])
        self.assertEqual(c['layout']['values'],[1,1,20,20,40,4])

    def test_whole_ordinary_template_and_implicit_lifetime_alternatives(self):
        c=self.plan['public_control']
        self.assertEqual(sorted(c['alternatives'].values()),[56,56,75,78])
        positive=c['comparisons']
        self.assertEqual((len(positive),sum(r['size'] for r in positive)),(8,542))
        self.assertEqual(sorted(r['size'] for r in positive),[19,19,19,19,56,56,177,177])
        self.assertEqual(sum(len(r['bindings']) for r in positive),28)
        self.assertTrue(all(r['roots']==[0] for r in positive))

    def test_original_clear_and_destructor_definitions_share_tidy(self):
        h=self.plan['context']['header_definitions']
        self.assertEqual([(r['start'],r['end']) for r in h],[(324,329),(412,415),(797,800),(949,969)])
        self.assertIn('~deque()',h[1]['text']);self.assertIn('void clear()',h[2]['text'])
        self.assertTrue(all('_Tidy();' in r['text'] for r in h[1:3]))
        c=self.plan['public_control'];sections={r['section']:r for r in c['sections']}
        for r in c['comparisons']:V.verify_source_owner(r,sections[r['section']]['fields'])

    def test_virtual_bss_storage_has_no_fabricated_raw_bytes(self):
        actual=V.virtual_storage(self.c.verified_target(),0x68be04,44)
        self.assertEqual(actual,self.plan['context']['storage'])
        self.assertEqual(actual['permissions'],0xc0000000)
        self.assertFalse(actual['file_backed'])
        with self.assertRaises(ValueError):V.virtual_storage(self.c.verified_target(),0xffffffff,44)

    def test_raw_pointer_observation_cannot_invent_original_owner_layout(self):
        bad=copy.deepcopy(self.plan);bad['public_control']['layout']['values'][0]=40
        with self.assertRaises(ValueError):V.verify_plan(bad)
        bad=copy.deepcopy(self.plan);bad['functions'][0]['accepted_function']['signature']='ArchiveCatalog::ArchiveCatalog()'
        with self.assertRaises(ValueError):V.verify_plan(bad)

    def test_false_clear_destructor_symbol_is_rejected(self):
        r=copy.deepcopy(self.plan['public_control']['comparisons'][0])
        fields=copy.deepcopy(next(q['fields'] for q in self.plan['public_control']['sections'] if q['section']==r['section']))
        next(f for f in fields if f['type']=='REL32')['symbol']='??1?$deque@PAD@std@@QAE@XZ'
        with self.assertRaisesRegex(ValueError,'relabels public clear'):V.verify_source_owner(r,fields)

    def test_wrong_paired_queue_and_typed_tidy_target_are_rejected(self):
        ctl=self.plan['public_control'];sections={r['section']:r for r in ctl['sections']}
        for index,field in [(0,2),(1,0)]:
            r=copy.deepcopy(ctl['comparisons'][index]);r['bindings'][field]['target']='0x0041DF50'
            with self.assertRaises(ValueError):V.verify_source_owner(r,sections[r['section']]['fields'])

    def test_cropped_function_or_exception_carrier_is_rejected(self):
        for mutation in ['function','carrier']:
            bad=copy.deepcopy(self.plan)
            if mutation=='function':bad['functions'][0]['size']=55
            else:next(r for r in bad['public_control']['sections'] if r['size']==36)['size']=28
            with self.assertRaises(ValueError):V.verify_plan(bad)

    def test_prior_vendor_aliases_and_original_snapshot_state_are_literal(self):
        self.assertEqual(self.plan['historical_snapshots'],[])
        for r in self.plan['context']['vendor_records']:self.assertIn(r['record'],V.rows(r['path']))
        pairs={r['function']['address']:r for r in self.plan['canonical']}
        for a in ['0x0041DCD0','0x0041DF50']:
            self.assertEqual(pairs[a]['origin']['evidence_id'],'R077')
            self.assertIn('Destructor',pairs[a]['function']['proposed_name'])

if __name__=='__main__':unittest.main()
