"""Whole companion evidence must preserve source identity and mutable dispatch."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('test_sdk_companion', ROOT/'scripts/verify-sdk-companion-origins.py')
V = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(V)
M = json.loads((ROOT/V.EVIDENCE).read_text())


class CompanionEvidenceTests(unittest.TestCase):
    def reject(self, mutate):
        m=copy.deepcopy(M); mutate(m)
        with self.assertRaises(ValueError): V.verify_plan(m)

    def test_immutable_manifest(self):
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        V.verify_plan(M)

    def test_prior_source_graph_is_pinned(self):
        for path,sha in M['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT/path).read_bytes()),sha,path)

    def test_false_historical_rotation_quaternion_association(self):
        self.reject(lambda m:m['controls'][2].update(symbol='?c_D3DXMatrixRotationQuaternion@@YGPAUD3DXMATRIX@@PAU1@PBUD3DXQUATERNION@@@Z'))

    def test_missing_whole_companion(self):
        self.reject(lambda m:m['controls'].pop())

    def test_truncated_lookat_policy(self):
        self.reject(lambda m:m['controls'][1].update(size=327))

    def test_transformation_tail_cannot_be_fixed_callee(self):
        self.reject(lambda m:m['controls'][0]['flow']['external_tails'][0].update(runtime_selected=False))

    def test_transformation_wrong_source_slot(self):
        self.reject(lambda m:m['controls'][0]['fields'][0].update(addend=152))

    def test_lookat_wrong_normalize_dependency(self):
        self.reject(lambda m:m['controls'][1]['fields'][0].update(symbol='_D3DXPlaneNormalize@8'))

    def test_quaternion_operator_wrong_multiply_dependency(self):
        self.reject(lambda m:m['controls'][2]['fields'][0].update(symbol='_D3DXMatrixMultiply@12'))

    def test_missing_explicit_header_policy(self):
        self.reject(lambda m:m['header_evidence'].pop('quaternion-multiply-body'))

    def test_no_exact_credit(self):
        self.reject(lambda m:m['functions'][0]['accepted_function'].update(match_percent='100.00'))

    def test_no_source_or_private_abi_credit(self):
        self.reject(lambda m:m['functions'][0]['accepted_function'].update(signature='private table*'))


if __name__=='__main__': unittest.main()
