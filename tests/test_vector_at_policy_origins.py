"""Guard complete vector policies, scoped ownership and COFF debug provenance."""
import copy
import importlib.util
import json
from pathlib import Path
import struct
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('vector_at_tests', ROOT / 'scripts/verify-vector-at-policy-origins.py')
V = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(V)
M = json.loads((ROOT / V.EVIDENCE).read_text())


class VectorPolicyTests(unittest.TestCase):
    def reject(self, mutate):
        m = copy.deepcopy(M); mutate(m)
        with self.assertRaises(ValueError): V.verify_plan(m)

    def test_immutable_complete_plan(self):
        self.assertEqual(V.digest((ROOT / V.EVIDENCE).read_bytes()), V.MANIFEST_SHA256)
        V.verify_plan(M)

    def test_original_source_pins(self):
        for path, sha in M['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT / path).read_bytes()), sha, path)

    def test_all_eighteen_complete_extents(self):
        self.assertEqual(sum(V.KEYS.values()), 615)
        self.reject(lambda m: m['functions'].pop())
        self.reject(lambda m: m['functions'][0].update(size=69))

    def test_no_private_source_or_abi_credit(self):
        for key in ['source_file', 'signature', 'calling_convention']:
            self.reject(lambda m: m['functions'][0]['accepted_function'].update({key: 'private'}))

    def test_no_exact_credit(self):
        self.reject(lambda m: m['functions'][0]['accepted_function'].update(match_percent='100.00'))

    def test_no_private_element_type_claim(self):
        self.reject(lambda m: m['functions'][0]['accepted_function'].update(proposed_name='std::vector<Private>::at'))

    def test_original_unknown_snapshot(self):
        self.reject(lambda m: m['functions'][0]['original_origin'].update(origin='library'))

    def test_all_actual_fields(self):
        self.reject(lambda m: m['sections'][0]['fields'].pop())

    def test_all_actual_bindings(self):
        self.reject(lambda m: m['sections'][0]['bindings'].pop())

    def test_same_source_has_independent_group_owners(self):
        a, b = M['groups'][0], M['groups'][2]
        self.assertEqual(a['source_symbol'], b['source_symbol'])
        self.assertNotEqual(a['root'], b['root'])
        self.reject(lambda m: m['groups'][2].update(root=m['groups'][0]['root']))

    def test_own_coff_symbol_indices(self):
        self.reject(lambda m: m['sections'][0]['source']['aux_records'][1].update(index=0))

    def test_whole_eh_carriers(self):
        carriers = [r for r in M['sections'] if r['kind'] == 'code' and r['size'] == 18]
        self.assertEqual(len(carriers), 4)
        self.assertTrue(all(r['roots'] == [0, 8] for r in carriers))
        self.reject(lambda m: next(r for r in m['sections'] if r['size'] == 18).update(size=8))

    def test_whole_eh_data(self):
        self.reject(lambda m: next(r for r in m['sections'] if r['kind'] == 'data' and r['size'] == 36).update(size=28))

    def test_entire_normal_and_exception_cfg(self):
        self.reject(lambda m: m['sections'][0]['flow'].update(reachable_instruction_count=1))

    def test_no_hidden_inventory_entry(self):
        self.reject(lambda m: m['interiors'].append({'address': '0x004093E1'}))

    def test_actual_xran_owners_not_legacy_alias(self):
        errors = [r for r in M['sections'] if r['symbol'].startswith('?_Xran@')]
        self.assertEqual(len(errors), 4)
        self.assertTrue(all(r['size'] == 90 for r in errors))
        self.reject(lambda m: next(r for r in m['sections'] if r['symbol'].startswith('?_Xran@')).update(symbol='?_Xlen'))

    def test_whole_throw_type_data(self):
        self.reject(lambda m: next(r for r in m['shared'] if r['record']['symbol'].startswith('__TI3')).get('record').update(size=4))

    def test_retained_shared_owners(self):
        self.reject(lambda m: m['shared'].pop())

    def test_actual_crt_helpers(self):
        self.reject(lambda m: m['crt_anchors'][0]['record'].update(size=57))

    def test_original_absolute_definition(self):
        self.reject(lambda m: m['absolute']['__except_list']['definition'].update(section=1))

    def test_whole_game_parent_and_call(self):
        self.reject(lambda m: m['parents'][0].update(call_site='0x004079F9'))

    def test_full_wrong_stride_alternatives(self):
        self.assertEqual(len(M['rejected_stride_alternatives']), 4)
        self.reject(lambda m: m['rejected_stride_alternatives'][1].update(size=57))

    def test_const_routes_retain_actual_typed_fields(self):
        self.assertTrue(all(r['size'] == 70 and r['dereference']['size'] == 16 for r in M['const_routes']))
        self.reject(lambda m: m['const_routes'][0]['fields'].pop())

    def test_const_dereference_cannot_be_mutable_wrapper(self):
        self.reject(lambda m: m['const_routes'][0]['dereference'].update(size=19))

    def test_all_ordinary_emissions(self):
        self.assertEqual(len(M['public_control']['emission']), 130)
        self.assertEqual(sum(r['size'] for r in M['public_control']['emission']), 5548)
        self.reject(lambda m: m['public_control']['emission'].pop())

    def test_all_actual_headers(self):
        self.assertEqual(len(M['public_control']['headers']), 27)
        self.reject(lambda m: m['public_control']['headers'].pop(next(iter(m['public_control']['headers']))))

    def test_generic_observations_not_private_layout(self):
        self.assertEqual(M['public_control']['layout']['values'], [4, 4, 4, 8, 16, 116, 16, 4, 4])
        self.reject(lambda m: m['public_control']['layout']['values'].__setitem__(5, 120))

    def test_unowned_local_field_cannot_reuse_other_group(self):
        f = dict(offset=1, type='REL32', symbol='local', addend=0,
                 symbol_section=2, symbol_storage=3, symbol_index=7, symbol_offset=0)
        b = dict(f, source_base='0x00002000', target_address='0x00002000')
        with self.assertRaises(ValueError):
            V.BASE.bind_fields(b'\xe8\0\0\0\0', [f], [b], {('G1', 2, 7): 0x2000}, 'G0', 0x1000)


class CoffLineProvenanceTests(unittest.TestCase):
    def fixture(self, base=80, pointer_delta=0, index=7, size=5):
        body = bytearray(base + 12)
        struct.pack_into('<8sIIIIIIHHI', body, 20, b'.text', 0, 0, size, 60, 0, base, 0, 2, 0)
        struct.pack_into('<IHIH', body, base, index, 0, 0, 123)
        aux = struct.pack('<IIIIH', 4, size, base + pointer_delta, 0, 0)
        source = dict(section=1, definitions=[dict(symbol='f', type=32)],
                      aux_records=[dict(symbol='f', index=7, aux_count=1, aux_hex=aux.hex())])
        return source, body

    def test_debug_file_shift_keeps_full_line_provenance(self):
        a = V.canonical_source(*self.fixture(80)); b = V.canonical_source(*self.fixture(112))
        self.assertEqual(a, b)
        self.assertEqual(a['coff_line_table'], [[7, 0], [0, 123]])

    def test_misaligned_debug_pointer_rejected(self):
        with self.assertRaises(ValueError): V.canonical_source(*self.fixture(pointer_delta=1))

    def test_other_symbol_debug_owner_rejected(self):
        with self.assertRaises(ValueError): V.canonical_source(*self.fixture(index=9))

    def test_truncated_debug_table_rejected(self):
        source, body = self.fixture()
        with self.assertRaises(ValueError): V.canonical_source(source, body[:-1])

    def test_function_aux_extent_not_normalized(self):
        self.assertNotEqual(V.canonical_source(*self.fixture(size=5)), V.canonical_source(*self.fixture(size=6)))

    def test_line_records_not_normalized(self):
        source, body = self.fixture(); changed = bytearray(body)
        struct.pack_into('<H', changed, 90, 124)
        self.assertNotEqual(V.canonical_source(source, body), V.canonical_source(source, changed))


if __name__ == '__main__': unittest.main()
