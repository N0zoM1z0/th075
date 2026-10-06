"""Guard whole archived SDK wrappers, defining routes and cold compatibility scope."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('sdk_wrapper_tests', ROOT/'scripts/verify-sdk-public-wrapper-origins.py')
V = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(V)
M = json.loads((ROOT/V.EVIDENCE).read_text())


class SdkPublicWrapperTests(unittest.TestCase):
    def reject(self, change):
        m = copy.deepcopy(M); change(m)
        with self.assertRaises(ValueError): V.verify_plan(m)

    def test_immutable_source_proof_and_five_whole_roots(self):
        V.verify_plan(M)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()), V.MANIFEST_SHA256)
        for path, sha in M['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT/path).read_bytes()), sha, path)
        self.assertEqual(sum(V.WHOLE.values()), 179)
        self.reject(lambda m: m['functions'][0]['accepted_function'].update(size='50'))
        self.reject(lambda m: m['functions'][0]['instructions'].pop())

    def test_no_private_source_abi_mapping_or_exact_credit(self):
        for key, value in [('source_file', 'Owner.cpp'), ('signature', 'Owner*'),
                           ('calling_convention', 'stdcall'), ('match_percent', '100.00')]:
            self.reject(lambda m: m['functions'][0]['accepted_function'].update({key: value}))
        for r in M['functions']:
            self.assertEqual(r['accepted_function']['current_name'], r['original_function']['current_name'])

    def test_complete_original_aux_actual_fields_and_cfgs(self):
        self.assertEqual(sum(len(r['fields']) for r in M['functions']), 6)
        self.assertTrue(all(r['source']['aux_records'] for r in M['functions']))
        self.reject(lambda m: m['functions'][0]['source']['aux_records'].clear())
        self.reject(lambda m: m['functions'][0]['bindings'].pop())
        self.reject(lambda m: m['functions'][0]['flow'].clear())

    def test_static_helper_fields_keep_actual_member_section_index_keys(self):
        r = M['functions'][1]; f = r['fields'][0]
        catalog = V.provider_catalog(M, [f], r['member_offset'], {})
        self.assertEqual(catalog[(r['member_offset'], f['symbol_section'], f['symbol_index'])], 0x6054ef)
        self.assertNotIn(f['symbol'], catalog)
        for field in ['symbol_section', 'symbol_offset', 'symbol_type', 'symbol_storage']:
            mutated = dict(f); mutated[field] += 1
            with self.assertRaises(ValueError): V.provider_catalog(M, [mutated], r['member_offset'], {})

    def test_call_destination_cannot_supply_a_missing_defining_owner(self):
        r = M['functions'][1]; f = r['fields'][0]
        m = copy.deepcopy(M)
        m['providers'] = [q for q in m['providers'] if q['record']['symbol'] != f['symbol']]
        with self.assertRaises(ValueError): V.provider_catalog(m, [f], r['member_offset'], {})
        m = copy.deepcopy(M)
        owner = next(q for q in m['providers'] if q['record']['symbol'] == f['symbol'])
        owner['record']['source']['definitions'] = []
        with self.assertRaises(ValueError): V.provider_catalog(m, [f], r['member_offset'], {})

    def test_gdi_import_is_logically_named_and_unique(self):
        r = M['functions'][0]; f = r['fields'][0]
        actual = {0x657034: ('GDI32.dll', 'GetObjectA')}
        self.assertEqual(V.provider_catalog(M, [f], r['member_offset'], actual)[f['symbol']], 0x657034)
        for imports in [{}, {0x657034: ('GDI32.dll', 'GetObjectW')},
                        {0x657034: ('USER32.dll', 'GetObjectA')},
                        dict(actual, **{} ) | {0x657038: ('GDI32.dll', 'GetObjectA')}]:
            with self.assertRaises(ValueError): V.provider_catalog(M, [f], r['member_offset'], imports)

    def test_entire_ordinary_wrappers_are_byte_equal_with_independent_routes(self):
        self.assertEqual(sorted(r['size'] for r in M['ordinary_controls']), [32, 32, 32, 32, 51])
        self.assertTrue(all(r['unmasked_byte_equal'] and r['size'] == r['native_size'] for r in M['ordinary_controls']))
        for q in M['ordinary_controls']:
            original = next(r for r in M['functions'] if r['address'] == q['native'])
            self.assertEqual(q['native_sha256'], original['body_sha256'])
            self.assertEqual(len(q['fields']), len(original['fields']))
        self.reject(lambda m: m['ordinary_controls'][0]['bindings'].clear())

    def test_full_surface_volume_and_encoding_peer_controls(self):
        self.assertEqual([q['kind'] for q in M['peer_controls']], ['wrong-surface-volume', 'wrong-A-W']*4)
        self.assertTrue(all(q['size'] == 32 and len(q['fields']) == 1 for q in M['peer_controls']))
        self.assertTrue(all(q['whole_differences'] == [4] for q in M['peer_controls'] if q['kind'] == 'wrong-A-W'))
        self.reject(lambda m: m['peer_controls'][0]['bindings'].clear())
        self.reject(lambda m: m['peer_controls'][0]['whole_differences'].clear())

    def test_full_cold_sdk_emission_public_declarations_and_layout(self):
        c = M['public_control']; em = c['emission']
        self.assertEqual((len(em), sum(r['size'] for r in em), sum(len(r['fields']) for r in em)), (11, 330, 11))
        self.assertEqual((len(c['headers']), c['layout_values']), (88, [60, 16, 24, 4, 4, 28, 4, 4]))
        self.assertEqual({r['api'] for r in M['clients']}, {r['symbol'] for r in M['functions']})
        self.reject(lambda m: m['public_control']['layout_values'].pop())
        self.reject(lambda m: m['clients'].pop())

    def test_full_prior_graphs_and_all_literal_old_inputs_retained(self):
        self.assertEqual(sum(r['record']['size'] for r in M['providers']), 463)
        paths = {p['path']: p for p in M['providers']}
        self.assertEqual(len(paths), 2)
        for path, p in paths.items():
            old = V.module('wrapper_prior_test_'+str(len(path)), Path(p['script']).name)
            original = json.loads((ROOT/path).read_text()); old.verify_plan(original)
            self.assertEqual(V.metadata_digest(original), p['plan_sha256'])
            self.assertEqual(original['sections'][p['section_index']], p['record'])
        self.reject(lambda m: m['providers'][0]['record'].update(size=110))

    def test_no_old_selected_snapshot_or_extra_origin_credit(self):
        self.assertFalse(M['historical_snapshots'])
        self.assertEqual(len(M['functions']), 5)
        self.assertEqual(len(M['canonical']), 11)
        self.reject(lambda m: m['functions'].pop())

    def test_adjacent25_constructor_is_complete_code_not_padding_or_selected_extent(self):
        r = M['adjacent_carriers'][0]
        self.assertEqual((r['address'], r['size'], r['symbol']), ('0x006055E2', 25, '??0D3DXVECTOR3@@QAE@MMM@Z'))
        self.assertFalse(r['fields'])
        self.assertNotIn(r['address'], V.WHOLE)
        self.assertEqual([r['size'] for r in M['boundaries']], [0, 0, 25, 0, 0])
        self.assertEqual(M['boundaries'][2]['kind'], 'complete-noninventory-code')
        self.reject(lambda m: m['boundaries'][2].update(kind='alignment'))
        self.reject(lambda m: m['functions'][2]['accepted_function'].update(size='57'))


@unittest.skipUnless((ROOT/'resources/th075.exe').is_file(), 'private pinned target is not supplied')
class SdkPublicWrapperNativeTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.c = V.module('wrapper_test_target', 'compare-coff-function.py')
        cls.coff = V.module('wrapper_test_coff', 'coff_data.py')
        cls.flow = V.module('wrapper_test_flow', 'sdk_image_carriers.py')
        cls.target = cls.c.verified_target()

    def test_complete_native_and_archived_wrappers(self):
        V.verify_native(M, self.target, self.c, self.flow)
        V.verify_archived(M, self.target, self.c, self.coff, self.flow)

    def test_wrong_encoded_call_owner_or_whole_extent_is_rejected(self):
        for change in [lambda m: m['functions'][1]['bindings'][0].update(source_base='0x006056CE', target_address='0x006056CE'),
                       lambda m: m['functions'][1].update(size=31),
                       lambda m: m['boundaries'][2].update(kind='alignment', hex='cc'*25)]:
            m = copy.deepcopy(M); change(m)
            with self.assertRaises(ValueError):
                V.verify_native(m, self.target, self.c, self.flow)
                V.verify_archived(m, self.target, self.c, self.coff, self.flow)


if __name__ == '__main__': unittest.main()
