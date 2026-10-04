import importlib.util
from pathlib import Path
from types import SimpleNamespace
import unittest


ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('elementary_math', ROOT / 'scripts/verify-elementary-math-origins.py')
REVIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class ElementaryMathOriginTests(unittest.TestCase):
    def setUp(self):
        self.m = REVIEW.manifest()
        self.parent = self.m['functions'][0]
        self.label = self.m['interior_labels'][1]

    def reject(self, message):
        with self.assertRaisesRegex(ValueError, message):
            REVIEW.verify_plan(self.m)

    def entry_fixture(self):
        def instruction(address, mnemonic, destination=None, size=1):
            operands = [] if destination is None else [SimpleNamespace(type=REVIEW.X86_OP_IMM, imm=destination)]
            return SimpleNamespace(address=address, mnemonic=mnemonic, operands=operands, size=size)
        base = int(self.parent['address'], 16)
        offset = self.parent['source_definition']['offset']
        source = [instruction(offset+11, 'call', offset+29, 5),
                  instruction(offset+24, 'call', 0x1234, 5), instruction(offset+29, 'push')]
        target = [instruction(base+11, 'call', base+29, 5), instruction(base+29, 'push')]
        return source, target

    def check_entry(self, source, target):
        REVIEW.check_interior_entry(self.label, self.parent, [], target, source)

    def test_cos_requires_entire_174_byte_owner(self):
        self.parent['size'] = 20
        self.reject('complete own auxiliary extent')

    def test_sin_shared_tail_cannot_be_independent_primary(self):
        self.m['functions'][1]['size'] = 145
        self.reject('complete own auxiliary extent')

    def test_sqrt_requires_entire_186_byte_owner(self):
        self.m['functions'][2]['code_size'] = 20
        self.reject('complete own auxiliary extent')

    def test_fast_exit_cannot_gain_inventory_credit(self):
        self.m['auxiliary_bodies'][0]['ledger_size'] = 13
        self.reject('invented candidates')

    def test_c_entry_requires_offset_twenty(self):
        self.m['interior_labels'][0]['source_offset'] = 0
        self.reject('shared entries lose complete source parents')

    def test_internal_entry_requires_own_parent(self):
        self.label['parent'] = '0x006417F0'
        self.reject('shared entries lose complete source parents')

    def test_all_six_existing_entries_are_required(self):
        self.m['interior_labels'].pop()
        self.reject('shared entries lose complete source parents')

    def test_default_word_requires_complete_68_byte_carrier(self):
        self.m['state_data'][0]['size'] = 2
        self.reject('complete defining sections')

    def test_sqrt_name_requires_all_eight_source_bytes(self):
        self.m['state_data'][-1]['size'] = 5
        self.reject('complete defining sections')

    def test_fastflag_requires_complete_bss(self):
        self.m['state_data'][1]['size'] = 4
        self.reject('complete defining sections')

    def test_operation_code_is_not_guessed_from_name(self):
        self.m['elementary_protocol'][0]['operation'] = 30
        self.reject('operation/stack/control-word protocol')

    def test_intrinsic_stack_is_twelve_bytes(self):
        self.m['elementary_protocol'][0]['intrinsic_stack_bytes'] = 8
        self.reject('operation/stack/control-word protocol')

    def test_control_word_is_actual_027f(self):
        self.m['elementary_protocol'][0]['control_word'] = 0x37f
        self.reject('operation/stack/control-word protocol')

    def test_normal_and_error_operation_moves_are_required(self):
        witness = next(w for w in self.parent['instruction_witnesses'] if w['operands'] == 'edx, 0x12')
        witness['operands'] = 'edx, 0x1e'
        self.reject('normal/error paths')

    def test_range_reduction_path_cannot_be_removed(self):
        witness = next(w for w in self.parent['instruction_witnesses'] if w['mnemonic'] == 'fprem1')
        witness['mnemonic'] = 'fprem'
        self.reject('range-reduction paths')

    def test_sqrt_sign_policy_cannot_be_removed(self):
        witness = next(w for w in self.m['functions'][2]['instruction_witnesses'] if w['operands'] == 'eax, 0x80000000')
        witness['operands'] = 'eax, 0x7fffffff'
        self.reject('square-root sign')

    def test_c_entry_cannot_be_replaced_by_intrinsic_stack(self):
        witness = next(w for w in self.parent['instruction_witnesses'] if w['site'] == '0x00641754')
        witness['operands'] = 'edx, [esp]'
        self.reject('intrinsic/C/shared-entry ABI')

    def test_natural_sdk_controls_keep_fp80_size(self):
        self.m['sdk_layout']['objects'][0]['values'][2] = 12
        self.reject('operation/layout controls')

    def test_both_independent_retained_graphs_are_required(self):
        self.m['retained_controls'].pop()
        self.reject('independently retained')

    def test_actual_internal_call_and_fallthrough_are_sufficient(self):
        self.check_entry(*self.entry_fixture())

    def test_unnamed_entry_cannot_gain_fake_coff_symbol(self):
        self.label['source_definition'] = {'symbol': 'invented'}
        with self.assertRaisesRegex(ValueError, 'invented source definition'):
            self.check_entry(*self.entry_fixture())

    def test_unnamed_entry_requires_source_call_to_offset_29(self):
        source, target = self.entry_fixture()
        source[0].operands[0].imm += 1
        with self.assertRaisesRegex(ValueError, 'call/fallthrough evidence'):
            self.check_entry(source, target)

    def test_unnamed_entry_requires_actual_target_call(self):
        source, target = self.entry_fixture()
        target[0].operands[0].imm += 1
        with self.assertRaisesRegex(ValueError, 'call/fallthrough evidence'):
            self.check_entry(source, target)

    def test_c_entry_must_fall_through_to_shared_entry(self):
        source, target = self.entry_fixture()
        source[1].size = 4
        with self.assertRaisesRegex(ValueError, 'call/fallthrough evidence'):
            self.check_entry(source, target)

    def test_shared_entry_requires_real_instruction_start(self):
        source, target = self.entry_fixture()
        target.pop()
        with self.assertRaisesRegex(ValueError, 'actual full-owner instruction'):
            self.check_entry(source, target)

    def test_member_local_names_cannot_share_one_address(self):
        use = {'member_offset': 2709246, 'symbol': '_NAME_', 'target_address': '0x0066FEE0'}
        with self.assertRaisesRegex(ValueError, 'member-local data reference'):
            REVIEW.resolve_state_reference(use, {(2709246, '_NAME_'): 0x66fed0}, {})


if __name__ == '__main__':
    unittest.main()
