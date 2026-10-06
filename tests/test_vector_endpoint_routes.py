"""Guard complete endpoint routes and bounded historical canonical projections."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('endpoint_tests',ROOT/'scripts/verify-vector-endpoint-route-origins.py')
V = importlib.util.module_from_spec(SPEC);SPEC.loader.exec_module(V)
M = json.loads((ROOT/V.EVIDENCE).read_text())


class VectorEndpointRouteTests(unittest.TestCase):
    def reject(self,change):
        m=copy.deepcopy(M);change(m)
        with self.assertRaises(ValueError):V.verify_plan(m)

    def test_immutable_current_and_original_inputs(self):
        V.verify_plan(M)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        for path,sha in M['retained_sha256'].items():self.assertEqual(V.digest((ROOT/path).read_bytes()),sha,path)

    def test_four_whole31_extents_and_no_partial_credit(self):
        self.assertEqual(sum(V.WHOLE.values()),124)
        self.reject(lambda m:m['functions'][0]['accepted_function'].update(size='30'))
        self.reject(lambda m:m['functions'][0]['instructions'].pop())

    def test_no_source_private_abi_or_exact_credit(self):
        for key,value in [('source_file','Owner.cpp'),('signature','Owner*'),('calling_convention','thiscall'),('match_percent','100.00')]:
            self.reject(lambda m:m['functions'][0]['accepted_function'].update({key:value}))

    def test_twenty_defining_sections_and_every_real_field(self):
        self.assertEqual((len(M['sections']),sum(r['size'] for r in M['sections']),sum(len(r['fields']) for r in M['sections'])),(20,552,12))
        self.assertTrue(all(r['source']['aux_records'] for r in M['sections']))
        self.reject(lambda m:m['sections'][0]['source']['aux_records'].clear())
        self.reject(lambda m:m['sections'][0]['bindings'].clear())

    def test_missing_constructor_cannot_be_replaced_by_field_observations(self):
        scoped=[r for r in M['sections'] if r['group']==0];root=scoped[0]
        constructor=next(r for r in scoped if r['symbol'].startswith('??0iterator'))
        catalog=V.SOURCE.owned_catalog([r for r in scoped if r is not constructor],{},0,[])
        self.assertNotIn(constructor['symbol'],catalog)
        with self.assertRaises(ValueError):V.SOURCE.BASE.BASE.bind_fields(bytes(root['size']),root['fields'],root['bindings'],catalog,0,int(root['base'],16))

    def test_full_compatible_ordinary_members_remain_byte_equal(self):
        for left,right in zip(M['groups'][:4],M['groups'][4:]):
            self.assertEqual(left['role'],'original-header');self.assertEqual(right['role'],'manual-member')
            l=[(r['base'],r['size'],r['body_sha256']) for r in M['sections'] if r['group']==left['id']]
            r=[(r['base'],r['size'],r['body_sha256']) for r in M['sections'] if r['group']==right['id']]
            self.assertEqual(l,r)
        self.reject(lambda m:m['groups'].pop())

    def test_whole_first_last_and_const_mutable_controls(self):
        self.assertEqual([r['kind'] for r in M['negative_controls']],['wrong-endpoint-field','wrong-const-route']*2+['wrong-endpoint-field','mutable-route']*2)
        self.assertEqual([r['size'] for r in M['negative_controls']],[31]*8)
        self.assertTrue(all(len(r['fields'])==1 for r in M['negative_controls']))
        self.reject(lambda m:m['negative_controls'][0]['bindings'].clear())

    def test_entire_ordinary_emission_and_readonly_layout(self):
        q=M['public_control'];em=q['emission']
        self.assertEqual((len(em),sum(r['size'] for r in em),sum(len(r['fields']) for r in em)),(55,1416,51))
        self.assertEqual(q['layout_values'],[4,116,16,16,16,16,4,4,16])
        self.assertEqual((q['layout']['size'],len(q['headers'])),(36,27))
        self.reject(lambda m:m['public_control']['layout_values'].pop())

    def test_three_whole_library_receivers_including_complete208_copy_body(self):
        self.assertEqual((len(M['parents']),sum(r['size'] for r in M['parents']),sum(len(r['call_sequences']) for r in M['parents'])),(3,499,4))
        copy_parent=next(r for r in M['parents'] if r['address']=='0x00459390')
        self.assertEqual(copy_parent['size'],208)
        self.assertEqual({r['target'] for r in copy_parent['call_sequences']},{'0x00459C40','0x00459C60'})
        self.reject(lambda m:m['parents'][-1].update(size=162))

    def test_literal_historical_unknowns_and_unchanged_old_verifier_hashes(self):
        self.assertEqual(len(M['historical_snapshots']),15)
        self.assertEqual(set(M['retained_replays']),{'R209','R210','R211'})
        for q in M['retained_replays'].values():
            self.assertEqual(V.digest((ROOT/q['script']).read_bytes()),q['script_sha256'])
            self.assertEqual(V.digest((ROOT/q['path']).read_bytes()),q['manifest_sha256'])
        self.assertTrue(all(r['record']['origin']['origin']=='unknown' for r in M['historical_snapshots']))
        self.reject(lambda m:m['retained_replays']['R211'].update(script_sha256='0'*64))

    def test_current_projection_changes_only_exact_selected_canonical_pairs(self):
        selected={r['address']:r for r in M['functions']}
        for key,q in M['retained_replays'].items():
            original=json.loads((ROOT/q['path']).read_text());before=copy.deepcopy(original)
            projected=V.project_retained(M,key,original)
            self.assertEqual(original,before)
            changes=0
            def compare(left,right):
                nonlocal changes
                if isinstance(left,dict):
                    a=left.get('function',{}).get('address') if isinstance(left.get('function'),dict) else None
                    row=selected.get(a) if 'origin' in left else None
                    if row:
                        self.assertEqual(right['function'],row['accepted_function']);self.assertEqual(right['origin'],row['accepted_origin']);changes+=1
                    self.assertEqual(set(left),set(right))
                    for k in left:
                        if row and k in ['function','origin']:continue
                        compare(left[k],right[k])
                elif isinstance(left,list):
                    self.assertEqual(len(left),len(right))
                    for l,r in zip(left,right):compare(l,r)
                else:self.assertEqual(left,right)
            compare(original,projected)
            self.assertEqual(changes,len([r for r in M['historical_snapshots'] if r['path']==q['path']]))

    def test_original_projection_is_literal_and_has_no_disk_write(self):
        for key,q in M['retained_replays'].items():
            path=ROOT/q['path'];raw=path.read_bytes();old=json.loads(raw)
            self.assertEqual(V.project_retained(M,key,old,True),old)
            self.assertEqual(path.read_bytes(),raw)

    def test_projection_rejects_changed_source_and_unrelated_old_state(self):
        old=json.loads((ROOT/M['retained_replays']['R211']['path']).read_text())
        for change in [lambda m:m['sections'][0].update(source_sha256='0'*64),lambda m:m['retained_unknowns'][0]['origin'].update(origin='library')]:
            mutated=copy.deepcopy(old);change(mutated)
            with self.assertRaises(ValueError):V.project_retained(M,'R211',mutated)

    def test_projection_rejects_omitted_snapshots_and_unapproved_successors(self):
        old=json.loads((ROOT/M['retained_replays']['R209']['path']).read_text())
        for change in [lambda m:m['historical_snapshots'].pop(),lambda m:m['functions'][0]['accepted_function'].update(calling_convention='cdecl')]:
            mutated=copy.deepcopy(M);change(mutated)
            with self.assertRaises(ValueError):V.project_retained(mutated,'R209',old)

    def test_opaque_leaves_and_other_private_policies_remain_unknown(self):
        protected={q['function']['address'] for q in M['retained_unknowns']}
        self.assertEqual(len(protected),15)
        self.assertTrue({'0x0040E9B0','0x0040EA20','0x004124B0','0x0041F7E0','0x00532350'}<=protected)
        self.reject(lambda m:m['retained_unknowns'][0]['origin'].update(origin='library'))

    def test_alignment_remains_outside_whole_extent(self):
        self.assertEqual([r['size'] for r in M['boundaries']],[1]*4)
        self.assertTrue(all(r['hex']=='cc' for r in M['boundaries']))
        self.reject(lambda m:m['boundaries'][0].update(size=0))


@unittest.skipUnless((ROOT/'resources/th075.exe').is_file(),'private pinned target is not supplied')
class VectorEndpointNativeTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.c=V.module('endpoint_test_c','compare-coff-function.py');cls.flow=V.module('endpoint_test_cfg','sdk_image_carriers.py');cls.target=cls.c.verified_target()

    def test_complete_native_policies_and_whole_receivers(self):
        V.verify_native(M,self.target,self.c,self.flow)

    def test_shortened_copy_or_changed_receiver_are_rejected(self):
        for change in [lambda m:m['parents'][-1].update(size=162),lambda m:m['parents'][0]['call_sequences'][0]['instructions'][0].update(operands='wrong')]:
            mutated=copy.deepcopy(M);change(mutated)
            with self.assertRaises(ValueError):V.verify_native(mutated,self.target,self.c,self.flow)


if __name__=='__main__':unittest.main()
