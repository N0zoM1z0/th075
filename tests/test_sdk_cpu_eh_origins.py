import copy
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import unittest

ROOT=Path(__file__).resolve().parents[1]
def module(name,filename):
    spec=importlib.util.spec_from_file_location(name,ROOT/'scripts'/filename)
    result=importlib.util.module_from_spec(spec);spec.loader.exec_module(result);return result
verify=module('test_cpu_eh','verify-sdk-cpu-eh-origins.py')
sdk=module('test_cpu_cfg','verify-sdk-origins.py')


class SDKCpuEHTests(unittest.TestCase):
    def setUp(self):
        self.m=json.loads((ROOT/verify.EVIDENCE).read_text())

    def reject(self,mutate):
        m=copy.deepcopy(self.m);mutate(m)
        with self.assertRaises(ValueError):verify.verify_plan(m)

    def test_immutable_whole_scope(self):
        verify.verify_plan(self.m)
        self.assertEqual(hashlib.sha256((ROOT/verify.EVIDENCE).read_bytes()).hexdigest(),verify.MANIFEST_SHA256)

    def test_incomplete_inventory_prefix_cannot_be_accepted(self):
        self.reject(lambda m:m['functions'][0].update(size=58))

    def test_complete_source_cannot_be_truncated(self):
        self.reject(lambda m:m['sections'][0]['source'].update(size=58))

    def test_catch_entry_cannot_be_hidden(self):
        self.reject(lambda m:m['sections'][0]['flow'].update(roots=[0,76]))

    def test_resume_cannot_be_removed(self):
        self.reject(lambda m:m['sections'][0]['source']['definitions'].pop(2))

    def test_continuation_is_not_an_independent_library_function(self):
        self.reject(lambda m:m['functions'][2].update(role='whole-library-parent'))

    def test_no_duplicate_function_byte_credit(self):
        self.reject(lambda m:m['functions'][1].update(size=165))

    def test_absolute_zero_cannot_be_a_fake_undefined_symbol(self):
        self.reject(lambda m:m['absolute']['definition'].update(section=0))

    def test_real_fs_field_cannot_be_dropped(self):
        self.reject(lambda m:m['sections'][0]['source']['fields'].pop())

    def test_catch_resume_must_bind_actual_source_label(self):
        self.reject(lambda m:m['catalog'].update({'$L48087':'0x00620B87'}))

    def test_full_funcinfo_is_not_a_selected_pointer(self):
        self.reject(lambda m:m['sections'][4]['source'].update(size=4))

    def test_catch_type_cannot_be_ignored(self):
        self.reject(lambda m:m['sections'][4]['topology'].update(handler_type=[16,4]))

    def test_eh_prolog_retains_prior_compiler_ownership(self):
        self.reject(lambda m:m['anchors'][1]['origin'].update(origin='library'))

    def test_imports_must_be_independently_typed(self):
        self.reject(lambda m:m['imports'][1].update(name='GetVersionExA'))

    def test_no_private_abi_or_source_credit(self):
        self.reject(lambda m:m['functions'][0]['accepted_function'].update(signature='int fake()'))

    def test_cold_generated_catch_metadata_cannot_be_dropped(self):
        self.reject(lambda m:m['emission'][3]['fields'].pop())

    def test_full_code_requires_all_separate_entries(self):
        code=bytes.fromhex('eb01 c3 c3')
        with self.assertRaises(ValueError):verify.flow(code,0,[0],sdk)
        self.assertEqual(verify.flow(code,0,[0,2],sdk)['returns'],[2,3])

    def test_entry_inside_an_instruction_is_rejected(self):
        with self.assertRaises(ValueError):verify.flow(bytes.fromhex('b800000000c3'),0,[0,1],sdk)

    def test_eh_state_and_handlers_are_not_masks(self):
        words=[0xffffffff,0,0xffffffff,0,0,0,0,0x620b7b,0,0,1,1,0x66a928,0x19930520,2,0x66a918,1,0x66a938,0,0]
        verify.check_eh(struct.pack('<20I',*words))
        words[7]=0x620b87
        with self.assertRaises(ValueError):verify.check_eh(struct.pack('<20I',*words))

    def test_silent_field_addend_override_is_rejected(self):
        field=dict(offset=1,type='DIR32',symbol=dict(symbol='p'),addend=1)
        with self.assertRaises(ValueError):verify.link(bytes(5),[field],[dict(field=field,target_address='0x00001000')],0,{'p':0x1000})


if __name__=='__main__':unittest.main()
