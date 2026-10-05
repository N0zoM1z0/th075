#!/usr/bin/env python3
"""Replay R197 whole SDK resource-lock policies and original public COM/GUIDs."""
import argparse
import csv
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import tempfile

import capstone

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('resource_lock_graphics', ROOT/'scripts/verify-sdk-graphics-origins.py')
BASE = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(BASE)
EVIDENCE = 'config/sdk-resource-lock-origin-evidence.json'
MANIFEST_SHA256 = '18b992174e5b4d8c86ef8e3a37a85c3041dadaf363e8e476fa15e09f1d594751'
CONFIDENCE = 'whole-original-sdk-resource-lock-policy-complete-guid-com-and-extent-proof'
KEYS = {'0x00614BE7': 1043, '0x00614FFF': 859}
GUIDS = {'_IID_IDirect3DBaseTexture8': '0x0065C3FC',
         '_IID_IDirect3DTexture8': '0x0065C3EC',
         '_IID_IDirect3DVolumeTexture8': '0x0065C3CC'}
SLOTS = {'ProbeSurfaceDesc': 32, 'ProbeSurfaceContainer': 28,
         'ProbeSurfaceDevice': 12, 'ProbeSurfaceLock': 36,
         'ProbeVolumeDesc': 32, 'ProbeVolumeContainer': 28,
         'ProbeVolumeLock': 36, 'ProbeSurfaceTextureContainer': 28,
         'ProbeTextureLevels': 52, 'ProbeVolumeLevels': 52,
         'ProbeSurfaceUnlock': 40, 'ProbeVolumeUnlock': 40,
         'ProbeImageSurface': 108, 'ProbeCopyRects': 112,
         'ProbeResourceRelease': 8}
GUID_CALLS = {'ProbeSurfaceContainer': '_IID_IDirect3DBaseTexture8',
              'ProbeVolumeContainer': '_IID_IDirect3DVolumeTexture8',
              'ProbeSurfaceTextureContainer': '_IID_IDirect3DTexture8'}
LAYOUT = [32,0,4,8,12,16,20,24,28,32,20,24,28,8,0,4,12,0,4,8,
          16,24,0,4,8,12,16,20,0,2,16]


def verify_plan(m):
    code = {r['base']: r for r in m['sections'] if r['kind']=='code'}
    data = [r for r in m['sections'] if r['kind']=='data']
    if (m['evidence_id']!='R197' or len(m['functions'])!=2
            or {r['address']: r['size'] for r in m['functions']}!=KEYS
            or {a: r['size'] for a,r in code.items()}!=KEYS
            or len(m['sections'])!=5 or len(data)!=3
            or {r['symbol']: r['base'] for r in data}!=GUIDS
            or any(r['size']!=16 or r['fields'] or r['bindings'] for r in data)
            or len(m['anchors'])!=3 or m['data_anchors'] or m['imports']
            or m['interiors'] or m['game_parents'] or m['retained_unknown']
            or sum(len(r.get('fields',[])) for r in m['sections'])!=11):
        raise ValueError('Resource-lock bounded source/field/ownership scope differs')
    for r in m['functions']:
        old = r['original_function']; source = code[r['address']]
        if (source['function']!=old or source['origin']!=r['original_origin']
                or r['original_origin']['origin']!='unknown'
                or int(old['size'])!=r['size'] or old['status']!='unclassified'
                or any(old[k] for k in ['owner','source_file','calling_convention','signature'])
                or old['match_percent']!='0.00'
                or r['accepted_function']!=dict(old,proposed_name=source['symbol'],
                    module='D3DX8',status='excluded',owner='library',evidence='R197',notes=r['notes'])
                or r['accepted_origin']!=dict(address=r['address'],origin='library',
                    subsystem='D3DX8',disposition='exclude',confidence=CONFIDENCE,evidence_id='R197')):
            raise ValueError('Resource-lock canonical source/private ABI/mapping/exact scope differs')
    for r in code.values():
        if (r['roots']!=[0] or r['switch'] is not None
                or r['flow']['whole_size']!=r['size'] or r['flow']['code_size']!=r['size']
                or r['flow']['table_size'] or r['flow']['tails']
                or r['flow']['returns']!=[dict(offset=959 if r['size']==1043 else 856,cleanup=24)]
                or len(r['fields'])!=len(r['bindings'])
                or any(any(b.get(k)!=v for k,v in f.items()) for f,b in zip(r['fields'],r['bindings']))):
            raise ValueError('Resource-lock loses a whole reachable CFG, exit or genuine field')
    expected = {'0x00614BE7': ['0x00614B5D','0x0060EB24','0x0065C3FC',
                              '0x0060EB24','0x0060EB24','0x0065C3EC','0x0060EB24'],
                '0x00614FFF': ['0x00614BCC','0x0060EB24','0x0065C3CC','0x0060EB24']}
    if any([b['target_address'] for b in code[a]['bindings']]!=dest for a,dest in expected.items()):
        raise ValueError('Resource-lock substitutes an original source dependency')
    public = m['public_control']
    if (public['layout']!=dict(section=3,size=124,values=LAYOUT)
            or len(public['emission'])!=63 or len(public['headers'])!=84
            or public['profile']!=m['profile']):
        raise ValueError('Resource-lock complete public observer/include/profile differs')


def check_public(body, emission, flow):
    seen = set()
    for r in emission:
        definitions = [d for d in r['definitions'] if d['type']==32]
        if not definitions:
            continue
        if len(definitions)!=1 or definitions[0]['offset']:
            raise ValueError('Resource-lock cold control is not a whole function')
        name = definitions[0]['symbol'].split('@@')[0][1:]
        if name not in SLOTS or name in seen:
            raise ValueError('Resource-lock unexpected or repeated public call control')
        seen.add(name)
        h = struct.unpack_from('<8sIIIIIIHHI',body,20+(r['section']-1)*40)
        ins = flow.instructions(body[h[4]:h[4]+h[3]],0,h[3])
        calls = [i for i in ins if i.group(capstone.CS_GRP_CALL)]
        if len(calls)!=1:
            raise ValueError('Resource-lock cold public control drops an actual call')
        operand = calls[0].operands[0]
        if (operand.type!=capstone.x86.X86_OP_MEM or not operand.mem.base
                or operand.mem.index or operand.mem.disp!=SLOTS[name]):
            raise ValueError('Resource-lock complete original public COM slot differs')
        expected = [GUID_CALLS[name]] if name in GUID_CALLS else []
        if ([f['symbol']['symbol'] for f in r['fields']]!=expected
                or any(f['type']!='DIR32' or f['addend'] for f in r['fields'])):
            raise ValueError('Resource-lock cold public call GUID field differs')
    if seen!=set(SLOTS):
        raise ValueError('Resource-lock missing complete public call control')


def check_guids(body, emission, m, c, coff):
    target = c.verified_target()
    for r in m['sections']:
        if r['kind']!='data':
            continue
        matches = [q for q in emission if any(d['symbol']==r['symbol'] for d in q['definitions'])]
        if len(matches)!=1 or matches[0]['size']!=16 or matches[0]['fields']:
            raise ValueError('Resource-lock public GUID lacks a whole original header definition')
        raw, definitions = coff.readonly_section(body,matches[0]['section'],c.coff_name)
        if (len(raw)!=16 or BASE.digest(raw)!=r['source_sha256']
                or BASE.digest(raw)!=r['body_sha256']
                or raw!=c.pe_bytes_at(target,int(r['base'],16),16)
                or not any(d['symbol']==r['symbol'] and not d['offset'] for d in definitions)):
            raise ValueError('Resource-lock full original SDK/public/target GUID differs')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only',action='store_true')
    args = parser.parse_args()
    m = json.loads((ROOT/EVIDENCE).read_text()); verify_plan(m)
    public = m['public_control']
    for path, sha in [(EVIDENCE,MANIFEST_SHA256),(public['probe'],public['probe_sha256']),*m['retained_sha256'].items()]:
        if BASE.digest((ROOT/path).read_bytes())!=sha:
            raise ValueError('Resource-lock immutable original/source provenance differs: '+path)
    # Replay every unchanged prior graph before using the whole accepted anchors.
    result = subprocess.run([str(ROOT/'scripts/repo-python'),'scripts/verify-sdk-cube-volume-origins.py'],
                            cwd=ROOT,capture_output=True,text=True,check=True)
    print('retained '+result.stdout.strip().splitlines()[-1])
    BASE.replay(m,args.evidence_only)
    c = BASE.module('resource_lock_coff','compare-coff-function.py')
    coff = BASE.module('resource_lock_data','coff_data.py')
    api = BASE.module('resource_lock_api','verify-sdk-interface-origins.py')
    flow = BASE.module('resource_lock_flow','sdk_graphics_carriers.py')
    inventory = BASE.module('resource_lock_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    target = c.verified_target()
    for anchor in m['anchors']:
        if anchor.get('kind')!='R008':
            continue
        address = int(anchor['address'],16); q = anchor['comparison']
        raw = c.pe_bytes_at(target,address,q['size'])
        if q['fields'] or flow.flow(raw,address,[0],[],{}, {})!=anchor['whole_flow']:
            raise ValueError('Resource-lock complete previous Unlock source/CFG differs')
    scratch = ROOT/'build/origin-sdk-resource-lock-verification'; scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj = Path(temp)/'Public.obj'
        result = subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/public['probe']),str(obj),*public['profile']],
                                cwd=ROOT,capture_output=True,text=True)
        if (result.returncode or api.included_headers(result.stdout+result.stderr)!=public['headers']
                or inventory(obj.read_bytes(),c,coff)!=public['emission']):
            raise ValueError('Resource-lock cold whole emission or original included headers differ')
        body = obj.read_bytes(); check_public(body,public['emission'],flow)
        check_guids(body,public['emission'],m,c,coff)
        raw,_ = coff.readonly_section(body,public['layout']['section'],c.coff_name)
        if len(raw)!=124 or list(struct.unpack('<31I',raw))!=LAYOUT:
            raise ValueError('Resource-lock full public readonly observer differs')
    print('R197 origins OK:two whole library Lock policies1902;684 reachable instructions/17 public indirect calls;'
          'three original/public complete GUIDs48,all11 genuine fields,three complete accepted anchors271;'
          '15 cold whole public COM controls,47 complete GUID definitions752,layout124,84 original headers;'
          'unchanged full R196/R195 replay;no private SDK owner/layout/source/ABI/mapping/exact credit.')
    return 0


if __name__=='__main__':
    raise SystemExit(main())
