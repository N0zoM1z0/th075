"""Guard whole random-range policy, actual game contexts and source alternatives."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
SPEC=importlib.util.spec_from_file_location('range_tests',ROOT/'scripts/verify-integer-range-origins.py')
V=importlib.util.module_from_spec(SPEC);SPEC.loader.exec_module(V)
M=json.loads((ROOT/V.EVIDENCE).read_text())


class RangePlanTests(unittest.TestCase):
    def reject(self,change):
        m=copy.deepcopy(M);change(m)
        with self.assertRaises(ValueError):V.verify_plan(m)

    def test_complete_plan_and_original_inputs(self):
        V.verify_plan(M)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        for path,sha in M['retained_sha256'].items():self.assertEqual(V.digest((ROOT/path).read_bytes()),sha,path)

    def test_both_full44_byte_extents(self):
        self.assertEqual(sum(r['size'] for r in M['functions']),88)
        self.reject(lambda m:m['functions'][0]['accepted_function'].update(size='43'))

    def test_no_source_abi_or_exact_credit(self):
        for key,value in [('source_file','Private.cpp'),('signature','int Private::Range(int,int)'),
                          ('calling_convention','thiscall'),('match_percent','100.00')]:
            self.reject(lambda m:m['functions'][0]['accepted_function'].update({key:value}))

    def test_whole_independent_action_and_ai_parents(self):
        self.assertEqual([p['size'] for p in M['parents']],[31352,8871])
        self.assertEqual([p['record']['evidence_id'] for p in M['parents']],['R064','R047'])
        self.reject(lambda m:m['parents'][0].update(size=31351))

    def test_all63_action_and_six_ai_calls_retained(self):
        self.assertEqual([len(p['call_sequences']) for p in M['parents']],[63,6])
        self.reject(lambda m:m['parents'][0]['call_sequences'].pop())

    def test_complete_guarded_switch_remap_and_table(self):
        self.assertEqual([r['size'] for r in M['parents'][0]['tables']],[145,280])
        self.reject(lambda m:m['parents'][0]['tables'][1].update(size=276))

    def test_real_endpoint_and_result_context_not_caller_name(self):
        action=M['parents'][0]['call_sequences'][0]['instructions']
        ai=M['parents'][1]['call_sequences'][0]['instructions']
        self.assertIn('dword ptr [eax + 0x28]',[r['operands'] for r in action])
        self.assertIn('word ptr [ecx + 0x512], ax',[r['operands'] for r in ai])
        self.reject(lambda m:m['parents'][1]['call_sequences'][0]['instructions'].pop())

    def test_complete_rand_provider_and_actual_typed_thread_state_entry(self):
        p=M['provider']['record']
        self.assertEqual((p['size'],p['coff_symbol']),(34,'_rand'))
        self.assertEqual(p['relocation_bindings'][0]['code_entry']['owner'],'0x00646196')
        self.reject(lambda m:m['provider']['record']['relocation_bindings'].clear())

    def test_generic_distribution_alternative_does_not_prove_original_identity(self):
        a,b=[r for r in M['public_control']['methods'] if r['role']=='ordinary-range-alternative']
        self.assertEqual(a['sha256'],b['sha256'])
        self.assertEqual(a['source']['size'],31)
        self.reject(lambda m:m['public_control']['methods'][0]['source'].update(size=44))

    def test_full_sdk_shuffle_and_all_emitted_dependencies(self):
        control=M['public_control']
        self.assertEqual((len(control['emission']),sum(r['size'] for r in control['emission'])),(10,267))
        self.assertEqual(sum(len(r['fields']) for r in control['methods']),9)
        self.reject(lambda m:m['public_control']['emission'].pop())

    def test_original_sdk_modulo_swap_is_a_distinct_algorithm(self):
        r=next(r for r in M['public_control']['methods'] if r['source']['size']==99)
        self.assertIn('div',[i['mnemonic'] for i in r['instructions']])
        self.assertNotIn('imul',[i['mnemonic'] for i in r['instructions']])
        self.reject(lambda m:m['public_control']['methods'].remove(r))

    def test_natural_layout_observations_are_not_private_game_layout(self):
        self.assertEqual(M['public_control']['layout_values'],[1,1,4,32767])
        self.reject(lambda m:m['public_control']['layout_values'].__setitem__(0,0x514))

    def test_external_alignment_stays_outside_both_bodies(self):
        self.assertEqual([r['hex'] for r in M['boundaries']],['cccccccc','cccccccc'])
        self.reject(lambda m:m['boundaries'][0].update(size=3))

    def test_retained_sdk_lifetime_and_generic_ambiguities_stay_unknown(self):
        rows={r['function']['address']:r for r in M['canonical']}
        for key in ['0x00608D8E','0x00608F7B','0x00609AA4','0x00609F58','0x0060B728','0x006200DA',
                    '0x00411C10','0x004251C0','0x00449DE0','0x00641DAA','0x0041CA30','0x00455770']:
            self.assertEqual(rows[key]['origin']['origin'],'unknown')
        self.reject(lambda m:m['canonical'][8]['origin'].update(origin='library'))


@unittest.skipUnless((ROOT/'resources/th075.exe').is_file(),'private pinned target is not supplied')
class RangeNativeTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.c=V.module('range_test_target','compare-coff-function.py');cls.target=cls.c.verified_target()
        cls.flow=V.module('range_test_flow','sdk_image_carriers.py')

    def test_all_complete_native_policies_and_actual_parent_contexts(self):
        V.verify_native(M,self.target,self.c,self.flow)

    def test_missing_sign_bias_wrong_divisor_or_ret_is_rejected(self):
        raw=self.c.pe_bytes_at(self.target,0x410f00,44)
        for at,value in [(25,0),(33,14),(42,4)]:
            altered=bytearray(raw);altered[at]=value
            with self.assertRaises(ValueError):V.range_policy(altered,0x410f00,self.flow)

    def test_wrong_parent_call_or_missing_switch_data_is_rejected(self):
        m=copy.deepcopy(M);m['parents'][0]['child']='0x00455610'
        with self.assertRaises(ValueError):V.verify_native(m,self.target,self.c,self.flow)
        m=copy.deepcopy(M);m['parents'][0]['tables'][0]['address']='0x006028A8'
        with self.assertRaises(ValueError):V.verify_native(m,self.target,self.c,self.flow)


if __name__=='__main__':unittest.main()
