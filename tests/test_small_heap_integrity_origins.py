"""Guard complete heap-check evidence and independent full relocation linking."""
import importlib.util
from pathlib import Path
import struct
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('small_heap_review', ROOT/'scripts/verify-small-heap-integrity-origins.py')
REVIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class SmallHeapIntegrityOriginTests(unittest.TestCase):
    def setUp(self):
        self.m = REVIEW.manifest()
        self.row = self.m['functions'][0]

    def reject(self):
        with self.assertRaises(ValueError):
            REVIEW.verify_plan(self.m)

    def test_complete_plan(self):
        REVIEW.verify_plan(self.m)

    def test_final_error_tail_cannot_be_dropped(self):
        self.row['size'] = 789
        self.reject()

    def test_first_return_is_not_whole_extent(self):
        self.row['size'] = 42
        self.reject()

    def test_complete_aux_cannot_be_a_masked_partition(self):
        self.row['code_regions'] = [dict(offset=0,size=761)]
        self.reject()

    def test_shared_epilogue_cannot_be_dropped(self):
        self.row['body_facts']['returns'].pop()
        self.reject()

    def test_last_error_branch_is_required(self):
        self.row['branches'].pop()
        self.reject()

    def test_every_actual_api_call_is_required(self):
        self.row['indirect_calls'].pop()
        self.reject()

    def test_api_cannot_be_guessed_from_name(self):
        self.row['relocation_bindings'][2]['target_address'] = '0x00657158'
        self.reject()

    def test_common_count_and_pointer_cannot_be_swapped(self):
        self.m['common_globals'][0]['target_address'] = '0x0068FA64'
        self.reject()

    def test_common_cannot_be_initialized_definition(self):
        self.m['common_globals'][0]['source_definition']['section'] = 1
        self.reject()

    def test_common_complete_storage_is_four_bytes(self):
        self.m['common_globals'][0]['size'] = 8
        self.reject()

    def test_common_cannot_be_beyond_loader_virtual_range(self):
        self.m['common_globals'][0]['zero_fill_region']['virtual_size'] = 24576
        self.reject()

    def test_competing_strong_definition_cannot_be_ignored(self):
        self.m['common_alternatives'][0]['definitions'].append(self.m['common_alternatives'][0]['definitions'][0])
        self.reject()

    def test_retained_heap_context_is_required(self):
        self.m['retained_controls'].clear()
        self.reject()

    def test_vendor_source_cannot_change_to_other_translation_unit(self):
        self.m['vendor_reproduction']['source'] = '.tools/msvc710/Vc7/crt/src/heapchk.c'
        self.reject()

    def test_vendor_compile_profile_cannot_change(self):
        self.m['vendor_reproduction']['profile'][0] = '/O2'
        self.reject()

    def test_cold_selected_function_requires_whole_aux(self):
        self.m['vendor_reproduction']['size'] = 761
        self.reject()

    def test_cold_source_header_hash_is_required(self):
        self.m['vendor_reproduction']['headers']['crt/src/winheap.h'] = '0'*64
        self.reject()

    def test_sdk_complete_region_size_is_required(self):
        self.m['sdk_layout']['objects'][0]['values'][8] = 324
        self.reject()

    def test_commit_rule_keeps_actual_signed_bit(self):
        self.m['heap_protocol']['commit_rule'] = 'MSB set selects a committed group'
        self.reject()

    def test_free_class_keeps_actual_upper_clamp(self):
        self.m['heap_protocol']['free_class_upper_clamp'] = 64
        self.reject()

    def test_return_minus_three_cannot_be_invented(self):
        self.m['heap_protocol']['source_returns'].append(dict(value=-3,meaning='Invented result'))
        self.reject()

    def test_no_original_private_game_layout_claim(self):
        self.m['heap_protocol']['unknowns'].clear()
        self.reject()

    def link_fixture(self, destination=0x68FA60):
        # Test actual linking independently of target-derived solved fields.
        body = bytes(8)
        field = dict(offset=2,type='DIR32',symbol='___sbh_cntHeaderList',addend=4,local_symbol_offset=None)
        row = dict(size=8,member_offset=827680,relocation_bindings=[dict(field,target_kind='state',target_address=f'0x{destination:08X}')])
        return body,[field],row,{(827680,'___sbh_cntHeaderList'):0x68FA60}

    def test_complete_link_writes_independently_bound_common_and_addend(self):
        body,fields,row,state = self.link_fixture()
        linked = REVIEW.link_complete(body,fields,row,state,{},None)
        self.assertEqual(linked,b'\0\0'+struct.pack('<I',0x68FA64)+b'\0\0')
        self.assertNotEqual(linked[:-1]+b'\1',linked)

    def test_target_solved_address_cannot_override_independent_binding(self):
        body,fields,row,state = self.link_fixture(0x68FA64)
        with self.assertRaisesRegex(ValueError,'independently resolved COMMON'):
            REVIEW.link_complete(body,fields,row,state,{},None)

    def test_complete_link_rejects_field_outside_full_extent(self):
        body,fields,row,state = self.link_fixture()
        fields[0]['offset'] = 6
        row['relocation_bindings'][0]['offset'] = 6
        with self.assertRaisesRegex(ValueError,'range/type'):
            REVIEW.link_complete(body,fields,row,state,{},None)

    def test_complete_link_rejects_overlapping_fields(self):
        body,fields,row,state = self.link_fixture()
        fields.append(dict(fields[0]));row['relocation_bindings'].append(dict(row['relocation_bindings'][0]))
        with self.assertRaisesRegex(ValueError,'overlaps'):
            REVIEW.link_complete(body,fields,row,state,{},None)

    def test_unbound_import_cannot_be_substituted_as_common(self):
        body,fields,row,state = self.link_fixture()
        row['relocation_bindings'][0]['target_kind'] = 'opaque'
        with self.assertRaisesRegex(ValueError,'independent binding'):
            REVIEW.link_complete(body,fields,row,state,{},None)

    def test_complete_link_rejects_prefix_extent(self):
        body,fields,row,state = self.link_fixture();row['size']=7
        with self.assertRaisesRegex(ValueError,'topology'):
            REVIEW.link_complete(body,fields,row,state,{},None)

    def test_canonical_acceptance_cannot_gain_source_or_exact_credit(self):
        fn = dict(size='793',span_end='0x0064B2DD',source_file='src/fake.cpp',match_percent='100.00',calling_convention='',signature='')
        with self.assertRaisesRegex(ValueError,'origin-only extent'):
            REVIEW.check_ledger(self.row,fn,{})


if __name__ == '__main__':
    unittest.main()
