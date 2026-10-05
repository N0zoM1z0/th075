"""Guard original aligned-buffer policy, complete tails and source ownership."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('aligned_tests',ROOT/'scripts/verify-sdk-aligned-buffer-origins.py')
V = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(V)
M = json.loads((ROOT/V.EVIDENCE).read_text())


class AlignedBufferPlanTests(unittest.TestCase):
    def reject(self,change):
        m = copy.deepcopy(M);change(m)
        with self.assertRaises(ValueError): V.verify_plan(m)

    def test_complete_immutable_review_and_inputs(self):
        V.verify_plan(M)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        for path,sha in M['retained_sha256'].items(): self.assertEqual(V.digest((ROOT/path).read_bytes()),sha,path)

    def test_original27_byte_extent_has_a_real_external_base_tail(self):
        root = next(q for q in M['sections'] if q['base']=='0x0061FEDB')
        self.assertEqual((root['size'],root['flow']['returns'],root['flow']['tails']),
                         (27,[],[{'offset':22,'destination':'0x0061FE0A'}]))
        self.reject(lambda m:m['functions'][0]['accepted_function'].update(size='26'))

    def test_no_private_declaration_or_exact_credit(self):
        for key,value in [('source_file','PrivateSDK.cpp'),('signature','CD3DXBufferA16*'),
                          ('calling_convention','thiscall'),('match_percent','100.00')]:
            self.reject(lambda m:m['functions'][0]['accepted_function'].update({key:value}))

    def test_complete_source_carriers_and_all_actual_fields(self):
        self.assertEqual((len(M['sections']),sum(q['size'] for q in M['sections']),
                          sum(len(q['fields']) for q in M['sections'])),(15,494,30))
        self.reject(lambda m:m['sections'][0]['bindings'].pop())

    def test_both_complete_original_seven_slot_tables(self):
        tables = [q for q in M['sections'] if q['kind']=='data']
        self.assertEqual([(q['size'],len(q['fields'])) for q in tables],[(28,7),(28,7)])
        self.reject(lambda m:m['sections'][2]['source']['aux_records'].clear())

    def test_original_weak_fallbacks_have_positive_owning_definitions(self):
        self.assertEqual(len(M['weak_references']),2)
        self.assertTrue(all(q['fallback_definition']['section']>0 for q in M['weak_references']))
        self.reject(lambda m:m['weak_references'][0].update(fallback_symbol='invented'))

    def test_factory_and_alignment_init_are_complete_source_owners(self):
        self.assertIn((87,'0x00620188'),[(q['size'],q['base']) for q in M['sections']])
        self.assertIn((49,'0x0061FF12'),[(q['size'],q['base']) for q in M['sections']])
        self.reject(lambda m:next(q for q in m['sections'] if q['base']=='0x0061FF12').update(size=46))

    def test_scalar_providers_use_full_runtime_source_owners(self):
        self.assertEqual([q['size'] for q in M['providers']],[5,14])
        self.assertEqual([q['record']['size'] for q in M['runtime_owners']],[44,113])
        self.reject(lambda m:m['runtime_owners'][0]['record'].update(address='0x00644300'))

    def test_entire_generic_emission_and_natural_layout(self):
        control = M['public_control']
        self.assertEqual((len(control['emission']),sum(q['size'] for q in control['emission'])),(17,315))
        self.assertEqual(control['layout_values'],[16,16,16,16,4,4])
        self.reject(lambda m:m['public_control']['emission'].pop())

    def test_full_default_and_empty_policy_controls_are_distinct_observations(self):
        controls = M['public_control']['methods']
        default = next(q for q in controls if q['symbol'].startswith('??1Default'))
        empty = next(q for q in controls if q['symbol'].startswith('??1Empty'))
        self.assertEqual((default['source']['size'],empty['source']['size']),(5,11))
        self.assertEqual([i['mnemonic'] for i in default['instructions']],['jmp'])
        self.reject(lambda m:m['public_control']['methods'].pop())

    def test_original_guid_source_and_uuid_member_are_frozen(self):
        self.assertEqual([q['symbol'] for q in M['guids']],['_IID_IUnknown','_IID_ID3DXBuffer'])
        self.assertEqual(len(M['guid_control']['emission']),47)
        self.reject(lambda m:m['guids'][0].update(member_offset=0))

    def test_all_eight_private_lifetimes_remain_unknown(self):
        self.assertEqual(len(M['retained_unknowns']),8)
        self.assertTrue(all(q['origin']['origin']=='unknown' for q in M['retained_unknowns']))
        self.reject(lambda m:m['retained_unknowns'][0]['origin'].update(origin='compiler'))

    def test_three_generated_deleting_wrappers_remain_separate(self):
        self.assertEqual(len(M['wrappers']),3)
        self.assertTrue(all(q['origin']['origin']=='compiler' for q in M['wrappers']))
        self.reject(lambda m:m['wrappers'][0]['origin'].update(origin='library'))

    def test_original_member_aux_and_debug_provenance_cannot_be_dropped(self):
        self.assertEqual(M['member']['member_offset'],380178)
        self.reject(lambda m:m['sections'][0]['source']['aux_records'].clear())


@unittest.skipUnless((ROOT/'resources/th075.exe').is_file(),'private pinned target is not supplied')
class AlignedBufferNativeTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.c = V.module('aligned_test_target','compare-coff-function.py');cls.target = cls.c.verified_target()
        cls.flow = V.module('aligned_test_flow','sdk_image_carriers.py')

    def test_complete_allocation_prefix_write_and_recovery_tail(self):
        V.verify_native(M,self.target,self.c,self.flow)

    def test_wrong_pointer_prefix_and_base_tail_are_rejected(self):
        raw = self.c.pe_bytes_at(self.target,0x61fedb,27)
        for offset,value in [(2,8),(16,0),(22,0xc3)]:
            changed = bytearray(raw);changed[offset]=value
            with self.assertRaises(ValueError): V.prefix_policy(changed,0x61fedb,self.flow)


if __name__=='__main__': unittest.main()
