"""Guard complete image provenance and real state/nonreturn control flow."""
import copy
import importlib.util
import json
from pathlib import Path
import struct
import unittest

ROOT=Path(__file__).resolve().parents[1]
SPEC=importlib.util.spec_from_file_location('image_tests',ROOT/'scripts/verify-sdk-image-chain-origins.py')
V=importlib.util.module_from_spec(SPEC);SPEC.loader.exec_module(V)
M=json.loads((ROOT/V.EVIDENCE).read_text())
F=V.module('image_flow_tests','sdk_image_carriers.py')


class ImageProvenanceTests(unittest.TestCase):
    def reject(self,mutate):
        m=copy.deepcopy(M);mutate(m)
        with self.assertRaises(ValueError):V.verify_plan(m)

    def test_whole_immutable_plan(self):
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        V.verify_plan(M)

    def test_all_source_and_previous_provenance_pins(self):
        for path,sha in M['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT/path).read_bytes()),sha,path)

    def test_no_source_private_abi_or_exact_credit(self):
        for change in [dict(source_file='private.cpp'),dict(signature='private-owner'),dict(match_percent='100.00')]:
            self.reject(lambda m:m['functions'][0]['accepted_function'].update(change))

    def test_original_unknown_state_is_preserved(self):
        self.reject(lambda m:m['functions'][0]['original_origin'].update(origin='library'))

    def test_no_lifetime_credit_from_method_name(self):
        self.reject(lambda m:m['functions'][0].update(symbol='??1PrivateOwner@@QAE@XZ'))

    def test_two_lifetime_alternatives_retained(self):
        self.reject(lambda m:m['retained_unknown'].pop())

    def test_interior_compiler_snapshot_retained(self):
        self.reject(lambda m:m['interiors'][0]['origin'].update(origin='library'))

    def test_every_real_field_is_required(self):
        self.reject(lambda m:m['sections'][0]['fields'].pop())

    def test_every_real_binding_is_required(self):
        self.reject(lambda m:m['sections'][0]['bindings'].pop())

    def test_complete_original_data_image_required(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['kind']=='data').update(size=1))

    def test_complete_original_bss_required(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['kind']=='bss').update(size=1))

    def test_all_whole_prior_anchors_required(self):
        self.reject(lambda m:m['anchors'].pop())

    def test_original_setjmp3_record_cannot_be_changed(self):
        self.reject(lambda m:next(r for r in m['anchors'] if r['path']=='config/runtime-leaf-origin-evidence.json')['record'].update(size=122))

    def test_absolute_exception_symbol_is_not_pe_storage(self):
        self.reject(lambda m:m['absolute']['__except_list']['definition'].update(section=1))

    def test_full_inflate_table_required(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['base']=='0x00629471').update(size=815))

    def test_full_blocks_table_required(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['base']=='0x0063A903').update(size=1907))

    def test_full_codes_table_required(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['base']=='0x0063D7EC').update(size=1340))

    def test_actual_ecx_index_required(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['base']=='0x0063D7EC')['switch'].update(register='eax'))

    def test_both_blocks_bounds_required(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['base']=='0x0063A903')['switch']['guards'].pop())

    def test_nonvolatile_constant_restore_definitions_required(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['base']=='0x00629471')['switch']['constants'].pop())

    def test_divisor31_cannot_be_claimed_as_table_bound(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['base']=='0x00629471')['switch']['index_paths'].update(table_path_bounds=[31]))

    def test_source_pop_after_nonreturn_is_not_cropped(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['base']=='0x0060F6FF').update(size=27))

    def test_source_int3_after_nonreturn_is_retained(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['base']=='0x00610141')['nonreturn']['suffix'].update(bytes='90'))

    def test_nonreturn_callee_is_independently_owned(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['base']=='0x0062245E')['nonreturn'].update(target='0x00643604'))

    def test_short_policies_need_whole_typed_references(self):
        self.reject(lambda m:m['policy_references'][next(r['address'] for r in m['functions'] if r['size']<=32)].clear())

    def test_all_ordinary_public_emissions_required(self):
        self.reject(lambda m:m['public_control']['emission'].pop())

    def test_original_public_headers_required(self):
        self.reject(lambda m:m['public_control']['headers'].pop(next(iter(m['public_control']['headers']))))

    def test_generic_observer_is_not_private_jpeg_layout(self):
        self.reject(lambda m:m['public_control']['layout']['values'].__setitem__(1,196))


class StateIndexPathTests(unittest.TestCase):
    def run_switch(self,code,count,jump,compare,guard,constant=None):
        address=0x1000;size=len(code);case=size-1
        raw=code+struct.pack('<'+'I'*count,*([address+case]*count))
        fields=[dict(offset=size+4*j,type='DIR32',symbol_type=0,symbol_storage=6,
                     symbol_offset=case,local_symbol_offset=case,addend=0) for j in range(count)]
        spec=dict(code_size=size,count=count,register='eax' if constant else 'ecx',jump=jump,
                  guards=[dict(compare=compare,guard=guard,maximum=count-1,**({'bound_register':'ebp'} if constant else {}))],
                  constants=[constant] if constant else [],index_paths=dict(reaching_comparison_bounds=[dict(compare=compare,maximum=count-1)],
                      table_path_bounds=[count-1],opaque_index_overapproximation=[]))
        return F.switch_edges(raw,address,fields,F.instructions(raw,address,size),spec)

    def test_unsigned_guard_reaches_complete_source_table(self):
        # Toy x86 control flow, unrelated to any supplied target body.
        code=bytes.fromhex('83f9097601c3ff248d')+struct.pack('<I',0x100e)+bytes.fromhex('c3')
        edges,fields=self.run_switch(code,10,6,0,3)
        self.assertEqual(edges,{0x1006:[0x100d]*10});self.assertEqual(len(fields),10)

    def test_index_rewrite_after_guard_is_rejected(self):
        code=bytes.fromhex('83f9097601c3b90a000000ff248d')+struct.pack('<I',0x1013)+bytes.fromhex('c3')
        with self.assertRaisesRegex(ValueError,'unbounded'):self.run_switch(code,10,11,0,3)

    def test_flag_rewrite_before_guard_is_rejected(self):
        code=bytes.fromhex('83f90931c07601c3ff248d')+struct.pack('<I',0x1010)+bytes.fromhex('c3')
        with self.assertRaisesRegex(ValueError,'incomplete|unbounded'):self.run_switch(code,10,8,0,5)

    def test_actual_nonvolatile13_definition_bounds14_labels(self):
        code=bytes.fromhex('6a0d5d3bc57601c3ff2485')+struct.pack('<I',0x1010)+bytes.fromhex('c3')
        self.run_switch(code,14,8,3,5,dict(register='ebp',value=13,push=0,pop=2))

    def test_nonvolatile31_cannot_bound14_label_table(self):
        code=bytes.fromhex('6a1f5d3bc57601c3ff2485')+struct.pack('<I',0x1010)+bytes.fromhex('c3')
        with self.assertRaisesRegex(ValueError,'unbounded'):
            self.run_switch(code,14,8,3,5,dict(register='ebp',value=31,push=0,pop=2))


class NonreturnSourceExtentTests(unittest.TestCase):
    def fixture(self,postlude=b'\x5e'):
        address=0x1000;target=0x00643604
        raw=b'\xe8'+struct.pack('<I',target-address-5)+postlude
        fields=[dict(offset=1,type='REL32',symbol='_longjmp')]
        calls={address+1:target}
        spec=dict(call=0,symbol='_longjmp',target='0x00643604',
                  suffix=dict(offset=5,bytes='5e',mnemonic='pop',operands='esi'))
        return raw,address,fields,calls,{},spec

    def test_complete_source_suffix_is_counted_without_fake_return(self):
        raw,a,fields,calls,data,spec=self.fixture()
        result=F.flow(raw,a,[0],fields,calls,data,nonreturn=spec)
        self.assertEqual(result['whole_size'],6)
        self.assertEqual(result['instruction_count'],2)
        self.assertEqual(result['reachable_instruction_count'],1)
        self.assertEqual(result['returns'],[])

    def test_nonreturn_contract_cannot_be_guessed_for_an_ordinary_call(self):
        raw,a,fields,calls,data,spec=self.fixture()
        with self.assertRaisesRegex(ValueError,'fallthrough'):
            F.flow(raw,a,[0],fields,calls,data)

    def test_extra_ret_cannot_hide_after_the_retained_suffix(self):
        raw,a,fields,calls,data,spec=self.fixture(b'\x5e\xc3')
        with self.assertRaisesRegex(ValueError,'suffix'):
            F.flow(raw,a,[0],fields,calls,data,nonreturn=spec)


if __name__=='__main__':unittest.main()
