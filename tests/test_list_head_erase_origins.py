"""Guard complete list recovery extents and preserved alternative ownership."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('list_head_tests', ROOT / 'scripts/verify-list-head-erase-origins.py')
V = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(V)
M = json.loads((ROOT / V.EVIDENCE).read_text())


class ListHeadEraseTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.c = V.module('head_test_target', 'compare-coff-function.py')
        cls.target = cls.c.verified_target()
        cls.flow = V.module('head_test_flow', 'sdk_image_carriers.py')

    def reject(self, change, native=False):
        m = copy.deepcopy(M); change(m)
        with self.assertRaises(ValueError):
            if native: V.verify_native(m, self.target, self.c, self.flow)
            else: V.verify_plan(m)

    def test_complete_plan_and_all_retained_pins(self):
        V.verify_plan(M)
        self.assertEqual(V.digest((ROOT / V.EVIDENCE).read_bytes()), V.MANIFEST_SHA256)
        for path, sha in M['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT / path).read_bytes()), sha, path)

    def test_only_head_extent_changes_and_interior_has_no_unique_credit(self):
        self.assertEqual(sum(r['size'] for r in M['functions']), 751)
        self.assertEqual(sum(r['size'] for r in M['functions'] if not r['source_offset']), 671)
        changes = [(r['address'], r['original_function']['size'], r['accepted_function']['size'])
                   for r in M['functions'] if r['original_function']['size'] != r['accepted_function']['size']]
        self.assertEqual(changes, [('0x00531F30', '143', '223')])
        self.reject(lambda m: m['extent'].update(unique_policy_bytes=751))

    def test_full_native_head_recovery_parent_and_protected_leaves(self):
        V.verify_native(M, self.target, self.c, self.flow)

    def test_recovery_cannot_escape_source_owner(self):
        self.reject(lambda m: next(r for r in m['functions'] if r['source_offset']).update(source_offset=142), True)
        self.reject(lambda m: next(r for r in m['functions'] if r['source_offset']).update(source_owner='0x00531C00'), True)

    def test_real_ret_and_entire_shared_exit_are_required(self):
        self.reject(lambda m: next(r for r in m['functions'] if r['source_offset'])['instructions'].pop(), True)
        self.reject(lambda m: next(r for r in m['functions'] if r['source_offset'])['instructions'][-1].update(operands='4'), True)

    def test_alignment_is_exactly_one_cc(self):
        self.reject(lambda m: m['extent']['alignment'].update(hex='cccc'), True)
        self.reject(lambda m: m['extent']['next_owner'].update(size=99))

    def test_actual_local_eh_definition_and_all_roots(self):
        self.reject(lambda m: m['recovery']['definition'].update(storage=2))
        self.reject(lambda m: m['recovery']['eh_field'].update(symbol_index=0))
        self.reject(lambda m: next(r for r in m['sections'] if r['base']=='0x00531F30')['roots'].pop())

    def test_full_source_aux_and_fields_cannot_be_masked(self):
        self.reject(lambda m: m['sections'][0]['source']['aux_records'].pop())
        self.reject(lambda m: m['sections'][0]['bindings'].pop())
        self.reject(lambda m: m['sections'][0]['fields'].pop())

    def test_both_actual_weak_records_and_strong_owners_required(self):
        self.assertEqual(len(M['weak_references']), 2)
        self.reject(lambda m: m['weak_references'].pop())

    def test_ambiguous_getters_and_empty_destroy_keep_unknown(self):
        self.assertEqual({r['address'] for r in M['retained_unknowns']},
                         {'0x00531D80','0x00531D90','0x00532350','0x00532480','0x00532500'})
        self.assertTrue(all(r['origin']['origin']=='unknown' for r in M['retained_unknowns']))
        self.reject(lambda m: m['retained_unknowns'][0]['origin'].update(origin='library'))

    def test_all64_old_literal_snapshots_stay_immutable(self):
        self.assertEqual(len(M['historical_snapshots']), 64)
        self.reject(lambda m: m['historical_snapshots'][0]['record']['origin'].update(origin='library'))

    def test_source_alternatives_keep_complete_original_public_controls(self):
        self.assertEqual([len(r['controls']) for r in M['alternatives']], [6,12])
        self.reject(lambda m: m['alternatives'][0]['controls'].pop())

    def test_no_private_source_abi_or_exact_credit(self):
        for key, value in [('source_file','game.cpp'),('signature','PrivateNode*'),('calling_convention','cdecl'),('match_percent','100.00')]:
            self.reject(lambda m: m['functions'][0]['accepted_function'].update({key:value}))

    def test_complete_source_catalog_rejects_native_address_override(self):
        row=M['sections'][0];d=next(d for d in row['source']['definitions'] if d['storage']==2)
        with self.assertRaises(ValueError): V.SOURCE.owned_catalog([row],{d['symbol']:1},0,[])
        with self.assertRaises(ValueError): V.SOURCE.owned_catalog([row]*2,{},0,[])

    def test_retained_whole_vtable_preserves_interior_address_point(self):
        coff=V.module('head_test_coff','coff_data.py')
        V.prior_catalog(M,self.target,self.c,coff)
        r=next(r['record'] for r in M['prior']['external'] if r['record']['symbol']=='??_7type_info@@6B@')
        self.assertEqual(int(r['address'],16)-int(r['record']['target_address'],16),4)
        self.assertEqual(r['size'],8)


if __name__=='__main__':unittest.main()
