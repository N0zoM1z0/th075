"""Guard real frame receiver/dispatch provenance and complete source alternatives."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
SPEC=importlib.util.spec_from_file_location('virtual_frame_tests',ROOT/'scripts/verify-virtual-frame-origins.py')
V=importlib.util.module_from_spec(SPEC);SPEC.loader.exec_module(V)
M=json.loads((ROOT/V.EVIDENCE).read_text())


class VirtualFramePlanTests(unittest.TestCase):
    def reject(self,change):
        m=copy.deepcopy(M);change(m)
        with self.assertRaises(ValueError):V.verify_plan(m)

    def test_complete_plan_and_all_original_inputs(self):
        V.verify_plan(M)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        for path,sha in M['retained_sha256'].items():self.assertEqual(V.digest((ROOT/path).read_bytes()),sha,path)

    def test_entire149_byte_extent_stays_unchanged(self):
        self.assertEqual(M['functions'][0]['size'],149)
        self.reject(lambda m:m['functions'][0]['accepted_function'].update(size='148'))

    def test_no_source_private_abi_or_exact_credit(self):
        for key,value in [('source_file','PrivateFrame.cpp'),('signature','PrivateFrame*'),
                          ('calling_convention','thiscall'),('match_percent','100.00')]:
            self.reject(lambda m:m['functions'][0]['accepted_function'].update({key:value}))

    def test_full_independent_game_owners(self):
        self.assertEqual((len(M['owners']),sum(r['size'] for r in M['owners'])),(8,51694))
        self.reject(lambda m:m['owners'].pop())

    def test_large_action_retains_all132_receiver_call_windows(self):
        action=next(r for r in M['owners'] if r['address']=='0x00476A40')
        self.assertEqual((action['size'],action['instruction_count'],len(action['call_sequences'])),(50915,13357,132))
        self.assertIsNone(action['instructions'])
        self.reject(lambda m:m['owners'][-1]['call_sequences'].pop())

    def test_complete_action_switch_remap_and_table(self):
        action=M['owners'][-1]
        self.assertEqual([r['size'] for r in action['switch_tables']],[199,264])
        self.reject(lambda m:m['owners'][-1]['switch_tables'][1].update(size=260))

    def test_game_constructor_installs_selected_callback_and_resource_owner(self):
        ctor=next(r for r in M['owners'] if r['address']=='0x004769B0')
        self.assertIn(dict(offset=59,size=6,mnemonic='mov',operands='dword ptr [ecx + 0xc4], eax'),ctor['instructions'])
        self.assertEqual([r['constructor'] for r in M['tables']],['0x0045B760','0x004769B0'])
        self.reject(lambda m:m['tables'][1]['words'].__setitem__(0,0x453d80))

    def test_table_observation_does_not_claim_complete_private_interface(self):
        self.assertEqual([len(r['words']) for r in M['tables']],[6,6])
        self.assertTrue(all(r['words'][-1]==0 for r in M['tables']))
        self.reject(lambda m:m['tables'][0]['words'].append(0))

    def test_five_actual_calls_preserve_nested_one_argument_protocol(self):
        policy=M['functions'][0]['policy']
        self.assertEqual([(r['offset'],r['target']) for r in policy['calls']],
            [(32,'0x004420B0'),(39,'0x00442060'),(96,'0x004420B0'),(103,'0x00442120'),(132,'0x004420B0')])
        self.assertEqual(policy['ret_cleanup'],0)
        self.reject(lambda m:m['functions'][0]['policy']['calls'][1].update(target='0x004420B0'))

    def test_generic_asset_view_is_an_alternative_not_original_layout(self):
        a,b=M['public_control']['methods'][:2]
        self.assertEqual(a['sha256'],b['sha256'])
        self.assertEqual(a['source']['size'],140)
        self.assertEqual(M['public_control']['layout_values'],[8,16,16,28,28,28])
        self.reject(lambda m:m['public_control']['layout_values'].__setitem__(0,116))

    def test_implicit_controls_do_not_select_frames(self):
        controls=[r for r in M['public_control']['methods'] if r['role']=='implicit-construction-alternative']
        self.assertEqual([r['source']['size'] for r in controls],[31,23])
        self.assertFalse(any('at@' in f['symbol'] for r in controls for f in r['fields']))
        self.reject(lambda m:m['public_control']['methods'][2]['fields'].clear())

    def test_full_ordinary_code_data_eh_and_every207_fields(self):
        emission=M['public_control']['emission']
        self.assertEqual((len(emission),sum(r['size'] for r in emission),sum(len(r['fields']) for r in emission)),(91,4179,207))
        self.reject(lambda m:m['public_control']['emission'].pop())

    def test_all18_historical_unknown_snapshots_remain_literal(self):
        self.assertEqual(len(M['historical_snapshots']),18)
        self.assertTrue(all(r['record']['origin']['origin']=='unknown' for r in M['historical_snapshots']))
        self.reject(lambda m:m['historical_snapshots'][0]['record']['origin'].update(origin='authored'))

    def test_external_alignment_and_independent_lifetimes_stay_protected(self):
        self.assertEqual(M['boundary']['hex'],'cc'*11)
        canonical={r['function']['address']:r['origin']['origin'] for r in M['canonical']}
        for key in ['0x00458650','0x00458670','0x00411C10','0x004251C0','0x00449DE0']:
            self.assertEqual(canonical[key],'unknown')
        self.reject(lambda m:m['boundary'].update(size=10))


@unittest.skipUnless((ROOT/'resources/th075.exe').is_file(),'private pinned target is not supplied')
class VirtualFrameNativeTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.c=V.module('virtual_frame_test_target','compare-coff-function.py');cls.target=cls.c.verified_target()
        cls.flow=V.module('virtual_frame_test_flow','sdk_image_carriers.py')

    def test_complete_native_policy_resource_and_game_dispatch(self):
        V.verify_native(M,self.target,self.c,self.flow)

    def test_wrong_lookup_pointer_output_field_or_return_is_rejected(self):
        raw=self.c.pe_bytes_at(self.target,0x45b880,149)
        for at,value in [(28,0x7c),(49,0x78),(148,0xcc)]:
            altered=bytearray(raw);altered[at]=value
            with self.assertRaises(ValueError):V.frame_policy(altered,0x45b880,self.flow)

    def test_wrong_callback_table_resource_constructor_or_action_call_is_rejected(self):
        m=copy.deepcopy(M);m['tables'][0]['address']='0x00659038'
        with self.assertRaises(ValueError):V.verify_native(m,self.target,self.c,self.flow)
        m=copy.deepcopy(M);m['owners'][-1]['call_sequences'][0]['instructions'].pop()
        with self.assertRaises(ValueError):V.verify_native(m,self.target,self.c,self.flow)


if __name__=='__main__':unittest.main()
