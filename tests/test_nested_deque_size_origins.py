"""Guard complete nested container provenance and independent unmasked field linkage."""
import importlib.util
from pathlib import Path
import struct
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('nested_review', ROOT / 'scripts/verify-nested-deque-size-origins.py')
REVIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class NestedDequeSizeTests(unittest.TestCase):
    def setUp(self):
        self.m = REVIEW.manifest()

    def reject(self):
        with self.assertRaises(ValueError):
            REVIEW.verify_plan(self.m)

    def test_complete_plan(self):
        REVIEW.verify_plan(self.m)

    def test_prefix_is_not_a_complete_getter(self):
        self.m['functions'][0]['size'] = 14
        self.reject()

    def test_count_control_does_not_gain_game_origin(self):
        self.m['functions'].append(dict(address='0x0045DD00', size=66, decision='authored'))
        self.reject()

    def test_outer_typing_cannot_be_flat_byte_shape(self):
        next(r for r in self.m['code'] if r['address'] == '0x00421550')['symbol'] = '?size@?$deque@E'
        self.reject()

    def test_inner_typing_cannot_be_outer_shape(self):
        next(r for r in self.m['code'] if r['address'] == '0x0045DD50')['symbol'] = '?size@?$deque@V?$deque@'
        self.reject()

    def test_complete_constant_cannot_be_literal_prefix(self):
        next(r for r in self.m['state_data'] if r['address'] == '0x00657B34')['size'] -= 1
        self.reject()

    def test_funcinfo_cannot_replace_its_whole_owner(self):
        next(r for r in self.m['state_data'] if r['address'] == '0x0066886C')['size'] = 28
        self.reject()

    def test_shared_copy_scope_cannot_be_truncated(self):
        next(r for r in self.m['state_data'] if r['address'] == '0x00667AD8')['size'] = 28
        self.reject()

    def test_code_carriers_cannot_be_omitted(self):
        self.m['code_carriers'].pop()
        self.reject()

    def test_independent_registered_frame_is_required(self):
        self.m['retained_frames'].pop()
        self.reject()

    def test_whole_parser_context_is_required(self):
        self.m['contexts'][0]['size'] = 2300
        self.reject()

    def test_returned_object_must_be_transferred_into_real_this_register(self):
        for w in self.m['contexts'][1]['instruction_windows']:
            for i in w:
                if i['address'] == '0x0045DD35': i['operands'] = 'ecx, edx'
        self.reject()

    def test_outer_size_and_back_must_use_same_observed_field(self):
        for w in self.m['contexts'][0]['instruction_windows']:
            for i in w:
                if i['address'] == '0x00420CEC': i['operands'] = 'ecx, 0x7e4'
        self.reject()

    def test_reviewed_child_name_does_not_replace_real_producer(self):
        for w in self.m['contexts'][0]['instruction_windows']:
            for i in w:
                if i['address'] == '0x00420949': i['operands'] = '0x421550'
        self.reject()

    def test_legacy_operation_name_remains_a_distinct_observation(self):
        self.m['retained_legacy_helper']['evidence_id'] = 'R150'
        self.reject()

    def test_complete_fields_are_linked_unmasked_with_correct_pc_base(self):
        fields = [dict(offset=0, type='DIR32', symbol='data', addend=4),
                  dict(offset=4, type='REL32', symbol='callee', addend=0)]
        bindings = [dict(**fields[0], target_address='0x00002000'), dict(**fields[1], target_address='0x00001020')]
        linked = REVIEW.link_complete(bytes(8), fields, 0x1000, bindings, dict(data=0x2000, callee=0x1020))
        self.assertEqual(struct.unpack('<2I', linked), (0x2004, 0x18))

    def test_linker_cannot_override_independent_owner(self):
        field = dict(offset=0, type='DIR32', symbol='data', addend=0)
        with self.assertRaises(ValueError):
            REVIEW.link_complete(bytes(4), [field], 0x1000, [dict(**field, target_address='0x3000')], dict(data=0x2000))

    def test_unresolved_field_cannot_be_masked_out(self):
        field = dict(offset=0, type='DIR32', symbol='unknown', addend=0)
        with self.assertRaises(ValueError):
            REVIEW.link_complete(bytes(4), [field], 0x1000, [dict(**field, target_address='0x2000')], {})

    def test_overlapping_fields_do_not_gain_complete_credit(self):
        fields = [dict(offset=0, type='DIR32', symbol='data', addend=0), dict(offset=2, type='DIR32', symbol='data', addend=0)]
        bindings = [dict(**f, target_address='0x2000') for f in fields]
        with self.assertRaises(ValueError):
            REVIEW.link_complete(bytes(8), fields, 0x1000, bindings, dict(data=0x2000))

    def test_field_must_stay_inside_complete_owner(self):
        field = dict(offset=2, type='DIR32', symbol='data', addend=0)
        with self.assertRaises(ValueError):
            REVIEW.link_complete(bytes(4), [field], 0x1000, [dict(**field, target_address='0x2000')], dict(data=0x2000))
