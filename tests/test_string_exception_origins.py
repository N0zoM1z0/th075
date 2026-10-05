"""Protect contextual provider identity, whole throw extents and source-owned graphs."""
import copy
import importlib.util
import json
from pathlib import Path
import struct
import unittest

ROOT=Path(__file__).resolve().parents[1]
SPEC=importlib.util.spec_from_file_location('string_exception_tests',ROOT/'scripts/verify-string-exception-origins.py')
V=importlib.util.module_from_spec(SPEC);SPEC.loader.exec_module(V)
M=json.loads((ROOT/V.EVIDENCE).read_text())


class StringExceptionPlanTests(unittest.TestCase):
    def reject(self,change):
        m=copy.deepcopy(M);change(m)
        with self.assertRaises(ValueError):V.verify_plan(m)

    def test_complete_plan_and_original_pins(self):
        V.verify_plan(M)
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        for path,sha in M['retained_sha256'].items():self.assertEqual(V.digest((ROOT/path).read_bytes()),sha,path)

    def test_only_two_unchanged64_byte_providers(self):
        self.assertEqual({r['address']:r['size'] for r in M['functions']},V.KEYS)
        self.reject(lambda m:m['functions'][0]['accepted_function'].update(size='63'))

    def test_no_source_private_abi_or_exact_credit(self):
        for key,value in [('source_file','game.cpp'),('signature','Private*'),('calling_convention','cdecl'),('match_percent','100.00')]:
            self.reject(lambda m:m['functions'][0]['accepted_function'].update({key:value}))

    def test_two_full_original_archives_remain_distinct(self):
        self.assertNotEqual(M['vendor_groups'][0]['archive_sha256'],M['vendor_groups'][1]['archive_sha256'])
        self.reject(lambda m:m['vendor_groups'][1].update(member_sha256=m['vendor_groups'][0]['member_sha256']))

    def test_whole_rtti_vtable_prefix_not_dropped(self):
        tables=[r for r in M['vendor_groups'][0]['sections'] if r['symbol'].startswith('??_7')]
        self.assertEqual([r['size'] for r in tables],[12,12])
        self.assertTrue(all(next(d for d in r['source']['definitions'] if d['symbol']==r['symbol'])['offset']==4 for r in tables))
        self.reject(lambda m:next(r for r in m['vendor_groups'][0]['sections'] if r['symbol'].startswith('??_7')).update(size=8))

    def test_entire_eh_cleanup_and_handler_sections(self):
        rows=[r for r in M['vendor_groups'][0]['sections'] if r['kind']=='code' and r['base'] not in V.KEYS]
        self.assertEqual([(r['size'],r['roots']) for r in rows],[(18,[0,8]),(18,[0,8])])
        self.reject(lambda m:next(r for r in m['vendor_groups'][0]['sections'] if r['base']=='0x00656CD0')['roots'].pop())

    def test_every_real_field_index_and_aux_is_retained(self):
        self.assertEqual(sum(len(r['fields']) for r in M['vendor_groups'][0]['sections']),70)
        self.reject(lambda m:m['vendor_groups'][0]['sections'][0]['fields'].pop())
        self.reject(lambda m:m['vendor_groups'][0]['sections'][0]['source']['aux_records'].pop())

    def test_sdk_parent_external_declarations_are_actual_fields(self):
        self.assertEqual([(p['base'],p['size'],p['call_offset']) for p in M['parents']],
                         [('0x00404D30',178,25),('0x00404EF0',141,23),('0x00405010',151,25)])
        self.reject(lambda m:m['parents'][0]['field'].update(symbol='?invalid_position@OrdinaryStringFailure@@QBEXXZ'))

    def test_ordinary_whole_graph_also_matches_without_provider_identity(self):
        a,b=M['public_groups']
        self.assertEqual([(r['base'],r['body_sha256']) for r in a['sections']],[(r['base'],r['body_sha256']) for r in b['sections']])
        self.assertNotEqual(a['sections'][0]['symbol'],b['sections'][0]['symbol'])
        self.reject(lambda m:m['public_groups'].pop())

    def test_whole_ordinary_emission_and_public_object_observations(self):
        control=M['public_control']
        self.assertEqual((len(control['emission']),sum(r['size'] for r in control['emission'])),(119,2712))
        self.assertEqual(control['layout_values'],[1,1,28,40,40])
        self.reject(lambda m:m['public_control']['emission'].pop())

    def test_literal_historical_unknowns_remain_immutable(self):
        self.assertEqual(len(M['historical_snapshots']),8)
        self.reject(lambda m:m['historical_snapshots'][0]['record']['function'].update(owner='library'))

    def test_actual_weak_fallback_cannot_be_invented(self):
        group=M['vendor_groups'][0];refs=group['weak_references']
        self.assertEqual(len(refs),2)
        shared={r['fallback_symbol']:0x1000+i for i,r in enumerate(refs)}
        # Native field observations cannot supply a missing strong source owner.
        with self.assertRaises(ValueError):V.graph_catalog([],{},group['id'],refs)
        bad=copy.deepcopy(refs);bad[0]['fallback_definition']['storage']=3
        with self.assertRaises(ValueError):V.graph_catalog([],shared,group['id'],bad)

    def test_duplicate_source_owner_and_native_override_rejected(self):
        row=M['vendor_groups'][0]['sections'][0]
        symbol=next(d['symbol'] for d in row['source']['definitions'] if d['storage']==2)
        with self.assertRaises(ValueError):V.graph_catalog([row,row],{},'libcpmt.lib',[])
        with self.assertRaises(ValueError):V.graph_catalog([row],{symbol:1},'libcpmt.lib',[])


@unittest.skipUnless((ROOT/'resources/th075.exe').is_file(),'private pinned target is not supplied')
class StringExceptionNativeTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.c=V.module('string_test_target','compare-coff-function.py');cls.target=cls.c.verified_target()
        cls.flow=V.module('string_test_flow','sdk_image_carriers.py')

    def test_complete_native_providers_and_independent_callers(self):
        V.verify_native(M,self.target,self.c,self.flow)

    def test_parent_call_destination_and_real_field_are_checked(self):
        m=copy.deepcopy(M);m['parents'][0]['callee']='0x00654B0E'
        with self.assertRaises(ValueError):V.verify_native(m,self.target,self.c,self.flow)
        m=copy.deepcopy(M);m['parents'][0]['field']['symbol_index']=0
        with self.assertRaises(ValueError):V.verify_native(m,self.target,self.c,self.flow)

    def prove(self,raw,fields):
        a=0x654ace;calls={};data={}
        for f in fields:
            at=f['offset']
            if f['type']=='REL32':calls[a+at]=(a+at+4+struct.unpack_from('<i',raw,at)[0])&0xffffffff
            else:data[a+at]=struct.unpack_from('<I',raw,at)[0]
        return V.provider_flow(raw,a,fields,calls,data,self.flow)

    def test_terminal_int3_is_complete_source_byte_not_fake_return(self):
        raw=bytearray(self.c.pe_bytes_at(self.target,0x654ace,64));fields=M['vendor_groups'][0]['sections'][0]['fields']
        result=self.prove(raw,fields);self.assertEqual(result['reachable_instruction_count'],16)
        with self.assertRaises(ValueError):self.prove(raw[:-1],fields)
        raw[-1]=0xc3
        with self.assertRaises(ValueError):self.prove(raw,fields)

    def test_throw_is_bound_to_real_runtime_not_a_named_unknown_call(self):
        raw=self.c.pe_bytes_at(self.target,0x654ace,64);fields=copy.deepcopy(M['vendor_groups'][0]['sections'][0]['fields'])
        fields[-1]['symbol']='_unknown_throw'
        with self.assertRaises(ValueError):self.prove(raw,fields)


if __name__=='__main__':unittest.main()
