"""Guard cube/volume policy scope and independent unresolved callback evidence."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
SPEC=importlib.util.spec_from_file_location('test_cube_volume',ROOT/'scripts/verify-sdk-cube-volume-origins.py')
V=importlib.util.module_from_spec(SPEC);SPEC.loader.exec_module(V)
M=json.loads((ROOT/V.EVIDENCE).read_text())


class CubeVolumeProvenanceTests(unittest.TestCase):
    def reject(self, mutate):
        m=copy.deepcopy(M);mutate(m)
        with self.assertRaises(ValueError):
            V.verify_plan(m)

    def test_original_manifest_and_plan(self):
        self.assertEqual(V.BASE.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        V.verify_plan(M)

    def test_original_shared_replay_and_previous_evidence_pinned(self):
        for path,sha in M['retained_sha256'].items():
            self.assertTrue(V.retained_digest_matches(path,sha),path)

    def test_no_constructor_credit_from_factory(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['base']=='0x0060B728')['origin'].update(origin='library'))

    def test_no_credit_for_noninventory_face(self):
        self.reject(lambda m:m['opaque'][0].update(origin={'origin':'library'}))

    def test_original_end_ownership_remains_independent(self):
        self.reject(lambda m:m['opaque'][1]['origin'].update(origin='library'))

    def test_prior_partial_callback_comparison_cannot_be_replaced(self):
        self.reject(lambda m:m['opaque'][1].update(bindings=[]))

    def test_no_source_or_exact_credit(self):
        self.reject(lambda m:m['functions'][0]['accepted_function'].update(source_file='new.cpp'))
        self.reject(lambda m:m['functions'][0]['accepted_function'].update(match_percent='100.00'))

    def test_no_private_abi_declaration(self):
        self.reject(lambda m:m['functions'][-1]['accepted_function'].update(signature='private-owner'))

    def test_whole_cube_creation_required(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['base']=='0x00605BC7').update(size=94))

    def test_every_real_field_required(self):
        self.reject(lambda m:m['sections'][0]['fields'].pop())

    def test_every_independent_binding_required(self):
        self.reject(lambda m:m['sections'][0]['bindings'].pop())

    def test_cube_wrapper_cannot_call_volume_requirement(self):
        self.reject(lambda m:m['sections'][2]['bindings'][0].update(target_address='0x00605B38'))

    def test_whole_original_env_vtable_required(self):
        self.reject(lambda m:m['data_anchors'][0]['record'].update(size=48))

    def test_public_env_desc_has_no_invented_mip_field(self):
        self.reject(lambda m:m['public_control']['layout']['values'].__setitem__(2,20))

    def test_all_natural_public_controls_required(self):
        self.reject(lambda m:m['public_control']['emission'].pop())


if __name__=='__main__':
    unittest.main()
