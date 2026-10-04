"""Guard native load widths, whole negative extents and source-owner ambiguity."""
import importlib.util
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('font_byte_tests',ROOT/'scripts/verify-font-byte-policy-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)

class FontBytePolicyOrigins(unittest.TestCase):
    def setUp(self):self.m=V.manifest()
    def reject(self,mutation):
        mutation(self.m)
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_complete_plan(self):V.verify_plan(self.m)
    def test_decoder_never_truncated_to_source(self):self.reject(lambda m:m['functions'][0].update(size=74))
    def test_complete_resource_initializer(self):self.reject(lambda m:m['functions'][1].update(size=63))
    def test_no_source_presence(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(source_file='src/False.cpp'))
    def test_no_private_abi(self):self.reject(lambda m:m['functions'][1]['accepted_function'].update(calling_convention='cdecl'))
    def test_no_complete_original_resource_type(self):self.reject(lambda m:m['functions'][1]['accepted_function'].update(signature='OriginalOwner::OriginalOwner()'))
    def test_no_exact_credit(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(match_percent='100.00'))
    def test_no_source_symbol_credit(self):self.reject(lambda m:m['functions'][0].update(symbol='FalseMatch'))
    def test_complete_authored_body_record(self):self.reject(lambda m:m['functions'][0]['accepted_authored_record'].update(size='74'))
    def test_no_original_extent_change(self):self.reject(lambda m:m['functions'][1]['accepted_function'].update(span_end='0x0041BFCE'))
    def test_full_byte_source(self):self.reject(lambda m:m['controls'][0].update(size=85))
    def test_full_original_byte_target(self):self.reject(lambda m:m['controls'][0].update(target_size=74))
    def test_byte_width_negative_never_positive(self):self.reject(lambda m:m['controls'][0].update(comparison='positive'))
    def test_equal_ctor_length_not_a_match(self):self.reject(lambda m:m['controls'][1].update(comparison='positive'))
    def test_original_storage_offset_difference_retained(self):self.reject(lambda m:m['controls'][1]['differences'].clear())
    def test_storage_offset_not_padded(self):self.reject(lambda m:m['controls'][1]['differences'][0].update(source=20))
    def test_all_decoder_differences_visible(self):self.reject(lambda m:m['controls'][0]['differences'].pop())
    def test_real_call_not_masked(self):self.reject(lambda m:m['controls'][0]['bindings'][0].update(type='MASKED'))
    def test_real_classifier_call_not_replaced(self):self.reject(lambda m:m['controls'][0]['bindings'][0].update(target_address='0x0041CA80'))
    def test_all_ordinary_sections(self):self.reject(lambda m:m['emission'].pop())
    def test_actual_include_owners(self):self.reject(lambda m:m['headers'].pop(next(iter(m['headers']))))
    def test_whole_source_layout(self):self.reject(lambda m:m['layout'].update(size=20))
    def test_source_storage_is_small_owner(self):self.reject(lambda m:m['layout_values'].__setitem__(2,56))
    def test_full_rasterizer_parent(self):self.reject(lambda m:m['anchors'][0].update(size=1765))
    def test_full_texture_parent(self):self.reject(lambda m:m['anchors'][1].update(size=397))
    def test_full_music_room_parent(self):self.reject(lambda m:m['anchors'][2].update(size=554))
    def test_full_accepted_release_parent(self):self.reject(lambda m:m['anchors'][3].update(size=128))
    def test_all_snapshots(self):self.reject(lambda m:m['snapshots'].pop())
    def test_original_frames_preserved(self):self.reject(lambda m:m['frames'].pop())
    def test_original_actual_import_preserved(self):self.reject(lambda m:m['import_slots'][0].update(name='FalseObject'))
    def test_classifier_remains_unknown(self):self.reject(lambda m:m['pending']['origin'].update(origin='authored'))
    def test_classifier_has_no_accepted_transition(self):self.reject(lambda m:m['pending'].update(accepted_origin={}))
    def test_classifier_full_extent(self):self.reject(lambda m:m['pending'].update(size=76))
    def test_full_generic_member_alternative(self):self.reject(lambda m:m['controls'][3].update(size=76))
    def test_keep_other_opaque_integer_helper(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x00641DAA')['origin'].update(origin='library'))
    def test_full_sdk_macro(self):self.reject(lambda m:m['policies'][0].update(size=77))
    def test_no_fictitious_sdk_table_binding(self):self.reject(lambda m:m['policies'][0].update(bindings=[]))
    def test_sdk_real_table_field_retained(self):self.reject(lambda m:m['policies'][0]['section']['fields'][0].update(addend=0))
    def test_implicit_default_has_no_target_credit(self):self.reject(lambda m:m['policies'][4].update(target_positive=True))
    def test_actual_first_dword_read(self):self.reject(lambda m:next(w for w in m['functions'][0]['witnesses'] if w['site']=='0x0041C9EF').update(operands='ecx, byte ptr [eax]'))
    def test_actual_second_dword_read(self):self.reject(lambda m:next(w for w in m['functions'][0]['witnesses'] if w['site']=='0x0041C9FD').update(operands='eax, byte ptr [edx + 1]'))
    def test_actual_signed_single_byte_fallback(self):self.reject(lambda m:next(w for w in m['functions'][0]['witnesses'] if w['site']=='0x0041CA15').update(mnemonic='movzx'))
    def test_actual_selected_window(self):self.reject(lambda m:next(w for w in m['functions'][1]['witnesses'] if w['site']=='0x0041BF9D').update(operands='dword ptr [eax], 0'))
    def test_actual_native_storage_slot(self):self.reject(lambda m:next(w for w in m['functions'][1]['witnesses'] if w['site']=='0x0041BFC0').update(operands='dword ptr [edx + 0x10], 0'))
    def test_whole_equal_length_negative(self):
        r=self.m['controls'][1];raw=bytearray(64);actual=bytearray(64);raw[50]=16;actual[50]=20
        r['source_sha256']=V.digest(raw);r['body_sha256']=V.digest(actual);V.verify_control(r,raw,raw,actual)
        with self.assertRaises(ValueError):V.verify_control(r,raw[:50],raw[:50],actual[:50])
        with self.assertRaises(ValueError):V.verify_control(r,raw,actual,actual)
    def test_distinct_full_lengths_cannot_be_hidden(self):
        r=self.m['controls'][0];raw=bytes(74);actual=bytes(85);r['source_sha256']=V.digest(raw);r['body_sha256']=V.digest(actual);r['differences']=[]
        V.verify_control(r,raw,raw,actual)
        with self.assertRaises(ValueError):V.verify_control(r,raw,raw,actual[:74])
        with self.assertRaises(ValueError):V.verify_control(r,raw+bytes(11),raw+bytes(11),actual)

if __name__=='__main__':unittest.main()
