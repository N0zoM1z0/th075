"""Preserve whole vendor parent scope and genuinely unresolved buffer ownership."""
import importlib.util,json,copy,unittest
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('sdk_debug_tests',ROOT/'scripts/verify-sdk-debug-parent-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)
class SDKDebugParentEvidenceTests(unittest.TestCase):
    def setUp(self):self.m=json.loads((ROOT/V.EVIDENCE).read_text())
    def test_frozen_whole_scope_passes(self):
        V.verify_plan(self.m)
        self.assertEqual(V.BASE.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
    def test_pending_byte_identity_does_not_grant_library_credit(self):
        self.m['pending']['origin']['origin']='library'
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_pending_cannot_gain_acceptance_record(self):
        self.m['pending']['accepted_origin']={}
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_actual_pending_extent_is_preserved(self):
        self.m['pending']['function']['size']='37'
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_pending_complete_comparison_is_not_truncated(self):
        self.m['pending']['comparison']['size']=37
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_complete_stack_constructor_is_required(self):
        self.m['retained'][-1]['requested_symbol']='unproven'
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_typed_stack_context_cannot_be_replaced_by_name(self):
        self.m['functions'][2]['accepted_function']['notes']='a matching name'
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_previous_source_callee_cannot_be_redirected(self):
        self.m['functions'][0]['bindings'][0]['target_address']='0x00401000'
        with self.assertRaises(ValueError):V.verify_plan(self.m)
if __name__=='__main__':unittest.main()
