"""Guard complete SDK shader/font ownership, imports and foreign source protocols."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
SPEC=importlib.util.spec_from_file_location('shader_font_tests',ROOT/'scripts/verify-sdk-shader-font-origins.py')
V=importlib.util.module_from_spec(SPEC);SPEC.loader.exec_module(V)
M=json.loads((ROOT/V.EVIDENCE).read_text())


class ShaderFontProvenanceTests(unittest.TestCase):
    def reject(self,mutate):
        m=copy.deepcopy(M);mutate(m)
        with self.assertRaises(ValueError):V.verify_plan(m)

    def test_whole_immutable_plan(self):
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        V.verify_plan(M)

    def test_prior_source_and_provenance_pins(self):
        for path,sha in M['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT/path).read_bytes()),sha,path)

    def test_no_source_or_private_abi_credit(self):
        for key,value in [('source_file','private.cpp'),('signature','private'),('calling_convention','__cdecl')]:
            self.reject(lambda m:m['functions'][0]['accepted_function'].update({key:value}))

    def test_no_exact_credit(self):
        self.reject(lambda m:m['functions'][0]['accepted_function'].update(match_percent='100.00'))

    def test_original_unknown_record_retained(self):
        self.reject(lambda m:m['functions'][0]['original_origin'].update(origin='library'))

    def test_original_extent_retained(self):
        self.reject(lambda m:m['functions'][0]['original_function'].update(size='1'))

    def test_eight_lifetime_alternatives_retained(self):
        self.reject(lambda m:m['retained_unknown'].pop())

    def test_fourteen_interior_compiler_rows_retained(self):
        self.reject(lambda m:m['interiors'][0]['origin'].update(origin='library'))

    def test_all_real_fields_retained(self):
        self.reject(lambda m:m['sections'][0]['fields'].pop())

    def test_all_source_definitions_retained(self):
        self.reject(lambda m:m['sections'][0]['source']['definitions'].pop())

    def test_all_real_bindings_retained(self):
        self.reject(lambda m:m['sections'][0]['bindings'].pop())

    def test_data_carrier_cannot_be_truncated(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['kind']=='data').update(size=1))

    def test_bss_carrier_cannot_be_guessed(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['kind']=='bss').update(size=1))

    def test_all_prior_complete_anchors_retained(self):
        self.reject(lambda m:m['anchors'].pop())

    def test_foreign_uuid_owner_cannot_be_substituted(self):
        self.reject(lambda m:m['foreign_guids'][0]['record'].update(member_offset=333374))

    def test_uuid_section_cannot_be_guessed(self):
        self.reject(lambda m:m['foreign_guids'][0]['record'].update(section=1))

    def test_actual_stack_alias_definitions_required(self):
        self.reject(lambda m:m['alias_anchors'][0]['record']['alias_definitions'].pop())

    def test_primary_stack_source_extent_required(self):
        self.reject(lambda m:m['alias_anchors'][0]['record'].update(source_size=60))

    def test_stack_alias_source_is_not_inferred_from_native_call(self):
        self.reject(lambda m:m['alias_anchors'][0]['record']['alias_definitions'][0].update(offset=1))

    def test_all_original_import_identities_required(self):
        self.reject(lambda m:m['imports'][0].update(name='OtherApi'))

    def test_resource_policy_cannot_be_truncated(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['base']=='0x0060EA96').update(size=141))

    def test_name_does_not_give_lifetime_credit(self):
        self.reject(lambda m:m['functions'][0].update(symbol='??1PrivateOwner@@QAE@XZ'))

    def test_folded_scalar_sources_retained_separately(self):
        self.assertEqual(sum(r['base']=='0x006049A0' for r in M['sections']),2)
        self.reject(lambda m:m['sections'].remove(next(r for r in m['sections'] if r['base']=='0x006049A0')))

    def test_noninventory_bodies_do_not_create_credit(self):
        expected={'0x00608DC8','0x00608F63','0x00608E4A','0x00608E94','0x00608EA3','0x00608EFE','0x00608F0D'}
        self.assertEqual({r['base'] for r in M['sections'] if r['kind']=='code' and r['function'] is None},expected)
        self.assertTrue(all(r['address'] not in expected for r in M['functions']))

    def test_all_cold_emitted_sections_required(self):
        self.reject(lambda m:m['public_control']['emission'].pop())

    def test_original_public_headers_required(self):
        self.reject(lambda m:m['public_control']['headers'].pop(next(iter(m['public_control']['headers']))))

    def test_public_logfont_layout_is_not_a_private_owner(self):
        self.reject(lambda m:m['public_control']['layout']['values'].__setitem__(2,52))

    def test_absolute_crt_definition_is_not_pe_storage(self):
        self.reject(lambda m:m['absolute']['__except_list']['definition'].update(section=1))

    def test_unowned_field_destination_is_rejected(self):
        f=dict(offset=1,type='REL32',symbol='callee',addend=0,symbol_section=0,symbol_storage=2)
        b=dict(f,source_base='0x00002000',target_address='0x00002000')
        with self.assertRaises(ValueError):V.bind_fields(b'\xe8\0\0\0\0',[f],[b],{},1,0x1000)

    def test_genuine_binding_requires_independent_symbol_owner(self):
        f=dict(offset=1,type='REL32',symbol='callee',addend=0,symbol_section=0,symbol_storage=2)
        b=dict(f,source_base='0x00002000',target_address='0x00002000')
        linked,calls,data=V.bind_fields(b'\xe8\0\0\0\0',[f],[b],{'callee':0x2000},1,0x1000)
        self.assertEqual(calls,{0x1001:0x2000});self.assertFalse(data)
        self.assertEqual(int.from_bytes(linked[1:],'little'),0xffb)


if __name__=='__main__':unittest.main()
