"""Reject incomplete vendor evidence and unsupported real SDK field bindings."""
import copy
import importlib.util
import json
from pathlib import Path
import struct
import unittest

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('sdk_file_tests',ROOT/'scripts/verify-sdk-file-image-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)
SDK=V.module('sdk_file_test_cfg','verify-sdk-origins.py')

class SDKFileImageEvidenceTests(unittest.TestCase):
    def setUp(self):
        self.m=json.loads((ROOT/V.EVIDENCE).read_text())
        self.code=b'\xe8\0\0\0\0\xc3'
        self.field=dict(offset=1,type_id=20,type='REL32',symbol='_callee',addend=0,local_symbol_offset=None)
        self.binding=dict(self.field,target_address='0x00402000',kind='callee')

    def call(self,code=None,fields=None,bindings=None,callees=None,imports=None):
        return V.bind_fields(self.code if code is None else code,[self.field] if fields is None else fields,
                             [self.binding] if bindings is None else bindings,0x401000,
                             {'_callee':0x402000} if callees is None else callees,
                             {} if imports is None else imports,lambda name,dest:b'\0\0\x80\x3f')

    def test_manifest_retains_complete_source_scope(self):
        V.verify_plan(self.m)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)

    def test_independent_callee_links_complete_call(self):
        code,calls,data=self.call()
        self.assertEqual(struct.unpack_from('<I',code,1)[0],0xffb)
        self.assertEqual(SDK.verify_control_flow(code,0x401000,calls,data),0)

    def test_missing_source_callee_cannot_be_replaced_by_name(self):
        with self.assertRaises(ValueError):self.call(callees={})

    def test_real_callee_address_cannot_be_overridden(self):
        with self.assertRaises(ValueError):self.call(callees={'_callee':0x403000})

    def test_call_field_cannot_cover_mov_operand(self):
        with self.assertRaises(ValueError):self.call(code=b'\xb8\0\0\0\0\xc3')

    def test_partial_binding_coverage_is_rejected(self):
        with self.assertRaises(ValueError):self.call(bindings=[])

    def test_duplicate_fields_are_rejected(self):
        with self.assertRaises(ValueError):self.call(fields=[self.field,self.field],bindings=[self.binding,self.binding])

    def test_nonzero_source_addend_is_rejected(self):
        f=dict(self.field,addend=1);b=dict(self.binding,addend=1)
        with self.assertRaises(ValueError):self.call(fields=[f],bindings=[b])

    def test_nonzero_original_source_field_is_rejected(self):
        with self.assertRaises(ValueError):self.call(code=b'\xe8\x01\0\0\0\xc3')

    def test_local_symbol_alias_is_not_assumed(self):
        f=dict(self.field,local_symbol_offset=0);b=dict(self.binding,local_symbol_offset=0)
        with self.assertRaises(ValueError):self.call(fields=[f],bindings=[b])

    def test_field_crossing_complete_extent_is_rejected(self):
        with self.assertRaises(ValueError):self.call(code=b'\xe8\0\0')

    def test_binding_source_symbol_cannot_change(self):
        with self.assertRaises(ValueError):self.call(bindings=[dict(self.binding,symbol='_other')])

    def test_named_iat_uses_actual_pe_import_identity(self):
        f=dict(self.field,offset=2,type_id=6,type='DIR32',symbol='__imp__CloseHandle@4')
        b=dict(f,target_address='0x00657138',kind='import',dll='KERNEL32.dll',name='CloseHandle')
        code,calls,data=self.call(code=b'\xff\x15\0\0\0\0\xc3',fields=[f],bindings=[b],imports={0x657138:('KERNEL32.dll','CloseHandle')})
        self.assertEqual(SDK.verify_control_flow(code,0x401000,calls,data),1)
        for imports in ({},{0x657138:('USER32.dll','CloseHandle')},{0x657138:('KERNEL32.dll','WriteFile')}):
            with self.assertRaises(ValueError):self.call(code=b'\xff\x15\0\0\0\0\xc3',fields=[f],bindings=[b],imports=imports)

    def test_iat_source_spelling_cannot_be_guessed(self):
        f=dict(self.field,offset=2,type_id=6,type='DIR32',symbol='__imp__WrongName@4')
        b=dict(f,target_address='0x00657138',kind='import',dll='KERNEL32.dll',name='CloseHandle')
        with self.assertRaises(ValueError):self.call(code=b'\xff\x15\0\0\0\0\xc3',fields=[f],bindings=[b],imports={0x657138:('KERNEL32.dll','CloseHandle')})

    def test_opaque_state_field_is_not_a_scalar(self):
        f=dict(self.field,type_id=6,type='DIR32',symbol='_state');b=dict(f,target_address='0x00670000',kind='scalar',literal_hex='0000803f')
        with self.assertRaises(ValueError):self.call(code=b'\xa1\0\0\0\0\xc3',fields=[f],bindings=[b])

    def test_scalar_bits_must_come_from_complete_member(self):
        f=dict(self.field,type_id=6,type='DIR32',symbol='__real@3f800000');b=dict(f,target_address='0x0065747C',kind='scalar',literal_hex='00000040')
        with self.assertRaises(ValueError):self.call(code=b'\xa1\0\0\0\0\xc3',fields=[f],bindings=[b])

    def test_catalogue_cannot_override_retained_callee(self):
        self.m['functions'][0]['bindings'][2]['target_address']='0x00401000'
        with self.assertRaises(ValueError):V.verify_plan(self.m)

    def test_native_extent_is_not_truncated(self):
        self.m['functions'][0]['size']-=1
        with self.assertRaises(ValueError):V.verify_plan(self.m)

    def test_library_evidence_cannot_grant_exact_credit(self):
        self.m['functions'][0]['accepted_function']['match_percent']='100.00'
        with self.assertRaises(ValueError):V.verify_plan(self.m)

    def test_no_source_or_abi_is_invented(self):
        for key in ('source_file','signature','calling_convention'):
            m=copy.deepcopy(self.m);m['functions'][0]['accepted_function'][key]='invented'
            with self.assertRaises(ValueError):V.verify_plan(m)

    def test_alias_must_share_actual_primary_section_and_offset(self):
        defs=[dict(symbol='__chkstk',offset=0,section=1,type=32,storage=2),dict(symbol='__alloca_probe',offset=0,section=1,type=0,storage=2)]
        V.verify_alias(defs,'__chkstk','__alloca_probe')
        for key,value in [('offset',1),('section',2),('type',32),('storage',3)]:
            changed=copy.deepcopy(defs);changed[1][key]=value
            with self.assertRaises(ValueError):V.verify_alias(changed,'__chkstk','__alloca_probe')

    def test_internal_final_tail_is_preserved(self):
        self.assertEqual(SDK.verify_control_flow(b'\xc3\xeb\xfd',0x401000),0)
        self.assertEqual(V.flow_counts(b'\xc3\xeb\xfd',0x401000),[1,1])

if __name__=='__main__':unittest.main()
