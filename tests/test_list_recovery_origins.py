"""Guard actual source-local list recovery ownership and complete shared exits."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('list_recovery_tests',ROOT/'scripts/verify-list-recovery-origins.py')
V = importlib.util.module_from_spec(SPEC);SPEC.loader.exec_module(V)
M = json.loads((ROOT/V.EVIDENCE).read_text())


class ListRecoveryTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.c=V.module('recovery_test_target','compare-coff-function.py')
        cls.target=cls.c.verified_target()
        cls.flow=V.module('recovery_test_flow','sdk_image_carriers.py')

    def reject(self,change,native=False):
        m=copy.deepcopy(M);change(m)
        with self.assertRaises(ValueError):
            if native:V.verify_native(m,self.target,self.c,self.flow)
            else:V.verify_plan(m)

    def test_complete_plan_and_retained_original_pins(self):
        V.verify_plan(M)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        for path,sha in M['retained_sha256'].items():self.assertEqual(V.digest((ROOT/path).read_bytes()),sha,path)

    def test_four_interiors_keep_all_existing_parent_extents(self):
        self.assertEqual(sum(r['size'] for r in M['functions']),236)
        self.assertEqual([int(r['parent_function']['size']) for r in M['recoveries']],[223,189,186,186])
        self.assertTrue(all(r['original_function']['size']==r['accepted_function']['size'] for r in M['functions']))
        self.reject(lambda m:m['recoveries'][0]['parent_function'].update(size='143'))

    def test_actual_local_definitions_are_not_standalone_primaries(self):
        self.assertEqual([r['definition']['offset'] for r in M['recoveries']],[143,137,134,134])
        self.reject(lambda m:m['recoveries'][0]['definition'].update(storage=2))
        self.reject(lambda m:m['recoveries'][1]['definition'].update(type=0))

    def test_actual_eh_indices_sections_offsets_and_addends(self):
        self.assertEqual([r['eh_field']['offset'] for r in M['recoveries']],[28,36,36,36])
        for key,value in [('symbol_index',0),('symbol_section',1),('symbol_offset',133),('addend',1)]:
            self.reject(lambda m:m['recoveries'][2]['eh_field'].update({key:value}))

    def test_all_normal_recovery_and_handler_roots_are_preserved(self):
        roots=[next(r for r in M['sections'] if r['group']==g['id'] and r['base']==g['root'])['roots'] for g in M['groups']]
        self.assertEqual(roots,[[0,143],[0,137],[0,134],[0,134]])
        self.reject(lambda m:m['sections'][0]['roots'].pop())

    def test_entire_native_recoveries_shared_exits_and_next_owners(self):
        V.verify_native(M,self.target,self.c,self.flow)

    def test_recovery_cannot_detach_from_its_source_owner(self):
        self.reject(lambda m:m['functions'][0].update(source_owner='0x004123E0'),True)
        self.reject(lambda m:m['functions'][1].update(source_offset=136),True)

    def test_shared_normal_exit_not_cropped_at_rethrow(self):
        self.reject(lambda m:m['recoveries'][1].update(common_exit='0x004122E2'),True)
        self.reject(lambda m:m['functions'][2]['instructions'].pop(),True)

    def test_value_node_ret12_and_head_ret0_are_actual(self):
        self.reject(lambda m:m['functions'][0]['instructions'][-1].update(operands='0xc'),True)
        self.reject(lambda m:m['functions'][3]['instructions'][-1].update(operands='8'),True)

    def test_alignment_remains_outside_owners(self):
        self.assertEqual([r['alignment_size'] for r in M['boundaries']],[1,3,6,6])
        self.reject(lambda m:m['boundaries'][0].update(alignment_size=2),True)
        self.reject(lambda m:m['boundaries'][1]['next_owner']['instructions'].pop(),True)

    def test_all_actual_fields_and_complete_aux_lines(self):
        self.assertEqual((len(M['sections']),sum(len(r['fields']) for r in M['sections'])),(40,85))
        self.reject(lambda m:m['sections'][0]['fields'].pop())
        self.reject(lambda m:m['sections'][0]['bindings'].pop())
        self.reject(lambda m:m['sections'][0]['source']['aux_records'].pop())

    def test_whole_ordinary_emission_and_readonly_observations(self):
        self.assertEqual(sum(len(g['control']['emission']) for g in M['groups']),767)
        self.assertEqual([g['control']['layout']['size'] for g in M['groups']],[56,76,88,16])
        self.reject(lambda m:m['groups'][0]['control']['emission'].pop())
        self.reject(lambda m:m['groups'][1]['control']['layout_values'].pop())

    def test63_literal_historical_unknown_snapshots_are_not_rewritten(self):
        self.assertEqual(len(M['historical_snapshots']),63)
        self.reject(lambda m:m['historical_snapshots'][0]['record']['origin'].update(origin='library'))

    def test_tiny_getters_and_empty_destroy_stay_unknown(self):
        self.assertEqual({r['address'] for r in M['retained_unknowns']},{'0x00411E80','0x00411E90','0x00412600'})
        self.reject(lambda m:m['retained_unknowns'][0]['origin'].update(origin='library'))

    def test_original_frame_registration_is_tied_to_actual_source_field(self):
        self.assertEqual(len(M['retained_frames']),4)
        self.reject(lambda m:m['retained_frames'][0]['source_binding'].update(target_address='0x00000000'))

    def test_no_source_private_abi_mapping_or_exact_credit(self):
        for key,value in [('source_file','Game.cpp'),('signature','Private*'),('calling_convention','cdecl'),('match_percent','100.00')]:
            self.reject(lambda m:m['functions'][0]['accepted_function'].update({key:value}))

    def test_source_catalog_rejects_duplicates_and_native_override(self):
        row=M['sections'][0];d=next(d for d in row['source']['definitions'] if d['storage']==2)
        with self.assertRaises(ValueError):V.SOURCE.owned_catalog([row]*2,{},0,[])
        with self.assertRaises(ValueError):V.SOURCE.owned_catalog([row],{d['symbol']:1},0,[])


if __name__=='__main__':unittest.main()
