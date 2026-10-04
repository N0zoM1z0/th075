import copy
import importlib.util
from pathlib import Path
import struct
from types import SimpleNamespace
import unittest

ROOT=Path(__file__).resolve().parents[1]
SPEC=importlib.util.spec_from_file_location('input_format',ROOT/'scripts/verify-input-format-origins.py')
REVIEW=importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)

class InputFormatOriginTests(unittest.TestCase):
    def setUp(self):
        self.m=REVIEW.manifest()
        self.rows={r['address']:r for r in self.m['functions']}
        self.graph={r['address']:r for r in self.m['functions']+self.m['auxiliary_bodies']+self.m['anchors']}

    def reject(self,message):
        with self.assertRaisesRegex(ValueError,message):
            REVIEW.verify_plan(self.m)

    def test_complete_plan_is_supported(self):
        REVIEW.verify_plan(self.m)

    def test_input_requires_entire_error_epilog(self):
        self.rows['0x0064993C']['size']=3390
        self.reject('complete own auxiliary extent')

    def test_input_requires_filter_and_normal_exit(self):
        self.rows['0x0064993C']['code_size']=3451
        self.reject('complete own auxiliary extent')

    def test_localeinfo_requires_integer_query_path(self):
        self.rows['0x006519EE']['size']=195
        self.reject('complete own auxiliary extent')

    def test_wide_nls_requires_cleanup_exit(self):
        self.rows['0x00653B2C']['size']=298
        self.reject('complete own auxiliary extent')

    def test_narrow_nls_requires_fallback_exit(self):
        self.rows['0x00653C5C']['code_size']=303
        self.reject('complete own auxiliary extent')

    def test_input_auxiliaries_cannot_gain_inventory_credit(self):
        self.m['auxiliary_bodies'][0]['decision']='library'
        self.reject('complete auxiliary owners')

    def test_input_filter_cannot_gain_new_candidate(self):
        self.m['interior_labels']=[dict(address='0x00649F66')]
        self.reject('shared entries')

    def test_scope_must_include_filter_and_handler(self):
        self.m['scope_tables'].pop()
        self.reject('three complete source-defined SEH scopes')

    def test_scope_filter_must_precede_handler(self):
        self.m['scope_tables'][0]['filter_offset']=1582
        self.reject('three complete source-defined SEH scopes')

    def test_scope_cannot_omit_handler_field(self):
        next(r for r in self.m['state_data'] if r['symbol']=='$T21139')['relocations'].pop()
        self.reject('scope loses its full actual')

    def test_scope_filter_cannot_point_at_other_parent(self):
        next(r for r in self.m['state_data'] if r['symbol']=='$T21139')['relocations'][0]['code_entry']['owner']='0x00653B2C'
        self.reject('actual defining source owner')

    def test_scope_reference_requires_actual_object(self):
        next(b for b in self.rows['0x0064993C']['relocation_bindings'] if b['symbol']=='$T21139')['target_address']='0x0066255C'
        self.reject('actual complete parent reference')

    def test_scope_cannot_be_twelve_byte_prefix(self):
        next(r for r in self.m['state_data'] if r['symbol']=='$T20169')['size']=8
        self.reject('complete defining sections')

    def test_ctype_requires_whole_combined_carrier(self):
        next(r for r in self.m['state_data'] if r['symbol']=='___newctype')['size']=514
        self.reject('complete defining sections')

    def test_locale_requires_full_default_carrier(self):
        next(r for r in self.m['state_data'] if r['symbol']=='__clocalestr')['size']=84
        self.reject('complete defining sections')

    def test_numeric_buffer_requires_four_wide_chars(self):
        next(r for r in self.m['state_data'] if r['symbol'].startswith('?wcbuffer'))['size']=4
        self.reject('complete defining sections')

    def test_nls_flavor_state_must_keep_distinct_definitions(self):
        next(r for r in self.m['state_data'] if r['symbol'].startswith('?f_use') and r['target_address']=='0x0068E798')['target_address']='0x0068E794'
        self.reject('complete defining sections')

    def test_fp_table_requires_all_six_image_slots(self):
        next(r for r in self.m['state_data'] if r['symbol']=='__cfltcvt_tab')['relocations'].pop()
        self.reject('six complete fatal-stub fields')

    def test_fassign_requires_actual_table_slot(self):
        next(b for b in self.rows['0x0064993C']['relocation_bindings'] if b['symbol']=='__cfltcvt_tab')['addend']=0
        self.reject('actual fassign callback slot')

    def test_fp_runtime_state_cannot_be_assumed(self):
        self.m['runtime_dispatch']['basis']='runtime initialized'
        self.reject('complete initial/initialized six-slot')

    def test_fp_view_requires_all_initializer_fields(self):
        next(r for r in self.m['anchors'] if r['address']=='0x0064057A')['relocation_bindings'].pop()
        self.reject('full initializer writes')

    def test_natural_argument_pointer_requires_four_bytes(self):
        self.m['sdk_layout']['objects'][0]['values'][0]=8
        self.reject('operation/layout controls')

    def test_natural_va_list_requires_pointer_carrier(self):
        self.m['sdk_layout']['objects'][0]['values'][6]=8
        self.reject('operation/layout controls')

    def test_scanf_stream_requires_read_flags(self):
        self.m['sdk_layout']['objects'][0]['values'][17]=66
        self.reject('operation/layout controls')

    def test_scanset_requires_all_256_bits(self):
        self.m['input_protocol']['scanset_size']=16
        self.reject('pointer-varargs/scanset')

    def test_input_float_storage_cannot_use_output_capacity(self):
        self.m['input_protocol']['float_buffer_size']=512
        self.reject('pointer-varargs/scanset')

    def test_input_float_width_requires_349_limit(self):
        self.m['sdk_layout']['objects'][0]['values'][32]=512
        self.reject('operation/layout controls')

    def test_locale_requires_real_thread_pointer_offset(self):
        self.m['locale_layout']['objects'][0]['values'][3]=104
        self.reject('natural SDK/thread/locale')

    def test_locale_requires_complete_84_byte_type(self):
        self.m['locale_layout']['objects'][0]['values'][4]=380
        self.reject('natural SDK/thread/locale')

    def test_multibyte_api_requires_invalid_character_flag(self):
        self.m['locale_call_controls'][0]['instructions'][12]['operands']='1'
        self.reject('pointer-varargs/scanset')

    def test_multibyte_api_requires_real_stdcall_import(self):
        self.m['locale_call_controls'][0]['relocation_metadata'][0]['symbol']='_MultiByteToWideChar'
        self.reject('pointer-varargs/scanset')

    def test_fassign_control_requires_twelve_byte_caller_cleanup(self):
        self.m['call_controls'][2]['instructions'][8]['operands']='esp, 0x14'
        self.reject('pointer-varargs/scanset')

    def test_multiply_requires_actual_runtime_symbol(self):
        self.m['call_controls'][1]['relocation_metadata'][0]['symbol']='__aulldvrm'
        self.reject('pointer-varargs/scanset')

    def test_inc_requires_source_local_storage(self):
        self.rows['0x006498FC']['source_definition']['storage']=2
        self.reject('source-local defining parent')

    def test_retained_output_graph_is_required(self):
        self.m['retained_controls']=[]
        self.reject('independently retained')

    def test_ctype_defining_source_is_required(self):
        self.m['vendor_sources'].pop('crt/src/_ctype.c')
        self.reject('defining vendor sources')

    def test_input_requires_readonly_byte_load(self):
        self.rows['0x006498FC']['instruction_witnesses']=[w for w in self.rows['0x006498FC']['instruction_witnesses'] if w['mnemonic']!='movzx']
        self.reject('behavior witnesses')

    def test_locale_error_requires_actual_insufficient_buffer_policy(self):
        self.rows['0x006519EE']['instruction_witnesses']=[w for w in self.rows['0x006519EE']['instruction_witnesses'] if w['operands']!='eax, 0x7a']
        self.reject('behavior witnesses')

    def scope_fixture(self):
        decoded={}
        for scope in self.m['scope_tables']:
            witnesses=self.graph[scope['parent']]['instruction_witnesses']
            decoded[scope['parent']]=[SimpleNamespace(address=int(w['site'],16),
                mnemonic=w['mnemonic'],op_str=w['operands'],
                size=int(witnesses[i+1]['site'],16)-int(w['site'],16) if i+1<len(witnesses) else 1)
                for i,w in enumerate(witnesses)]
        data={int(s['address'],16):struct.pack('<3I',0xffffffff,
            int(s['parent'],16)+s['filter_offset'],int(s['parent'],16)+s['handler_offset'])
            for s in self.m['scope_tables']}
        comparison=SimpleNamespace(pe_bytes_at=lambda target,address,size:data[address][:size])
        return decoded,data,comparison

    def test_complete_scope_records_are_supported(self):
        decoded,data,comparison=self.scope_fixture()
        REVIEW.check_seh_scopes(self.m,None,comparison,decoded)

    def test_actual_scope_requires_negative_enclosing_level(self):
        decoded,data,comparison=self.scope_fixture()
        data[0x662558]=struct.pack('<3I',0,0x649f66,0x649f6a)
        with self.assertRaisesRegex(ValueError,'full -1/filter/handler'):
            REVIEW.check_seh_scopes(self.m,None,comparison,decoded)

    def test_filter_cannot_lose_constant_one_return(self):
        decoded,data,comparison=self.scope_fixture()
        next(i for i in decoded['0x0064993C'] if i.address==0x649f68).mnemonic='nop'
        with self.assertRaisesRegex(ValueError,'complete constant-one return'):
            REVIEW.check_seh_scopes(self.m,None,comparison,decoded)

    def test_handler_cannot_skip_real_stack_reset(self):
        decoded,data,comparison=self.scope_fixture()
        next(i for i in decoded['0x00653B2C'] if i.address==0x653beb).op_str='0x65188e'
        with self.assertRaisesRegex(ValueError,'stack restoration and real reset'):
            REVIEW.check_seh_scopes(self.m,None,comparison,decoded)

if __name__=='__main__':
    unittest.main()
