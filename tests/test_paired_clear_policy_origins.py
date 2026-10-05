"""Guard complete construction carriers and native game-policy ownership context."""
import copy
import importlib.util
import json
from pathlib import Path
import struct
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('paired_clear_tests', ROOT / 'scripts/verify-paired-clear-policy-origins.py')
V = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(V)
M = json.loads((ROOT / V.EVIDENCE).read_text())


class PairedClearPolicyTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.c = V.module('paired_test_target', 'compare-coff-function.py')
        cls.target = cls.c.verified_target()
        cls.flow = V.module('paired_test_flow', 'sdk_image_carriers.py')
        cls.pe = V.module('paired_test_pe', 'verify-sdk-x3d-origins.py')
        cls.authored = V.module('paired_test_authored', 'verify-authored-origins.py')
        cls.functions = {r['function']['address']: r['function'] for r in M['native_unknowns']}
        cls.origins = {r['origin']['address']: r['origin'] for r in M['native_unknowns']}

    def reject(self, change):
        m = copy.deepcopy(M); change(m)
        with self.assertRaises(ValueError): V.verify_plan(m)

    def context(self, m):
        V.verify_native_context(m, self.target, self.c, self.flow, self.pe, self.authored, self.functions, self.origins)

    def reject_context(self, change):
        m = copy.deepcopy(M); change(m)
        with self.assertRaises(ValueError): self.context(m)

    def test_complete_frozen_plan(self):
        self.assertEqual(V.digest((ROOT / V.EVIDENCE).read_bytes()), V.MANIFEST_SHA256)
        V.verify_plan(M)

    def test_prior_source_evidence_and_all_authored_pins(self):
        for path, sha in M['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT / path).read_bytes()), sha, path)

    def test_four_authored_policies355_and_whole_extents(self):
        self.assertEqual({r['address']: r['size'] for r in M['functions']}, V.WHOLE)
        self.assertEqual(sum(r['size'] for r in M['functions']), 355)
        self.assertTrue(all(r['accepted_origin']['origin'] == 'authored' for r in M['functions']))
        self.reject(lambda m: m['functions'].pop())

    def test_no_source_private_layout_abi_or_exact_credit(self):
        for key, value in [('source_file', 'game.cpp'), ('signature', 'PrivateOwner*'),
                           ('calling_convention', 'cdecl'), ('match_percent', '100.00')]:
            self.reject(lambda m: m['functions'][0]['accepted_function'].update({key: value}))

    def test_complete_deque_construction_then_clear75(self):
        self.assertEqual([r['target'] for r in M['functions'][0]['calls']], ['0x004212F0', '0x004214C0'])
        self.reject(lambda m: m['functions'][0]['calls'].reverse())

    def test_complete_vector_construction_then_clear75(self):
        self.assertEqual([r['target'] for r in M['functions'][1]['calls']], ['0x005F7F70', '0x005F8020'])
        self.reject(lambda m: m['functions'][1]['instructions'].pop())

    def test_two_implicit22_controls_have_no_explicit_clear(self):
        self.assertEqual([r['size'] for r in M['alternatives']], [22, 22])
        self.assertFalse(any(f['symbol'].startswith('?clear@') for r in M['alternatives'] for f in r['fields']))
        self.reject(lambda m: m['alternatives'][0].update(size=75))

    def test_deque_size8_and_full_external_destruction_protocol(self):
        self.assertEqual(M['groups'][0]['width'], 8)
        r = next(r for r in M['sections'] if r['base'] == '0x004229B0')
        wrapper = next(r for r in M['sections'] if r['base'] == '0x004229F0')
        self.assertEqual((r['size'], wrapper['size']), (15, 44))
        self.assertTrue(wrapper['symbol'].startswith('??_GClearValue8'))
        self.assertIn(M['opaque_destructor']['symbol'], [f['symbol'] for f in wrapper['fields']])
        self.reject(lambda m: m['opaque_destructor'].update(size=42))

    def test_external_destructor43_keeps_prior_R153_record_and_no_stack_arguments(self):
        r = M['opaque_destructor']
        self.assertEqual(r['origin']['evidence_id'], 'R153')
        self.assertEqual(r['instructions'][-1]['operands'], '')
        self.reject(lambda m: m['opaque_destructor']['instructions'][-1].update(operands='4'))

    def test_two_complete_graphs885_and1299(self):
        rows = [[r for r in M['sections'] if r['group'] == g['id']] for g in M['groups']]
        self.assertEqual([len(r) for r in rows], [21, 37])
        self.assertEqual([sum(r['size'] for r in rows) for rows in rows], [885, 1299])
        self.reject(lambda m: m['groups'].pop())

    def test_all100_actual_fields_and_bindings(self):
        self.assertEqual(sum(len(r['fields']) for r in M['sections']), 100)
        self.reject(lambda m: m['sections'][0]['fields'].pop())
        self.reject(lambda m: m['sections'][0]['bindings'].pop())

    def test_actual_coff_aux_and_debug_line_provenance(self):
        self.reject(lambda m: m['sections'][0]['source']['aux_records'][1].update(index=0))
        self.reject(lambda m: m['sections'][0]['source']['coff_line_table'].pop())

    def test_all49_normal_and_exception_cfgs(self):
        self.assertEqual(sum(r['kind'] == 'code' for r in M['sections']), 49)
        self.reject(lambda m: m['sections'][0]['roots'].pop())
        self.reject(lambda m: m['sections'][0]['flow'].update(reachable_instruction_count=1))

    def test_whole_data_owners_and_inventory_cannot_be_cropped(self):
        self.reject(lambda m: next(r for r in m['sections'] if r['kind'] == 'data').update(size=1))
        self.reject(lambda m: m['sections'][0]['inventory_entries'].pop())

    def test_seven_whole_game_contexts6129_and_two_actual_calls(self):
        self.assertEqual(sum(r['size'] for r in M['parents']), 6129)
        self.assertEqual(sum(len(r['calls']) for r in M['parents']), 2)
        self.reject(lambda m: m['parents'][0]['instructions'].pop())

    def test_script_parser_switch_remap_remains_complete(self):
        self.assertEqual(M['parents'][0]['cfg'], [1, 63])
        self.assertEqual(M['parents'][0]['switches'][0]['remap_size'], '100')
        self.reject(lambda m: m['parents'][0]['switches'].pop())

    def test_retained_definition_not_field_observation(self):
        self.reject(lambda m: m['prior']['shared'][0]['owner']['record'].update(address='0x00000000'))

    def test_actual_weak_aux_and_positive_fallback_owner(self):
        self.assertEqual(len(bytes.fromhex(M['weak_references'][0]['aux_hex'])), 18)
        self.assertEqual([len(g['weak_symbols']) for g in M['groups']], [0, 1])
        self.reject(lambda m: m['groups'][0]['weak_symbols'].append(M['weak_references'][0]['symbol']))

    def test_original_absolute_crt_owner(self):
        self.reject(lambda m: m['prior']['absolute']['__except_list']['definition'].update(section=1))

    def test_full381_ordinary_emissions22716(self):
        self.assertEqual(len(M['public_control']['emission']), 381)
        self.assertEqual(sum(r['size'] for r in M['public_control']['emission']), 22716)
        self.reject(lambda m: m['public_control']['emission'].pop())

    def test_all29_original_cpp_and_sdk_includes(self):
        self.assertEqual(len(M['public_control']['headers']), 29)
        self.assertIn('tests/origin_probes/VectorInsertionCarriers.cpp', M['public_control']['headers'])
        self.assertTrue(any(p.endswith('/deque') for p in M['public_control']['headers']))
        self.reject(lambda m: m['public_control']['headers'].pop('tests/origin_probes/VectorInsertionCarriers.cpp'))

    def test_whole_combined_layout60_not_only_new20(self):
        self.assertEqual(len(M['public_control']['layout_values']), 15)
        self.assertEqual(M['public_control']['layout_values'][-5:], [8, 20, 20, 16, 16])
        self.reject(lambda m: m['public_control']['layout_values'].pop(0))

    def test_four_short_private_controls_remain_unknown(self):
        self.assertEqual(len(M['retained_unknowns']), 4)
        self.reject(lambda m: m['retained_unknowns'][0]['origin'].update(origin='library'))

    def test_complete_native_context(self):
        self.context(M)

    def test_inclusive320_is_not_replaced_by319(self):
        self.reject_context(lambda m: m['bit_context'].update(index_max_inclusive=319))

    def test_signed_guard_and_divide32_cannot_be_removed(self):
        self.reject_context(lambda m: m['functions'][2]['instructions'][9].update(mnemonic='nop'))
        self.reject_context(lambda m: m['functions'][2]['instructions'][15].update(operands='eax, 4'))

    def test_clear_complement_mask_and_store_cannot_be_removed(self):
        self.reject_context(lambda m: m['functions'][2]['instructions'][26].update(mnemonic='add'))
        self.reject_context(lambda m: m['functions'][2]['instructions'][-4].update(mnemonic='nop'))

    def test_bg05b_selected_slot_has_no_invented_full_table_extent(self):
        self.reject_context(lambda m: m['background_context'].update(table_extent_claim=24))
        self.reject_context(lambda m: m['background_context'].update(slot_index=2))

    def test_bg05b_owner_write_and_complete_resource_path(self):
        self.reject_context(lambda m: m['background_context']['owner_table_writes'][0].update(instruction_bytes='00'))
        self.reject_context(lambda m: m['background_context'].update(literal_bytes=b'BG05b.dat\0'.hex()))

    def test_bg05b_initialization_and_both_wrap_values(self):
        self.reject_context(lambda m: m['background_context']['counter_initialization'][0].update(field=0x64))
        self.reject_context(lambda m: m['background_context'].update(wrap_values=[3840, 41]))

    def test_coordinate111_stays_unknown_despite_relative_fields_and_scalars(self):
        self.assertEqual(M['native_unknowns'][0]['function']['size'], '111')
        self.reject_context(lambda m: m['native_unknowns'][0]['origin'].update(origin='authored'))
        self.reject_context(lambda m: m['native_unknowns'][0]['scalars'][0].update(value=800.0))
        self.reject_context(lambda m: m['native_unknowns'][0]['writable_fields'][0].update(address='0x006714AC'))

    def test_duplicate_scoped_source_owner_rejected(self):
        with self.assertRaises(ValueError): V.SOURCE.owned_catalog([M['sections'][0]] * 2, {}, 0, [])

    def test_borrowed_definition_cannot_override_independent_owner(self):
        row = M['sections'][0]; d = next(d for d in row['source']['definitions'] if d['storage'] == 2)
        with self.assertRaises(ValueError): V.SOURCE.owned_catalog([row], {d['symbol']: 1}, 0, [])

    def test_weak_binding_requires_complete_strong_source_owner(self):
        with self.assertRaises(ValueError): V.SOURCE.owned_catalog([M['sections'][0]], {}, 0, M['weak_references'])

    def test_call_evidence_requires_full_instruction_inside_parent(self):
        raw = b'\xe8' + struct.pack('<i', 0x2000 - 0x1005)
        V.check_call(raw, 0x1000, dict(site='0x00001000', target='0x00002000'))
        for site, target in [('0x00000FFF', '0x00002000'), ('0x00001001', '0x00002000'), ('0x00001000', '0x00002001')]:
            with self.assertRaises(ValueError): V.check_call(raw, 0x1000, dict(site=site, target=target))


if __name__ == '__main__': unittest.main()
