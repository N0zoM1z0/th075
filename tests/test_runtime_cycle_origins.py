"""Reject convenient extents, open code edges and unearned interior-label credit."""
import copy
import importlib.util
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]


def load(name):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / (name+'.py'))
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


CYCLE = load('verify-runtime-cycle-origins')
RECONCILE = load('origin_reconciliation')


class RuntimeCycleOriginTests(unittest.TestCase):
    def setUp(self):
        self.m = json.loads((ROOT / 'config/runtime-cycle-origin-evidence.json').read_text())
        self.rows = {r['address']: r for r in self.m['functions']}

    def ledger(self, row, label=False):
        f = dict(owner='library', module='VC71CRT', status='excluded', source_file='',
                 match_percent='0.00', proposed_name='' if label else row['coff_symbol'],
                 size=str(row['size']), span_end=f"0x{int(row['address'],16)+row['size']-1:08X}")
        o = dict(origin='library', subsystem='VC71CRT', disposition='exclude', evidence_id='R120',
                 confidence=RECONCILE.LABEL_CONFIDENCE if label else RECONCILE.ROOT_CONFIDENCE)
        return f, o

    def test_cycle_rejects_truncated_lazy_lock(self):
        self.rows['0x00646685']['size'] = 151
        with self.assertRaisesRegex(ValueError, 'whole own source extent'):
            CYCLE.verify_plan(self.m)

    def test_cycle_rejects_missing_terminal_int3(self):
        self.rows['0x006405E0']['size'] = 48
        with self.assertRaisesRegex(ValueError, 'whole own source extent'):
            CYCLE.verify_plan(self.m)

    def test_cycle_rejects_missing_heap_cleanup(self):
        self.rows['0x0064428A']['size'] = 111
        with self.assertRaisesRegex(ValueError, 'whole own source extent'):
            CYCLE.verify_plan(self.m)

    def test_cycle_cannot_leave_a_diagnostic_code_edge(self):
        self.rows['0x00646725']['relocation_bindings'][0]['target_kind'] = 'diagnostic'
        with self.assertRaisesRegex(ValueError, 'unreviewed relocation'):
            CYCLE.verify_plan(self.m)

    def test_cycle_cannot_substitute_a_same_shape_callee(self):
        b = next(b for b in self.rows['0x00644331']['relocation_bindings'] if b['target_kind'] == 'callee')
        b['target_address'] = '0x00647F98'
        with self.assertRaisesRegex(ValueError, 'relocation provenance|code dependency'):
            CYCLE.verify_plan(self.m)

    def test_cycle_cannot_credit_fls_initializer_from_pointer_lookups(self):
        self.m['diagnostic_contexts'][0]['decision'] = 'library'
        with self.assertRaisesRegex(ValueError, 'unearned acceptance'):
            CYCLE.verify_plan(self.m)

    def test_cycle_cannot_invent_a_standalone_cleanup(self):
        self.m['interior_labels'][0]['extent_basis'] = 'function-auxiliary-record'
        with self.assertRaisesRegex(ValueError, 'standalone body'):
            CYCLE.verify_plan(self.m)

    def test_cycle_requires_complete_error_messages(self):
        self.m['literal_controls'].pop()
        with self.assertRaisesRegex(ValueError, 'defining data controls'):
            CYCLE.verify_plan(self.m)

    def test_cycle_requires_actual_callback_initializer(self):
        self.m['onexit_registration']['relocations'][0]['target_address'] = '0x00644331'
        with self.assertRaisesRegex(ValueError, 'initializer provenance'):
            CYCLE.verify_plan(self.m)

    def test_historical_reconciliation_rejects_altered_source_hash(self):
        row = copy.deepcopy(self.rows['0x00644331'])
        f, o = self.ledger(row)
        row['source_sha256'] = '0'*64
        with self.assertRaisesRegex(ValueError, 'source identity'):
            RECONCILE.check_root(row, f, o)

    def test_historical_reconciliation_rejects_old_truncated_ledger(self):
        row = self.rows['0x0064428A']
        f, o = self.ledger(row)
        f.update(size='111', span_end='0x006442F8')
        with self.assertRaisesRegex(ValueError, 'complete origin-only acceptance'):
            RECONCILE.check_root(row, f, o)

    def test_origin_cannot_grant_exact_credit(self):
        row = self.rows['0x00644331']
        f, o = self.ledger(row)
        f['match_percent'] = '100.00'
        with self.assertRaisesRegex(ValueError, 'origin-only acceptance'):
            RECONCILE.check_root(row, f, o)

    def test_label_cannot_be_accepted_while_parent_is_unknown(self):
        label = self.m['interior_labels'][0]
        parent = self.rows[label['parent']]
        f, o = self.ledger(label, True)
        pf, po = self.ledger(parent)
        po['origin'] = 'unknown'
        with self.assertRaisesRegex(ValueError, 'origin-only acceptance'):
            RECONCILE.check_label(label, f, o, {parent['address']: pf}, {parent['address']: po})

    def test_label_cannot_gain_an_independent_function_name(self):
        label = self.m['interior_labels'][0]
        parent = self.rows[label['parent']]
        f, o = self.ledger(label, True)
        pf, po = self.ledger(parent)
        f['proposed_name'] = '__cleanup'
        with self.assertRaisesRegex(ValueError, 'independent/source credit'):
            RECONCILE.check_label(label, f, o, {parent['address']: pf}, {parent['address']: po})

    def test_label_cannot_change_its_complete_parent(self):
        label = copy.deepcopy(self.m['interior_labels'][0])
        label['parent'] = '0x00644331'
        f, o = self.ledger(label, True)
        with self.assertRaisesRegex(ValueError, 'source label differs'):
            RECONCILE.check_label(label, f, o, {}, {})


if __name__ == '__main__':
    unittest.main()
