"""Protect explicit SDK policy from field substitution and compiler-wrapper credit."""
import copy,importlib.util,json,unittest
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('destructor_tests',ROOT/'scripts/verify-sdk-destructor-origins.py');V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)
class SDKDestructorEvidenceTests(unittest.TestCase):
    def setUp(self):self.m=json.loads((ROOT/V.EVIDENCE).read_text())
    def test_complete_scope_and_digest(self):
        V.verify_plan(self.m);self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
    def test_complete_native_extent_cannot_be_shortened(self):
        self.m['functions'][0]['size']=20
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_same_shape_does_not_substitute_interface_context(self):
        self.m['functions'][1]['source_record']=self.m['functions'][2]['source_record']
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_real_cleanup_field_cannot_be_redirected(self):
        self.m['functions'][1]['source_record']['bindings'][1]['target_address']='0x0060A535'
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_raw_pointer_default_cleanup_stays_empty(self):
        self.m['controls'][0]['calls']=[{}]
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_sdk_surface_api_slot_cannot_be_replaced(self):
        self.m['controls'][3]['api_slots']=[44]
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_public_observer_cannot_become_original_target_layout(self):
        self.m['controls'][3]['target_address']='0x00609EEF'
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_whole_generated_wrapper_is_retained(self):
        self.m['controls'][2]['size']=28
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_generated_wrapper_has_real_destructor_and_delete_routes(self):
        self.m['controls'][2]['call_symbols']=['??1ExplicitSurfaceLease@@QAE@XZ']
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_original_compiler_wrapper_set_cannot_drop_one(self):
        self.m['wrappers'].pop()
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_no_abi_or_source_credit_is_added(self):
        for key in ('calling_convention','source_file','signature','match_percent'):
            m=copy.deepcopy(self.m);m['functions'][0]['accepted_function'][key]='invented'
            with self.assertRaises(ValueError):V.verify_plan(m)
    def test_exact_old_anchor_transition_is_permitted(self):
        for r in self.m['functions']:
            self.assertTrue(V.PARENT.reviewed_destructor_anchor_matches(r['source_record'],r['original_function'],r['original_origin']))
            self.assertTrue(V.PARENT.reviewed_destructor_anchor_matches(r['source_record'],r['accepted_function'],r['accepted_origin']))
            changed=dict(r['accepted_function'],size='20');self.assertFalse(V.PARENT.reviewed_destructor_anchor_matches(r['source_record'],changed,r['accepted_origin']))
    def test_transition_cannot_promote_opaque_envmap_parent(self):
        prior=json.loads((ROOT/'config/sdk-interface-origin-evidence.json').read_text());r=next(r for r in prior['code'] if r['address']=='0x0060BE10')
        self.assertFalse(V.PARENT.reviewed_destructor_anchor_matches(r,dict(r['function'],owner='library'),dict(r['origin'],origin='library')))
    def test_transition_does_not_allow_other_origin_or_evidence(self):
        r=self.m['functions'][0]
        for key,value in [('origin','authored'),('evidence_id','invented')]:
            changed=dict(r['accepted_origin'],**{key:value});self.assertFalse(V.PARENT.reviewed_destructor_anchor_matches(r['source_record'],r['accepted_function'],changed))
if __name__=='__main__':unittest.main()
