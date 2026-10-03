"""Reject unresolved CRT edges, zero-fill lookalikes and truncated archive extents."""
import importlib.util
import json
from pathlib import Path
import struct
import unittest

ROOT=Path(__file__).resolve().parents[1]
SPEC=importlib.util.spec_from_file_location('startup_dependencies',ROOT/'scripts/verify-startup-dependency-origins.py')
STARTUP=importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(STARTUP)


class StartupDependencyOriginTests(unittest.TestCase):
    def setUp(self):
        self.manifest=json.loads((ROOT/'config/startup-dependency-origin-evidence.json').read_text())
        self.rows={r['address']:r for r in self.manifest['functions']}

    def test_heap_callee_cannot_be_a_named_unknown_boundary(self):
        binding=next(b for b in self.rows['0x00649735']['relocation_bindings'] if b['target_kind']=='callee')
        binding['target_address']='0x006440A5'
        with self.assertRaisesRegex(ValueError,'complete independently compared source body'):
            STARTUP.verify_plan(self.manifest)

    def test_pending_error_chain_cannot_promote_an_edge(self):
        binding=self.rows['0x006422B2']['relocation_bindings'][1]
        binding['target_kind']='callee'
        with self.assertRaisesRegex(ValueError,'promotes an unverified binding'):
            STARTUP.verify_plan(self.manifest)

    def test_same_width_zero_globals_require_actual_version_result_fields(self):
        witness=next(w for w in self.manifest['entry_context']['instruction_witnesses'] if w['site']=='0x00642352')
        witness['operands']='ecx, dword ptr [esi + 4]'
        with self.assertRaisesRegex(ValueError,'result-field provenance'):
            STARTUP.verify_plan(self.manifest)

    def test_version_layout_requires_the_full_platform_field_offset(self):
        self.manifest['sdk_layout']['values'][-1]=12
        with self.assertRaisesRegex(ValueError,'complete SDK layout'):
            STARTUP.verify_plan(self.manifest)

    def test_heap_api_requires_raw_import_identity(self):
        binding=next(b for b in self.rows['0x00649735']['relocation_bindings'] if b['target_kind']=='import')
        binding['import_name']='HeapDestroy'
        with self.assertRaisesRegex(ValueError,'raw PE import identity'):
            STARTUP.check_import_binding(binding,{0x657160:('KERNEL32.dll','HeapCreate')})

    def test_auxiliary_extent_cannot_drop_the_terminal_int3(self):
        row=next(r for r in self.manifest['diagnostic_boundaries'] if r['address']=='0x006440A5')
        row['size']=47
        with self.assertRaisesRegex(ValueError,'auxiliary extent'):
            STARTUP.verify_plan(self.manifest)

    def test_literal_field_cannot_omit_its_complete_readonly_definition(self):
        self.manifest['literal_controls'].pop()
        with self.assertRaisesRegex(ValueError,'whole readonly source definitions'):
            STARTUP.verify_plan(self.manifest)

    def test_alias_label_cannot_point_inside_the_primary_body(self):
        with self.assertRaisesRegex(ValueError,'complete primary definition'):
            STARTUP.check_alias_definition({'section':1,'offset':0},{'section':1,'offset':1,'storage':2})

    def test_common_declaration_cannot_use_an_arbitrary_zero_span(self):
        with self.assertRaisesRegex(ValueError,'four-byte object'):
            STARTUP.check_common_definition({'section':0,'storage':2,'type':0,'offset':8})

    def test_file_backed_zero_bytes_are_not_loader_zero_fill(self):
        target=bytearray(256)
        struct.pack_into('<I',target,0x3C,64)
        struct.pack_into('<H',target,70,1)
        struct.pack_into('<H',target,84,32)
        struct.pack_into('<I',target,116,0x400000)
        struct.pack_into('<8sIIIIIIHHI',target,120,b'.data',128,0x1000,64,0,0,0,0,0,0xC0000040)
        with self.assertRaisesRegex(ValueError,'PE zero-fill region'):
            STARTUP.zero_fill_region(target,0x401020,4)
        self.assertEqual(STARTUP.zero_fill_region(target,0x401040,4)['raw_size'],64)

    def test_new_archive_origin_cannot_grant_exact_credit(self):
        row=self.rows['0x0064544F']
        function={'size':'17','span_end':row['span_end'],'source_file':'src/Invented.cpp','match_percent':'100.00'}
        with self.assertRaisesRegex(ValueError,'source or exact credit'):
            STARTUP.check_ledger(row,{row['address']:function},{row['address']:{}},True)


if __name__=='__main__':
    unittest.main()
