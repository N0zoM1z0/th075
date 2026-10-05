"""Preserve complete public/ordinary getter ambiguity and independent contexts."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('leaf_tests', ROOT / 'scripts/verify-vector-list-leaf-alternatives-origins.py')
V = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(V)
M = json.loads((ROOT / V.EVIDENCE).read_text())


class LeafAlternativesTests(unittest.TestCase):
    def reject(self, mutate):
        m = copy.deepcopy(M); mutate(m)
        with self.assertRaises(ValueError): V.verify_plan(m)

    def test_immutable_complete_review(self):
        self.assertEqual(V.digest((ROOT / V.EVIDENCE).read_bytes()), V.MANIFEST_SHA256)
        V.verify_plan(M)

    def test_prior_source_and_evidence_pins(self):
        for path, sha in M['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT / path).read_bytes()), sha, path)

    def test_all_six_whole_leaves(self):
        self.assertEqual(sum(V.KEYS.values()), 96)
        self.reject(lambda m: m['leaves'].pop())
        self.reject(lambda m: m['leaves'][0].update(size=15))

    def test_shape_cannot_gain_library_credit(self):
        self.reject(lambda m: m['leaves'][0].update(decision='library'))

    def test_shape_cannot_gain_compiler_credit(self):
        self.reject(lambda m: m['leaves'][0]['origin'].update(origin='compiler'))

    def test_unknown_canonical_owner_preserved(self):
        self.reject(lambda m: m['leaves'][0]['function'].update(owner='library', status='excluded'))

    def test_no_source_or_private_abi_credit(self):
        for key in ['source_file', 'signature', 'calling_convention']:
            self.reject(lambda m: m['leaves'][0]['function'].update({key: 'private'}))

    def test_no_exact_credit(self):
        self.reject(lambda m: m['leaves'][0]['function'].update(match_percent='100.00'))

    def test_all_whole_parents_and_real_fields(self):
        self.assertEqual(sum(len(r['fields']) for r in M['parents']), 34)
        self.reject(lambda m: m['parents'].pop())
        self.reject(lambda m: m['parents'][0]['fields'].pop())

    def test_real_parent_binding_cannot_change(self):
        self.reject(lambda m: m['parents'][0]['bindings'][0].update(target_address='0x0040EA20'))

    def test_full_parent_source_aux_and_cfg(self):
        self.reject(lambda m: m['parents'][0]['source']['aux_records'].pop())
        self.reject(lambda m: m['parents'][0]['flow'].update(reachable_instruction_count=1))

    def test_whole_list_erase_parent(self):
        self.reject(lambda m: next(r for r in m['parents'] if r['address'] == '0x00411F20').update(size=185))

    def test_six_distinct_public_and_ordinary_definitions(self):
        symbols = [r['symbol'] for r in M['alternatives']]
        self.assertEqual(sum(s.startswith('??Dconst_iterator') for s in symbols), 2)
        self.assertEqual(sum(s.startswith('?_Mynode') for s in symbols), 2)
        self.assertEqual(sum(s.startswith('?get@Ordinary') for s in symbols), 2)
        self.assertEqual(len({r['source_sha256'] for r in M['alternatives']}), 1)

    def test_ordinary_alternatives_cannot_be_discarded(self):
        self.reject(lambda m: m['alternatives'].pop())

    def test_getter_body_cannot_be_cropped(self):
        self.reject(lambda m: m['alternatives'][0].update(size=15))

    def test_source_definitions_cannot_be_relabelled(self):
        self.reject(lambda m: m['alternatives'][0].update(symbol='private_getter'))

    def test_all_prior_ordinary_emissions(self):
        self.assertEqual(sum(len(r['emission']) for r in M['prior']), 912)
        self.assertEqual(sum(sum(q['size'] for q in r['emission']) for r in M['prior']), 40011)
        self.reject(lambda m: m['prior'][0]['emission'].pop())

    def test_actual_original_includes(self):
        self.reject(lambda m: m['prior'][0]['headers'].pop(next(iter(m['prior'][0]['headers']))))

    def test_full_new_ordinary_emission_and_layout(self):
        self.assertEqual(len(M['public_control']['emission']), 13)
        self.assertEqual(sum(r['size'] for r in M['public_control']['emission']), 206)
        self.assertEqual(M['public_control']['layout_values'], [4, 16, 4, 4, 4, 4, 4, 4])
        self.reject(lambda m: m['public_control']['emission'].pop())
        self.reject(lambda m: m['public_control']['layout_values'].__setitem__(0, 116))

    def test_retained_catalog_uses_owners_not_observed_field_targets(self):
        p = dict(controls=[dict(address='0x00001000', section=dict(definitions=[
            dict(symbol='callee', offset=3, storage=2)]), bindings=[dict(symbol='callee', target_address='0xDEADBEEF')])], external={})
        self.assertEqual(V.retained_catalog(p), {'callee': 0x1003})

    def test_conflicting_complete_owners_rejected(self):
        p = dict(controls=[dict(address='0x00001000', section=dict(definitions=[
            dict(symbol='callee', offset=0, storage=2)]))], external={'callee': '0x00002000'})
        with self.assertRaises(ValueError): V.retained_catalog(p)


if __name__ == '__main__': unittest.main()
