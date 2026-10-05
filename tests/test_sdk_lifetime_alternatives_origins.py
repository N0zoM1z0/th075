"""Guard full PNG destruction provenance and retained SDK lifetime ambiguity."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('lifetime_tests', ROOT / 'scripts/verify-sdk-lifetime-alternatives-origins.py')
V = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(V)
M = json.loads((ROOT / V.EVIDENCE).read_text())


class LifetimeAlternativesTests(unittest.TestCase):
    def reject(self, mutate):
        m = copy.deepcopy(M); mutate(m)
        with self.assertRaises(ValueError): V.verify_plan(m)

    def test_whole_immutable_plan(self):
        self.assertEqual(V.digest((ROOT / V.EVIDENCE).read_bytes()), V.MANIFEST_SHA256)
        V.verify_plan(M)

    def test_prior_source_pins(self):
        for path, sha in M['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT / path).read_bytes()), sha, path)

    def test_all_six_root_decisions_retained(self):
        self.reject(lambda m: m['reviewed_cohort'].pop())

    def test_constructor_does_not_gain_library_credit(self):
        self.reject(lambda m: m['reviewed_cohort'][0].update(decision='library'))

    def test_all_unknown_alternatives_retained(self):
        self.reject(lambda m: m['retained_unknown'].pop())

    def test_unknown_destructor_does_not_gain_compiler_credit(self):
        self.reject(lambda m: m['retained_unknown'][0]['origin'].update(origin='compiler'))

    def test_no_source_or_private_abi_credit(self):
        for key in ['source_file', 'signature', 'calling_convention']:
            self.reject(lambda m: m['functions'][0]['accepted_function'].update({key: 'private'}))

    def test_no_exact_credit(self):
        self.reject(lambda m: m['functions'][0]['accepted_function'].update(match_percent='100.00'))

    def test_original_unknown_record_retained(self):
        self.reject(lambda m: m['functions'][0]['original_origin'].update(origin='library'))

    def test_png_complete_extent_retained(self):
        self.reject(lambda m: m['functions'][0].update(size=37))

    def test_png_clear_is_not_a_declared_private_layout(self):
        self.assertEqual(M['public_control']['layout']['values'], [4, 8, 12, 12, 4, 4, 8, 8])
        self.reject(lambda m: m['public_control']['layout']['values'].__setitem__(0, 64))

    def test_all_source_fields_retained(self):
        self.reject(lambda m: m['sections'][0]['fields'].pop())

    def test_all_source_bindings_retained(self):
        self.reject(lambda m: m['sections'][0]['bindings'].pop())

    def test_entire_base_destructor_retained(self):
        self.reject(lambda m: next(r for r in m['sections'] if r['base'] == '0x0061535A').update(size=18))

    def test_whole_eh_code_carrier_retained(self):
        self.reject(lambda m: next(r for r in m['sections'] if r['base'] == '0x00656ABA').update(size=8))

    def test_whole_eh_data_carrier_retained(self):
        self.reject(lambda m: next(r for r in m['sections'] if r['base'] == '0x0066A6D0').update(size=4))

    def test_entire_vtable_retained(self):
        self.reject(lambda m: next(r for r in m['sections'] if r['base'] == '0x0065DA68')['fields'].pop())

    def test_accepted_owner_vtable_retained(self):
        self.reject(lambda m: m['data_anchors'][0]['record'].update(size=4))

    def test_actual_weak_fallback_aux_required(self):
        self.reject(lambda m: m['weak_references'][0].update(search_characteristics=0))

    def test_fallback_source_section_cannot_be_guessed(self):
        self.reject(lambda m: m['weak_references'][0]['fallback_definition'].update(section=1))

    def test_noninventory_yuv_wrapper_gets_no_function_credit(self):
        r = next(r for r in M['sections'] if r['base'] == '0x0061AC28')
        self.assertIsNone(r['function']); self.assertIsNone(r['origin'])
        self.reject(lambda m: next(r for r in m['sections'] if r['base'] == '0x0061AC28').update(function={}))

    def test_all_complete_anchors_required(self):
        self.reject(lambda m: m['anchors'].pop())

    def test_all_complete_cfgs_required(self):
        self.reject(lambda m: m['sections'][0]['flow'].update(reachable_instruction_count=1))

    def test_all_ordinary_cold_emissions_required(self):
        self.reject(lambda m: m['public_control']['emission'].pop())

    def test_original_public_headers_required(self):
        self.reject(lambda m: m['public_control']['headers'].pop(next(iter(m['public_control']['headers']))))

    def test_complete_explicit_implicit_pairs_required(self):
        self.assertEqual(M['alternative_pairs'], V.PAIRS)
        self.reject(lambda m: m['alternative_pairs'].pop())

    def test_vtable_field_identity_must_still_differ(self):
        self.reject(lambda m: m['alternative_pairs'][0]['field_symbols'].__setitem__(1, m['alternative_pairs'][0]['field_symbols'][0]))

    def test_generic_alternative_cannot_be_mapped_to_target(self):
        self.reject(lambda m: m['alternative_pairs'][0].update(target_address='0x00609F58'))

    def test_absolute_crt_definition_required(self):
        self.reject(lambda m: m['absolute']['__except_list']['definition'].update(section=1))

    def test_unowned_field_destination_is_rejected(self):
        f = dict(offset=1, type='REL32', symbol='callee', addend=0, symbol_section=0, symbol_storage=2)
        b = dict(f, source_base='0x00002000', target_address='0x00002000')
        with self.assertRaises(ValueError): V.bind_fields(b'\xe8\0\0\0\0', [f], [b], {}, 1, 0x1000)


if __name__ == '__main__': unittest.main()
