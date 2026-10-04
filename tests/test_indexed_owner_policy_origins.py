"""Guard signed indexed copies, explicit lifetime operations and unresolved extents."""
import importlib.util
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('indexed_owner_tests',ROOT/'scripts/verify-indexed-owner-policy-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)

class IndexedOwnerPolicyOrigins(unittest.TestCase):
    def setUp(self):self.m=V.manifest()
    def reject(self,mutation):
        mutation(self.m)
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_complete_plan(self):V.verify_plan(self.m)
    def test_entire_store(self):self.reject(lambda m:m['functions'][0].update(size=83))
    def test_entire_load(self):self.reject(lambda m:m['functions'][1].update(size=84))
    def test_entire_queue_cleanup(self):self.reject(lambda m:m['functions'][2].update(size=83))
    def test_entire_archive_construction(self):self.reject(lambda m:m['functions'][3].update(size=89))
    def test_no_source_positive_from_equal_length(self):self.reject(lambda m:m['functions'][3].update(symbol='FalsePositive'))
    def test_no_source_presence(self):self.reject(lambda m:m['functions'][0]['accepted_function'].update(source_file='src/False.cpp'))
    def test_no_original_owner_layout(self):self.reject(lambda m:m['functions'][1]['accepted_function'].update(signature='FalseOwner::load()'))
    def test_no_private_abi(self):self.reject(lambda m:m['functions'][2]['accepted_function'].update(calling_convention='cdecl'))
    def test_no_exact_credit(self):self.reject(lambda m:m['functions'][3]['accepted_function'].update(match_percent='100.00'))
    def test_entire_authored_record(self):self.reject(lambda m:m['functions'][0]['accepted_authored_record'].update(size='83'))
    def test_actual_eight_byte_copy(self):self.reject(lambda m:next(r for r in m['functions'][0]['witnesses'] if r['site']=='0x00416E27').update(operands='16'))
    def test_signed_bank_selector(self):self.reject(lambda m:next(r for r in m['functions'][0]['witnesses'] if r['site']=='0x00416E35').update(mnemonic='movzx'))
    def test_actual_bank_stride(self):self.reject(lambda m:next(r for r in m['functions'][0]['witnesses'] if r['site']=='0x00416E3C').update(operands='edx, edx, 0x5fc'))
    def test_actual_category_stride(self):self.reject(lambda m:next(r for r in m['functions'][1]['witnesses'] if r['site']=='0x00416EA6').update(operands='eax, eax, 0x17f0'))
    def test_signed_record_selector(self):self.reject(lambda m:next(r for r in m['functions'][1]['witnesses'] if r['site']=='0x00416EAE').update(mnemonic='movzx'))
    def test_actual_record_stride(self):self.reject(lambda m:next(r for r in m['functions'][1]['witnesses'] if r['site']=='0x00416EB2').update(operands='edx, 3'))
    def test_actual_store_source(self):self.reject(lambda m:next(r for r in m['functions'][0]['witnesses'] if r['site']=='0x00416E2C').update(operands='eax, 0x55c'))
    def test_actual_load_destination(self):self.reject(lambda m:next(r for r in m['functions'][1]['witnesses'] if r['site']=='0x00416EC0').update(operands='ecx, 0x55c'))
    def test_clear_before_automatic_cleanup(self):self.reject(lambda m:next(r for r in m['functions'][2]['witnesses'] if r['site']=='0x004204FC').update(operands='0x421530'))
    def test_actual_queue_member_offset(self):self.reject(lambda m:next(r for r in m['functions'][2]['witnesses'] if r['site']=='0x004204F6').update(operands='ecx, 0'))
    def test_actual_explicit_archive_default(self):self.reject(lambda m:next(r for r in m['functions'][3]['witnesses'] if r['site']=='0x0041D1C1').update(operands='dword ptr [eax], 1'))
    def test_actual_postconstruction_list_clear(self):self.reject(lambda m:next(r for r in m['functions'][3]['witnesses'] if r['site']=='0x0041D1CD').update(operands='0x41d930'))
    def test_full_copy_source_control(self):self.reject(lambda m:m['policies'][0].update(size=84))
    def test_complete_implicit_control(self):self.reject(lambda m:m['policies'][3].update(implicit=False))
    def test_explicit_source_cleanup_order(self):self.reject(lambda m:m['policies'][2]['call_symbols'].reverse())
    def test_no_target_positive_for_operation_control(self):self.reject(lambda m:m['policies'][4].update(target_positive=True))
    def test_all_ordinary_sections(self):self.reject(lambda m:m['emission'].pop())
    def test_all_actual_includes(self):self.reject(lambda m:m['headers'].pop(next(iter(m['headers']))))
    def test_full_readonly_layout(self):self.reject(lambda m:m['layout'].update(size=36))
    def test_full_game_parent(self):self.reject(lambda m:m['anchors'][1].update(size=540))
    def test_complete_registered_frames(self):self.reject(lambda m:m['frames'].pop())
    def test_default_list_dependency_stays_unknown(self):self.reject(lambda m:m['pending'][0]['origin'].update(origin='library'))
    def test_no_pending_accepted_transition(self):self.reject(lambda m:m['pending'][3].update(accepted_origin='False'))
    def test_unreconciled_node_extent_stays_visible(self):self.reject(lambda m:m['pending'][3].update(size=223))
    def test_external_node_tail_not_hidden(self):self.reject(lambda m:m['pending'][3]['external_tails'].clear())
    def test_no_node_prefix_exit_credit(self):self.reject(lambda m:m['pending'][3].update(bounded_cfg=[1,0]))
    def test_protected_interface_owner_stays_unknown(self):self.reject(lambda m:next(r for r in m['snapshots'] if r['address']=='0x004170B0')['origin'].update(origin='authored'))

if __name__=='__main__':unittest.main()
