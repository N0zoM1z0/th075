"""Guard complete deque count extents and actual source-local recovery ownership."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('deque_count_tests', ROOT / 'scripts/verify-byte-deque-count-origins.py')
V = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(V)
M = json.loads((ROOT / V.EVIDENCE).read_text())


class ByteDequeCountTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.c = V.module('count_test_target', 'compare-coff-function.py')
        cls.target = cls.c.verified_target()
        cls.flow = V.module('count_test_flow', 'sdk_image_carriers.py')

    def reject(self, change):
        m = copy.deepcopy(M); change(m)
        with self.assertRaises(ValueError): V.verify_plan(m)

    def reject_native(self, change):
        m = copy.deepcopy(M); change(m)
        with self.assertRaises(ValueError): V.verify_recovery(m, self.target, self.c, self.flow)

    def test_complete_plan_and_retained_pins(self):
        self.assertEqual(V.digest((ROOT / V.EVIDENCE).read_bytes()), V.MANIFEST_SHA256)
        V.verify_plan(M)
        for path, sha in M['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT / path).read_bytes()), sha, path)

    def test_six_library_transitions_with_two_contained_interiors(self):
        self.assertEqual(len(M['functions']), 6)
        self.assertEqual(sum(r['size'] for r in M['functions']), 1806)
        self.assertEqual(sum(r['size'] for r in M['functions'] if not r['source_offset']), 1696)
        self.reject(lambda m: m['functions'].pop())
        self.reject(lambda m: m['functions'][0]['accepted_origin'].update(origin='authored'))

    def test_only_insertion_extent_changes(self):
        rows = [r for r in M['functions'] if r['original_function']['size'] != r['accepted_function']['size']]
        self.assertEqual([(r['address'], r['original_function']['size'], r['accepted_function']['size']) for r in rows], [('0x00455E40', '1459', '1521')])
        self.reject(lambda m: m['functions'][0]['accepted_function'].update(size='28'))

    def test_no_private_source_abi_or_exact_credit(self):
        for key, value in [('source_file', 'game.cpp'), ('signature', 'PrivateByte*'), ('calling_convention', 'cdecl'), ('match_percent', '100.00')]:
            self.reject(lambda m: m['functions'][0]['accepted_function'].update({key: value}))

    def test_all70_owners5500_and_all178_fields(self):
        self.assertEqual((len(M['sections']), sum(r['size'] for r in M['sections']), sum(len(r['fields']) for r in M['sections'])), (70, 5500, 178))
        self.reject(lambda m: m['sections'][0]['fields'].pop())
        self.reject(lambda m: m['sections'][0]['bindings'].pop())

    def test_complete62_cfgs_and_three_insertion_roots(self):
        self.assertEqual(sum(r['kind'] == 'code' for r in M['sections']), 62)
        r = next(r for r in M['sections'] if r['base'] == '0x00455E40')
        self.assertEqual(r['roots'], [0, 759, 1459])
        self.reject(lambda m: next(r for r in m['sections'] if r['base'] == '0x00455E40')['roots'].pop())

    def test_real_coff_aux_line_and_local_definitions(self):
        self.reject(lambda m: m['sections'][0]['source']['coff_line_table'].pop())
        self.reject(lambda m: m['recovery'][0]['definition'].update(storage=2))
        self.reject(lambda m: m['recovery'][0]['eh_field'].update(symbol_index=0))

    def test_real_weak_aux_and_full_strong_fallback(self):
        self.assertEqual(len(M['weak_references']), 1)
        self.reject(lambda m: m['weak_references'].pop())

    def test_full_eh132_owns_both_local_recovery_pointers(self):
        r = next(r for r in M['sections'] if r['base'] == '0x006695B8')
        self.assertEqual(r['size'], 132)
        self.assertEqual([r['eh_field']['offset'] for r in M['recovery']], [44, 60])
        self.reject(lambda m: m['recovery'][0]['eh_field'].update(symbol_offset=758))
        self.reject(lambda m: m['recovery'][1]['eh_field'].update(addend=1))

    def test_complete_native_recovery_protocol(self):
        V.verify_recovery(M, self.target, self.c, self.flow)

    def test_front48_includes_external_to_view_but_owned_shared_exit(self):
        self.reject_native(lambda m: next(r for r in m['functions'] if r['address'] == '0x00456137')['instructions'].pop())
        self.reject_native(lambda m: m['recovery'][0].update(common_exit='0x00456416'))

    def test_back62_keeps_real_ret16(self):
        self.reject_native(lambda m: next(r for r in m['functions'] if r['address'] == '0x004563F3')['instructions'][-1].update(operands='0xc'))

    def test_recovery_cannot_escape_complete_source(self):
        self.reject_native(lambda m: next(r for r in m['functions'] if r['address'] == '0x00456137').update(source_owner='0x00455CA0'))
        self.reject_native(lambda m: next(r for r in m['functions'] if r['address'] == '0x004563F3').update(source_offset=1458))

    def test_alignment15_is_not_extra_source_padding(self):
        self.reject_native(lambda m: m['extent']['alignment'].update(size=14))
        self.reject(lambda m: m['extent']['next_owner'].update(size=225))

    def test_whole_inventory_keeps_interiors_visible(self):
        r = next(r for r in M['sections'] if r['base'] == '0x00455E40')
        self.assertEqual([q['function']['address'] for q in r['inventory_entries']], ['0x00455E40', '0x00456137', '0x004563F3'])
        self.reject(lambda m: next(r for r in m['sections'] if r['base'] == '0x00455E40')['inventory_entries'].pop())

    def test_complete_public_insert37_is_distinct_from_worker1521(self):
        self.assertEqual(M['public_insert_control']['size'], 37)
        self.assertEqual(len(M['public_insert_control']['fields']), 1)
        self.reject(lambda m: m['public_insert_control'].update(size=1521))

    def test_ordinary121_emissions8145_and_full_layout16(self):
        self.assertEqual(len(M['public_control']['emission']), 121)
        self.assertEqual(sum(r['size'] for r in M['public_control']['emission']), 8145)
        self.assertEqual(M['public_control']['layout_values'], [1, 20, 8, 8])
        self.reject(lambda m: m['public_control']['emission'].pop())
        self.reject(lambda m: m['public_control']['layout_values'].pop())

    def test_original_headers_and_independent_erase_proof(self):
        self.assertEqual(len(M['public_control']['headers']), 27)
        self.assertEqual(M['erase_prior']['path'], 'config/vendor-deque-erase-origins.json')
        self.reject(lambda m: m['erase_prior'].update(sha256='0' * 64))

    def test_retained_definition_cannot_be_borrowed_from_native_field(self):
        self.reject(lambda m: m['prior']['shared'][0]['owner']['record'].update(address='0x00000000'))

    def test_duplicate_source_owner_rejected(self):
        with self.assertRaises(ValueError): V.SOURCE.owned_catalog([M['sections'][0]] * 2, {}, 0, [])

    def test_observed_address_cannot_override_defined_source(self):
        row = M['sections'][0]; d = next(d for d in row['source']['definitions'] if d['storage'] == 2)
        with self.assertRaises(ValueError): V.SOURCE.owned_catalog([row], {d['symbol']: 1}, 0, [])


if __name__ == '__main__': unittest.main()
