import copy
import importlib.util
import json
from pathlib import Path
import unittest
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('sprite_render_parameters',ROOT/'scripts/verify-sprite-render-parameter-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)

class SpriteRenderParameterTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.plan=json.loads((ROOT/V.EVIDENCE).read_text())
        cls.c=V.module('sprite_parameter_test_target','compare-coff-function.py')
        cls.flow=V.module('sprite_parameter_test_flow','sdk_image_carriers.py')

    def test_complete_immutable_plan_and_every_original_input(self):
        V.verify_plan(self.plan)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        for p,h in self.plan['retained_sha256'].items():self.assertEqual(V.digest((ROOT/p).read_bytes()),h,p)

    def test_two_whole_origins_without_source_abi_mapping_or_exact_credit(self):
        self.assertEqual({r['address']:r['size'] for r in self.plan['functions']},V.WHOLE)
        for r in self.plan['functions']:
            f=r['accepted_function'];self.assertEqual(r['cfg'],[1,0])
            self.assertEqual(f['current_name'],r['original_function']['current_name'])
            self.assertEqual((f['status'],f['match_percent']),('unclassified','0.00'))
            self.assertFalse(any(f[k] for k in ['source_file','signature','calling_convention']))
            self.assertEqual(r['instructions'][-1]['operands'],'4')

    def test_complete_independent_game_native_and_original_switch_context(self):
        V.verify_native(self.plan,self.c.verified_target(),self.c,self.flow)
        self.assertEqual((len(self.plan['anchors']),sum(r['size'] for r in self.plan['anchors'])),(20,66108))
        self.assertEqual(len(self.plan['canonical']),22)
        action=next(r for r in self.plan['anchors'] if r['address']=='0x0045DD70')
        self.assertEqual((action['size'],action['instruction_count'],action['cfg']),(60999,16837,[1,1690]))
        self.assertIsNone(action['instructions']);self.assertEqual(len(action['instructions_sha256']),64)
        self.assertTrue(action['switches'])

    def test_shared_created_owner_and_all_seven_real_action_calls(self):
        frame=self.plan['frame_context'];self.assertEqual(frame['game_context']['setters'],['0x00410FA0','0x00410FE0'])
        self.assertEqual(frame['game_context']['setter_fields'],[0x10,0x14])
        self.assertEqual(frame['game_context']['command_owner_field'],0x480)
        action=next(r for r in frame['parents'] if r['address']=='0x0045DD70')
        self.assertEqual((len(action['calls']),len(action['call_sequences'])),(7,7))
        for q in action['call_sequences']:
            self.assertEqual([i['mnemonic'] for i in q['instructions']],['push','push','push','mov','call'])
            self.assertEqual(q['instructions'][-1]['operands'],'0x454bc0')
        self.assertEqual(sum(r['size'] for r in frame['parents']),62405)

    def test_actual_sampling_modulo_and_packet_color_mask_consumers(self):
        draw=next(r for r in self.plan['anchors'] if r['address']=='0x00411110');ins={i['offset']:i for i in draw['instructions']}
        self.assertEqual(draw['size'],746)
        self.assertEqual(ins[212]['operands'],'ecx, byte ptr [eax + 0x10]')
        self.assertEqual((ins[223]['mnemonic'],ins[223]['operands']),('idiv','ecx'))
        self.assertEqual(ins[459]['operands'],'ecx, dword ptr [edx + 0x14]')
        self.assertEqual((ins[462]['mnemonic'],ins[462]['operands']),('and','ecx, dword ptr [eax + 0x9c]'))

    def test_no_reference_word_setter_and_implicit_constructor_stay_unknown(self):
        pairs={r['function']['address']:r for r in self.plan['canonical']}
        for a,size in [('0x00410FC0','24'),('0x00411C10','25')]:
            self.assertEqual((pairs[a]['origin']['origin'],pairs[a]['function']['size']),('unknown',size))
            self.assertFalse(pairs[a]['function']['owner'])
        self.assertEqual([r['size'] for r in self.plan['context']['boundaries']],[10,10])

    def test_all_source_code_data_fields_headers_and_weak_aliases(self):
        c=self.plan['public_control'];self.assertEqual((len(c['emission']),sum(r['size'] for r in c['emission'])),(189,8309))
        self.assertEqual(sum(len(r['fields']) for r in c['sections']),392)
        self.assertEqual(len(c['headers']),31);self.assertEqual(len(c['weak_references']),2)
        self.assertEqual(c['layouts'][0]['values'],[20,20,84,84,40,4,4,12,20,164,20,12,1,16,20,24,24,1])
        section=next(r for r in c['sections'] if r['section']==c['layouts'][0]['section'])
        self.assertEqual((section['size'],section['fields']),(72,[]))

    def test_all_whole_ordinary_template_and_borrowed_alternatives(self):
        c=self.plan['public_control'];positive=[r for r in c['comparisons'] if r['role']=='positive'];negative=[r for r in c['comparisons'] if r['role']=='negative']
        self.assertEqual((len(positive),sum(r['source_size'] for r in positive)),(4,88))
        self.assertEqual([r['source_size'] for r in negative],[13,13])
        for r in c['comparisons']:self.assertEqual((r['target_size'],r['bindings']),(22,[]))
        for a in V.WHOLE:
            symbols=[r['source_definition']['symbol'] for r in positive if r['address']==a]
            self.assertEqual(len(symbols),2);self.assertEqual(sum('TemplateSprite' in s for s in symbols),1)
        for r in negative:self.assertEqual([d['offset'] for d in r['differences'] if d['source'] is None],list(range(13,22)))

    def test_full_negative_guard_rejects_cropping_or_masking(self):
        for r in self.plan['public_control']['comparisons']:
            if r['role']!='negative':continue
            actual=self.c.pe_bytes_at(self.c.verified_target(),int(r['address'],16),22);raw=bytearray(actual[:13])
            for d in r['differences']:
                if d['source'] is not None:raw[d['offset']]=d['source']
            V.verify_comparison(r,bytes(raw),actual,[])
            with self.assertRaisesRegex(ValueError,'crops'):V.verify_comparison(r,bytes(raw),actual[:13],[])
            bad=copy.deepcopy(r);bad['differences']=[d for d in bad['differences'] if d['source'] is not None]
            with self.assertRaisesRegex(ValueError,'discards'):V.verify_comparison(bad,bytes(raw),actual,[])

    def test_comparison_cannot_invent_relocations_or_discard_ret_cleanup(self):
        r=self.plan['public_control']['comparisons'][0];raw=self.c.pe_bytes_at(self.c.verified_target(),int(r['address'],16),22)
        V.verify_comparison(r,raw,raw,[])
        with self.assertRaises(ValueError):V.verify_comparison(r,raw,raw,[dict(offset=13,type='DIR32')])
        bad=bytearray(raw);bad[-2]=0
        with self.assertRaisesRegex(ValueError,'positive differs'):V.verify_comparison(r,bytes(bad),raw,[])

    def test_all_four_literal_original_unknown_snapshots_remain_unchanged(self):
        V.verify_history(self.plan);h=self.plan['historical_snapshots']
        self.assertEqual(len(h),4)
        self.assertEqual({q['path'] for q in h},{'config/frame-index-policy-origin-evidence.json'})
        self.assertEqual({tuple(q['trail']) for q in h},{('retained_unknowns',i,k) for i in [0,1] for k in ['function','origin']})
        for q in h:
            r=next(r for r in self.plan['functions'] if r['address']==q['record']['address'])
            self.assertEqual(q['record'],r['original_'+q['trail'][-1]])

    def test_false_historical_successor_or_short_parent_is_rejected(self):
        bad=copy.deepcopy(self.plan);bad['historical_snapshots'][0]['record']['size']='21'
        with self.assertRaisesRegex(ValueError,'literal original'):V.verify_history(bad)
        bad=copy.deepcopy(self.plan);bad['frame_context']['parents'][1]['size']=60998
        with self.assertRaisesRegex(ValueError,'complete original'):V.verify_history(bad)

    def test_only_relevant_complete_list_graph_is_newly_cold_replayed(self):
        self.assertEqual(self.plan['cold_dependencies'],['scripts/verify-guarded-sprite-list-origins.py'])
        self.assertEqual(self.plan['frame_context']['manifest_sha256'],'bb5d5d550cf326252c7bf9a83961a4a90334bc75196f2c460ef2cc7a29236a22')

    def test_wrong_private_abi_source_or_large_owner_extent_is_rejected(self):
        for change in ['abi','source','action','layout']:
            bad=copy.deepcopy(self.plan)
            if change=='abi':bad['functions'][0]['accepted_function']['calling_convention']='thiscall'
            elif change=='source':bad['functions'][0]['accepted_function']['source_file']='src/Sprite.cpp'
            elif change=='action':next(r for r in bad['anchors'] if r['address']=='0x0045DD70')['size']=16837
            else:bad['public_control']['layouts'][0]['values']=[24]
            with self.assertRaises(ValueError):V.verify_plan(bad)

    def test_fixed_include_mapping_rejects_an_unreviewed_generic_owner(self):
        with self.assertRaises(ValueError):V.BASE.included_headers('Note: including file: probes/Other.cpp')
        p='probes/VC7ListPolicyDependencies.cpp'
        self.assertEqual(V.BASE.included_headers('Note: including file: probes\\VC7ListPolicyDependencies.cpp'),{p:V.digest((ROOT/p).read_bytes())})

if __name__=='__main__':unittest.main()
