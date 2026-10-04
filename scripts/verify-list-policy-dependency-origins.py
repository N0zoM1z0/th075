#!/usr/bin/env python3
"""Cold-replay complete list dependencies, actual node allocation and catch tails."""
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

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('list_parent', ROOT/'scripts/verify-game-parent-policy-origins.py')
PRIOR = importlib.util.module_from_spec(spec); spec.loader.exec_module(PRIOR)
SDK = PRIOR.SDK; module = SDK.module; digest = SDK.digest
EVIDENCE = 'config/list-policy-dependency-origin-evidence.json'
MANIFEST_SHA256 = '86ca07a2553872893e906a10b1f93da6fbd45da103d94a191aee610c1b32b9f0'
KEYS = {'0x004110F0':22, '0x00411C30':56, '0x00411C70':19, '0x00411D60':153,
        '0x00411FE0':223, '0x004120C0':100, '0x00412130':53, '0x00412170':14,
        '0x004121A0':25, '0x004123E0':27, '0x00412420':25, '0x004125A0':23}
ADDRESSES = ['0x00410F30','0x00655010','0x00411C30','0x004110F0','0x00411C70','0x00668170',
 '0x00412170','0x00412130','0x00411FE0','0x00411D60','0x004120C0','0x004123D0','0x00412390',
 '0x00655030','0x004123E0','0x00411E80','0x00412400','0x00411E90','0x00412420','0x00412180',
 '0x004121A0','0x004124F0','0x00412590','0x00668194','0x004125A0','0x004125C0','0x00412600',
 '0x00412580','0x00412610','0x004063D0','0x00411C70']
SIZES = [104,21,56,22,19,36,14,53,223,153,100,16,53,10,27,8,29,11,25,25,25,28,16,80,23,58,5,5,16,8,19]
LAYOUT = PRIOR.LAYOUT + [164,20,12,1,16]
PROTECTED = {'0x00411E80':8,'0x00411E90':11,'0x00412580':5,'0x00412600':5,'0x0041206F':80,
 '0x004229C0':15,'0x0042E580':5,'0x004212A0':72,'0x004591E0':417,'0x0045AAE0':368,
 '0x0040D8E0':19,'0x004229D0':28,'0x0040F9F0':15,'0x0040E000':158,'0x005F84B0':167,
 '0x00641FB8':11,'0x00641DAA':11,'0x00458650':31,'0x00458670':23,'0x0045B880':149}
EXTERNAL = {'__except_list':0, '___CxxFrameHandler':0x6407B8, '__CxxThrowException@8':0x640C12,
            '??3@YAXPAX@Z':0x640F15, '??2@YAPAXI@Z':0x64159D,
            '?tidy@OrdinaryTidyObservation@@QAEXXZ':0x4120C0}


def manifest(): return json.loads((ROOT/EVIDENCE).read_text())


def included_headers(output):
    found = {}
    for line in output.splitlines():
        if 'Note: including file:' not in line: continue
        text = line.split('Note: including file:',1)[1].strip().replace('\\','/')
        if text[:3].lower() != 'z:/': raise ValueError('list include loses its actual host mapping')
        path = Path(text[2:]); relative = str(path.relative_to(ROOT))
        if relative != 'probes/VC7GameContextPolicies.cpp' and not relative.startswith('.tools/msvc710/Vc7/include/'):
            raise ValueError('list probe gains an unreviewed include owner')
        found[relative] = digest(path.read_bytes())
    return found


def verify_plan(m):
    if (m['evidence_id']!='R167' or m['target_sha256']!=SDK.manifest()['target_sha256']
            or m['probe']!='probes/VC7ListPolicyDependencies.cpp' or m['profile']!=SDK.PROFILE
            or len(m['headers'])!=30 or {r['address']:r['size'] for r in m['functions']}!=KEYS
            or len(m['functions'])!=12 or [r['address'] for r in m['controls']]!=ADDRESSES
            or [r['size'] for r in m['controls']]!=SIZES or sum(len(r['bindings']) for r in m['controls'])!=62
            or len(m['emission'])!=182 or sum(r['size'] for r in m['emission'])!=8150
            or len(m['snapshots'])!=103 or len(m['retained'])!=13
            or m['layout'] not in m['emission'] or m['layout']['size']!=56 or m['layout_values']!=LAYOUT):
        raise ValueError('list policy loses complete bounded source, emission, fields, context or layout')
    mutable = {'proposed_name','module','status','owner','evidence','notes'}
    records = {r['address']:r for r in m['functions']}
    for r in m['functions']:
        a = r['address']; old,new = r['original_function'],r['accepted_function']
        owner = 'authored' if a=='0x004110F0' else 'library'; subsystem = 'GameContextPolicy' if owner=='authored' else 'VC7STL'
        allowed = mutable | ({'size','span_end'} if a=='0x00411FE0' else set())
        confidence = ('complete-custom-list-wrapper-with-whole-parent-and-sdk-graph' if owner=='authored'
                      else 'complete-vc7-list-dependency-with-whole-parent-source-eh-graph')
        if (r['decision']!=owner or r['original_origin']['origin']!='unknown' or old['address']!=a
                or int(old['size'])!=(143 if a=='0x00411FE0' else r['size'])
                or {k:v for k,v in old.items() if k not in allowed}!={k:v for k,v in new.items() if k not in allowed}
                or new['size']!=str(r['size']) or new['span_end']!=f'0x{int(a,16)+r["size"]-1:08X}'
                or new['module']!=subsystem or new['owner']!=owner or new['status']!=('unclassified' if owner=='authored' else 'excluded')
                or new['source_file'] or new['calling_convention'] or new['signature'] or new['match_percent']!='0.00'
                or r['accepted_origin']!=dict(address=a,origin=owner,subsystem=subsystem,
                    disposition='authored' if owner=='authored' else 'exclude',confidence=confidence,evidence_id='R167')):
            raise ValueError('list policy changes unrelated extent or grants false source/private ABI/mapping/exact credit')
        control = next(x for x in m['controls'] if x['address']==a)
        if (r['symbol']!=control['source_definition']['symbol'] or r['cfg']!=control['cfg']
                or r['body_sha256']!=control['body_sha256'] or not r['witnesses']):
            raise ValueError('list policy loses its own whole defining source/CFG/target')
        if owner=='authored' and r['accepted_authored_record']!=dict(address=a,size='22',body_sha256=r['body_sha256'],
                inferred_role=new['proposed_name'],return_count='1',internal_branch_count='0',external_branch_count='0',evidence_id='R167'):
            raise ValueError('list custom wrapper loses its complete authored extent')
    for i,r in enumerate(m['controls']):
        ss,d = r['section'],r['source_definition']
        if (ss not in m['emission'] or d not in ss['definitions'] or ss['size']!=r['size']
                or ss['source_sha256']!=r['source_sha256'] or len(ss['fields'])!=len(r['bindings'])
                or r['role']!=('byte-equal-ordinary-destructor-alternative' if i==30 else 'closed-whole-source-context')):
            raise ValueError('list policy truncates full source or substitutes an independent source owner')
        if r['kind']=='code' and (d['offset'] or d['storage']!=2 or d['type']!=32):
            raise ValueError('list policy regular function loses its own complete definition')
        if r['kind']!='code' and (i,r['kind'],d['offset']) not in [(1,'eh-code',11),(5,'state-data',8),(13,'eh-code',0),(23,'state-data',52)]:
            raise ValueError('list policy slices EH/code/try-state data')
        for field,b in zip(ss['fields'],r['bindings']):
            if (b!=dict(offset=field['offset'],type=field['type'],symbol=field['symbol']['symbol'],addend=field['addend'],target_address=b['target_address'])
                    or field['type'] not in ('REL32','DIR32') or field['offset']+4>r['size']):
                raise ValueError('list policy masks or substitutes a genuine source field')
    buy = m['controls'][8]; catch = [d for d in buy['section']['definitions'] if d['type']==32 and d['storage']==3]
    if len(catch)!=1 or catch[0]['offset']!=143 or not catch[0]['symbol'].startswith('$L'):
        raise ValueError('list node loses complete local catch and shared-tail ownership')
    if [(b['offset'],b['target_address']) for b in m['controls'][23]['bindings']]!=[(28,'0x0041206F'),(48,'0x006681A4'),(60,'0x00668194'),(68,'0x006681B4')]:
        raise ValueError('list node changes actual entire catch/try/unwind linkage')
    if m['controls'][30]['source_definition']['symbol']!='??1OrdinaryTidyObservation@@QAE@XZ':
        raise ValueError('list destructor loses distinct entire ordinary alternative')
    negatives = m['negatives']
    if [(r['address'],r['size'],r['target_size'],r['role']) for r in negatives]!=[
            ('0x004110F0',22,22,'whole-implicit-destruction-negative'),('0x004125A0',20,23,'whole-unsigned-node-allocation-negative')]:
        raise ValueError('list policy replaces entire lifetime/allocation negatives with prefixes')
    for i,r in enumerate(negatives):
        ss,d = r['section'],r['source_definition']; expected = '0x00411C70' if i==0 else '0x0064159D'
        if (ss not in m['emission'] or ss['size']!=r['size'] or d not in ss['definitions']
                or d['offset'] or d['type']!=32 or d['storage']!=2 or ss['source_sha256']!=r['source_sha256']
                or len(ss['fields'])!=1 or len(r['bindings'])!=1 or r['bindings'][0]['target_address']!=expected):
            raise ValueError('list negative loses full defining source or actual child')
        b,field = r['bindings'][0],ss['fields'][0]
        if b!=dict(offset=field['offset'],type=field['type'],symbol=field['symbol']['symbol'],addend=field['addend'],target_address=expected):
            raise ValueError('list negative substitutes its actual field')
        if i==0: PRIOR.verify_implicit_extent(r)
        elif not d['symbol'].startswith('??$_Allocate@U_Node@?$_List_nod@I'):
            raise ValueError('list node negative loses entire unsigned allocation source')
    snapshots = {r['address']:r for r in m['snapshots']}
    for a,size in PROTECTED.items():
        r = snapshots.get(a)
        if not r or r['size']!=size or r['origin']['origin']!='unknown':
            raise ValueError('list policy resolves an independent opaque pointer/catch/destruction/lifetime/copy/math owner')
    parent = m['parent']; anchor = m['anchor']
    if (parent['address']!='0x00410F30' or parent['size']!=104 or parent['origin']['origin']!='authored'
            or parent['origin']['evidence_id']!='R166' or anchor!=PRIOR.manifest()['anchors'][0]
            or [r['handler_address'] for r in m['retained_frames']]!=['0x0065501B','0x00655030']):
        raise ValueError('list policy loses independent whole parent, game anchor or registered frame')
    defs = sorted([(d['symbol'],d['offset']) for d in m['layout']['definitions'] if d['storage']==2],key=lambda d:d[1])
    if defs!=[('_GameContextLayout',0),('_ListDependencyLayout',36)]:
        raise ValueError('list layout slices either complete observer array')


def accepted_snapshot(snapshot,function,origin):
    if digest((ROOT/EVIDENCE).read_bytes())!=MANIFEST_SHA256: raise ValueError('list immutable manifest differs')
    m = manifest(); verify_plan(m); r = next((r for r in m['functions'] if r['address']==function['address']),None)
    return bool(r and snapshot==dict(function=r['original_function'],origin=r['original_origin'])
                and function==r['accepted_function'] and origin==r['accepted_origin'])


def verify_negative(raw,linked,actual,row):
    if (len(raw)!=row['size'] or len(linked)!=row['size'] or len(actual)!=row['target_size']
            or digest(raw)!=row['source_sha256'] or digest(actual)!=row['body_sha256'] or linked==actual):
        raise ValueError('list negative compares a prefix or grants positive source credit')
    if row['role']=='whole-implicit-destruction-negative' and [i for i,(a,b) in enumerate(zip(linked,actual)) if a!=b]!=[14,15]:
        raise ValueError('list implicit destructor loses its exact complete real-callee difference')


def main():
    parser = argparse.ArgumentParser(description=__doc__); parser.add_argument('--evidence-only',action='store_true')
    args = parser.parse_args(); m = manifest(); verify_plan(m)
    for path,expected in [(EVIDENCE,MANIFEST_SHA256),(m['probe'],m['probe_sha256']),*m['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes())!=expected: raise ValueError('list immutable source/prior evidence differs: '+path)
    c = module('list_target','compare-coff-function.py'); coff = module('list_coff','coff_data.py')
    cfg = module('list_cfg','verify-authored-origins.py'); extent = module('list_extent','verify-vendor-record-origins.py')
    eh = module('list_eh','compiler_eh.py'); target = c.verified_target(); rows = cfg.rows
    if digest(target)!=m['target_sha256']: raise ValueError('list target identity differs')
    functions = {r['address']:r for r in rows('functions.csv')}; origins = {r['address']:r for r in rows('function-origins.csv')}
    authored = {r['address']:r for r in rows('authored-origin-evidence.csv')}; records = {r['address']:r for r in m['functions']}
    if {a for a,r in authored.items() if r['evidence_id']=='R167'}!=(set() if args.evidence_only else {'0x004110F0'}):
        raise ValueError('list authored evidence registry differs')
    decoder = Cs(CS_ARCH_X86,CS_MODE_32)
    for r in m['functions']:
        a = r['address']; SDK.check_ledger(r,functions[a],origins[a],args.evidence_only)
        body = c.pe_bytes_at(target,int(a,16),r['size'])
        if (digest(body)!=r['body_sha256'] or list(cfg.verify_body(body,int(a,16)))!=r['cfg']
                or [dict(site=f'0x{x.address:08X}',mnemonic=x.mnemonic,operands=x.op_str) for x in decoder.disasm(body,int(a,16))]!=r['witnesses']):
            raise ValueError('list entire accepted extent/CFG/witnesses differ')
        if not args.evidence_only and r['decision']=='authored' and authored[a]!=r['accepted_authored_record']:
            raise ValueError('list canonical authored record differs')
    for r in m['snapshots']:
        a = r['address']
        if a in records: SDK.check_ledger(records[a],functions[a],origins[a],args.evidence_only)
        elif functions[a]!=r['function'] or origins[a]!=r['origin']: raise ValueError('list alters unrelated canonical evidence')
        if digest(c.pe_bytes_at(target,int(a,16),r['size']))!=r['body_sha256']:
            raise ValueError('list original boundary snapshot differs')
    for r in m['retained']:
        path = ROOT/r['file']; inventory = json.loads(path.read_text())[r.get('collection','functions')] if path.suffix=='.json' else rows(path.name)
        if r['record'] not in inventory: raise ValueError('list original independent source record differs')
    for r in [m['parent'],m['anchor']]:
        a = r['address']; body = c.pe_bytes_at(target,int(a,16),r['size'])
        if functions[a]!=r['function'] or origins[a]!=r['origin']: raise ValueError('list changes whole independent authored parent')
        if a==m['parent']['address']:
            if digest(body)!=r['body_sha256'] or list(cfg.verify_body(body,int(a,16)))!=r['cfg']: raise ValueError('list full parent CFG differs')
            if [dict(site=f'0x{x.address:08X}',mnemonic=x.mnemonic,operands=x.op_str) for x in decoder.disasm(body,int(a,16))]!=r['witnesses']:
                raise ValueError('list full actual parent instructions differ')
        else:
            if authored[a]!=r['record'] or digest(body)!=r['record']['body_sha256']: raise ValueError('list full original game anchor differs')
            cfg.verify_body(body,int(a,16),r['switches'],lambda a,n:c.pe_bytes_at(target,a,n),r['direct_switches'])
            for filename,key in [('authored-origin-switches.csv','switches'),('authored-origin-direct-switches.csv','direct_switches')]:
                if [x for x in rows(filename) if x['address']==a]!=r[key]: raise ValueError('list original switch evidence differs')
            window = c.pe_bytes_at(target,int(r['window_start'],16),r['window_size'])
            if digest(window)!=r['window_sha256'] or not any(f'0x{x.address:08X}'==r['call_site'] and x.mnemonic=='call' and x.op_str==hex(int(r['child'],16)) for x in decoder.disasm(window,int(r['window_start'],16))):
                raise ValueError('list loses independent real parent call context')
    for frame in m['retained_frames']:
        if frame not in rows('compiler-eh-frames.csv'): raise ValueError('list original frame registration differs')
        eh.verify_frame(frame,lambda a,n:c.pe_bytes_at(target,a,n),lambda a,n:c.pe_bytes_at(target,a,n),{int(a,16) for a in functions},set())
    scratch = ROOT/'build/origin-list-policy-verification'; scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as dirname:
        path = Path(dirname)/'ListDependencies.obj'
        result = subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/m['probe']),str(path),*m['profile']],cwd=ROOT,capture_output=True,text=True)
        if result.returncode or included_headers(result.stdout+result.stderr)!=m['headers']:
            raise ValueError('list cold source or actual include provenance differs')
        data = path.read_bytes()
        if SDK.PAIRED.BUFFER.inventory(data,c,coff)!=m['emission']: raise ValueError('list entire ordinary emission differs')
        catalog = {}
        def add(name,address):
            if name in catalog and catalog[name]!=address: raise ValueError('list overrides a coherent complete defining source owner')
            catalog[name] = address
        for r in m['controls']:
            for d in r['section']['definitions']:
                if d['storage'] in (2,3) and not d['symbol'].startswith('.'): add(d['symbol'],int(r['address'],16)+d['offset'])
        for r in m['controls']:
            for b in r['bindings']:
                name,a = b['symbol'],int(b['target_address'],16)
                if name not in catalog and EXTERNAL.get(name)!=a: raise ValueError('list external field lacks complete runtime/ordinary context')
                add(name,a)
            raw,linked = SDK.ENDPOINT.link(data,r,catalog,c); actual = c.pe_bytes_at(target,int(r['address'],16),r['size'])
            if len(raw)!=r['size'] or linked!=actual or digest(raw)!=r['source_sha256'] or digest(actual)!=r['body_sha256']:
                raise ValueError('list entire unmasked comparison differs: '+r['address'])
            if r['kind']=='code':
                if extent.complete_aux_section_size(data,r['source_definition']['symbol'],c.coff_name)!=r['size'] or list(cfg.verify_body(actual,int(r['address'],16)))!=r['cfg']:
                    raise ValueError('list loses full positive primary AUX/CFG extent')
            elif r['kind']=='eh-code':
                ins = list(decoder.disasm(actual,int(r['address'],16)))
                if sum(x.size for x in ins)!=r['size'] or ins[-1].mnemonic!='jmp' or ins[-1].op_str!='0x6407b8':
                    raise ValueError('list slices whole EH handler/cleanup tail')
        for r in m['negatives']:
            for b in r['bindings']: add(b['symbol'],int(b['target_address'],16))
            raw,linked = SDK.ENDPOINT.link(data,r,catalog,c); actual = c.pe_bytes_at(target,int(r['address'],16),r['target_size'])
            verify_negative(raw,linked,actual,r); cfg.verify_body(linked,int(r['address'],16))
            if r['role']=='whole-implicit-destruction-negative': PRIOR.verify_implicit_extent(r,data,c.coff_name)
            elif extent.complete_aux_section_size(data,r['source_definition']['symbol'],c.coff_name)!=r['size']:
                raise ValueError('list unsigned negative loses its entire own AUX extent')
        raw,_ = coff.readonly_section(data,m['layout']['section'],c.coff_name)
        if list(struct.unpack('<14I',raw))!=LAYOUT: raise ValueError('list complete combined observer layout differs')
    print('R167 origins OK: one custom wrapper / 22 bytes and eleven SDK dependencies / 718 bytes; complete 223-byte node allocation includes catch/shared tail; unchanged whole R166 104-byte policy and R045 1186-byte game anchor; 31 full positive controls / 1288 bytes and 62 real unmasked fields; two whole negative controls / 42 bytes; all 182 cold ordinary sections / 8150 bytes, 29 SDK headers plus original pinned probe include, both registered frames and entire 56-byte layout; observed node allocation is 172 bytes, original payload identity unknown; getters, empty destruction children and interior catch remain unknown; no source/private ABI/mapping/exact credit.')
    return 0


if __name__=='__main__':
    try: raise SystemExit(main())
    except (OSError,KeyError,IndexError,StopIteration,ValueError,struct.error,json.JSONDecodeError) as error:
        print('error: '+str(error),file=sys.stderr); raise SystemExit(1)
