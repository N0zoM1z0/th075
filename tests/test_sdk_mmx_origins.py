"""Reject partial MMX provenance and changes to the independently accepted helper."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
SPEC=importlib.util.spec_from_file_location('test_sdk_mmx',ROOT/'scripts/verify-sdk-mmx-origins.py')
V=importlib.util.module_from_spec(SPEC);SPEC.loader.exec_module(V)
M=json.loads((ROOT/V.EVIDENCE).read_text())


class MmxEvidenceTests(unittest.TestCase):
    def reject(self,mutate):
        m=copy.deepcopy(M);mutate(m)
        with self.assertRaises(ValueError):V.verify_plan(m)

    def test_immutable_manifest(self):
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        V.verify_plan(M)

    def test_prior_source_evidence_is_pinned(self):
        for path,sha in M['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT/path).read_bytes()),sha,path)

    def test_no_duplicate_acceptance_for_R008_helper(self):
        self.reject(lambda m:m['functions'].append(m['functions'][0]))

    def test_helper_cannot_be_declared_noninventory(self):
        self.reject(lambda m:m['controls'][1].update(origin=None))

    def test_helper_original_origin_cannot_change(self):
        self.reject(lambda m:m['controls'][1]['origin'].update(origin='compiler'))

    def test_full_policy_not_a_prefix(self):
        self.reject(lambda m:m['controls'][0].update(size=152))

    def test_complete_cpuid_helper_required(self):
        self.reject(lambda m:m['controls'][1].update(size=36))

    def test_all_genuine_fields_required(self):
        self.reject(lambda m:m['controls'][0]['fields'].pop())

    def test_full_disable_mmx_literal_required(self):
        self.reject(lambda m:m['data'][2].update(size=10))

    def test_actual_call_to_cpuid_helper_required(self):
        self.reject(lambda m:m['controls'][0]['bindings'][9].update(target_address='0x00620B09'))

    def test_unrelated_import_cannot_replace_registry_api(self):
        self.reject(lambda m:m['imports'][0].update(name='GetVersionExA'))

    def test_no_source_or_exact_credit(self):
        self.reject(lambda m:m['functions'][0]['accepted_function'].update(source_file='invented.cpp'))
        self.reject(lambda m:m['functions'][0]['accepted_function'].update(match_percent='100.00'))


if __name__=='__main__':unittest.main()
