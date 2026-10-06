import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('effect_owner_binding',ROOT/'scripts/verify-effect-owner-binding-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)


class EffectOwnerBindingTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.plan=json.loads((ROOT/V.EVIDENCE).read_text())
        cls.c=V.module('effect_owner_test_target','compare-coff-function.py')
        cls.flow=V.module('effect_owner_test_flow','sdk_image_carriers.py')

    def test_complete_plan_and_unchanged_original_evidence(self):
        V.verify_plan(self.plan)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        for p,h in self.plan['retained_sha256'].items():self.assertEqual(V.digest((ROOT/p).read_bytes()),h,p)

    def test_one_origin_without_source_abi_extent_or_exact_credit(self):
        r=self.plan['functions'][0];f=r['accepted_function']
        self.assertEqual({r['address']:r['size'] for r in self.plan['functions']},{'0x0045BA10':21})
        self.assertEqual(r['cfg'],[1,0])
        self.assertEqual((f['current_name'],f['size'],f['span_end']),tuple(r['original_function'][k] for k in ['current_name','size','span_end']))
        self.assertEqual((f['status'],f['match_percent']),('unclassified','0.00'))
        self.assertFalse(any(f[k] for k in ['source_file','signature','calling_convention']))
        self.assertEqual(self.plan['historical_snapshots'],[])
        self.assertEqual(self.plan['context']['boundaries'][0]['size'],11)

    def test_full_native_context_and_two_complete_lifetime_frames(self):
        V.verify_native(self.plan,self.c.verified_target(),self.c,self.flow)
        self.assertEqual((len(self.plan['anchors']),sum(r['size'] for r in self.plan['anchors'])),(17,3217))
        self.assertEqual(len(self.plan['canonical']),18)
        self.assertEqual({r['handler_address'] for r in self.plan['context']['frames']},{'0x006563B6','0x006560D1'})

    def test_binding_happens_after_complete_manager_construction(self):
        r=next(r for r in self.plan['anchors'] if r['address']=='0x004567B0')
        ins={i['offset']:i for i in r['instructions']}
        self.assertEqual((ins[202]['operands'],ins[204]['operands']),('0x54','0x64159d'))
        self.assertEqual(ins[228]['operands'],'0x45b920')
        self.assertEqual(ins[258]['operands'],'ecx, dword ptr [ebp - 0x2c]')
        self.assertEqual(ins[261]['operands'],'dword ptr [eax + 0x2ec], ecx')
        self.assertEqual([ins[i]['operands'] for i in [267,270,271,274,280]],
            ['edx, dword ptr [ebp - 0x34]','edx','eax, dword ptr [ebp - 0x34]','ecx, dword ptr [eax + 0x2ec]','0x45ba10'])

    def test_real_effect_creation_consumes_the_bound_fighter(self):
        r=next(r for r in self.plan['anchors'] if r['address']=='0x0045BB10')
        ins={i['offset']:i for i in r['instructions']}
        self.assertEqual([ins[i]['operands'] for i in [18,23,25,27]],
            ['edx, dword ptr [ecx]','ecx, dword ptr [eax]','edx, dword ptr [edx]','dword ptr [edx + 0x1c]'])
        self.assertEqual([ins[i]['operands'] for i in [198,203,209]],
            ['edx, dword ptr [ecx]','ecx, dword ptr [edx + 0xa4]','dword ptr [eax + 0xa4], ecx'])
        self.assertEqual([ins[i]['operands'] for i in [259,265,269]],
            ['eax, eax, 0x14','ecx, [ecx + eax + 4]','0x45bfc0'])

    def test_scene_base_ctor_and_receiver_return_remain_unclassified(self):
        canonical={r['function']['address']:r for r in self.plan['canonical']}
        self.assertEqual(canonical['0x004251C0']['origin']['origin'],'unknown')
        self.assertEqual(canonical['0x004251C0']['origin']['evidence_id'],'R108')
        anchors={r['address']:r for r in self.plan['anchors']}
        ins={i['offset']:i for i in anchors['0x00417210']['instructions']}
        self.assertEqual(ins[524]['operands'],'eax, dword ptr [ebp - 4]')
        self.assertEqual(self.plan['context']['vtable']['slots'],['0x00641E19']*3)
        self.assertEqual(self.plan['cold_dependencies'],[['scripts/verify-game-lifetime-origins.py','--evidence-only']])

    def test_five_whole_scene_parents_keep_their_original_calls(self):
        anchors={r['address']:r for r in self.plan['anchors']}
        for a,size in [('0x00424E00',308),('0x004251F0',181),('0x00425490',183),('0x00425750',372),('0x004275D0',219)]:
            r=anchors[a];self.assertEqual(r['size'],size)
            self.assertTrue(any(i['mnemonic']=='call' and i['operands']=='0x4251c0' for i in r['instructions']))

    def test_every_whole_source_and_actual_member_pointer_field(self):
        ctl=self.plan['public_control']
        self.assertEqual((len(ctl['emission']),sum(r['size'] for r in ctl['emission'])),(9,161))
        self.assertEqual(sum(len(r['fields']) for r in ctl['sections']),2)
        self.assertEqual((ctl['headers'],ctl['weak_references']),({},[]))
        member_pointer=next(r for r in ctl['sections'] if r['section']==4)
        self.assertEqual(member_pointer['size'],4)
        field=member_pointer['fields'][0]
        self.assertEqual((field['type'],field['offset'],field['symbol_section']),('DIR32',0,11))
        self.assertTrue(field['symbol'].startswith('??4ImplicitEffectReferenceObservation'))
        self.assertEqual(ctl['layouts'][0]['values'],[4]*5)

    def test_natural_ctor_copy_and_borrowed_controls_are_complete_negatives(self):
        comparisons=self.plan['public_control']['comparisons']
        self.assertEqual([r['source_size'] for r in comparisons if r['role']=='positive'],[21,21])
        self.assertEqual([r['source_size'] for r in comparisons if r['role']=='negative'],[24,26,15,13])
        for r in comparisons:
            self.assertEqual(r['target_size'],21);self.assertEqual(r['bindings'],[])
            if r['role']=='negative':self.assertTrue(r['differences'])

    def test_trailing_missing_bytes_and_full_longer_controls_are_retained(self):
        negatives=[r for r in self.plan['public_control']['comparisons'] if r['role']=='negative']
        for r in negatives:
            if r['source_size']<21:
                tails=[d for d in r['differences'] if d['offset']>=r['source_size']]
                self.assertEqual(len(tails),21-r['source_size'])
                self.assertTrue(all(d['source'] is None for d in tails))
            else:
                tails=[d for d in r['differences'] if d['offset']>=21]
                self.assertEqual(len(tails),r['source_size']-21)
                self.assertTrue(all(d['target'] is None for d in tails))

    def test_cropped_or_falsely_bound_comparison_is_rejected(self):
        r=next(r for r in self.plan['public_control']['comparisons'] if r['role']=='positive')
        raw=self.c.pe_bytes_at(self.c.verified_target(),0x45ba10,21)
        V.verify_comparison(r,raw,raw,[])
        with self.assertRaisesRegex(ValueError,'crops'):V.verify_comparison(r,raw[:-1],raw,[])
        bad=copy.deepcopy(r);bad['bindings']=[{'offset':1}]
        with self.assertRaisesRegex(ValueError,'invents'):V.verify_comparison(bad,raw,raw,[])

    def test_altered_receiver_relation_and_source_family_are_rejected(self):
        bad=copy.deepcopy(self.plan)
        bad['context']['witnesses']['0x004567B0']['274']=['mov','ecx, dword ptr [eax + 0x2f0]']
        with self.assertRaisesRegex(ValueError,'witness|instruction|context'):
            V.verify_native(bad,self.c.verified_target(),self.c,self.flow)
        bad=copy.deepcopy(self.plan);bad['public_control']['comparisons'][1]['role']='positive'
        with self.assertRaisesRegex(ValueError,'immutable'):V.verify_plan(bad)


if __name__=='__main__':unittest.main()
