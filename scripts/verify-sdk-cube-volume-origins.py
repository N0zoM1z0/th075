#!/usr/bin/env python3
"""Replay original cube/volume requirements, creation and EnvMap factory policy."""
import argparse
import csv
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import tempfile
import capstone

ROOT=Path(__file__).resolve().parents[1]
SPEC=importlib.util.spec_from_file_location('cube_volume_graphics',ROOT/'scripts/verify-sdk-graphics-origins.py')
BASE=importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(BASE)
EVIDENCE='config/sdk-cube-volume-origin-evidence.json'
MANIFEST_SHA256='1f6e40980b678af117d09e65999e3506b437e7dec4f81c47630a2eefe3d39ad1'
KEYS={'0x00605B10':40,'0x00605B38':41,'0x00605BC7':95,'0x00605C26':109,'0x00605107':126,'0x00609F9E':134}
CONFIDENCE='whole-original-sdk-cube-volume-env-gateway-policy-and-public-abi'


def verify_plan(m):
    code={r['base']:r for r in m['sections'] if r['kind']=='code'}
    if (m['evidence_id']!='R196' or len(m['functions'])!=6
            or {r['address']:r['size'] for r in m['functions']}!=KEYS
            or m['retained_unknown']!=['0x0060B728'] or m['interiors'] or m['game_parents']
            or [(k,len([r for r in m['sections'] if r['kind']==k]),sum(r['size'] for r in m['sections'] if r['kind']==k)) for k in ['code','data','bss']]
                !=[('code',12,1905),('data',5,1624),('bss',2,8)]
            or len(m['anchors'])!=3 or len(m['data_anchors'])!=1
            or m['data_anchors'][0]['record']['size']!=52 or len(m['imports'])!=3
            or sum(len(r.get('fields',[])) for r in m['sections'])!=39):
        raise ValueError('Cube/volume bounded source graph differs')
    for r in m['functions']:
        old=r['original_function']; control=code[r['address']]
        if (control['function']!=old or control['origin']!=r['original_origin'] or r['original_origin']['origin']!='unknown'
                or old['status']!='unclassified' or old['owner'] or old['source_file'] or old['calling_convention']
                or old['signature'] or old['match_percent']!='0.00' or int(old['size'])!=r['size']
                or r['accepted_function']!=dict(old,proposed_name=control['symbol'],module='D3DX8',status='excluded',
                    owner='library',evidence='R196',notes=r['notes'])
                or r['accepted_origin']!=dict(address=r['address'],origin='library',subsystem='D3DX8',disposition='exclude',
                    confidence=CONFIDENCE,evidence_id='R196')):
            raise ValueError('Cube/volume source/private ABI/mapping/exact scope differs')
    if code['0x0060B728']['size']!=104 or code['0x0060B728']['origin']['origin']!='unknown':
        raise ValueError('Cube/volume grants constructor ownership from a factory')
    for r in m['sections']:
        if r['kind']=='bss':
            continue
        if len(r['fields'])!=len(r['bindings']) or any(any(b.get(k)!=v for k,v in f.items()) for f,b in zip(r['fields'],r['bindings'])):
            raise ValueError('Cube/volume loses a genuine original field')
        if r['kind']=='code' and (r['roots']!=[0] or r['switch'] or r['flow']['whole_size']!=r['size'] or r['flow']['code_size']!=r['size']):
            raise ValueError('Cube/volume truncated code/CFG or fabricated switch')
    for a,dests in {'0x00605B10':['0x006057BE'],'0x00605B38':['0x006057BE'],
                    '0x00605BC7':['0x00605B10'],'0x00605C26':['0x00605B38'],
                    '0x00605107':['0x0064159D','0x0060B728','0x00609F9E','0x006049F4'],
                    '0x00609F9E':['0x00605AE8']}.items():
        if [b['target_address'] for b in code[a]['bindings']]!=dests:
            raise ValueError('Cube/volume substitutes a real source dependency')
    opaque=m['opaque']
    if ([(r['address'],r['size']) for r in opaque]!=[('0x0060BDED',35),('0x0060BE10',227)]
            or opaque[0]['function'] is not None or opaque[0]['origin'] is not None
            or opaque[1]['origin']['origin']!='unknown'
            or any(r['comparison']!='unresolved-callee-context-only' or 'bindings' in r for r in opaque)):
        raise ValueError('Cube/volume overwrites earlier unresolved callback provenance')
    public=m['public_control']
    if len(public['emission'])!=9 or len(public['headers'])!=85 or public['layout']!=dict(section=3,size=28,values=[5,4,16,0,4,8,12]):
        raise ValueError('Cube/volume public SDK observer layout differs')


def check_public(body, emission, flow):
    apis={'ProbeCheckCube':'_D3DXCheckCubeTextureRequirements@24',
          'ProbeCheckVolume':'_D3DXCheckVolumeTextureRequirements@32',
          'ProbeCreateCube':'_D3DXCreateCubeTexture@28','ProbeCreateVolume':'_D3DXCreateVolumeTexture@36',
          'ProbeCreateEnv':'_D3DXCreateRenderToEnvMap@24'}
    slots={'ProbeDeviceCube':88,'ProbeDeviceVolume':84,'ProbeEnvDesc':16}; seen=set()
    for r in emission:
        defs=[d for d in r['definitions'] if d['type']==32]
        if not defs:
            continue
        if len(defs)!=1 or defs[0]['offset']:
            raise ValueError('Cube/volume cold control is not a whole function')
        name=defs[0]['symbol'].split('@@')[0][1:];seen.add(name)
        h=struct.unpack_from('<8sIIIIIIHHI',body,20+(r['section']-1)*40)
        ins=flow.instructions(body[h[4]:h[4]+h[3]],0,h[3]);calls=[i for i in ins if i.group(capstone.CS_GRP_CALL)]
        if len(calls)!=1:
            raise ValueError('Cube/volume cold control loses an actual call')
        if name in apis:
            if [f['symbol']['symbol'] for f in r['fields']]!=[apis[name]] or r['fields'][0]['type']!='REL32':
                raise ValueError('Cube/volume public WINAPI declaration differs')
        elif name in slots:
            op=calls[0].operands[0]
            if op.type!=capstone.x86.X86_OP_MEM or not op.mem.base or op.mem.index or op.mem.disp!=slots[name]:
                raise ValueError('Cube/volume complete public COM slot differs')
        else:
            raise ValueError('Cube/volume unreviewed cold control')
    if seen!=set(apis)|set(slots):
        raise ValueError('Cube/volume missing whole natural public control')


def retained_digest_matches(path,expected):
    if BASE.retained_digest_matches(path,expected):return True
    return (path=='scripts/verify-sdk-graphics-origins.py' and expected=='338306579c942974df5099a5974ff7c8d64458e1c89c844e3efaed57830c8809'
            and BASE.digest((ROOT/path).read_bytes())=='a89133e29ff64053bfd903b6f0cb06c6a5fedce577b9db587376422c7d4c4eba')


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args()
    m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    public=m['public_control']
    for path,sha in [(EVIDENCE,MANIFEST_SHA256),(public['probe'],public['probe_sha256']),*m['retained_sha256'].items()]:
        if not retained_digest_matches(path,sha):
            raise ValueError('Cube/volume immutable source/provenance differs: '+path)
    # The shared replay is pinned by this manifest. Its actual R195 graph and
    # public controls are independently replayed, with all old decisions intact.
    result=subprocess.run([str(ROOT/'scripts/repo-python'),'scripts/verify-sdk-graphics-origins.py'],cwd=ROOT,capture_output=True,text=True,check=True)
    print('retained '+result.stdout.strip().splitlines()[-1])
    BASE.replay(m,args.evidence_only)
    old=json.loads((ROOT/'config/sdk-interface-origin-evidence.json').read_text())
    if m['opaque']!=[r for r in old['code'] if 'bindings' not in r]:
        raise ValueError('Cube/volume changes prior opaque callback records')
    functions={r['address']:r for r in csv.DictReader((ROOT/'config/functions.csv').open())}
    origins={r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
    for r in m['opaque']:
        if not BASE.module('cube_volume_end_snapshot','verify-sdk-interface-origins.py').reviewed_destructor_anchor_matches(r,functions.get(r['address']),origins.get(r['address'])):
            raise ValueError('Cube/volume promotes an opaque callback')
    c=BASE.module('cube_volume_coff','compare-coff-function.py');coff=BASE.module('cube_volume_data','coff_data.py')
    api=BASE.module('cube_volume_api','verify-sdk-interface-origins.py');flow=BASE.module('cube_volume_flow','sdk_graphics_carriers.py')
    inventory=BASE.module('cube_volume_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    scratch=ROOT/'build/origin-sdk-cube-volume-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj=Path(temp)/'Public.obj'
        result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/public['probe']),str(obj),*public['profile']],cwd=ROOT,capture_output=True,text=True)
        if result.returncode or api.included_headers(result.stdout+result.stderr)!=public['headers'] or inventory(obj.read_bytes(),c,coff)!=public['emission']:
            raise ValueError('Cube/volume cold complete ordinary sections/SDK headers differ')
        check_public(obj.read_bytes(),public['emission'],flow)
        raw,_=coff.readonly_section(obj.read_bytes(),public['layout']['section'],c.coff_name)
        if len(raw)!=28 or list(struct.unpack('<7I',raw))!=public['layout']['values']:
            raise ValueError('Cube/volume whole public readonly observer differs')
    print('R196 origins OK:six complete library gateways/initializer545;12 whole original code1905,five initialized source sections1624,two BSS8,all39 real fields;EnvMap table52/13 original entries;three complete original anchors;full unchanged R195 replay and eleven retained natural public controls;new eight whole public controls305/readonly28,85 headers,actual Cube88/Volume84/GetDesc16;constructor104 and original opaque Face35(noninventory)/End227 provenance preserved;no source/private ABI/mapping/exact credit.')
    return 0


if __name__=='__main__':
    raise SystemExit(main())
