#!/usr/bin/env python3
"""Replay explicit lifetime operations while preserving interface-owner ambiguity."""
from __future__ import annotations
import argparse
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('remaining_lifetime_prior',ROOT/'scripts/verify-static-resource-policy-origins.py')
PRIOR=importlib.util.module_from_spec(spec);spec.loader.exec_module(PRIOR)
SDK=PRIOR.SDK;module=PRIOR.module;digest=PRIOR.digest
EVIDENCE='config/remaining-lifetime-policy-origin-evidence.json'
MANIFEST_SHA256='05d51c763ba642659a651a3c3a8dfbaba3cb9a87d15b682265d12df0d225a1f9'
KEYS={'0x005F6F60':142,'0x0041BFD0':129}
LAYOUT=[20,1,16,60,60,20,20,4,4,4,4,4]
POLICIES=[('explicit-construction',142,'??0ExplicitLifetimeConstruction@@QAE@XZ',False),('implicit-construction',108,'??0ImplicitLifetimeConstruction@@QAE@XZ',True),('explicit-raster-release',129,'??1ExplicitLifetimeRaster@@QAE@XZ',False),('implicit-raster-observation',5,'?ObserveImplicitLifetimeRaster@@YAXPAUImplicitLifetimeRaster@@@Z',False),('explicit-interface-release',27,'??1ExplicitLifetimeInterface@@QAE@XZ',False),('implicit-interface-destruction',19,'??1ImplicitLifetimeInterface@@QAE@XZ',True),('ordinary-interface-release',27,'??1OrdinaryLifetimeSmartOwner@@QAE@XZ',False)]
IMPORTS=[dict(address=a,dll=d,name=n) for a,d,n in [('0x00657048','GDI32.dll','SelectObject'),('0x0065704C','GDI32.dll','DeleteObject'),('0x00657214','USER32.dll','ReleaseDC')]]
NEGATIVE_BINDINGS={'??3@YAXPAX@Z':'0x00640F15','__imp__SelectLifetimeObject@8':'0x00657048','__imp__DeleteLifetimeObject@4':'0x0065704C','__imp__ReleaseLifetimeDC@8':'0x00657214'}

def manifest():return json.loads((ROOT/EVIDENCE).read_text())

def verify_plan(m):
    if (m['evidence_id']!='R178' or m['target_sha256']!=PRIOR.manifest()['target_sha256']
            or m['probe']!='probes/VC7RemainingLifetimePolicies.cpp' or m['profile']!=SDK.PROFILE
            or {r['address']:r['size'] for r in m['functions']}!=KEYS or len(m['functions'])!=2
            or len(m['policies'])!=7 or sum(r['size'] for r in m['policies'])!=457
            or len(m['emission'])!=119 or sum(r['size'] for r in m['emission'])!=5446 or len(m['headers'])!=28
            or len(m['snapshots'])!=133 or len({r['address'] for r in m['snapshots']})!=133
            or len(m['anchors'])!=3 or sum(r['size'] for r in m['anchors'])!=531
            or len(m['retained'])!=5 or m['layout'] not in m['emission'] or m['layout']['size']!=48
            or m['layout_values']!=LAYOUT or m['import_slots']!=IMPORTS
            or m['protected']!=dict(PRIOR.PROTECTED,**{'0x004170B0':27}) or m['frame']['handler_address']!='0x00656629'):
        raise ValueError('remaining lifetime loses bounded whole policy/source/context scope')
    mutable={'proposed_name','module','status','owner','evidence','notes'}
    for r in m['functions']:
        a=r['address'];old,new=r['original_function'],r['accepted_function'];owner='StaticResourcePolicy' if a=='0x005F6F60' else 'RasterResources'
        if (r['decision']!='authored' or r['original_origin']['origin']!='unknown' or old['address']!=a or int(old['size'])!=r['size']
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['module']!=owner or new['owner']!='authored' or new['status']!='unclassified'
                or new['source_file'] or new['calling_convention'] or new['signature'] or new['match_percent']!='0.00' or 'symbol' in r
                or r['accepted_origin']!=dict(address=a,origin='authored',subsystem=owner,disposition='authored',confidence='complete-explicit-lifetime-policy-and-whole-source-operation-controls',evidence_id='R178')
                or r['accepted_authored_record']!=dict(address=a,size=str(r['size']),body_sha256=r['body_sha256'],inferred_role=new['proposed_name'],return_count=str(r['cfg'][0]),internal_branch_count=str(r['cfg'][1]),external_branch_count='0',evidence_id='R178')):
            raise ValueError('remaining lifetime loses independent ownership or adds false source/private ABI/exact credit')
    records={r['address']:r for r in m['functions']}
    calls=[r['operands'] for r in records['0x005F6F60']['witnesses'] if r['mnemonic']=='call']
    if calls!=['0x641c78','0x40ad80','0x5f82f0','0x5f82d0','0x5f82d0','0x5f83e0']:
        raise ValueError('remaining lifetime loses construction-before-explicit-clear order')
    calls=[r['operands'] for r in records['0x0041BFD0']['witnesses'] if r['mnemonic']=='call']
    if calls!=['0x640f15','dword ptr [0x657048]','dword ptr [0x65704c]','dword ptr [0x657214]']:
        raise ValueError('remaining lifetime loses explicit storage/GDI/DC release order')
    required={'0x005F6F60':[('0x005F6F86','push','2'),('0x005F6F88','push','0x14'),('0x005F6FAC','add','ecx, 0x78'),('0x005F6FC3','add','ecx, 0x14'),('0x005F6FCE','add','ecx, 0x78')],
              '0x0041BFD0':[('0x0041BFDC','cmp','dword ptr [eax + 0x14], 0'),('0x0041BFE0','je','0x41c001'),('0x0041BFFA','mov','dword ptr [ecx + 0x14], 0'),('0x0041C032','mov','dword ptr [ecx + 8], 0'),('0x0041C03C','mov','dword ptr [edx + 0xc], 0'),('0x0041C046','mov','dword ptr [eax + 4], 0')]}
    for a,expected in required.items():
        if not set(expected)<={(r['site'],r['mnemonic'],r['operands']) for r in records[a]['witnesses']}:
            raise ValueError('remaining lifetime loses actual explicit guard/clear/reset operation')
    for r,(role,size,symbol,implicit) in zip(m['policies'],POLICIES):
        if (r['role'],r['size'],r['source_definition']['symbol'],r['implicit'])!=(role,size,symbol,implicit) or r['section'] not in m['emission']:
            raise ValueError('remaining lifetime loses full own source-operation control')
        fields=r['section']['fields']
        if r['call_symbols']!=[q['symbol']['symbol'] for q in fields if q['type']=='REL32']:
            raise ValueError('remaining lifetime source order differs from genuine fields')
        if r['ambiguous_target']!=('0x004170B0' if role in ('explicit-interface-release','ordinary-interface-release') else None):
            raise ValueError('remaining lifetime promotes source observation to target byte credit')
    p=m['policies'];deque='?clear@?$deque@ULifetimeValueObservation@@V?$allocator@ULifetimeValueObservation@@@std@@@std@@QAEXXZ';vector='?clear@?$vector@PAULifetimeValueObservation@@V?$allocator@PAULifetimeValueObservation@@@std@@@std@@QAEXXZ'
    if p[0]['call_symbols']!=p[1]['call_symbols']+[deque,deque,vector] or len(p[1]['call_symbols'])!=3 or p[2]['call_symbols']!=['??3@YAXPAX@Z'] or p[3]['section']['fields']:
        raise ValueError('remaining lifetime loses explicit versus automatic source operations')
    negative=m['negative'];fields=negative['section']['fields']
    if (negative['address']!='0x0041BFD0' or negative['size']!=129 or negative['section']!=p[2]['section']
            or negative['source_definition']!=p[2]['source_definition'] or negative['differences']!=[14,23,44]
            or len(fields)!=4 or len(negative['bindings'])!=4
            or [{k:b[k] for k in ('offset','type','symbol','addend')} for b in negative['bindings']]!=[dict(offset=q['offset'],type=q['type'],symbol=q['symbol']['symbol'],addend=q['addend']) for q in fields]
            or {b['symbol']:b['target_address'] for b in negative['bindings']}!=NEGATIVE_BINDINGS):
        raise ValueError('remaining lifetime masks a whole negative or changes actual field binding')
    pending=m['pending']
    if pending['address']!='0x004170B0' or pending['size']!=27 or pending['origin']['origin']!='unknown' or pending['function']['owner'] or 'accepted_origin' in pending:
        raise ValueError('remaining lifetime resolves indistinguishable interface ownership')
    snapshots={r['address']:r for r in m['snapshots']}
    for a,size in m['protected'].items():
        if snapshots[a]['size']!=size or snapshots[a]['origin']['origin']!='unknown':raise ValueError('remaining lifetime changes protected opaque ownership')
    for a in ('0x00413620','0x0041A140'):
        if snapshots[a]['origin']['origin']!='compiler':raise ValueError('remaining lifetime grants game ownership from deleting parents')

def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args();m=manifest();verify_plan(m)
    for path,expected in [(EVIDENCE,MANIFEST_SHA256),(m['probe'],m['probe_sha256']),*m['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes())!=expected:raise ValueError('remaining lifetime immutable source/evidence differs: '+path)
    c=module('remaining_target','compare-coff-function.py');coff=module('remaining_coff','coff_data.py');cfg=module('remaining_cfg','verify-authored-origins.py');extent=module('remaining_extent','verify-vendor-record-origins.py');target=c.verified_target();rows=cfg.rows
    functions={r['address']:r for r in rows('functions.csv')};origins={r['address']:r for r in rows('function-origins.csv')};authored={r['address']:r for r in rows('authored-origin-evidence.csv')};records={r['address']:r for r in m['functions']};decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    def witness(raw,a):return [dict(site=f'0x{x.address:08X}',mnemonic=x.mnemonic,operands=x.op_str) for x in decoder.disasm(raw,int(a,16))]
    if digest(target)!=m['target_sha256'] or {a for a,r in authored.items() if r['evidence_id']=='R178'}!=(set() if args.evidence_only else set(KEYS)):
        raise ValueError('remaining lifetime target/authored registry differs')
    for r in m['functions']:
        a=r['address'];SDK.check_ledger(r,functions[a],origins[a],args.evidence_only)
        if not args.evidence_only and authored[a]!=r['accepted_authored_record']:raise ValueError('remaining lifetime accepted authored record differs')
    for r in m['snapshots']:
        a=r['address']
        if a in records:SDK.check_ledger(records[a],functions[a],origins[a],args.evidence_only)
        elif functions[a]!=r['function'] or origins[a]!=r['origin']:raise ValueError('remaining lifetime changes unrelated canonical context')
        if int(functions[a]['size'])!=r['size'] or digest(c.pe_bytes_at(target,int(a,16),r['size']))!=r['body_sha256']:raise ValueError('remaining lifetime full target snapshot differs')
    for r in [*m['functions'],m['pending'],*m['anchors']]:
        a=r['address'];raw=c.pe_bytes_at(target,int(a,16),r['size'])
        if digest(raw)!=r['body_sha256'] or witness(raw,a)!=r['witnesses'] or list(cfg.verify_body(raw,int(a,16)))!=r['cfg']:
            raise ValueError('remaining lifetime entire policy/context/CFG differs')
        if any(int(a,16)<int(q,16)<int(a,16)+r['size'] for q in functions):raise ValueError('remaining lifetime enters another function extent')
        if 'record' in r:
            if authored[a]!=r['record'] or functions[a]!=r['function'] or origins[a]!=r['origin']:raise ValueError('remaining lifetime whole authored anchor differs')
            for file,key in [('authored-origin-switches.csv','switches'),('authored-origin-direct-switches.csv','direct_switches')]:
                if [q for q in rows(file) if q['address']==a]!=r[key]:raise ValueError('remaining lifetime original anchor switch evidence differs')
    for r in m['retained']:
        path=ROOT/r['file'];inventory=json.loads(path.read_text())[r['collection']] if path.suffix=='.json' else rows(path.name)
        if r['record'] not in inventory:raise ValueError('remaining lifetime original full compiler/policy record differs')
    if m['frame'] not in rows('compiler-eh-frames.csv'):raise ValueError('remaining lifetime original complete EH frame differs')
    module('remaining_eh','compiler_eh.py').verify_frame(m['frame'],lambda a,n:c.pe_bytes_at(target,a,n),lambda a,n:c.pe_bytes_at(target,a,n),{int(a,16) for a in functions})
    imports=module('remaining_imports','verify-import-origins.py').pe_imports(target,c)
    for r in IMPORTS:
        if imports[int(r['address'],16)]!=(r['dll'],r['name']):raise ValueError('remaining lifetime actual PE import differs')
    scratch=ROOT/'build/origin-remaining-lifetime-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as dirname:
        path=Path(dirname)/'RemainingLifetimePolicies.obj';result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/m['probe']),str(path),*m['profile']],cwd=ROOT,capture_output=True,text=True)
        if result.returncode or PRIOR.included_headers(result.stdout+result.stderr)!=m['headers']:raise ValueError('remaining lifetime cold source/actual include ownership differs')
        data=path.read_bytes()
        if SDK.PAIRED.BUFFER.inventory(data,c,coff)!=m['emission']:raise ValueError('remaining lifetime complete ordinary emission differs')
        for r in m['policies']:
            head=struct.unpack_from('<8sIIIIIIHHI',data,20+(r['section']['section']-1)*40);raw=data[head[4]:head[4]+head[3]]
            if len(raw)!=r['size'] or digest(raw)!=r['source_sha256'] or witness(raw,'0x00000000')!=r['witnesses'] or list(cfg.verify_body(raw,0))!=r['cfg']:raise ValueError('remaining lifetime whole source operation differs')
            if r['implicit']:module('remaining_generated','verify-game-parent-policy-origins.py').verify_implicit_extent(r,data,c.coff_name)
            elif extent.complete_aux_section_size(data,r['source_definition']['symbol'],c.coff_name)!=r['size']:raise ValueError('remaining lifetime loses own complete primary AUX')
            if r['ambiguous_target']:
                if r['section']['fields'] or raw!=c.pe_bytes_at(target,0x4170B0,27):raise ValueError('remaining lifetime loses full byte-equal owner ambiguity')
        negative=m['negative'];raw,linked=SDK.ENDPOINT.link(data,negative,{k:int(a,16) for k,a in NEGATIVE_BINDINGS.items()},c);actual=c.pe_bytes_at(target,0x41BFD0,129)
        if len(linked)!=129 or [i for i,(a,b) in enumerate(zip(linked,actual)) if a!=b]!=negative['differences'] or digest(raw)!=negative['source_sha256'] or digest(actual)!=negative['body_sha256']:raise ValueError('remaining lifetime whole unmasked layout negative differs')
        raw,_=coff.readonly_section(data,m['layout']['section'],c.coff_name)
        if list(struct.unpack('<12I',raw))!=LAYOUT:raise ValueError('remaining lifetime full readonly source layout differs')
    print('R178 origins OK: two whole explicit policies /271 bytes; seven full source-operation controls /457 bytes; two whole byte-equal interface alternatives /54 bytes preserve unknown ownership; whole129-byte raster negative retains four genuine unmasked fields and three actual layout differences;119 ordinary sections /5446 bytes,28 SDK headers and48-byte layout;133 full snapshots,40 protected unknowns,531 bytes of authored anchors,five retained records and complete EH frame; no source/private ABI/mapping/exact credit, exact stays60.')
    return 0

if __name__=='__main__':
    try:raise SystemExit(main())
    except (OSError,KeyError,IndexError,StopIteration,ValueError,struct.error,json.JSONDecodeError) as error:
        print('error: '+str(error),file=sys.stderr);raise SystemExit(1)
