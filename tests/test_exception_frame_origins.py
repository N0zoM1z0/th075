import copy
import importlib.util
from pathlib import Path
import struct
from types import SimpleNamespace
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('exception_frame', ROOT / 'scripts/verify-exception-frame-origins.py')
REVIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class ExceptionFrameOriginTests(unittest.TestCase):
    def setUp(self):
        self.m = REVIEW.manifest()
        self.graph = {r['address']:r for r in self.m['functions'] + self.m['auxiliary_bodies'] + self.m['anchors']}

    def reject(self, message):
        with self.assertRaisesRegex(ValueError,message):
            REVIEW.verify_plan(self.m)

    def remove_witness(self, owner, mnemonic, operands):
        row = self.graph[owner]
        row['instruction_witnesses'] = [w for w in row['instruction_witnesses']
                                        if (w['mnemonic'],w['operands']) != (mnemonic,operands)]

    def scope_fixture(self):
        scope = copy.deepcopy(self.m['scope_tables'][0])
        data = copy.deepcopy(next(r for r in self.m['state_data'] if r['symbol']==scope['symbol']))
        raw = bytearray()
        for r in scope['records']:
            raw.extend(struct.pack('<iII',r['enclosing'],int(r['filter'],16) if r['filter'] else 0,int(r['handler'],16)))
        decoded = {scope['owner']:[SimpleNamespace(address=int(b['target_address'],16)) for b in scope['callbacks']]}
        return scope,data,raw,decoded

    def test_complete_closed_plan_passes(self):
        REVIEW.verify_plan(self.m)

    def test_unwind_cannot_stop_before_finally(self):
        self.graph['0x006455D6']['size'] = 173
        self.reject('complete own AUX')

    def test_destructor_cannot_omit_filter_handler(self):
        self.graph['0x006456D4']['size'] = 52
        self.reject('complete own AUX')

    def test_catch_cannot_stop_at_first_return(self):
        self.graph['0x0064592D']['size'] = 332
        self.reject('complete own AUX')

    def test_build_catch_cannot_omit_termination_scope(self):
        self.graph['0x00645AF1']['size'] = 368
        self.reject('complete own AUX')

    def test_jump_continuation_requires_real_epilogue(self):
        self.graph['0x00640721']['size'] = 43
        self.reject('complete own AUX')

    def test_root_callee_requires_its_own_complete_owner(self):
        self.m['functions'].pop()
        self.reject('cohort differs')

    def test_noninventory_filter_cannot_gain_candidate_credit(self):
        self.m['auxiliary_bodies'][0]['decision'] = 'library'
        self.reject('invented inventory credit')

    def test_own_extent_cannot_be_a_whole_section_substitute(self):
        self.graph['0x00645C6D']['extent_basis'] = 'whole-defining-code-section'
        self.reject('complete own AUX')

    def test_no_invented_private_type_source(self):
        self.m['vendor_sources']['crt/src/ehdata.h'] = 'invented'
        self.reject('actual SDK or available source')

    def test_thread_frame_chain_offset_is_136(self):
        self.m['sdk_layout']['objects'][0]['values'][18] = 128
        self.reject('actual SDK')

    def test_seh_filter_result_is_not_handler_disposition(self):
        self.m['sdk_layout']['objects'][0]['values'][28] = 0
        self.reject('actual SDK')

    def test_register_build_catch_cannot_be_four_stack_cdecl(self):
        self.m['register_contracts']['0x00645AF1']['incoming'] = ['four stack arguments']
        self.reject('private ABI')

    def test_private_layout_and_callback_unknowns_are_retained(self):
        self.m['frame_protocol']['runtime_unknowns'] = 'complete private records and all callbacks known'
        self.reject('private ABI')

    def test_rtlunwind_stays_compiler_owned(self):
        self.m['retained_thunks'][0]['origin_evidence'] = 'R141'
        self.reject('compiler thunk ownership')

    def test_source_rtlunwind_requires_actual_iat_slot(self):
        b = next(b for b in self.graph['0x00640766']['relocation_bindings'] if b['target_kind']=='import-thunk')
        b['iat_slot'] = '0x00657184'
        self.reject('compiler thunk/IAT identity')

    def test_source_rtlunwind_cannot_gain_library_entry(self):
        b = next(b for b in self.graph['0x00640766']['relocation_bindings'] if b['target_kind']=='import-thunk')
        b['code_entry'] = {'owner':'0x00654B54'}
        self.reject('compiler thunk/IAT identity')

    def test_retained_thread_heap_type_error_graph_is_required(self):
        self.m['retained_controls'] = []
        self.reject('retained independent R140')

    def test_member_trampoline_cannot_gain_return(self):
        self.graph['0x00640751']['body_facts']['returns'] = [dict(site='0x00640756',cleanup=0)]
        self.reject('tail transfer or gains fake return')

    def test_member_trampoline_requires_this_in_ecx(self):
        self.remove_witness('0x00640758','pop','ecx')
        self.reject('tail transfer')

    def test_callsettingframe_pops_three_arguments(self):
        self.graph['0x00646500']['body_facts']['returns'][0]['cleanup'] = 0
        self.reject('return cleanup')

    def test_nested_unwind_pops_two_arguments(self):
        self.graph['0x00640766']['body_facts']['returns'][0]['cleanup'] = 0
        self.reject('return cleanup')

    def test_translator_requires_both_cleanup_pops(self):
        self.graph['0x00640843']['instruction_witnesses'] = [w for w in self.graph['0x00640843']['instruction_witnesses'] if w['site']!='0x006408D9']
        self.reject('two-pop caller cleanup')

    def test_build_catch_requires_register_ecx_input(self):
        self.remove_witness('0x00645AF1','mov','esi, ecx')
        self.reject('register/stack ABI')

    def test_adjust_pointer_requires_eax_base(self):
        self.remove_witness('0x00645719','add','eax, esi')
        self.reject('register/stack ABI')

    def test_private_unwind_filter_requires_eax_storage(self):
        self.remove_witness('0x006455B8','mov','eax, dword ptr [eax]')
        self.reject('register/stack ABI')

    def test_member_tail_dispatch_cannot_be_dropped(self):
        self.graph['0x0064075F']['indirect_jumps'] = []
        self.reject('runtime dispatch inventory')

    def test_typed_entry_cannot_land_in_memmove_table(self):
        row = self.graph['0x00641260']; table = row['embedded_tables'][0]
        b = copy.deepcopy(next(b for b in self.graph['0x00645AF1']['relocation_bindings'] if b['symbol']=='_memmove'))
        e = b['code_entry']; e['source_offset'] = table['offset']; e['source_definition']['offset'] = table['offset']
        b['target_address'] = f"0x{int(row['address'],16)+table['offset']:08X}"
        with self.assertRaisesRegex(ValueError,'defining source owner/entry'):
            REVIEW.check_code_entry(b,self.graph)

    def test_table_partition_requires_all_six_memmove_tables(self):
        row = copy.deepcopy(self.graph['0x00641260']);row['embedded_tables'].pop()
        with self.assertRaisesRegex(ValueError,'six complete inline tables'):
            REVIEW.check_partition(row,b'',[],self.graph)

    def test_complete_code_catalog_rejects_invented_same_address_label(self):
        b = copy.deepcopy(next(b for b in self.graph['0x006455D6']['relocation_bindings'] if 'code_entry' in b))
        REVIEW.check_catalog_entry(b,self.m['code_definitions'])
        b['code_entry']['source_definition']['symbol'] = 'invented-private-label'
        with self.assertRaisesRegex(ValueError,'actual COFF definitions'):
            REVIEW.check_catalog_entry(b,self.m['code_definitions'])

    def test_scope_complete_valid_records_pass(self):
        scope,data,raw,decoded = self.scope_fixture()
        REVIEW.check_scope_records(scope,data,raw,self.graph,decoded)

    def test_scope_record_cannot_enclose_itself(self):
        scope,data,raw,decoded = self.scope_fixture();struct.pack_into('<i',raw,0,0)
        scope['records'][0]['enclosing'] = 0
        with self.assertRaisesRegex(ValueError,'enclosing/filter/handler'):
            REVIEW.check_scope_records(scope,data,raw,self.graph,decoded)

    def test_scope_handler_cannot_be_null(self):
        scope,data,raw,decoded = self.scope_fixture();struct.pack_into('<I',raw,8,0)
        scope['records'][0]['handler'] = '0x00000000'
        with self.assertRaisesRegex(ValueError,'enclosing/filter/handler'):
            REVIEW.check_scope_records(scope,data,raw,self.graph,decoded)

    def test_scope_requires_actual_handler_instruction_start(self):
        scope,data,raw,decoded = self.scope_fixture();decoded[scope['owner']].pop(0)
        with self.assertRaisesRegex(ValueError,'instruction start'):
            REVIEW.check_scope_records(scope,data,raw,self.graph,decoded)

    def test_scope_callback_cannot_belong_to_another_owner(self):
        scope,data,raw,decoded = self.scope_fixture()
        scope['callbacks'][0]['code_entry']['owner'] = '0x006456D4'
        data['relocations'][0]['code_entry']['owner'] = '0x006456D4'
        with self.assertRaisesRegex(ValueError,'complete source owner'):
            REVIEW.check_scope_records(scope,data,raw,self.graph,decoded)

    def test_scope_prefix_cannot_replace_complete_two_records(self):
        scope,data,raw,decoded = self.scope_fixture();scope['records'].pop()
        with self.assertRaisesRegex(ValueError,'whole defining records'):
            REVIEW.check_scope_records(scope,data,raw,self.graph,decoded)

    def test_existing_cleanup_label_is_six_bytes_after_scope_entry(self):
        label = copy.deepcopy(self.m['interior_labels'][0]);parent = self.graph[label['parent']]
        target = [SimpleNamespace(address=int(parent['address'],16)+x) for x in (label['source_offset'],label['scope_entry_offset'])]
        source = [SimpleNamespace(address=parent['source_definition']['offset']+label['source_offset'])]
        REVIEW.check_interior_entry(label,parent,[label['source_definition']],target,source)
        label['scope_entry_offset'] += 1
        with self.assertRaisesRegex(ValueError,'six-byte scope prologue'):
            REVIEW.check_interior_entry(label,parent,[label['source_definition']],target,source)

    def test_no_aux_model_handler_is_whole_section(self):
        self.m['probe_generated_code'][0]['size'] = 5
        self.reject('probe_generated_code')

    def test_model_catch_metadata_cannot_be_only_funcinfo_prefix(self):
        self.m['probe_generated_data'][-1]['source_section']['size'] = 28
        self.reject('probe_generated_data')

    def test_natural_translator_requires_real_header_abi(self):
        self.m['call_controls'][0]['size'] = 20
        self.reject('call_controls')


if __name__ == '__main__':
    unittest.main()
