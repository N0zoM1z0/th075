"""Guard complete policies, original header dispatch and independently owned fields."""
import copy
import importlib.util
import json
from pathlib import Path
import struct
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('neighbor_tests', ROOT / 'scripts/verify-neighbor-policy-origins.py')
V = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(V)
M = json.loads((ROOT / V.EVIDENCE).read_text())


class NeighborPolicyTests(unittest.TestCase):
    def reject(self, change):
        m = copy.deepcopy(M); change(m)
        with self.assertRaises(ValueError): V.verify_plan(m)

    def test_complete_frozen_plan(self):
        self.assertEqual(V.digest((ROOT / V.EVIDENCE).read_bytes()), V.MANIFEST_SHA256)
        V.verify_plan(M)

    def test_prior_source_evidence_and_all_authored_pins(self):
        for path, sha in M['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT / path).read_bytes()), sha, path)

    def test_only_four_transitions_with_complete_extents_preserved(self):
        self.assertEqual({r['address']: r['size'] for r in M['functions']}, V.WHOLE)
        self.assertTrue(all(r['original_function']['size'] == r['accepted_function']['size'] for r in M['functions']))
        self.reject(lambda m: m['functions'].pop())

    def test_two_authored_policies163(self):
        self.assertEqual(sum(r['size'] for r in M['functions'] if r['accepted_origin']['origin'] == 'authored'), 163)
        self.reject(lambda m: m['functions'][0]['accepted_origin'].update(origin='compiler'))

    def test_two_public_library_policies224(self):
        self.assertEqual(sum(r['size'] for r in M['functions'] if r['accepted_origin']['origin'] == 'library'), 224)
        self.reject(lambda m: m['functions'][2]['accepted_origin'].update(origin='authored'))

    def test_no_source_private_layout_abi_or_exact_credit(self):
        for key, value in [('source_file', 'game.cpp'), ('signature', 'PrivateOwner*'),
                           ('calling_convention', 'cdecl'), ('match_percent', '100.00')]:
            self.reject(lambda m: m['functions'][0]['accepted_function'].update({key: value}))

    def test_allocation_guard_and_full_memset_calls(self):
        self.assertEqual(M['functions'][0]['cfg'], [1, 1])
        self.assertEqual([r['target'] for r in M['functions'][0]['calls']], ['0x0064159D', '0x00640490'])
        self.reject(lambda m: m['functions'][0]['calls'].reverse())

    def test_constructor_clear_after_complete_public_construction(self):
        r = next(r for r in M['functions'] if r['address'] == '0x00458960')
        self.assertEqual([q['target'] for q in r['calls']], ['0x00458AA0', '0x00458B50'])
        self.reject(lambda m: m['functions'][1]['instructions'].pop())

    def test_default_constructor22_has_no_explicit_clear(self):
        self.assertEqual(M['alternatives'][0]['size'], 22)
        self.assertFalse(any(f['symbol'].startswith('?clear@') for f in M['alternatives'][0]['fields']))
        self.reject(lambda m: m['alternatives'][0].update(size=93))

    def test_member_zero_constructor40_is_whole_negative_control(self):
        self.assertEqual(M['alternatives'][1]['size'], 40)
        self.assertFalse(any(f['symbol'].startswith('?clear@') for f in M['alternatives'][1]['fields']))
        self.reject(lambda m: m['alternatives'][1]['instructions'].pop())

    def test_single_insert114_cannot_replace_assignment195(self):
        self.assertEqual(M['alternatives'][2]['size'], 114)
        r = next(r for r in M['sections'] if r['base'] == '0x00458E70')
        self.assertEqual(r['size'], 195); self.assertTrue(r['symbol'].startswith('?_Assign_n@'))
        self.reject(lambda m: m['alternatives'][2].update(size=195))

    def test_full_count_assignment_temporary_erase_insert_and_cleanup(self):
        r = next(r for r in M['functions'] if r['address'] == '0x00458E70')
        self.assertEqual([q['target'] for q in r['calls']],
                         ['0x004591E0', '0x00459890', '0x00442100', '0x00459900',
                          '0x00442100', '0x004598D0', '0x004588E0'])
        self.reject(lambda m: m['functions'][2]['calls'].pop())

    def test_public_wrapper29_binds_entire_assignment_and_ret8(self):
        r = next(r for r in M['sections'] if r['base'] == '0x00458B30')
        parent = next(r for r in M['sections'] if r['base'] == '0x00458E70')
        self.assertEqual(len(r['fields']), 1); self.assertEqual(r['fields'][0]['symbol'], parent['symbol'])
        q = next(r for r in M['functions'] if r['address'] == '0x00458B30')
        self.assertEqual(q['instructions'][-1]['operands'], '8')
        self.reject(lambda m: m['functions'][3]['calls'][0].update(target='0x00000000'))

    def test_all_three_scoped_graphs(self):
        rows = [[r for r in M['sections'] if r['group'] == g['id']] for g in M['groups']]
        self.assertEqual([len(r) for r in rows], [1, 50, 119])
        self.assertEqual([sum(r['size'] for r in rows) for rows in rows], [70, 1861, 7650])
        self.reject(lambda m: m['groups'].pop())

    def test_all402_actual_fields_and_bindings(self):
        self.assertEqual(sum(len(r['fields']) for r in M['sections']), 402)
        self.reject(lambda m: m['sections'][0]['fields'].pop())
        self.reject(lambda m: m['sections'][0]['bindings'].pop())

    def test_real_coff_aux_indices_and_debug_line_provenance(self):
        self.reject(lambda m: m['sections'][1]['source']['aux_records'][1].update(index=0))
        self.reject(lambda m: m['sections'][1]['source']['coff_line_table'].pop())

    def test_all143_normal_and_exception_cfgs(self):
        self.assertEqual(sum(r['kind'] == 'code' for r in M['sections']), 143)
        self.reject(lambda m: m['sections'][1]['roots'].pop())
        self.reject(lambda m: m['sections'][1]['flow'].update(reachable_instruction_count=1))

    def test_whole_data_owners_cannot_be_cropped(self):
        self.reject(lambda m: next(r for r in m['sections'] if r['kind'] == 'data').update(size=1))

    def test_whole_source_inventory_cannot_hide_entries(self):
        self.reject(lambda m: m['sections'][0]['inventory_entries'].pop())

    def test_native_complete_selected_policy_hashes(self):
        self.reject(lambda m: m['functions'][0].update(body_sha256='0' * 64))

    def test_two_whole_authored_parents5418_and_three_actual_calls(self):
        self.assertEqual(sum(r['size'] for r in M['parents']), 5418)
        self.assertEqual(sum(len(r['calls']) for r in M['parents']), 3)
        self.reject(lambda m: m['parents'][0]['instructions'].pop())

    def test_original_memset96_own_aux_and_full_cfg(self):
        aux = next(r for r in M['memset']['source']['aux_records'] if r['symbol'] == '_memset')
        self.assertEqual(struct.unpack_from('<I', bytes.fromhex(aux['aux_hex']), 4)[0], 96)
        self.assertEqual(M['memset']['cfg'], [2, 7])
        self.reject(lambda m: m['memset']['record'].update(member_offset='0'))

    def test_retained_definition_not_target_field_observation(self):
        self.reject(lambda m: m['prior']['shared'][0]['owner']['record'].update(address='0x00000000'))

    def test_actual_weak_aux_and_group_ownership(self):
        self.assertEqual(len(bytes.fromhex(M['weak_references'][0]['aux_hex'])), 18)
        self.assertEqual([len(g['weak_symbols']) for g in M['groups']], [0, 1, 1])
        self.reject(lambda m: m['groups'][0]['weak_symbols'].append(M['weak_references'][0]['symbol']))

    def test_original_absolute_crt_owner(self):
        self.reject(lambda m: m['prior']['absolute']['__except_list']['definition'].update(section=1))

    def test_full454_ordinary_emissions28704(self):
        self.assertEqual(len(M['public_control']['emission']), 454)
        self.assertEqual(sum(r['size'] for r in M['public_control']['emission']), 28704)
        self.reject(lambda m: m['public_control']['emission'].pop())

    def test_both_original_cpp_includes_and_headers(self):
        self.assertEqual(len(M['public_control']['headers']), 29)
        for p in ['tests/origin_probes/NestedVectorInsertionCarriers.cpp', 'tests/origin_probes/VectorInsertionCarriers.cpp']:
            self.assertIn(p, M['public_control']['headers'])
            self.reject(lambda m: m['public_control']['headers'].pop(p))

    def test_full_combined_observation96_not_new32_only(self):
        self.assertEqual(len(M['public_control']['layout_values']), 24)
        self.assertEqual(M['public_control']['layout_values'][-8:], [36, 16, 8, 12, 20, 16, 18, 20])
        self.reject(lambda m: m['public_control']['layout_values'].pop(0))

    def test_thirteen_private_and_short_controls_remain_unknown(self):
        self.assertEqual(len(M['retained_unknowns']), 13)
        self.assertTrue({'0x004591E0', '0x0045AAE0', '0x00458B50', '0x00458AD0', '0x00459890'}
                        <= {r['function']['address'] for r in M['retained_unknowns']})
        self.reject(lambda m: m['retained_unknowns'][0]['origin'].update(origin='library'))

    def test_duplicate_scoped_source_owner_rejected_independently(self):
        with self.assertRaises(ValueError): V.SOURCE.owned_catalog([M['sections'][0]] * 2, {}, 0, [])

    def test_borrowed_definition_cannot_override_independent_owner(self):
        row = M['sections'][0]; d = next(d for d in row['source']['definitions'] if d['storage'] == 2)
        with self.assertRaises(ValueError): V.SOURCE.owned_catalog([row], {d['symbol']: 1}, 0, [])

    def test_weak_binding_requires_full_strong_source_owner(self):
        with self.assertRaises(ValueError): V.SOURCE.owned_catalog([M['sections'][0]], {}, 0, M['weak_references'])

    def test_call_evidence_requires_full_instruction_inside_parent(self):
        raw = b'\xe8' + struct.pack('<i', 0x2000 - 0x1005)
        V.check_call(raw, 0x1000, dict(site='0x00001000', target='0x00002000'))
        for site, target in [('0x00000FFF', '0x00002000'), ('0x00001001', '0x00002000'), ('0x00001000', '0x00002001')]:
            with self.assertRaises(ValueError): V.check_call(raw, 0x1000, dict(site=site, target=target))


if __name__ == '__main__': unittest.main()
