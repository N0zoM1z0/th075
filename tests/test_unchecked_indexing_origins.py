"""Guard whole unchecked indexing, original ownership and route/stride separation."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('index_tests',ROOT/'scripts/verify-unchecked-indexing-origins.py')
V = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(V)
M = json.loads((ROOT/V.EVIDENCE).read_text())


class UncheckedIndexingPlanTests(unittest.TestCase):
    def reject(self,change):
        m = copy.deepcopy(M); change(m)
        with self.assertRaises(ValueError): V.verify_plan(m)

    def test_complete_review_and_immutable_inputs(self):
        V.verify_plan(M)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        for path,sha in M['retained_sha256'].items(): self.assertEqual(V.digest((ROOT/path).read_bytes()),sha,path)

    def test_all_twelve_complete_extents561(self):
        self.assertEqual(sum(V.WHOLE.values()),561)
        self.reject(lambda m:m['functions'][0]['accepted_function'].update(size='48'))
        self.assertEqual(V.WHOLE['0x0042DCC0'],35)
        self.assertEqual(V.WHOLE['0x0042E2F0'],32)

    def test_source_abi_and_exact_credit_are_not_inferred(self):
        for key,value in [('source_file','Game.cpp'),('signature','Game*'),
                          ('calling_convention','thiscall'),('match_percent','100.00')]:
            self.reject(lambda m:m['functions'][0]['accepted_function'].update({key:value}))

    def test_all_source_owners_and_actual_fields_are_retained(self):
        self.assertEqual((len(M['sections']),sum(r['size'] for r in M['sections']),
                          sum(len(r['fields']) for r in M['sections'])),(128,4694,112))
        self.reject(lambda m:m['sections'][0]['bindings'].pop())

    def test_source_aux_and_line_provenance_is_complete(self):
        self.assertTrue(all(r['source']['aux_records'] for r in M['sections']))
        self.reject(lambda m:m['sections'][0]['source']['aux_records'].clear())

    def test_complete_ordinary_emission_and_whole_layout(self):
        control = M['public_control']
        self.assertEqual((len(control['emission']),sum(r['size'] for r in control['emission']),
                          sum(len(r['fields']) for r in control['emission'])),(97,3393,108))
        self.assertEqual(control['layout_values'],[4,16,116,1,4,60,16,4,4,20,8,8])
        self.assertEqual((control['layout']['size'],len(control['headers'])),(48,28))
        self.reject(lambda m:m['public_control']['layout_values'].pop())

    def test_manual_member_alternatives_are_full_and_byte_equal(self):
        for original,manual in zip(M['groups'][:8],M['groups'][8:]):
            self.assertEqual(original['role'],'original-header')
            self.assertEqual(manual['role'],'manual-member')
            self.assertTrue(manual['symbol'].startswith('?read@?$ManualIndexObservation'))
            left=[r for r in M['sections'] if r['group']==original['id']]
            right=[r for r in M['sections'] if r['group']==manual['id']]
            self.assertEqual([(r['base'],r['size'],r['body_sha256']) for r in left],
                             [(r['base'],r['size'],r['body_sha256']) for r in right])
        self.reject(lambda m:m['groups'].pop())

    def test_source_owned_catalog_cannot_use_an_omitted_begin_definition(self):
        scoped = [r for r in M['sections'] if r['group']==0]
        root = scoped[0]; begin = next(r for r in scoped if r['symbol'].startswith('?begin@'))
        catalog = V.SOURCE.owned_catalog([r for r in scoped if r is not begin],{},0,[])
        self.assertNotIn(begin['symbol'],catalog)
        with self.assertRaises(ValueError):
            V.SOURCE.BASE.BASE.bind_fields(bytes(root['size']),root['fields'],root['bindings'],catalog,0,
                                          int(root['base'],16))

    def test_const_and_wrong_width_controls_remain_distinct(self):
        self.assertEqual([q['kind'] for q in M['negative_controls']],['const-route']*6+['wrong-width']*6)
        self.assertEqual([g['width'] for g in M['groups'][:8]],[4,4,4,1,60,116,4,16])
        self.assertEqual([g['family'] for g in M['groups'][:8]],
                         ['vector','deque','deque','deque','deque','vector','vector','vector'])
        self.reject(lambda m:m['negative_controls'][-1].update(native_size=49))

    def test_all_whole_game_parents_and_receiver_index_result_windows(self):
        self.assertEqual((len(M['parents']),sum(r['size'] for r in M['parents']),
                          sum(len(r['call_sequences']) for r in M['parents'])),(7,9720,143))
        self.assertEqual({w['target'] for r in M['parents'] for w in r['call_sequences']},
                         {g['root'] for g in M['groups'][:8]})
        self.reject(lambda m:m['parents'][-1]['call_sequences'][0]['instructions'].pop())

    def test_original_header_definitions_and_previous_snapshots_are_literal(self):
        self.assertEqual(len(M['header_definitions']),10)
        self.assertEqual(M['historical_snapshots'],[])
        self.reject(lambda m:m['header_definitions'][0]['lines'].pop())

    def test_private_lifetime_and_forwarding_policies_remain_unknown(self):
        self.assertTrue(M['retained_unknowns'])
        self.reject(lambda m:m['retained_unknowns'][0]['origin'].update(origin='library'))

    def test_adjacent_owner_and_external_alignment_are_separate(self):
        self.assertTrue(all(q['hex']=='cc'*q['size'] for q in M['boundaries']))
        adjacent = next(q for q in M['boundaries'] if q['address']=='0x0042E310')
        self.assertEqual(adjacent['size'],0)
        self.assertEqual(adjacent['next_owner'],'0x0042E310')
        self.reject(lambda m:m['boundaries'][0].update(size=1))


@unittest.skipUnless((ROOT/'resources/th075.exe').is_file(),'private pinned target is not supplied')
class UncheckedIndexingNativeTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.c=V.module('index_test_target','compare-coff-function.py'); cls.target=cls.c.verified_target()
        cls.flow=V.module('index_test_flow','sdk_image_carriers.py')

    def test_whole_game_receiver_index_result_and_native_policies(self):
        V.verify_native(M,self.target,self.c,self.flow)

    def test_truncated_policy_and_wrong_receiver_are_rejected(self):
        for change in [lambda m:m['functions'][0].update(size=48),
                       lambda m:m['parents'][0]['instructions'][0].update(operands='wrong')]:
            m=copy.deepcopy(M);change(m)
            with self.assertRaises(ValueError): V.verify_native(m,self.target,self.c,self.flow)


if __name__=='__main__': unittest.main()
