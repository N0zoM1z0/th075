#!/usr/bin/env python3
"""Cold-replay complete list construction, including its source-owned shared catch."""
from __future__ import annotations
import argparse
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('list_construction_sdk',ROOT/'scripts/verify-sdk-dependency-origins.py')
SDK=importlib.util.module_from_spec(spec);spec.loader.exec_module(SDK)
module=SDK.module;digest=SDK.digest
EVIDENCE='config/list-construction-origin-evidence.json'
MANIFEST_SHA256='5aef9d6a4703aca9bc9a5bcd8df95e874258917fd409f21588f434f3d0630d66'
KEYS={'0x0041D8F0':56,'0x0041E2F0':53,'0x0041E1A0':223,'0x0041E22F':80}
CONFIDENCE='complete-header-owned-default-list-code-data-and-shared-catch-graph'
LAYOUT=[8,8,4,20,20,20,108,12,16,16,1,1,12]
EXTERNAL={'__except_list':'0x00000000','__CxxThrowException@8':'0x00640C12','___CxxFrameHandler':'0x006407B8','??3@YAXPAX@Z':'0x00640F15','??2@YAPAXI@Z':'0x0064159D'}
CONTROL_SIZES=[56,53,223,14,16,53,10,27,8,29,11,25,25,28,16,80,20,58,5,16,8,14]

def manifest():return json.loads((ROOT/EVIDENCE).read_text())

def verify_plan(m):
    prior=json.loads((ROOT/'config/indexed-owner-policy-origin-evidence.json').read_text())
    if (m['evidence_id']!='R181' or m['target_sha256']!=prior['target_sha256']
            or m['probe']!='probes/VC7ListConstructionAlternatives.cpp' or m['profile']!=SDK.PROFILE
            or len(m['functions'])!=4 or {r['address']:r['size'] for r in m['functions']}!=KEYS
            or len(m['controls'])!=22 or [r['size'] for r in m['controls']]!=CONTROL_SIZES
            or sum(len(r['bindings']) for r in m['controls'])!=35
            or len(m['emission'])!=65 or sum(r['size'] for r in m['emission'])!=2690 or len(m['headers'])!=30
            or len(m['snapshots'])!=168 or len({r['address'] for r in m['snapshots']})!=168
            or {r['address']:r['size'] for r in m['anchors']}!={'0x0041D190':90,'0x0041D6C0':133}
            or len(m['retained'])!=4 or m['frame']['handler_address']!='0x00655470'
            or m['frame']['evidence_id']!='R020' or m['frame']['state_count']!='2' or m['frame']['try_count']!='1'
            or m['layout'] not in m['emission'] or m['layout']['size']!=52 or m['layout_values']!=LAYOUT
            or m['external']!=EXTERNAL or m['protected']!=dict(prior['protected'],**{'0x0041E330':14})):
        raise ValueError('list construction loses complete source/code/data/fields/context scope')
    controls={r['address']:r for r in m['controls'][:-1]}
    for r in m['functions']:
        a=r['address'];old,new=r['original_function'],r['accepted_function']
        allowed={'proposed_name','module','status','owner','evidence','notes'}|({'size','span_end'} if a=='0x0041E1A0' else set())
        if (r['decision']!='library' or r['original_origin']['origin']!='unknown' or old['address']!=a
                or int(old['size'])!=(143 if a=='0x0041E1A0' else r['size']) or r['original_size']!=int(old['size'])
                or {k:v for k,v in old.items() if k not in allowed}!={k:v for k,v in new.items() if k not in allowed}
                or new['size']!=str(r['size']) or new['span_end']!=f'0x{int(a,16)+r["size"]-1:08X}'
                or new['module']!='VC7STL' or new['owner']!='library' or new['status']!='excluded'
                or new['source_file'] or new['signature'] or new['calling_convention'] or new['match_percent']!='0.00'
                or 'accepted_authored_record' in r or r['accepted_origin']!=dict(address=a,origin='library',subsystem='VC7STL',disposition='exclude',confidence=CONFIDENCE,evidence_id='R181')):
            raise ValueError('list construction alters unrelated extent or grants false source/ABI/exact credit')
        if r['source_owner'] not in controls:raise ValueError('list construction invents a standalone source owner')
        owner=controls[r['source_owner']];offset=r['source_offset'];d=r['source_definition']
        if (d not in owner['section']['definitions'] or d['offset']!=offset
                or offset+r['size']!=owner['size'] or d['type']!=32
                or r['source_owner']!=('0x0041E1A0' if a=='0x0041E22F' else a)
                or offset!=(143 if a=='0x0041E22F' else 0)
                or d['storage']!=(3 if a=='0x0041E22F' else 2) or 'Ordinary' in d['symbol']):
            raise ValueError('list construction substitutes a prefix or a fictitious standalone callback')
    for r in m['controls']:
        ss,d=r['section'],r['source_definition']
        if (ss not in m['emission'] or ss['size']!=r['size'] or d not in ss['definitions']
                or ss['source_sha256']!=r['source_sha256'] or len(ss['fields'])!=len(r['bindings'])
                or d['offset']!=(52 if r['kind']=='data' else 0)):
            raise ValueError('list construction truncates a whole defining carrier')
        if r['kind']=='code' and (d['type']!=32 or d['storage']!=(3 if r['address']=='0x00655470' else 2)):
            raise ValueError('list construction loses its own primary or generated definition')
        for field,b in zip(ss['fields'],r['bindings']):
            if (b!=dict(offset=field['offset'],type=field['type'],symbol=field['symbol']['symbol'],addend=field['addend'],target_address=b['target_address'])
                    or field['type'] not in ('REL32','DIR32') or field['offset']+4>r['size']):
                raise ValueError('list construction masks, drops or substitutes a genuine field')
    node=controls['0x0041E1A0'];entry=m['shared_entry'];d=entry['definition']
    if (entry!=dict(address='0x0041E22F',owner='0x0041E1A0',owner_size=223,offset=143,size=80,definition=d,section=node['section'],original_split_size=143,original_jump_site='0x0041E22D',shared_exit='0x0041E264',source_shared_exit_offset=196)
            or d not in node['section']['definitions'] or d['offset']!=143 or d['type']!=32 or d['storage']!=3 or not d['symbol'].startswith('$L')
            or [q for q in node['section']['definitions'] if q['type']==32 and q['storage']==3]!=[d] or node['cfg']!=[1,2]):
        raise ValueError('list construction loses entire shared owner/catch and reconciled exit')
    state=controls['0x006685F8']
    if (state['kind']!='data' or state['size']!=80 or not any(b['symbol']==d['symbol'] and b['target_address']=='0x0041E22F' for b in state['bindings'])
            or not any(b['target_address']=='0x0066862C' for b in controls['0x00655470']['bindings'])):
        raise ValueError('list construction loses real complete try-map/handler linkage')
    ordinary=m['controls'][-1]
    if (ordinary['address']!='0x0041E330' or ordinary['size']!=14 or 'Ordinary' not in ordinary['source_definition']['symbol']
            or ordinary['bindings'] or ordinary['role']!='byte-equal-ordinary-empty-constructor'):
        raise ValueError('list construction loses complete ambiguous ordinary allocator alternative')
    snapshots={r['address']:r for r in m['snapshots']}
    for a,size in m['protected'].items():
        if snapshots[a]['size']!=size or snapshots[a]['origin']['origin']!='unknown':raise ValueError('list construction resolves an opaque child from source equality')

def accepted_snapshot(snapshot,function,origin):
    if digest((ROOT/EVIDENCE).read_bytes())!=MANIFEST_SHA256:raise ValueError('list construction immutable manifest differs')
    m=manifest();verify_plan(m);r=next((r for r in m['functions'] if r['address']==function['address']),None)
    return bool(r and snapshot==dict(function=r['original_function'],origin=r['original_origin'])
                and function==r['accepted_function'] and origin==r['accepted_origin'])

def included_headers(output):
    found={}
    for line in output.splitlines():
        if 'Note: including file:' not in line:continue
        name=line.split('Note: including file:',1)[1].strip().replace('\\','/')
        if name[:3].lower()!='z:/':raise ValueError('list construction include loses actual host mapping')
        path=Path(name[2:]);relative=str(path.relative_to(ROOT))
        if relative!='probes/VC7IndexedOwnerPolicies.cpp' and not relative.startswith('.tools/msvc710/Vc7/include/'):
            raise ValueError('list construction gains an unreviewed include owner')
        found[relative]=digest(path.read_bytes())
    return found

def verify_generated_handler(row,data,coff_name):
    ss,d=row['section'],row['source_definition']
    if (ss['size']!=10 or d['offset'] or d['type']!=32 or d['storage']!=3
            or [q for q in ss['definitions'] if q['type']==32]!=[d] or not ss['flags']&0x20 or not ss['flags']&0x1000):
        raise ValueError('list construction handler loses entire unique generated COMDAT')
    _,_,_,offset,count,_,_=struct.unpack_from('<HHIIIHH',data);strings_at=offset+count*18
    length=struct.unpack_from('<I',data,strings_at)[0];strings=data[strings_at:strings_at+length];found=[];i=0
    while i<count:
        name,value,number,kind,storage,aux=struct.unpack_from('<8sIhHBB',data,offset+i*18)
        if coff_name(name,strings)==d['symbol'] and number>0:found.append((value,number,kind,storage,aux))
        i+=1+aux
    if found!=[(0,ss['section'],32,3,0)]:raise ValueError('list construction handler changes its generated definition metadata')

def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args();m=manifest();verify_plan(m)
    for path,expected in [(EVIDENCE,MANIFEST_SHA256),(m['probe'],m['probe_sha256']),*m['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes())!=expected:raise ValueError('list construction immutable source/prior evidence differs: '+path)
    c=module('construction_target','compare-coff-function.py');coff=module('construction_coff','coff_data.py');cfg=module('construction_cfg','verify-authored-origins.py')
    extent=module('construction_extent','verify-vendor-record-origins.py');bounded=module('construction_bounded','verify-game-context-origins.py');target=c.verified_target();rows=cfg.rows
    if digest(target)!=m['target_sha256']:raise ValueError('list construction target identity differs')
    functions={r['address']:r for r in rows('functions.csv')};origins={r['address']:r for r in rows('function-origins.csv')};authored={r['address']:r for r in rows('authored-origin-evidence.csv')};records={r['address']:r for r in m['functions']}
    if any(r['evidence_id']=='R181' for r in authored.values()):raise ValueError('list construction adds false authored credit')
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    def witness(raw,a):return [dict(site=f'0x{x.address:08X}',mnemonic=x.mnemonic,operands=x.op_str) for x in decoder.disasm(raw,int(a,16))]
    for r in m['functions']:
        a=r['address'];SDK.check_ledger(r,functions[a],origins[a],args.evidence_only);raw=c.pe_bytes_at(target,int(a,16),r['size'])
        if digest(raw)!=r['body_sha256'] or witness(raw,a)!=r['witnesses'] or list(cfg.verify_body(raw,int(a,16)))!=r['cfg']:
            raise ValueError('list construction entire accepted body/CFG differs')
        contained={q for q in functions if int(a,16)<int(q,16)<int(a,16)+r['size']}
        if contained!=({'0x0041E22F'} if a=='0x0041E1A0' else set()):raise ValueError('list construction hides an unrelated entry in extent')
    for r in m['snapshots']:
        a=r['address']
        if a in records:SDK.check_ledger(records[a],functions[a],origins[a],args.evidence_only)
        elif functions[a]!=r['function'] or origins[a]!=r['origin']:raise ValueError('list construction changes unrelated canonical context')
        if digest(c.pe_bytes_at(target,int(a,16),r['size']))!=r['body_sha256']:raise ValueError('list construction original full target snapshot differs')
    for r in m['retained']:
        if r['record'] not in json.loads((ROOT/r['file']).read_text())[r['collection']]:raise ValueError('list construction original complete source record differs')
    for r in m['anchors']:
        a=r['address'];raw=c.pe_bytes_at(target,int(a,16),r['size'])
        if functions[a]!=r['function'] or origins[a]!=r['origin'] or authored[a]!=r['record'] or digest(raw)!=r['body_sha256'] or witness(raw,a)!=r['witnesses']:
            raise ValueError('list construction original full authored anchor differs')
        for file,key in [('authored-origin-switches.csv','switches'),('authored-origin-direct-switches.csv','direct_switches')]:
            if [q for q in rows(file) if q['address']==a]!=r[key]:raise ValueError('list construction original switch evidence differs')
        if list(cfg.verify_body(raw,int(a,16),r['switches'],lambda a,n:c.pe_bytes_at(target,a,n),r['direct_switches']))!=r['cfg']:raise ValueError('list construction entire anchor CFG differs')
    frame=m['frame'];eh=module('construction_eh','compiler_eh.py')
    if frame not in rows('compiler-eh-frames.csv'):raise ValueError('list construction original complete frame differs')
    eh.verify_frame(frame,lambda a,n:c.pe_bytes_at(target,a,n),lambda a,n:c.pe_bytes_at(target,a,n),{int(a,16) for a in functions})
    # Verify the complete original handler table, including its actual local entry.
    low,high,catch_high,count,handlers=struct.unpack('<5I',c.pe_bytes_at(target,int(frame['trymap_address'],16),20))
    if (low,high,catch_high,count)!=(0,0,1,1) or struct.unpack('<4I',c.pe_bytes_at(target,handlers,16))!=(0,0,0,0x41E22F):
        raise ValueError('list construction original complete catch table differs')
    scratch=ROOT/'build/origin-list-construction-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as dirname:
        path=Path(dirname)/'ListConstruction.obj';result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/m['probe']),str(path),*m['profile']],cwd=ROOT,capture_output=True,text=True)
        if result.returncode or included_headers(result.stdout+result.stderr)!=m['headers']:raise ValueError('list construction cold source/actual includes differ')
        data=path.read_bytes()
        if SDK.PAIRED.BUFFER.inventory(data,c,coff)!=m['emission']:raise ValueError('list construction full ordinary emission differs')
        catalog={}
        def add(name,address):
            if name in catalog and catalog[name]!=address:raise ValueError('list construction overrides coherent full source definition')
            catalog[name]=address
        for r in m['controls']:
            for d in r['section']['definitions']:
                if d['storage'] in (2,3) and not d['symbol'].startswith('.'):add(d['symbol'],int(r['address'],16)+d['offset'])
        for name,address in EXTERNAL.items():add(name,int(address,16))
        linked_controls=[]
        for r in m['controls']:
            for b in r['bindings']:
                if catalog.get(b['symbol'])!=int(b['target_address'],16):raise ValueError('list construction loses actual complete source/external linkage')
            raw,linked=SDK.ENDPOINT.link(data,r,catalog,c);actual=c.pe_bytes_at(target,int(r['address'],16),r['size'])
            if len(raw)!=r['size'] or linked!=actual or digest(raw)!=r['source_sha256'] or digest(actual)!=r['body_sha256']:
                raise ValueError('list construction full unmasked comparison differs: '+r['address'])
            linked_controls.append(linked)
            if r['kind']=='code':
                if r['address']=='0x00655470':verify_generated_handler(r,data,c.coff_name)
                elif extent.complete_aux_section_size(data,r['source_definition']['symbol'],c.coff_name)!=r['size']:raise ValueError('list construction loses full own primary AUX')
                if bounded.verify_bounded_context(actual,int(r['address'],16),r['external_tails'])!=r['cfg']:raise ValueError('list construction whole CFG/tail differs')
            else:
                head=struct.unpack_from('<8sIIIIIIHHI',data,20+(r['section']['section']-1)*40)
                if head[3]!=80 or not head[9]&0x40000000 or head[9]&0xA0000000 or data[head[4]:head[4]+head[3]]!=raw:
                    raise ValueError('list construction truncates complete readonly EH metadata')
                sections=module('construction_sections','verify-compiler-origins.py').sections(target);start=int(r['address'],16)
                if not any(base<=start and start+80<=base+size and flags&0x40000000 and not flags&0xA0000000 for base,size,flags in sections):
                    raise ValueError('list construction original EH metadata loses readonly extent')
        entry=m['shared_entry'];parent=linked_controls[2];callback=parent[entry['offset']:]
        if callback!=c.pe_bytes_at(target,0x41E22F,80) or list(cfg.verify_body(callback,0x41E22F))!=records['0x0041E22F']['cfg']:
            raise ValueError('list construction source-owned entire callback/shared exit differs')
        if ('0x0041E22D','jmp','0x41e264') not in {(r['site'],r['mnemonic'],r['operands']) for r in witness(parent,'0x0041E1A0')}:
            raise ValueError('list construction loses original node-to-shared-exit jump')
        if linked_controls[3]!=linked_controls[-1]:raise ValueError('list construction hides ordinary empty-constructor ambiguity')
        raw,_=coff.readonly_section(data,m['layout']['section'],c.coff_name)
        if list(struct.unpack('<13I',raw))!=LAYOUT:raise ValueError('list construction entire combined readonly layout differs')
    print('R181 origins OK: four library ledger entries /412 bytes, with80 shared bytes and332 distinct primary bytes; complete223-byte node owner and80-byte source-local catch/shared exit;22 full code/EH/data/ordinary controls /795 bytes,35 real unmasked fields;65 cold ordinary sections /2690 bytes,30 actual includes,52-byte layout;168 snapshots,41 protected unknowns,223-byte authored anchors and original R020 frame preserved;14-byte empty allocator stays unknown; no source/ABI/mapping/exact credit, exact stays60.')
    return 0

if __name__=='__main__':
    try:raise SystemExit(main())
    except (OSError,KeyError,IndexError,StopIteration,ValueError,struct.error,json.JSONDecodeError) as error:
        print('error: '+str(error),file=sys.stderr);raise SystemExit(1)
