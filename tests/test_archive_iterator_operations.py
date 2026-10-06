import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('archive_iterator_operations',ROOT/'scripts/verify-archive-iterator-operation-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)


class ArchiveIteratorOperationTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.plan=json.loads((ROOT/V.EVIDENCE).read_text())
        cls.c=V.module('archive_iterator_test_target','compare-coff-function.py')
        cls.flow=V.module('archive_iterator_test_flow','sdk_image_carriers.py')
        cls.owners={r['symbol']:r['address'] for r in cls.plan['public_control']['providers']}

    def test_immutable_scope_and_all_original_inputs(self):
        V.verify_plan(self.plan)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        for p,h in self.plan['retained_sha256'].items():self.assertEqual(V.digest((ROOT/p).read_bytes()),h,p)

    def test_six_origins_preserve_extents_abi_source_and_exact_state(self):
        self.assertEqual({r['address']:r['size'] for r in self.plan['functions']},V.WHOLE)
        self.assertEqual(sum(r['size'] for r in self.plan['functions']),162)
        for r in self.plan['functions']:
            f=r['accepted_function'];old=r['original_function']
            self.assertEqual((f['current_name'],f['size'],f['span_end']),tuple(old[k] for k in ['current_name','size','span_end']))
            self.assertEqual((f['owner'],f['status'],f['match_percent']),('library','excluded','0.00'))
            self.assertFalse(any(f[k] for k in ['source_file','calling_convention','signature']))
        self.assertEqual(self.plan['historical_snapshots'],[])

    def test_full_container_and_game_native_context(self):
        V.verify_native(self.plan,self.c.verified_target(),self.c,self.flow)
        self.assertEqual((len(self.plan['anchors']),sum(r['size'] for r in self.plan['anchors'])),(20,2264))
        self.assertEqual(len(self.plan['canonical']),26)
        self.assertEqual(len(self.plan['context']['prior_policy']['functions']),13)
        self.assertEqual(len(self.plan['context']['imports']),5)

    def test_outer_arrow_and_mutable_dereference_use_distinct_real_providers(self):
        comparisons=self.plan['public_control']['comparisons']
        arrow=next(r for r in comparisons if r['source_definition']['symbol'].startswith('??Citerator@'))
        dereference=next(r for r in comparisons if r['source_definition']['symbol'].startswith('??Diterator@'))
        self.assertEqual((arrow['source_size'],dereference['source_size']),(19,19))
        self.assertEqual([b['target'] for b in arrow['bindings']],['0x0041EF20'])
        self.assertEqual([b['target'] for b in dereference['bindings']],['0x0041F790'])
        self.assertTrue(arrow['bindings'][0]['symbol'].startswith('??Diterator@'))
        self.assertTrue(dereference['bindings'][0]['symbol'].startswith('??Dconst_iterator@'))
        sections={r['section']:r for r in self.plan['public_control']['sections']}
        for r in [arrow,dereference]:V.validate_bindings(r,sections[r['section']]['fields'],self.owners)

    def test_swapped_equal_shape_provider_is_rejected(self):
        r=copy.deepcopy(self.plan['public_control']['comparisons'][0])
        sections={r['section']:r for r in self.plan['public_control']['sections']}
        r['bindings'][0]['target']='0x0041F790'
        with self.assertRaisesRegex(ValueError,'provider'):
            V.validate_bindings(r,sections[r['section']]['fields'],self.owners)

    def test_postfix_preserves_old_cursor_hidden_result_and_dummy_argument(self):
        r=next(r for r in self.plan['functions'] if r['address']=='0x0041E080')
        ins={i['offset']:i for i in r['instructions']}
        self.assertEqual([ins[i]['operands'] for i in [12,14,20,25,28,31,33,39]],
            ['ecx, dword ptr [eax]','dword ptr [ebp - 4], ecx','0x41ef40','edx, dword ptr [ebp + 8]',
             'eax, dword ptr [ebp - 4]','dword ptr [edx], eax','eax, dword ptr [ebp + 8]','8'])
        self.assertFalse(any('[ebp + 0xc]' in i['operands'] for i in r['instructions']))

    def test_prefix_and_const_prefix_retain_the_actual_nextnode_call(self):
        ctl=self.plan['public_control'];providers={r['address']:r for r in ctl['providers']}
        prefix=next(r for r in ctl['comparisons'] if r['source_definition']['symbol']==providers['0x0041EF40']['symbol'])
        const_prefix=next(r for r in ctl['comparisons'] if r['source_definition']['symbol']==providers['0x0041F7B0']['symbol'])
        self.assertEqual([b['target'] for b in prefix['bindings']],['0x0041F7B0'])
        self.assertEqual([b['target'] for b in const_prefix['bindings']],['0x0041E100'])
        self.assertEqual((prefix['source_size'],const_prefix['source_size']),(22,35))

    def test_named_seeks_use_same_owner_begin_end_and_payload_fields(self):
        anchors={r['address']:r for r in self.plan['anchors']}
        for a,size in [('0x0041D750',164),('0x0041D800',180)]:
            r=anchors[a];ins={i['offset']:i for i in r['instructions']};self.assertEqual(r['size'],size)
            self.assertEqual([ins[i]['operands'] for i in [16,19,31,34,46,65,94,132,137]],
                ['ecx, 4','0x41d950','ecx, 4','0x41d980','0x41e0d0','0x41e060','0x41e080','0x41e060','edx, dword ptr [eax + 0x68]'])
            self.assertEqual([ins[i]['operands'] for i in [85,87,90,91]],['0','edx, [ebp - 0xc]','edx','ecx, [ebp - 4]'])
        self.assertEqual({i['offset']:i['operands'] for i in anchors['0x0041D800']['instructions']}[164],'eax, dword ptr [eax + 0x64]')

    def test_opaque_node_accessors_gain_no_origin_or_private_type_credit(self):
        canonical={r['function']['address']:r for r in self.plan['canonical']}
        for a in ['0x0041E100','0x0041F7F0']:
            self.assertEqual(canonical[a]['origin']['origin'],'unknown')
            self.assertEqual(canonical[a]['function']['owner'],'')
        providers=self.plan['public_control']['providers']
        self.assertEqual([r['size'] for r in providers if r['scope']=='whole-context-provider-only-origin-remains-unknown'],[8,11])

    def test_entire_emission_includes_every_field_and_real_weak_alias(self):
        ctl=self.plan['public_control']
        self.assertEqual((len(ctl['emission']),sum(r['size'] for r in ctl['emission'])),(260,11499))
        self.assertEqual(sum(len(r['fields']) for r in ctl['sections']),551)
        self.assertEqual(len(ctl['headers']),33);self.assertEqual(len(ctl['weak_references']),3)
        self.assertEqual(len(ctl['layouts'][0]['values']),27)
        self.assertEqual(ctl['layouts'][0]['values'][-5:],[108,4,4,4,4])

    def test_all_whole_sdk_and_ordinary_comparisons_remain_visible(self):
        comparisons=self.plan['public_control']['comparisons']
        self.assertEqual((len(comparisons),sum(r['source_size'] for r in comparisons)),(10,242))
        self.assertEqual(sum(len(r['bindings']) for r in comparisons),8)
        ordinary=[r for r in comparisons if r['compatible_declarations']]
        self.assertEqual([r['source_size'] for r in ordinary],[19,42])
        for r in comparisons:self.assertEqual(r['source_size'],r['target_size'])
        self.assertTrue(all('OrdinaryArchive' in r['source_definition']['symbol'] for r in ordinary))

    def test_ordinary_declarations_do_not_claim_recovered_original_definitions(self):
        ctl=self.plan['public_control'];sections={r['section']:r for r in ctl['sections']}
        for r in ctl['comparisons']:
            if not r['compatible_declarations']:continue
            fields=sections[r['section']]['fields']
            self.assertEqual(len(fields),1);self.assertEqual(fields[0]['symbol_section'],0)
            self.assertEqual(fields[0]['symbol_storage'],2);self.assertEqual(fields[0]['symbol_type'],32)
            V.validate_bindings(r,fields,self.owners)
            bad=copy.deepcopy(fields);bad[0]['symbol_section']=17
            with self.assertRaisesRegex(ValueError,'declaration'):V.validate_bindings(r,bad,self.owners)

    def test_current_successor_readback_preserves_all_eight_literal_old_pairs(self):
        scope=self.plan['retained_replays']['scopes'][0]
        transitions=V.retained_transitions(self.plan,scope)
        self.assertEqual(set(transitions),{'0x0040E000','0x0041206F','0x004122C9','0x0041EFE6','0x0045B880','0x005F84B0','0x00654ACE','0x00654B0E'})
        old=json.loads((ROOT/scope['path']).read_text())
        for r in scope['transitions']:self.assertEqual(r['snapshot'],old['snapshots'][r['snapshot_index']])

    def test_historical_projection_rejects_unapproved_metadata_change(self):
        scope=self.plan['retained_replays']['scopes'][0];transitions=V.retained_transitions(self.plan,scope)
        actual=V.rows('functions.csv');projected=V.project_rows('functions.csv',actual,transitions)
        by={r['address']:r for r in projected}
        for a,r in transitions.items():self.assertEqual(by[a],r['original_function'])
        bad=copy.deepcopy(actual);next(r for r in bad if r['address']=='0x0040E000')['notes']='unchecked'
        with self.assertRaisesRegex(ValueError,'unapproved'):V.project_rows('functions.csv',bad,transitions)
        self.assertEqual(V.project_rows('authored-origin-evidence.csv',[{'unchanged':1}],transitions),[{'unchanged':1}])

    def test_complete_extents_and_real_relocation_types_cannot_be_cropped(self):
        r=copy.deepcopy(self.plan['public_control']['comparisons'][0])
        raw=self.c.pe_bytes_at(self.c.verified_target(),0x41e060,19)
        V.compare_whole(r,raw,raw)
        with self.assertRaisesRegex(ValueError,'crops'):V.compare_whole(r,raw[:-1],raw)
        sections={q['section']:q for q in self.plan['public_control']['sections']};fields=copy.deepcopy(sections[r['section']]['fields'])
        fields[0]['type']='DIR32'
        with self.assertRaisesRegex(ValueError,'type'):V.validate_bindings(r,fields,self.owners)

    def test_all_six_external_alignment_gaps_stay_outside_functions(self):
        self.assertEqual([r['size'] for r in self.plan['context']['boundaries']],[13,6,13,10,7,13])
        self.assertEqual(sum(r['size'] for r in self.plan['context']['boundaries']),62)

    def test_changed_hidden_result_or_node_offset_is_rejected(self):
        bad=copy.deepcopy(self.plan)
        bad['context']['witnesses']['0x0041E080']['31']=['mov','dword ptr [edx + 4], eax']
        with self.assertRaises(ValueError):V.verify_native(bad,self.c.verified_target(),self.c,self.flow)
        bad=copy.deepcopy(self.plan);bad['public_control']['providers'][-1]['address']='0x0041E100'
        with self.assertRaisesRegex(ValueError,'immutable'):V.verify_plan(bad)


if __name__=='__main__':unittest.main()
