import importlib.util
from pathlib import Path
import struct
from types import SimpleNamespace
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('locale_time_parent', ROOT / 'scripts/verify-locale-time-parent-origins.py')
REVIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class LocaleTimeParentOriginTests(unittest.TestCase):
    def setUp(self):
        self.m = REVIEW.manifest()
        self.rows = {r['address']: r for r in self.m['functions']}
        self.graph = {r['address']: r for r in self.m['functions'] + self.m['auxiliary_bodies'] + self.m['anchors']}

    def reject(self, message):
        with self.assertRaisesRegex(ValueError, message):
            REVIEW.verify_plan(self.m)

    def state(self, name):
        return next(r for r in self.m['state_data'] if r['symbol'] == name)

    def test_complete_plan_is_supported(self):
        REVIEW.verify_plan(self.m)

    def test_setlocale_requires_complete_finally_and_exit(self):
        self.rows['0x006434A9']['size'] = 329
        self.reject('complete own auxiliary extent')

    def test_winword_requires_full_localized_fallback(self):
        self.rows['0x0064BCB1']['size'] = 349
        self.reject('complete own auxiliary extent')

    def test_expandtime_requires_timezone_and_string_exit(self):
        self.rows['0x0064BA4B']['code_size'] = 600
        self.reject('complete own auxiliary extent')

    def test_auxiliary_categories_cannot_gain_inventory_credit(self):
        self.m['auxiliary_bodies'][0]['decision'] = 'library'
        self.reject('complete auxiliary owners')

    def test_finally_requires_existing_full_parent_entry(self):
        self.m['interior_labels'][0]['source_offset'] = 330
        self.reject('shared entries')

    def test_exception_filter_cannot_gain_new_candidate(self):
        self.m['interior_labels'].append(dict(address='0x0064BD84'))
        self.reject('shared entries')

    def test_scope_requires_finally_and_exception_records(self):
        self.m['scope_tables'].pop()
        self.reject('finally/exception scopes')

    def test_finally_scope_requires_real_cleanup_field(self):
        self.state('$T20508')['relocations'].pop()
        self.reject('actual defining fields')

    def test_exception_scope_requires_both_source_entries(self):
        self.state('$T20935')['relocations'].pop()
        self.reject('actual defining fields')

    def test_scope_requires_actual_defining_parent(self):
        self.state('$T20935')['relocations'][0]['code_entry']['owner'] = '0x006434A9'
        self.reject('defining source owner')

    def test_scope_requires_whole_parent_reference(self):
        next(b for b in self.rows['0x006434A9']['relocation_bindings'] if b['symbol'] == '$T20508')['target_address'] = '0x006626A0'
        self.reject('whole parent reference')

    def test_initial_locale_requires_whole_combined_carrier(self):
        self.state('__clocalestr')['size'] = 84
        self.reject('complete defining sections')

    def test_category_requires_all_seventeen_fields(self):
        self.state('___lc_category')['relocations'].pop()
        self.reject('actual defining callback fields')

    def test_common_pointer_requires_source_declaration(self):
        self.m['common_globals'][4]['size'] = 8
        self.reject('COMMON declarations')

    def test_thread_locale_requires_real_offset_100(self):
        self.m['sdk_layout']['objects'][0]['values'][43] = 132
        self.reject('operation/layout controls')

    def test_systemtime_requires_complete_sixteen_bytes(self):
        self.m['locale_parent_protocol']['systemtime_size'] = 14
        self.reject('layouts and cdecl/stdcall')

    def test_format_call_requires_twenty_four_caller_bytes(self):
        control = self.m['call_controls'][1]
        next(i for i in control['instructions'] if i['mnemonic'] == 'add')['operands'] = 'esp, 0x1c'
        self.reject('layouts and cdecl/stdcall')

    def test_expand_call_requires_twenty_eight_caller_bytes(self):
        self.m['locale_parent_protocol']['expand_caller_cleanup'] = 24
        self.reject('layouts and cdecl/stdcall')

    def test_sdk_formatter_requires_real_import_type(self):
        self.m['call_controls'][3]['relocation_metadata'][0]['symbol'] = '_GetDateFormatA'
        self.reject('layouts and cdecl/stdcall')

    def test_runtime_formatter_and_calendar_cannot_be_assumed(self):
        self.m['runtime_format_dispatch']['basis'] = 'current date API selected'
        self.reject('date/time API selection')

    def test_locale_lifetime_graph_must_remain_independent(self):
        self.m['retained_controls'] = []
        self.reject('independently retained')

    def test_time_defining_source_is_required(self):
        self.m['vendor_sources'].pop('crt/src/strftime.c')
        self.reject('source/header context')

    def fixture(self):
        decoded = {}
        for key, row in self.graph.items():
            witnesses = row['instruction_witnesses']
            decoded[key] = [SimpleNamespace(address=int(w['site'], 16), mnemonic=w['mnemonic'], op_str=w['operands'],
                            size=int(witnesses[i + 1]['site'], 16) - int(w['site'], 16) if i + 1 < len(witnesses) else 1)
                            for i, w in enumerate(witnesses)]
        records = {int(s['address'], 16): struct.pack('<iII', -1,
                   0 if s['filter_offset'] is None else int(s['parent'], 16) + s['filter_offset'],
                   int(s['parent'], 16) + s['handler_offset']) for s in self.m['scope_tables']}
        comparison = SimpleNamespace(pe_bytes_at=lambda target, address, size: records[address][:size])
        return decoded, records, comparison

    def test_actual_scope_and_api_contracts_are_supported(self):
        decoded, records, comparison = self.fixture()
        REVIEW.check_scopes(self.m, None, comparison, decoded)
        REVIEW.check_dispatch_instructions(self.m, decoded)

    def test_actual_finally_rejects_nonnull_filter(self):
        decoded, records, comparison = self.fixture()
        records[0x661180] = struct.pack('<iII', -1, 0x6435F2, 0x6435F2)
        with self.assertRaisesRegex(ValueError, 'enclosing/filter/handler'):
            REVIEW.check_scopes(self.m, None, comparison, decoded)

    def test_actual_finally_rejects_wrong_lock(self):
        decoded, records, comparison = self.fixture()
        next(i for i in decoded['0x006434A9'] if i.address == 0x6435F2).op_str = '0x8'
        with self.assertRaisesRegex(ValueError, 'SETLOCALE unlock'):
            REVIEW.check_scopes(self.m, None, comparison, decoded)

    def test_actual_filter_requires_return_one(self):
        decoded, records, comparison = self.fixture()
        next(i for i in decoded['0x0064BCB1'] if i.address == 0x64BD86).mnemonic = 'dec'
        with self.assertRaisesRegex(ValueError, 'return-one body'):
            REVIEW.check_scopes(self.m, None, comparison, decoded)

    def test_actual_handler_requires_stack_restoration(self):
        decoded, records, comparison = self.fixture()
        next(i for i in decoded['0x0064BCB1'] if i.address == 0x64BD88).op_str = 'esp, dword ptr [ebp - 0x14]'
        with self.assertRaisesRegex(ValueError, 'stack restoration/reset'):
            REVIEW.check_scopes(self.m, None, comparison, decoded)

    def test_actual_dispatch_rejects_wrong_api_selection(self):
        decoded, records, comparison = self.fixture()
        next(i for i in decoded['0x0064BCB1'] if i.address == 0x64BCFC).op_str = 'eax, dword ptr [0x657150]'
        with self.assertRaisesRegex(ValueError, 'raw SDK pointer selection'):
            REVIEW.check_dispatch_instructions(self.m, decoded)

    def test_actual_dispatch_requires_saved_output_slot(self):
        decoded, records, comparison = self.fixture()
        next(i for i in decoded['0x0064BCB1'] if i.address == 0x64BDCD).op_str = 'eax'
        with self.assertRaisesRegex(ValueError, 'sizing/output indirect'):
            REVIEW.check_dispatch_instructions(self.m, decoded)

    def test_actual_capacity_query_requires_null_destination(self):
        decoded, records, comparison = self.fixture()
        next(i for i in decoded['0x0064BCB1'] if i.address == 0x64BD49).op_str = 'edi'
        with self.assertRaisesRegex(ValueError, 'six-argument capacity/output'):
            REVIEW.check_dispatch_instructions(self.m, decoded)


if __name__ == '__main__':
    unittest.main()
