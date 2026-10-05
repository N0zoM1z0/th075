"""Guard complete nested policies, authored lifetime discrimination and history."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
SPEC=importlib.util.spec_from_file_location('nested_insertion_tests',ROOT/'scripts/verify-nested-vector-insertion-origins.py')
V=importlib.util.module_from_spec(SPEC);SPEC.loader.exec_module(V)
M=json.loads((ROOT/V.EVIDENCE).read_text())


class NestedInsertionTests(unittest.TestCase):
    def reject(self,mutate):
        m=copy.deepcopy(M);mutate(m)
        with self.assertRaises(ValueError):V.verify_plan(m)

    def test_frozen_complete_plan(self):
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256);V.verify_plan(M)

    def test_prior_evidence_source_pins(self):
        for path,sha in M['retained_sha256'].items():self.assertEqual(V.digest((ROOT/path).read_bytes()),sha,path)

    def test_all_eighteen_transitions(self):
        self.assertEqual(sum(r['accepted_origin']['origin']=='library' for r in M['functions']),17)
        self.assertEqual(sum(r['accepted_origin']['origin']=='authored' for r in M['functions']),1)
        self.reject(lambda m:m['functions'].pop())

    def test_whole_nested_head_includes_final37(self):
        self.assertEqual(V.WHOLE['0x00459CB0'],1101)
        self.reject(lambda m:m['groups'][1].update(whole_size=1064))

    def test_pointer_head_final19(self):
        self.assertEqual(V.WHOLE['0x005F9A10'],796)
        self.reject(lambda m:m['sections'][0].update(size=777))

    def test_full_copy_constructor208(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['base']=='0x00459390').update(size=162))

    def test_full_uninitialized_copy189(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['base']=='0x0045B300').update(size=120))

    def test_recovery_entries2_9_58_are_not_independent_functions(self):
        entries=[r for r in M['interiors'] if r['parent']=='0x0045B300']
        self.assertEqual([r['size'] for r in entries],[2,9,58])
        self.reject(lambda m:m['interiors'].pop())

    def test_shared_tail37_has_cleanup_policy(self):
        r=next(r for r in M['interiors'] if r['address']=='0x0045A0D8')
        self.assertEqual(r['accepted_origin']['origin'],'library')
        self.reject(lambda m:next(r for r in m['functions'] if r['address']=='0x0045A0D8')['accepted_origin'].update(origin='compiler'))

    def test_all_fields_and_bindings(self):
        self.reject(lambda m:m['sections'][0]['fields'].pop())
        self.reject(lambda m:m['sections'][0]['bindings'].pop())

    def test_real_coff_symbol_indices_and_aux(self):
        self.reject(lambda m:m['sections'][0]['source']['aux_records'][1].update(index=0))

    def test_complete_debug_line_provenance(self):
        self.reject(lambda m:m['sections'][0]['source']['coff_line_table'].pop())

    def test_full_graph_inventory_entries(self):
        self.reject(lambda m:m['sections'][0]['inventory_entries'].pop())

    def test_all_normal_catch_and_unwind_roots(self):
        self.reject(lambda m:m['sections'][0]['roots'].pop())
        self.reject(lambda m:m['sections'][0]['flow'].update(reachable_instruction_count=1))

    def test_full_data_not_throw_address_point_only(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['kind']=='data' and r['size']==132).update(size=36))

    def test_retained_owners_not_native_field_observations(self):
        self.reject(lambda m:m['prior']['shared'][0]['owner']['record'].update(address='0x00000000'))

    def test_actual_weak_full_aux(self):
        self.assertEqual(len(bytes.fromhex(M['weak_references'][0]['aux_hex'])),18)
        self.reject(lambda m:m['weak_references'][0].update(fallback_symbol_index=0))

    def test_original_absolute_owner(self):
        self.reject(lambda m:m['prior']['absolute']['__except_list']['definition'].update(section=1))

    def test_authored_clear_policy_is_not_default_implicit_lifetime(self):
        self.reject(lambda m:next(r for r in m['functions'] if r['address']=='0x004588E0')['accepted_origin'].update(origin='compiler'))

    def test_complete_implicit_alternative90(self):
        self.assertEqual(M['implicit_alternative']['size'],90)
        self.reject(lambda m:m['implicit_alternative'].update(size=116))

    def test_both_explicit_clear_calls_and_order(self):
        self.assertEqual([r['site'] for r in M['authored_policy']['explicit_clear_calls']],['0x00458909','0x00458914'])
        self.reject(lambda m:m['authored_policy']['explicit_clear_calls'].pop())

    def test_automatic_vector_and_prefix_destruction(self):
        self.assertEqual(len(M['authored_policy']['automatic_destruction_calls']),3)
        self.reject(lambda m:m['authored_policy']['automatic_destruction_calls'].reverse())

    def test_separate_durable_authored_record(self):
        self.assertEqual(M['authored_policy']['record']['size'],'116')
        self.reject(lambda m:m['authored_policy']['record'].update(return_count='0'))

    def test_whole_authored_cfg(self):
        self.assertEqual(M['authored_policy']['cfg'],[1,0])
        self.reject(lambda m:m['authored_policy']['instructions'].pop())

    def test_private_copy_assignment_and_short_origins_remain_unknown(self):
        self.assertEqual(len(M['retained_unknowns']),10)
        self.assertTrue({'0x004591E0','0x0045AAE0','0x004588B0'} <= {r['function']['address'] for r in M['retained_unknowns']})
        self.reject(lambda m:m['retained_unknowns'][0]['origin'].update(origin='compiler'))

    def test_full413_ordinary_emissions(self):
        self.assertEqual(len(M['public_control']['emission']),413)
        self.assertEqual(sum(r['size'] for r in M['public_control']['emission']),26626)
        self.reject(lambda m:m['public_control']['emission'].pop())

    def test_pinned_included_cpp_and_original_headers(self):
        self.assertIn('tests/origin_probes/VectorInsertionCarriers.cpp',M['public_control']['headers'])
        self.reject(lambda m:m['public_control']['headers'].pop('tests/origin_probes/VectorInsertionCarriers.cpp'))

    def test_combined_layout64_not_just_new24(self):
        self.assertEqual(M['public_control']['layout_values'],[4,16,16,4,4,16,16,16,44,16,116,16,20,68,84,100])
        self.reject(lambda m:m['public_control']['layout_values'].__setitem__(0,116))

    def test_historical_r162_snapshot_remains_original777(self):
        self.assertEqual(M['historical_snapshots'][0]['record']['size'],777)
        self.reject(lambda m:m['historical_snapshots'][0]['record']['function'].update(size='796'))

    def test_no_private_layout_abi_source_or_exact_credit(self):
        for key,value in [('source_file','game.cpp'),('signature','Private116*'),('calling_convention','cdecl'),('match_percent','100.00')]:
            self.reject(lambda m:m['functions'][0]['accepted_function'].update({key:value}))

    def test_only_four_whole_extents_change(self):
        changed={r['address'] for r in M['functions'] if r['original_function']['size']!=r['accepted_function']['size']}
        self.assertEqual(changed,{'0x005F9A10','0x00459CB0','0x00459390','0x0045B300'})
        self.reject(lambda m:m['functions'][1]['accepted_function'].update(size='167'))


if __name__=='__main__':unittest.main()
