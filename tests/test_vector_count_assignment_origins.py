"""Guard complete count-assignment provenance, scope and private lifetime limits."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('count_tests',ROOT/'scripts/verify-vector-count-assignment-origins.py')
V = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(V)
M = json.loads((ROOT/V.EVIDENCE).read_text())


class VectorCountAssignmentPlanTests(unittest.TestCase):
    def reject(self,change):
        m = copy.deepcopy(M); change(m)
        with self.assertRaises(ValueError): V.verify_plan(m)

    def test_complete_review_and_immutable_inputs(self):
        V.verify_plan(M)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        for path,sha in M['retained_sha256'].items(): self.assertEqual(V.digest((ROOT/path).read_bytes()),sha,path)

    def test_five_complete_owners414_keep_original_extents(self):
        self.assertEqual(sum(V.WHOLE.values()),414)
        self.reject(lambda m:m['functions'][0]['accepted_function'].update(size='96'))

    def test_source_declaration_cannot_earn_exact_credit(self):
        for key,value in [('source_file','PrivateValue.cpp'),('signature','PrivateValue*'),
                          ('calling_convention','thiscall'),('match_percent','100.00')]:
            self.reject(lambda m:m['functions'][0]['accepted_function'].update({key:value}))

    def test_all_actual_normal_eh_and_state_fields_are_retained(self):
        self.assertEqual((len(M['sections']),sum(r['size'] for r in M['sections']),
                          sum(len(r['fields']) for r in M['sections'])),(242,13988,590))
        self.reject(lambda m:m['sections'][0]['bindings'].pop())

    def test_source_aux_and_line_provenance_is_complete(self):
        self.assertTrue(all(r['source']['aux_records'] for r in M['sections']))
        self.reject(lambda m:m['sections'][0]['source']['aux_records'].clear())

    def test_complete_ordinary_emission_and_merged_readonly_carrier(self):
        control = M['public_control']
        self.assertEqual((len(control['emission']),sum(r['size'] for r in control['emission'])),(366,22274))
        self.assertEqual((control['layout']['size'],len(control['layout_values'])),(64,16))
        self.assertEqual(len(control['headers']),28)
        self.reject(lambda m:m['public_control']['layout_values'].pop(0))

    def test_manual_members_include_complete_eh_and_state_alternatives(self):
        self.assertEqual([g['width'] for g in M['groups']],[44,16,44,16])
        self.assertEqual([len([r for r in M['sections'] if r['group']==g['id']]) for g in M['groups']],[61,61,60,60])
        self.assertTrue(all(g['symbol'].startswith('?assignValue@') for g in M['groups'][2:]))
        self.reject(lambda m:m['groups'].pop())

    def test_source_owned_catalog_rejects_omitted_local_eh_owner(self):
        scoped = copy.deepcopy([r for r in M['sections'] if r['group']==0])
        local = next(f for r in scoped for f in r['fields'] if f['symbol_storage']==3 and f['symbol_section']>0)
        scoped = [r for r in scoped if r['source']['section'] != local['symbol_section']]
        with self.assertRaises(ValueError): V.SOURCE.owned_catalog(scoped,{},0,M['weak_references'])

    def test_actual_weak_fallback_cannot_be_replaced_by_name(self):
        self.assertTrue(M['weak_references'])
        self.reject(lambda m:m['weak_references'][0].update(fallback_symbol='invented'))

    def test_four_complete_game_parents_and_argument_windows(self):
        self.assertEqual(sum(r['size'] for r in M['parents']),2295)
        self.assertEqual([r['call_sequences'][0]['site'] for r in M['parents']],
                         ['0x0040B06F','0x0040B18A','0x0040B212','0x005F73D1'])
        self.reject(lambda m:m['parents'][-1]['call_sequences'][0]['instructions'].pop())

    def test_implicit_value_copies_have_no_range_policy(self):
        self.assertEqual([r['source']['size'] for r in M['implicit_controls']],[22,33])
        self.assertFalse(any(r['fields'] for r in M['implicit_controls']))
        self.reject(lambda m:m['implicit_controls'].pop())

    def test_all43_historical_unknown_snapshots_remain_literal(self):
        self.assertEqual(len(M['historical_snapshots']),43)
        self.assertTrue(all(q['record']['origin']['origin']=='unknown' for q in M['historical_snapshots']))
        self.reject(lambda m:m['historical_snapshots'][0]['record']['origin'].update(origin='library'))

    def test_four_private_lifetime_declarations_remain_unknown(self):
        self.assertEqual([q['function']['address'] for q in M['retained_unknowns']],
                         ['0x0040D8E0','0x004588B0','0x0040F9F0','0x005FAAD0'])
        self.reject(lambda m:m['retained_unknowns'][0]['origin'].update(origin='library'))

    def test_retained_source_definition_cannot_come_from_field_observation(self):
        self.reject(lambda m:m['shared'][0]['owner']['record'].update(symbol='invented'))

    def test_alignment_does_not_expand_owner_extent(self):
        self.assertTrue(all(q['hex']=='cc'*q['size'] for q in M['boundaries']))
        self.reject(lambda m:m['boundaries'][0].update(size=1))


@unittest.skipUnless((ROOT/'resources/th075.exe').is_file(),'private pinned target is not supplied')
class VectorCountAssignmentNativeTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.c=V.module('count_test_target','compare-coff-function.py'); cls.target=cls.c.verified_target()
        cls.flow=V.module('count_test_flow','sdk_image_carriers.py')

    def test_whole_game_receiver_count_value_and_target_policies(self):
        V.verify_native(M,self.target,self.c,self.flow)

    def test_truncated_native_policy_and_wrong_game_receiver_are_rejected(self):
        for change in [lambda m:m['functions'][0].update(size=96),
                       lambda m:m['parents'][0]['instructions'][0].update(operands='wrong')]:
            m=copy.deepcopy(M);change(m)
            with self.assertRaises(ValueError): V.verify_native(m,self.target,self.c,self.flow)


if __name__=='__main__': unittest.main()
