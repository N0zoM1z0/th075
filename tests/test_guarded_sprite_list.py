import copy
import importlib.util
import json
from pathlib import Path
import unittest
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('guarded_sprite_list',ROOT/'scripts/verify-guarded-sprite-list-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)

class GuardedSpriteListTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.plan=json.loads((ROOT/V.EVIDENCE).read_text())
        cls.c=V.module('sprite_test_target','compare-coff-function.py')
        cls.flow=V.module('sprite_test_flow','sdk_image_carriers.py')

    def test_complete_immutable_plan_and_original_inputs(self):
        V.verify_plan(self.plan)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        for p,h in self.plan['retained_sha256'].items():self.assertEqual(V.digest((ROOT/p).read_bytes()),h,p)

    def test_one_full_origin_preserves_source_abi_mapping_and_exact_state(self):
        r=self.plan['functions'][0];f=r['accepted_function']
        self.assertEqual({q['address']:q['size'] for q in self.plan['functions']},V.WHOLE)
        self.assertEqual(r['cfg'],[1,1]);self.assertEqual(f['current_name'],r['original_function']['current_name'])
        self.assertEqual((f['status'],f['match_percent']),('unclassified','0.00'))
        self.assertFalse(any(f[k] for k in ['source_file','signature','calling_convention']))
        self.assertEqual(self.plan['historical_snapshots'],[])

    def test_full_independent_native_context_and_unknown_constructor(self):
        V.verify_native(self.plan,self.c.verified_target(),self.c,self.flow)
        self.assertEqual((len(self.plan['anchors']),sum(r['size'] for r in self.plan['anchors'])),(13,4992))
        self.assertEqual(len(self.plan['canonical']),21)
        pair=next(r for r in self.plan['canonical'] if r['function']['address']=='0x00411C10')
        self.assertEqual((pair['origin']['origin'],pair['function']['size']),('unknown','25'))
        self.assertEqual(self.plan['context']['boundaries'][0]['size'],11)

    def test_complete_append_packet_and_twice_same_owner_removal(self):
        records={r['address']:r for r in self.plan['anchors']}
        driver=records['0x00453F70']['instructions'];calls=[i for i in driver if i['mnemonic']=='call' and i['operands']=='0x4110c0']
        self.assertEqual([i['offset'] for i in calls],[1764,1781])
        for offset in [1758,1775]:
            self.assertIn('0x480',next(i['operands'] for i in driver if i['offset']==offset))
        packet=records['0x00411000']['instructions']
        self.assertEqual(next(i['operands'] for i in packet if i['offset']==39),'ecx, 0x21')
        self.assertEqual(packet[-1]['operands'],'0xa4')
        self.assertEqual(records['0x00411110']['size'],746)

    def test_actual_public_queue_is_unconditional_and_list_pop_is_typed(self):
        h=self.plan['context']['header_definitions']
        self.assertEqual([(r['start'],r['end']) for r in h],[(429,432),(474,477),(69,72)])
        self.assertIn('return (_Mysize)',h[0]['text']);self.assertIn('erase(begin())',h[1]['text'])
        self.assertIn('c.pop_front();',h[2]['text']);self.assertNotIn('if',h[2]['text'])
        providers=self.plan['public_control']['providers']
        self.assertEqual([r['prior_record']['size'] for r in providers],[17,40])
        self.assertEqual([b['target_address'] for b in providers[1]['prior_record']['bindings']],['0x00411C90','0x00411F20'])

    def test_whole_source_code_data_and_actual_weak_aliases(self):
        c=self.plan['public_control']
        self.assertEqual((len(c['emission']),sum(r['size'] for r in c['emission'])),(196,8712))
        self.assertEqual(sum(len(r['fields']) for r in c['sections']),414)
        self.assertEqual(len(c['headers']),34);self.assertEqual(len(c['weak_references']),2)
        self.assertEqual(c['layouts'][0]['values'],[20,20,84,84,40,4,4,12,20,164,20,12,1,16,164,20,20,12])
        layout=next(r for r in c['sections'] if r['section']==c['layouts'][0]['section'])
        self.assertEqual(layout['size'],72);self.assertEqual(layout['fields'],[])

    def test_full_ordinary_library_and_borrowed_comparison_extents(self):
        c=self.plan['public_control'];sections={r['section']:r for r in c['sections']};owners={r['symbol']:r['address'] for r in c['providers']}
        self.assertEqual([(r['role'],r['source_size'],r['target_size']) for r in c['comparisons']],[('positive',37,37),('negative',19,37),('negative',25,37)])
        for r in c['comparisons']:V.validate_bindings(r,sections[r['section']]['fields'],owners)
        for r in c['comparisons'][1:]:
            missing=[d['offset'] for d in r['differences'] if d['source'] is None]
            self.assertEqual(missing,list(range(r['source_size'],37)))
        self.assertEqual([b['offset'] for b in c['comparisons'][0]['bindings']],[14,29])

    def test_full_difference_guard_rejects_cropping_and_masking(self):
        r=copy.deepcopy(self.plan['public_control']['comparisons'][1]);actual=self.c.pe_bytes_at(self.c.verified_target(),0x4110c0,37)
        # Reconstruct the full linked alternative only for this validator test.
        source=bytearray(actual[:r['source_size']])
        for d in r['differences']:
            if d['source'] is not None:source[d['offset']]=d['source']
        V.compare_whole(r,bytes(source),actual)
        with self.assertRaisesRegex(ValueError,'crops'):V.compare_whole(r,bytes(source),actual[:19])
        r['differences']=[d for d in r['differences'] if d['source'] is not None]
        with self.assertRaisesRegex(ValueError,'discards'):V.compare_whole(r,bytes(source),actual)

    def test_false_operation_owner_type_or_addend_is_rejected(self):
        c=self.plan['public_control'];r=c['comparisons'][0];fields=next(q['fields'] for q in c['sections'] if q['section']==r['section']);owners={q['symbol']:q['address'] for q in c['providers']}
        for key,value in [('symbol','??1FalseOwner@@QAE@XZ'),('type','DIR32'),('addend',4)]:
            bad=copy.deepcopy(fields);bad[0][key]=value
            with self.assertRaises(ValueError):V.validate_bindings(r,bad,owners)
        bad=copy.deepcopy(r);bad['bindings'][0]['target']='0x00411D00'
        with self.assertRaises(ValueError):V.validate_bindings(bad,fields,owners)

    def test_scoped_historical_replay_validates_all_full_successor_pairs(self):
        scopes=self.plan['retained_replays']['scopes']
        self.assertEqual([(r['evidence_id'],len(r['transitions'])) for r in scopes],[('R167',4),('R168',7)])
        self.assertEqual([r['evidence_id'] for r in self.plan['retained_replays']['successors']],['R218','R219','R222','R223'])
        for scope in scopes:
            transitions=V.retained_transitions(self.plan,scope)
            self.assertEqual(set(transitions),{r['address'] for r in scope['transitions']})
            old=json.loads((ROOT/scope['path']).read_text())
            for r in scope['transitions']:self.assertEqual(r['snapshot'],old['snapshots'][r['snapshot_index']])

    def test_projection_only_reverses_literal_accepted_pairs(self):
        scope=self.plan['retained_replays']['scopes'][0];transitions=V.retained_transitions(self.plan,scope)
        for dataset,kind in [('functions.csv','function'),('function-origins.csv','origin')]:
            actual=V.rows(dataset);projected=V.project_rows(dataset,actual,transitions)
            self.assertEqual(len(actual),len(projected))
            for row,new in zip(actual,projected):self.assertEqual(new,transitions[row['address']]['original_'+kind] if row['address'] in transitions else row)
        other=V.rows('authored-origin-evidence.csv')
        self.assertIs(V.project_rows('authored-origin-evidence.csv',other,transitions),other)

    def test_unapproved_or_missing_current_projection_is_rejected(self):
        scope=self.plan['retained_replays']['scopes'][0];transitions=V.retained_transitions(self.plan,scope);a=next(iter(transitions));actual=V.rows('functions.csv')
        bad=copy.deepcopy(actual);next(r for r in bad if r['address']==a)['size']='1'
        with self.assertRaisesRegex(ValueError,'unapproved'):V.project_rows('functions.csv',bad,transitions)
        with self.assertRaisesRegex(ValueError,'complete successor'):V.project_rows('functions.csv',[r for r in actual if r['address']!=a],transitions)

    def test_fabricated_successor_or_literal_old_snapshot_is_rejected(self):
        scope=copy.deepcopy(self.plan['retained_replays']['scopes'][0]);scope['transitions'][0]['snapshot']['origin']['origin']='library'
        with self.assertRaisesRegex(ValueError,'literal old'):V.retained_transitions(self.plan,scope)
        scope=copy.deepcopy(self.plan['retained_replays']['scopes'][0]);scope['transitions'][0]['record']['accepted_origin']['evidence_id']='R238'
        with self.assertRaisesRegex(ValueError,'exact bounded'):V.retained_transitions(self.plan,scope)

    def test_false_layout_source_credit_and_cropped_extent_are_rejected(self):
        for key,value in [('size',36),('accepted_function',dict(self.plan['functions'][0]['accepted_function'],source_file='src/Sprite.cpp'))]:
            bad=copy.deepcopy(self.plan);bad['functions'][0][key]=value
            with self.assertRaises(ValueError):V.verify_plan(bad)
        bad=copy.deepcopy(self.plan);bad['public_control']['layouts'][0]['values']=[164,20,20,12]
        with self.assertRaises(ValueError):V.verify_plan(bad)

    def test_relative_include_requires_the_literal_probe_and_fixed_cwd(self):
        p='probes/VC7ListPolicyDependencies.cpp'
        self.assertEqual(V.included_headers('Note: including file: probes\\VC7ListPolicyDependencies.cpp'),{p:V.digest((ROOT/p).read_bytes())})
        for name in ['../probes/VC7ListPolicyDependencies.cpp','probes/Other.cpp','C:/tools/list']:
            with self.assertRaises(ValueError):V.included_headers('Note: including file: '+name)

if __name__=='__main__':unittest.main()
