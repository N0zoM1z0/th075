"""Guard complete SDK image-entry ownership, backward extents and real peer fields."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
SPEC=importlib.util.spec_from_file_location('image_entry_tests',ROOT/'scripts/verify-sdk-image-entry-origins.py')
V=importlib.util.module_from_spec(SPEC);SPEC.loader.exec_module(V)
M=json.loads((ROOT/V.EVIDENCE).read_text())


class ImageEntryProvenanceTests(unittest.TestCase):
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

    def test_four_lifetime_alternatives_retained(self):
        self.reject(lambda m:m['retained_unknown'].pop())

    def test_two_interior_compiler_rows_retained(self):
        self.reject(lambda m:m['interiors'][0]['origin'].update(origin='library'))

    def test_all_real_fields_retained(self):
        self.reject(lambda m:m['sections'][0]['fields'].pop())

    def test_all_source_definitions_retained(self):
        self.reject(lambda m:m['sections'][0]['source']['definitions'].pop())

    def test_all_real_bindings_retained(self):
        self.reject(lambda m:m['sections'][0]['bindings'].pop())

    def test_data_carrier_cannot_be_truncated(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['kind']=='data').update(size=1))

    def test_full_eh_data_carrier_required(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['kind']=='data').update(size=1))

    def test_all_prior_complete_anchors_retained(self):
        self.reject(lambda m:m['anchors'].pop())

    def test_full_backward_surface_extent_required(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['base']=='0x00607005').update(size=132))

    def test_full_backward_volume_extent_required(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['base']=='0x00607263').update(size=135))

    def test_internal_returns_do_not_allow_cropping_source_tail(self):
        self.assertEqual(next(r for r in M['sections'] if r['base']=='0x00607005')['flow']['returns'],[dict(offset=130,cleanup=36)])
        self.assertEqual(next(r for r in M['sections'] if r['base']=='0x00607263')['flow']['returns'],[dict(offset=133,cleanup=36)])

    def test_all_backward_instructions_must_be_reachable(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['base']=='0x00607005')['flow'].update(reachable_instruction_count=1))

    def test_private_static_source_identities_retained(self):
        self.reject(lambda m:next(d for d in next(r for r in m['sections'] if r['base']=='0x00607F32')['source']['definitions']
                                 if d['type']==32 and not d['offset']).update(storage=2))

    def test_all_original_import_identities_required(self):
        self.reject(lambda m:m['imports'][0].update(name='OtherApi'))

    def test_save_policy_cannot_be_truncated(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['base']=='0x006054EF').update(size=175))

    def test_name_does_not_give_lifetime_credit(self):
        self.reject(lambda m:m['functions'][0].update(symbol='??1PrivateOwner@@QAE@XZ'))

    def test_all_complete_peers_required(self):
        self.reject(lambda m:m['rejected_peers'].pop())

    def test_peer_source_owner_cannot_be_substituted(self):
        self.reject(lambda m:m['rejected_peers'][0]['source_owner'].update(section=1))

    def test_real_surface_volume_callee_distinction_required(self):
        self.reject(lambda m:m['rejected_peers'][0]['conflicts'][0].update(independent='0x00607263'))

    def test_peer_comparison_cannot_be_truncated(self):
        self.reject(lambda m:m['rejected_peers'][0].update(size=80))

    def test_peer_target_image_cannot_be_substituted(self):
        self.reject(lambda m:m['rejected_peers'][0].update(native_sha256='0'*64))

    def test_all_cold_emitted_sections_required(self):
        self.reject(lambda m:m['public_control']['emission'].pop())

    def test_original_public_headers_required(self):
        self.reject(lambda m:m['public_control']['headers'].pop(next(iter(m['public_control']['headers']))))

    def test_public_image_layout_is_not_a_private_owner(self):
        self.reject(lambda m:m['public_control']['layout']['values'].__setitem__(0,32))

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
