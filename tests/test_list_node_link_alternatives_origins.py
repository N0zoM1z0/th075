"""Guard whole public/intrusive node alternatives without ownership credit."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('node_tests', ROOT / 'scripts/verify-list-node-link-alternatives-origins.py')
V = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(V)
M = json.loads((ROOT / V.EVIDENCE).read_text())


class ListNodeAlternativesTests(unittest.TestCase):
    def reject(self, mutate):
        m = copy.deepcopy(M); mutate(m)
        with self.assertRaises(ValueError): V.verify_plan(m)

    def test_immutable_complete_review(self):
        self.assertEqual(V.digest((ROOT / V.EVIDENCE).read_bytes()), V.MANIFEST_SHA256)
        V.verify_plan(M)

    def test_prior_source_and_evidence_pins(self):
        for path, sha in M['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT / path).read_bytes()), sha, path)

    def test_all_seven_whole_leaves(self):
        self.assertEqual(sum(V.KEYS.values()), 68)
        self.reject(lambda m: m['leaves'].pop())

    def test_full_next_body_cannot_be_cropped(self):
        self.reject(lambda m: m['leaves'][0].update(size=7))

    def test_no_library_credit_from_shape(self):
        self.reject(lambda m: m['leaves'][0].update(decision='library'))

    def test_no_compiler_credit_from_shape(self):
        self.reject(lambda m: m['leaves'][0]['origin'].update(origin='compiler'))

    def test_original_unknown_rows(self):
        self.reject(lambda m: m['leaves'][0]['function'].update(owner='library', status='excluded'))

    def test_no_private_source_or_abi(self):
        for key in ['source_file', 'signature', 'calling_convention']:
            self.reject(lambda m: m['leaves'][0]['function'].update({key: 'private'}))

    def test_no_exact_credit(self):
        self.reject(lambda m: m['leaves'][0]['function'].update(match_percent='100.00'))

    def test_complete_typed_source_references(self):
        self.assertEqual([r['index'] for r in M['prior']], [2, 3, 4])
        self.reject(lambda m: m['prior'][0].update(index=3))

    def test_original_full_parent_records(self):
        self.assertEqual(sum(r['size'] for r in M['parents']), 556)
        self.reject(lambda m: m['parents'].pop())

    def test_all_real_parent_fields(self):
        self.assertEqual(sum(len(r['fields']) for r in M['parents']), 32)
        self.reject(lambda m: m['parents'][0]['fields'].pop())

    def test_source_binding_cannot_reuse_another_family(self):
        self.reject(lambda m: m['parents'][0]['bindings'][0].update(target_address='0x0041E100'))

    def test_all_parent_aux_and_cfg(self):
        self.reject(lambda m: m['parents'][0]['source']['aux_records'].pop())
        self.reject(lambda m: m['parents'][0]['flow'].update(reachable_instruction_count=1))

    def test_next_previous_and_value_are_distinct_policies(self):
        for role, size in [('next', 8), ('previous', 11), ('value', 11)]:
            alternatives = [r for r in M['alternatives'] if r['role'] == role]
            self.assertEqual(len(alternatives), 4)
            self.assertTrue(all(r['size'] == size and not r['fields'] for r in alternatives))
            self.assertEqual(len({r['source_sha256'] for r in alternatives}), 1)
        self.assertEqual(len({r['source_sha256'] for r in M['alternatives']}), 3)

    def test_ordinary_alternatives_cannot_be_removed(self):
        self.reject(lambda m: m['alternatives'].pop())

    def test_node_value_cannot_be_relabelled_as_previous(self):
        self.reject(lambda m: next(r for r in m['alternatives'] if r['role'] == 'value').update(role='previous'))

    def test_all_new_ordinary_emissions(self):
        self.assertEqual(len(M['public_control']['emission']), 31)
        self.assertEqual(sum(r['size'] for r in M['public_control']['emission']), 526)
        self.reject(lambda m: m['public_control']['emission'].pop())

    def test_all_actual_original_headers(self):
        self.assertEqual(len(M['public_control']['headers']), 28)
        self.reject(lambda m: m['public_control']['headers'].pop(next(iter(m['public_control']['headers']))))

    def test_complete_generic_node_observations(self):
        self.assertEqual(M['public_control']['layout_values'], [4, 16, 4, 4, 12, 24, 0, 4, 8])
        self.reject(lambda m: m['public_control']['layout_values'].__setitem__(4, 64))


if __name__ == '__main__': unittest.main()
