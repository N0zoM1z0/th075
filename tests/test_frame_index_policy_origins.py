"""Guard full public indexing provenance and native game composition successors."""
import copy
import importlib.util
import json
from pathlib import Path
import struct
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('frame_index_tests', ROOT / 'scripts/verify-frame-index-policy-origins.py')
V = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(V)
M = json.loads((ROOT / V.EVIDENCE).read_text())


class FrameIndexPolicyTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.c = V.module('frame_test_target', 'compare-coff-function.py')
        cls.target = cls.c.verified_target()
        cls.flow = V.module('frame_test_flow', 'sdk_image_carriers.py')
        cls.functions = {r['address']: r['original_function'] for r in M['functions']}
        cls.origins = {r['address']: r['original_origin'] for r in M['functions']}

    def reject(self, change):
        m = copy.deepcopy(M); change(m)
        with self.assertRaises(ValueError): V.verify_plan(m)

    def reject_native(self, change):
        m = copy.deepcopy(M); change(m)
        with self.assertRaises(ValueError): V.verify_native_context(m, self.target, self.c, self.flow)

    def test_complete_frozen_plan(self):
        self.assertEqual(V.digest((ROOT / V.EVIDENCE).read_bytes()), V.MANIFEST_SHA256)
        V.verify_plan(M)

    def test_all_retained_source_and_evidence_pins(self):
        for path, sha in M['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT / path).read_bytes()), sha, path)

    def test_ten_transitions457_keep_whole_extents(self):
        self.assertEqual(len(M['functions']), 10)
        self.assertEqual(sum(r['size'] for r in M['functions']), 457)
        self.assertEqual({r['address']: r['size'] for r in M['functions']}, V.WHOLE)
        self.reject(lambda m: m['functions'].pop())

    def test_eight_library295_and_two_authored162(self):
        self.assertEqual(sum(r['size'] for r in M['functions'] if r['accepted_origin']['origin'] == 'library'), 295)
        self.assertEqual(sum(r['size'] for r in M['functions'] if r['accepted_origin']['origin'] == 'authored'), 162)
        self.reject(lambda m: m['functions'][0]['accepted_origin'].update(origin='compiler'))

    def test_no_private_abi_source_or_exact_credit(self):
        for key, value in [('source_file', 'game.cpp'), ('signature', 'PrivateFrame*'),
                           ('calling_convention', 'cdecl'), ('match_percent', '100.00')]:
            self.reject(lambda m: m['functions'][0]['accepted_function'].update({key: value}))

    def test_two_complete_scoped_graphs489_each(self):
        rows = [[r for r in M['sections'] if r['group'] == g['id']] for g in M['groups']]
        self.assertEqual([len(r) for r in rows], [13, 13])
        self.assertEqual([sum(r['size'] for r in rows) for rows in rows], [489, 489])
        self.assertEqual([g['width'] for g in M['groups']], [16, 4])
        self.reject(lambda m: m['groups'].pop())

    def test_all46_actual_fields_and_bindings(self):
        self.assertEqual(sum(len(r['fields']) for r in M['sections']), 46)
        self.reject(lambda m: m['sections'][0]['fields'].pop())
        self.reject(lambda m: m['sections'][0]['bindings'].pop())

    def test_actual_coff_aux_and_debug_line_provenance(self):
        self.reject(lambda m: m['sections'][0]['source']['aux_records'][1].update(index=0))
        self.reject(lambda m: m['sections'][0]['source']['coff_line_table'].pop())

    def test_all22_normal_exception_cfgs_and_complete_data(self):
        self.assertEqual(sum(r['kind'] == 'code' for r in M['sections']), 22)
        self.reject(lambda m: m['sections'][0]['roots'].pop())
        self.reject(lambda m: next(r for r in m['sections'] if r['kind'] == 'data').update(size=1))

    def test_whole_source_inventory_cannot_hide_entry(self):
        self.reject(lambda m: m['sections'][0]['inventory_entries'].pop())

    def test_at70_is_complete_unsigned_guard_and_ret4(self):
        rows = [r for r in M['functions'] if r['address'] in ['0x005FACD0', '0x005FAD20']]
        self.assertEqual([r['size'] for r in rows], [70, 70])
        self.assertTrue(all(any(i['mnemonic'] == 'ja' for i in r['instructions']) for r in rows))
        self.assertTrue(all(r['instructions'][-1]['operands'] == '4' for r in rows))
        self.reject(lambda m: m['functions'][0]['instructions'].pop())

    def test_original_Xran_owner_not_provisional_Xlen_name(self):
        rows = [r for r in M['sections'] if r['base'] in ['0x005FAD70', '0x005FADD0']]
        self.assertEqual([r['size'] for r in rows], [90, 90])
        self.assertTrue(all(r['symbol'].startswith('?_Xran@') for r in rows))
        self.reject(lambda m: next(r for r in m['sections'] if r['base'] == '0x005FAD70').update(size=89))

    def test_full_out_of_range37_and_throw_metadata16_own_sources(self):
        self.assertEqual([r['source']['size'] for r in M['additional_shared']], [37, 16])
        self.assertEqual([len(r['fields']) for r in M['additional_shared']], [2, 2])
        self.assertEqual(M['additional_shared'][0]['prior_record']['origin']['evidence_id'], 'R096')
        self.reject(lambda m: m['additional_shared'][0]['fields'].pop())

    def test_throw_owner_cannot_be_borrowed_from_observed_destination(self):
        self.reject(lambda m: m['additional_shared'][1]['owner']['record'].update(address='0x00000000'))

    def test_whole_wrong_stride32_controls(self):
        self.assertEqual([r['size'] for r in M['alternatives'][:2]], [32, 32])
        self.assertFalse(any(r['fields'] for r in M['alternatives'][:2]))
        self.reject(lambda m: m['alternatives'][0]['instructions'].pop())

    def test_whole_const70_routes_use_const_dereference(self):
        self.assertEqual([r['size'] for r in M['alternatives'][2:]], [70, 70])
        self.assertTrue(all(r['fields'][-1]['symbol'].startswith('??Dconst_iterator@') for r in M['alternatives'][2:]))
        self.reject(lambda m: m['alternatives'][2]['fields'].pop())

    def test_full130_ordinary_emissions5568(self):
        self.assertEqual(len(M['public_control']['emission']), 130)
        self.assertEqual(sum(r['size'] for r in M['public_control']['emission']), 5568)
        self.reject(lambda m: m['public_control']['emission'].pop())

    def test_full28_original_cpp_and_sdk_includes(self):
        self.assertEqual(len(M['public_control']['headers']), 28)
        self.assertIn('tests/origin_probes/VectorAtPolicyProbe.cpp', M['public_control']['headers'])
        self.reject(lambda m: m['public_control']['headers'].pop('tests/origin_probes/VectorAtPolicyProbe.cpp'))

    def test_full_observation56_not_only_new20(self):
        self.assertEqual(len(M['public_control']['layout_values']), 14)
        self.assertEqual(M['public_control']['layout_values'][-5:], [4, 16, 16, 16, 4])
        self.reject(lambda m: m['public_control']['layout_values'].pop(0))

    def test_four_whole_parents62405_and_nine_actual_calls(self):
        self.assertEqual(sum(r['size'] for r in M['parents']), 62405)
        self.assertEqual(sum(len(r['calls']) for r in M['parents']), 9)
        self.reject(lambda m: m['parents'][0]['instructions'].pop())

    def test_full_large_action_owner60999_and16837_instructions(self):
        r = next(r for r in M['parents'] if r['address'] == '0x0045DD70')
        self.assertEqual((r['size'], r['instruction_count'], r['cfg']), (60999, 16837, [1, 1690]))
        self.assertIsNone(r['instructions'])
        self.assertEqual(len(r['call_sequences']), 7)
        self.reject(lambda m: m['parents'][1].update(instructions_sha256='0' * 64))

    def test_complete_native_context(self):
        V.verify_native_context(M, self.target, self.c, self.flow)

    def test_frame_receiver_is_derived_from_actual_resource_offset(self):
        self.reject_native(lambda m: m['game_context'].update(frame_resource_container_offset=0x74))
        self.reject_native(lambda m: m['game_context'].update(frame_container_field=0x78))

    def test_nested_indices_and_output_fields_cannot_change(self):
        self.reject_native(lambda m: m['game_context'].update(index_fields=[0x62, 0x60]))
        self.reject_native(lambda m: m['game_context'].update(output_fields=[8, 0x70, 0x72]))

    def test_nested_stack_protocol_not_two_argument_member(self):
        row = next(i for i, r in enumerate(M['functions']) if r['address'] == '0x005FAC60')
        self.reject_native(lambda m: m['functions'][row]['instructions'][9].update(operands='ecx'))
        row = next(i for i, r in enumerate(M['functions']) if r['address'] == '0x005FAD20')
        self.reject_native(lambda m: m['functions'][row]['instructions'][-1].update(operands='8'))

    def test_complete_selected_frame_then_size_composition(self):
        row = next(i for i, r in enumerate(M['functions']) if r['address'] == '0x005FAC60')
        self.reject_native(lambda m: m['functions'][row]['calls'].reverse())

    def test_game_command_owner_and_selection_fields(self):
        self.reject_native(lambda m: m['game_context'].update(command_owner_field=0x47c))
        self.reject_native(lambda m: m['game_context'].update(command_selection_field=0x480))

    def test_actual_action_arguments_and_receiver_are_required(self):
        self.reject_native(lambda m: m['parents'][1]['call_sequences'][0]['instructions'][0].update(operands='0'))
        self.reject_native(lambda m: m['parents'][1]['call_sequences'][0]['instructions'][3].update(operands='ecx, eax'))

    def test_command_setters_remain_unknown(self):
        self.assertEqual([r['function']['size'] for r in M['retained_unknowns']], ['22', '22'])
        self.assertTrue(all(r['origin']['origin'] == 'unknown' for r in M['retained_unknowns']))
        self.reject(lambda m: m['retained_unknowns'][0]['origin'].update(origin='authored'))

    def test_ten_literal_historical_records_and_explicit_successors(self):
        self.assertEqual(len(M['historical_snapshots']), 10)
        V.verify_history(M, self.target, self.c, self.functions, self.origins, 'original')
        accepted_f = {r['address']: r['accepted_function'] for r in M['functions']}
        accepted_o = {r['address']: r['accepted_origin'] for r in M['functions']}
        V.verify_history(M, self.target, self.c, accepted_f, accepted_o, 'accepted')
        self.reject(lambda m: m['historical_snapshots'].pop())

    def test_old_R162_annotations_are_owned_by_original_manifest(self):
        r = [r for r in M['historical_snapshots'] if r['path'] == 'config/vector-producer-origin-evidence.json']
        self.assertEqual({r['record']['address'] for r in r}, {'0x005F8490', '0x005F95B0'})
        self.reject(lambda m: m['historical_snapshots'][-1]['record']['function'].update(signature='Private*'))

    def test_history_cannot_be_rewritten_or_rebound(self):
        m = copy.deepcopy(M); m['historical_snapshots'][0]['record']['function']['size'] = '15'
        with self.assertRaises(ValueError): V.verify_history(m, self.target, self.c, self.functions, self.origins, 'original')
        m = copy.deepcopy(M)
        next(r for r in m['functions'] if r['address'] == '0x005F8490')['original_function']['source_file'] = 'game.cpp'
        with self.assertRaises(ValueError): V.verify_history(m, self.target, self.c, self.functions, self.origins, 'original')

    def test_retained_source_definition_not_field_observation(self):
        self.reject(lambda m: m['prior']['shared'][0]['owner']['record'].update(address='0x00000000'))

    def test_original_absolute_crt_owner(self):
        self.reject(lambda m: m['prior']['absolute']['__except_list']['definition'].update(section=1))

    def test_duplicate_scoped_source_owner_is_rejected(self):
        with self.assertRaises(ValueError): V.SOURCE.owned_catalog([M['sections'][0]] * 2, {}, 0, [])

    def test_borrowed_definition_cannot_override_full_owner(self):
        row = M['sections'][0]; d = next(d for d in row['source']['definitions'] if d['storage'] == 2)
        with self.assertRaises(ValueError): V.SOURCE.owned_catalog([row], {d['symbol']: 1}, 0, [])

    def test_actual_call_must_be_inside_complete_parent(self):
        raw = b'\xe8' + struct.pack('<i', 0x2000 - 0x1005)
        V.check_call(raw, 0x1000, dict(site='0x00001000', target='0x00002000'))
        for site, target in [('0x00000FFF', '0x00002000'), ('0x00001001', '0x00002000'), ('0x00001000', '0x00002001')]:
            with self.assertRaises(ValueError): V.check_call(raw, 0x1000, dict(site=site, target=target))


if __name__ == '__main__': unittest.main()
