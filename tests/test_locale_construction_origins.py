import importlib.util
from pathlib import Path
import struct
from types import SimpleNamespace
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('locale_construction', ROOT / 'scripts/verify-locale-construction-origins.py')
REVIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(REVIEW)


class LocaleConstructionOriginTests(unittest.TestCase):
    def setUp(self):
        self.m = REVIEW.manifest()
        self.rows = {r['address']: r for r in self.m['functions']}
        self.graph = {r['address']: r for r in self.m['functions'] + self.m['auxiliary_bodies'] + self.m['anchors']}

    def reject(self, message):
        with self.assertRaisesRegex(ValueError, message):
            REVIEW.verify_plan(self.m)

    def state(self, symbol):
        return next(r for r in self.m['state_data'] if r['symbol'] == symbol)

    def test_complete_plan_is_supported(self):
        REVIEW.verify_plan(self.m)

    def test_time_owner_requires_failure_cleanup(self):
        self.rows['0x0064C25F']['size'] = 870
        self.reject('complete own auxiliary extent')

    def test_qualification_requires_full_exit(self):
        self.rows['0x0064D853']['code_size'] = 436
        self.reject('complete own auxiliary extent')

    def test_category_owner_requires_full_extent(self):
        self.rows['0x00643041']['span_end'] = '0x006432CC'
        self.reject('complete own auxiliary extent')

    def test_auxiliary_category_cannot_gain_inventory_credit(self):
        self.m['auxiliary_bodies'][0]['decision'] = 'library'
        self.reject('complete auxiliary owners')

    def test_enum_callback_cannot_gain_invented_interior_candidate(self):
        self.m['interior_labels'] = [dict(address='0x0064D45C')]
        self.reject('shared entries')

    def test_category_table_requires_all_record_fields(self):
        self.state('___lc_category')['relocations'].pop()
        self.reject('full source fields')

    def test_category_table_requires_real_callback_owner(self):
        self.m['category_dispatch']['entries'][2]['target_address'] = '0x0064CF9A'
        self.reject('six-record category callback graph')

    def test_registration_requires_actual_defining_member(self):
        self.rows['0x0064D357']['member_offset'] = 1389094
        self.reject('defining source owner')

    def test_callback_requires_stdcall_cleanup(self):
        self.rows['0x0064D45C']['body_facts']['returns'][0]['cleanup'] = 0
        self.reject('real RET 4')

    def test_fallback_query_requires_stdcall_cleanup(self):
        self.rows['0x0064D222']['body_facts']['returns'][0]['cleanup'] = 0
        self.reject('real RET 16')

    def test_registration_requires_installed_flag(self):
        self.m['callback_registrations'][2]['flag'] = 2
        self.reject('SDK enumeration registrations')

    def test_runtime_query_selection_cannot_be_assumed(self):
        self.m['query_dispatch']['basis'] = 'runtime API selected'
        self.reject('null/NT/API/fallback')

    def test_query_pointer_requires_full_bss_carrier(self):
        self.state('_iLcidState')['size'] = 32
        self.reject('complete defining sections')

    def test_query_pointer_requires_actual_last_definition(self):
        definitions = self.state('_iLcidState')['source_section']['definitions']
        next(d for d in definitions if d['symbol'] == '_pfnGetLocaleInfoA')['offset'] = 28
        self.reject('complete defining BSS carrier')

    def test_common_refcount_requires_complete_source_declaration(self):
        self.m['common_globals'][0]['source_definition']['offset'] = 8
        self.reject('COMMON declarations')

    def test_locale_cache_requires_full_combined_carrier(self):
        self.state('__clocalestr')['size'] = 131
        self.reject('complete defining sections')

    def test_ctype_requires_combined_carrier(self):
        self.state('___newctype')['size'] = 514
        self.reject('complete defining sections')

    def test_style_requires_nul_and_complete_character_storage(self):
        self.state('__ctype_loc_style')['size'] = 382
        self.reject('complete defining sections')

    def test_locale_id_is_six_bytes(self):
        self.m['locale_protocol']['locale_id_size'] = 12
        self.reject('layouts and cdecl/stdcall')

    def test_ctype_copy_preserves_actual_254_bytes(self):
        self.m['locale_protocol']['classification_copy_bytes'] = 256
        self.reject('layouts and cdecl/stdcall')

    def test_sdk_multibyte_limit_cannot_be_guessed(self):
        self.m['sdk_layout']['objects'][0]['values'][65] = 2
        self.reject('operation/layout controls')

    def test_category_init_control_requires_cdecl(self):
        self.m['call_controls'][2]['body_facts']['returns'][0]['cleanup'] = 4
        self.reject('layouts and cdecl/stdcall')

    def test_enum_api_control_requires_real_sdk_import(self):
        self.m['call_controls'][1]['relocation_metadata'][0]['symbol'] = '_EnumSystemLocalesA'
        self.reject('layouts and cdecl/stdcall')

    def test_memcpy_requires_vendor_table_source(self):
        self.m['vendor_sources'].pop('crt/src/intel/memcpy.asm')
        self.reject('defining vendor sources')

    def test_retained_input_and_runtime_graph_is_required(self):
        self.m['retained_controls'] = []
        self.reject('independently retained')

    def test_memcpy_requires_all_829_bytes(self):
        self.graph['0x00640F20']['size'] = 709
        self.reject('independent complete anchors')

    def test_memcpy_tables_cannot_be_decoded_as_code(self):
        self.graph['0x00640F20']['code_regions'] = [dict(offset=0, size=829)]
        self.reject('code/data partition')

    def test_memcpy_requires_all_six_tables(self):
        self.graph['0x00640F20']['embedded_tables'].pop()
        self.reject('six whole embedded tables')

    def dispatch_fixture(self):
        return {key: [SimpleNamespace(address=int(w['site'], 16), mnemonic=w['mnemonic'], op_str=w['operands'])
                      for w in row['instruction_witnesses']]
                for key, row in self.graph.items()}

    def test_scheduled_country_registration_is_supported(self):
        REVIEW.check_dispatch_instructions(self.m, self.dispatch_fixture())

    def test_actual_registration_rejects_wrong_flag(self):
        decoded = self.dispatch_fixture()
        next(i for i in decoded['0x0064D741'] if i.address == 0x64D754).op_str = '2'
        with self.assertRaisesRegex(ValueError, 'installed-flag/API'):
            REVIEW.check_dispatch_instructions(self.m, decoded)

    def test_actual_registration_rejects_wrong_import(self):
        decoded = self.dispatch_fixture()
        next(i for i in decoded['0x0064D741'] if i.address == 0x64D761).op_str = 'dword ptr [0x65711c]'
        with self.assertRaisesRegex(ValueError, 'installed-flag/API'):
            REVIEW.check_dispatch_instructions(self.m, decoded)

    def test_actual_registration_rejects_extra_stack_operation(self):
        decoded = self.dispatch_fixture()
        next(i for i in decoded['0x0064D741'] if i.address == 0x64D756).mnemonic = 'pop'
        with self.assertRaisesRegex(ValueError, 'installed-flag/API'):
            REVIEW.check_dispatch_instructions(self.m, decoded)

    def test_actual_category_rejects_wrong_table_slot(self):
        decoded = self.dispatch_fixture()
        next(i for i in decoded['0x00643041'] if i.address == 0x64326A).op_str = 'dword ptr [ebx + 0x6700bc]'
        with self.assertRaisesRegex(ValueError, 'initializer indirect instruction'):
            REVIEW.check_dispatch_instructions(self.m, decoded)

    def memcpy_fixture(self):
        row = self.graph['0x00640F20']
        raw = bytearray(row['size'])
        instructions = []
        for table in row['embedded_tables']:
            for entry in table['entries']:
                address = int(entry['target_address'], 16)
                struct.pack_into('<I', raw, entry['offset'], address)
                instructions.append(SimpleNamespace(address=address))
        return row, raw, instructions

    def test_complete_synthetic_memcpy_table_partition_is_supported(self):
        REVIEW.check_memcpy_partition(*self.memcpy_fixture())

    def test_actual_memcpy_table_rejects_wrong_case(self):
        row, raw, instructions = self.memcpy_fixture()
        struct.pack_into('<I', raw, 100, 0x640F84)
        with self.assertRaisesRegex(ValueError, 'actual code case starts'):
            REVIEW.check_memcpy_partition(row, raw, instructions)

    def test_actual_memcpy_partition_rejects_missing_region(self):
        row, raw, instructions = self.memcpy_fixture()
        row['code_regions'][0]['size'] = 99
        with self.assertRaisesRegex(ValueError, 'omits or pads'):
            REVIEW.check_memcpy_partition(row, raw, instructions)

    def test_actual_memcpy_table_rejects_code_overlap(self):
        row, raw, instructions = self.memcpy_fixture()
        row['code_regions'][0]['size'] = 101
        with self.assertRaisesRegex(ValueError, 'decoded as code'):
            REVIEW.check_memcpy_partition(row, raw, instructions)


if __name__ == '__main__':
    unittest.main()
