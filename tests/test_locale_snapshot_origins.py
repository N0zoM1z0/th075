import importlib.util
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('locale_snapshot', ROOT / 'scripts/verify-locale-snapshot-origins.py')
REVIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class LocaleSnapshotOriginTests(unittest.TestCase):
    def setUp(self):
        self.m = REVIEW.manifest()
        self.rows = {r['address']: r for r in self.m['functions']}
        self.graph = {r['address']: r for r in self.m['functions'] + self.m['anchors']}

    def reject(self, message):
        with self.assertRaisesRegex(ValueError, message):
            REVIEW.verify_plan(self.m)

    def state(self, name):
        return next(r for r in self.m['state_data'] if r['symbol'] == name)

    def test_complete_plan_is_supported(self):
        REVIEW.verify_plan(self.m)

    def test_time_snapshot_requires_all_copy_and_relocation_exits(self):
        self.rows['0x0064B749']['size'] = 559
        self.reject('complete own auxiliary extent')

    def test_days_requires_terminating_null_and_return(self):
        self.rows['0x0064B635']['code_size'] = 123
        self.reject('complete own auxiliary extent')

    def test_alpha_requires_both_full_branches(self):
        self.rows['0x0064274D']['code_size'] = 46
        self.reject('complete own auxiliary extent')

    def test_snapshot_cannot_gain_invented_interior_entry(self):
        self.m['interior_labels'] = [dict(address='0x0064B836')]
        self.reject('shared entries')

    def test_snapshot_cannot_gain_unsupported_scope(self):
        self.m['scope_tables'] = [dict(address='0x006626A0')]
        self.reject('unsupported owners/scopes')

    def test_snapshot_requires_whole_184_byte_time_record(self):
        self.state('___lc_time_c')['size'] = 172
        self.reject('complete defining sections')

    def test_snapshot_requires_all_43_defining_string_pointers(self):
        self.state('___lc_time_c')['relocations'].pop()
        self.reject('all 43 defining strings')

    def test_snapshot_requires_last_time_format_pointer(self):
        self.state('___lc_time_c')['relocations'][-1]['offset'] = 164
        self.reject('all 43 defining strings')

    def test_initial_locale_requires_whole_403_byte_carrier(self):
        self.state('__clocalestr')['size'] = 84
        self.reject('complete defining sections')

    def test_ctype_requires_whole_combined_carrier(self):
        self.state('___newctype')['size'] = 514
        self.reject('complete defining sections')

    def test_snapshot_cannot_assume_atomic_runtime_consistency(self):
        self.m['snapshot_protocol']['basis'] = 'coherent current locale snapshot'
        self.reject('ownership/layout/classification ABI')

    def test_snapshot_keeps_real_pointer_offsets(self):
        self.m['sdk_layout']['objects'][0]['values'][24] = 68
        self.reject('operation/layout controls')

    def test_snapshot_requires_unsigned_short_classification(self):
        self.m['snapshot_protocol']['ctype_width'] = 4
        self.reject('ownership/layout/classification ABI')

    def test_alpha_and_alnum_masks_cannot_be_conflated(self):
        self.m['snapshot_protocol']['classification_alnum'] = 259
        self.reject('ownership/layout/classification ABI')

    def test_original_eof_is_minus_one(self):
        self.m['sdk_layout']['objects'][0]['values'][-1] = 255
        self.reject('operation/layout controls')

    def test_copy_control_requires_complete_record(self):
        self.m['call_controls'][0]['instructions'][2]['operands'] = '0xac'
        self.reject('ownership/layout/classification ABI')

    def test_classification_control_requires_real_worker(self):
        self.m['call_controls'][1]['relocation_metadata'][0]['symbol'] = '_isctype'
        self.reject('ownership/layout/classification ABI')

    def test_defining_function_versions_require_actual_source(self):
        self.m['vendor_sources'].pop('crt/src/_ctype.c')
        self.reject('source/header context')

    def test_retained_time_and_locale_graph_is_required(self):
        self.m['retained_controls'] = []
        self.reject('independently retained')

    def test_alpha_requires_actual_unsigned_word_load(self):
        self.rows['0x0064274D']['instruction_witnesses'] = [w for w in self.rows['0x0064274D']['instruction_witnesses'] if w['mnemonic'] != 'movzx']
        self.reject('actual copy/separator/classification')

    def test_alnum_requires_actual_digit_mask(self):
        self.rows['0x006428ED']['instruction_witnesses'] = [w for w in self.rows['0x006428ED']['instruction_witnesses'] if w['operands'] != 'eax, 0x107']
        self.reject('actual copy/separator/classification')

    def test_months_require_actual_separator(self):
        self.rows['0x0064B6B4']['instruction_witnesses'] = [w for w in self.rows['0x0064B6B4']['instruction_witnesses'] if w['operands'] != 'byte ptr [esi], 0x3a']
        self.reject('actual copy/separator/classification')

    def test_snapshot_requires_actual_full_record_copy(self):
        self.rows['0x0064B749']['instruction_witnesses'] = [w for w in self.rows['0x0064B749']['instruction_witnesses'] if w['operands'] != '0xb8']
        self.reject('actual copy/separator/classification')

    def test_memcpy_requires_829_byte_source_owner(self):
        self.graph['0x00640F20']['size'] = 709
        self.reject('independent complete anchors')

    def test_memcpy_tables_cannot_be_treated_as_instructions(self):
        self.graph['0x00640F20']['code_regions'] = [dict(offset=0, size=829)]
        self.reject('source code/data partition')

    def test_memcpy_requires_all_six_tables(self):
        self.graph['0x00640F20']['embedded_tables'].pop()
        self.reject('full six-table owner')

    def test_snapshot_cannot_gain_unresolved_indirect_call(self):
        self.rows['0x0064B749']['indirect_calls'] = [dict(site='0x0064B836', operand='eax')]
        self.reject('unsupported indirect dispatch')


if __name__ == '__main__':
    unittest.main()
