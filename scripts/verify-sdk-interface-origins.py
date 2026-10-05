#!/usr/bin/env python3
"""Cold-replay real SDK GUIDs and whole interface owners without masked fields."""
from __future__ import annotations
import argparse
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('interface_shared',ROOT/'scripts/verify-sdk-file-image-origins.py')
BASE=importlib.util.module_from_spec(spec);spec.loader.exec_module(BASE)
module=BASE.module;digest=BASE.digest
EVIDENCE='config/sdk-interface-origin-evidence.json'
MANIFEST_SHA256='4fb78070d97506d8a9604dd860090cce66bf4e6a67946cfc24e241954df886f4'
KEYS={'0x00609F11':71,'0x0060A1FA':71,'0x00620093':71,'0x0061FE1F':38}
PROFILE=['/Od','/Ob0','/Gy','/GR-','/GX','/Zi','/GS','/showIncludes']
CONFIDENCE='whole-pinned-sdk-interface-with-independent-guids-and-complete-owner-context'
OPAQUE={'?Face@CD3DXRenderToEnvMap@@UAGJW4_D3DCUBEMAP_FACES@@@Z','?End@CD3DXRenderToEnvMap@@UAGJXZ'}
GUIDS={'_IID_IUnknown':'0x00660E58','_IID_ID3DXBuffer':'0x0065DDFC','_IID_ID3DXRenderToSurface':'0x0065DDCC','_IID_ID3DXRenderToEnvMap':'0x0065DDBC'}

def verify_plan(m):
    if (m['evidence_id']!='R186' or {r['address']:r['size'] for r in m['functions']}!=KEYS or len(m['functions'])!=4
            or len(m['code'])!=35 or sum(r['size'] for r in m['code'])!=2955
            or len(m['tables'])!=3 or [t['size'] for t in m['tables']]!=[36,52,28]
            or sum(len(r['fields']) for r in m['code'] if 'bindings' in r)!=25 or len(m['aliases'])!=1
            or {r['symbol'] for r in m['code'] if 'bindings' not in r}!=OPAQUE
            or m['profile']!=PROFILE or m['probe']!='probes/VC7D3DXInterfaceGuids.cpp' or len(m['negatives'])!=2
            or {r['symbol']:r['address'] for r in m['guids']}!=GUIDS
            or any(r['definitions']!=[dict(symbol=r['symbol'],offset=0)] for r in m['guids'])):
        raise ValueError('SDK interface loses bounded whole source/GUID/context scope')
    mutable={'proposed_name','module','status','owner','evidence','notes'}
    by_address={r['address']:r for r in m['code']}
    for r in m['functions']:
        old,new=r['original_function'],r['accepted_function'];a=r['address']
        if (r['original_origin']['origin']!='unknown' or new['owner']!='library' or new['status']!='excluded'
                or new['module']!='D3DX8' or int(old['size'])!=r['size'] or int(old['span_end'],16)!=int(a,16)+r['size']-1
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['source_file'] or new['signature'] or new['calling_convention'] or new['match_percent']!='0.00'
                or r['accepted_origin']!=dict(address=a,origin='library',subsystem='D3DX8',disposition='exclude',confidence=CONFIDENCE,evidence_id='R186')
                or by_address[a]['body_sha256']!=r['body_sha256'] or 'bindings' not in by_address[a]):
            raise ValueError('SDK interface changes an extent or grants source/ABI/exact credit')
    for r in m['code']:
        if r['symbol'] in OPAQUE and ('bindings' in r or r.get('comparison')!='unresolved-callee-context-only'):
            raise ValueError('SDK interface invents unresolved EndScene/filter callee linkage')
    for n in m['negatives']:
        if n['size']!=71 or n['source_symbol']!='?QueryInterface@CD3DXBuffer@@UAGJABU_GUID@@PAPAX@Z' or n['differences']!=[dict(offset=35,source=252,target=(204 if n['address']=='0x00609F11' else 188))]:
            raise ValueError('SDK interface hides complete wrong-interface pointer negatives')

def included_headers(output):
    found={}
    for line in output.splitlines():
        if 'Note: including file:' not in line:continue
        name=line.split('Note: including file:',1)[1].strip().replace('\\','/')
        if name[:3].lower()!='z:/':raise ValueError('SDK interface include loses host mapping')
        path=Path(name[2:]);relative=str(path.relative_to(ROOT))
        if not relative.lower().startswith(('.tools/msvc710/vc7/include/','.tools/msvc710/vc7/platformsdk/include/')):
            raise ValueError('SDK interface include is outside pinned tool roots')
        if not path.exists():
            path=ROOT
            for part in Path(relative).parts:
                matches=[entry for entry in path.iterdir() if entry.name.casefold()==part.casefold()]
                if len(matches)!=1:raise ValueError('SDK include lacks one actual host case mapping')
                path=matches[0]
        found[str(path.relative_to(ROOT))]=digest(path.read_bytes())
    return found

def vendor_table(body, symbol, c, coff):
    _,defs=coff.parse_symbols(body,c.coff_name);matches=[d for d in defs if d['symbol']==symbol and d['section']>0]
    if len(matches)!=1:raise ValueError('SDK vtable lacks unique actual source definition')
    d=matches[0];h=struct.unpack_from('<8sIIIIIIHHI',body,20+(d['section']-1)*40)
    if (d['offset'] or d['type'] or d['storage']!=2 or not h[9]&0x40 or not h[9]&0x1000
            or h[9]&0x80000000 or not h[9]&0x40000000 or h[3]%4 or h[7]!=h[3]//4):
        raise ValueError('SDK vtable is not a complete readonly pointer COMDAT')
    syoff,count=struct.unpack_from('<II',body,8);strings=body[syoff+count*18:];names={};i=0
    while i<count:
        nm,_,_,_,_,aux=struct.unpack_from('<8sIhHBB',body,syoff+i*18);names[i]=c.coff_name(nm,strings);i+=1+aux
    raw=body[h[4]:h[4]+h[3]];fields=[]
    for i in range(h[7]):
        off,index,typ=struct.unpack_from('<IIH',body,h[5]+i*10)
        if off!=i*4 or typ!=6 or struct.unpack_from('<I',raw,off)[0]:raise ValueError('SDK vtable real fields are incomplete or have addends')
        fields.append(dict(offset=off,type_id=typ,symbol=names[index]))
    return raw,d,fields

def link_code(raw,fields,bindings,address,catalog):
    if len(fields)!=len(bindings):raise ValueError('SDK interface real code field coverage differs')
    linked=bytearray(raw);calls={};data={};seen=set()
    for f,b in zip(fields,bindings):
        off=f['offset'];sn=f['symbol'];dest=int(b['target_address'],16)
        if (off in seen or off<1 or off+4>len(raw) or f['addend'] or f['local_symbol_offset'] is not None
                or {k:b[k] for k in f}!=f or catalog.get(sn)!=dest or sn in OPAQUE
                or struct.unpack_from('<I',raw,off)[0]):raise ValueError('SDK interface masks/overrides a real code field')
        seen.add(off)
        if f['type']=='REL32' and f['type_id']==20 and raw[off-1] in (0xe8,0xe9):
            value=(dest-address-off-4)&0xffffffff;calls[address+off]=dest
        elif f['type']=='DIR32' and f['type_id']==6:
            value=dest;data[address+off]=dest
        else:raise ValueError('SDK interface unsupported field kind')
        struct.pack_into('<I',linked,off,value)
    return linked,calls,data

def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args()
    m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    for path,h in [(EVIDENCE,MANIFEST_SHA256),(m['probe'],m['probe_sha256']),*m['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes())!=h:raise ValueError('SDK interface immutable prior/source evidence differs: '+path)
    c=module('interface_target','compare-coff-function.py');rt=module('interface_archive','verify-runtime-origins.py');coff=module('interface_coff','coff_data.py');sdk=module('interface_cfg','verify-sdk-origins.py')
    geometry=module('interface_geometry','verify-compiler-origins.py');weak=module('interface_weak','verify-standard-exception-origins.py');inventory=module('interface_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    target=c.verified_target();functions={r['address']:r for r in BASE.rows('config/functions.csv')};origins={r['address']:r for r in BASE.rows('config/function-origins.csv')};primary={r['address']:r for r in m['functions']};catalog={k:int(v,16) for k,v in m['catalog'].items()}
    prior=json.loads((ROOT/'config/sdk-file-image-origin-evidence.json').read_text())
    expected_external=[r for r in prior['retained'] if r['requested_symbol'] in ('??2@YAPAXI@Z','??3@YAXPAX@Z')]
    if m['external_records']!=expected_external or m['external_symbols']!={r['requested_symbol']:r['address'] for r in expected_external}:raise ValueError('SDK interface loses original full allocation source provenance')
    if digest(target)!=m['target_sha256']:raise ValueError('SDK interface target identity differs')
    archives={}
    for r in m['archives']:
        raw=(ROOT/r['path']).read_bytes()
        if digest(raw)!=r['sha256']:raise ValueError('SDK interface readonly archive differs')
        archives[r['library']]={off:(name,b) for off,name,b in rt.archive_members(raw)}
    def member(r):
        name,body=archives['d3dx8.lib'][r['member_offset']]
        if name!=r['member'] or digest(body)!=r['member_sha256']:raise ValueError('SDK interface complete source member differs')
        return body
    scratch=ROOT/'build/origin-sdk-interface-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj=Path(temp)/'Guids.obj';result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/m['probe']),str(obj),*m['profile']],cwd=ROOT,capture_output=True,text=True)
        if result.returncode or included_headers(result.stdout+result.stderr)!=m['headers']:raise ValueError('SDK interface cold GUID source/includes differ')
        emitted=obj.read_bytes()
        if inventory(emitted,c,coff)!=m['emission']:raise ValueError('SDK interface drops complete cold ordinary GUID emission')
        for r in m['guids']:
            if r['symbol']=='_IID_IUnknown':
                name,source=archives['Uuid.Lib'][r['member_offset']]
                if name!=r['member'] or digest(source)!=r['member_sha256']:raise ValueError('SDK original complete IUnknown member differs')
            else:source=emitted
            raw,definitions=coff.readonly_section(source,r['section'],c.coff_name);a=int(r['address'],16)
            if (len(raw)!=16 or definitions!=r['definitions'] or digest(raw)!=r['source_sha256'] or c.pe_bytes_at(target,a,16)!=raw
                    or not any(base<=a and a+16<=base+n and flags&0x40000000 and not flags&0x80000000 for base,n,flags in geometry.sections(target))):
                raise ValueError('SDK actual GUID is not a complete source/readonly target identity')
        code={r['symbol']:r for r in m['code']};tables={t['symbol']:t for t in m['tables']}
        for r in m['code']:
            body=member(r);size=sdk.complete_comdat_size(body,r['symbol'],c.coff_name)
            if size!=r['size']:raise ValueError('SDK interface truncates a full own function COMDAT')
            obj.write_bytes(body);raw,fields=c.object_function(obj,r['symbol'],size);a=r['address'];actual=c.pe_bytes_at(target,int(a,16),size)
            if digest(raw)!=r['source_sha256'] or fields!=r['fields'] or digest(actual)!=r['body_sha256']:raise ValueError('SDK interface whole source/native body or field metadata differs')
            if a in primary:
                state='original' if args.evidence_only else 'accepted';r0=primary[a]
                if functions[a]!=r0[state+'_function'] or origins[a]!=r0[state+'_origin']:raise ValueError('SDK interface bounded canonical acceptance differs')
                if any(int(a,16)<int(q,16)<int(a,16)+size for q in functions):raise ValueError('SDK interface hides an interior inventory entry')
            elif functions.get(a)!=r['function'] or origins.get(a)!=r['origin']:raise ValueError('SDK interface changes another original source/native anchor')
            if 'bindings' not in r:
                # Entire source/native bodies remain context, with actual unsolved fields.
                # They receive no body-positive, callee linkage or origin credit.
                if list(module('interface_opaque_cfg','verify-authored-origins.py').verify_body(actual,int(a,16)))!=r['cfg']:
                    raise ValueError('SDK opaque complete original CFG differs')
                continue
            for f in fields:
                sn=f['symbol']
                if f['type']=='REL32' and sn not in code and sn not in m['external_symbols']:raise ValueError('SDK interface code field lacks complete independently read source body')
                if f['type']=='DIR32' and sn not in GUIDS and sn not in tables:raise ValueError('SDK interface data field lacks complete GUID/table provenance')
            linked,calls,data=link_code(raw,fields,r['bindings'],int(a,16),catalog)
            if linked!=actual or sdk.verify_control_flow(linked,int(a,16),calls,data)!=r['indirect_call_count'] or BASE.flow_counts(actual,int(a,16))!=r['cfg']:
                raise ValueError('SDK interface whole unmasked body/branches/exits differ')
            if r.get('old_sdk_record') and r['old_sdk_record'] not in BASE.rows('config/sdk-origin-evidence.csv'):raise ValueError('SDK interface prior full typed library source record differs')
        for alias in m['aliases']:
            r=alias['reference'];owner=next(t for t in m['tables'] if t['member_offset']==r['member_offset']);actual=weak.read_weak_reference(member(owner),r['symbol'],c,coff,r['member_offset'])
            if actual!=r or catalog[r['symbol']]!=catalog[r['fallback_symbol']] or r['fallback_symbol'] not in code:raise ValueError('SDK interface weak pointer lacks actual same-member complete fallback')
        for t in m['tables']:
            source,d,fields=vendor_table(member(t),t['symbol'],c,coff);a=int(t['address'],16);actual=c.pe_bytes_at(target,a,t['size'])
            if d!=t['definition'] or len(source)!=t['size'] or digest(source)!=t['source_sha256'] or digest(actual)!=t['body_sha256'] or not any(base<=a and a+t['size']<=base+n and flags&0x40000000 and not flags&0x80000000 for base,n,flags in geometry.sections(target)):raise ValueError('SDK interface drops or changes a complete owning pointer carrier')
            if len(fields)!=len(t['fields']):raise ValueError('SDK interface drops an owning-table slot')
            for f,b in zip(fields,t['fields']):
                if {k:b[k] for k in f}!=f or struct.unpack_from('<I',actual,f['offset'])[0]!=int(b['target_address'],16) or catalog[f['symbol']]!=int(b['target_address'],16):raise ValueError('SDK interface original complete slot differs')
                if f['symbol'] not in code and not any(x['reference']['symbol']==f['symbol'] for x in m['aliases']):raise ValueError('SDK interface table callback lacks a complete read source definition')
        buffer=next(r for r in m['code'] if r['symbol']=='?QueryInterface@CD3DXBuffer@@UAGJABU_GUID@@PAPAX@Z');obj.write_bytes(member(buffer));raw,fields=c.object_function(obj,buffer['symbol'],sdk.complete_comdat_size(member(buffer),buffer['symbol'],c.coff_name));linked,_,_=link_code(raw,fields,buffer['bindings'],0x620093,catalog)
        for n in m['negatives']:
            actual=c.pe_bytes_at(target,int(n['address'],16),71);differences=[dict(offset=i,source=a,target=b) for i,(a,b) in enumerate(zip(linked,actual)) if a!=b]
            source_guid=c.pe_bytes_at(target,int(GUIDS['_IID_ID3DXBuffer'],16),16);native_guid=c.pe_bytes_at(target,int(n['native_guid_address'],16),16)
            gd=[dict(offset=i,source=a,target=b) for i,(a,b) in enumerate(zip(source_guid,native_guid)) if a!=b]
            if differences!=n['differences'] or gd!=n['guid_differences'] or not gd:raise ValueError('SDK interface hides full wrong-IID code/GUID negatives')
    # Prior complete source graphs remain independent and are reopened once, serially.
    for filename in ('verify-sdk-debug-parent-origins.py',):
        result=subprocess.run([str(ROOT/'scripts/repo-python'),str(ROOT/'scripts'/filename)],cwd=ROOT,capture_output=True,text=True)
        if result.returncode:raise ValueError('SDK interface prior complete origin replay failed: '+result.stderr[-1500:])
    print('R186 origins OK: three whole interface queries and buffer initializer /251 bytes;three complete owning pointer carriers /116 bytes and29 slots;33 whole unmasked source bodies /2693 bytes with25 real fields and73 unchanged indirect calls;two complete opaque EnvMap controls /262 bytes stay unresolved;actual cold SDK GUIDs and whole UUID IUnknown,real weak fallback,full wrong-interface negatives;prior evidence preserved;no source/ABI/mapping/exact credit.')
    return 0

if __name__=='__main__':
    try:raise SystemExit(main())
    except (OSError,KeyError,IndexError,ValueError,struct.error,json.JSONDecodeError) as error:
        print('error: '+str(error),file=sys.stderr);raise SystemExit(1)
