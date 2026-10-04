#!/usr/bin/env python3
"""Cold-replay entire deque retreat graphs and distinct real addition controls."""
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
spec=importlib.util.spec_from_file_location('deque_retreat_prior',ROOT/'scripts/verify-resource-release-policy-origins.py')
PRIOR=importlib.util.module_from_spec(spec);spec.loader.exec_module(PRIOR)
SDK=PRIOR.SDK;module=SDK.module;digest=SDK.digest
EVIDENCE='config/deque-retreat-origin-evidence.json'
MANIFEST_SHA256='52df1cfdeb68bb07a9b2e8b01503cff48522a028319c7eaa19f1f59713a17a30'
CONFIDENCE='complete-vc7-deque-retreat-and-whole-addition-subtraction-context'
KEYS={'0x0041F650': 27, '0x0041F6F0': 27, '0x00455D10': 27, '0x005F9530': 27}
LAYOUT=[1, 2, 4, 64, 8, 8, 8, 8, 8, 8, 8, 8]
EXTERNAL={}
PROTECTED=PRIOR.PROTECTED
ROUTES=[('0x0041F650', 27, 'candidate-whole-sdk-retreat', '??Ziterator@?$deque@U?$RetreatValueObservation@$00@@V?$allocator@U?$RetreatValueObservation@$00@@@std@@@std@@QAEAAV012@H@Z', ['0x0041F630']), ('0x0041F630', 31, 'retained-whole-sdk-advance', '??Yiterator@?$deque@U?$RetreatValueObservation@$00@@V?$allocator@U?$RetreatValueObservation@$00@@@std@@@std@@QAEAAV012@H@Z', []), ('0x0041ED00', 57, 'retained-whole-sdk-subtraction', '??Giterator@?$deque@U?$RetreatValueObservation@$00@@V?$allocator@U?$RetreatValueObservation@$00@@@std@@@std@@QBE?AV012@H@Z', ['0x0041F650']), ('0x0041F650', 27, 'byte-equal-ordinary-alternative', '?retreat@?$OrdinaryRetreatObservation@$00@@QAEAAViterator@?$deque@U?$RetreatValueObservation@$00@@V?$allocator@U?$RetreatValueObservation@$00@@@std@@@std@@H@Z', ['0x0041F630']), ('0x0041ECC0', 57, 'retained-whole-sdk-addition', '??Hiterator@?$deque@U?$RetreatValueObservation@$00@@V?$allocator@U?$RetreatValueObservation@$00@@@std@@@std@@QBE?AV012@H@Z', ['0x0041F630']), ('0x0041F6F0', 27, 'candidate-whole-sdk-retreat', '??Ziterator@?$deque@U?$RetreatValueObservation@$01@@V?$allocator@U?$RetreatValueObservation@$01@@@std@@@std@@QAEAAV012@H@Z', ['0x0041F6D0']), ('0x0041F6D0', 31, 'retained-whole-sdk-advance', '??Yiterator@?$deque@U?$RetreatValueObservation@$01@@V?$allocator@U?$RetreatValueObservation@$01@@@std@@@std@@QAEAAV012@H@Z', []), ('0x0041EE60', 57, 'retained-whole-sdk-subtraction', '??Giterator@?$deque@U?$RetreatValueObservation@$01@@V?$allocator@U?$RetreatValueObservation@$01@@@std@@@std@@QBE?AV012@H@Z', ['0x0041F6F0']), ('0x0041F6F0', 27, 'byte-equal-ordinary-alternative', '?retreat@?$OrdinaryRetreatObservation@$01@@QAEAAViterator@?$deque@U?$RetreatValueObservation@$01@@V?$allocator@U?$RetreatValueObservation@$01@@@std@@@std@@H@Z', ['0x0041F6D0']), ('0x0041EE20', 57, 'retained-whole-sdk-addition', '??Hiterator@?$deque@U?$RetreatValueObservation@$01@@V?$allocator@U?$RetreatValueObservation@$01@@@std@@@std@@QBE?AV012@H@Z', ['0x0041F6D0']), ('0x00455D10', 27, 'candidate-whole-sdk-retreat', '??Ziterator@?$deque@U?$RetreatValueObservation@$03@@V?$allocator@U?$RetreatValueObservation@$03@@@std@@@std@@QAEAAV012@H@Z', ['0x0042E2D0']), ('0x0042E2D0', 31, 'retained-whole-sdk-advance', '??Yiterator@?$deque@U?$RetreatValueObservation@$03@@V?$allocator@U?$RetreatValueObservation@$03@@@std@@@std@@QAEAAV012@H@Z', []), ('0x00455C60', 57, 'retained-whole-sdk-subtraction', '??Giterator@?$deque@U?$RetreatValueObservation@$03@@V?$allocator@U?$RetreatValueObservation@$03@@@std@@@std@@QBE?AV012@H@Z', ['0x00455D10']), ('0x00455D10', 27, 'byte-equal-ordinary-alternative', '?retreat@?$OrdinaryRetreatObservation@$03@@QAEAAViterator@?$deque@U?$RetreatValueObservation@$03@@V?$allocator@U?$RetreatValueObservation@$03@@@std@@@std@@H@Z', ['0x0042E2D0']), ('0x0042E040', 57, 'retained-whole-sdk-addition', '??Hiterator@?$deque@U?$RetreatValueObservation@$03@@V?$allocator@U?$RetreatValueObservation@$03@@@std@@@std@@QBE?AV012@H@Z', ['0x0042E2D0']), ('0x005F9530', 27, 'candidate-whole-sdk-retreat', '??Ziterator@?$deque@U?$RetreatValueObservation@$0EA@@@V?$allocator@U?$RetreatValueObservation@$0EA@@@@std@@@std@@QAEAAV012@H@Z', ['0x005F9510']), ('0x005F9510', 31, 'retained-whole-sdk-advance', '??Yiterator@?$deque@U?$RetreatValueObservation@$0EA@@@V?$allocator@U?$RetreatValueObservation@$0EA@@@@std@@@std@@QAEAAV012@H@Z', []), ('0x005F8D70', 57, 'retained-whole-sdk-subtraction', '??Giterator@?$deque@U?$RetreatValueObservation@$0EA@@@V?$allocator@U?$RetreatValueObservation@$0EA@@@@std@@@std@@QBE?AV012@H@Z', ['0x005F9530']), ('0x005F9530', 27, 'byte-equal-ordinary-alternative', '?retreat@?$OrdinaryRetreatObservation@$0EA@@@QAEAAViterator@?$deque@U?$RetreatValueObservation@$0EA@@@V?$allocator@U?$RetreatValueObservation@$0EA@@@@std@@@std@@H@Z', ['0x005F9510']), ('0x005F8D30', 57, 'retained-whole-sdk-addition', '??Hiterator@?$deque@U?$RetreatValueObservation@$0EA@@@V?$allocator@U?$RetreatValueObservation@$0EA@@@@std@@@std@@QBE?AV012@H@Z', ['0x005F9510'])]
NEGATIVE_ROUTES=[('0x0041ED00', 57, '??Hiterator@?$deque@U?$RetreatValueObservation@$00@@V?$allocator@U?$RetreatValueObservation@$00@@@std@@@std@@QBE?AV012@H@Z', ['0x0041F630']), ('0x0041EE60', 57, '??Hiterator@?$deque@U?$RetreatValueObservation@$01@@V?$allocator@U?$RetreatValueObservation@$01@@@std@@@std@@QBE?AV012@H@Z', ['0x0041F6D0']), ('0x00455C60', 57, '??Hiterator@?$deque@U?$RetreatValueObservation@$03@@V?$allocator@U?$RetreatValueObservation@$03@@@std@@@std@@QBE?AV012@H@Z', ['0x0042E2D0']), ('0x005F8D70', 57, '??Hiterator@?$deque@U?$RetreatValueObservation@$0EA@@@V?$allocator@U?$RetreatValueObservation@$0EA@@@@std@@@std@@QBE?AV012@H@Z', ['0x005F9510'])]
RETAINED=[('config/vendor-deque-access-origins.csv', '0x0041ECC0'), ('config/vendor-deque-access-origins.csv', '0x0041ED00'), ('config/vendor-deque-access-origins.csv', '0x0041EE20'), ('config/vendor-deque-access-origins.csv', '0x0041EE60'), ('config/vendor-deque-access-origins.csv', '0x0042E040'), ('config/vendor-deque-access-origins.csv', '0x00455C60'), ('config/vendor-deque-access-origins.csv', '0x005F8D30'), ('config/vendor-deque-access-origins.csv', '0x005F8D70'), ('config/vendor-deque-iterator-advance-origins.csv', '0x0041F630'), ('config/vendor-deque-iterator-advance-origins.csv', '0x0041F6D0'), ('config/vendor-deque-iterator-advance-origins.csv', '0x0042E2D0'), ('config/vendor-deque-iterator-advance-origins.csv', '0x005F9510')]


def manifest():return json.loads((ROOT/EVIDENCE).read_text())


def included_headers(output):
    found={}
    for line in output.splitlines():
        if 'Note: including file:' not in line:continue
        text=line.split('Note: including file:',1)[1].strip().replace('\\','/')
        if text[:3].lower()!='z:/':raise ValueError('replay include loses actual host mapping')
        path=Path(text[2:]);relative=str(path.relative_to(ROOT))
        if not relative.startswith('.tools/msvc710/Vc7/include/'):raise ValueError('replay gains unrelated include owner')
        found[relative]=digest(path.read_bytes())
    return found


def verify_plan(m):
    if (m['evidence_id']!='R176' or m['target_sha256']!=PRIOR.manifest()['target_sha256']
            or m['probe']!='probes/VC7DequeRetreatAlternatives.cpp' or m['profile']!=SDK.PROFILE
            or len(m['headers'])!=27 or len(m['functions'])!=4 or {r['address']:r['size'] for r in m['functions']}!=KEYS
            or len(m['controls'])!=20 or sum(r['size'] for r in m['controls'])!=796
            or sum(len(r['bindings']) for r in m['controls'])!=16 or len(m['emission'])!=33
            or sum(r['size'] for r in m['emission'])!=1152 or len(m['snapshots'])!=84 or len(m['retained'])!=12
            or m['layout'] not in m['emission'] or m['layout']['size']!=48 or m['layout_values']!=LAYOUT
            or m['external']!=EXTERNAL or m['protected']!=PROTECTED):
        raise ValueError('deque retreat loses bounded whole source/fields/emission/layout scope')
    mutable={'proposed_name','module','status','owner','evidence','notes'}
    for r in m['functions']:
        a=r['address'];old,new=r['original_function'],r['accepted_function'];control=next(x for x in m['controls'] if x['address']==a)
        if (r['decision']!='library' or r['original_origin']['origin']!='unknown' or old['address']!=a or int(old['size'])!=r['size']
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['module']!='VC7STL' or new['status']!='excluded' or new['owner']!='library' or new['source_file'] or new['signature'] or new['calling_convention'] or new['match_percent']!='0.00'
                or r['accepted_origin']!=dict(address=a,origin='library',subsystem='VC7STL',disposition='exclude',confidence=CONFIDENCE,evidence_id='R176')
                or r['symbol']!=control['source_definition']['symbol'] or r['body_sha256']!=control['body_sha256'] or r['cfg']!=control['cfg'] or not r['witnesses']):
            raise ValueError('deque retreat loses own SDK source or adds false source/private ABI/exact credit')
        if dict(site=f'0x{int(a,16)+10:08X}',mnemonic='neg',operands='eax') not in r['witnesses']:
            raise ValueError('deque retreat loses actual signed offset negation')
    actual=[]
    for r in m['controls']:
        ss,d=r['section'],r['source_definition'];actual.append((r['address'],r['size'],r['role'],d['symbol'],[b['target_address'] for b in r['bindings']]))
        if (r['kind']!='code' or ss not in m['emission'] or ss['size']!=r['size'] or d not in ss['definitions']
                or d['offset'] or d['type']!=32 or d['storage']!=2 or ss['source_sha256']!=r['source_sha256'] or len(ss['fields'])!=len(r['bindings'])):
            raise ValueError('deque retreat slices complete defining SDK/ordinary source')
        for f,b in zip(ss['fields'],r['bindings']):
            if b!=dict(offset=f['offset'],type=f['type'],symbol=f['symbol']['symbol'],addend=f['addend'],target_address=b['target_address']) or f['type']!='REL32' or f['offset']+4>r['size']:
                raise ValueError('deque retreat drops, masks or substitutes a real field')
    if actual!=ROUTES:raise ValueError('deque retreat changes actual full addition/subtraction/ordinary graph')
    actual=[]
    for r in m['negatives']:
        ss,d=r['section'],r['source_definition'];actual.append((r['address'],r['size'],d['symbol'],[b['target_address'] for b in r['bindings']]))
        if (r['kind']!='code' or r['role']!='whole-real-addition-negative' or r['target_size']!=57 or ss not in m['emission']
                or ss['size']!=r['size'] or d not in ss['definitions'] or d['offset'] or d['type']!=32 or d['storage']!=2
                or ss['source_sha256']!=r['source_sha256'] or len(ss['fields'])!=len(r['bindings'])):
            raise ValueError('deque retreat truncates real addition control or substitutes source')
        for f,b in zip(ss['fields'],r['bindings']):
            if b!=dict(offset=f['offset'],type=f['type'],symbol=f['symbol']['symbol'],addend=f['addend'],target_address=b['target_address']) or f['type']!='REL32':
                raise ValueError('deque retreat masks real addition destination')
    if actual!=NEGATIVE_ROUTES:raise ValueError('deque retreat conflates historical addition shape with actual subtraction')
    snapshots={r['address']:r for r in m['snapshots']}
    for a,size in PROTECTED.items():
        r=snapshots.get(a)
        if not r or r['size']!=size or r['origin']['origin']!='unknown':raise ValueError('deque retreat resolves independent opaque owner')
    if [(r['file'],r['address']) for r in m['retained']]!=RETAINED:raise ValueError('deque retreat loses original entire parent/child records')
    for r in m['retained']:
        expected='R078' if r['file']=='config/vendor-deque-access-origins.csv' else 'R083'
        if r['record']['evidence_id']!=expected or snapshots[r['address']]['origin']['evidence_id']!=expected or snapshots[r['address']]['origin']['origin']!='library':
            raise ValueError('deque retreat reclassifies accepted independent SDK evidence')


def accepted_snapshot(snapshot,function,origin):
    if digest((ROOT/EVIDENCE).read_bytes())!=MANIFEST_SHA256:raise ValueError('texture vector immutable manifest differs')
    m=manifest();verify_plan(m);r=next((r for r in m['functions'] if r['address']==function['address']),None)
    return bool(r and snapshot==dict(function=r['original_function'],origin=r['original_origin']) and function==r['accepted_function'] and origin==r['accepted_origin'])


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args();m=manifest();verify_plan(m)
    for path,expected in [(EVIDENCE,MANIFEST_SHA256),(m['probe'],m['probe_sha256']),*m['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes())!=expected:raise ValueError('replay immutable source/prior evidence differs: '+path)
    c=module('replay_target','compare-coff-function.py');coff=module('replay_coff','coff_data.py');cfg=module('replay_cfg','verify-authored-origins.py');extent=module('replay_extent','verify-vendor-record-origins.py');target=c.verified_target();rows=cfg.rows
    if digest(target)!=m['target_sha256']:raise ValueError('replay target identity differs')
    functions={r['address']:r for r in rows('functions.csv')};origins={r['address']:r for r in rows('function-origins.csv')};authored={r['address']:r for r in rows('authored-origin-evidence.csv')};records={r['address']:r for r in m['functions']};decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    def witnesses(body,a):return [dict(site=f'0x{x.address:08X}',mnemonic=x.mnemonic,operands=x.op_str) for x in decoder.disasm(body,int(a,16))]
    if any(r['evidence_id']=='R176' for r in authored.values()):raise ValueError('replay adds false authored extent credit')
    for r in m['functions']:
        a=r['address'];SDK.check_ledger(r,functions[a],origins[a],args.evidence_only);body=c.pe_bytes_at(target,int(a,16),r['size'])
        if digest(body)!=r['body_sha256'] or list(cfg.verify_body(body,int(a,16)))!=r['cfg'] or witnesses(body,a)!=r['witnesses']:raise ValueError('replay entire accepted body/CFG/instructions differ')
    for r in m['snapshots']:
        a=r['address']
        if a in records:SDK.check_ledger(records[a],functions[a],origins[a],args.evidence_only)
        elif functions[a]!=r['function'] or origins[a]!=r['origin']:raise ValueError('replay changes unrelated original canonical record')
        if digest(c.pe_bytes_at(target,int(a,16),r['size']))!=r['body_sha256']:raise ValueError('replay whole original snapshot differs')
    for r in m['retained']:
        path=ROOT/r['file'];inventory=json.loads(path.read_text())[r['collection']] if path.suffix=='.json' else rows(path.name)
        if r['record'] not in inventory:raise ValueError('texture vector original full pending/runtime/compiler evidence differs')
    scratch=ROOT/'build/origin-deque-retreat-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as dirname:
        path=Path(dirname)/'DequeRetreatAlternatives.obj';result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/m['probe']),str(path),*m['profile']],cwd=ROOT,capture_output=True,text=True)
        if result.returncode or included_headers(result.stdout+result.stderr)!=m['headers']:raise ValueError('replay cold source/actual include ownership differs')
        data=path.read_bytes()
        if SDK.PAIRED.BUFFER.inventory(data,c,coff)!=m['emission']:raise ValueError('replay entire ordinary emission differs')
        catalog={}
        for r in m['controls']:
            for d in r['section']['definitions']:
                if d['storage'] in (2,3) and not d['symbol'].startswith('.'):
                    name,a=d['symbol'],int(r['address'],16)+d['offset']
                    if name in catalog and catalog[name]!=a:raise ValueError('replay overrides one coherent source definition')
                    catalog[name]=a
        for r in m['controls']:
            for b in r['bindings']:
                if catalog.get(b['symbol'],int(EXTERNAL[b['symbol']],16) if b['symbol'] in EXTERNAL else None)!=int(b['target_address'],16):raise ValueError('replay real field loses its entire actual defining source')
            for b in r['bindings']:
                if b['symbol'] in EXTERNAL:catalog[b['symbol']]=int(EXTERNAL[b['symbol']],16)
            raw,linked=SDK.ENDPOINT.link(data,r,catalog,c);actual=c.pe_bytes_at(target,int(r['address'],16),r['size'])
            if len(raw)!=r['size'] or linked!=actual or digest(raw)!=r['source_sha256'] or digest(actual)!=r['body_sha256']:raise ValueError('replay whole unmasked source comparison differs: '+r['address'])
            if r['kind']=='compiler-code':module('texture_implicit','verify-game-parent-policy-origins.py').verify_implicit_extent(r,data,c.coff_name)
            elif extent.complete_aux_section_size(data,r['source_definition']['symbol'],c.coff_name)!=r['size']:raise ValueError('texture vector full own primary AUX differs')
            if list(cfg.verify_body(actual,int(r['address'],16)))!=r['cfg']:raise ValueError('texture vector whole positive CFG differs')
        for r in m['negatives']:
            raw,linked=SDK.ENDPOINT.link(data,r,catalog,c);actual=c.pe_bytes_at(target,int(r['address'],16),r['target_size'])
            if len(raw)!=57 or len(linked)!=57 or len(actual)!=57 or digest(raw)!=r['source_sha256'] or digest(actual)!=r['body_sha256'] or linked==actual:
                raise ValueError('deque retreat compares a negative prefix or grants false positive credit')
            if extent.complete_aux_section_size(data,r['source_definition']['symbol'],c.coff_name)!=57:raise ValueError('deque retreat real addition lacks full own AUX')
            if any(catalog[b['symbol']]!=int(b['target_address'],16) for b in r['bindings']):raise ValueError('deque retreat negative loses actual entire source child')
            changed={i for i,(left,right) in enumerate(zip(linked,actual)) if left!=right}
            fields={i for b in r['bindings'] for i in range(b['offset'],b['offset']+4)}
            if not changed or not changed<=fields:raise ValueError('deque retreat actual addition/subtraction difference escapes genuine field')
        raw,_=coff.readonly_section(data,m['layout']['section'],c.coff_name)
        if list(struct.unpack('<12I',raw))!=LAYOUT:raise ValueError('replay complete readonly layout differs')
    print('R176 origins OK: four whole SDK iterator retreat wrappers /108 bytes;20 entire SDK/ordinary controls /796 bytes and16 real unmasked fields; four full57-byte real-addition negatives distinguish call destinations; all33 cold ordinary sections /1152 bytes,27 actual SDK headers and whole48-byte layout;84 canonical/body snapshots and twelve original whole R078/R083 records preserved; width1/2/4/64 source variants expose unresolved original width and ordinary27-byte alternatives are byte-equal; no source/private ABI/mapping/exact credit.')
    return 0


if __name__=='__main__':
    try:raise SystemExit(main())
    except (OSError,KeyError,IndexError,StopIteration,ValueError,struct.error,json.JSONDecodeError) as error:
        print('error: '+str(error),file=sys.stderr);raise SystemExit(1)
