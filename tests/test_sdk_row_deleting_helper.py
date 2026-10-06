import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('row_deletion',ROOT/'scripts/verify-sdk-row-deleting-helper-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)


class SDKRowDeletingHelperTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.plan=json.loads((ROOT/V.EVIDENCE).read_text())
        cls.c=V.module('row_test_target','compare-coff-function.py')
        cls.flow=V.module('row_test_flow','sdk_image_carriers.py')

    def test_one_whole_compiler_origin_and_every_immutable_retained_input(self):
        V.verify_plan(self.plan)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        for p,h in self.plan['retained_sha256'].items():self.assertEqual(V.digest((ROOT/p).read_bytes()),h,p)
        self.assertEqual({r['address']:r['size'] for r in self.plan['functions']},{'0x006114A7':76})
        self.assertEqual(self.plan['functions'][0]['accepted_origin']['origin'],'compiler')

    def test_complete_original_sdk_defining_sections_are_reread_unmasked(self):
        V.verify_context(self.plan,self.c.verified_target(),self.c,self.flow)
        self.assertEqual([(r['symbol'],r['size'],len(r['fields'])) for r in self.plan['archive_records']],
            [('??1TF_Row@@QAE@XZ',9,1),('??_ETF_Row@@QAEPAXI@Z',76,5)])
        bad=copy.deepcopy(self.plan);bad['archive_records'][1]['size']=73
        with self.assertRaises(ValueError):V.verify_context(bad,self.c.verified_target(),self.c,self.flow)

    def test_all_scalar_array_flags_real_cookie_and_ret_four_are_in_the_full_cfg(self):
        V.verify_native(self.plan,self.c.verified_target(),self.c,self.flow)
        r=self.plan['functions'][0];self.assertEqual(r['cfg'],[1,4]);ins={i['offset']:i['operands'] for i in r['instructions']}
        self.assertEqual([ins[i] for i in [5,14,19,22,24,27,32,38,49,51,56,63,73]],
            ['bl, 2','0x6111e1','edi, [esi - 4]','dword ptr [edi]','0xc','0x641d4a','bl, 1','0x640f15','dword ptr [esi]','0x640f15','bl, 1','0x640f15','4'])
        bad=copy.deepcopy(self.plan);bad['context']['witnesses']['0x006114A7']['24']=['push','0x10']
        with self.assertRaises(ValueError):V.verify_native(bad,self.c.verified_target(),self.c,self.flow)

    def test_fresh_compiler_e_preserves_all_three_real_array_delete_differences(self):
        ctl=self.plan['public_control'];r=ctl['comparisons'][1]
        self.assertEqual((r['source_size'],r['target_size'],r['role']),(76,76,'negative'))
        self.assertTrue(r['source_definition']['symbol'].startswith('??_E'))
        self.assertEqual([d['offset'] for d in r['differences']],[39,40,41])
        field=next(b for b in r['bindings'] if b['offset']==39)
        self.assertEqual((field['symbol'],field['target']),('??_V@YAXPAX@Z','0x0064169D'))
        original=self.plan['archive_records'][1];field=next(b for b in original['bindings'] if b['offset']==39)
        self.assertEqual((field['symbol'],field['target_address']),('??3@YAXPAX@Z','0x00640F15'))
        bad=copy.deepcopy(self.plan);bad['public_control']['comparisons'][1]['differences']=[]
        with self.assertRaisesRegex(ValueError,'immutable'):V.verify_plan(bad)

    def test_full_callback_positive_and_scalar_and_ordinary_controls_remain_independent(self):
        r=self.plan['public_control']['comparisons']
        self.assertEqual([(q['source_size'],q['target_size'],q['role']) for q in r],[(9,9,'positive'),(76,76,'negative'),(31,76,'negative'),(16,76,'negative'),(16,76,'negative')])
        for q in r[2:]:
            self.assertEqual([d['offset'] for d in q['differences'] if d['source'] is None],list(range(q['source_size'],76)))

    def test_real_array_iterator_and_both_delete_entries_keep_the_full_free_tail(self):
        anchors={r['address']:r for r in self.plan['anchors']}
        self.assertEqual(anchors['0x00641D4A']['size'],96)
        self.assertEqual([anchors[a]['size'] for a in ['0x0064169D','0x00640F15','0x00642A61']],[5,5,113])
        bad=copy.deepcopy(self.plan);bad['anchors']=[r for r in bad['anchors'] if r['address']!='0x00640F15']
        with self.assertRaisesRegex(ValueError,'bound tail'):V.verify_native(bad,self.c.verified_target(),self.c,self.flow)

    def test_historical_view_requires_the_exact_original_or_accepted_pair(self):
        r=self.plan['functions'][0]
        for name,kind in [('functions.csv','function'),('function-origins.csv','origin')]:
            self.assertEqual(V.historical_rows(name,[r['accepted_'+kind]],r,False),[r['original_'+kind]])
            self.assertEqual(V.historical_rows(name,[r['original_'+kind]],r,True),[r['original_'+kind]])
            bad=dict(r['accepted_'+kind],notes='unapproved')
            with self.assertRaisesRegex(ValueError,'unapproved'):V.historical_rows(name,[bad],r,False)
            with self.assertRaisesRegex(ValueError,'unique pair'):V.historical_rows(name,[],r,False)

    def test_literal_selected_sdk_snapshots_and_other_lifetime_unknowns_are_preserved(self):
        self.assertEqual(len(self.plan['historical_snapshots']),2)
        old=json.loads((ROOT/self.plan['retained_scope']['path']).read_text())
        self.assertIn('0x006114A7',old['retained_unknown'])
        selected=next(r for r in old['sections'] if r['base']=='0x006114A7')
        self.assertEqual(selected['origin']['origin'],'unknown')
        current={r['address']:r for r in V.rows('function-origins.csv')}
        for a in old['retained_unknown']:
            if a!='0x006114A7':self.assertEqual(current[a]['origin'],'unknown')
        for snapshot in self.plan['historical_snapshots']:
            node=json.loads((ROOT/snapshot['path']).read_text())
            for k in snapshot['trail']:node=node[k]
            self.assertEqual(node,snapshot['record'])

    def test_no_private_sdk_source_abi_extent_or_exact_credit(self):
        r=self.plan['functions'][0];old=r['original_function'];new=r['accepted_function']
        self.assertEqual([old[k] for k in ['size','span_end','current_name']],[new[k] for k in ['size','span_end','current_name']])
        self.assertFalse(any(new[k] for k in ['source_file','signature','calling_convention']))
        self.assertEqual(new['match_percent'],'0.00')
        self.assertEqual(self.plan['public_control']['layouts'][0]['values'],[12,4])
        bad=copy.deepcopy(self.plan);bad['functions'][0]['accepted_function']['owner']='library'
        with self.assertRaises(ValueError):V.verify_plan(bad)

    def test_whole_provider_symbol_substitution_or_discarded_field_is_rejected(self):
        for mutate in [lambda p:p['public_control']['comparisons'][1]['bindings'].pop(),
                       lambda p:p['public_control']['providers'][-2].update(address='0x00640F15'),
                       lambda p:p['archive_records'][1]['fields'].pop()]:
            bad=copy.deepcopy(self.plan);mutate(bad)
            with self.assertRaisesRegex(ValueError,'immutable'):V.verify_plan(bad)


if __name__=='__main__':unittest.main()
