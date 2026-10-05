"""Guard resource-lock whole extents, real fields and independent public proof."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('test_resource_lock', ROOT/'scripts/verify-sdk-resource-lock-origins.py')
V = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(V)
M = json.loads((ROOT/V.EVIDENCE).read_text())


class ResourceLockProvenanceTests(unittest.TestCase):
    def reject(self, mutate):
        m = copy.deepcopy(M); mutate(m)
        with self.assertRaises(ValueError):
            V.verify_plan(m)

    def test_original_manifest_and_bounded_plan(self):
        self.assertEqual(V.BASE.digest((ROOT/V.EVIDENCE).read_bytes()), V.MANIFEST_SHA256)
        V.verify_plan(M)

    def test_earlier_graphs_and_full_replay_are_pinned(self):
        for path, sha in M['retained_sha256'].items():
            self.assertTrue(V.retained_digest_matches(path,sha),path)

    def test_no_source_or_exact_credit(self):
        self.reject(lambda m: m['functions'][0]['accepted_function'].update(source_file='new.cpp'))
        self.reject(lambda m: m['functions'][0]['accepted_function'].update(match_percent='100.00'))

    def test_no_private_abi_or_layout_credit(self):
        self.reject(lambda m: m['functions'][1]['accepted_function'].update(signature='private-owner'))

    def test_surface_whole_extent_required(self):
        self.reject(lambda m: m['sections'][0].update(size=1042))

    def test_volume_whole_extent_required(self):
        self.reject(lambda m: m['sections'][1].update(size=858))

    def test_no_hidden_source_jump_table(self):
        self.reject(lambda m: m['sections'][0]['flow'].update(table_size=4))

    def test_every_real_field_required(self):
        self.reject(lambda m: m['sections'][0]['fields'].pop())

    def test_every_real_binding_required(self):
        self.reject(lambda m: m['sections'][1]['bindings'].pop())

    def test_no_guessed_guid_substitution(self):
        self.reject(lambda m: m['sections'][0]['bindings'][2].update(target_address='0x0065C3CC'))

    def test_original_three_guid_carriers_required(self):
        self.reject(lambda m: m['sections'].pop())

    def test_guid_cannot_be_truncated(self):
        self.reject(lambda m: m['sections'][2].update(size=12))

    def test_actual_thiscall_cleanup_required(self):
        self.reject(lambda m: m['sections'][0]['flow']['returns'][0].update(cleanup=28))

    def test_complete_public_layout_required(self):
        self.reject(lambda m: m['public_control']['layout']['values'].__setitem__(0,28))

    def test_all_public_controls_required(self):
        self.reject(lambda m: m['public_control']['emission'].pop())

    def test_no_codec_or_constructor_credit(self):
        self.reject(lambda m: m['functions'].append(copy.deepcopy(m['functions'][0])))


if __name__=='__main__':
    unittest.main()
