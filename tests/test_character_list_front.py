import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('character_front',ROOT/'scripts/verify-character-list-front-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)


class CharacterListFrontTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.plan=json.loads((ROOT/V.EVIDENCE).read_text())
        cls.c=V.module('front_test_target','compare-coff-function.py')
        cls.flow=V.module('front_test_flow','sdk_image_carriers.py')
        cls.owners={r['symbol']:r['address'] for r in cls.plan['public_control']['providers']}

    def test_all_pinned_inputs_and_bounded_scope(self):
        V.verify_plan(self.plan)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        for p,h in self.plan['retained_sha256'].items():self.assertEqual(V.digest((ROOT/p).read_bytes()),h,p)
        self.assertEqual(sum(r['size'] for r in self.plan['functions']),76)
        self.assertEqual(self.plan['historical_snapshots'],[])

    def test_entire_original_switch_consumer_and_container_provenance(self):
        V.verify_native(self.plan,self.c.verified_target(),self.c,self.flow)
        anchors={r['address']:r for r in self.plan['anchors']}
        r=anchors['0x00536400']
        self.assertEqual((r['size'],len(r['instructions']),r['cfg']),(39999,10573,[1,968]))
        self.assertTrue(r['switches'])
        ins={i['offset']:i['operands'] for i in r['instructions']}
        self.assertEqual([ins[i] for i in [499,505,511,529,542,563]],
            ['ecx, dword ptr [edx + 0xe4]','ecx, 0xfec','0x540220',
             'eax, word ptr [edx]','ax, word ptr [edx + 0xe]','ecx, word ptr [eax + 2]'])
        self.assertEqual((len(anchors),sum(r['size'] for r in anchors.values())),(17,41770))
        self.assertEqual(len(self.plan['context']['prior_policy']['functions']),12)

    def test_full_front_chain_cannot_substitute_begin_or_dereference(self):
        ctl=self.plan['public_control'];sections={r['section']:r for r in ctl['sections']}
        front=next(r for r in ctl['comparisons'] if r['source_definition']['symbol'].startswith('?front@'))
        self.assertEqual([r['target'] for r in front['bindings']],['0x00531DA0','0x00540240'])
        V.validate_bindings(front,sections[front['section']]['fields'],self.owners)
        bad=copy.deepcopy(front);bad['bindings'][0]['target']='0x00540240'
        with self.assertRaisesRegex(ValueError,'provider'):V.validate_bindings(bad,sections[front['section']]['fields'],self.owners)

    def test_ordinary_equivalent_and_all_fresh_fields_remain_whole(self):
        ctl=self.plan['public_control'];comparisons=ctl['comparisons']
        ordinary=[r for r in comparisons if r['source_definition']['symbol'].startswith('?First@Ordinary')]
        self.assertEqual([r['source_size'] for r in ordinary],[32])
        self.assertEqual((len(comparisons),sum(r['source_size'] for r in comparisons),sum(len(r['bindings']) for r in comparisons)),(9,221,9))
        self.assertEqual((len(ctl['emission']),sum(r['size'] for r in ctl['emission']),sum(len(r['fields']) for r in ctl['sections'])),(281,12482,600))
        self.assertEqual((len(ctl['headers']),len(ctl['weak_references'])),(34,3))
        self.assertEqual(ctl['layouts'][0]['values'][-5:],[16,12,4,4,12])

    def test_opaque_helpers_keep_unknown_and_no_private_abi_or_exact_credit(self):
        canonical={r['function']['address']:r for r in self.plan['canonical']}
        for a in ['0x00540280','0x00531D80']:
            self.assertEqual(canonical[a]['origin']['origin'],'unknown')
            self.assertEqual(canonical[a]['function']['owner'],'')
        for r in self.plan['functions']:
            f=r['accepted_function'];old=r['original_function']
            self.assertEqual([f[k] for k in ['current_name','size','span_end']],[old[k] for k in ['current_name','size','span_end']])
            self.assertFalse(any(f[k] for k in ['source_file','calling_convention','signature']))
            self.assertEqual(f['match_percent'],'0.00')
        bad=copy.deepcopy(self.plan);bad['functions'][0]['accepted_function']['signature']='invented'
        with self.assertRaisesRegex(ValueError,'immutable'):V.verify_plan(bad)

    def test_full_source_and_target_cannot_be_cropped(self):
        r=copy.deepcopy(self.plan['public_control']['comparisons'][0]);raw=self.c.pe_bytes_at(self.c.verified_target(),0x540220,32)
        V.compare_whole(r,raw,raw)
        with self.assertRaisesRegex(ValueError,'crops'):V.compare_whole(r,raw[:-1],raw)
        with self.assertRaisesRegex(ValueError,'positive'):V.compare_whole(r,raw[:-1]+b'\xcc',raw)

    def test_real_call_type_and_addend_cannot_be_masked(self):
        ctl=self.plan['public_control'];r=ctl['comparisons'][0]
        fields=next(s['fields'] for s in ctl['sections'] if s['section']==r['section'])
        for key,value in [('type','DIR32'),('addend',1)]:
            bad=copy.deepcopy(fields);bad[0][key]=value
            with self.assertRaisesRegex(ValueError,'type/addend'):V.validate_bindings(r,bad,self.owners)

    def test_all_nine_literal_history_pairs_require_exact_successor_readback(self):
        scope=self.plan['retained_replays']['scopes'][0];transitions=V.retained_transitions(self.plan,scope)
        self.assertEqual(set(transitions),{'0x0040E000','0x0041206F','0x004122C9','0x0041EFE6','0x0045B880','0x00532196','0x005F84B0','0x00654ACE','0x00654B0E'})
        old=json.loads((ROOT/scope['path']).read_text())
        for r in scope['transitions']:self.assertEqual(r['snapshot'],old['snapshots'][r['snapshot_index']])
        bad=copy.deepcopy(scope);bad['transitions'][0]['snapshot']['origin']['confidence']='unchecked'
        with self.assertRaisesRegex(ValueError,'literal'):V.retained_transitions(self.plan,bad)

    def test_history_projection_rejects_unapproved_current_transition(self):
        scope=self.plan['retained_replays']['scopes'][0];transitions=V.retained_transitions(self.plan,scope)
        actual=V.rows('functions.csv');projected=V.project_rows('functions.csv',actual,transitions);by={r['address']:r for r in projected}
        for a,r in transitions.items():self.assertEqual(by[a],r['original_function'])
        bad=copy.deepcopy(actual);next(r for r in bad if r['address']=='0x00532196')['notes']='unchecked'
        with self.assertRaisesRegex(ValueError,'unapproved'):V.project_rows('functions.csv',bad,transitions)

    def test_changed_receiver_record_use_and_guarded_switch_is_rejected(self):
        bad=copy.deepcopy(self.plan);bad['context']['witnesses']['0x00536400']['505']=['add','ecx, 0xff0']
        with self.assertRaises(ValueError):V.verify_native(bad,self.c.verified_target(),self.c,self.flow)
        bad=copy.deepcopy(self.plan);r=next(r for r in bad['anchors'] if r['address']=='0x00536400');r['switches'].pop()
        with self.assertRaises(ValueError):V.verify_native(bad,self.c.verified_target(),self.c,self.flow)


if __name__=='__main__':unittest.main()
