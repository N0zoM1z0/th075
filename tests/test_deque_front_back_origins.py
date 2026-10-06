"""Guard complete deque end access and strictly bounded historical transitions."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('ends_tests',ROOT/'scripts/verify-deque-front-back-origins.py')
V = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(V)
M = json.loads((ROOT/V.EVIDENCE).read_text())
OLD = V.module('ends_previous','verify-unchecked-indexing-origins.py')
PREVIOUS = json.loads((ROOT/OLD.EVIDENCE).read_text())


class DequeFrontBackPlanTests(unittest.TestCase):
    def reject(self,change):
        m=copy.deepcopy(M);change(m)
        with self.assertRaises(ValueError): V.verify_plan(m)

    def test_immutable_inputs_and_complete_review(self):
        V.verify_plan(M)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        for path,sha in M['retained_sha256'].items():self.assertEqual(V.digest((ROOT/path).read_bytes()),sha,path)

    def test_nine_complete_extents365(self):
        self.assertEqual(sum(V.WHOLE.values()),365)
        self.reject(lambda m:m['functions'][0]['accepted_function'].update(size='31'))
        self.assertEqual(V.WHOLE['0x004099E0'],35)
        self.assertEqual(V.WHOLE['0x00409A10'],41)
        self.assertEqual(V.WHOLE['0x0040A170'],32)

    def test_no_private_source_abi_or_exact_credit(self):
        for key,value in [('source_file','Owner.cpp'),('signature','Owner*'),
                          ('calling_convention','thiscall'),('match_percent','100.00')]:
            self.reject(lambda m:m['functions'][0]['accepted_function'].update({key:value}))

    def test_full_source_scopes_and_all_actual_fields(self):
        self.assertEqual((len(M['sections']),sum(r['size'] for r in M['sections']),
                          sum(len(r['fields']) for r in M['sections'])),(102,4192,90))
        self.reject(lambda m:m['sections'][0]['bindings'].pop())

    def test_whole_coff_aux_and_debug_lines(self):
        self.assertTrue(all(r['source']['aux_records'] for r in M['sections']))
        self.reject(lambda m:m['sections'][0]['source']['aux_records'].clear())

    def test_entire_emission_and_readonly_observation(self):
        control=M['public_control']
        self.assertEqual((len(control['emission']),sum(r['size'] for r in control['emission']),
                          sum(len(r['fields']) for r in control['emission'])),(88,2873,105))
        self.assertEqual(control['layout_values'],[4,8,64,20,20,20,8,8,4,4])
        self.assertEqual((control['layout']['size'],len(control['headers'])),(40,27))
        self.reject(lambda m:m['public_control']['layout_values'].pop())

    def test_full_manual_member_alternatives_are_byte_equal(self):
        for original,manual in zip(M['groups'][:6],M['groups'][6:]):
            self.assertEqual(original['role'],'original-header')
            self.assertEqual(manual['role'],'manual-member')
            self.assertTrue(manual['symbol'].startswith(('?first@?$ManualEnds','?last@?$ManualEnds')))
            left=[r for r in M['sections'] if r['group']==original['id']]
            right=[r for r in M['sections'] if r['group']==manual['id']]
            self.assertEqual([(r['base'],r['size'],r['body_sha256']) for r in left],
                             [(r['base'],r['size'],r['body_sha256']) for r in right])
        self.reject(lambda m:m['groups'].pop())

    def test_missing_defining_begin_cannot_be_replaced_by_field_destination(self):
        scoped=[r for r in M['sections'] if r['group']==0]
        root=scoped[0];begin=next(r for r in scoped if r['symbol'].startswith('?begin@'))
        catalog=V.SOURCE.owned_catalog([r for r in scoped if r is not begin],{},0,[])
        self.assertNotIn(begin['symbol'],catalog)
        with self.assertRaises(ValueError):
            V.SOURCE.BASE.BASE.bind_fields(bytes(root['size']),root['fields'],root['bindings'],catalog,0,
                                          int(root['base'],16))

    def test_const_and_compatible_abi_predecrement_routes_stay_distinct(self):
        self.assertEqual([q['kind'] for q in M['negative_controls']],
                         ['const-route']*6+['predecrement-route']*3+['wrong-width']*3)
        previous=M['negative_controls'][6:9]
        self.assertEqual([r['size'] for r in previous],[41]*3)
        self.assertTrue(all(r['symbol'].startswith('?lastByDecrement@?$ManualEnds') for r in previous))
        self.reject(lambda m:m['negative_controls'][6].update(native_size=41))

    def test_whole_stride_and_block_policies_are_not_truncated(self):
        self.assertEqual([g['width'] for g in M['groups'][:6]],[64,64,4,4,8,4])
        self.assertEqual([q['size'] for q in M['negative_controls'][9:]],[83,89,87])
        self.reject(lambda m:m['negative_controls'][-1].update(native_size=32))

    def test_fourteen_whole_game_parents_and_all90_receiver_windows(self):
        self.assertEqual((len(M['parents']),sum(r['size'] for r in M['parents']),
                          sum(len(r['call_sequences']) for r in M['parents'])),(14,6811,90))
        self.assertEqual({w['target'] for r in M['parents'] for w in r['call_sequences']},
                         {g['root'] for g in M['groups'][:6]})
        self.reject(lambda m:m['parents'][-1]['call_sequences'][0]['instructions'].pop())

    def test_two_original_unknown_snapshots_remain_literal(self):
        self.assertEqual(len(M['historical_snapshots']),2)
        self.assertTrue(all(q['path']=='config/unchecked-indexing-origin-evidence.json'
                            and q['record']['origin']['origin']=='unknown' for q in M['historical_snapshots']))
        self.assertEqual(len(M['header_definitions']),5)
        self.reject(lambda m:m['historical_snapshots'][0]['record']['origin'].update(origin='library'))

    def test_separate_private_lifetime_policies_remain_unknown(self):
        self.assertEqual(len(M['retained_unknowns']),16)
        self.reject(lambda m:m['retained_unknowns'][0]['origin'].update(origin='library'))

    def test_adjacent_constructor_and_external_alignment_are_preserved(self):
        self.assertTrue(all(q['hex']=='cc'*q['size'] for q in M['boundaries']))
        adjacent=next(q for q in M['boundaries'] if q['address']=='0x0040A190')
        self.assertEqual(adjacent['size'],0)
        self.assertEqual(adjacent['next_owner'],'0x0040A190')
        self.reject(lambda m:m['boundaries'][0].update(size=1))

    def test_prior_verifier_allows_only_literal_original_to_accepted_successors(self):
        for address in ['0x0041DB80','0x0041DE00']:
            row=next(r for r in M['functions'] if r['address']==address)
            old=next(q for q in PREVIOUS['canonical'] if q['function']['address']==address)
            accepted=dict(function=row['accepted_function'],origin=row['accepted_origin'])
            self.assertEqual(OLD.retained_state(old,old),old)
            self.assertEqual(OLD.retained_state(old,accepted),accepted)
            changed=copy.deepcopy(accepted);changed['function']['match_percent']='100.00'
            with self.assertRaises(ValueError):OLD.retained_state(old,changed)
            rewritten=copy.deepcopy(old);rewritten['function']['notes']='changed'
            with self.assertRaises(ValueError):OLD.retained_state(rewritten,accepted)

    def test_prior_verifier_rejects_unrelated_retained_changes(self):
        old=next(q for q in PREVIOUS['canonical'] if q['function']['address'] not in ['0x0041DB80','0x0041DE00'])
        changed=copy.deepcopy(old);changed['origin']['confidence']='changed'
        with self.assertRaises(ValueError):OLD.retained_state(old,changed)


@unittest.skipUnless((ROOT/'resources/th075.exe').is_file(),'private pinned target is not supplied')
class DequeFrontBackNativeTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.c=V.module('ends_test_target','compare-coff-function.py');cls.target=cls.c.verified_target()
        cls.flow=V.module('ends_test_flow','sdk_image_carriers.py')

    def test_complete_native_policies_and_whole_game_contexts(self):
        V.verify_native(M,self.target,self.c,self.flow)

    def test_shortened_policy_and_changed_receiver_are_rejected(self):
        for change in [lambda m:m['functions'][0].update(size=31),
                       lambda m:m['parents'][0]['instructions'][0].update(operands='wrong')]:
            m=copy.deepcopy(M);change(m)
            with self.assertRaises(ValueError):V.verify_native(m,self.target,self.c,self.flow)


if __name__=='__main__':unittest.main()
