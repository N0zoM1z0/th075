"""Guard complete game switch data, receiver provenance and independent unknowns."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('game_switch_tests', ROOT / 'scripts/verify-game-switch-policy-origins.py')
V = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(V)
M = json.loads((ROOT / V.EVIDENCE).read_text())


class GameSwitchPolicyTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.c = V.module('switch_test_target', 'compare-coff-function.py')
        cls.authored = V.module('switch_test_cfg', 'verify-authored-origins.py')
        cls.target = cls.c.verified_target()
        cls.functions = {q['address']: q['original_function'] for q in M['functions']}
        cls.origins = {q['address']: q['original_origin'] for q in M['functions']}

    def reject(self, change):
        m = copy.deepcopy(M); change(m)
        with self.assertRaises(ValueError): V.verify_plan(m)

    def reject_context(self, change):
        m = copy.deepcopy(M); change(m)
        with self.assertRaises(ValueError): V.verify_context(m)

    def reject_tables(self, change):
        m = copy.deepcopy(M); change(m)
        with self.assertRaises(ValueError): V.verify_tables(m, self.target, self.c, self.functions, self.origins, 'original')

    def test_manifest_and_retained_evidence_pins(self):
        self.assertEqual(V.digest((ROOT / V.EVIDENCE).read_bytes()), V.MANIFEST_SHA256)
        V.verify_plan(M)
        for path, sha in M['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT / path).read_bytes()), sha, path)

    def test_three_authored_policies1191_keep_all_extents(self):
        self.assertEqual(sum(r['size'] for r in M['functions']), 1191)
        self.assertEqual({r['address']: r['size'] for r in M['functions']}, V.KEYS)
        self.assertTrue(all(r['original_function']['size'] == r['accepted_function']['size'] for r in M['functions']))
        self.reject(lambda m: m['functions'][0]['accepted_function'].update(size='231'))

    def test_no_source_private_abi_or_exact_credit(self):
        for key, value in [('source_file', 'battle.cpp'), ('calling_convention', 'cdecl'), ('signature', 'PrivateState*'), ('match_percent', '100.00')]:
            self.reject(lambda m: m['functions'][0]['accepted_function'].update({key: value}))

    def test_complete_native_code_and_guarded_cfgs(self):
        self.assertEqual([r['cfg'] for r in M['functions']], [[1, 5], [1, 26], [1, 10]])
        for r in M['functions']: V.verify_native(r, self.target, self.c, self.authored)
        r = copy.deepcopy(M['functions'][1]); r['size'] -= 1
        with self.assertRaises(ValueError): V.verify_native(r, self.target, self.c, self.authored)

    def test_tables98_with_fifteen_entries_and_selector38(self):
        self.assertEqual(sum(r['count'] for r in M['tables']), 15)
        self.assertEqual(sum(r['count'] * 4 + r['selector_count'] for r in M['tables']), 98)
        V.verify_tables(M, self.target, self.c, self.functions, self.origins, 'original')
        self.reject_tables(lambda m: m['tables'][0].update(selector_count=37))

    def test_table_or_selector_changes_fail_without_plan_digest(self):
        self.reject_tables(lambda m: m['tables'][1]['entries'].__setitem__(0, '0x0044845B'))
        self.reject_tables(lambda m: m['tables'][0].update(selector_sha256='0' * 64))

    def test_alignment0_8_15_remains_outside_code(self):
        self.assertEqual([len(bytes.fromhex(r['alignment_hex'])) for r in M['tables']], [0, 8, 15])
        self.reject_tables(lambda m: m['tables'][1].update(alignment_hex='cc' * 7))
        self.reject_tables(lambda m: m['tables'][2].update(alignment_address='0x00454CF0'))

    def test_switch_data_begins_after_the_whole_real_return(self):
        for r, table in zip(M['functions'], M['tables']):
            self.assertEqual(int(r['address'], 16) + r['size'], int(table['table'], 16))
            self.assertEqual(r['instructions'][-1]['mnemonic'], 'ret')
        self.reject_tables(lambda m: m['tables'][0].update(table='0x00444735'))

    def test_independent_next_code_owners_are_full_contexts(self):
        self.assertEqual([r['next_head'] for r in M['tables']], ['0x00444770', '0x00448710', '0x00454D00'])
        self.reject_tables(lambda m: m['anchors'].pop())

    def test_inventory_cannot_hide_an_interior(self):
        self.assertEqual([len(r['inventory_entries']) for r in M['tables']], [1, 1, 1])
        self.reject_tables(lambda m: m['tables'][0]['inventory_entries'].clear())

    def test_ten_complete_contexts10779_and_four_receiver_sequences(self):
        self.assertEqual((len(M['anchors']), sum(r['size'] for r in M['anchors'])), (10, 10779))
        self.assertEqual(sum(len(r['call_sequences']) for r in M['anchors']), 4)
        for r in M['anchors']: V.verify_native(r, self.target, self.c, self.authored)
        self.reject(lambda m: m['anchors'][0]['instructions'].pop())

    def test_native_game_composition(self):
        V.verify_context(M)

    def test_mode5_guard_and_original_receiver_required(self):
        row = next(i for i, r in enumerate(M['anchors']) if r['address'] == '0x004461D0')
        self.reject_context(lambda m: m['anchors'][row]['call_sequences'][0]['instructions'][-4].update(operands='eax, 4'))
        self.reject_context(lambda m: m['anchors'][row]['call_sequences'][0]['instructions'][-2].update(operands='ecx, dword ptr [ebp + 8]'))

    def test_three_argument_reaction_protocol_ret12(self):
        self.reject_context(lambda m: m['anchors'][0]['call_sequences'][0]['instructions'][-7].update(operands='edx'))
        self.reject_context(lambda m: m['functions'][0]['instructions'][-1].update(operands='8'))

    def test_reaction_scale1_25_and_actual_state_bounds(self):
        self.assertEqual([r['value'] for r in M['data']], [1.25, 620.0, 660.0])
        self.reject_context(lambda m: m['context'].update(reaction_scale=0.5))
        self.reject_context(lambda m: m['context'].update(reaction_base=49))

    def test_six_option_fields_and_nine_row_cursor(self):
        self.reject_context(lambda m: m['context']['option_fields'].reverse())
        self.reject_context(lambda m: m['context'].update(cursor_modulus=8))
        self.reject_context(lambda m: m['context']['option_moduli'].__setitem__(1, 9))

    def test_actual_indirect_virtual_slot_is_not_a_full_vtable_claim(self):
        self.assertEqual(M['context']['virtual_slot'], 0x2c)
        self.reject_context(lambda m: m['functions'][2]['calls'][0].update(target='dword ptr [edx + 0x30]'))

    def test_direction_option_fields_and_x87_bounds(self):
        self.reject_context(lambda m: m['context'].update(position_bounds=[600.0, 660.0]))
        self.reject_context(lambda m: m['context'].update(position_option_field=0x530))

    def test_whole_abs_wrapper17_and_worker11_remain_unknown(self):
        self.assertEqual([r['size'] for r in M['retained_unknowns']], [17, 11])
        for r in M['retained_unknowns']: V.verify_native(r, self.target, self.c, self.authored)
        self.reject(lambda m: m['retained_unknowns'][0]['origin'].update(origin='library'))
        self.reject(lambda m: m['retained_unknowns'][1]['prior_record'].update(decision='authored'))

    def test_dedicated_switch_registries_do_not_change_old_authored_records(self):
        self.assertEqual(V.rows(M['authored_path']), [r['record'] for r in M['functions']])
        self.assertEqual(len(V.rows(M['switch_path'])), 1)
        self.assertEqual(len(V.rows(M['direct_switch_path'])), 2)

    def test_independent_callee_composition_cannot_be_reordered(self):
        self.reject_context(lambda m: m['functions'][0]['calls'].reverse())
        self.reject_context(lambda m: m['functions'][1]['calls'][0].update(target='0x641fb8'))

    def test_full_body_instruction_decoder_rejects_cropped_code(self):
        self.assertEqual(V.native_instructions(b'\xc3', 0x1000), [dict(offset=0, size=1, mnemonic='ret', operands='')])
        with self.assertRaises(ValueError): V.native_instructions(b'\xe8\x00', 0x1000)


if __name__ == '__main__': unittest.main()
