"""Reject lost source fields, partial switches and unsupported graphics credit."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
SPEC=importlib.util.spec_from_file_location('test_graphics_sdk',ROOT/'scripts/verify-sdk-graphics-origins.py')
V=importlib.util.module_from_spec(SPEC);SPEC.loader.exec_module(V)
M=json.loads((ROOT/V.EVIDENCE).read_text())


class GraphicsProvenanceTests(unittest.TestCase):
    def reject(self, mutate):
        m=copy.deepcopy(M); mutate(m)
        with self.assertRaises(ValueError):
            V.verify_plan(m)

    def test_immutable_manifest(self):
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        V.verify_plan(M)

    def test_preserved_original_proof_inputs(self):
        for path,sha in M['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT/path).read_bytes()),sha,path)

    def test_no_constructor_credit_from_public_caller(self):
        self.reject(lambda m:m['functions'].append(m['functions'][0]))
        self.reject(lambda m:m['sections'][3]['origin'].update(origin='library'))

    def test_unknown_short_getters_are_retained(self):
        self.reject(lambda m:m['retained_unknown'].pop())

    def test_no_exact_or_private_abi_credit(self):
        self.reject(lambda m:m['functions'][0]['accepted_function'].update(match_percent='100.00'))
        self.reject(lambda m:m['functions'][0]['accepted_function'].update(calling_convention='stdcall'))
        self.reject(lambda m:m['functions'][0]['accepted_function'].update(source_file='private.cpp'))

    def test_no_prefix_comparison_for_parser(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['base']=='0x0060E0E0').update(size=1013))

    def test_selector_table_is_part_of_whole_production_source(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['base']=='0x0060D7A9')['flow'].update(table_size=124))

    def test_every_original_data_field_is_required(self):
        self.reject(lambda m:m['sections'][0]['fields'].pop())

    def test_every_real_binding_is_required(self):
        self.reject(lambda m:m['sections'][0]['bindings'].pop())

    def test_actual_gateway_dependencies_are_required(self):
        self.reject(lambda m:m['sections'][0]['bindings'][0].update(target_address='0x006200DA'))

    def test_no_fixed_dynamic_callback(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['base']=='0x0060EB24')['flow']['tails'][0].update(runtime_callee='DebugSetMute'))

    def test_complete_initialized_data_image_required(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['kind']=='data').update(size=1))

    def test_bss_cannot_be_replaced_by_initialized_data(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['kind']=='bss').update(kind='data'))

    def test_public_layout_is_compiler_observation(self):
        self.reject(lambda m:m['layout']['values'].__setitem__(0,208))

    def test_previous_interior_compiler_entries_required(self):
        self.reject(lambda m:m['interiors'].pop())


if __name__=='__main__':
    unittest.main()
