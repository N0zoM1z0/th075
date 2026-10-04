"""Guard full comparisons, mapped BSS bounds and independent opaque callees."""
import importlib.util
from pathlib import Path
import struct
import unittest

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('math_table_tests',ROOT/'scripts/verify-math-table-policy-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)

class MathTablePolicyOrigins(unittest.TestCase):
    def setUp(self):self.m=V.manifest()
    def reject(self,mutation):
        mutation(self.m)
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_complete_plan(self):V.verify_plan(self.m)
    def test_complete_build(self):self.reject(lambda m:m['functions'][0].update(size=81))
    def test_complete_lookup(self):self.reject(lambda m:m['functions'][1].update(size=42))
    def test_complete_phase_lookup(self):self.reject(lambda m:m['functions'][2].update(size=48))
    def test_complete_ratio(self):self.reject(lambda m:m['functions'][3].update(size=72))
    def test_counter_never_shrinks_to_model(self):self.reject(lambda m:m['functions'][4].update(size=67))
    def test_no_source_presence(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(source_file='src/False.cpp'))
    def test_no_private_abi(self):self.reject(lambda m:m['functions'][1]['accepted_function'].update(calling_convention='cdecl'))
    def test_no_original_counter_layout(self):self.reject(lambda m:m['functions'][4]['accepted_function'].update(signature='OriginalCounter::increment()'))
    def test_no_exact_credit(self):self.reject(lambda m:m['functions'][2]['accepted_function'].update(match_percent='100.00'))
    def test_no_mapping_symbol(self):self.reject(lambda m:m['functions'][3].update(symbol='FalseExact'))
    def test_complete_authored_record(self):self.reject(lambda m:m['functions'][4]['accepted_authored_record'].update(size='67'))
    def test_original_extent_unchanged(self):self.reject(lambda m:m['functions'][3]['accepted_function'].update(size='67'))
    def test_all_ordinary_emission(self):self.reject(lambda m:m['emission'].pop())
    def test_all_actual_headers(self):self.reject(lambda m:m['headers'].pop(next(iter(m['headers']))))
    def test_entire_source_layout(self):self.reject(lambda m:m['layout'].update(size=12))
    def test_all_real_fields(self):self.reject(lambda m:m['controls'][2]['bindings'].pop())
    def test_no_field_mask(self):self.reject(lambda m:m['controls'][0]['bindings'][0].update(type='MASKED'))
    def test_actual_constant(self):self.reject(lambda m:m['constants'][1].update(value=3.14))
    def test_full_constants(self):self.reject(lambda m:m['controls'][4].update(size=4))
    def test_real_table_used_range(self):self.reject(lambda m:m['table_span'].update(size=14396))
    def test_no_full_original_table_allocation_claim(self):self.reject(lambda m:m['table_span'].update(scope='complete-original-array'))
    def test_all_table_elements(self):self.reject(lambda m:m['table_span'].update(element_count=3599))
    def test_actual_table_width(self):self.reject(lambda m:m['table_span'].update(element_width=8))
    def test_full_character_parent(self):self.reject(lambda m:m['anchors'][1].update(size=43844))
    def test_full_startup_parent(self):self.reject(lambda m:m['anchors'][0].update(size=2986))
    def test_full_counter_parent(self):self.reject(lambda m:m['anchors'][2].update(size=214))
    def test_all_snapshots(self):self.reject(lambda m:m['snapshots'].pop())
    def test_abs_remains_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x00641DAA')['origin'].update(origin='library'))
    def test_no_borrowed_empty_allocator_origin(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x0041E330')['origin'].update(origin='library'))
    def test_ratio_never_gets_false_positive(self):self.reject(lambda m:m['controls'][3].update(comparison='positive'))
    def test_ratio_instruction_order_difference_is_frozen(self):self.reject(lambda m:m['controls'][3]['differences'].clear())
    def test_full_small_owner_control(self):self.reject(lambda m:m['policies'][0].update(size=79))
    def test_no_target_positive_for_small_owner(self):self.reject(lambda m:m['policies'][0].update(target_positive=True))
    def test_actual_loop_bound(self):self.reject(lambda m:next(w for w in m['functions'][0]['witnesses'] if w['site']=='0x0041CAF6').update(operands='dword ptr [ebp - 4], 0x708'))
    def test_actual_phase_offset(self):self.reject(lambda m:next(w for w in m['functions'][2]['witnesses'] if w['site']=='0x0041CB7C').update(mnemonic='fadd'))
    def test_original_zero_divisor_guard(self):self.reject(lambda m:next(w for w in m['functions'][3]['witnesses'] if w['site']=='0x0041CBCD').update(mnemonic='jnp'))
    def test_actual_signed_counter_index(self):self.reject(lambda m:next(w for w in m['functions'][4]['witnesses'] if w['site']=='0x00454D07').update(mnemonic='movzx'))
    def test_actual_signed_counter_bank(self):self.reject(lambda m:next(w for w in m['functions'][4]['witnesses'] if w['site']=='0x00454D0E').update(mnemonic='movzx'))
    def test_actual_bank_stride(self):self.reject(lambda m:next(w for w in m['functions'][4]['witnesses'] if w['site']=='0x00454D15').update(operands='edx, edx, 6'))
    def test_actual_counter_word_width(self):self.reject(lambda m:next(w for w in m['functions'][4]['witnesses'] if w['site']=='0x00454D41').update(operands='dword ptr [edx + ecx*4 + 0x394], eax'))
    def test_ratio_retains_all_three_calls(self):self.reject(lambda m:next(w for w in m['functions'][3]['witnesses'] if w['site']=='0x0041CBEA').update(operands='0x41cb70'))
    def test_full_negative_comparison(self):
        r=self.m['controls'][3];source=bytearray(73);actual=bytearray(73)
        for d in V.RATIO_DIFFERENCES:source[d['offset']]=d['source'];actual[d['offset']]=d['target']
        r['source_sha256']=V.digest(source);r['body_sha256']=V.digest(actual)
        V.verify_control(r,source,source,actual)
        with self.assertRaises(ValueError):V.verify_control(r,source[:-1],source[:-1],actual[:-1])
        changed=bytearray(source);changed[5]=1
        with self.assertRaises(ValueError):V.verify_control(r,source,changed,actual)
        with self.assertRaises(ValueError):V.verify_control(r,source,actual,actual)
    def image(self,flags=0xC0000040):
        target=bytearray(512);struct.pack_into('<I',target,0x3C,128);struct.pack_into('<H',target,134,1);struct.pack_into('<H',target,148,224)
        struct.pack_into('<I',target,180,0x400000);struct.pack_into('<I',target,208,0x4000)
        struct.pack_into('<8sIIIIIIHHI',target,376,b'.data',0x2000,0x1000,0x200,0,0,0,0,0,flags)
        return target
    def test_mapped_zero_fill_range_is_valid(self):V.verify_table_span(self.image(),dict(address='0x00401800',size=0x1000))
    def test_no_out_of_mapped_range(self):
        with self.assertRaises(ValueError):V.verify_table_span(self.image(),dict(address='0x00401800',size=0x2000))
    def test_table_must_be_writable(self):
        with self.assertRaises(ValueError):V.verify_table_span(self.image(0x40000040),dict(address='0x00401800',size=0x1000))
    def test_table_must_not_be_code(self):
        with self.assertRaises(ValueError):V.verify_table_span(self.image(0xE0000040),dict(address='0x00401800',size=0x1000))

if __name__=='__main__':unittest.main()
