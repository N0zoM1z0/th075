import copy
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import unittest

ROOT=Path(__file__).resolve().parents[1]
def module(name,filename):
    spec=importlib.util.spec_from_file_location(name,ROOT/'scripts'/filename)
    result=importlib.util.module_from_spec(spec);spec.loader.exec_module(result);return result
verify=module('test_x3d','verify-sdk-x3d-origins.py')
carrier=module('test_x3d_carrier','sdk_x3d_carriers.py')


class SDKX3DTests(unittest.TestCase):
    def setUp(self):self.m=json.loads((ROOT/verify.EVIDENCE).read_text())

    def reject(self,mutate):
        m=copy.deepcopy(self.m);mutate(m)
        with self.assertRaises(ValueError):verify.verify_plan(m)

    def test_complete_immutable_scope(self):
        verify.verify_plan(self.m)
        self.assertEqual(hashlib.sha256((ROOT/verify.EVIDENCE).read_bytes()).hexdigest(),verify.MANIFEST_SHA256)

    def test_last_optional_k7_callback_cannot_be_omitted(self):
        self.reject(lambda m:m['controls'][0]['fields'].pop())

    def test_initializer_cannot_stop_before_k7_overrides(self):
        self.reject(lambda m:m['controls'][0].update(size=507))

    def test_switch_table_cannot_be_truncated_to_return(self):
        self.reject(lambda m:next(r for r in m['controls'] if r['switch']).update(size=360))

    def test_inline_table_does_not_receive_function_credit(self):
        self.reject(lambda m:next(r for r in m['functions'] if r['address']=='0x00639897').update(size=392))

    def test_table_is_not_alignment(self):
        self.reject(lambda m:next(r for r in m['controls'] if r['switch'])['flow'].update(table_size=0))

    def test_whole_math_section_is_not_an_auxless_prefix(self):
        self.reject(lambda m:next(r for r in m['controls'] if r['kind']=='whole-math-section').update(size=247))

    def test_source_alias_cannot_be_hidden(self):
        self.reject(lambda m:next(p for r in m['controls'] if r['kind']=='whole-math-section' for p in r['flow']['partitions'] if p['offset']==1952)['aliases'].pop())

    def test_whole_math_constants_cannot_be_selected_words(self):
        self.reject(lambda m:m['data'][1].update(size=8))

    def test_initialized_writable_math_data_is_not_readonly(self):
        self.reject(lambda m:m['data'][1]['source'].update(flags=0x40700040))

    def test_original_readonly_constant_remains_readonly(self):
        self.reject(lambda m:m['data'][0]['source'].update(flags=0xc0400040))

    def test_pending_public_dispatch_cannot_be_credited(self):
        self.reject(lambda m:m['pending'][1]['origin'].update(origin='library'))

    def test_cpu_selector_cannot_be_silently_linked(self):
        self.reject(lambda m:m['pending'][0].update(bindings=[]))

    def test_original_function_extent_cannot_change(self):
        self.reject(lambda m:m['functions'][0]['accepted_function'].update(size='549'))

    def test_source_credit_is_separate_from_original_archive_evidence(self):
        self.reject(lambda m:m['functions'][0]['accepted_function'].update(source_file='src/Fake.cpp'))

    def test_math_partition_extent_must_support_selected_function(self):
        def change(m):
            math=next(r for r in m['controls'] if r['kind']=='whole-math-section')
            math['flow']['partitions'][1]['flow']['extent']-=1
            math['flow']['partitions'][0]['flow']['extent']+=1
        self.reject(change)

    def test_unreachable_nonidentity_instruction_is_not_alignment(self):
        with self.assertRaises(ValueError):carrier.flow(bytes.fromhex('c3 b801000000'),0,[0],[],{},{})

    def test_original_add_padding_is_retained_with_eflags_effect(self):
        result=carrier.flow(bytes.fromhex('c3 0500000000'),0,[0],[],{},{})
        self.assertEqual((result['extent'],result['alignment_size']),(1,5))
        self.assertEqual(result['padding'][0]['mnemonic'],'add')

    def test_internal_identity_alignment_is_recorded(self):
        result=carrier.flow(bytes.fromhex('eb02 90 90 c3'),0,[0],[],{},{})
        self.assertEqual([r['offset'] for r in result['internal_padding']],[2,3])

    def test_real_field_cannot_be_hidden_in_internal_padding(self):
        with self.assertRaises(ValueError):carrier.flow(bytes.fromhex('eb02 90 90 c3'),0,[0],[],{},{2:0})

    def test_external_tail_requires_its_actual_bound_whole_owner(self):
        code=b'\xe9'+struct.pack('<i',0x2000-0x1000-5)
        with self.assertRaises(ValueError):carrier.flow(code,0x1000,[0],[],{},{})
        self.assertEqual(carrier.flow(code,0x1000,[0],[],{0x1001:0x2000},{})['extent'],5)

    def test_fields_use_source_member_section_and_index(self):
        f=dict(symbol='local',symbol_section=1,symbol_type=0,symbol_storage=3,symbol_index=4)
        self.assertNotEqual(verify.field_key(10,f),verify.field_key(20,f))

    def test_switch_labels_do_not_lose_original_storage_class(self):
        f=dict(symbol='label',symbol_section=1,symbol_type=0,symbol_storage=6,symbol_index=4)
        self.assertEqual(verify.field_key(10,f),(10,1,4))

    def test_switch_requires_original_eight_way_guard(self):
        address=0x1000;table=13
        code=bytes.fromhex('83f807 7707 ff2485')+struct.pack('<I',address+table)+b'\xc3'+struct.pack('<8I',*[address+12]*8)
        fields=[dict(offset=table+4*i,type='DIR32',symbol_type=0,symbol_storage=6,local_symbol_offset=12,symbol_offset=12) for i in range(8)]
        data={address+8:address+table,**{address+table+4*i:address+12 for i in range(8)}}
        switch=dict(offset=table,jump_offset=5)
        self.assertEqual(carrier.flow(code,address,[0],fields,{},data,switch)['table_size'],32)
        changed=bytearray(code);changed[2]=8
        with self.assertRaises(ValueError):carrier.flow(changed,address,[0],fields,{},data,switch)


if __name__=='__main__':unittest.main()
