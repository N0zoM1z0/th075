import copy
import importlib.util
import json
from pathlib import Path
import struct
import unittest

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('music_lifetime',ROOT/'scripts/verify-music-scene-lifetime-origins.py')
V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)

class MusicSceneLifetimeTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.plan=json.loads((ROOT/V.EVIDENCE).read_text())
        cls.c=V.module('music_test_target','compare-coff-function.py')
        cls.flow=V.module('music_test_flow','sdk_image_carriers.py')

    def test_whole_immutable_plan_and_every_retained_input(self):
        V.verify_plan(self.plan)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        for p,h in self.plan['retained_sha256'].items():self.assertEqual(V.digest((ROOT/p).read_bytes()),h,p)

    def test_only_three_full_game_origins_without_source_private_abi_credit(self):
        self.assertEqual({r['address']:r['size'] for r in self.plan['functions']},V.WHOLE)
        for r in self.plan['functions']:
            f=r['accepted_function']
            self.assertEqual(f['current_name'],r['original_function']['current_name'])
            self.assertEqual((f['status'],f['match_percent']),('unclassified','0.00'))
            for k in ['source_file','signature','calling_convention']:self.assertFalse(f[k])
        self.assertEqual([r['cfg'] for r in self.plan['functions']],[[1,3],[1,0],[1,0]])

    def test_true_array_contract_and_real_game_assets(self):
        ctx=self.plan['context'];a=ctx['array']
        self.assertEqual((a['size'],a['count']),(16,60))
        self.assertEqual([s['text'] for s in ctx['strings']],['data','data\\system\\music.dat','datab','musicroom.dat'])
        anchors={r['address']:r for r in self.plan['anchors']}
        self.assertEqual((anchors['0x00641C78']['size'],anchors['0x00641D4A']['size']),(98,96))
        self.assertEqual(anchors['0x00641C78']['cfg'],[2,3])
        self.assertEqual(anchors['0x00641D4A']['cfg'],[2,3])
        self.assertEqual(len(ctx['renderer_witnesses']),3)

    def test_whole_source_code_data_and_genuine_implicit_controls(self):
        c=self.plan['public_control']
        self.assertEqual((len(c['emission']),sum(r['size'] for r in c['emission'])),(18,796))
        self.assertEqual(len(c['headers']),73)
        self.assertEqual(sorted(c['alternatives'].values()),[5,19,50,82,244])
        self.assertEqual(c['layouts'][0]['values'],[1,16,8,988,16,988])
        self.assertEqual(c['layouts'][0]['definitions'][1]['offset'],16)
        self.assertEqual(len(c['weak_references']),3)

    def test_whole_positive_and_negative_normal_exception_graph(self):
        c=self.plan['public_control'];rs=c['comparisons']
        self.assertEqual([r['size'] for r in rs],[244,50,82,44,44,40,44])
        self.assertEqual(sum(r['size'] for r in rs),548)
        self.assertEqual(rs[-2]['roots'],[0,8,30])
        self.assertEqual(rs[-1]['roots'],[])
        negative=rs[2]
        self.assertEqual(negative['role'],'scalar-array-delete-route-alternative')
        self.assertEqual(len(negative['differences']),6)
        self.assertTrue(all(b['symbol']=='??3@YAXPAX@Z' and b['target']=='0x00640F15' for b in negative['bindings']))

    def test_complete_native_context_and_mixed_vendor_owner(self):
        V.verify_native(self.plan,self.c.verified_target(),self.c,self.flow)
        self.assertEqual((len(self.plan['anchors']),sum(r['size'] for r in self.plan['anchors'])),(29,9276))
        memcpy=next(r for r in self.plan['anchors'] if r['address']=='0x00640F20')
        self.assertEqual(memcpy['kind'],'whole-mixed-vendor-code-data')
        self.assertEqual(memcpy['source_record']['relocation_count'],'46')
        self.assertIsNone(memcpy['instructions']);self.assertEqual(memcpy['size'],829)
        pairs={r['function']['address']:r for r in self.plan['canonical']}
        self.assertEqual(pairs['0x004251C0']['origin']['origin'],'unknown')
        self.assertEqual(self.plan['historical_snapshots'],[])

    def test_reversed_array_argument_order_cannot_earn_credit(self):
        bad=copy.deepcopy(self.plan);bad['context']['array'].update(size=60,count=16)
        with self.assertRaises(ValueError):V.verify_plan(bad)
        r=next(r for r in self.plan['anchors'] if r['address']=='0x00425750')
        instructions=copy.deepcopy(r['instructions'])
        next(i for i in instructions if i['offset']==64)['operands']='0x10'
        with self.assertRaises(ValueError):V.require(instructions,{64:('push','0x3c'),66:('push','0x10')})

    def test_wrong_scalar_to_array_binding_is_rejected(self):
        r=copy.deepcopy(self.plan['public_control']['comparisons'][2]);section=next(q for q in self.plan['public_control']['sections'] if q['section']==r['section'])
        r['bindings'][0]['target']='0x0064169D'
        with self.assertRaisesRegex(ValueError,'falsely binds scalar source'):
            V.compare_alternative(r,bytes(82),bytes(82),section['fields'],self.c.verified_target(),self.c,self.flow)

    def test_masked_deallocator_differences_cannot_earn_credit(self):
        r=copy.deepcopy(self.plan['public_control']['comparisons'][2]);section=next(q for q in self.plan['public_control']['sections'] if q['section']==r['section'])
        target=self.c.verified_target();actual=self.c.pe_bytes_at(target,0x427470,82);linked=bytearray(actual)
        for off in [29,50,71]:struct.pack_into('<I',linked,off,(0x640f15-(0x427470+off+4))&0xffffffff)
        V.compare_alternative(r,linked,actual,section['fields'],target,self.c,self.flow)
        r['differences']=[]
        with self.assertRaisesRegex(ValueError,'six genuine'):
            V.compare_alternative(r,linked,actual,section['fields'],target,self.c,self.flow)

    def test_cropped_eh_or_private_owner_signature_is_rejected(self):
        for key in ['context','functions']:
            bad=copy.deepcopy(self.plan)
            if key=='context':bad[key]['exception_parts'][0]['size']=30
            else:bad[key][0]['accepted_function']['signature']='~MusicRoomScene()'
            with self.assertRaises(ValueError):V.verify_plan(bad)

if __name__=='__main__':unittest.main()
