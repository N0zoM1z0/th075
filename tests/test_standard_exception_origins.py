import copy
import importlib.util
from pathlib import Path
import struct
from types import SimpleNamespace
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('standard_exception', ROOT / 'scripts/verify-standard-exception-origins.py')
REVIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


def symbol(name,value,section,typ,storage,aux=0):
    return struct.pack('<8sIhHBB',name.encode().ljust(8,b'\0'),value,section,typ,storage,aux)


def weak_object(search=2,tag=2):
    header = struct.pack('<HHIIIHH',0x14C,1,0,60,4,0,0)
    section = struct.pack('<8sIIIIIIHHI',b'.text',0,0,0,0,0,0,0,0,0x20)
    records = (symbol('Weak',0,0,32,105,1)+struct.pack('<II10s',tag,search,b'\0'*10)
               +symbol('Body',0,0,32,2)+symbol('Body',0,1,32,2))
    return header+section+records+struct.pack('<I',4)


def interior_vtable_object():
    # Synthetic initialized data: locator prefix and two callback slots.
    header = struct.pack('<HHIIIHH',0x14C,1,0,102,3,0,0)
    section = struct.pack('<8sIIIIIIHHI',b'.rdata',0,0,12,60,72,0,3,0,0x40000040)
    raw = struct.pack('<III',0,0,0)
    fields = b''.join(struct.pack('<IIH',offset,target,6) for offset,target in [(0,1),(4,2),(8,2)])
    records = symbol('Vtable',4,1,0,2)+symbol('Locator',0,0,0,2)+symbol('Callback',0,0,32,2)
    return header+section+raw+fields+records+struct.pack('<I',4)


class StandardExceptionOriginTests(unittest.TestCase):
    def setUp(self):
        self.m = REVIEW.manifest()
        self.graph = {r['address']:r for r in self.m['functions']+self.m['auxiliary_bodies']+self.m['anchors']}

    def reject(self,message):
        with self.assertRaisesRegex(ValueError,message):
            REVIEW.verify_plan(self.m)

    def remove_witness(self,key,mnemonic,operands):
        row = self.graph[key]
        row['instruction_witnesses'] = [w for w in row['instruction_witnesses'] if (w['mnemonic'],w['operands'])!=(mnemonic,operands)]

    def test_complete_closed_plan_passes(self):
        REVIEW.verify_plan(self.m)

    def test_type_info_destructor_requires_finally_tail(self):
        self.graph['0x00640E49']['size'] = 61
        self.reject('complete own AUX')

    def test_copy_constructor_cannot_drop_borrowed_branch(self):
        self.graph['0x00640C9A']['size'] = 61
        self.reject('complete own AUX')

    def test_throw_requires_return_and_both_arguments(self):
        self.graph['0x00640C12']['code_size'] = 54
        self.reject('complete own AUX')

    def test_frame_shim_requires_full_register_restore(self):
        self.graph['0x006407B8']['size'] = 47
        self.reject('complete own AUX')

    def test_actual_finally_entry_cannot_be_six_bytes_late(self):
        self.m['interior_labels'][0]['source_offset'] = 67
        self.reject('complete source parents')

    def test_uninventoried_what_control_cannot_gain_candidate_credit(self):
        self.m['auxiliary_bodies'][0]['decision'] = 'library'
        self.reject('invented inventory credit')

    def test_scalar_compiler_anchors_keep_prior_r038_origin(self):
        self.m['anchors'][-1]['origin'] = 'library'
        self.reject('independent full anchors')

    def test_r038_full_cold_control_cannot_be_omitted(self):
        self.m['retained_controls'].pop()
        self.reject('retained independent R141/R038')

    def test_complete_rtti_data_cannot_be_prefix(self):
        self.m['state_data'][1]['size'] = 8
        self.reject('complete defining data')

    def test_full_exception_vtable_has_locator_and_two_slots(self):
        self.m['standard_protocol']['exception_vtable_complete_size'] = 8
        self.reject('private ABI')

    def test_type_info_vtable_has_locator_prefix(self):
        self.m['standard_protocol']['type_info_vtable_complete_size'] = 4
        self.reject('private ABI')

    def test_source_base_array_has_all_five_bytes(self):
        self.m['standard_protocol']['rtti_base_array_complete_size'] = 4
        self.reject('private ABI')

    def test_sdk_record_is_not_private_32_byte_template(self):
        self.m['standard_protocol']['sdk_exception_record_size'] = 32
        self.reject('private ABI')

    def test_actual_throw_parameter_count_is_three(self):
        self.m['standard_protocol']['throw_parameter_count'] = 15
        self.reject('private ABI')

    def test_throw_descriptor_is_opaque_input(self):
        self.m['standard_protocol']['runtime_unknowns'] = 'complete private ThrowInfo and original linker decisions known'
        self.reject('private ABI')

    def test_sdk_exception_size_and_model_offsets_are_distinct_facts(self):
        self.m['sdk_layout']['objects'][0]['values'][11] = 8
        self.reject('actual SDK')

    def test_source_frame_metadata_arrives_in_eax(self):
        self.m['register_contracts']['0x006407B8']['incoming'] = ['five conventional stack arguments']
        self.reject('private ABI')

    def test_frame_shim_requires_eight_arg_cleanup(self):
        self.remove_witness('0x006407B8','add','esp, 0x20')
        self.reject('ownership/ABI/finally')

    def test_type_info_finally_must_unlock(self):
        self.remove_witness('0x00640E49','call','0x646658')
        self.reject('ownership/ABI/finally')

    def test_type_info_destructor_uses_lock_fourteen(self):
        self.remove_witness('0x00640E49','push','0xe')
        self.reject('ownership/ABI/finally')

    def test_copy_requires_owned_flag_copy(self):
        self.remove_witness('0x00640C9A','mov','dword ptr [esi + 8], eax')
        self.reject('ownership/ABI/finally')

    def test_copy_requires_terminator_byte_in_allocation(self):
        self.remove_witness('0x00640C9A','inc','eax')
        self.reject('ownership/ABI/finally')

    def test_assignment_requires_self_guard(self):
        self.remove_witness('0x00640DD6','cmp','esi, dword ptr [esp + 8]')
        self.reject('ownership/ABI/finally')

    def test_destructor_cannot_free_borrowed_message(self):
        self.remove_witness('0x00640CE4','cmp','dword ptr [ecx + 8], 0')
        self.reject('ownership/ABI/finally')

    def test_throw_ret_cannot_be_cdecl(self):
        self.graph['0x00640C12']['body_facts']['returns'][0]['cleanup'] = 0
        self.reject('callee cleanup')

    def test_copy_ret_pops_one_argument(self):
        self.graph['0x00640C9A']['body_facts']['returns'][0]['cleanup'] = 0
        self.reject('callee cleanup')

    def test_operator_delete_cannot_gain_fake_return(self):
        self.graph['0x00640F15']['body_facts']['returns'] = [dict(site='0x00640F19',cleanup=0)]
        self.reject('fake return')

    def test_raise_import_identity_is_independent_of_patched_bytes(self):
        b = next(b for b in self.graph['0x00640C12']['relocation_bindings'] if b['target_kind']=='import')
        b['import_name'] = 'RtlUnwind'
        self.reject('RaiseException source/API')

    def test_actual_raise_indirect_site_cannot_be_dropped(self):
        self.graph['0x00640C12']['indirect_calls'] = []
        self.reject('dispatch inventory')

    def test_weak_search_mode_cannot_be_invented_alias_mode(self):
        self.m['source_weak_references'][0]['search_characteristics'] = 3
        self.reject('actual weak fallback')

    def test_weak_fallback_cannot_be_changed_to_ordinary_destructor(self):
        self.m['source_weak_references'][0]['fallback_symbol'] = '??1exception@@UAE@XZ'
        self.reject('actual weak fallback')

    def test_typed_weak_callback_requires_complete_actual_fallback_catalog(self):
        b = copy.deepcopy(next(b for r in self.m['state_data'] for b in r['relocations'] if 'source_weak_reference' in b))
        REVIEW.check_code_entry(b,self.graph)
        REVIEW.check_catalog_entry(b,self.m['code_definitions'])
        b['code_entry']['source_definition']['section'] = 17
        with self.assertRaisesRegex(ValueError,'actual COFF definitions'):
            REVIEW.check_catalog_entry(b,self.m['code_definitions'])

    def test_cold_generated_handler_prefix_cannot_replace_whole_section(self):
        self.m['probe_generated_code'][1]['size'] = 17
        self.reject('probe_generated_code')

    def test_model_catch_metadata_cannot_omit_neighbours(self):
        self.m['probe_generated_data'][-1]['source_section']['size'] = 28
        self.reject('probe_generated_data')

    def test_supplied_complete_sdk_exception_header_is_required(self):
        self.m['sdk_layout']['headers'].pop('crt/src/exception')
        self.reject('actual SDK')

    def test_invented_private_original_source_is_rejected(self):
        self.m['vendor_sources']['crt/src/throw.cpp'] = 'guessed'
        self.reject('actual SDK or available source')

    def test_weak_reader_uses_actual_aux_tag_and_search_record(self):
        c = REVIEW.module('weak_test_comparison','compare-coff-function.py')
        coff = REVIEW.module('weak_test_coff','coff_data.py')
        row = REVIEW.read_weak_reference(weak_object(),'Weak',c,coff,12)
        self.assertEqual(row['fallback_symbol'],'Body')
        self.assertEqual(row['fallback_definition']['section'],1)
        self.assertEqual(row['search_characteristics'],2)

    def test_weak_reader_rejects_wrong_search_mode(self):
        c = REVIEW.module('weak_mode_comparison','compare-coff-function.py')
        coff = REVIEW.module('weak_mode_coff','coff_data.py')
        with self.assertRaisesRegex(ValueError,'search mode or fallback tag'):
            REVIEW.read_weak_reference(weak_object(search=3),'Weak',c,coff,12)

    def test_weak_reader_rejects_auxiliary_tag(self):
        c = REVIEW.module('weak_tag_comparison','compare-coff-function.py')
        coff = REVIEW.module('weak_tag_coff','coff_data.py')
        with self.assertRaisesRegex(ValueError,'search mode or fallback tag'):
            REVIEW.read_weak_reference(weak_object(tag=1),'Weak',c,coff,12)

    def test_interior_vtable_reader_keeps_locator_prefix_and_all_fields(self):
        c = REVIEW.module('whole_vtable_comparison','compare-coff-function.py')
        coff = REVIEW.module('whole_vtable_coff','coff_data.py')
        raw,desc,anchor = REVIEW.whole_defining_section(interior_vtable_object(),'Vtable',c,coff)
        self.assertEqual(anchor['offset'],4)
        self.assertEqual(len(raw),12)
        self.assertEqual([r['offset'] for r in desc['relocations']],[0,4,8])

    def test_finally_entry_starts_at_actual_scope_callback(self):
        label = self.m['interior_labels'][0];parent = self.graph[label['parent']]
        target = [SimpleNamespace(address=int(label['address'],16))]
        source = [SimpleNamespace(address=parent['source_definition']['offset']+label['source_offset'])]
        REVIEW.check_interior_entry(label,parent,[label['source_definition']],target,source)
        changed = copy.deepcopy(label);changed['scope_entry_offset'] = 55
        with self.assertRaisesRegex(ValueError,'actual finally scope entry'):
            REVIEW.check_interior_entry(changed,parent,[label['source_definition']],target,source)


if __name__ == '__main__':
    unittest.main()
