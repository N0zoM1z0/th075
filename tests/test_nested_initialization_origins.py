"""Reject truncated initialization evidence and unsupported ownership/credit."""
import copy
import importlib.util
import json
from pathlib import Path
import struct
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('initialization_tests', ROOT / 'scripts/verify-nested-initialization-origins.py')
V = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(V)
M = json.loads((ROOT / V.EVIDENCE).read_text())


class NestedInitializationTests(unittest.TestCase):
    def reject(self, change):
        m = copy.deepcopy(M); change(m)
        with self.assertRaises(ValueError): V.verify_plan(m)

    def test_complete_frozen_plan(self):
        self.assertEqual(V.digest((ROOT / V.EVIDENCE).read_bytes()), V.MANIFEST_SHA256)
        V.verify_plan(M)

    def test_independent_source_evidence_pins(self):
        for path, sha in M['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT / path).read_bytes()), sha, path)

    def test_only_two_authored_transitions_without_extent_change(self):
        self.assertEqual(sum(r['size'] for r in M['functions']), 192)
        self.assertTrue(all(r['accepted_origin']['origin'] == 'authored' for r in M['functions']))
        self.assertTrue(all(r['original_function']['size'] == r['accepted_function']['size'] for r in M['functions']))
        self.reject(lambda m: m['functions'].pop())

    def test_no_header_or_compiler_ownership_from_initialization_shape(self):
        for origin in ['compiler', 'library']:
            self.reject(lambda m: m['functions'][0]['accepted_origin'].update(origin=origin))

    def test_no_source_private_layout_abi_or_exact_credit(self):
        for key, value in [('source_file', 'game.cpp'), ('signature', 'PrivateOwner*'),
                           ('calling_convention', 'cdecl'), ('match_percent', '100.00')]:
            self.reject(lambda m: m['functions'][0]['accepted_function'].update({key: value}))

    def test_whole_initializer_native_cfg(self):
        self.reject(lambda m: m['functions'][0]['instructions'].pop())
        self.reject(lambda m: m['functions'][0]['cfg'].__setitem__(0, 0))

    def test_prefix_extent_is47_not_cropped28(self):
        self.assertEqual(V.WHOLE['0x00458880'], 47)
        self.reject(lambda m: m['functions'][1].update(size=28))

    def test_memset_then_both_explicit_clear_calls(self):
        self.assertEqual([r['target'] for r in M['functions'][0]['calls']],
                         ['0x00458880', '0x004589C0', '0x004589C0', '0x00640490', '0x00458A80', '0x00458A80'])
        self.reject(lambda m: m['functions'][0]['calls'].reverse())

    def test_complete_implicit_constructor93(self):
        self.assertEqual(M['alternatives'][0]['size'], 93)
        self.assertFalse(any(f['symbol'] == '_memset' or f['symbol'].startswith('?clear@') for f in M['alternatives'][0]['fields']))
        self.reject(lambda m: m['alternatives'][0].update(size=145))

    def test_complete_value_initialization_observer81(self):
        self.assertEqual(M['alternatives'][1]['size'], 81)
        self.reject(lambda m: m['alternatives'][1]['instructions'].pop())

    def test_complete_explicit_prefix_observer104(self):
        self.assertEqual(M['alternatives'][2]['size'], 104)
        self.reject(lambda m: m['alternatives'][2]['fields'].pop())

    def test_all_code_and_data_carriers(self):
        self.assertEqual(len(M['sections']), 37)
        self.assertEqual(sum(r['size'] for r in M['sections']), 1400)
        self.reject(lambda m: m['sections'].pop())

    def test_actual_fields_and_bindings_cannot_be_masked(self):
        self.assertEqual(sum(len(r['fields']) for r in M['sections']), 73)
        self.reject(lambda m: m['sections'][0]['fields'].pop())
        self.reject(lambda m: m['sections'][0]['bindings'].pop())

    def test_actual_coff_aux_indices_and_line_provenance(self):
        self.reject(lambda m: m['sections'][0]['source']['aux_records'][1].update(index=0))
        self.reject(lambda m: m['sections'][0]['source']['coff_line_table'].pop())

    def test_all_exception_data_and_unwind_roots(self):
        self.reject(lambda m: next(r for r in m['sections'] if r['kind'] == 'data').update(size=1))
        self.reject(lambda m: m['sections'][0]['roots'].pop())

    def test_native_coverage_includes_all_reachable_instructions(self):
        self.reject(lambda m: m['sections'][0]['flow'].update(reachable_instruction_count=1))

    def test_full_source_inventory_cannot_hide_entries(self):
        self.reject(lambda m: m['sections'][0]['inventory_entries'].pop())

    def test_both_full_authored_parents_and_actual_calls(self):
        self.assertEqual(sum(r['size'] for r in M['parents']), 5418)
        self.assertEqual([r['call']['site'] for r in M['parents']], ['0x00457692', '0x005F7214'])
        self.reject(lambda m: m['parents'][0]['instructions'].pop())
        self.reject(lambda m: m['parents'][1]['call'].update(target='0x00000000'))

    def test_memset_original_archive_own_function_aux96(self):
        p = M['memset']; aux = next(r for r in p['source']['aux_records'] if r['symbol'] == '_memset')
        self.assertEqual(struct.unpack_from('<I', bytes.fromhex(aux['aux_hex']), 4)[0], 96)
        self.assertEqual(p['cfg'], [2, 7])
        self.reject(lambda m: m['memset']['record'].update(member_offset='0'))

    def test_retained_definition_not_callee_observation(self):
        self.reject(lambda m: m['prior']['shared'][0]['owner']['record'].update(address='0x00000000'))

    def test_actual_weak_fallback_full_aux(self):
        self.assertEqual(len(bytes.fromhex(M['weak_references'][0]['aux_hex'])), 18)
        self.reject(lambda m: m['weak_references'][0].update(fallback_symbol_index=0))

    def test_original_absolute_crt_definition(self):
        self.reject(lambda m: m['prior']['absolute']['__except_list']['definition'].update(section=1))

    def test_all_ordinary_emission_and_original_headers(self):
        self.assertEqual(len(M['public_control']['emission']), 100)
        self.assertEqual(len(M['public_control']['headers']), 27)
        self.reject(lambda m: m['public_control']['emission'].pop())
        self.reject(lambda m: m['public_control']['headers'].pop(next(iter(m['public_control']['headers']))))

    def test_whole_layout_observation_carrier(self):
        self.assertEqual(M['public_control']['layout_values'], [16, 12, 116, 16, 20, 68, 84, 100, 116, 16])
        self.reject(lambda m: m['public_control']['layout_values'].pop())

    def test_four_short_or_private_origins_remain_unknown(self):
        self.assertEqual({r['function']['address'] for r in M['retained_unknowns']},
                         {'0x00458A80', '0x004589F0', '0x004588B0', '0x0045B630'})
        self.reject(lambda m: m['retained_unknowns'][0]['origin'].update(origin='library'))

    def test_duplicate_scoped_source_owner_rejected_independently(self):
        with self.assertRaises(ValueError):
            V.SOURCE.owned_catalog([M['sections'][0], M['sections'][0]], {}, 0, [])

    def test_borrowed_field_cannot_override_independent_owner(self):
        row = M['sections'][0]
        definition = next(d for d in row['source']['definitions'] if d['storage'] == 2)
        with self.assertRaises(ValueError):
            V.SOURCE.owned_catalog([row], {definition['symbol']: 1}, 0, [])

    def test_actual_call_must_be_within_complete_parent(self):
        raw = bytearray(b'\xe8' + struct.pack('<i', 0x2000 - 0x1005))
        V.check_call(raw, 0x1000, dict(site='0x00001000', target='0x00002000'))
        for call in [dict(site='0x00000FFF', target='0x00002000'),
                     dict(site='0x00001001', target='0x00002000'),
                     dict(site='0x00001000', target='0x00002001')]:
            with self.assertRaises(ValueError): V.check_call(raw, 0x1000, call)


if __name__ == '__main__': unittest.main()
