"""Reject incomplete family provenance and erased destructor alternatives."""
import importlib.util
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('derived_exception', ROOT / 'scripts/verify-derived-exception-origins.py')
REVIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class DerivedExceptionOriginTests(unittest.TestCase):
    def setUp(self):
        self.m = REVIEW.manifest()
        self.graph = {r['address']:r for r in self.m['functions']+self.m['auxiliary_bodies']+self.m['anchors']}

    def reject(self, message):
        with self.assertRaisesRegex(ValueError, message):
            REVIEW.verify_plan(self.m)

    def reject_protocol(self, message):
        with self.assertRaisesRegex(ValueError, message):
            REVIEW.check_derived_protocol(self.m, self.graph)

    def test_complete_plan_passes(self):
        REVIEW.verify_plan(self.m)

    def test_destructor_cannot_end_before_tail_jump(self):
        self.graph['0x00640DAF']['size'] = 6
        self.reject('complete own AUX')

    def test_non_inventory_constructor_has_no_candidate_credit(self):
        self.graph['0x00640D7F']['decision'] = 'library'
        self.reject('invented inventory credit')

    def test_non_inventory_constructor_requires_full_return(self):
        self.graph['0x00640D7F']['code_size'] = 21
        self.reject('invented inventory credit')

    def test_compiler_controls_keep_existing_r038_origin(self):
        next(r for r in self.m['anchors'] if r['address']=='0x00640E2D')['origin'] = 'library'
        self.reject('independent full anchors')

    def test_independent_incoming_callback_cannot_be_swapped(self):
        callback = self.graph['0x00640E2D']
        callback['relocation_bindings'][0]['target_address'] = '0x00640D74'
        self.reject_protocol('incoming destructor context')

    def test_callback_requires_the_actual_source_destructor_symbol(self):
        self.graph['0x00640E2D']['relocation_bindings'][0]['symbol'] = '??1bad_typeid@@UAE@XZ'
        self.reject_protocol('incoming destructor context')

    def test_non_rtti_destruction_stage_is_bad_typeid(self):
        self.graph['0x00640DAF']['instruction_witnesses'][0]['operands'] = 'dword ptr [ecx], 0x660ed0'
        self.reject_protocol('destruction-stage vtable')

    def test_tail_is_not_a_fake_return(self):
        self.graph['0x00640D74']['body_facts']['returns'] = [{'cleanup':0}]
        self.reject_protocol('vtable-store/base-tail')

    def test_tail_cannot_gain_an_intermediate_bad_typeid_call(self):
        self.graph['0x00640DAF']['instruction_witnesses'][1]['operands'] = '0x640d74'
        self.reject_protocol('destruction-stage vtable')

    def test_destructor_keeps_both_typed_fields(self):
        self.graph['0x00640DAF']['relocation_bindings'].pop()
        self.reject_protocol('typed stage/base fields')

    def test_constructed_vtable_keeps_locator_prefix(self):
        row = next(r for r in self.m['state_data'] if r['symbol']=='??_7__non_rtti_object@@6B@')
        row['size'] = 8
        self.reject_protocol('whole prefixed constructed vtable')

    def test_address_point_cannot_be_rebased_to_section_start(self):
        row = next(r for r in self.m['state_data'] if r['symbol']=='??_7bad_cast@@6B@')
        row['source_anchor']['offset'] = 0
        self.reject_protocol('whole prefixed constructed vtable')

    def test_non_rtti_vtable_keeps_its_own_scalar_callback(self):
        row = next(r for r in self.m['state_data'] if r['symbol']=='??_7__non_rtti_object@@6B@')
        row['relocations'][1]['target_address'] = '0x00640E11'
        self.reject_protocol('paired actual weak/compiler callback')

    def test_weak_callback_requires_actual_fallback_symbol(self):
        row = next(r for r in self.m['state_data'] if r['symbol']=='??_7bad_typeid@@6B@')
        row['relocations'][1]['source_weak_reference']['fallback_symbol'] = '??_G__non_rtti_object@@UAEPAXI@Z'
        self.reject_protocol('paired actual weak/compiler callback')

    def test_weak_search_two_is_not_forced_alias_three(self):
        self.m['source_weak_references'][0]['search_characteristics'] = 3
        self.reject('actual weak fallback')

    def test_message_constructor_keeps_actual_base_call(self):
        self.graph['0x00640D7F']['relocation_bindings'][0]['target_address'] = '0x00640C5D'
        self.reject_protocol('constructor/base ABI')

    def test_copy_constructor_is_not_message_constructor(self):
        self.graph['0x00640D97']['relocation_bindings'][0]['target_address'] = '0x00640D43'
        self.reject_protocol('constructor/base ABI')

    def test_constructor_cannot_use_destruction_stage_vtable(self):
        self.graph['0x00640D7F']['relocation_bindings'][1]['target_address'] = '0x00660EC4'
        self.reject_protocol('constructor/base ABI')

    def test_member_constructor_retains_four_callee_bytes(self):
        self.graph['0x00640D97']['body_facts']['returns'][0]['cleanup'] = 0
        self.reject_protocol('constructor/base ABI')

    def test_two_base_array_keeps_ninth_byte(self):
        row = next(r for r in self.m['state_data'] if r['symbol']=='??_R2bad_cast@@8')
        row['size'] = 8
        self.reject_protocol('full RTTI base array')

    def test_three_base_array_keeps_thirteenth_byte(self):
        row = next(r for r in self.m['state_data'] if r['symbol']=='??_R2__non_rtti_object@@8')
        row['size'] = 12
        self.reject_protocol('full RTTI base array')

    def test_non_rtti_base_array_keeps_bad_typeid_middle_base(self):
        row = next(r for r in self.m['state_data'] if r['symbol']=='??_R2__non_rtti_object@@8')
        row['relocations'][1]['symbol'] = '??_R1A@?0A@A@bad_cast@@8'
        self.reject_protocol('full RTTI base array')

    def test_equal_source_owners_keep_both_alternatives(self):
        self.m['source_alternatives'].pop()
        self.reject_protocol('complete equal-body source alternatives')

    def test_non_rtti_source_alternative_matches_both_full_targets(self):
        self.m['source_alternatives'][2]['full_linked_results'][1]['complete_match'] = False
        self.reject_protocol('complete equal-body source alternatives')

    def test_bad_cast_is_not_a_second_equal_body_alternative(self):
        self.m['source_alternatives'][0]['full_linked_results'][1]['complete_match'] = True
        self.reject_protocol('complete equal-body source alternatives')

    def test_retained_full_r142_r038_chain_cannot_be_omitted(self):
        self.m['retained_controls'].clear()
        self.reject('retained independent R142')

    def test_complete_probe_scalar_section_cannot_be_truncated(self):
        self.m['probe_generated_code'][0]['size'] = 28
        self.reject('complete probe_generated_code')

    def test_probe_rtti_base_array_requires_complete_defining_section(self):
        row = next(r for r in self.m['probe_generated_data'] if r['symbol']=='??_R2IndependentMissingRtti@@8')
        row['source_section']['size'] = 12
        self.reject('complete probe_generated_data')

    def test_real_sdk_complete_interface_not_invented_layout(self):
        self.m['sdk_layout']['objects'][0]['values'][4] = 8
        self.reject('actual SDK')

    def test_runtime_linker_unknowns_remain_explicit(self):
        self.m['derived_protocol']['runtime_unknowns'] = 'original link search fully known'
        self.reject('private ABI')


if __name__ == '__main__':
    unittest.main()
