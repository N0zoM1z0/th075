"""Reject incomplete jump/SEH extents and invented absolute-zero provenance."""
import hashlib
import importlib.util
from pathlib import Path
import struct
import unittest

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('jump_unwind', ROOT / 'scripts/verify-jump-unwind-origins.py')
REVIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)
COMPARISON = REVIEW.module('jump_test_comparison', 'compare-coff-function.py')
COFF = REVIEW.module('jump_test_coff', 'coff_data.py')


def symbol_object(section, value=0, storage=2):
    # A valid synthetic one-section COFF with a single external/ABS symbol.
    name = b'__except_list\0'
    header = struct.pack('<HHIIIHH', 0x14c, 1, 0, 60, 1, 0, 0)
    section_header = struct.pack('<8sIIIIIIHHI', b'.data\0\0\0', 0, 0, 0, 0, 0, 0, 0, 0, 0xC0000040)
    symbol = struct.pack('<8sIhHBB', struct.pack('<II',0,4), value, section, 0, storage, 0)
    return header+section_header+symbol+struct.pack('<I',4+len(name))+name


class JumpUnwindOriginTests(unittest.TestCase):
    def setUp(self):
        self.m = REVIEW.manifest()
        self.graph = {r['address']:r for r in self.m['functions']+self.m['anchors']}

    def reject(self, message):
        with self.assertRaisesRegex(ValueError,message):
            REVIEW.verify_plan(self.m)

    def reject_protocol(self,message):
        with self.assertRaisesRegex(ValueError,message):
            REVIEW.check_unwind_protocol(self.m,self.graph)

    def remove_witness(self,key,mnemonic,operands):
        row = self.graph[key]
        row['instruction_witnesses'] = [w for w in row['instruction_witnesses'] if (w['mnemonic'],w['operands'])!=(mnemonic,operands)]

    def absolute_fixture(self, segment=b'\x64', value=0, storage=2):
        definition = symbol_object(-1,value,storage)
        reference = symbol_object(0)
        row = self.m['absolute_symbols'][0]
        row['member'] = 'synthetic-exsup.obj'
        row['member_sha256'] = hashlib.sha256(definition).hexdigest()
        members = {1210238:(row['member'],definition),1227402:('synthetic-longjmp.obj',reference)}
        decoder = Cs(CS_ARCH_X86,CS_MODE_32)
        decoder.detail = True
        decoded = {'0x00643604':list(decoder.disasm(segment+b'\x3b\x35\0\0\0\0',0x0064360D))}
        return members,decoded

    def check_absolute(self,members,decoded):
        REVIEW.check_absolute_symbols(self.m,members,COMPARISON,COFF,decoded)

    def test_complete_plan_passes(self):
        REVIEW.verify_plan(self.m)

    def test_longjmp_requires_final_own_aux_ret_byte(self):
        self.graph['0x00643604']['size'] = 120
        self.reject('complete own AUX')

    def test_longjmp_cannot_silently_replace_original_extent(self):
        self.graph['0x00643604']['ledger_size'] = 121
        self.reject('complete own AUX')

    def test_read_probe_cannot_omit_exception_filter_region(self):
        self.graph['0x0064DC10']['code_regions'] = [{'offset':0,'size':29},{'offset':54,'size':12}]
        self.reject('complete code partition')

    def test_full_scope_cannot_be_a_handler_pointer_prefix(self):
        self.m['state_data'][0]['size'] = 8
        self.reject('complete defining data')

    def test_scope_filter_must_start_at_real_source_entry(self):
        self.m['scope_tables'][0]['records'][0]['filter'] = '0x0064DC30'
        self.reject_protocol('scope filter/handler entry')

    def test_scope_handler_keeps_stack_restore_before_zero_result(self):
        self.m['scope_tables'][0]['callbacks'][1]['code_entry']['source_offset'] = 52
        self.reject_protocol('scope filter/handler entry')

    def test_scope_filter_cannot_be_changed_to_finally(self):
        self.m['scope_tables'][0]['records'][0]['filter'] = None
        self.reject_protocol('scope filter/handler entry')

    def test_scope_enclosing_level_is_minus_one(self):
        self.m['scope_tables'][0]['records'][0]['enclosing'] = 0
        self.reject_protocol('scope filter/handler entry')

    def test_scope_cannot_gain_a_new_parent(self):
        self.m['scope_tables'][0]['owner'] = '0x00643604'
        self.reject_protocol('scope filter/handler entry')

    def test_filter_handles_only_access_violation(self):
        self.remove_witness('0x0064DC10','cmp','eax, 0xc0000005')
        self.reject_protocol('load/success/filter/handler')

    def test_filter_return_keeps_zero_callee_cleanup(self):
        self.graph['0x0064DC10']['body_facts']['returns'][0]['cleanup'] = 4
        self.reject_protocol('load/success/filter/handler')

    def test_primary_read_probe_keeps_ret_four(self):
        self.graph['0x0064DC10']['body_facts']['returns'][1]['cleanup'] = 0
        self.reject_protocol('load/success/filter/handler')

    def test_probe_success_requires_actual_load(self):
        self.remove_witness('0x0064DC10','mov','eax, dword ptr [eax]')
        self.reject_protocol('load/success/filter/handler')

    def test_probe_success_is_one(self):
        self.remove_witness('0x0064DC10','inc','eax')
        self.reject_protocol('load/success/filter/handler')

    def test_exception_handler_restores_saved_stack(self):
        self.remove_witness('0x0064DC10','mov','esp, dword ptr [ebp - 0x18]')
        self.reject_protocol('load/success/filter/handler')

    def test_jump_restores_esp_before_saved_eip_transfer(self):
        self.remove_witness('0x00643604','mov','esp, dword ptr [edx + 0x10]')
        self.reject_protocol('saved-context/register/normalization')

    def test_jump_cookie_is_actual_vc20_value(self):
        self.remove_witness('0x00643604','cmp','eax, 0x56433230')
        self.reject_protocol('saved-context/register/normalization')

    def test_zero_result_normalization_requires_adc(self):
        self.remove_witness('0x00643604','adc','eax, 0')
        self.reject_protocol('saved-context/register/normalization')

    def test_saved_callback_identity_remains_opaque(self):
        self.m['runtime_dispatch'][0]['calls'][0]['operand'] = '0x00645460'
        self.reject_protocol('opaque saved callback')

    def test_saved_return_jump_is_preserved(self):
        self.m['runtime_dispatch'][0]['jumps'].clear()
        self.reject_protocol('saved-return dispatch')

    def test_fs_zero_field_is_not_a_pe_state_object(self):
        self.graph['0x00643604']['relocation_bindings'][0]['target_kind'] = 'state'
        self.reject_protocol('actual external ABS')

    def test_actual_absolute_definition_section_is_minus_one(self):
        self.graph['0x00643604']['relocation_bindings'][0]['absolute_definition']['source_definition']['section'] = 0
        self.reject_protocol('actual external ABS')

    def test_actual_absolute_definition_member_cannot_be_guessed(self):
        self.graph['0x00643604']['relocation_bindings'][0]['absolute_definition']['member_offset'] = 1227402
        self.reject_protocol('actual external ABS')

    def test_synthetic_actual_abs_definition_and_fs_instruction_pass(self):
        members,decoded = self.absolute_fixture()
        self.check_absolute(members,decoded)

    def test_external_undefined_symbol_is_not_absolute_proof(self):
        members,decoded = self.absolute_fixture()
        members[1210238] = ('synthetic-exsup.obj',symbol_object(0))
        self.m['absolute_symbols'][0]['member_sha256'] = hashlib.sha256(members[1210238][1]).hexdigest()
        with self.assertRaisesRegex(ValueError,'unique actual whole-archive'):
            self.check_absolute(members,decoded)

    def test_static_abs_symbol_is_not_external_binding(self):
        members,decoded = self.absolute_fixture(storage=3)
        with self.assertRaisesRegex(ValueError,'unique actual whole-archive'):
            self.check_absolute(members,decoded)

    def test_duplicate_abs_definitions_are_rejected(self):
        members,decoded = self.absolute_fixture()
        members[999999] = members[1210238]
        with self.assertRaisesRegex(ValueError,'unique actual whole-archive'):
            self.check_absolute(members,decoded)

    def test_changed_abs_value_is_rejected_from_actual_symbol(self):
        members,decoded = self.absolute_fixture(value=4)
        with self.assertRaisesRegex(ValueError,'unique actual whole-archive'):
            self.check_absolute(members,decoded)

    def test_source_external_referring_record_is_required(self):
        members,decoded = self.absolute_fixture()
        members[1227402] = ('synthetic-longjmp.obj',symbol_object(-1))
        with self.assertRaisesRegex(ValueError,'unique actual whole-archive'):
            self.check_absolute(members,decoded)

    def test_gs_zero_does_not_prove_fs_exception_list(self):
        members,decoded = self.absolute_fixture(segment=b'\x65')
        with self.assertRaisesRegex(ValueError,'FS segment/displacement'):
            self.check_absolute(members,decoded)

    def test_abs_use_must_point_at_displacement_field(self):
        members,decoded = self.absolute_fixture()
        self.m['absolute_symbols'][0]['uses'][0]['instruction_offset'] = 8
        with self.assertRaisesRegex(ValueError,'FS segment/displacement'):
            self.check_absolute(members,decoded)

    def test_retained_complete_unwind_dependency_replay_is_required(self):
        self.m['retained_controls'].clear()
        self.reject('retained independent R141')

    def test_actual_sdk_jump_buffer_is_complete_64_bytes(self):
        self.m['sdk_layout']['objects'][0]['values'][3] = 32
        self.reject('actual SDK')

    def test_natural_scope_data_cannot_drop_handler_field(self):
        self.m['probe_generated_data'][0]['source_section']['relocations'].pop()
        self.reject('complete probe_generated_data')

    def test_private_saved_callback_abi_is_not_invented(self):
        self.m['unwind_protocol']['runtime_unknowns'] = 'saved callback fully identified'
        self.reject('private ABI')


if __name__ == '__main__':
    unittest.main()
