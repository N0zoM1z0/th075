"""Keep full SDK GUID identity, unresolved callbacks and strict origin transitions."""
import copy,importlib.util,json,struct,unittest
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('interface_tests',ROOT/'scripts/verify-sdk-interface-origins.py');V=importlib.util.module_from_spec(spec);spec.loader.exec_module(V)
OLD=V.module('interface_old_tests','verify-sdk-debug-parent-origins.py')
class SDKInterfaceEvidenceTests(unittest.TestCase):
    def setUp(self):self.m=json.loads((ROOT/V.EVIDENCE).read_text())
    def test_complete_scope_and_digest(self):
        V.verify_plan(self.m);self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
    def test_interface_names_do_not_replace_guid_identity(self):
        self.m['guids'][1]['address']='0x0065DDCC'
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_cold_scalar_definition_cannot_be_relabelled(self):
        self.m['guids'][1]['definitions'][0]['symbol']='_IID_ID3DXSprite'
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_complete_target_extent_is_not_truncated(self):
        self.m['functions'][0]['size']=70
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_full_table_is_not_reduced_to_known_slots(self):
        self.m['tables'][1]['size']=36
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_opaque_callback_cannot_gain_linkage(self):
        r=next(r for r in self.m['code'] if r['symbol'] in V.OPAQUE);r['bindings']=[]
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_wrong_interface_negative_cannot_mask_pointer(self):
        self.m['negatives'][0]['differences']=[]
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_full_negative_is_not_a_convenient_prefix(self):
        self.m['negatives'][0]['size']=35
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_library_evidence_cannot_grant_exact_credit(self):
        self.m['functions'][0]['accepted_function']['match_percent']='100.00'
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_no_original_abi_or_owner_layout_is_invented(self):
        self.m['functions'][0]['accepted_function']['signature']='invented'
        with self.assertRaises(ValueError):V.verify_plan(self.m)
    def test_real_field_requires_complete_catalogue_identity(self):
        f=dict(offset=1,type_id=20,type='REL32',symbol='_callee',addend=0,local_symbol_offset=None);b=dict(f,target_address='0x00402000')
        with self.assertRaises(ValueError):V.link_code(b'\xe8\0\0\0\0\xc3',[f],[b],0x401000,{})
        linked,_,_=V.link_code(b'\xe8\0\0\0\0\xc3',[f],[b],0x401000,{'_callee':0x402000});self.assertEqual(struct.unpack_from('<I',linked,1)[0],0xffb)
    def test_opaque_name_cannot_become_a_known_code_callee(self):
        name=next(iter(V.OPAQUE));f=dict(offset=1,type_id=20,type='REL32',symbol=name,addend=0,local_symbol_offset=None);b=dict(f,target_address='0x00402000')
        with self.assertRaises(ValueError):V.link_code(b'\xe8\0\0\0\0\xc3',[f],[b],0x401000,{name:0x402000})
    def test_prior_pending_record_allows_only_exact_new_transition(self):
        p=json.loads((ROOT/OLD.EVIDENCE).read_text())['pending'];r=next(r for r in self.m['functions'] if r['address']==p['address'])
        self.assertTrue(OLD.pending_ledger_matches(p,p['function'],p['origin']))
        self.assertTrue(OLD.pending_ledger_matches(p,r['accepted_function'],r['accepted_origin']))
        changed=copy.deepcopy(r['accepted_function']);changed['size']='37';self.assertFalse(OLD.pending_ledger_matches(p,changed,r['accepted_origin']))
        changed=copy.deepcopy(r['accepted_origin']);changed['evidence_id']='invented';self.assertFalse(OLD.pending_ledger_matches(p,r['accepted_function'],changed))
    def test_prior_pending_transition_cannot_grant_source_or_abi(self):
        p=json.loads((ROOT/OLD.EVIDENCE).read_text())['pending'];r=next(r for r in self.m['functions'] if r['address']==p['address'])
        for key,value in [('source_file','invented.cpp'),('calling_convention','cdecl'),('match_percent','100.00')]:
            changed=dict(r['accepted_function'],**{key:value});self.assertFalse(OLD.pending_ledger_matches(p,changed,r['accepted_origin']))
if __name__=='__main__':unittest.main()
