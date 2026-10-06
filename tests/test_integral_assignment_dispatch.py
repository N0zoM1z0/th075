"""Guard whole integral dispatch ownership, controls and bounded canonical state."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('integral_tests', ROOT/'scripts/verify-integral-assignment-dispatch-origins.py')
V = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(V)
M = json.loads((ROOT/V.EVIDENCE).read_text())


class IntegralAssignmentDispatchTests(unittest.TestCase):
    def reject(self, change):
        m = copy.deepcopy(M); change(m)
        with self.assertRaises(ValueError): V.verify_plan(m)

    def test_immutable_complete_inputs_and_bounded185(self):
        V.verify_plan(M)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()), V.MANIFEST_SHA256)
        for path, sha in M['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT/path).read_bytes()), sha, path)
        self.assertEqual(sum(V.WHOLE.values()), 185)
        self.reject(lambda m: m['functions'][0]['accepted_function'].update(size='49'))
        self.reject(lambda m: m['functions'][0]['instructions'].pop())

    def test_no_private_declaration_or_exact_credit(self):
        for key, value in [('source_file', 'Owner.cpp'), ('signature', 'Owner*'),
                           ('calling_convention', 'thiscall'), ('match_percent', '100.00')]:
            self.reject(lambda m: m['functions'][0]['accepted_function'].update({key: value}))

    def test_full_source_owners_aux_every_field_and_eh_cfg(self):
        self.assertEqual((len(M['sections']), sum(r['size'] for r in M['sections']),
                          sum(len(r['fields']) for r in M['sections']),
                          sum(r['kind'] == 'code' for r in M['sections'])), (221, 13561, 545, 185))
        self.reject(lambda m: m['sections'][0]['bindings'].clear())
        self.reject(lambda m: m['sections'][0]['source']['aux_records'].clear())
        self.reject(lambda m: next(r for r in m['sections'] if r['kind'] == 'code')['flow'].clear())

    def test_missing_assign_n_owner_cannot_be_replaced_by_observed_destination(self):
        scoped = [r for r in M['sections'] if r['group'] == 0]
        root = next(r for r in scoped if r['symbol'].startswith('??$_Assign@H@'))
        callee = next(r for r in scoped if r['symbol'].startswith('?_Assign_n@?$vector@'))
        catalog = V.SOURCE.owned_catalog([r for r in scoped if r is not callee], {}, 0, [])
        self.assertNotIn(callee['symbol'], catalog)
        with self.assertRaises(ValueError):
            V.SOURCE.BASE.BASE.bind_fields(bytes(root['size']), root['fields'], root['bindings'],
                                         catalog, 0, int(root['base'], 16))

    def test_all_actual_weak_aliases_have_complete_current_fallback_owners(self):
        self.assertEqual(len(M['weak_references']), 2)
        for g in M['groups']:
            scoped = [r for r in M['sections'] if r['group'] == g['id']]
            refs = [r for r in M['weak_references'] if r['symbol'] in g['weak_symbols']]
            catalog = V.SOURCE.owned_catalog(scoped, {}, g['id'], refs)
            for ref in refs:
                self.assertEqual(catalog[ref['symbol']], catalog[ref['fallback_symbol']])
                shortened = [r for r in scoped if r['source']['section'] != ref['fallback_definition']['section']]
                with self.assertRaises(ValueError): V.SOURCE.owned_catalog(shortened, {}, g['id'], refs)
        self.reject(lambda m: m['weak_references'][0].update(aux_hex='00'))

    def test_natural_ordinary_members_share_whole_target_bodies(self):
        self.assertEqual(sorted(q['whole_size'] for q in M['ordinary_members']), [37, 37, 50, 50])
        for q in M['ordinary_members']:
            source = next(r for r in M['sections'] if r['group'] == q['group'] and r['symbol'] == q['symbol'])
            original = next(r for r in M['sections'] if r['group'] == q['group']
                            and r['base'] == q['native'] and r['symbol'].startswith('??$'))
            self.assertEqual((source['size'], source['body_sha256']), (original['size'], original['body_sha256']))
        self.reject(lambda m: m['ordinary_members'].pop())

    def test_whole_pointer_category_and_range_routes_are_distinct(self):
        self.assertEqual(sorted(q['size'] for q in M['range_controls']), [11, 11, 51, 51, 88, 100])
        self.assertTrue(all(not q['raw_byte_equal'] for q in M['range_controls']))
        self.reject(lambda m: m['range_controls'][0].update(size=50))
        self.reject(lambda m: m['range_controls'][2].update(raw_byte_equal=True))

    def test_full_ordinary_emission_includes_and_readonly_observations(self):
        c = M['public_control']; emission = c['emission']
        self.assertEqual((len(emission), sum(r['size'] for r in emission),
                          sum(len(r['fields']) for r in emission)), (204, 14612, 547))
        self.assertEqual((len(c['headers']), c['layout_values']), (28, [4, 4, 1, 16, 20, 1, 1]))
        self.reject(lambda m: m['public_control']['emission'].pop())
        self.reject(lambda m: m['public_control']['layout_values'].pop())

    def test_three_whole_game_parents_and_actual_integer_call_sites(self):
        self.assertEqual(sum(r['size'] for r in M['parents']), 996)
        windows = [q for r in M['parents'] for q in r['call_sequences']]
        self.assertEqual({q['site'] for q in windows}, {'0x004075AD', '0x004076F8', '0x00456875'})
        self.reject(lambda m: m['parents'][-1]['call_sequences'][0]['instructions'].pop())

    def test_unrelated_canonical_changes_and_unapproved_selected_states_rejected(self):
        actual = {name: V.rows(name) for name in ['functions.csv', 'function-origins.csv']}
        for selected in [False, True]:
            changed = copy.deepcopy(actual)
            row = next(r for r in changed['functions.csv'] if (r['address'] in V.WHOLE) == selected)
            row['calling_convention'] = 'cdecl'
            with patch.object(V, 'rows', side_effect=lambda name: changed[name]):
                with self.assertRaises(ValueError): V.verify_canonical(M, check_unselected=True)

    def test_later_independent_cohorts_do_not_change_scoped_source_expectations(self):
        actual = {name: V.rows(name) for name in ['functions.csv', 'function-origins.csv']}
        scoped = {r['function']['address'] for r in M['canonical']}
        row = next(r for r in actual['function-origins.csv'] if r['address'] not in scoped and r['origin'] == 'unknown')
        row.update(origin='library', disposition='exclude', evidence_id='later-independent-cohort')
        with patch.object(V, 'rows', side_effect=lambda name: actual[name]):
            V.verify_canonical(M)
            with self.assertRaises(ValueError): V.verify_canonical(M, check_unselected=True)

    def test_retained_provider_and_no_historical_rewrite(self):
        self.assertFalse(M['historical_snapshots'])
        self.assertEqual(len(M['shared']), 13)
        self.assertEqual(M['retained_provider']['script'], 'scripts/verify-nested-deque-size-origins.py')
        self.reject(lambda m: m['shared'][0]['owner']['record'].update(address='0x00400000'))
        self.reject(lambda m: m['unselected_sha256'].update({'functions.csv': '0'*64}))


@unittest.skipUnless((ROOT/'resources/th075.exe').is_file(), 'private pinned target is not supplied')
class IntegralAssignmentNativeTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.c = V.module('integral_test_c', 'compare-coff-function.py')
        cls.flow = V.module('integral_test_flow', 'sdk_image_carriers.py')
        cls.target = cls.c.verified_target()

    def test_whole_roots_and_game_receivers(self):
        V.verify_native(M, self.target, self.c, self.flow)

    def test_shortened_parent_and_changed_count_receiver_rejected(self):
        for change in [lambda m: m['parents'][0].update(size=340),
                       lambda m: m['parents'][-1]['call_sequences'][0]['instructions'][0].update(operands='wrong')]:
            m = copy.deepcopy(M); change(m)
            with self.assertRaises(ValueError): V.verify_native(m, self.target, self.c, self.flow)


if __name__ == '__main__': unittest.main()
