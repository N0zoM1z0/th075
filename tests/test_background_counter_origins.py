"""Guard game callback identity and preserve explicit/implicit SDK alternatives."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
SPEC=importlib.util.spec_from_file_location('counter_tests',ROOT/'scripts/verify-background-counter-origins.py')
V=importlib.util.module_from_spec(SPEC);SPEC.loader.exec_module(V)
M=json.loads((ROOT/V.EVIDENCE).read_text())


class CounterPlanTests(unittest.TestCase):
    def reject(self,change):
        m=copy.deepcopy(M);change(m)
        with self.assertRaises(ValueError):V.verify_plan(m)

    def test_complete_plan_and_prior_inputs(self):
        V.verify_plan(M)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        for path,sha in M['retained_sha256'].items():self.assertEqual(V.digest((ROOT/path).read_bytes()),sha,path)

    def test_four_complete_callback_extents_stay26(self):
        self.assertEqual(sum(r['size'] for r in M['functions']),104)
        self.reject(lambda m:m['functions'][0]['accepted_function'].update(size='25'))

    def test_no_source_private_layout_abi_or_exact_credit(self):
        for key,value in [('source_file','BG.cpp'),('signature','PrivateBackground*'),('calling_convention','thiscall'),('match_percent','100.00')]:
            self.reject(lambda m:m['functions'][0]['accepted_function'].update({key:value}))

    def test_six_original_sdk_lifetimes_do_not_become_library_or_compiler(self):
        self.assertEqual(len(M['reviewed_sdk']),6)
        for value in ['library','compiler']:
            self.reject(lambda m:m['reviewed_sdk'][0]['origin'].update(origin=value))
        self.reject(lambda m:m['reviewed_sdk'][1].update(decision='library'))

    def test_full_original_sdk_fields_and_sections_retained(self):
        self.assertEqual(sum(len(r['source']['fields']) for r in M['reviewed_sdk']),9)
        self.assertEqual(sum(r['source']['size'] for r in M['reviewed_sdk']),282)
        self.reject(lambda m:m['reviewed_sdk'][0]['source']['fields'].pop())

    def test_debug_source_does_not_supply_private_type_declarations(self):
        self.assertEqual(len(M['debug_observations']),5)
        self.assertFalse(any(s['name']=='.debug$T' for r in M['debug_observations'] for s in r['sections']))
        self.reject(lambda m:m['debug_observations'][0]['private_type_sections'].append(1))

    def test_whole_constructor_and_all_callback_contexts(self):
        self.assertEqual(sum(len(r['owners']) for r in M['contexts']),28)
        self.assertEqual(sum(o['size'] for r in M['contexts'] for o in r['owners']),6647)
        self.reject(lambda m:m['contexts'][0]['owners'].pop())

    def test_real_asset_paths_are_evidence_not_names(self):
        self.assertEqual([r['constructor']['witness']['asset_path'] for r in M['contexts']],
            ['data\\background\\BG00b.dat','data\\background\\BG04b.dat','data\\background\\BG06a.dat','data\\background\\BG09a.dat'])
        self.reject(lambda m:m['contexts'][0]['constructor']['witness'].update(asset_path='other.dat'))

    def test_normal_slot1_is_distinct_from_deleting_slot0(self):
        self.assertTrue(all(r['table']['slots'][1]==int(r['callback'],16) and r['table']['slots'][0]!=r['table']['slots'][1] for r in M['contexts']))
        self.reject(lambda m:m['contexts'][0]['table']['slots'].__setitem__(1,m['contexts'][0]['table']['slots'][0]))

    def test_constructor_clear_and_real_animation_readers_retained(self):
        self.assertEqual([len(r['counter_readers']) for r in M['contexts']],[2,5,4,4])
        self.reject(lambda m:m['contexts'][1]['counter_readers'].pop())

    def test_generic_reference_increment_shape_is_not_ownership(self):
        a,b=M['public_control']['methods']
        self.assertEqual(a['sha256'],b['sha256'])
        self.assertEqual(a['diagnostic_game_displacement_difference_offsets'],[12,21])
        self.assertEqual(a['policy']['field_offset'],4)
        self.reject(lambda m:m['public_control']['methods'][0]['policy'].update(field_offset=0x68))

    def test_whole_ordinary_controls_and_public_observations(self):
        self.assertEqual((len(M['public_control']['emission']),sum(r['size'] for r in M['public_control']['emission'])),(4,79))
        self.assertEqual(M['public_control']['layout_values'],[8,8,4])
        self.reject(lambda m:m['public_control']['emission'].pop())

    def test_literal_historical_unknown_snapshots_stay_immutable(self):
        self.assertEqual(len(M['historical_snapshots']),14)
        self.reject(lambda m:m['historical_snapshots'][0]['record']['function'].update(owner='library'))

    def test_alignment_and_next_owners_stay_outside_callbacks(self):
        self.assertEqual([r['size'] for r in M['boundaries']],[6,6,6,6])
        self.reject(lambda m:m['boundaries'][0].update(size=5))


@unittest.skipUnless((ROOT/'resources/th075.exe').is_file(),'private pinned target is not supplied')
class CounterNativeTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.c=V.module('counter_test_target','compare-coff-function.py');cls.target=cls.c.verified_target()
        cls.flow=V.module('counter_test_flow','sdk_image_carriers.py')

    def test_entire_native_callbacks_and_independent_context(self):
        V.verify_native(M,self.target,self.c,self.flow)

    def test_wrong_field_decrement_or_return_is_not_counter_policy(self):
        raw=bytearray(self.c.pe_bytes_at(self.target,0x449ec0,26))
        with self.assertRaises(ValueError):V.counter_policy(raw,0x449ec0,self.flow,4)
        raw[15]=2
        with self.assertRaises(ValueError):V.counter_policy(raw,0x449ec0,self.flow,0x68)
        raw=bytearray(self.c.pe_bytes_at(self.target,0x449ec0,26));raw[-1]=0xcc
        with self.assertRaises(ValueError):V.counter_policy(raw,0x449ec0,self.flow,0x68)

    def test_wrong_constructor_table_or_missing_render_context_rejected(self):
        m=copy.deepcopy(M);m['contexts'][0]['table']['address']='0x00658434'
        with self.assertRaises(ValueError):V.verify_native(m,self.target,self.c,self.flow)
        m=copy.deepcopy(M);m['contexts'][1]['counter_readers'].pop()
        with self.assertRaises(ValueError):V.verify_native(m,self.target,self.c,self.flow)


if __name__=='__main__':unittest.main()
