"""Reject incomplete dispatch graphs and unsupported historical snapshot transitions."""
import copy
import importlib.util
import json
from pathlib import Path
import struct
import unittest

ROOT = Path(__file__).resolve().parents[1]

def load(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT/'scripts'/filename)
    module = importlib.util.module_from_spec(spec); spec.loader.exec_module(module)
    return module

V = load('test_dispatch_origins', 'verify-sdk-dispatch-origins.py')
CFG = load('test_dispatch_cfg', 'sdk_dispatch_carriers.py')
M = json.loads((ROOT/V.EVIDENCE).read_text())


class DispatchEvidenceTests(unittest.TestCase):
    def reject(self, mutate):
        m = copy.deepcopy(M); mutate(m)
        with self.assertRaises(ValueError): V.verify_plan(m)

    def test_immutable_manifest(self):
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()), V.MANIFEST_SHA256)
        V.verify_plan(M)

    def test_retained_manifests_and_carriers(self):
        for path, sha in M['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT/path).read_bytes()), sha, path)

    def test_missing_whole_callback(self):
        self.reject(lambda m: m['controls'].pop())

    def test_truncated_data_section(self):
        self.reject(lambda m: m['data'][0].update(size=456))

    def test_missing_real_pointer(self):
        self.reject(lambda m: m['data'][0]['fields'].pop())

    def test_false_default_slot(self):
        self.reject(lambda m: m['data'][0]['fields'][-1].update(offset=228))

    def test_missing_actual_finite_caller(self):
        self.reject(lambda m: next(r for r in m['controls'] if r['address']=='0x0061BE75')['fields'][0].update(symbol='__CIacos'))

    def test_omitted_cpu_dependency(self):
        self.reject(lambda m: m['anchors'].pop())

    def test_wrong_independent_anchor(self):
        self.reject(lambda m: m['anchors'][0].update(symbol='_invented'))

    def test_false_switch_code_extent(self):
        self.reject(lambda m: next(r for r in m['controls'] if r['address']=='0x0061E467')['flow'].update(extent=397))

    def test_false_switch_table_kind(self):
        self.reject(lambda m: next(r for r in m['controls'] if r['address']=='0x0061E5F4')['flow'].update(table_size=0))

    def test_hidden_selected_entry(self):
        self.reject(lambda m: m['functions'][-1].update(address=m['functions'][0]['address']))

    def test_false_exact_credit(self):
        self.reject(lambda m: m['functions'][0]['accepted_function'].update(match_percent='100.00'))

    def test_false_abi_credit(self):
        self.reject(lambda m: m['functions'][0]['accepted_function'].update(calling_convention='stdcall'))

    def test_false_source_credit(self):
        self.reject(lambda m: m['functions'][0]['accepted_function'].update(source_file='invented.cpp'))

    def test_false_extent_change(self):
        self.reject(lambda m: m['functions'][0]['accepted_function'].update(size='5'))

    def test_false_private_layout_claim(self):
        self.reject(lambda m: m['functions'][0]['accepted_function'].update(signature='D3DXFASTTABLE* table'))

    def test_four_exact_transitions(self):
        for a in ['0x0061AF34','0x0061CA33','0x00620C9A','0x00643FC6']:
            r=next(r for r in M['functions'] if r['address']==a)
            self.assertTrue(V.allows_transition(a,r['original_function'],r['original_origin'],r['accepted_function'],r['accepted_origin']))

    def test_unrelated_pending_row_never_transitions(self):
        r=M['functions'][0]
        self.assertFalse(V.allows_transition('0x0064F513',r['original_function'],r['original_origin'],r['accepted_function'],r['accepted_origin']))

    def test_modified_historical_row_never_transitions(self):
        r=M['functions'][0]; old=dict(r['original_function'],size='5')
        self.assertFalse(V.allows_transition(r['address'],old,r['original_origin'],r['accepted_function'],r['accepted_origin']))

    def test_modified_accepted_row_never_transitions(self):
        r=M['functions'][0]; new=dict(r['accepted_function'],owner='authored')
        self.assertFalse(V.allows_transition(r['address'],r['original_function'],r['original_origin'],new,r['accepted_origin']))

    def test_pinned_field_definition(self):
        raw=b'\xff\x25'+bytes(4); f=dict(offset=2,type='DIR32',symbol='table',addend=4,symbol_section=3,symbol_type=0,symbol_storage=2)
        b=dict(f,source_base='0x00002000',target_address='0x00002004')
        linked,_,_=V.bind(raw,[f],[b],{'table':0x2000},1,0x1000)
        self.assertEqual(linked,b'\xff\x25'+struct.pack('<I',0x2004))
        with self.assertRaises(ValueError): V.bind(raw,[f],[b],{'table':0x3000},1,0x1000)

    def test_data_field_zero_is_genuine(self):
        f=dict(offset=0,type='DIR32',symbol='callback',addend=0,symbol_section=0,symbol_type=32,symbol_storage=2)
        b=dict(f,source_base='0x00002000',target_address='0x00002000')
        linked,_,_=V.bind(bytes(4),[f],[b],{'callback':0x2000},1,0x3000,True)
        self.assertEqual(linked,struct.pack('<I',0x2000))
        with self.assertRaises(ValueError): V.bind(bytes(4),[f],[b],{'callback':0x2000},1,0x3000)

    def test_overlapping_real_fields_rejected(self):
        f=dict(offset=2,type='DIR32',symbol='table',addend=0,symbol_section=3,symbol_type=0,symbol_storage=2)
        b=dict(f,source_base='0x00002000',target_address='0x00002000')
        with self.assertRaises(ValueError): V.bind(bytes(6),[f,f],[b,b],{'table':0x2000},1,0x1000)

    def test_actual_table_tail_remains_runtime_selected(self):
        code=b'\xff\x25'+struct.pack('<I',0x2000)
        proof=CFG.flow(code,0x1000,[0],[],{}, {0x1002:0x2000},slots={0x2000})
        self.assertEqual(proof['external_tails'],[dict(site=0,slot='0x00002000',runtime_selected=True)])
        with self.assertRaises(ValueError): CFG.flow(code,0x1000,[0],[],{}, {0x1002:0x2000},slots={0x2004})

    def test_unbound_table_tail_rejected(self):
        code=b'\xff\x25'+struct.pack('<I',0x2000)
        with self.assertRaises(ValueError): CFG.flow(code,0x1000,[0],[],{}, {},slots={0x2000})

    def test_register_tail_never_gets_fixed_callee_credit(self):
        with self.assertRaises(ValueError): CFG.flow(b'\xff\xe0',0x1000,[0],[],{}, {},slots={0x2000})

    def test_bound_slot_call_and_return(self):
        code=b'\xff\x15'+struct.pack('<I',0x2000)+b'\xc3'
        self.assertEqual(CFG.flow(code,0x1000,[0],[],{}, {0x1002:0x2000},slots={0x2000})['indirect_call_count'],1)
        with self.assertRaises(ValueError): CFG.flow(code,0x1000,[0],[],{}, {0x1002:0x2000},slots={0x2004})

    def test_register_call_rejected(self):
        with self.assertRaises(ValueError): CFG.flow(b'\xff\xd0\xc3',0x1000,[0],[],{}, {},slots={0x2000})

    def test_hidden_field_after_return_rejected(self):
        with self.assertRaises(ValueError): CFG.flow(b'\xc3\x90',0x1000,[0],[],{}, {0x1001:0},slots=())


if __name__ == '__main__': unittest.main()
