#!/usr/bin/env python3
"""Cold-replay complete deque leaves, genuine whole parents/EH and ordinary alternatives."""
from __future__ import annotations
import argparse
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
import importlib.util

ROOT = Path(__file__).resolve().parents[1]
MANIFEST_SHA256 = '6360156350feac7c88f7756e073b43dd1d5ab84abf6a3ac5f2bf2548119cb2b6'
CONFIDENCE = 'complete-vc7-deque-leaf-whole-parent-eh-protocol-and-ordinary-alternative-provenance'
KEYS = {'0x0042E3B0':44, '0x00423550':38, '0x00422480':27, '0x004229B0':15, '0x00412300':5}
CONTEXTS = ['0x0042E0E0','0x00421F80','0x004225C0','0x00422D70','0x0042DCF0','0x004228C0','0x004229F0',
            '0x00421F40','0x00421F20','0x00422460','0x00421220','0x00640F15']


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec); spec.loader.exec_module(result)
    return result


ENDPOINT = module('leaf_endpoint', 'verify-deque-endpoint-dispatch-origins.py')
PAIRED = ENDPOINT.PAIRED


def manifest():
    return json.loads((ROOT / 'config/deque-leaf-origin-evidence.json').read_text())


def verify_plan(m):
    prior = PAIRED.manifest(); PAIRED.verify_plan(prior)
    if (m['evidence_id'] != 'R160' or m['target_sha256'] != prior['target_sha256']
            or m['retained_manifest'] != 'config/paired-deque-producer-origin-evidence.json' or m['retained_sha256'] != PAIRED.MANIFEST_SHA256
            or m['endpoint_manifest'] != 'config/deque-endpoint-dispatch-origin-evidence.json' or m['endpoint_sha256'] != ENDPOINT.MANIFEST_SHA256
            or m['probe'] != 'probes/VC7DequeLeafAlternatives.cpp' or m['profile'] != prior['profile']
            or m['headers'] != dict(prior['headers'], **{prior['probe']:prior['probe_sha256']})
            or len(m['functions']) != 5 or {r['address']:r['size'] for r in m['functions']} != KEYS
            or len(m['controls']) != 17 or sum(r['size'] for r in m['controls']) != 2568
            or sum(len(r['bindings']) for r in m['controls']) != 88
            or len(m['emission']) != 191 or sum(r['size'] for r in m['emission']) != 12034
            or m['layout_values'] != [8,20,60,20,20,4,8,8,8,20,60,20,20,4,8,8,1,1]
            or m['layout'] not in m['emission'] or m['layout']['size'] != 72
            or [r['address'] for r in m['contexts']] != CONTEXTS
            or len(m['protected']) != 1 or m['protected'][0]['address'] != '0x004229D0'):
        raise ValueError('deque leaf loses whole owners, actual source context/EH, alternatives or complete emission/layout')
    source = {r['symbol']:r for r in prior['code'] + prior['state_data']}
    routes = {'0x0042E3B0':[], '0x00423550':['0x00421F40','0x00421F20'],
              '0x00422480':['0x00422460'], '0x004229B0':['0x004229F0'], '0x00412300':[]}
    for row in m['functions']:
        old = source.get(row['symbol']); f, accepted = row['original_function'], row['accepted_function']
        mutable = {'proposed_name','module','status','owner','evidence','notes'}
        if (row['decision'] != 'library' or old is None or (old['address'],old['size']) != (row['address'],row['size'])
                or [r['target_address'] for r in old['bindings']] != routes[row['address']]
                or f['status'] != 'unclassified' or row['original_origin']['origin'] != 'unknown'
                or row['original_origin']['disposition'] != 'review'
                or {k:v for k,v in f.items() if k not in mutable} != {k:v for k,v in accepted.items() if k not in mutable}
                or accepted['owner'] != 'library' or accepted['module'] != 'VC7STL' or accepted['status'] != 'excluded'
                or accepted['source_file'] or accepted['calling_convention'] or accepted['signature'] or accepted['match_percent'] != '0.00'
                or row['accepted_origin'] != dict(address=row['address'],origin='library',subsystem='VC7STL',disposition='exclude',confidence=CONFIDENCE,evidence_id='R160')):
            raise ValueError('deque leaf changes genuine operation/wrapper routes or grants false extent/source/ABI/exact credit')
    addresses = list(KEYS) + CONTEXTS[:7] + ['0x00655690','0x006688D8','0x0042E3B0','0x004229B0','0x00412300']
    if ([r['address'] for r in m['controls']] != addresses
            or [r['role'] for r in m['controls']] != ['sdk-owner']*5 + ['whole-source-context']*9 + ['byte-equal-ordinary-alternative']*3
            or [r['source_definition']['symbol'] for r in m['controls'][-3:]] !=
               ['?max_size@OrdinaryCapacityObservation@@QBEIXZ','?OrdinaryDestroyInner@@YAXPAUInnerRecordObservation@@@Z','?OrdinaryPlacementNoop@@YAXPAX0@Z']):
        raise ValueError('deque leaf omits its actual whole source protocol or distinct ordinary alternatives')
    for control in m['controls']:
        old = source.get(control['retained_symbol']); definition = control['source_definition']; section = control['section']
        if (old is None or any(control[k] != old[k] for k in ('address','size','source_sha256','body_sha256'))
                or section not in m['emission'] or definition not in section['definitions']
                or control['size'] != section['size'] or control['source_sha256'] != section['source_sha256']
                or [(r['offset'],r['type'],r['addend'],r['target_address']) for r in control['bindings']] !=
                   [(r['offset'],r['type'],r['addend'],r['target_address']) for r in old['bindings']]
                or len(section['fields']) != len(old['section']['fields'])):
            raise ValueError('deque leaf truncates a complete independent source parent/owner or masks a field')
        if control['role'] != 'byte-equal-ordinary-alternative' and not old['source_definition']['symbol'].startswith('$') and definition['symbol'] != old['source_definition']['symbol']:
            raise ValueError('deque leaf substitutes an unrelated SDK or compiler definition')
        for field, previous, binding in zip(section['fields'],old['section']['fields'],control['bindings']):
            a,b = field['symbol'],previous['symbol']
            if (any(field[k] != previous[k] for k in ('offset','type','addend'))
                    or any(a[k] != b[k] for k in ('offset','type','storage'))
                    or (a['symbol'] != b['symbol'] and not (a['symbol'].startswith('$') and b['symbol'].startswith('$')))
                    or binding['symbol'] != a['symbol']):
                raise ValueError('deque leaf replaces an actual source field or its real local carrier')
    expected_evidence = ['R074','R078','R074','R158','R071','R157','R037','R078','R082','R083','R153','R142']
    for row, evidence in zip(m['contexts'],expected_evidence):
        if row['function']['address'] != row['address'] or row['origin']['evidence_id'] != evidence or row['origin']['origin'] != ('compiler' if evidence == 'R037' else 'authored' if evidence == 'R153' else 'library'):
            raise ValueError('deque leaf conflates SDK parent, generated wrapper and independent authored/runtime policy')
    for address in CONTEXTS[:7] + CONTEXTS[7:10]:
        original = next(r for r in prior['code'] if r['address'] == address)
        context = next(r for r in m['contexts'] if r['address'] == address)
        if not any(PAIRED.preserved_snapshot(s,context['function'],context['origin']) for s in original['canonical_rows']):
            raise ValueError('deque leaf loses independently retained whole source operation context')
    protected = m['protected'][0]; record = ENDPOINT.COPY.manifest()['functions'][0]
    if protected != dict(address=record['address'],function=record['accepted_function'],origin=record['accepted_origin']) or protected['origin']['origin'] != 'unknown':
        raise ValueError('deque leaf changes protected implicit/ordinary copy ambiguity')


def accepted_snapshot(snapshot, function, origin):
    m = manifest()
    if PAIRED.digest((ROOT / 'config/deque-leaf-origin-evidence.json').read_bytes()) != MANIFEST_SHA256:
        raise ValueError('deque leaf immutable follow-up evidence differs')
    verify_plan(m)
    row = next((r for r in m['functions'] if r['address'] == function['address']),None)
    return bool(row and snapshot == dict(function=row['original_function'],origin=row['original_origin'])
                and function == row['accepted_function'] and origin == row['accepted_origin'])


def check_ledger(row, function, origin, evidence_only=False):
    if evidence_only and function == row['original_function'] and origin == row['original_origin']:
        return
    if function != row['accepted_function'] or origin != row['accepted_origin']:
        raise ValueError('deque leaf exact bounded canonical acceptance differs')


def main():
    parser = argparse.ArgumentParser(description=__doc__); parser.add_argument('--evidence-only',action='store_true')
    args = parser.parse_args(); m = manifest(); verify_plan(m)
    for path,expected in [('config/deque-leaf-origin-evidence.json',MANIFEST_SHA256),
                          (m['retained_manifest'],m['retained_sha256']),(m['endpoint_manifest'],m['endpoint_sha256']),(m['probe'],m['probe_sha256'])]:
        if PAIRED.digest((ROOT / path).read_bytes()) != expected:
            raise ValueError('deque leaf immutable source/evidence differs: ' + path)
    c = module('leaf_target','compare-coff-function.py'); coff = module('leaf_coff','coff_data.py')
    extent = module('leaf_extent','verify-vendor-record-origins.py'); cfg = module('leaf_cfg','verify-authored-origins.py')
    target = c.verified_target()
    if PAIRED.digest(target) != m['target_sha256']:
        raise ValueError('deque leaf target differs')
    functions = {r['address']:r for r in PAIRED.BUFFER.PRIOR.PRIOR.rows('functions.csv')}
    origins = {r['address']:r for r in PAIRED.BUFFER.PRIOR.PRIOR.rows('function-origins.csv')}
    for row in m['functions']:
        check_ledger(row,functions[row['address']],origins[row['address']],args.evidence_only)
    for row in m['contexts'] + m['protected']:
        if functions[row['address']] != row['function'] or origins[row['address']] != row['origin']:
            raise ValueError('deque leaf changes independent source/compiler/authored/runtime context or protected ambiguity')
    result = subprocess.run([str(ROOT / 'scripts/repo-python'),str(ROOT / 'scripts/verify-deque-endpoint-dispatch-origins.py')],cwd=ROOT,capture_output=True,text=True)
    if result.returncode:
        raise ValueError('deque leaf whole retained cold evidence failed: ' + result.stderr[-1500:])
    print('retained endpoints: ' + result.stdout.splitlines()[-1],flush=True)
    prior = PAIRED.manifest(); catalog = {k:v for k,v in PAIRED.source_catalog(prior,[]).items() if not k.startswith('$')}
    scratch = ROOT / 'build/origin-deque-leaf-verification'; scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as dirname:
        path = Path(dirname) / 'VC7DequeLeafAlternatives.obj'
        result = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'),str(ROOT / m['probe']),str(path),*m['profile']],cwd=ROOT,capture_output=True,text=True)
        if result.returncode or ENDPOINT.COPY.ELEMENT.included_headers(result.stdout + result.stderr) != m['headers']:
            raise ValueError('deque leaf actual cold source/header ownership differs')
        data = path.read_bytes(); inventory = PAIRED.BUFFER.inventory(data,c,coff)
        if inventory != m['emission']:
            raise ValueError('deque leaf entire ordinary emission differs or omits an owner')
        for control in m['controls']:
            for definition in control['section']['definitions']:
                if definition['storage'] in (2,3) and not definition['symbol'].startswith('.'):
                    address = int(control['address'],16) + definition['offset']
                    if definition['symbol'] in catalog and catalog[definition['symbol']] != address:
                        raise ValueError('deque leaf source definition overrides independent complete ownership')
                    catalog[definition['symbol']] = address
        for control in m['controls']:
            section = control['section']; head = struct.unpack_from('<8sIIIIIIHHI',data,20 + (section['section']-1)*40)
            raw = data[head[4]:head[4]+head[3]]
            fields = [dict(offset=r['offset'],type=r['type'],symbol=r['symbol']['symbol'],addend=r['addend']) for r in section['fields']]
            actual = c.pe_bytes_at(target,int(control['address'],16),control['size'])
            if (PAIRED.digest(raw) != control['source_sha256'] or PAIRED.digest(actual) != control['body_sha256']
                    or PAIRED.BUFFER.PRIOR.link_complete(raw,fields,int(control['address'],16),control['bindings'],catalog) != actual):
                raise ValueError('deque leaf entire defining source carrier fails genuine unmasked field comparison')
            if control['address'] not in ('0x00655690','0x006688D8','0x004229F0'):
                if extent.complete_aux_section_size(data,control['source_definition']['symbol'],c.coff_name) != control['size']:
                    raise ValueError('deque leaf source owner loses its complete positive own AUX')
                cfg.verify_body(actual,int(control['address'],16))
            else:
                old = next(r for r in prior['code']+prior['state_data'] if r['symbol']==control['retained_symbol'])
                if old['size'] != section['size'] or section['flags'] != old['section']['flags']:
                    raise ValueError('deque leaf compiler/data fallback is not its complete independently retained defining section')
        raw,_ = coff.readonly_section(data,m['layout']['section'],c.coff_name)
        if list(struct.unpack('<18I',raw)) != m['layout_values']:
            raise ValueError('deque leaf whole actual SDK/observation layout differs')
    print('R160 origins OK: five complete SDK leaves / 129 bytes; sixteen whole code controls / 2532 bytes plus entire construction EH data / 36 bytes, 88 unmasked genuine fields, all 191 cold ordinary sections / 12034 bytes and whole 72-byte observation layout; ordinary capacity / 44, destruction / 15 and two-argument no-op / 5 are fully byte-equal, with ownership inferred only through independently complete real SDK parent/placement-construction/EH protocols; unchanged R037 compiler wrapper and R153 authored destruction remain separate; original declarations/source and live outcomes unknown; protected copy ambiguity and unrelated canonical/exact inputs preserved; no source/private ABI/mapping/exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError,KeyError,IndexError,StopIteration,ValueError,struct.error,json.JSONDecodeError) as error:
        print('error: ' + str(error),file=sys.stderr)
        raise SystemExit(1)
