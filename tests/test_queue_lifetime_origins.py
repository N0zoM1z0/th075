"""Reject loss of lifetime alternatives, callback context and pending bindings."""
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('queue_lifetime', ROOT/'scripts/verify-queue-lifetime-origins.py')
QUEUE = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(QUEUE)


class QueueLifetimeOriginTests(unittest.TestCase):
    def setUp(self):
        self.manifest = json.loads((ROOT/'config/queue-lifetime-origin-evidence.json').read_text())
        self.rows = {r['address']:r for r in self.manifest['functions']}

    def test_pulse_cannot_choose_only_the_ordinary_source(self):
        self.rows['0x00423B20']['source_alternatives'].pop()
        with self.assertRaisesRegex(ValueError,'ordinary/compiler-generated'):
            QUEUE.verify_decisions(self.manifest)

    def test_generated_alternative_requires_its_initializer_registration(self):
        self.manifest['initializer_registration']['relocations'][1]['symbol'] = '?ExplicitPulseProbe@@YAXXZ'
        with self.assertRaisesRegex(ValueError,'initializer registration'):
            QUEUE.verify_decisions(self.manifest)

    def test_short_wrapper_cannot_be_a_guessed_destructor(self):
        self.rows['0x004239C0']['source_alternatives'][0]['symbol'] = '??1ExplicitDestroyProbe@@QAE@XZ'
        with self.assertRaisesRegex(ValueError,'explicit constructor control'):
            QUEUE.verify_decisions(self.manifest)

    def test_wrapper_must_bind_the_actual_release(self):
        self.rows['0x004239C0']['source_alternatives'][0]['relocations'][1]['target_address'] = '0x004239F0'
        with self.assertRaisesRegex(ValueError,'actual typed fields'):
            QUEUE.verify_decisions(self.manifest)

    def test_callback_requires_the_actual_registration(self):
        main = next(r for r in self.manifest['contexts'] if r['address'] == '0x00602A60')
        witness = next(w for w in main['instruction_witnesses'] if w['site'] == '0x00602B47')
        witness['operands'] = 'dword ptr [ebp - 0x28], 0x603660'
        with self.assertRaisesRegex(ValueError,'registration/readiness'):
            QUEUE.verify_decisions(self.manifest)

    def test_interval_api_cannot_be_sleep(self):
        self.rows['0x004239F0']['indirect_calls'][0]['symbol'] = 'Sleep'
        with self.assertRaisesRegex(ValueError,'raw API identities'):
            QUEUE.verify_decisions(self.manifest)

    def test_matching_startup_cannot_gain_library_credit(self):
        self.rows['0x0064232C']['decision'] = 'library'
        with self.assertRaisesRegex(ValueError,'retained ambiguity'):
            QUEUE.verify_decisions(self.manifest)

    def test_startup_cannot_promote_unresolved_bindings(self):
        binding = next(b for b in self.rows['0x0064232C']['archive_source']['relocations']
                       if b['binding_status'] == 'unresolved')
        binding['binding_status'] = 'accepted-runtime'
        with self.assertRaisesRegex(ValueError,'unresolved code/data fields'):
            QUEUE.verify_decisions(self.manifest)

    def test_source_probes_cannot_grant_exact_credit(self):
        row = self.rows['0x004239F0']
        function = {'size':'155','span_end':row['span_end'],'source_file':'src/Invented.cpp','match_percent':'100.00'}
        with self.assertRaisesRegex(ValueError,'source or exact credit'):
            QUEUE.check_ledger(row,{row['address']:function},{row['address']:{}},True)


if __name__ == '__main__':
    unittest.main()
