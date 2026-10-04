#!/usr/bin/env python3
"""Replay full static resource policies and complete SDK/source-order evidence."""
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
spec=importlib.util.spec_from_file_location('static_resource_prior',ROOT/'scripts/verify-deque-retreat-origins.py')
PRIOR=importlib.util.module_from_spec(spec);spec.loader.exec_module(PRIOR)
SDK=PRIOR.SDK;module=SDK.module;digest=SDK.digest
EVIDENCE='config/static-resource-policy-origin-evidence.json'
MANIFEST_SHA256='8c0beafe33c5b79a6b0d6cb8f135427cf225fe7890de98cfc37f3e81da69fb41'
KEYS={'0x00413650': 132, '0x004136E0': 161, '0x00413880': 67, '0x005F6FF0': 235, '0x005F8380': 49, '0x005F8320': 19, '0x005F83E0': 19, '0x005F8EA0': 19}
AUTHORED={'0x00413650','0x004136E0','0x00413880','0x005F6FF0'}
LAYOUT=[20, 20, 20, 84, 84, 4, 16, 60, 60, 16, 4, 16]
EXTERNAL={'??1StaticDeleteObservation@@QAE@XZ': '0x005F7ED0', '??3@YAXPAX@Z': '0x00640F15', '?tidy@OrdinaryStaticVectorTidyObservation@@QAEXXZ': '0x005F8C50'}
PROTECTED={'0x00411E80': 8, '0x00411E90': 11, '0x00412580': 5, '0x00412600': 5, '0x0041206F': 80, '0x004229C0': 15, '0x0042E580': 5, '0x004212A0': 72, '0x004591E0': 417, '0x0045AAE0': 368, '0x0040D8E0': 19, '0x004229D0': 28, '0x0040F9F0': 15, '0x0040E000': 158, '0x005F84B0': 167, '0x00641FB8': 11, '0x00641DAA': 11, '0x00458650': 31, '0x00458670': 23, '0x0045B880': 149, '0x004124B0': 16, '0x004124C0': 11, '0x004122C9': 52, '0x0041E100': 8, '0x0041E110': 11, '0x0041F7E0': 16, '0x0041EFE6': 52, '0x00531D80': 8, '0x00531D90': 11, '0x00532350': 16, '0x00532196': 52, '0x0040E9B0': 16, '0x0040EA20': 16, '0x0041F9F0': 5, '0x0041FDF0': 5, '0x00532480': 5, '0x00532500': 5, '0x005F9640': 16, '0x005F7ED0': 72}
ROUTES=[('0x005F8380', 49, 'code', '??A?$vector@PAUStaticDeleteObservation@@V?$allocator@PAUStaticDeleteObservation@@@std@@@std@@QAEAAPAUStaticDeleteObservation@@I@Z', ['0x005F8B50', '0x005F8EC0', '0x005F8EA0']), ('0x005F8340', 52, 'code', '?size@?$vector@PAUStaticDeleteObservation@@V?$allocator@PAUStaticDeleteObservation@@@std@@@std@@QBEIXZ', []), ('0x005F83E0', 19, 'code', '?clear@?$vector@PAUStaticDeleteObservation@@V?$allocator@PAUStaticDeleteObservation@@@std@@@std@@QAEXXZ', ['0x005F8C50']), ('0x005F8320', 19, 'code', '??1?$vector@PAUStaticDeleteObservation@@V?$allocator@PAUStaticDeleteObservation@@@std@@@std@@QAE@XZ', ['0x005F8C50']), ('0x005F7EA0', 44, 'compiler-code', '??_GStaticDeleteObservation@@QAEPAXI@Z', ['0x005F7ED0', '0x00640F15']), ('0x005F8B50', 31, 'code', '?begin@?$vector@PAUStaticDeleteObservation@@V?$allocator@PAUStaticDeleteObservation@@@std@@@std@@QAE?AViterator@12@XZ', ['0x005F9600']), ('0x005F8EC0', 45, 'code', '??Hiterator@?$vector@PAUStaticDeleteObservation@@V?$allocator@PAUStaticDeleteObservation@@@std@@@std@@QBE?AV012@H@Z', ['0x005F9620']), ('0x005F8EA0', 19, 'code', '??Diterator@?$vector@PAUStaticDeleteObservation@@V?$allocator@PAUStaticDeleteObservation@@@std@@@std@@QBEAAPAUStaticDeleteObservation@@XZ', ['0x005F9640']), ('0x005F8C50', 103, 'code', '?_Tidy@?$vector@PAUStaticDeleteObservation@@V?$allocator@PAUStaticDeleteObservation@@@std@@@std@@IAEXXZ', ['0x005F9430', '0x005F94D0']), ('0x005F9600', 28, 'code', '??0iterator@?$vector@PAUStaticDeleteObservation@@V?$allocator@PAUStaticDeleteObservation@@@std@@@std@@QAE@PAPAUStaticDeleteObservation@@@Z', ['0x005F9E00']), ('0x005F9620', 32, 'code', '??Yiterator@?$vector@PAUStaticDeleteObservation@@V?$allocator@PAUStaticDeleteObservation@@@std@@@std@@QAEAAV012@H@Z', []), ('0x005F9640', 16, 'code', '??Dconst_iterator@?$vector@PAUStaticDeleteObservation@@V?$allocator@PAUStaticDeleteObservation@@@std@@@std@@QBEABQAUStaticDeleteObservation@@XZ', []), ('0x005F9430', 33, 'code', '?_Destroy@?$vector@PAUStaticDeleteObservation@@V?$allocator@PAUStaticDeleteObservation@@@std@@@std@@IAEXPAPAUStaticDeleteObservation@@0@Z', ['0x005FA290']), ('0x005F94D0', 25, 'code', '?deallocate@?$allocator@PAUStaticDeleteObservation@@@std@@QAEXPAPAUStaticDeleteObservation@@I@Z', ['0x00640F15']), ('0x005F9E00', 24, 'code', '??0const_iterator@?$vector@PAUStaticDeleteObservation@@V?$allocator@PAUStaticDeleteObservation@@@std@@@std@@QAE@PAPAUStaticDeleteObservation@@@Z', []), ('0x005FA290', 51, 'code', '??$_Destroy_range@PAUStaticDeleteObservation@@V?$allocator@PAUStaticDeleteObservation@@@std@@@std@@YAXPAPAUStaticDeleteObservation@@0AAV?$allocator@PAUStaticDeleteObservation@@@0@@Z', ['0x005FA6B0', '0x005FA700']), ('0x005FA6B0', 11, 'code', '??$_Ptr_cat@UStaticDeleteObservation@@@std@@YA?AU_Scalar_ptr_iterator_tag@0@PAPAUStaticDeleteObservation@@0@Z', []), ('0x005FA700', 5, 'code', '??$_Destroy_range@PAUStaticDeleteObservation@@V?$allocator@PAUStaticDeleteObservation@@@std@@@std@@YAXPAPAUStaticDeleteObservation@@0AAV?$allocator@PAUStaticDeleteObservation@@@0@U_Scalar_ptr_iterator_tag@0@@Z', []), ('0x005F8380', 49, 'code', '?entry@OrdinaryStaticVectorIndexObservation@@QAEAAPAUStaticDeleteObservation@@I@Z', ['0x005F8B50', '0x005F8EC0', '0x005F8EA0']), ('0x005F8B50', 31, 'code', '?begin@OrdinaryStaticVectorIndexObservation@@QAE?AViterator@?$vector@PAUStaticDeleteObservation@@V?$allocator@PAUStaticDeleteObservation@@@std@@@std@@XZ', ['0x005F9600']), ('0x005F8EA0', 19, 'code', '?value@OrdinaryStaticIteratorObservation@@QBEAAPAUStaticDeleteObservation@@XZ', ['0x005F9640']), ('0x005F8320', 19, 'code', '?clean@OrdinaryStaticVectorTidyObservation@@QAEXXZ', ['0x005F8C50'])]
POLICIES=[('eh', '0x00413650', 120, '??0ExplicitStaticQueuesObservation@@QAE@XZ', False, ['??0?$deque@U?$StaticValueObservation@$00@@V?$allocator@U?$StaticValueObservation@$00@@@std@@@std@@QAE@XZ', '??0?$deque@U?$StaticValueObservation@$01@@V?$allocator@U?$StaticValueObservation@$01@@@std@@@std@@QAE@XZ', '??0?$deque@U?$StaticValueObservation@$00@@V?$allocator@U?$StaticValueObservation@$00@@@std@@@std@@QAE@XZ', '??0?$deque@U?$StaticValueObservation@$03@@V?$allocator@U?$StaticValueObservation@$03@@@std@@@std@@QAE@XZ']), ('eh', '0x00413650', 111, '??0ImplicitStaticQueuesObservation@@QAE@XZ', True, ['??0?$deque@U?$StaticValueObservation@$00@@V?$allocator@U?$StaticValueObservation@$00@@@std@@@std@@QAE@XZ', '??0?$deque@U?$StaticValueObservation@$01@@V?$allocator@U?$StaticValueObservation@$01@@@std@@@std@@QAE@XZ', '??0?$deque@U?$StaticValueObservation@$00@@V?$allocator@U?$StaticValueObservation@$00@@@std@@@std@@QAE@XZ', '??0?$deque@U?$StaticValueObservation@$03@@V?$allocator@U?$StaticValueObservation@$03@@@std@@@std@@QAE@XZ']), ('eh', '0x004136E0', 149, '??1ExplicitStaticQueuesObservation@@QAE@XZ', False, ['?clearQueues@ExplicitStaticQueuesObservation@@QAEXXZ', '??1?$deque@U?$StaticValueObservation@$03@@V?$allocator@U?$StaticValueObservation@$03@@@std@@@std@@QAE@XZ', '??1?$deque@U?$StaticValueObservation@$00@@V?$allocator@U?$StaticValueObservation@$00@@@std@@@std@@QAE@XZ', '??1?$deque@U?$StaticValueObservation@$01@@V?$allocator@U?$StaticValueObservation@$01@@@std@@@std@@QAE@XZ', '??1?$deque@U?$StaticValueObservation@$00@@V?$allocator@U?$StaticValueObservation@$00@@@std@@@std@@QAE@XZ']), ('eh', '0x00413880', 55, '?clearQueues@ExplicitStaticQueuesObservation@@QAEXXZ', False, ['?clear@?$deque@U?$StaticValueObservation@$00@@V?$allocator@U?$StaticValueObservation@$00@@@std@@@std@@QAEXXZ', '?clear@?$deque@U?$StaticValueObservation@$01@@V?$allocator@U?$StaticValueObservation@$01@@@std@@@std@@QAEXXZ', '?clear@?$deque@U?$StaticValueObservation@$00@@V?$allocator@U?$StaticValueObservation@$00@@@std@@@std@@QAEXXZ', '?clear@?$deque@U?$StaticValueObservation@$03@@V?$allocator@U?$StaticValueObservation@$03@@@std@@@std@@QAEXXZ']), ('eh', '0x004136E0', 108, '??1ImplicitStaticQueuesObservation@@QAE@XZ', True, ['??1?$deque@U?$StaticValueObservation@$03@@V?$allocator@U?$StaticValueObservation@$03@@@std@@@std@@QAE@XZ', '??1?$deque@U?$StaticValueObservation@$00@@V?$allocator@U?$StaticValueObservation@$00@@@std@@@std@@QAE@XZ', '??1?$deque@U?$StaticValueObservation@$01@@V?$allocator@U?$StaticValueObservation@$01@@@std@@@std@@QAE@XZ', '??1?$deque@U?$StaticValueObservation@$00@@V?$allocator@U?$StaticValueObservation@$00@@@std@@@std@@QAE@XZ']), ('eh', '0x005F6FF0', 235, '??1ExplicitStaticPointerOwnerObservation@@QAE@XZ', False, ['?releaseEntries@ExplicitStaticPointerOwnerObservation@@QAEXXZ', '?size@?$vector@PAUStaticDeleteObservation@@V?$allocator@PAUStaticDeleteObservation@@@std@@@std@@QBEIXZ', '??A?$vector@PAUStaticDeleteObservation@@V?$allocator@PAUStaticDeleteObservation@@@std@@@std@@QAEAAPAUStaticDeleteObservation@@I@Z', '??A?$vector@PAUStaticDeleteObservation@@V?$allocator@PAUStaticDeleteObservation@@@std@@@std@@QAEAAPAUStaticDeleteObservation@@I@Z', '??_GStaticDeleteObservation@@QAEPAXI@Z', '?clear@?$vector@PAUStaticDeleteObservation@@V?$allocator@PAUStaticDeleteObservation@@@std@@@std@@QAEXXZ', '??1?$vector@PAUStaticDeleteObservation@@V?$allocator@PAUStaticDeleteObservation@@@std@@@std@@QAE@XZ', '??1StaticTextureObservation@@QAE@XZ', '??_M@YGXPAXIHP6EX0@Z@Z']), ('eh', '0x005F6FF0', 100, '??1ImplicitStaticPointerOwnerObservation@@QAE@XZ', True, ['??1?$vector@PAUStaticDeleteObservation@@V?$allocator@PAUStaticDeleteObservation@@@std@@@std@@QAE@XZ', '??1StaticTextureObservation@@QAE@XZ', '??_M@YGXPAXIHP6EX0@Z@Z']), ('no-eh', '0x00413880', 55, '?clearQueues@ExplicitStaticQueuesObservation@@QAEXXZ', False, ['?clear@?$deque@U?$StaticValueObservation@$00@@V?$allocator@U?$StaticValueObservation@$00@@@std@@@std@@QAEXXZ', '?clear@?$deque@U?$StaticValueObservation@$01@@V?$allocator@U?$StaticValueObservation@$01@@@std@@@std@@QAEXXZ', '?clear@?$deque@U?$StaticValueObservation@$00@@V?$allocator@U?$StaticValueObservation@$00@@@std@@@std@@QAEXXZ', '?clear@?$deque@U?$StaticValueObservation@$03@@V?$allocator@U?$StaticValueObservation@$03@@@std@@@std@@QAEXXZ']), ('no-eh', '0x004136E0', 55, '??1ImplicitStaticQueuesObservation@@QAE@XZ', True, ['??1?$deque@U?$StaticValueObservation@$03@@V?$allocator@U?$StaticValueObservation@$03@@@std@@@std@@QAE@XZ', '??1?$deque@U?$StaticValueObservation@$00@@V?$allocator@U?$StaticValueObservation@$00@@@std@@@std@@QAE@XZ', '??1?$deque@U?$StaticValueObservation@$01@@V?$allocator@U?$StaticValueObservation@$01@@@std@@@std@@QAE@XZ', '??1?$deque@U?$StaticValueObservation@$00@@V?$allocator@U?$StaticValueObservation@$00@@@std@@@std@@QAE@XZ'])]
RETAINED=[('config/compiler-static-evidence.csv', '0x00656DC0', None), ('config/compiler-static-evidence.csv', '0x00656EC0', None), ('config/compiler-static-evidence.csv', '0x00656EB0', None), ('config/scalar-deleting-origin-evidence.csv', '0x005F7EA0', None), ('config/initializer-startup-origin-evidence.json', '0x00656DC0', 'compiler_callbacks')]


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
    if (m['evidence_id']!='R177' or m['target_sha256']!=PRIOR.manifest()['target_sha256']
            or m['probe']!='probes/VC7StaticResourceAlternatives.cpp' or m['profile']!=SDK.PROFILE
            or len(m['headers'])!=28 or len(m['functions'])!=8 or {r['address']:r['size'] for r in m['functions']}!=KEYS
            or len(m['controls'])!=22 or sum(r['size'] for r in m['controls'])!=724
            or sum(len(r['bindings']) for r in m['controls'])!=23 or len(m['emission'])!=112
            or sum(r['size'] for r in m['emission'])!=4968 or len(m['snapshots'])!=121 or len(m['retained'])!=5
            or m['layout'] not in m['emission'] or m['layout']['size']!=48 or m['layout_values']!=LAYOUT
            or m['external']!=EXTERNAL or m['protected']!=PROTECTED or len(m['policies'])!=9
            or m['secondary']['profile']!=[x for x in SDK.PROFILE if x!='/GX']
            or len(m['secondary']['headers'])!=28 or len(m['secondary']['emission'])!=96
            or sum(r['size'] for r in m['secondary']['emission'])!=3879 or m['secondary']['layout'] not in m['secondary']['emission']):
        raise ValueError('static resource loses bounded whole source/field/emission/profile/layout scope')
    mutable={'proposed_name','module','status','owner','evidence','notes'}
    for r in m['functions']:
        a=r['address'];old,new=r['original_function'],r['accepted_function'];decision='authored' if a in AUTHORED else 'library';owner='StaticResourcePolicy' if a in AUTHORED else 'VC7STL'
        confidence='complete-explicit-static-resource-policy-and-whole-source-order-controls' if a in AUTHORED else 'complete-vc7-owned-pointer-vector-and-whole-static-game-policy'
        if (r['decision']!=decision or r['original_origin']['origin']!='unknown' or old['address']!=a or int(old['size'])!=r['size']
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['module']!=owner or new['status']!=('unclassified' if a in AUTHORED else 'excluded') or new['owner']!=decision
                or new['source_file'] or new['signature'] or new['calling_convention'] or new['match_percent']!='0.00'
                or r['accepted_origin']!=dict(address=a,origin=decision,subsystem=owner,disposition='authored' if a in AUTHORED else 'exclude',confidence=confidence,evidence_id='R177') or not r['witnesses']):
            raise ValueError('static resource loses independent owner or adds false source/private ABI/exact credit')
        if a in AUTHORED:
            if 'symbol' in r or r['accepted_authored_record']!=dict(address=a,size=str(r['size']),body_sha256=r['body_sha256'],inferred_role=new['proposed_name'],return_count=str(r['cfg'][0]),internal_branch_count=str(r['cfg'][1]),external_branch_count='0',evidence_id='R177'):
                raise ValueError('static resource loses entire authored record or claims a false source-byte match')
        else:
            control=next(x for x in m['controls'][:18] if x['address']==a)
            if r['symbol']!=control['source_definition']['symbol'] or r['body_sha256']!=control['body_sha256'] or r['cfg']!=control['cfg']:
                raise ValueError('static resource replaces entire actual defining SDK source')
    actual=[]
    for r in m['controls']:
        ss,d=r['section'],r['source_definition'];actual.append((r['address'],r['size'],r['kind'],d['symbol'],[b['target_address'] for b in r['bindings']]))
        if (ss not in m['emission'] or ss['size']!=r['size'] or d not in ss['definitions'] or d['offset'] or d['type']!=32 or d['storage']!=2
                or ss['source_sha256']!=r['source_sha256'] or len(ss['fields'])!=len(r['bindings'])):
            raise ValueError('static resource slices full defining SDK/ordinary/compiler source')
        for f,b in zip(ss['fields'],r['bindings']):
            if b!=dict(offset=f['offset'],type=f['type'],symbol=f['symbol']['symbol'],addend=f['addend'],target_address=b['target_address']) or f['type']!='REL32' or f['offset']+4>r['size']:
                raise ValueError('static resource drops, substitutes or masks a real field')
    if actual!=ROUTES:raise ValueError('static resource overrides actual closed source/ordinary/compiler routes')
    actual=[]
    for r in m['policies']:
        ss,d=r['section'],r['source_definition'];inventory=m['emission'] if r['profile']=='eh' else m['secondary']['emission']
        actual.append((r['profile'],r['address'],r['size'],d['symbol'],r['implicit'],r['call_symbols']))
        if (ss not in inventory or ss['size']!=r['size'] or ss['source_sha256']!=r['source_sha256'] or d not in ss['definitions']
                or d['offset'] or d['type']!=32 or d['storage']!=2 or r['target_size']!=KEYS[r['address']]
                or r['role']!='whole-small-layout-source-operation-control' or not r['witnesses']
                or [f['symbol']['symbol'] for f in ss['fields'] if f['type']=='REL32']!=r['call_symbols']):
            raise ValueError('static resource loses whole source operation/order alternative')
    if actual!=POLICIES:raise ValueError('static resource replaces generated/explicit operation or source order')
    snapshots={r['address']:r for r in m['snapshots']}
    for a,size in PROTECTED.items():
        r=snapshots.get(a)
        if not r or r['size']!=size or r['origin']['origin']!='unknown':raise ValueError('static resource resolves independent opaque ownership')
    if snapshots['0x005F7EA0']['origin']['origin']!='compiler' or snapshots['0x005F7EA0']['origin']['evidence_id']!='R037':raise ValueError('static resource reclassifies old deleting compiler thunk')
    if {r['address']:r['size'] for r in m['anchors']}!={'0x0040AE40':434,'0x005F7140':162} or any(r['origin']['origin']!='authored' or r['record']['evidence_id']!=r['origin']['evidence_id'] for r in m['anchors']):
        raise ValueError('static resource loses independent whole game release context')
    if [(r['file'],r['address'],r.get('collection')) for r in m['retained']]!=RETAINED:raise ValueError('static resource loses full original static/deleting/callback records')
    if [r['handler_address'] for r in m['retained_frames']]!=['0x006550EA','0x0065512C','0x0065665C'] or any(r['evidence_id']!='R020' for r in m['retained_frames']):
        raise ValueError('static resource loses original registered unwind frames')
    if m['import_slot']!=dict(address='0x00657138',dll='KERNEL32.dll',name='CloseHandle'):raise ValueError('static resource substitutes actual CloseHandle import')
    records={r['address']:r for r in m['functions']}
    for a,targets in {'0x00413650':['0x414360','0x414550','0x414360','0x414740'],
                      '0x004136E0':['0x413880','0x414790','0x4143b0','0x4145a0','0x4143b0'],
                      '0x00413880':['0x414530','0x414720','0x414530','0x414910'],
                      '0x005F6FF0':['0x5f7140','0x5f8340','0x5f8380','0x5f8380','0x5f7ea0','0x5f83e0','0x5f8320','0x40ae40','0x641d4a']}.items():
        if [r['operands'] for r in records[a]['witnesses'] if r['mnemonic']=='call' and r['operands'].startswith('0x')]!=targets:
            raise ValueError('static resource loses actual complete direct-call policy/order')
    for a,offsets in {'0x00413650':['ecx, 0x154','ecx, 0x168','ecx, 0x17c','ecx, 0x190'],
                      '0x004136E0':['ecx, 0x190','ecx, 0x17c','ecx, 0x168','ecx, 0x154'],
                      '0x00413880':['ecx, 0x154','ecx, 0x168','ecx, 0x17c','ecx, 0x190']}.items():
        if [r['operands'] for r in records[a]['witnesses'] if r['mnemonic']=='add']!=offsets:
            raise ValueError('static resource conflates ascending clear with reverse automatic destruction')
    required={'0x00413650':[('0x004136B6','mov','dword ptr [eax], 0')],
              '0x004136E0':[('0x0041370E','cmp','dword ptr [eax], 0'),('0x00413711','je','0x413728'),('0x00413719','call','dword ptr [0x657138]'),('0x00413722','mov','dword ptr [eax], 0')],
              '0x005F6FF0':[('0x005F704E','cmp','dword ptr [eax], 0'),('0x005F7062','mov','eax, dword ptr [eax]'),('0x005F7073','push','1'),('0x005F7089','jmp','0x5f7026')]}
    for a,expected in required.items():
        if not set(expected)<={(r['site'],r['mnemonic'],r['operands']) for r in records[a]['witnesses']}:raise ValueError('static resource loses explicit handle/pointer ownership operation')


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
    if {a for a,r in authored.items() if r['evidence_id']=='R177'}!=(set() if args.evidence_only else AUTHORED):raise ValueError('resource release authored extent registry differs')
    for r in m['functions']:
        a=r['address'];SDK.check_ledger(r,functions[a],origins[a],args.evidence_only);body=c.pe_bytes_at(target,int(a,16),r['size'])
        if not args.evidence_only and a in AUTHORED and authored[a]!=r['accepted_authored_record']:raise ValueError('resource release canonical authored record differs')
        if digest(body)!=r['body_sha256'] or list(cfg.verify_body(body,int(a,16)))!=r['cfg'] or witnesses(body,a)!=r['witnesses']:raise ValueError('replay entire accepted body/CFG/instructions differ')
    for r in m['snapshots']:
        a=r['address']
        if a in records:SDK.check_ledger(records[a],functions[a],origins[a],args.evidence_only)
        elif functions[a]!=r['function'] or origins[a]!=r['origin']:raise ValueError('replay changes unrelated original canonical record')
        if digest(c.pe_bytes_at(target,int(a,16),r['size']))!=r['body_sha256']:raise ValueError('replay whole original snapshot differs')
    for r in m['retained']:
        path=ROOT/r['file'];inventory=json.loads(path.read_text())[r['collection']] if path.suffix=='.json' else rows(path.name)
        if r['record'] not in inventory:raise ValueError('texture vector original full pending/runtime/compiler evidence differs')
    for r in m['anchors']:
        a=r['address'];body=c.pe_bytes_at(target,int(a,16),r['size'])
        if functions[a]!=r['function'] or origins[a]!=r['origin'] or authored[a]!=r['record'] or digest(body)!=r['record']['body_sha256'] or witnesses(body,a)!=r['witnesses']:raise ValueError('replay whole independent game policy differs')
        for filename,key in [('authored-origin-switches.csv','switches'),('authored-origin-direct-switches.csv','direct_switches')]:
            if [x for x in rows(filename) if x['address']==a]!=r[key]:raise ValueError('replay original game switch evidence differs')
        if cfg.verify_body(body,int(a,16),r['switches'],lambda a,n:c.pe_bytes_at(target,a,n),r['direct_switches'])!=(int(r['record']['return_count']),int(r['record']['internal_branch_count'])):raise ValueError('replay entire game policy CFG differs')
    eh=module('resource_release_eh','compiler_eh.py')
    for frame in m['retained_frames']:
        if frame not in rows('compiler-eh-frames.csv'):raise ValueError('resource release original full frame differs')
        eh.verify_frame(frame,lambda a,n:c.pe_bytes_at(target,a,n),lambda a,n:c.pe_bytes_at(target,a,n),{int(a,16) for a in functions})
    if module('resource_release_import','verify-import-origins.py').pe_imports(target,c)[0x657138]!=('KERNEL32.dll','CloseHandle'):raise ValueError('resource release actual PE import differs')
    scratch=ROOT/'build/origin-static-resource-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as dirname:
        path=Path(dirname)/'StaticResourceAlternatives.obj';result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/m['probe']),str(path),*m['profile']],cwd=ROOT,capture_output=True,text=True)
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
            if r['kind']=='compiler-code':module('static_resource_implicit','verify-game-parent-policy-origins.py').verify_implicit_extent(r,data,c.coff_name)
            elif extent.complete_aux_section_size(data,r['source_definition']['symbol'],c.coff_name)!=r['size']:raise ValueError('static resource full positive own AUX differs')
            if list(cfg.verify_body(actual,int(r['address'],16)))!=r['cfg']:raise ValueError('static resource entire positive CFG differs')
        def source_policies(obj,profile):
            for r in m['policies']:
                if r['profile']!=profile:continue
                ss=r['section'];header=struct.unpack_from('<8sIIIIIIHHI',obj,20+(ss['section']-1)*40);raw=obj[header[4]:header[4]+header[3]]
                if len(raw)!=r['size'] or digest(raw)!=r['source_sha256'] or witnesses(raw,'0x00000000')!=r['witnesses'] or list(cfg.verify_body(raw,0))!=r['cfg']:raise ValueError('static resource whole source-policy control differs')
                if r['implicit']:module('static_resource_generated','verify-game-parent-policy-origins.py').verify_implicit_extent(r,obj,c.coff_name)
                elif extent.complete_aux_section_size(obj,r['source_definition']['symbol'],c.coff_name)!=r['size']:raise ValueError('static resource explicit source policy loses own full AUX')
        source_policies(data,'eh')
        raw,_=coff.readonly_section(data,m['layout']['section'],c.coff_name)
        if list(struct.unpack('<12I',raw))!=LAYOUT:raise ValueError('replay complete readonly layout differs')
        secondary=m['secondary'];other=Path(dirname)/'StaticResourceNoEH.obj'
        result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/m['probe']),str(other),*secondary['profile']],cwd=ROOT,capture_output=True,text=True)
        if result.returncode or included_headers(result.stdout+result.stderr)!=secondary['headers']:raise ValueError('static resource second cold source/header profile differs')
        other_data=other.read_bytes()
        if SDK.PAIRED.BUFFER.inventory(other_data,c,coff)!=secondary['emission']:raise ValueError('static resource second entire ordinary emission differs')
        raw,_=coff.readonly_section(other_data,secondary['layout']['section'],c.coff_name)
        if list(struct.unpack('<12I',raw))!=LAYOUT:raise ValueError('static resource second whole readonly layout differs')
        source_policies(other_data,'no-eh')
    print('R177 origins OK: four entire explicit static resource policies /595 bytes and four SDK vector dependencies /106 bytes;22 whole SDK/ordinary/compiler controls /724 bytes and23 genuine unmasked fields; nine whole small-layout operation/order controls /988 bytes under two cold profiles, with no source-byte credit for custom targets;112/96 complete ordinary sections /4968/3879 bytes,28 actual SDK headers and whole48-byte layout; full R017/R166 context /596 bytes, three original EH frames, five prior records and121 canonical/body snapshots preserved; ascending clear differs from reverse generated destruction; genuine CloseHandle and stride4 observed; const getter and lifetime child stay unknown; exact stays60.')
    return 0


if __name__=='__main__':
    try:raise SystemExit(main())
    except (OSError,KeyError,IndexError,StopIteration,ValueError,struct.error,json.JSONDecodeError) as error:
        print('error: '+str(error),file=sys.stderr);raise SystemExit(1)
