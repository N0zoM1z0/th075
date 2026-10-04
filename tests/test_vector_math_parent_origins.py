import copy
import importlib.util
from pathlib import Path
from types import SimpleNamespace
import unittest


ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('vector_math_parent', ROOT / 'scripts/verify-vector-math-parent-origins.py')
REVIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class VectorMathParentOriginTests(unittest.TestCase):
    def setUp(self):
        self.m=REVIEW.manifest()
        self.rows={r['address']:r for r in self.m['functions']}
        self.graph={r['address']:r for r in self.m['functions']+self.m['auxiliary_bodies']+self.m['anchors']}

    def reject(self, message):
        with self.assertRaisesRegex(ValueError,message):
            REVIEW.verify_plan(self.m)

    def test_cohort_retains_complete_graph(self):
        REVIEW.verify_plan(self.m)

    def test_constructor_cannot_stop_before_cleanup(self):
        self.rows['0x00641C78']['size']=74
        self.reject('complete own auxiliary extent')

    def test_constructor_cannot_invent_missing_aux(self):
        self.rows['0x00641C78']['extent_basis']='function-auxiliary-record'
        self.reject('complete own auxiliary extent')

    def test_qnan_requires_both_operands(self):
        self.rows['0x00647362']['instruction_witnesses']=[w for w in self.rows['0x00647362']['instruction_witnesses'] if w['operands']!='qword ptr [ebp + 0x14]']
        self.reject('both actual operand slots')

    def test_except_requires_actual_result_slot(self):
        self.rows['0x00647479']['instruction_witnesses']=[w for w in self.rows['0x00647479']['instruction_witnesses'] if w['operands']!='qword ptr [ebp + 0x20]']
        self.reject('both actual operands/result')

    def test_constructor_uses_member_callback(self):
        self.rows['0x00641C78']['indirect_calls'][0]['operand']='dword ptr [ebp + 0x18]'
        self.reject('count/receiver/callback')

    def test_constructor_keeps_unwind_callback_separate(self):
        self.m['parent_protocol']['unwind_callback_parameter']='dword ptr [ebp + 0x14]'
        self.reject('callback/operand/dispatch protocol')

    def test_constructor_scope_cannot_point_at_unreviewed_code(self):
        next(r for r in self.m['state_data'] if r['symbol']=='$T327')['relocations'][0]['code_entry']['owner']='0x00641DAA'
        self.reject('unreviewed actual code entry')

    def test_constructor_cleanup_cannot_gain_primary_credit(self):
        self.m['functions'].append(self.m['interior_labels'][0])
        self.reject('bounded complete')

    def test_log10_requires_entire_336_byte_carrier(self):
        self.m['code_carriers'][0]['size']=63
        self.reject('every complete source owner/alignment byte')

    def test_log10_default_body_cannot_be_omitted(self):
        self.m['code_carriers'][0]['components'].pop()
        self.reject('every complete source owner/alignment byte')

    def test_log10_alignment_cannot_gain_function_credit(self):
        self.m['code_carriers'][0]['gaps']=[]
        self.reject('every complete source owner/alignment byte')

    def test_ceil_requires_whole_sse_body(self):
        self.m['code_carriers'][1]['components'].pop()
        self.reject('every complete source owner/alignment byte')

    def test_carrier_cannot_discard_a_default_body_field(self):
        self.m['code_carriers'][0]['relocation_bindings'].pop()
        self.reject('complete bytes or typed fields')

    def test_carrier_cannot_move_an_own_aux_extent(self):
        self.graph['0x0064204B']['source_definition']['offset']-=1
        with self.assertRaisesRegex(ValueError,'complete own source AUX extent'):
            REVIEW.check_carrier_plan(self.m,self.graph)

    def test_complete_sse_primary_cannot_stop_at_intrinsic_prefix(self):
        self.rows['0x00648140']['size']=24
        self.reject('complete own auxiliary extent')

    def test_shared_c_entry_must_keep_actual_source_offset(self):
        self.m['interior_labels'][1]['source_offset']=0
        self.reject('shared entries lose complete source parents')

    def test_no_new_inventory_credit_for_uninventoried_helpers(self):
        self.m['auxiliary_bodies'][0]['decision']='library'
        self.reject('complete auxiliary owners')

    def test_exp_constant_requires_full_carrier_and_code_pointers(self):
        next(r for r in self.m['state_data'] if r['symbol']=='__infinity')['size']=10
        self.reject('complete defining sections')

    def test_log10_coefficients_require_the_entire_2336_byte_carrier(self):
        next(r for r in self.m['state_data'] if r['symbol']=='emask')['size']=16
        self.reject('complete defining sections')

    def test_fdiv_requires_all_64_entries(self):
        next(r for r in self.m['state_data'] if r['symbol']=='fdiv_risc_table')['relocations'].pop()
        self.reject('complete 64-entry source dispatch')

    def test_fdiv_entries_cannot_point_at_partial_helpers(self):
        next(r for r in self.m['state_data'] if r['symbol']=='fdiv_risc_table')['relocations'][0]['code_entry']['owner']='0x00650F81'
        self.reject('actual defining source owner/entry')

    def test_default_matherr_pointer_is_initialized_code(self):
        next(r for r in self.m['state_data'] if r['symbol']=='__pmatherr')['relocations'][0]['target_kind']='state'
        self.reject('initialized default matherr pointer')

    def test_libm_callback_calls_require_actual_slot(self):
        self.rows['0x006485D7']['indirect_calls'][0]['operand']='eax'
        self.reject('initialized default matherr pointer')

    def test_sse_flag_cannot_lose_common_definition(self):
        self.m['common_globals']=[]
        self.reject('COMMON/loader provenance')

    def test_retained_label_keeps_original_acceptance(self):
        self.m['retained_labels'][0]['origin_evidence']='R130'
        self.reject('duplicate credit')

    def test_natural_callback_keeps_ecx_receiver(self):
        self.m['callback_control']['instructions'][2]['operands']='eax, dword ptr [ebp + 8]'
        self.reject('callback/operand/dispatch protocol')

    def test_layout_keeps_second_operand_offset(self):
        self.m['sdk_layout']['objects'][0]['values'][7]=12
        self.reject('operation/layout controls')

    def test_atan_log_floor_modf_alternatives_are_whole_bodies(self):
        self.m['source_alternatives'][1]['size']=63
        self.reject('whole source alternatives')

    def test_prior_runtime_graph_cannot_be_replaced_by_prefixes(self):
        self.m['retained_controls']=[]
        self.reject('independently retained')

    def core_fixture(self):
        label=copy.deepcopy(self.m['interior_labels'][2]);parent=self.graph[label['parent']]
        base=int(parent['address'],16);source_base=parent['source_definition']['offset']
        call=SimpleNamespace(address=source_base+17,mnemonic='call',operands=[SimpleNamespace(type=REVIEW.X86_OP_IMM,imm=source_base+30)])
        predecessor=SimpleNamespace(address=source_base+24,mnemonic='movlpd',size=6)
        target_call=SimpleNamespace(address=base+17,operands=[SimpleNamespace(imm=base+30)])
        return label,parent,[target_call,SimpleNamespace(address=base+30)],[call,predecessor]

    def test_unnamed_core_requires_actual_call_and_fallthrough(self):
        label,parent,target,source=self.core_fixture()
        REVIEW.check_interior_entry(label,parent,[],target,source)

    def test_unnamed_core_cannot_invent_global_symbol(self):
        label,parent,target,source=self.core_fixture();label['source_definition']={'symbol':'__log10_core'}
        with self.assertRaisesRegex(ValueError,'invented source definition'):
            REVIEW.check_interior_entry(label,parent,[],target,source)

    def test_unnamed_core_call_cannot_jump_to_middle_of_instruction(self):
        label,parent,target,source=self.core_fixture();source[0].operands[0].imm+=1
        with self.assertRaisesRegex(ValueError,'call/C-entry fallthrough'):
            REVIEW.check_interior_entry(label,parent,[],target,source)

    def test_unnamed_core_c_entry_cannot_skip_fallthrough(self):
        label,parent,target,source=self.core_fixture();source[1].size=5
        with self.assertRaisesRegex(ValueError,'call/C-entry fallthrough'):
            REVIEW.check_interior_entry(label,parent,[],target,source)


if __name__=='__main__':
    unittest.main()
