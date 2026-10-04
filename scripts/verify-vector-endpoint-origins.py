#!/usr/bin/env python3
"""Cold-replay whole vector endpoints, constructors, real deque operations and lifetime controls."""
from __future__ import annotations
import argparse
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]
MANIFEST_SHA256 = 'afe1d3136b9d1ce15d370b11234b8bfa4b6be877032c76ba4623df3ecb8a11fe'
CONFIDENCE = 'complete-vc7-vector-endpoint-constructor-deque-operation-and-independent-lifetime-context'
CANDIDATES = {'0x00409760':31,'0x00409E60':31,'0x0040E1F0':31,'0x0040E680':31,
              '0x0040A120':28,'0x0040E9E0':28,'0x0040A190':27,'0x0040A830':15,'0x0040F9F0':15}
KEYS = dict(CANDIDATES, **{'0x00409DF0':57})
CONTEXTS = ['0x00409780','0x0040E210','0x00409470','0x0040DF20','0x00409DF0','0x00409D60','0x0040F860',
            '0x0040A590','0x0040F120','0x0040A5E0','0x0040A9F0','0x0040FA00',
            '0x00409ED0','0x00409EA0','0x0040E6F0','0x0040E6C0']
ROUTES = {
 '0x00409760':['0x0040A120'], '0x00409E60':['0x0040A120'],
 '0x0040E1F0':['0x0040E9E0'], '0x0040E680':['0x0040E9E0'],
 '0x0040A120':['0x0040A590'], '0x0040E9E0':['0x0040F120'],
 '0x0040A190':['0x0040A5E0'], '0x0040A830':['0x0040A9F0'], '0x0040F9F0':['0x0040FA00'],
 '0x00409780':['0x00409E60','0x00409760','0x00409ED0','0x00409760','0x00409EA0'],
 '0x0040E210':['0x0040E680','0x0040E1F0','0x0040E6F0','0x0040E1F0','0x0040E6C0'],
 '0x00409470':['0x00409780'], '0x0040DF20':['0x0040E210'], '0x00409DF0':['0x0040A190'],
 '0x00409D60':['0x0040A830'], '0x0040F860':['0x0040F9F0'],
 '0x0040A590':[], '0x0040F120':[], '0x0040A5E0':[],
 '0x0040A9F0':['0x004092F0','0x00640F15'], '0x0040FA00':['0x0040D8E0','0x00640F15'],
 '0x00409ED0':['0x0040A5B0','0x0040A840','0x00409F40'], '0x00409EA0':['0x0040A210'],
 '0x0040E6F0':['0x0040F140','0x0040F310','0x0040E760'], '0x0040E6C0':['0x0040EDB0']}


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec); spec.loader.exec_module(result)
    return result


LEAF = module('vector_endpoint_leaf','verify-deque-leaf-origins.py')
PAIRED = LEAF.PAIRED


def manifest():
    return json.loads((ROOT / 'config/vector-endpoint-origin-evidence.json').read_text())


def verify_plan(m):
    if (m['evidence_id'] != 'R161' or m['target_sha256'] != PAIRED.manifest()['target_sha256']
            or m['probe'] != 'probes/VC7VectorEndpointAlternatives.cpp' or m['profile'] != PAIRED.manifest()['profile']
            or len(m['headers']) != 28 or len(m['functions']) != 10
            or {r['address']:r['size'] for r in m['functions']} != KEYS
            or len(m['controls']) != 31 or sum(r['size'] for r in m['controls']) != 1169
            or sum(len(r['bindings']) for r in m['controls']) != 41
            or len(m['emission']) != 176 or sum(r['size'] for r in m['emission']) != 9404
            or len(m['retained']) != 14 or len(m['retained_sha256']) != 11
            or m['layout_values'] != [4,4,16,16,4,4,4,4,1,1,4,4,16,1,8,1,1]
            or m['layout'] not in m['emission'] or m['layout']['size'] != 68):
        raise ValueError('vector endpoint loses bounded complete ownership, source/parent fields or ordinary emission/layout')
    records = {r['address']:r for r in m['functions']}
    mutable = {'proposed_name','module','status','owner','evidence','notes'}
    for row in m['functions']:
        old, accepted = row['original_function'],row['accepted_function']
        if ({k:v for k,v in old.items() if k not in mutable} != {k:v for k,v in accepted.items() if k not in mutable}
                or old['address'] != row['address'] or int(old['size']) != row['size']
                or accepted['source_file'] or accepted['calling_convention'] or accepted['signature'] or accepted['match_percent'] != '0.00'):
            raise ValueError('vector endpoint grants false extent/source/private ABI/exact credit')
        if row['address'] == '0x0040F9F0':
            if (row['decision'] != 'unknown' or row['accepted_origin'] != row['original_origin'] or row['original_origin']['origin'] != 'unknown'
                    or any(accepted[k] != old[k] for k in ('proposed_name','module','status','owner'))):
                raise ValueError('vector endpoint resolves an unresolved surrounding lifetime policy from a byte-equal leaf')
        elif row['address'] == '0x00409DF0':
            if (row['decision'] != 'retained-library-operation-refinement' or row['accepted_origin'] != row['original_origin']
                    or row['accepted_origin']['origin'] != 'library' or row['accepted_origin']['evidence_id'] != 'R078'
                    or any(accepted[k] != old[k] for k in ('module','status','owner'))):
                raise ValueError('deque operation refinement changes original accepted origin credit')
        elif (row['decision'] != 'library' or row['original_origin']['origin'] != 'unknown'
                or accepted['owner'] != 'library' or accepted['status'] != 'excluded' or accepted['module'] != 'VC7STL'
                or row['accepted_origin'] != dict(address=row['address'],origin='library',subsystem='VC7STL',disposition='exclude',confidence=CONFIDENCE,evidence_id='R161')):
            raise ValueError('vector endpoint bounded library decision differs')
    if [r['address'] for r in m['controls'][:25]] != list(CANDIDATES)+CONTEXTS:
        raise ValueError('vector endpoint omits actual whole independent owners/parents')
    if [r['role'] for r in m['controls']] != ['candidate-sdk-owner']*9 + ['whole-independent-source-context']*16 + ['byte-equal-ordinary-alternative']*6:
        raise ValueError('vector endpoint replaces a whole source/ordinary control')
    ordinary = m['controls'][25:]
    if ([r['address'] for r in ordinary] != ['0x00409760','0x00409E60','0x0040A120','0x0040A590','0x0040A830','0x0040F9F0']
            or [r['size'] for r in ordinary] != [31,31,28,24,15,15]
            or any('Ordinary' not in r['source_definition']['symbol'] for r in ordinary)):
        raise ValueError('vector endpoint loses full distinct ordinary endpoint/constructor/destruction alternatives')
    for control in m['controls']:
        section,definition = control['section'],control['source_definition']
        if (section not in m['emission'] or definition not in section['definitions']
                or definition['offset'] or definition['type'] != 32 or definition['storage'] != 2
                or section['size'] != control['size'] or section['source_sha256'] != control['source_sha256']
                or len(section['fields']) != len(control['bindings'])
                or [r['target_address'] for r in control['bindings']] != ROUTES[control['address']]):
            raise ValueError('vector endpoint truncates a full defining owner or loses genuine operation/callee routes')
        if control['role'] == 'candidate-sdk-owner' and definition['symbol'] != records[control['address']]['symbol']:
            raise ValueError('vector endpoint substitutes an unrelated real SDK candidate source')
        for field,binding in zip(section['fields'],control['bindings']):
            if (binding != dict(offset=field['offset'],type=field['type'],symbol=field['symbol']['symbol'],addend=field['addend'],target_address=binding['target_address'])
                    or field['type'] != 'REL32' or field['addend'] or field['symbol']['type'] != 32
                    or field['symbol']['storage'] != 2 or field['symbol']['offset']):
                raise ValueError('vector endpoint masks or substitutes an actual complete source field')
    for retained in m['retained']:
        if ((retained['file'] not in m['retained_sha256'] and not (retained['file'] == 'config/authored-origin-evidence.csv' and retained['address'] == '0x004092F0' and retained['record']['evidence_id'] == 'R017')) or retained['record']['address'] != retained['address']):
            raise ValueError('vector endpoint drops independently retained ownership/operation evidence')
        row = next((r for r in m['controls'] if r['address']==retained['address']),None)
        if row and (row['body_sha256'] != retained['record']['body_sha256'] or row['source_sha256'] != retained['record'].get('source_sha256',row['source_sha256'])):
            raise ValueError('vector endpoint loses original entire parent/owner hashes')
    old_parent = next(r for r in m['retained'] if r['address']=='0x00409DF0')
    if (old_parent['file'] != 'config/vendor-deque-access-origins.csv'
            or not old_parent['record']['coff_symbol'].startswith('??Hiterator@?$deque@')
            or json.loads(old_parent['record']['relocation_bindings'])[0]['target_address'] != '0x0040A190'
            or not m['controls'][13]['source_definition']['symbol'].startswith('??Giterator@?$deque@')
            or not m['controls'][6]['source_definition']['symbol'].startswith('??Ziterator@?$deque@')
            or not m['controls'][18]['source_definition']['symbol'].startswith('??Yiterator@?$deque@')):
        raise ValueError('deque operation refinement erases original shape evidence or swaps real addition/subtraction source')
    negative = m['negative_operation']
    if (negative['address'] != '0x00409DF0' or negative['size'] != 57 or negative['section']['size'] != 57
            or negative['section'] not in m['emission'] or negative['source_definition'] not in negative['section']['definitions']
            or not negative['source_definition']['symbol'].startswith('??Hiterator@?$deque@')
            or negative['bindings'] != [dict(offset=31,type='REL32',symbol=m['controls'][18]['source_definition']['symbol'],addend=0,target_address='0x0040A5E0')]):
        raise ValueError('deque addition alternative bypasses its independently complete genuine addition callee')
    snapshots = {r['address']:r for r in m['snapshots']}
    for address,origin,evidence,size in [('0x004092F0','authored','R017',87),('0x0040D8E0','unknown','R108',19),
                                         ('0x0040A9F0','compiler','R037',44),('0x0040FA00','compiler','R037',44),
                                         ('0x004229D0','unknown','ghidra-12.1.3-initial-inventory',28)]:
        row = snapshots.get(address)
        if row is None or row['size'] != size or row['origin']['origin'] != origin or row['origin']['evidence_id'] != evidence:
            raise ValueError('vector endpoint conflates authored/compiler/unknown destruction or protected copy roles')


def check_ledger(row, function, origin, evidence_only=False):
    if evidence_only and function == row['original_function'] and origin == row['original_origin']:
        return
    if function != row['accepted_function'] or origin != row['accepted_origin']:
        raise ValueError('vector endpoint exact bounded canonical acceptance differs')


def accepted_snapshot(snapshot, function, origin):
    m = manifest()
    if PAIRED.digest((ROOT / 'config/vector-endpoint-origin-evidence.json').read_bytes()) != MANIFEST_SHA256:
        raise ValueError('vector endpoint immutable bounded evidence differs')
    verify_plan(m)
    row = next((r for r in m['functions'] if r['address']==function['address']),None)
    return bool(row and snapshot == dict(function=row['original_function'],origin=row['original_origin'])
                and function == row['accepted_function'] and origin == row['accepted_origin'])


def link(data, control, catalog, comparison):
    section = control['section']; head = struct.unpack_from('<8sIIIIIIHHI',data,20+(section['section']-1)*40)
    raw = data[head[4]:head[4]+head[3]]
    fields = [dict(offset=r['offset'],type=r['type'],symbol=r['symbol']['symbol'],addend=r['addend']) for r in section['fields']]
    return raw,PAIRED.BUFFER.PRIOR.link_complete(raw,fields,int(control['address'],16),control['bindings'],catalog)


def main():
    parser = argparse.ArgumentParser(description=__doc__); parser.add_argument('--evidence-only',action='store_true')
    args = parser.parse_args(); m = manifest(); verify_plan(m)
    for path,expected in [('config/vector-endpoint-origin-evidence.json',MANIFEST_SHA256),(m['probe'],m['probe_sha256']),*m['retained_sha256'].items()]:
        if PAIRED.digest((ROOT/path).read_bytes()) != expected:
            raise ValueError('vector endpoint immutable source/prior evidence differs: ' + path)
    c = module('vector_endpoint_target','compare-coff-function.py'); coff = module('vector_endpoint_coff','coff_data.py')
    extent = module('vector_endpoint_extent','verify-vendor-record-origins.py'); cfg = module('vector_endpoint_cfg','verify-authored-origins.py')
    target = c.verified_target()
    if PAIRED.digest(target) != m['target_sha256']:
        raise ValueError('vector endpoint target differs')
    functions = {r['address']:r for r in PAIRED.BUFFER.PRIOR.PRIOR.rows('functions.csv')}
    origins = {r['address']:r for r in PAIRED.BUFFER.PRIOR.PRIOR.rows('function-origins.csv')}
    records = {r['address']:r for r in m['functions']}
    for row in m['functions']:
        check_ledger(row,functions[row['address']],origins[row['address']],args.evidence_only)
    for row in m['snapshots']:
        a = row['address']
        if a in records:
            check_ledger(records[a],functions[a],origins[a],args.evidence_only)
        elif functions[a] != row['function'] or origins[a] != row['origin']:
            raise ValueError('vector endpoint changes original accepted or protected unknown boundary')
        if PAIRED.digest(c.pe_bytes_at(target,int(a,16),row['size'])) != row['body_sha256']:
            raise ValueError('vector endpoint entire independent target boundary differs')
    for row in m['retained']:
        if row['record'] not in PAIRED.BUFFER.PRIOR.PRIOR.rows(row['file'].removeprefix('config/')):
            raise ValueError('vector endpoint independent original source/parent/policy record differs')
    scratch = ROOT/'build/origin-vector-endpoint-verification'; scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as dirname:
        path = Path(dirname)/'VC7VectorEndpointAlternatives.obj'
        result = subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/m['probe']),str(path),*m['profile']],cwd=ROOT,capture_output=True,text=True)
        if result.returncode or PAIRED.BUFFER.PRIOR.PRIOR.included_headers(result.stdout+result.stderr) != m['headers']:
            raise ValueError('vector endpoint actual cold source/header ownership differs')
        data = path.read_bytes(); inventory = PAIRED.BUFFER.inventory(data,c,coff)
        if inventory != m['emission']:
            raise ValueError('vector endpoint entire ordinary emission differs or omits a carrier')
        catalog = {}
        def add(symbol,address):
            if symbol in catalog and catalog[symbol] != address:
                raise ValueError('vector endpoint symbol overrides independent whole ownership')
            catalog[symbol] = address
        for control in m['controls']:
            for d in control['section']['definitions']:
                if d['storage'] in (2,3) and not d['symbol'].startswith('.'):
                    add(d['symbol'],int(control['address'],16)+d['offset'])
        snapshots = {r['address']:r for r in m['snapshots']}
        retained = {r['address']:r for r in m['retained']}
        for control in m['controls']:
            for field in control['bindings']:
                if field['symbol'] in catalog:
                    if catalog[field['symbol']] != int(field['target_address'],16):
                        raise ValueError('vector endpoint field replaces its full defining source owner')
                    continue
                boundary = snapshots.get(field['target_address'])
                if boundary is None:
                    raise ValueError('vector endpoint external field lacks its whole independent canonical boundary')
                if control['address'] in ('0x00409ED0','0x00409EA0','0x0040E6F0','0x0040E6C0'):
                    original = json.loads(retained[control['address']]['record']['relocation_bindings'])
                    if not any(b['offset']==field['offset'] and b['type']==field['type'] and b['target_address']==field['target_address']
                               and b['symbol'].split('@',1)[0]==field['symbol'].split('@',1)[0] for b in original):
                        raise ValueError('vector endpoint external SDK operation loses original full same-family binding')
                elif control['address'] not in ('0x0040A9F0','0x0040FA00'):
                    raise ValueError('vector endpoint external field is outside independent source/policy boundaries')
                add(field['symbol'],int(field['target_address'],16))
        for control in m['controls']:
            raw,linked = link(data,control,catalog,c)
            actual = c.pe_bytes_at(target,int(control['address'],16),control['size'])
            if (PAIRED.digest(raw) != control['source_sha256'] or PAIRED.digest(actual) != control['body_sha256'] or linked != actual):
                raise ValueError('vector endpoint whole source carrier fails genuine unmasked byte/field comparison')
            if control['address'] in ('0x0040A9F0','0x0040FA00'):
                section = control['section']; d = control['source_definition']
                peers = [p for p in section['definitions'] if p['storage']==2 and p['type']==32]
                if d['offset'] or peers != [d] or not section['flags'] & 0x20 or not section['flags'] & 0x1000:
                    raise ValueError('vector endpoint compiler wrapper is not its complete unique defining COMDAT')
            elif extent.complete_aux_section_size(data,control['source_definition']['symbol'],c.coff_name) != control['size']:
                raise ValueError('vector endpoint source owner loses its full positive own AUX extent')
            cfg.verify_body(actual,int(control['address'],16))
        negative = m['negative_operation']; raw,linked = link(data,negative,catalog,c)
        actual = c.pe_bytes_at(target,int(negative['address'],16),negative['size'])
        if (extent.complete_aux_section_size(data,negative['source_definition']['symbol'],c.coff_name) != 57
                or linked == actual or any(linked[i]!=actual[i] for i in range(57) if i not in range(31,35))):
            raise ValueError('vector endpoint real whole addition control does not differ solely in its genuine operation call field')
        raw,_ = coff.readonly_section(data,m['layout']['section'],c.coff_name)
        if list(struct.unpack('<17I',raw)) != m['layout_values']:
            raise ValueError('vector endpoint entire actual SDK/ordinary observation layout differs')
    print('R161 origins OK: eight complete library candidates / 222 bytes; one whole SDK/ordinary destruction / 15 remains unknown with the unchanged protected R108 policy; original R078 library origin retained while genuine whole subtraction / 57 matches and addition / 57 differs through independently complete addition / 31; 31 full code controls / 1169 bytes and 41 unmasked actual fields, all 176 cold ordinary sections / 9404 bytes, 28 actual SDK headers and full 68-byte observation layout; six ordinary endpoint/constructor/destruction controls / 144 bytes are fully byte-equal; independent original source/runtime/compiler/authored and protected unknown boundaries preserved; original game declarations/source and live outcomes unknown; no source/private ABI/mapping/exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError,KeyError,IndexError,StopIteration,ValueError,struct.error,json.JSONDecodeError) as error:
        print('error: '+str(error),file=sys.stderr)
        raise SystemExit(1)
