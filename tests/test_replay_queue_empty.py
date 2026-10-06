import copy
import importlib.util
import json
from pathlib import Path
import unittest
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('replay_queue_empty',ROOT/'scripts/verify-replay-queue-empty-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)

class ReplayQueueEmptyTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.plan=json.loads((ROOT/V.EVIDENCE).read_text())
        cls.c=V.module('replay_queue_test_target','compare-coff-function.py')
        cls.flow=V.module('replay_queue_test_flow','sdk_image_carriers.py')

    def test_whole_immutable_plan_and_every_retained_input(self):
        V.verify_plan(self.plan)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        for p,h in self.plan['retained_sha256'].items():self.assertEqual(V.digest((ROOT/p).read_bytes()),h,p)

    def test_one_whole_origin_without_original_abi_source_mapping_or_exact(self):
        self.assertEqual({r['address']:r['size'] for r in self.plan['functions']},V.WHOLE)
        r=self.plan['functions'][0];f=r['accepted_function']
        self.assertEqual(r['cfg'],[1,2]);self.assertEqual(f['current_name'],r['original_function']['current_name'])
        self.assertEqual((f['status'],f['match_percent']),('unclassified','0.00'))
        self.assertFalse(any(f[k] for k in ['signature','calling_convention','source_file']))
        self.assertEqual(self.plan['historical_snapshots'],[])
        self.assertEqual(self.plan['context']['boundaries'][0]['size'],13)

    def test_complete_file_protocol_live_input_and_battle_owners(self):
        V.verify_native(self.plan,self.c.verified_target(),self.c,self.flow)
        self.assertEqual((len(self.plan['anchors']),sum(r['size'] for r in self.plan['anchors'])),(12,10568))
        self.assertEqual(len(self.plan['canonical']),13)
        imports=self.plan['context']['imports']
        self.assertEqual([r['name'] for r in imports],['CreateFileA','ReadFile','WriteFile','CloseHandle','SetFilePointer'])

    def test_same_global_primary_queue_and_only_low_byte_result(self):
        anchors={r['address']:r for r in self.plan['anchors']}
        battle={i['offset']:i for i in anchors['0x0043B610']['instructions']}
        self.assertEqual(battle[4596]['operands'],'ecx, 0x671750')
        self.assertEqual(battle[4601]['operands'],'0x4142d0')
        self.assertEqual(battle[4606]['operands'],'edx, al')
        consumer={i['offset']:i for i in anchors['0x00452F10']['instructions']}
        for offset in [147,161,176,950]:self.assertEqual(consumer[offset]['operands'],'ecx, 0x6718a4')
        self.assertEqual([consumer[i]['operands'] for i in [152,166,181,955]],['0x414430','0x454d50','0x454d70','0x414450'])
        self.assertEqual(0x671750+0x154,0x6718a4)
        selected={i['offset']:i for i in self.plan['functions'][0]['instructions']}
        self.assertEqual((selected[25]['operands'],selected[29]['operands']),('al, al','al, 1'))

    def test_four_loader_queues_remain_distinct(self):
        loader=next(r for r in self.plan['anchors'] if r['address']=='0x00413AC0')
        adds=[i['operands'] for i in loader['instructions'] if i['mnemonic']=='add' and i['operands'].startswith('ecx, 0x')]
        self.assertEqual(adds,['ecx, 0x154','ecx, 0x154','ecx, 0x168','ecx, 0x168','ecx, 0x17c','ecx, 0x17c','ecx, 0x190','ecx, 0x190'])
        self.assertEqual(loader['size'],792)

    def test_actual_file_backed_storage_has_no_invented_private_size(self):
        ctx=self.plan['context'];storage=V.BASE.BASE.BASE.virtual_storage(self.c.verified_target(),0x671750,420)
        self.assertEqual(storage,ctx['storage']);self.assertTrue(storage['file_backed'])
        self.assertEqual(storage['permissions'],0xc0000000)
        self.assertEqual(V.digest(self.c.pe_bytes_at(self.c.verified_target(),0x671750,420)),ctx['storage_sha256'])
        self.assertEqual(self.plan['public_control']['layouts'][0]['values'],[24,20,20,4])

    def test_every_compact_source_section_field_header_and_weak_record(self):
        c=self.plan['public_control']
        self.assertEqual((len(c['emission']),sum(r['size'] for r in c['emission'])),(9,182))
        self.assertEqual(sum(len(r['fields']) for r in c['sections']),5)
        self.assertEqual(len(c['headers']),31);self.assertEqual(c['weak_references'],[])
        layout=next(r for r in c['sections'] if r['section']==c['layouts'][0]['section'])
        self.assertEqual((layout['size'],layout['fields']),(16,[]))
        ordinary=next(r for r in c['sections'] if r['section']==4)
        self.assertEqual(next(i['operands'] for i in ordinary['instructions'] if i['offset']==10),'ecx, 4')

    def test_full_original_definitions_and_independent_public_providers(self):
        h=self.plan['context']['header_definitions']
        self.assertEqual([(r['start'],r['end']) for r in h],[(490,493),(500,503),(34,37)])
        self.assertIn('return (_Mysize);',h[0]['text']);self.assertIn('return (_Mysize == 0);',h[1]['text'])
        self.assertIn('return (c.empty());',h[2]['text'])
        self.assertEqual([(r['size'],r['address']) for r in self.plan['public_control']['providers']],[(17,'0x00414430'),(25,'0x004158B0')])
        self.assertEqual(self.plan['cold_dependencies'],['scripts/verify-deque-size-context-origins.py','scripts/verify-vendor-deque-empty-origins.py'])

    def test_complete_compact_borrowed_and_original_library_alternatives(self):
        c=self.plan['public_control'];positives=[r for r in c['comparisons'] if r['role']=='positive'];negatives=[r for r in c['comparisons'] if r['role']=='negative']
        self.assertEqual([r['source_size'] for r in positives],[17,25])
        self.assertEqual([r['source_size'] for r in negatives],[32,23,25,19])
        for r in negatives:
            self.assertEqual(r['target_size'],35)
            self.assertEqual([d['offset'] for d in r['differences'] if d['source'] is None],list(range(r['source_size'],35)))
        self.assertEqual(negatives[-1]['bindings'][0]['target'],'0x004158B0')
        self.assertNotEqual(negatives[-1]['bindings'][0]['target'],'0x00414430')

    def test_no_false_queue_empty_to_size_binding_or_field_type(self):
        c=self.plan['public_control'];r=c['comparisons'][-1];fields=next(q['fields'] for q in c['sections'] if q['section']==r['section']);owners={q['symbol']:q['address'] for q in c['providers']}
        V.verify_binding_owners(r,fields,owners)
        bad=copy.deepcopy(r);bad['bindings'][0]['target']='0x00414430'
        with self.assertRaises(ValueError):V.verify_binding_owners(bad,fields,owners)
        bad_fields=copy.deepcopy(fields);bad_fields[0]['type']='DIR32'
        with self.assertRaises(ValueError):V.verify_binding_owners(r,bad_fields,owners)

    def test_full_negative_guard_rejects_prefixes_and_missing_trailing_bytes(self):
        r=self.plan['public_control']['comparisons'][2];actual=self.c.pe_bytes_at(self.c.verified_target(),0x4142d0,35);linked=bytearray(actual[:32])
        for d in r['differences']:
            if d['source'] is not None:linked[d['offset']]=d['source']
        V.verify_comparison(r,bytes(linked),actual)
        with self.assertRaisesRegex(ValueError,'crops'):V.verify_comparison(r,bytes(linked),actual[:32])
        bad=copy.deepcopy(r);bad['differences']=[d for d in bad['differences'] if d['source'] is not None]
        with self.assertRaisesRegex(ValueError,'discards'):V.verify_comparison(bad,bytes(linked),actual)

    def test_fake_private_layout_abi_or_cropped_game_owner_is_rejected(self):
        for kind in ['layout','abi','extent']:
            bad=copy.deepcopy(self.plan)
            if kind=='layout':bad['public_control']['layouts'][0]['values']=[420,20,20,4]
            elif kind=='abi':bad['functions'][0]['accepted_function']['signature']='unsigned int __fastcall empty()'
            else:next(r for r in bad['anchors'] if r['address']=='0x0043B610')['size']=100
            with self.assertRaises(ValueError):V.verify_plan(bad)

if __name__=='__main__':unittest.main()
