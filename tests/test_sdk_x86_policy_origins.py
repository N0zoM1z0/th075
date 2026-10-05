import copy
import hashlib
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('test_sdk_x86_policy', ROOT / 'scripts/verify-sdk-x86-policy-origins.py')
verify = importlib.util.module_from_spec(spec)
spec.loader.exec_module(verify)


class SDKX86PolicyTests(unittest.TestCase):
    def setUp(self):
        self.m = json.loads((ROOT / verify.EVIDENCE).read_text())

    def reject(self, mutate):
        m = copy.deepcopy(self.m); mutate(m)
        with self.assertRaises(ValueError):
            verify.verify_plan(m)

    def test_whole_scoped_policy_and_immutable_manifest(self):
        verify.verify_plan(self.m)
        self.assertEqual(hashlib.sha256((ROOT / verify.EVIDENCE).read_bytes()).hexdigest(), verify.MANIFEST_SHA256)

    def test_lookup_table_cannot_drop_neighboring_source_definitions(self):
        self.reject(lambda m: m['data'][0].update(size=4096))

    def test_initialized_writable_table_is_not_called_readonly(self):
        self.reject(lambda m: m['data'][0].update(writable=False))

    def test_full_original_carrier_cannot_be_cut_to_one_slot(self):
        self.reject(lambda m: m['carrier'].update(size=32, fields=m['carrier']['fields'][:8]))

    def test_original_observed_pointer_carrier_is_not_independent_linkage(self):
        self.reject(lambda m: m['carrier'].update(target_positive=True))

    def test_initializer_retains_eight_separate_source_implementations(self):
        self.reject(lambda m: m['controls'][0]['bindings'][0].update(target_address=m['controls'][0]['bindings'][1]['target_address']))

    def test_same_table_field_does_not_erase_actual_plus_four_addend(self):
        self.reject(lambda m: m['controls'][2]['fields'][1].update(addend=0))

    def test_registry_call_requires_original_advapi_identity(self):
        self.reject(lambda m: m['imports'][0].update(dll='KERNEL32.dll'))

    def test_pending_public_entry_cannot_gain_false_positive_binding(self):
        self.reject(lambda m: m['pending'][0].update(bindings=[]))

    def test_cpu_selector_scope_cannot_be_promoted(self):
        self.reject(lambda m: m['cpu_context']['origin'].update(origin='library'))

    def test_vendor_origin_cannot_invent_game_abi_or_source(self):
        self.reject(lambda m: m['functions'][0]['accepted_function'].update(calling_convention='thiscall'))

    def test_non_inventory_controls_do_not_expand_canonical_cohort(self):
        self.reject(lambda m: m['functions'].append(m['controls'][3]))


if __name__ == '__main__':
    unittest.main()
