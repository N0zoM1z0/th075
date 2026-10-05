"""Guard complete velocity evidence, float argument order and unknown abs ownership."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('polar_tests', ROOT / 'scripts/verify-polar-velocity-origins.py')
V = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(V)
M = json.loads((ROOT / V.EVIDENCE).read_text())


class PolarVelocityTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.c = V.module('polar_test_target','compare-coff-function.py')
        cls.target = cls.c.verified_target()
        cls.cfg = V.module('polar_test_cfg','verify-authored-origins.py')

    def reject(self, change, context=False):
        m=copy.deepcopy(M);change(m)
        with self.assertRaises(ValueError):
            if context: V.verify_context(m)
            else: V.verify_plan(m)

    def test_plan_and_pinned_original_evidence(self):
        V.verify_plan(M)
        self.assertEqual(V.digest((ROOT / V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        for path,sha in M['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT / path).read_bytes()),sha,path)

    def test_complete_native_bodies_and_guarded_parent_cfgs(self):
        for r in M['functions']+M['anchors']+M['retained_unknowns']:
            V.verify_native(r,self.target,self.c,self.cfg)
        V.verify_context(M)

    def test_no_private_layout_source_abi_or_exact_credit(self):
        for key,value in [('source_file','Game.cpp'),('signature','Private*'),('calling_convention','cdecl'),('match_percent','100.00')]:
            self.reject(lambda m:m['functions'][0]['accepted_function'].update({key:value}))

    def test_entire57_byte_extent_unchanged(self):
        self.assertEqual(M['functions'][0]['original_function']['size'],'57')
        self.assertEqual(M['functions'][0]['accepted_function']['span_end'],'0x0040FBA8')
        self.reject(lambda m:m['functions'][0].update(size=56))

    def test_actual_ret8_not_invented_signature(self):
        self.reject(lambda m:m['functions'][0]['instructions'][-1].update(operands='4'),True)

    def test_actual_lookup_order_preserved(self):
        self.reject(lambda m:m['functions'][0]['instructions'][6].update(operands='0x41cb70'),True)

    def test_x87_negation_and_native_float_stores(self):
        self.reject(lambda m:next(i for i in m['functions'][0]['instructions'] if i['mnemonic']=='fchs').update(mnemonic='nop'),True)
        self.reject(lambda m:next(i for i in m['functions'][0]['instructions'] if i['mnemonic']=='fstp').update(operands='dword ptr [ecx + 0x54]'),True)

    def test_six_original_float_argument_and_receiver_sequences(self):
        self.assertEqual(sum(len(r['call_sequences']) for r in M['anchors']),6)
        self.reject(lambda m:next(r for r in m['anchors'] if r['call_sequences'])['call_sequences'][0]['instructions'].pop(),True)

    def test_game_receiver_not_substituted(self):
        self.reject(lambda m:next(r for r in m['anchors'] if r['call_sequences'])['call_sequences'][0]['instructions'][-2].update(operands='ecx, 1'),True)

    def test_actual_integer_helper641daa_stays_unknown(self):
        r=M['retained_unknowns'][0]
        self.assertEqual((r['address'],r['size'],r['origin']['origin']),('0x00641DAA',11,'unknown'))
        self.reject(lambda m:m['retained_unknowns'][0]['origin'].update(origin='library'))

    def test_phase_subtraction_cannot_be_replaced_by_assumed_sine(self):
        self.reject(lambda m:next(i for r in m['anchors'] if r['address']=='0x0041CB70' for i in r['instructions'] if i['mnemonic']=='fsub').update(mnemonic='fadd'),True)

    def test_whole_cosine_source_and_interior_c_entry(self):
        functions={r['address']:r for r in V.rows('config/functions.csv')}
        origins={r['address']:r for r in V.rows('config/function-origins.csv')}
        V.verify_external(M,self.target,self.c,functions,origins)
        m=copy.deepcopy(M);m['cos_entry']['record']['source_offset']=19
        with self.assertRaises(ValueError): V.verify_external(m,self.target,self.c,functions,origins)

    def test_virtual_table_range_is_used_span_not_runtime_content_hash(self):
        self.assertEqual(M['table_span']['size'],14400)
        math=V.module('polar_test_table','verify-math-table-policy-origins.py')
        math.verify_table_span(self.target,M['table_span'])
        with self.assertRaises(ValueError):math.verify_table_span(self.target,dict(M['table_span'],size=0x10000000))

    def test_all_six_independent_contexts_are_whole(self):
        self.assertEqual(sum(r['size'] for r in M['anchors']),5122)
        self.reject(lambda m:m['anchors'].pop())


if __name__=='__main__':unittest.main()
