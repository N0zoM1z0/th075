#!/usr/bin/env python3
"""Reopen whole SDK aligned allocation, prefix recovery and source-owned tails."""
import argparse
import csv
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('aligned_source',ROOT/'scripts/verify-vector-insertion-carrier-origins.py')
SOURCE = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(SOURCE)
module = SOURCE.module
digest = SOURCE.digest
EVIDENCE = 'config/sdk-aligned-buffer-origin-evidence.json'
MANIFEST_SHA256 = 'fba0048154169ef4e4eefa7cd13a321635bf6a6cf450a0df0ff39e016bb53297'
PLAN_DIGESTS = {'sections': '4891faa0c35be86dd26941c6fa0958c1c94f735a6610a3793839f992571f2eb3', 'weak_references': '9e863fc0a8b6ae44e1a84eedeb95d7442bd471be3e9f631c48453b6819785997', 'evidence_id': '172b681489c77a468e526695fcefaa5850e0c419f397a3d117d3d279297e1011', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'functions': 'a3cc06db2a7429f0cf3ba39171e0c722da4c7451fca890767bd2beeecf12dd60', 'member': 'fa57c906b44c9fe263d1a82d41c1a4b0f83d5ce4610ff9db565022a1d2aed930', 'archives': '63d4892df61c0b801568d58a9acd7d01b47e670fd41dc324d5906cfff48e2d37', 'guids': 'dbb808d4d92d0019031a27c52f0aa017176c16c8e27f0d2fae42808f7ba00e9e', 'providers': '6d2a2f77e0e42593978e80d84b08177d80c37df546aa1770ca92882086de65d8', 'runtime_owners': 'f4081b555c6f8fc5b603c92644132450cf84706331301003ac7da85c63a98054', 'retained_unknowns': '1db8550be65c14606830a33bc04b088ed71460a0f318d1615c33243cd4408f5f', 'wrappers': '31610bb3f30970c779fa30017c5a5f4b23427e8aa83d1c42318c8ba1287d111e', 'historical_snapshots': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'public_control': '5df51111a7e48e0bac0e69c8c97dd9e340e4679cf1ecbd17c49a15451c031264', 'guid_control': '67655658adfc6cfa6bec7dd47ad07fa55791999e548724c0090eb6b619251101', 'canonical': '45fbd4dc3458ee39d8f4eb8b58d68901d8352aff716b641beb537ba61f464421', 'retained_sha256': '271e01534639b6c6baeb78e64dce526057d1bfdf8680f73540e297166f7f2837', 'interpretation': '46078fa34ccb7e2c7914afd4e9fecbb83ef69c0c276685cdac148d09d94b2f0b'}
CONFIDENCE = 'whole-original-sdk-aligned-allocation-prefix-recovery-and-source-owned-base-tail'


def rows(name):
    return list(csv.DictReader((ROOT/'config'/name).open()))


def headers(log):
    return module('aligned_actual_headers','verify-sdk-interface-origins.py').included_headers(log)


def verify_plan(m):
    for key,sha in PLAN_DIGESTS.items():
        if SOURCE.BASE.metadata_digest(m[key]) != sha:
            raise ValueError('Aligned buffer reviewed evidence differs: '+key)
    if m['evidence_id'] != 'R224' or len(m['functions']) != 1:
        raise ValueError('Aligned buffer changes bounded origin scope')
    r = m['functions'][0]; f,af,ao = [r[k] for k in ['original_function','accepted_function','accepted_origin']]
    if (r['address'] != '0x0061FEDB' or r['size'] != 27 or r['original_origin']['origin'] != 'unknown'
            or any(af[k] != f[k] for k in ['address','size','span_end','current_name'])
            or af['owner'] != 'library' or af['status'] != 'excluded' or af['match_percent'] != '0.00'
            or any(af[k] for k in ['source_file','signature','calling_convention'])
            or ao != dict(address=r['address'],origin='library',subsystem='D3DX8',disposition='exclude',
                confidence=CONFIDENCE,evidence_id='R224')):
        raise ValueError('Aligned buffer grants unsupported extent/ABI/source/exact ownership')
    if any(q['origin']['origin'] != 'unknown' or q['function']['owner'] for q in m['retained_unknowns']):
        raise ValueError('Aligned buffer resolves short/private lifetime ambiguity by compatible source')


def prefix_policy(raw,address,flow):
    ins = SOURCE.instructions(raw,address,flow)
    if len(raw) != 27 or len(ins) != 8:
        raise ValueError('Aligned buffer omits whole prefix-recovery policy')
    expected = [('mov','eax, dword ptr [ecx + 0xc]'),('test','eax, eax'),
        ('mov','dword ptr [ecx], 0x65de38'),('je',hex(address+22)),
        ('movzx','edx, byte ptr [eax - 1]'),('sub','eax, edx'),
        ('mov','dword ptr [ecx + 0xc], eax'),('jmp','0x61fe0a')]
    if [(i['mnemonic'],i['operands']) for i in ins] != expected:
        raise ValueError('Aligned buffer loses offset-byte recovery, pointer write or genuine base tail')
    return ins


def verify_native(m,target,c,flow):
    for q in m['sections']:
        a = int(q['base'],16); raw = c.pe_bytes_at(target,a,q['size'])
        if digest(raw) != q['body_sha256'] or (q['kind']=='code' and SOURCE.instructions(raw,a,flow) != q['instructions']):
            raise ValueError('Aligned buffer complete native owner differs')
    prefix_policy(c.pe_bytes_at(target,0x61fedb,27),0x61fedb,flow)
    init = next(q for q in m['sections'] if q['symbol']=='?Init@CD3DXBufferA16@@UAEJK@Z')['instructions']
    required = [('add','eax, 0x10'),('call','0x61fe1f'),('and','dl, 0xf'),
        ('mov','cl, 0x10'),('sub','cl, dl'),('add','dword ptr [esi + 0xc], edx'),
        ('mov','byte ptr [esi - 1], cl'),('ret','4')]
    if not all(pair in [(i['mnemonic'],i['operands']) for i in init] for pair in required):
        raise ValueError('Aligned buffer loses complete matching allocation/prefix-write protocol')
    factory = next(q for q in m['sections'] if q['base']=='0x00620188')['instructions']
    if not all(pair in [(i['mnemonic'],i['operands']) for i in factory] for pair in
            [('push','0x10'),('call','dword ptr [eax + 0x18]'),('call','dword ptr [eax + 0x14]')]):
        raise ValueError('Aligned buffer loses complete factory allocation and actual virtual slots')


def verify_graph(m,body,target,c,coff,flow,shared):
    extra = module('aligned_carriers','sdk_x3d_carriers.py')
    pe = module('aligned_permissions','verify-sdk-x3d-origins.py')
    weak = module('aligned_weak','verify-standard-exception-origins.py')
    if [weak.read_weak_reference(body,q['symbol'],c,coff,m['member']['member_offset']) for q in m['weak_references']] != m['weak_references']:
        raise ValueError('Aligned buffer replaces actual original weak AUX/fallback owner')
    catalog = SOURCE.owned_catalog(m['sections'],shared,0,m['weak_references'])
    for q in m['sections']:
        raw,fields,source = extra.section_carrier(body,q['source']['section'],c,coff); a = int(q['base'],16)
        if (SOURCE.BASE.canonical_source(source,body) != q['source'] or fields != q['fields']
                or digest(raw) != q['source_sha256'] or len(raw) != q['size']
                or pe.image_permissions(target,a,len(raw)) != source['flags'] & 0xe0000000):
            raise ValueError('Aligned buffer loses original whole defining source/AUX/fields/permissions')
        linked,calls,data = SOURCE.BASE.BASE.bind_fields(raw,fields,q['bindings'],catalog,0,a,data_image=q['kind']=='data')
        if linked != c.pe_bytes_at(target,a,len(raw)):
            raise ValueError('Aligned buffer whole source/native comparison differs')
        if q['kind']=='code' and flow.flow(linked,a,q['roots'],fields,calls,data,None,None,None) != q['flow']:
            raise ValueError('Aligned buffer complete returns, branches, virtual calls or external tails differ')


def verify_control(m,body,c,coff,flow):
    extra = module('aligned_controls','sdk_x3d_carriers.py')
    inventory = module('aligned_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    control = m['public_control']
    if inventory(body,c,coff) != control['emission']:
        raise ValueError('Aligned buffer omits whole ordinary code/data emission')
    raw,_ = coff.readonly_section(body,control['layout']['section'],c.coff_name)
    if list(struct.unpack('<6I',raw)) != control['layout_values']:
        raise ValueError('Aligned buffer changes complete generic observation layout')
    for q in control['methods']:
        raw,fields,source = extra.section_carrier(body,q['source']['section'],c,coff)
        if (SOURCE.BASE.canonical_source(source,body) != q['source'] or fields != q['fields']
                or digest(raw) != q['source_sha256'] or SOURCE.instructions(raw,0,flow) != q['instructions']):
            raise ValueError('Aligned buffer changes whole implicit/explicit/allocation controls')


def replay(m,evidence_only=False):
    c = module('aligned_target','compare-coff-function.py'); coff = module('aligned_coff','coff_data.py')
    flow = module('aligned_flow','sdk_image_carriers.py'); extra = module('aligned_source_sections','sdk_x3d_carriers.py')
    rt = module('aligned_archive','verify-runtime-origins.py'); target = c.verified_target()
    if digest(target) != m['target_sha256']: raise ValueError('Aligned buffer target identity differs')
    for path,sha in m['retained_sha256'].items():
        if digest((ROOT/path).read_bytes()) != sha: raise ValueError('Aligned buffer changes retained input: '+path)
    fs = {q['address']:q for q in rows('functions.csv')}; origins = {q['address']:q for q in rows('function-origins.csv')}
    selected = m['functions'][0]; state = 'original' if evidence_only else 'accepted'
    for q in m['canonical']:
        key = q['function']['address']; expected = q
        if key==selected['address']: expected = dict(function=selected[state+'_function'],origin=selected[state+'_origin'])
        if dict(function=fs[key],origin=origins[key]) != expected: raise ValueError('Aligned buffer bounded canonical state differs')
    result = subprocess.run([str(ROOT/'scripts/repo-python'),str(ROOT/'scripts/verify-runtime-cycle-origins.py')],
        cwd=ROOT,capture_output=True,text=True)
    if result.returncode: raise ValueError('Aligned buffer original allocation/free/code/data/API/EH proof failed: '+result.stderr[-1400:])
    print(result.stdout.strip(),flush=True)
    archives = {}
    for q in m['archives']:
        raw = (ROOT/q['path']).read_bytes()
        if digest(raw) != q['sha256']: raise ValueError('Aligned buffer original archive differs')
        archives[q['library']] = {a:(n,b) for a,n,b in rt.archive_members(raw)}
    member = m['member']; name,body = archives['d3dx8.lib'][member['member_offset']]
    if name != member['member'] or digest(body) != member['member_sha256']:
        raise ValueError('Aligned buffer original source member differs')
    shared = {}
    # Runtime destinations come from independently defined full source owners.
    runtime = json.loads((ROOT/'config/runtime-cycle-origin-evidence.json').read_text())
    for q in m['runtime_owners']:
        if q['record'] not in runtime['functions']: raise ValueError('Aligned buffer replaces retained original runtime owner')
        name,original = archives['libcmt.lib'][q['record']['member_offset']]
        raw,fields,source = extra.section_carrier(original,q['source']['section'],c,coff)
        if (name != q['record']['member'] or digest(original) != q['record']['member_sha256']
                or SOURCE.BASE.canonical_source(source,original) != q['source'] or len(raw) != q['record']['size']
                or digest(raw) != q['record']['source_sha256']):
            raise ValueError('Aligned buffer runtime binding loses whole own original defining source')
        shared[q['symbol']] = int(q['record']['address'],16)
    for q in m['providers']:
        name,original = archives['libcmt.lib'][q['member_offset']]
        raw,fields,source = extra.section_carrier(original,q['source']['section'],c,coff)
        if (name != q['member'] or digest(original) != q['member_sha256']
                or SOURCE.BASE.canonical_source(source,original) != q['source'] or fields != q['fields']
                or len(raw) != q['size'] or digest(raw) != q['source_sha256']):
            raise ValueError('Aligned buffer original scalar allocation/delete owner differs')
        linked,_,_ = SOURCE.BASE.BASE.bind_fields(raw,fields,q['bindings'],shared,0,int(q['base'],16))
        if linked != c.pe_bytes_at(target,int(q['base'],16),len(raw)):
            raise ValueError('Aligned buffer original scalar provider is not compared unmasked')
        shared[q['symbol']] = int(q['base'],16)
    scratch = ROOT/'build/origin-sdk-aligned-buffer-verification'; scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        for kind in ['guid_control','public_control']:
            control = m[kind]; obj = Path(temp)/(kind+'.obj')
            result = subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/control['probe']),str(obj),*control['profile']],
                cwd=ROOT,capture_output=True,text=True)
            if result.returncode or headers(result.stdout+result.stderr) != control['headers']:
                raise ValueError('Aligned buffer cold original includes/source differ')
            emitted = obj.read_bytes()
            if kind=='public_control': verify_control(m,emitted,c,coff,flow); continue
            inventory = module('aligned_guid_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
            if inventory(emitted,c,coff) != control['emission']: raise ValueError('Aligned buffer omits whole ordinary SDK GUID emission')
            for q in m['guids']:
                source = emitted
                if q['symbol']=='_IID_IUnknown':
                    name,source = archives['Uuid.Lib'][q['member_offset']]
                    if name != q['member'] or digest(source) != q['member_sha256']:
                        raise ValueError('Aligned buffer IUnknown lacks original UUID member')
                raw,definitions = coff.readonly_section(source,q['section'],c.coff_name)
                if (len(raw) != 16 or definitions != q['definitions'] or digest(raw) != q['source_sha256']
                        or raw != c.pe_bytes_at(target,int(q['address'],16),16)):
                    raise ValueError('Aligned buffer source-owned interface GUID differs')
                permissions = module('aligned_guid_permissions','verify-sdk-x3d-origins.py')
                if permissions.image_permissions(target,int(q['address'],16),16) != 0x40000000:
                    raise ValueError('Aligned buffer interface identity is not in complete readonly storage')
                shared[q['symbol']] = int(q['address'],16)
    verify_graph(m,body,target,c,coff,flow,shared); verify_native(m,target,c,flow)
    for q in m['wrappers']:
        if q['record'] not in rows('optimized-deleting-origin-evidence.csv'):
            raise ValueError('Aligned buffer changes independently generated deleting-wrapper evidence')
        if digest(c.pe_bytes_at(target,int(q['record']['address'],16),28)) != q['record']['body_sha256']:
            raise ValueError('Aligned buffer whole generated wrapper body differs')


def main():
    parser = argparse.ArgumentParser(description=__doc__); parser.add_argument('--evidence-only',action='store_true')
    args = parser.parse_args(); m = json.loads((ROOT/EVIDENCE).read_text()); verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes()) != MANIFEST_SHA256: raise ValueError('Aligned buffer immutable manifest differs')
    replay(m,args.evidence_only)
    print('R224: one whole SDK aligned-buffer destructor27; complete allocation/prefix-write, source-owned vtable/interface/base/runtime/tail graph; implicit/empty forwarding alternatives and protected SDK lifetimes remain distinct; no source/ABI/exact credit.')


if __name__ == '__main__': main()
