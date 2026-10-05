"""Guard complete blit/codec ownership, source scopes and constructor alternatives."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT=Path(__file__).resolve().parents[1]
SPEC=importlib.util.spec_from_file_location('test_blit',ROOT/'scripts/verify-sdk-blit-origins.py')
V=importlib.util.module_from_spec(SPEC);SPEC.loader.exec_module(V)
M=json.loads((ROOT/V.EVIDENCE).read_text())


class BlitProvenanceTests(unittest.TestCase):
    def reject(self,mutate):
        m=copy.deepcopy(M);mutate(m)
        with self.assertRaises(ValueError):V.verify_plan(m)

    def test_original_whole_manifest_and_bounded_plan(self):
        self.assertEqual(V.digest((ROOT/V.EVIDENCE).read_bytes()),V.MANIFEST_SHA256)
        V.verify_plan(M)

    def test_all_prior_source_and_proof_hashes_are_fixed(self):
        for path,sha in M['retained_sha256'].items():
            self.assertEqual(V.digest((ROOT/path).read_bytes()),sha,path)

    def test_no_source_private_abi_or_exact_credit(self):
        for change in [dict(source_file='new.cpp'),dict(signature='private-owner'),dict(match_percent='100.00')]:
            self.reject(lambda m:m['functions'][0]['accepted_function'].update(change))

    def test_whole_codec_switch_table_required(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['base']=='0x0061A4CC').update(size=1824))

    def test_whole_box_switch_table_required(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['base']=='0x006131C5').update(size=1027))

    def test_codec_unsigned_bound_required(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['base']=='0x0061A4CC')['switch'].update(maximum=15))

    def test_box_actual_index_register_required(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['base']=='0x006131C5')['switch'].update(register='eax'))

    def test_every_real_original_field_required(self):
        self.reject(lambda m:m['sections'][0]['fields'].pop())

    def test_every_independent_binding_required(self):
        self.reject(lambda m:m['sections'][0]['bindings'].pop())

    def test_actual_weak_aux_mode_required(self):
        self.reject(lambda m:m['weak_references'][0].update(search_characteristics=3))

    def test_actual_same_member_fallback_required(self):
        self.reject(lambda m:m['weak_references'][0].update(fallback_symbol='guessed'))

    def test_all_weak_fallbacks_required(self):
        self.reject(lambda m:m['weak_references'].pop())

    def test_mutable_slots_cannot_gain_one_fixed_runtime_mapping(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['base']=='0x00611E9C')['dispatch_paths'].pop())

    def test_register_tail_cannot_lose_scalar_choice(self):
        self.reject(lambda m:next(r for r in m['sections'] if r['base']=='0x00611F00')['flow']['tails'][0]['alternatives'].pop())

    def test_static_functions_keep_both_actual_owner_scopes(self):
        pe=V.module('test_blit_key_prior','verify-sdk-x3d-origins.py')
        fields=[(r['member_offset'],f) for r in M['sections'] for f in r.get('fields',[])
                if f['symbol']=='?F2IBegin@@YAXXZ']
        self.assertEqual({owner for owner,f in fields},{1376096,1355416})
        for owner,f in fields:
            self.assertEqual(V.source_key(owner,f,pe),(owner,f['symbol_section'],f['symbol_index']))
            self.assertNotEqual(V.source_key(owner,f,pe),f['symbol'])

    def test_no_unexplained_legacy_script_upgrade(self):
        self.reject(lambda m:m['replay_script_transitions'].update(arbitrary={'accepted_sha256':'0'*64}))

    def test_original_end_context_cannot_be_overwritten(self):
        self.reject(lambda m:m['retained_end_context'].update(comparison='body-positive'))

    def test_exact_end_transition_cannot_change_signature(self):
        self.reject(lambda m:next(r for r in m['functions'] if r['address']=='0x0060BE10')['accepted_function'].update(signature='private'))

    def test_legacy_end_gate_accepts_only_complete_reviewed_pair(self):
        api=V.module('test_blit_old_end','verify-sdk-interface-origins.py')
        r=next(r for r in M['functions'] if r['address']=='0x0060BE10')
        self.assertTrue(api.reviewed_end_anchor_matches(r['source_record'],r['accepted_function'],r['accepted_origin']))
        self.assertTrue(api.reviewed_destructor_anchor_matches(r['source_record'],r['original_function'],r['original_origin']))
        for change in [dict(size='226'),dict(signature='private'),dict(evidence='other')]:
            self.assertFalse(api.reviewed_end_anchor_matches(r['source_record'],dict(r['accepted_function'],**change),r['accepted_origin']))
        old=copy.deepcopy(r['source_record']);old['comparison']='body-positive'
        self.assertFalse(api.reviewed_end_anchor_matches(old,r['accepted_function'],r['accepted_origin']))
        self.assertFalse(api.reviewed_end_anchor_matches(r['source_record'],r['accepted_function'],dict(r['accepted_origin'],origin='authored')))

    def test_legacy_script_hash_exceptions_are_exact_pairs(self):
        for filename in ['verify-sdk-destructor-origins.py','verify-sdk-x86-policy-origins.py',
                         'verify-sdk-graphics-origins.py','verify-sdk-cube-volume-origins.py',
                         'verify-sdk-resource-lock-origins.py','verify-sdk-mmx-origins.py']:
            verifier=V.module('test_blit_pairs_'+filename,filename)
            for path,transition in M['replay_script_transitions'].items():
                self.assertTrue(verifier.retained_digest_matches(path,transition['accepted_sha256']))
                self.assertFalse(verifier.retained_digest_matches(path,'0'*64))


    def test_explicit_constructor_needs_real_whole_callers(self):
        self.reject(lambda m:m['constructor_callers'][m['constructor_functions'][0]].clear())

    def test_pointer_constructor_cannot_be_implicit_copy(self):
        self.reject(lambda m:next(r for r in m['functions'] if r['address'] in m['constructor_functions']).update(symbol='??0ImplicitCopy@@QAE@ABV0@@Z'))

    def test_constructor_cannot_reuse_policy_confidence(self):
        self.reject(lambda m:next(r for r in m['functions'] if r['address'] in m['constructor_functions'])['accepted_origin'].update(confidence='policy'))

    def test_six_other_lifetime_alternatives_remain_independent(self):
        self.reject(lambda m:m['retained_unknown'].pop())

    def test_full_crt_vector_cleanup_extent_required(self):
        self.reject(lambda m:next(r for r in m['anchors'] if r.get('kind')=='CRT-COMDAT')['comparison'].update(size=74))

    def test_floor_primary_cannot_replace_shared_carrier(self):
        self.reject(lambda m:m['floor_carrier'].update(size=64))

    def test_all_interior_compiler_rows_are_preserved(self):
        self.reject(lambda m:m['interiors'].pop())

    def test_complete_public_control_required(self):
        self.reject(lambda m:m['public_control']['emission'].pop())

    def test_all_default_copy_constructor_alternatives_required(self):
        self.reject(lambda m:m['constructor_control']['emission'].pop())

    def test_observer_layout_is_not_a_private_codec_layout(self):
        self.reject(lambda m:m['constructor_control']['layout']['values'].__setitem__(0,0x106c))


if __name__=='__main__':
    unittest.main()
