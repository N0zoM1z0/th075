"""Guard whole insertion/EH ownership, historical transitions and unknown lifetimes."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('insertion_tests', ROOT / 'scripts/verify-vector-insertion-carrier-origins.py')
V = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(V)
M = json.loads((ROOT / V.EVIDENCE).read_text())


class InsertionEvidenceTests(unittest.TestCase):
    def reject(self, mutate):
        m = copy.deepcopy(M); mutate(m)
        with self.assertRaises(ValueError): V.verify_plan(m)

    def test_complete_immutable_plan(self):
        self.assertEqual(V.digest((ROOT / V.EVIDENCE).read_bytes()), V.MANIFEST_SHA256)
        V.verify_plan(M)

    def test_original_source_pins(self):
        for path, sha in M['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT / path).read_bytes()), sha, path)

    def test_six_full_carriers_include_final_ret(self):
        self.assertEqual(sum(V.ROOTS.values()), 4866)
        self.reject(lambda m: m['groups'][0].update(whole_size=777))

    def test_no_first_ret_truncation(self):
        self.reject(lambda m: m['sections'][0].update(size=315))

    def test_all_twenty_audited_transitions(self):
        self.reject(lambda m: m['functions'].pop())
        self.assertEqual(sum(r['accepted_origin']['origin']=='library' for r in M['functions']),18)
        self.assertEqual(sum(r['accepted_origin']['origin']=='compiler' for r in M['functions']),2)

    def test_interiors_not_independent_extents(self):
        self.assertEqual(len(M['interiors']),14)
        self.reject(lambda m: m['interiors'].pop())

    def test_real_catch_offsets(self):
        self.assertEqual([g['whole_size'] for g in M['groups']],[796,796,796,814,834,830])
        self.reject(lambda m: m['interiors'][0].update(offset=314))

    def test_shared_epilogues_have_no_own_aux(self):
        tails=[r for r in M['interiors'] if r['role']=='shared-eh-epilogue']
        self.assertTrue(all(r['size']==19 and r['source_definitions']==[] for r in tails))
        self.reject(lambda m: next(r for r in m['interiors'] if r['role']=='shared-eh-epilogue').update(size=18))

    def test_tail_restoration_not_library_policy(self):
        self.reject(lambda m: next(r for r in m['functions'] if r['role']=='shared-eh-epilogue')['accepted_origin'].update(origin='library'))

    def test_cold_whole_source_aux_and_debug_provenance(self):
        self.reject(lambda m: m['sections'][0]['source']['aux_records'][1].update(aux_hex='00'*18))
        self.reject(lambda m: m['sections'][0]['source']['coff_line_table'].pop())

    def test_every_real_field(self):
        self.reject(lambda m: m['sections'][0]['fields'].pop())

    def test_every_real_binding(self):
        self.reject(lambda m: m['sections'][0]['bindings'].pop())

    def test_field_addends_not_destination_fitting(self):
        self.reject(lambda m: m['sections'][0]['fields'][0].update(addend=1))

    def test_scoped_source_indices(self):
        a,b=M['groups'][0],M['groups'][1]
        self.assertEqual(a['symbol'],b['symbol']); self.assertNotEqual(a['root'],b['root'])
        self.reject(lambda m: m['groups'][1].update(root=m['groups'][0]['root']))

    def test_all_eh_roots_and_reachable_instructions(self):
        self.assertEqual(M['sections'][0]['roots'],[0,315,579])
        self.reject(lambda m: m['sections'][0]['roots'].pop())
        self.reject(lambda m: m['sections'][0]['flow'].update(reachable_instruction_count=1))

    def test_full_eh_state_owner(self):
        self.assertTrue(any(r['kind']=='data' and r['size']==132 for r in M['sections']))
        self.reject(lambda m: next(r for r in m['sections'] if r['kind']=='data' and r['size']==132).update(size=36))

    def test_complete_canonical_interior_inventory(self):
        self.reject(lambda m: m['sections'][0]['inventory_entries'].pop())

    def test_generic_width_not_old_record_alias(self):
        self.assertEqual(M['groups'][5]['width'],16)
        self.reject(lambda m: m['groups'][5].update(width=116))

    def test_no_private_target_element_declaration(self):
        self.reject(lambda m: m['functions'][0]['accepted_function'].update(proposed_name='vector<Private>::insert'))

    def test_no_source_abi_or_exact_credit(self):
        for key,value in [('source_file','private.cpp'),('signature','Private*'),('calling_convention','cdecl'),('match_percent','100.00')]:
            self.reject(lambda m: m['functions'][0]['accepted_function'].update({key:value}))

    def test_original_unknown_preserved_as_history(self):
        self.reject(lambda m: m['functions'][0]['original_origin'].update(origin='library'))

    def test_actual_original_weak_aux(self):
        ref=M['weak_references'][0]
        self.assertEqual(len(bytes.fromhex(ref['aux_hex'])),18)
        self.assertEqual(ref['search_characteristics'],2)
        self.reject(lambda m: m['weak_references'][0].update(fallback_symbol_index=0))

    def test_weak_fallback_has_actual_complete_source_definition(self):
        self.assertGreater(M['weak_references'][0]['fallback_definition']['section'],0)
        self.reject(lambda m: m['weak_references'][0]['fallback_definition'].update(section=0))

    def test_real_absolute_crt_definition(self):
        self.reject(lambda m: m['absolute']['__except_list']['definition'].update(section=1))

    def test_retained_catalog_uses_owned_records(self):
        self.reject(lambda m: m['shared'][0]['owner']['record'].update(address='0x00000000'))

    def test_whole_authored_receiver_policy(self):
        self.assertEqual(M['opaque_api']['record']['size'],'75')
        self.reject(lambda m: m['opaque_api']['function'].update(size='19'))

    def test_actual_receiver_protocol_not_guessed_signature(self):
        self.reject(lambda m: m['opaque_api']['instructions'][3].update(operands='eax, ecx'))
        self.assertEqual(M['opaque_api']['function']['calling_convention'],'')

    def test_five_private_cleanup_alternatives_stay_unknown(self):
        self.assertEqual(len(M['retained_unknowns']),5)
        self.reject(lambda m: m['retained_unknowns'][0]['origin'].update(origin='compiler'))

    def test_complete_scalar_aggregate_fill_rejection(self):
        q=next(r for r in M['alternatives'] if r['role']=='rejected-full-fill')
        self.assertEqual(q['size'],36); self.assertEqual(len(q['differences']),5)
        self.reject(lambda m: next(r for r in m['alternatives'] if r['role']=='rejected-full-fill')['differences'].pop())

    def test_direct_delete_alternative_not_truncated_to_guarded_body(self):
        self.reject(lambda m: next(r for r in m['alternatives'] if r['role']=='rejected-direct-delete').update(size=43))

    def test_ordinary_destruction_retains_actual_private_call(self):
        self.reject(lambda m: next(r for r in m['alternatives'] if r['role']=='byte-equal-whole-destruction')['bindings'][0].update(target_address='0x0041A380'))

    def test_complete_ordinary_emission_and_original_headers(self):
        self.assertEqual(len(M['public_control']['emission']),334)
        self.assertEqual(sum(r['size'] for r in M['public_control']['emission']),20598)
        self.reject(lambda m: m['public_control']['emission'].pop())
        self.reject(lambda m: m['public_control']['headers'].pop(next(iter(m['public_control']['headers']))))

    def test_full_generic_layout_observations(self):
        self.assertEqual(M['public_control']['layout_values'],[4,16,16,4,4,16,16,16,44,16])
        self.reject(lambda m: m['public_control']['layout_values'].pop())

    def test_four_historical_r161_r162_snapshots_are_literal(self):
        self.assertEqual({r['record']['address'] for r in M['historical_snapshots']},{'0x0040A210','0x0040EDB0','0x0040EA30','0x005F9650'})
        self.reject(lambda m: m['historical_snapshots'][0]['record']['function'].update(size='796'))


class IndependentSourceCatalogTests(unittest.TestCase):
    def row(self, section, address, symbol='f'):
        return dict(base=address,source=dict(section=section,definitions=[dict(symbol=symbol,storage=2,offset=0)]),fields=[])

    def test_observed_binding_cannot_define_owner(self):
        r=self.row(2,'0x00002000');r['bindings']=[dict(symbol='unknown',source_base='0x00003000')]
        self.assertNotIn('unknown',V.owned_catalog([r],{},'G0',[]))

    def test_conflicting_whole_retained_owner_rejected(self):
        with self.assertRaises(ValueError):V.owned_catalog([self.row(2,'0x00002000')],{'f':0x3000},'G0',[])

    def test_local_symbol_needs_own_whole_section(self):
        r=self.row(2,'0x00002000');r['fields']=[dict(symbol_storage=3,symbol_section=3,symbol_index=7,symbol_offset=0)]
        with self.assertRaises(ValueError):V.owned_catalog([r],{},'G0',[])

    def test_same_debug_name_different_scoped_indices(self):
        r=self.row(2,'0x00002000');r['fields']=[dict(symbol_storage=3,symbol_section=2,symbol_index=7,symbol_offset=4)]
        c=V.owned_catalog([r],{},'G0',[])
        self.assertEqual(c[('G0',2,7)],0x2004);self.assertNotIn(('G1',2,7),c)

    def test_weak_observation_cannot_create_strong_source_owner(self):
        ref=dict(symbol='weak',fallback_symbol='f',fallback_definition=dict(section=3,offset=0))
        with self.assertRaises(ValueError):V.owned_catalog([self.row(2,'0x00002000')],{},'G0',[ref])


if __name__=='__main__':unittest.main()
