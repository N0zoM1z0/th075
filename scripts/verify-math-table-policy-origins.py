#!/usr/bin/env python3
"""Cold-replay full custom table policies and preserve independent math ambiguities."""
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
spec=importlib.util.spec_from_file_location('math_table_sdk',ROOT/'scripts/verify-sdk-dependency-origins.py')
SDK=importlib.util.module_from_spec(spec);spec.loader.exec_module(SDK)
module=SDK.module;digest=SDK.digest
EVIDENCE='config/math-table-policy-origin-evidence.json'
MANIFEST_SHA256='98325bcd58a9dbb8c9ede7bde4820abfd95a1ecd37b22baa6936b76a9f80b2ef'
KEYS={'0x0041CAE0':82,'0x0041CB40':43,'0x0041CB70':49,'0x0041CBB0':73,'0x00454D00':79}
CONFIDENCE='complete-explicit-game-table-and-indexed-counter-policy'
LAYOUT=[14400,4,6,14]
EXTERNAL={'?MathLookupObservation@@3PAMA':'0x006884C0','_cos':'0x00641754','__ftol2':'0x006406AC','_abs':'0x00641DAA'}
CONSTANTS=[('0x00657B10',8,180.0),('0x00657B18',8,3.1415926535),('0x00657B20',8,10.0),('0x00657850',4,10.0),('0x00657B28',4,900.0),('0x0065782C',4,0.0)]
RATIO_DIFFERENCES=[dict(offset=48+i,source=a,target=b) for i,(a,b) in enumerate(zip([131,196,4,217,93,252],[217,93,252,131,196,4]))]

def manifest():return json.loads((ROOT/EVIDENCE).read_text())

def verify_plan(m):
    prior=json.loads((ROOT/'config/list-construction-origin-evidence.json').read_text())
    if (m['evidence_id']!='R182' or m['target_sha256']!=prior['target_sha256']
            or m['probe']!='probes/VC7MathTablePolicies.cpp' or m['profile']!=SDK.PROFILE
            or len(m['functions'])!=5 or {r['address']:r['size'] for r in m['functions']}!=KEYS
            or len(m['controls'])!=10 or [r['size'] for r in m['controls']]!=[82,43,49,73,8,8,8,4,4,4]
            or sum(len(r['bindings']) for r in m['controls'])!=19
            or len(m['emission'])!=13 or sum(r['size'] for r in m['emission'])!=383 or len(m['headers'])!=2
            or len(m['snapshots'])!=179 or len({r['address'] for r in m['snapshots']})!=179
            or {r['address']:r['size'] for r in m['anchors']}!={'0x00602A60':2987,'0x0057D580':43845,'0x00452B30':215,'0x0042A180':315}
            or len(m['retained'])!=4 or m['layout'] not in m['emission'] or m['layout']['size']!=16 or m['layout_values']!=LAYOUT
            or m['external']!=EXTERNAL or m['protected']!=prior['protected']
            or m['table_span']!=dict(address='0x006884C0',size=14400,element_count=3600,element_width=4,scope='selected-used-writable-range-only')
            or [(r['address'],r['size'],r['value']) for r in m['constants']]!=CONSTANTS):
        raise ValueError('math table loses whole bounded functions/source/fields/table/context scope')
    mutable={'proposed_name','module','status','owner','evidence','notes'}
    for r in m['functions']:
        a=r['address'];old,new=r['original_function'],r['accepted_function'];owner='ProfileSelection' if a=='0x00454D00' else 'MathLookup'
        if (r['decision']!='authored' or r['original_origin']['origin']!='unknown' or old['address']!=a or int(old['size'])!=r['size']
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['module']!=owner or new['owner']!='authored' or new['status']!='unclassified'
                or new['source_file'] or new['calling_convention'] or new['signature'] or new['match_percent']!='0.00' or 'symbol' in r
                or r['accepted_origin']!=dict(address=a,origin='authored',subsystem=owner,disposition='authored',confidence=CONFIDENCE,evidence_id='R182')
                or r['accepted_authored_record']!=dict(address=a,size=str(r['size']),body_sha256=r['body_sha256'],inferred_role=new['proposed_name'],return_count=str(r['cfg'][0]),internal_branch_count=str(r['cfg'][1]),external_branch_count='0',evidence_id='R182')):
            raise ValueError('math table alters original extent or grants false source/ABI/mapping/exact credit')
    for i,r in enumerate(m['controls']):
        ss,d=r['section'],r['source_definition']
        if (ss not in m['emission'] or ss['size']!=r['size'] or d not in ss['definitions'] or d['offset']
                or ss['source_sha256']!=r['source_sha256'] or len(ss['fields'])!=len(r['bindings'])
                or r['kind']!=('code' if i<4 else 'data') or d['storage']!=2 or d['type']!=(32 if i<4 else 0)
                or r['comparison']!=('whole-negative' if i==3 else 'positive') or r['differences']!=(RATIO_DIFFERENCES if i==3 else [])):
            raise ValueError('math table truncates defining carrier or invents a whole-source positive')
        for field,b in zip(ss['fields'],r['bindings']):
            if (b!=dict(offset=field['offset'],type=field['type'],symbol=field['symbol']['symbol'],addend=field['addend'],target_address=b['target_address'])
                    or field['type'] not in ('REL32','DIR32') or field['offset']+4>r['size']):
                raise ValueError('math table masks, substitutes or omits a genuine field')
        if i<4 and (r['address']!=m['functions'][i]['address'] or r['size']!=m['functions'][i]['size'] or r['body_sha256']!=m['functions'][i]['body_sha256']):
            raise ValueError('math table substitutes an unrelated original policy')
    if (len(m['policies'])!=2 or [(r['role'],r['size']) for r in m['policies']]!=[('whole-small-counter-policy',67),('whole-counter-caller',17)]):
        raise ValueError('math table replaces whole small-owner control with original-layout padding')
    for r in m['policies']:
        ss,d=r['section'],r['source_definition']
        if ss not in m['emission'] or ss['size']!=r['size'] or d not in ss['definitions'] or d['offset'] or d['type']!=32 or d['storage']!=2 or 'target_positive' in r:
            raise ValueError('math table invents source counter match or loses full primary definition')
        if r['call_symbols']!=[q['symbol']['symbol'] for q in ss['fields'] if q['type']=='REL32']:raise ValueError('math table source counter loses its actual whole call route')
    records={r['address']:r for r in m['functions']}
    calls={'0x0041CAE0':['0x641754'],'0x0041CB40':['0x6406ac','0x641daa'],'0x0041CB70':['0x6406ac','0x641daa'],'0x0041CBB0':['0x41cb40','0x41cb70','0x41cb40'],'0x00454D00':[]}
    for a,expected in calls.items():
        if [w['operands'] for w in records[a]['witnesses'] if w['mnemonic']=='call']!=expected:raise ValueError('math table loses original ordered math/lookup calls')
    required={'0x0041CAE0':[('0x0041CAF6','cmp','dword ptr [ebp - 4], 0xe10'),('0x0041CB02','fdiv','qword ptr [0x657b20]'),('0x0041CB08','fmul','qword ptr [0x657b18]'),('0x0041CB0E','fdiv','qword ptr [0x657b10]'),('0x0041CB25','fstp','dword ptr [ecx*4 + 0x6884c0]')],
              '0x0041CB40':[('0x0041CB46','fmul','dword ptr [0x657850]'),('0x0041CB5B','mov','ecx, 0xe10'),('0x0041CB60','idiv','ecx'),('0x0041CB62','fld','dword ptr [edx*4 + 0x6884c0]')],
              '0x0041CB70':[('0x0041CB7C','fsub','dword ptr [0x657b28]'),('0x0041CB91','mov','ecx, 0xe10'),('0x0041CB96','idiv','ecx'),('0x0041CB98','fld','dword ptr [edx*4 + 0x6884c0]')],
              '0x0041CBB0':[('0x0041CBC0','fld','dword ptr [0x65782c]'),('0x0041CBCA','test','ah, 0x44'),('0x0041CBCD','jp','0x41cbd7'),('0x0041CBF2','fdivr','dword ptr [ebp - 4]')],
              '0x00454D00':[('0x00454D07','movsx','eax, byte ptr [ebp + 8]'),('0x00454D0E','movsx','edx, byte ptr [ecx + 0x16ac4]'),('0x00454D15','imul','edx, edx, 0x17f0'),('0x00454D1E','mov','ax, word ptr [edx + eax*2 + 0x394]'),('0x00454D26','add','ax, 1'),('0x00454D2A','movsx','ecx, byte ptr [ebp + 8]'),('0x00454D31','movsx','edx, byte ptr [edx + 0x16ac4]'),('0x00454D38','imul','edx, edx, 0x17f0'),('0x00454D41','mov','word ptr [edx + ecx*2 + 0x394], ax')]}
    for a,expected in required.items():
        if not set(expected)<={(w['site'],w['mnemonic'],w['operands']) for w in records[a]['witnesses']}:raise ValueError('math table loses actual loop/data/phase/guard or signed counter policy')
    snapshots={r['address']:r for r in m['snapshots']}
    for a,size in m['protected'].items():
        if snapshots[a]['size']!=size or snapshots[a]['origin']['origin']!='unknown':raise ValueError('math table resolves independently opaque helper ownership')

def verify_control(row,raw,linked,actual):
    if len(raw)!=row['size'] or len(linked)!=row['size'] or len(actual)!=row['size'] or digest(raw)!=row['source_sha256'] or digest(actual)!=row['body_sha256']:
        raise ValueError('math table loses entire source/target comparison')
    differences=[dict(offset=i,source=a,target=b) for i,(a,b) in enumerate(zip(linked,actual)) if a!=b]
    expected=RATIO_DIFFERENCES if row['address']=='0x0041CBB0' else []
    if differences!=expected or row['differences']!=expected:raise ValueError('math table whole unmasked comparison differs')

def included_headers(output):
    found={}
    for line in output.splitlines():
        if 'Note: including file:' not in line:continue
        name=line.split('Note: including file:',1)[1].strip().replace('\\','/')
        if name[:3].lower()!='z:/':raise ValueError('math table include loses actual host mapping')
        path=Path(name[2:]);relative=str(path.relative_to(ROOT))
        if not relative.startswith('.tools/msvc710/Vc7/include/'):raise ValueError('math table gains unreviewed include ownership')
        found[relative]=digest(path.read_bytes())
    return found

def verify_table_span(target,span):
    # The observed table is in the loader's zero-filled virtual .data tail.
    # File-backed section lengths cannot validate this used memory range.
    pe=struct.unpack_from('<I',target,0x3C)[0];count=struct.unpack_from('<H',target,pe+6)[0];optional=struct.unpack_from('<H',target,pe+20)[0]
    base=struct.unpack_from('<I',target,pe+24+28)[0];image_size=struct.unpack_from('<I',target,pe+24+56)[0];start=int(span['address'],16)
    for i in range(count):
        head=struct.unpack_from('<8sIIIIIIHHI',target,pe+24+optional+i*40);virtual_size,rva,raw_size,flags=head[1],head[2],head[3],head[9]
        if (base+rva<=start and start+span['size']<=base+rva+virtual_size<=base+image_size
                and flags&0xC0000000==0xC0000000 and not flags&0x20000000):return
    raise ValueError('math table entire used original range loses loaded writable data extent')

def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args();m=manifest();verify_plan(m)
    for path,expected in [(EVIDENCE,MANIFEST_SHA256),(m['probe'],m['probe_sha256']),*m['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes())!=expected:raise ValueError('math table immutable source/prior evidence differs: '+path)
    c=module('math_table_target','compare-coff-function.py');coff=module('math_table_coff','coff_data.py');cfg=module('math_table_cfg','verify-authored-origins.py');extent=module('math_table_extent','verify-vendor-record-origins.py');target=c.verified_target();rows=cfg.rows
    functions={r['address']:r for r in rows('functions.csv')};origins={r['address']:r for r in rows('function-origins.csv')};authored={r['address']:r for r in rows('authored-origin-evidence.csv')};records={r['address']:r for r in m['functions']};decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    def witness(raw,a):return [dict(site=f'0x{x.address:08X}',mnemonic=x.mnemonic,operands=x.op_str) for x in decoder.disasm(raw,int(a,16))]
    if digest(target)!=m['target_sha256'] or {a for a,r in authored.items() if r['evidence_id']=='R182'}!=(set() if args.evidence_only else set(KEYS)):raise ValueError('math table target/authored registry differs')
    for r in m['functions']:
        a=r['address'];SDK.check_ledger(r,functions[a],origins[a],args.evidence_only);raw=c.pe_bytes_at(target,int(a,16),r['size'])
        if not args.evidence_only and authored[a]!=r['accepted_authored_record']:raise ValueError('math table new entire authored record differs')
        if digest(raw)!=r['body_sha256'] or witness(raw,a)!=r['witnesses'] or list(cfg.verify_body(raw,int(a,16)))!=r['cfg']:raise ValueError('math table entire accepted body/CFG differs')
        if any(int(a,16)<int(q,16)<int(a,16)+r['size'] for q in functions):raise ValueError('math table extent hides another function')
    for r in m['snapshots']:
        a=r['address']
        if a in records:SDK.check_ledger(records[a],functions[a],origins[a],args.evidence_only)
        elif functions[a]!=r['function'] or origins[a]!=r['origin']:raise ValueError('math table changes unrelated canonical evidence')
        if int(functions[a]['size'])!=r['size'] or digest(c.pe_bytes_at(target,int(a,16),r['size']))!=r['body_sha256']:raise ValueError('math table original full snapshot differs')
    for r in m['retained']:
        path=ROOT/r['file'];inventory=json.loads(path.read_text())[r['collection']] if path.suffix=='.json' else rows(path.name)
        if r['record'] not in inventory:raise ValueError('math table original entire runtime/interior/opaque source record differs')
    for r in m['anchors']:
        a=r['address'];raw=c.pe_bytes_at(target,int(a,16),r['size']);ws=witness(raw,a)
        if functions[a]!=r['function'] or origins[a]!=r['origin'] or authored[a]!=r['record'] or digest(raw)!=r['body_sha256'] or any(w not in ws for w in r['selected_witnesses']):
            raise ValueError('math table original entire independent game parent differs')
        for file,key in [('authored-origin-switches.csv','switches'),('authored-origin-direct-switches.csv','direct_switches')]:
            if [q for q in rows(file) if q['address']==a]!=r[key]:raise ValueError('math table original full parent switch evidence differs')
        if list(cfg.verify_body(raw,int(a,16),r['switches'],lambda a,n:c.pe_bytes_at(target,a,n),r['direct_switches']))!=r['cfg']:raise ValueError('math table original entire parent CFG differs')
    sections=module('math_table_sections','verify-compiler-origins.py').sections(target);verify_table_span(target,m['table_span'])
    for r in m['constants']:
        raw=c.pe_bytes_at(target,int(r['address'],16),r['size']);start=int(r['address'],16)
        if struct.unpack('<d' if r['size']==8 else '<f',raw)[0]!=r['value'] or not any(base<=start and start+r['size']<=base+size and flags&0x40000000 and not flags&0xA0000000 for base,size,flags in sections):
            raise ValueError('math table full original readonly constant differs')
    scratch=ROOT/'build/origin-math-table-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as dirname:
        path=Path(dirname)/'MathTablePolicies.obj';result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/m['probe']),str(path),*m['profile']],cwd=ROOT,capture_output=True,text=True)
        if result.returncode or included_headers(result.stdout+result.stderr)!=m['headers']:raise ValueError('math table cold source/actual includes differ')
        data=path.read_bytes()
        if SDK.PAIRED.BUFFER.inventory(data,c,coff)!=m['emission']:raise ValueError('math table complete ordinary emission differs')
        catalog={name:int(a,16) for name,a in EXTERNAL.items()}
        for r in m['controls']:
            for d in r['section']['definitions']:
                if d['storage'] in (2,3) and not d['symbol'].startswith('.'):
                    address=int(r['address'],16)+d['offset']
                    if d['symbol'] in catalog and catalog[d['symbol']]!=address:raise ValueError('math table overrides complete coherent definition')
                    catalog[d['symbol']]=address
        for r in m['controls']:
            for b in r['bindings']:
                if catalog.get(b['symbol'])!=int(b['target_address'],16):raise ValueError('math table loses independent real code/data field linkage')
            raw,linked=SDK.ENDPOINT.link(data,r,catalog,c);actual=c.pe_bytes_at(target,int(r['address'],16),r['size']);verify_control(r,raw,linked,actual)
            if r['kind']=='code':
                if extent.complete_aux_section_size(data,r['source_definition']['symbol'],c.coff_name)!=r['size'] or list(cfg.verify_body(linked,int(r['address'],16)))!=r['cfg']:
                    raise ValueError('math table source loses own primary extent or entire source CFG')
            else:
                whole,_=coff.readonly_section(data,r['section']['section'],c.coff_name)
                if whole!=raw:raise ValueError('math table slices readonly constant carrier')
        for r in m['policies']:
            h=struct.unpack_from('<8sIIIIIIHHI',data,20+(r['section']['section']-1)*40);raw=data[h[4]:h[4]+h[3]]
            if len(raw)!=r['size'] or digest(raw)!=r['source_sha256'] or witness(raw,'0x00000000')!=r['witnesses'] or list(cfg.verify_body(raw,0))!=r['cfg']:
                raise ValueError('math table full small-owner policy/caller differs')
            if extent.complete_aux_section_size(data,r['source_definition']['symbol'],c.coff_name)!=r['size']:raise ValueError('math table small policy loses full own primary AUX')
        raw,_=coff.readonly_section(data,m['layout']['section'],c.coff_name)
        if list(struct.unpack('<4I',raw))!=LAYOUT:raise ValueError('math table full readonly source layout differs')
    print('R182 origins OK: five whole authored table/counter policies /326 bytes; three whole math positives /174 bytes,full73-byte ratio negative with six live store/cleanup order differences;10 full code/constant controls /283 bytes,19 genuine unmasked fields;whole67-byte small-counter and17-byte caller controls without target/layout credit;13 cold ordinary sections /383 bytes,two SDK headers,16-byte layout;179 snapshots,41 protected unknowns,47362 bytes of entire game parents and four original runtime/opaque records preserved;14400-byte table claim is used writable range only;no source/ABI/mapping/exact credit, exact stays60.')
    return 0

if __name__=='__main__':
    try:raise SystemExit(main())
    except (OSError,KeyError,IndexError,StopIteration,ValueError,struct.error,json.JSONDecodeError) as error:
        print('error: '+str(error),file=sys.stderr);raise SystemExit(1)
