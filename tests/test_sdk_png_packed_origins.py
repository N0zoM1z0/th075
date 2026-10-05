"""Guard whole PNG policies, source-static mutable data and MMX state evidence."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('png_packed_tests', ROOT / 'scripts/verify-sdk-png-packed-origins.py')
V = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(V)
M = json.loads((ROOT / V.EVIDENCE).read_text())


class PngPackedProvenanceTests(unittest.TestCase):
    def reject(self, mutate):
        m = copy.deepcopy(M); mutate(m)
        with self.assertRaises(ValueError): V.verify_plan(m)

    def test_whole_immutable_plan(self):
        self.assertEqual(V.digest((ROOT / V.EVIDENCE).read_bytes()), V.MANIFEST_SHA256)
        V.verify_plan(M)

    def test_prior_source_and_provenance_pins(self):
        for path, sha in M['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT / path).read_bytes()), sha, path)

    def test_no_source_or_private_abi_credit(self):
        for key in ['source_file', 'signature', 'calling_convention']:
            self.reject(lambda m: m['functions'][0]['accepted_function'].update({key: 'private'}))

    def test_no_exact_credit(self):
        self.reject(lambda m: m['functions'][0]['accepted_function'].update(match_percent='100.00'))

    def test_original_unknown_record_retained(self):
        self.reject(lambda m: m['functions'][0]['original_origin'].update(origin='library'))

    def test_original_extent_retained(self):
        self.reject(lambda m: m['functions'][0]['original_function'].update(size='1'))

    def test_quantization_policy_cannot_be_cropped(self):
        self.reject(lambda m: next(r for r in m['sections'] if r['base'] == '0x006235B9').update(size=1618))

    def test_all_real_fields_retained(self):
        self.reject(lambda m: m['sections'][0]['fields'].pop())

    def test_all_real_bindings_retained(self):
        self.reject(lambda m: m['sections'][0]['bindings'].pop())

    def test_all_source_definitions_retained(self):
        self.reject(lambda m: m['sections'][0]['source']['definitions'].pop())

    def test_complete_png_label_bank_retained(self):
        self.reject(lambda m: next(r for r in m['sections'] if r['base'] == '0x0065F240').update(size=12))

    def test_whole_writable_coefficient_bank_retained(self):
        self.reject(lambda m: next(r for r in m['sections'] if r['base'] == '0x0066E2A8').update(size=40))

    def test_coefficients_are_not_readonly(self):
        self.reject(lambda m: next(r for r in m['sections'] if r['base'] == '0x0066E2A8')['source'].update(flags=0x40000040))

    def test_bss_initial_image_is_complete(self):
        self.reject(lambda m: next(r for r in m['sections'] if r['base'] == '0x0068E280').update(size=4))

    def test_source_static_coefficient_owner_retained(self):
        self.reject(lambda m: next(d for d in next(r for r in m['sections'] if r['base'] == '0x0066E2A8')['source']['definitions']
                                  if d['symbol'] == '_const_sub128').update(storage=2))

    def test_field_source_scope_cannot_be_flattened(self):
        self.reject(lambda m: next(r for r in m['sections'] if r['base'] == '0x0062E461')['fields'][0].update(symbol_index=0))

    def test_original_mmx_state_cannot_gain_emms(self):
        self.reject(lambda m: m['packed_observations'][0].update(emms_offsets=[300]))

    def test_whole_original_opcode_observations_retained(self):
        self.reject(lambda m: m['packed_observations'][0]['instruction_mnemonics'].update(pmaddwd=5))

    def test_legacy_invert_fields_retained(self):
        self.reject(lambda m: next(r for r in m['sections'] if r['base'] == '0x0062E58F')['bindings'].pop())

    def test_six_complete_cfgs_retained(self):
        self.reject(lambda m: m['sections'][0]['flow'].update(reachable_instruction_count=1))

    def test_all_complete_prior_anchors_required(self):
        self.reject(lambda m: m['anchors'].pop())

    def test_nonreturn_error_anchor_cannot_be_cropped(self):
        self.reject(lambda m: next(r['record'] for r in m['anchors'] if 'png_error' in r['record']['symbol']).update(size=29))

    def test_no_unrelated_interior_credit(self):
        self.reject(lambda m: m['interiors'].append({'address': '0x006235BA'}))

    def test_all_cold_emitted_sections_required(self):
        self.reject(lambda m: m['public_control']['emission'].pop())

    def test_original_intrinsic_headers_required(self):
        self.reject(lambda m: m['public_control']['headers'].pop(next(iter(m['public_control']['headers']))))

    def test_public_scalar_layout_is_not_private_png_layout(self):
        self.assertEqual(M['public_control']['layout']['values'], [8, 1, 2, 4, 4, 4])
        self.reject(lambda m: m['public_control']['layout']['values'].__setitem__(0, 64))

    def test_png_unsigned_long_coff_interface_required(self):
        self.reject(lambda m: next(r for r in m['public_control']['emission']
                                  if any('ProbePngReadRows' in d['symbol'] for d in r['definitions']))['fields'][0]['symbol']
                    .update(symbol='?png_read_rows@D3DX@@YAXPAUpng_struct_def@1@PAPAE1I@Z'))

    def test_full_cold_cookie_fields_retained(self):
        self.reject(lambda m: next(r for r in m['public_control']['emission']
                                  if any('ProbePackedKeepState' in d['symbol'] for d in r['definitions']))['fields'].pop())

    def test_explicit_clear_and_preserve_controls_required(self):
        self.reject(lambda m: m['public_control'].update(probe_sha256='0' * 64))

    def test_absolute_crt_definition_is_not_pe_storage(self):
        self.reject(lambda m: m['absolute']['__except_list']['definition'].update(section=1))

    def test_unowned_field_destination_is_rejected(self):
        f = dict(offset=1, type='REL32', symbol='callee', addend=0, symbol_section=0, symbol_storage=2)
        b = dict(f, source_base='0x00002000', target_address='0x00002000')
        with self.assertRaises(ValueError): V.bind_fields(b'\xe8\0\0\0\0', [f], [b], {}, 1, 0x1000)

    def test_genuine_binding_requires_independent_symbol_owner(self):
        f = dict(offset=1, type='REL32', symbol='callee', addend=0, symbol_section=0, symbol_storage=2)
        b = dict(f, source_base='0x00002000', target_address='0x00002000')
        linked, calls, data = V.bind_fields(b'\xe8\0\0\0\0', [f], [b], {'callee': 0x2000}, 1, 0x1000)
        self.assertEqual(calls, {0x1001: 0x2000}); self.assertFalse(data)
        self.assertEqual(int.from_bytes(linked[1:], 'little'), 0xffb)


if __name__ == '__main__': unittest.main()
