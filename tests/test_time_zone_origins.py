import copy
import importlib.util
from pathlib import Path
from types import SimpleNamespace
import unittest


ROOT=Path(__file__).resolve().parents[1]
SPEC=importlib.util.spec_from_file_location('time_zone',ROOT/'scripts/verify-time-zone-origins.py')
REVIEW=importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class TimeZoneOriginTests(unittest.TestCase):
    def setUp(self):
        self.m=REVIEW.manifest()
        self.rows={r['address']:r for r in self.m['functions']}
        self.graph={r['address']:r for r in self.m['functions']+self.m['auxiliary_bodies']+self.m['anchors']}

    def reject(self,message):
        with self.assertRaisesRegex(ValueError,message):
            REVIEW.verify_plan(self.m)

    def test_complete_plan_is_supported(self):
        REVIEW.verify_plan(self.m)

    def test_tzset_wrapper_requires_exceptional_tail(self):
        self.rows['0x00647D5F']['size']=67
        self.reject('complete own auxiliary extent')

    def test_dst_wrapper_requires_exceptional_tail(self):
        self.rows['0x00647DE0']['code_size']=53
        self.reject('complete own auxiliary extent')

    def test_tzset_reader_cannot_discard_cleanup(self):
        self.rows['0x00647778']['size']=539
        self.reject('complete own auxiliary extent')

    def test_getenv_requires_wide_conversion_path(self):
        self.rows['0x006506C5']['size']=70
        self.reject('complete own auxiliary extent')

    def test_compare_requires_both_exception_filters(self):
        self.rows['0x0065422E']['size']=424
        self.reject('complete own auxiliary extent')

    def test_strchr_preceding_entry_cannot_be_omitted(self):
        self.m['auxiliary_bodies'].pop()
        self.reject('complete auxiliary owners')

    def test_no_invented_strchr_inventory_candidate(self):
        self.m['auxiliary_bodies'][0]['decision']='library'
        self.reject('complete auxiliary owners')

    def test_cleanup_cannot_be_separate_primary(self):
        self.m['functions'].append(self.m['interior_labels'][0])
        self.reject('bounded complete')

    def test_tzset_cleanup_keeps_actual_subentry_offset(self):
        self.m['interior_labels'][0]['source_offset']=534
        self.reject('shared entries lose complete source parents')

    def test_cleanup_scope_cannot_point_at_unreviewed_code(self):
        next(r for r in self.m['state_data'] if r['symbol']=='$T20326')['relocations'][0]['code_entry']['owner']='0x00641961'
        self.reject('unreviewed actual code entry')

    def test_scope_entry_precedes_normal_cleanup_subentry(self):
        scope=next(r for r in self.m['state_data'] if r['symbol']=='$T20326')
        field=scope['relocations'][0];field['code_entry']['source_offset']=539
        self.reject('actual defining source owner/entry')

    def test_compare_scope_requires_all_four_filter_handler_fields(self):
        next(r for r in self.m['state_data'] if r['symbol']=='$T20293')['relocations'].pop()
        self.reject('full filter/handler/cleanup provenance')

    def test_native_tzinfo_requires_full_bss_carrier(self):
        next(r for r in self.m['state_data'] if r['symbol']=='_tzinfo')['size']=172
        self.reject('complete defining sections')

    def test_both_transition_records_are_required(self):
        next(r for r in self.m['state_data'] if r['symbol']=='_dststart')['size']=12
        self.reject('complete defining sections')

    def test_both_month_tables_are_required(self):
        next(r for r in self.m['state_data'] if r['symbol']=='__lpdays')['size']=52
        self.reject('complete defining sections')

    def test_timezone_name_pointers_cannot_be_dropped(self):
        next(r for r in self.m['state_data'] if r['symbol']=='__timezone')['relocations'].pop()
        self.reject('initial names/pointer carrier')

    def test_environment_common_cannot_be_treated_as_missing_state(self):
        self.m['common_globals'].pop()
        self.reject('COMMON/loader definitions')

    def test_common_size_comes_from_full_source_declaration(self):
        self.m['common_globals'][0]['source_definition']['offset']=8
        self.reject('COMMON/loader definitions')

    def test_epoch_margin_is_actual_signed_time_policy(self):
        self.m['time_protocol']['localtime_upper_bound']=2147483647
        self.reject('calendar/thread/transition/call protocol')

    def test_localtime_near_epoch_path_keeps_actual_dst_flag(self):
        self.rows['0x0064197E']['instruction_witnesses']=[w for w in self.rows['0x0064197E']['instruction_witnesses'] if w['operands']!='dword ptr [esi + 0x20], 1']
        self.reject('signed epoch margins/DST result field')

    def test_gmtime_allocation_is_whole_tm(self):
        self.rows['0x00647E1E']['instruction_witnesses']=[w for w in self.rows['0x00647E1E']['instruction_witnesses'] if w['mnemonic']!='push' or w['operands']!='0x24']
        self.reject('thread slot/whole tm allocation')

    def test_gmtime_uses_actual_thread_storage_slot(self):
        self.rows['0x00647E1E']['instruction_witnesses']=[w for w in self.rows['0x00647E1E']['instruction_witnesses'] if w['operands']!='dword ptr [edi + 0x44], eax']
        self.reject('thread slot/whole tm allocation')

    def test_time_lock_is_not_environment_lock(self):
        self.rows['0x00647D5F']['instruction_witnesses']=[w for w in self.rows['0x00647D5F']['instruction_witnesses'] if w['mnemonic']!='push' or w['operands']!='6']
        self.reject('time-lock/cdecl return')

    def test_natural_layout_keeps_four_byte_time_t(self):
        self.m['sdk_layout']['objects'][0]['values'][3]=8
        self.reject('operation/layout controls')

    def test_natural_layout_keeps_172_byte_windows_timezone(self):
        self.m['sdk_layout']['objects'][0]['values'][32]=180
        self.reject('operation/layout controls')

    def test_narrow_dup_call_cannot_use_wide_symbol(self):
        self.m['call_controls'][0]['relocation_metadata'][0]['symbol']='__wcsdup'
        self.reject('calendar/thread/transition/call protocol')

    def test_both_complete_vendor_alternatives_are_retained(self):
        self.m['source_alternatives'].pop()
        self.reject('equivalent complete vendor alternatives')

    def test_strncnt_requires_actual_defining_compare_parent(self):
        self.m['source_alternatives'][1]['selected_parent']='0x00654660'
        self.reject('equivalent complete vendor alternatives')

    def test_copy_local_definition_cannot_move_to_wide_vendor_member(self):
        self.rows['0x006545FF']['member_offset']=1550570
        self.reject('actual defining source owner/entry|typed source symbol')

    def test_whole_strchr_source_carrier_cannot_be_prefix(self):
        self.m['code_carriers'][0]['size']=16
        self.reject('both complete own-AUX entries')

    def test_entire_old_mbschr_range_is_required(self):
        self.m['extent_reconciliations']=[]
        self.reject('entire old provisional extent')

    def test_old_mbschr_range_must_keep_neighbor_source_body(self):
        self.m['extent_reconciliations'][0]['components'].pop()
        self.reject('complete bodies or invents padding credit')

    def test_linker_alignment_cannot_gain_origin_credit(self):
        self.m['extent_reconciliations'][0]['components'][1]['credit']='library'
        self.reject('complete bodies or invents padding credit')

    def test_localtime_cannot_inherit_origin_from_known_callees(self):
        self.rows['0x0064197E']['extent_basis']='callee-name'
        self.reject('complete own auxiliary extent')

    def test_complete_vendor_source_layouts_are_pinned(self):
        self.m['vendor_sources'].pop('crt/src/tzset.c')
        self.reject('pinned complete vendor sources')

    def test_prior_independent_graph_remains_required(self):
        self.m['retained_controls']=[]
        self.reject('independently retained')

    def test_actual_cleanup_definition_is_read_back(self):
        label=copy.deepcopy(self.m['interior_labels'][1]);parent=self.graph[label['parent']]
        definition=copy.deepcopy(label['source_definition']);definition['offset']-=1
        target=[SimpleNamespace(address=int(label['address'],16))]
        with self.assertRaisesRegex(ValueError,'full-owner defining source symbol'):
            REVIEW.check_interior_entry(label,parent,[definition],target,[])


if __name__=='__main__':
    unittest.main()
