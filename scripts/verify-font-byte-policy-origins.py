#!/usr/bin/env python3
"""Cold-replay complete font/resource controls while retaining classifier ambiguity."""
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
spec=importlib.util.spec_from_file_location('font_byte_sdk',ROOT/'scripts/verify-sdk-dependency-origins.py')
SDK=importlib.util.module_from_spec(spec);spec.loader.exec_module(SDK)
module=SDK.module;digest=SDK.digest
EVIDENCE='config/font-byte-policy-origin-evidence.json'
MANIFEST_SHA256='c426f7d1024c3bd35a6b26d6f497062fa21a2aded92479ca28acacb64bbd3cc2'
KEYS={'0x0041C9D0':85,'0x0041BF90':64}
CONFIDENCE='complete-explicit-font-byte-and-resource-default-policy-with-whole-game-context'
LAYOUT=[1,1,20,20,1,4]
POLICIES=[('whole-sdk-macro-alternative',25),('whole-ordinary-classifier-caller',17),('whole-byte-decoder-caller',21),('whole-explicit-resource-caller',108),('whole-generated-default-initialization-caller',25)]
IMPORTS=[dict(address=a,dll=d,name=n) for a,d,n in [('0x00657048','GDI32.dll','SelectObject'),('0x0065704C','GDI32.dll','DeleteObject'),('0x00657214','USER32.dll','ReleaseDC')]]

def manifest():return json.loads((ROOT/EVIDENCE).read_text())

def verify_plan(m):
    prior=json.loads((ROOT/'config/math-table-policy-origin-evidence.json').read_text())
    if (m['evidence_id']!='R183' or m['target_sha256']!=prior['target_sha256']
            or m['probe']!='probes/VC7FontBytePolicies.cpp' or m['profile']!=SDK.PROFILE
            or len(m['functions'])!=2 or {r['address']:r['size'] for r in m['functions']}!=KEYS
            or len(m['controls'])!=4 or [(r['size'],r['target_size']) for r in m['controls']]!=[(74,85),(64,64),(77,77),(77,77)]
            or sum(len(r['bindings']) for r in m['controls'])!=1
            or len(m['policies'])!=5 or [(r['role'],r['size']) for r in m['policies']]!=POLICIES
            or len(m['emission'])!=14 or sum(r['size'] for r in m['emission'])!=588 or len(m['headers'])!=10
            or len(m['snapshots'])!=187 or len({r['address'] for r in m['snapshots']})!=187
            or {r['address']:r['size'] for r in m['anchors']}!={'0x0041C2E0':1766,'0x00413460':398,'0x00426670':555,'0x0041BFD0':129,'0x0041C130':119}
            or len(m['retained'])!=2 or len(m['frames'])!=2 or {r['handler_address'] for r in m['frames']}!={'0x006550B5','0x006557F9'}
            or m['layout'] not in m['emission'] or m['layout']['size']!=24 or m['layout_values']!=LAYOUT
            or m['protected']!=dict(prior['protected'],**{'0x0041CA30':77}) or m['import_slots']!=IMPORTS):
        raise ValueError('font byte loses complete bounded source/parent/field/implicit scope')
    mutable={'proposed_name','module','status','owner','evidence','notes'}
    for r in m['functions']:
        a=r['address'];old,new=r['original_function'],r['accepted_function'];owner='FontSurface' if a=='0x0041C9D0' else 'RasterResources'
        if (r['decision']!='authored' or r['original_origin']['origin']!='unknown' or old['address']!=a or int(old['size'])!=r['size']
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['module']!=owner or new['owner']!='authored' or new['status']!='unclassified'
                or new['source_file'] or new['calling_convention'] or new['signature'] or new['match_percent']!='0.00' or 'symbol' in r
                or r['accepted_origin']!=dict(address=a,origin='authored',subsystem=owner,disposition='authored',confidence=CONFIDENCE,evidence_id='R183')
                or r['accepted_authored_record']!=dict(address=a,size=str(r['size']),body_sha256=r['body_sha256'],inferred_role=new['proposed_name'],return_count=str(r['cfg'][0]),internal_branch_count=str(r['cfg'][1]),external_branch_count='0',evidence_id='R183')):
            raise ValueError('font byte alters original extent or invents source/private ABI/exact credit')
    roles=['whole-byte-load-width-negative','whole-small-layout-negative','whole-source-lead-context','whole-byte-equal-ordinary-lead-alternative']
    for i,r in enumerate(m['controls']):
        ss,d=r['section'],r['source_definition']
        if (ss not in m['emission'] or ss['size']!=r['size'] or d not in ss['definitions'] or d['offset'] or d['type']!=32 or d['storage']!=2
                or ss['source_sha256']!=r['source_sha256'] or len(ss['fields'])!=len(r['bindings']) or r['role']!=roles[i]
                or r['comparison']!=('whole-negative' if i<2 else 'positive')
                or r['address']!=(['0x0041C9D0','0x0041BF90','0x0041CA30','0x0041CA30'][i])):
            raise ValueError('font byte truncates complete control or assigns opaque helper ownership')
        for field,b in zip(ss['fields'],r['bindings']):
            if b!=dict(offset=field['offset'],type=field['type'],symbol=field['symbol']['symbol'],addend=field['addend'],target_address='0x0041CA30') or field['type']!='REL32' or field['offset']+4>r['size']:
                raise ValueError('font byte masks, drops or substitutes its real classifier call')
        if i==0 and len(r['differences'])!=44:raise ValueError('font byte hides complete source load-width differences')
        if i==1 and r['differences']!=[dict(offset=50,source=16,target=20)]:raise ValueError('font byte hides actual small-owner storage offset')
        if i>=2 and (r['differences'] or r['bindings']):raise ValueError('font byte loses ordinary/source whole classifier equality')
    if 'Ordinary' not in m['controls'][3]['source_definition']['symbol']:raise ValueError('font byte loses independent generic classifier alternative')
    for r in m['policies']:
        ss,d=r['section'],r['source_definition']
        if (ss not in m['emission'] or ss['size']!=r['size'] or d not in ss['definitions'] or d['offset'] or d['type']!=32 or d['storage']!=2
                or ss['source_sha256']!=r['source_sha256'] or 'target_positive' in r or 'bindings' in r):
            raise ValueError('font byte invents SDK/implicit target binding or loses full source definition')
        if r['call_symbols']!=[q['symbol']['symbol'] for q in ss['fields'] if q['type']=='REL32']:raise ValueError('font byte changes actual complete source call route')
    fields=m['policies'][0]['section']['fields']
    if len(fields)!=1 or fields[0]['offset']!=10 or fields[0]['type']!='DIR32' or fields[0]['symbol']['symbol']!='__mbctype' or fields[0]['addend']!=1:
        raise ValueError('font byte loses SDK macro actual unresolved table field')
    if m['policies'][4]['call_symbols']!=['??2@YAPAXIPAX@Z']:raise ValueError('font byte gives implicit POD construction a fictitious explicit initializer')
    records={r['address']:r for r in m['functions']}
    if [w['operands'] for w in records['0x0041C9D0']['witnesses'] if w['mnemonic']=='call']!=['0x41ca30'] or any(w['mnemonic']=='call' for w in records['0x0041BF90']['witnesses']):
        raise ValueError('font byte loses native operation/callee separation')
    required={'0x0041C9D0':[('0x0041C9EF','mov','ecx, dword ptr [eax]'),('0x0041C9F1','and','ecx, 0xff'),('0x0041C9F7','shl','ecx, 8'),('0x0041C9FD','mov','eax, dword ptr [edx]'),('0x0041C9FF','and','eax, 0xff00'),('0x0041CA04','sar','eax, 8'),('0x0041CA0E','mov','al, 2'),('0x0041CA15','movsx','ecx, byte ptr [eax]'),('0x0041CA1D','mov','al, 1')],
              '0x0041BF90':[('0x0041BF9A','mov','ecx, dword ptr [ebp + 8]'),('0x0041BF9D','mov','dword ptr [eax], ecx'),('0x0041BFA2','mov','dword ptr [edx + 4], 0'),('0x0041BFAC','mov','dword ptr [eax + 8], 0'),('0x0041BFB6','mov','dword ptr [ecx + 0xc], 0'),('0x0041BFC0','mov','dword ptr [edx + 0x14], 0')]}
    for a,expected in required.items():
        if not set(expected)<={(w['site'],w['mnemonic'],w['operands']) for w in records[a]['witnesses']}:raise ValueError('font byte changes actual load width/sign/output or explicit resource state')
    p=m['pending'];snapshots={r['address']:r for r in m['snapshots']}
    if (p['address']!='0x0041CA30' or p['size']!=77 or p['origin']['origin']!='unknown' or p['function']['owner'] or 'accepted_origin' in p
            or p['cfg']!=[1,8] or p['function']!=snapshots[p['address']]['function'] or p['origin']!=snapshots[p['address']]['origin']):
        raise ValueError('font byte gives fixed-range helper unproven ownership')
    for a,size in m['protected'].items():
        if snapshots[a]['size']!=size or snapshots[a]['origin']['origin']!='unknown':raise ValueError('font byte resolves an independently opaque prior helper')

def verify_control(r,raw,linked,actual):
    if len(raw)!=r['size'] or len(linked)!=r['size'] or len(actual)!=r['target_size'] or digest(raw)!=r['source_sha256'] or digest(actual)!=r['body_sha256']:
        raise ValueError('font byte compares a prefix or changes entire source/target bytes')
    differences=[dict(offset=i,source=a,target=b) for i,(a,b) in enumerate(zip(linked,actual)) if a!=b]
    if differences!=r['differences'] or (linked==actual)!=(r['comparison']=='positive'):raise ValueError('font byte whole unmasked comparison differs')

def included_headers(output):
    found={}
    for line in output.splitlines():
        if 'Note: including file:' not in line:continue
        name=line.split('Note: including file:',1)[1].strip().replace('\\','/')
        if name[:3].lower()!='z:/':raise ValueError('font byte include loses actual host mapping')
        path=Path(name[2:]);relative=str(path.relative_to(ROOT))
        if not relative.startswith('.tools/msvc710/Vc7/include/'):raise ValueError('font byte gains unreviewed include ownership')
        found[relative]=digest(path.read_bytes())
    return found

def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args();m=manifest();verify_plan(m)
    for path,expected in [(EVIDENCE,MANIFEST_SHA256),(m['probe'],m['probe_sha256']),*m['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes())!=expected:raise ValueError('font byte immutable source/prior evidence differs: '+path)
    c=module('font_byte_target','compare-coff-function.py');coff=module('font_byte_coff','coff_data.py');cfg=module('font_byte_cfg','verify-authored-origins.py');extent=module('font_byte_extent','verify-vendor-record-origins.py');target=c.verified_target();rows=cfg.rows
    functions={r['address']:r for r in rows('functions.csv')};origins={r['address']:r for r in rows('function-origins.csv')};authored={r['address']:r for r in rows('authored-origin-evidence.csv')};records={r['address']:r for r in m['functions']};decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    def witness(raw,a):return [dict(site=f'0x{x.address:08X}',mnemonic=x.mnemonic,operands=x.op_str) for x in decoder.disasm(raw,int(a,16))]
    if digest(target)!=m['target_sha256'] or {a for a,r in authored.items() if r['evidence_id']=='R183'}!=(set() if args.evidence_only else set(KEYS)):raise ValueError('font byte target/authored registry differs')
    for r in m['functions']:
        a=r['address'];SDK.check_ledger(r,functions[a],origins[a],args.evidence_only);raw=c.pe_bytes_at(target,int(a,16),r['size'])
        if not args.evidence_only and authored[a]!=r['accepted_authored_record']:raise ValueError('font byte new whole authored evidence differs')
        if digest(raw)!=r['body_sha256'] or witness(raw,a)!=r['witnesses'] or list(cfg.verify_body(raw,int(a,16)))!=r['cfg']:raise ValueError('font byte entire accepted body/CFG differs')
        if any(int(a,16)<int(q,16)<int(a,16)+r['size'] for q in functions):raise ValueError('font byte extent hides another entry')
    for r in m['snapshots']:
        a=r['address']
        if a in records:SDK.check_ledger(records[a],functions[a],origins[a],args.evidence_only)
        elif functions[a]!=r['function'] or origins[a]!=r['origin']:raise ValueError('font byte changes unrelated canonical evidence')
        if int(functions[a]['size'])!=r['size'] or digest(c.pe_bytes_at(target,int(a,16),r['size']))!=r['body_sha256']:raise ValueError('font byte original full snapshot differs')
    p=m['pending'];raw=c.pe_bytes_at(target,int(p['address'],16),p['size'])
    if witness(raw,p['address'])!=p['witnesses'] or list(cfg.verify_body(raw,int(p['address'],16)))!=p['cfg']:raise ValueError('font byte complete opaque classifier differs')
    for r in m['retained']:
        if r['record'] not in json.loads((ROOT/r['file']).read_text())[r['collection']]:raise ValueError('font byte original whole release record differs')
    for r in m['anchors']:
        a=r['address'];raw=c.pe_bytes_at(target,int(a,16),r['size']);ws=witness(raw,a)
        if functions[a]!=r['function'] or origins[a]!=r['origin'] or authored[a]!=r['record'] or digest(raw)!=r['body_sha256'] or any(w not in ws for w in r['selected_witnesses']):raise ValueError('font byte entire original game/release anchor differs')
        for file,key in [('authored-origin-switches.csv','switches'),('authored-origin-direct-switches.csv','direct_switches')]:
            if [q for q in rows(file) if q['address']==a]!=r[key]:raise ValueError('font byte original complete parent switch evidence differs')
        if list(cfg.verify_body(raw,int(a,16),r['switches'],lambda a,n:c.pe_bytes_at(target,a,n),r['direct_switches']))!=r['cfg']:raise ValueError('font byte whole original parent CFG differs')
    eh=module('font_byte_eh','compiler_eh.py')
    for frame in m['frames']:
        if frame not in rows('compiler-eh-frames.csv'):raise ValueError('font byte original full EH frame differs')
        eh.verify_frame(frame,lambda a,n:c.pe_bytes_at(target,a,n),lambda a,n:c.pe_bytes_at(target,a,n),{int(a,16) for a in functions})
    imports=module('font_byte_imports','verify-import-origins.py').pe_imports(target,c)
    for r in IMPORTS:
        if imports[int(r['address'],16)]!=(r['dll'],r['name']):raise ValueError('font byte original actual release import differs')
    scratch=ROOT/'build/origin-font-byte-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as dirname:
        path=Path(dirname)/'FontBytePolicies.obj';result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/m['probe']),str(path),*m['profile']],cwd=ROOT,capture_output=True,text=True)
        if result.returncode or included_headers(result.stdout+result.stderr)!=m['headers']:raise ValueError('font byte cold source/actual includes differ')
        data=path.read_bytes()
        if SDK.PAIRED.BUFFER.inventory(data,c,coff)!=m['emission']:raise ValueError('font byte complete ordinary emission differs')
        catalog={}
        for r in m['controls']:
            d=r['source_definition'];name=d['symbol'];a=int(r['address'],16)
            if name in catalog and catalog[name]!=a:raise ValueError('font byte overrides coherent whole source definition')
            catalog[name]=a
        for r in m['controls']:
            for b in r['bindings']:
                if catalog.get(b['symbol'])!=int(b['target_address'],16):raise ValueError('font byte loses actual opaque-source callee linkage')
            raw,linked=SDK.ENDPOINT.link(data,r,catalog,c);actual=c.pe_bytes_at(target,int(r['address'],16),r['target_size']);verify_control(r,raw,linked,actual)
            if extent.complete_aux_section_size(data,r['source_definition']['symbol'],c.coff_name)!=r['size'] or list(cfg.verify_body(linked,int(r['address'],16)))!=r['source_cfg']:raise ValueError('font byte source loses own full primary or CFG')
            if list(cfg.verify_body(actual,int(r['address'],16)))!=r['target_cfg']:raise ValueError('font byte comparison loses full original CFG')
        for r in m['policies']:
            h=struct.unpack_from('<8sIIIIIIHHI',data,20+(r['section']['section']-1)*40);raw=data[h[4]:h[4]+h[3]]
            if len(raw)!=r['size'] or digest(raw)!=r['source_sha256'] or witness(raw,'0x00000000')!=r['witnesses'] or list(cfg.verify_body(raw,0))!=r['cfg'] or extent.complete_aux_section_size(data,r['source_definition']['symbol'],c.coff_name)!=r['size']:
                raise ValueError('font byte whole SDK/default/caller source control differs')
        raw,_=coff.readonly_section(data,m['layout']['section'],c.coff_name)
        if list(struct.unpack('<6I',raw))!=LAYOUT:raise ValueError('font byte whole source layout differs')
    print('R183 origins OK: two whole authored font/resource policies /149 bytes;full74-versus85 decoder negative with44 positional differences and11 extra original bytes;full64-byte constructor negative with one actual storage-offset difference;77-byte lead helper stays unknown despite two full equal source/ordinary controls;five whole SDK/implicit/caller controls /196 bytes,including real unresolved SDK table field;14 cold ordinary sections /588 bytes,ten headers,24-byte layout;187 snapshots,42 protected unknowns,2967 bytes of whole authored parents/releases,two original release records,two full frames and three real imports preserved;no source/private ABI/mapping/exact credit,exact stays60.')
    return 0

if __name__=='__main__':
    try:raise SystemExit(main())
    except (OSError,KeyError,IndexError,StopIteration,ValueError,struct.error,json.JSONDecodeError) as error:
        print('error: '+str(error),file=sys.stderr);raise SystemExit(1)
