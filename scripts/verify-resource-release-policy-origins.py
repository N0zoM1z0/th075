#!/usr/bin/env python3
"""Replay full explicit resource release policies and closed SDK/lifetime evidence."""
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
spec=importlib.util.spec_from_file_location('resource_release_prior',ROOT/'scripts/verify-secondary-texture-access-origins.py')
PRIOR=importlib.util.module_from_spec(spec);spec.loader.exec_module(PRIOR)
SDK=PRIOR.SDK;module=SDK.module;digest=SDK.digest
EVIDENCE='config/resource-release-policy-origin-evidence.json'
MANIFEST_SHA256='294b8efee42b9276eb0135e3b3006591d0d2096d02c9698cf64d48e1aec0fc23'
KEYS={'0x00412E50': 83, '0x0041D1F0': 98, '0x0052D020': 105, '0x0041D9F0': 153, '0x0041D930': 19, '0x0041E280': 100, '0x0041E360': 25, '0x0041F130': 25, '0x00531CE0': 153, '0x00531C40': 19, '0x00532010': 100, '0x005320F0': 25, '0x005322E0': 25}
AUTHORED={'0x00412E50','0x0041D1F0','0x0052D020'}
LAYOUT=[108, 16, 12, 12, 16, 16, 44, 44, 4, 16, 16]
EXTERNAL={'??1TextureReleaseObservation@@QAE@XZ': '0x0040AE40', '??3@YAXPAX@Z': '0x00640F15', '?tidy@OrdinaryArchiveTidyObservation@@QAEXXZ': '0x0041E280', '?tidy@OrdinaryCharacterTidyObservation@@QAEXXZ': '0x00532010', '___CxxFrameHandler': '0x006407B8', '__except_list': '0x00000000', '__imp__CloseObservedHandle@4': '0x00657138'}
PROTECTED={'0x00411E80': 8, '0x00411E90': 11, '0x00412580': 5, '0x00412600': 5, '0x0041206F': 80, '0x004229C0': 15, '0x0042E580': 5, '0x004212A0': 72, '0x004591E0': 417, '0x0045AAE0': 368, '0x0040D8E0': 19, '0x004229D0': 28, '0x0040F9F0': 15, '0x0040E000': 158, '0x005F84B0': 167, '0x00641FB8': 11, '0x00641DAA': 11, '0x00458650': 31, '0x00458670': 23, '0x0045B880': 149, '0x004124B0': 16, '0x004124C0': 11, '0x004122C9': 52, '0x0041E100': 8, '0x0041E110': 11, '0x0041F7E0': 16, '0x0041EFE6': 52, '0x00531D80': 8, '0x00531D90': 11, '0x00532350': 16, '0x00532196': 52, '0x0040E9B0': 16, '0x0040EA20': 16, '0x0041F9F0': 5, '0x0041FDF0': 5, '0x00532480': 5, '0x00532500': 5}
ROUTES=[('0x0041D1F0', 98, 'code', '??1ExplicitArchiveReleaseObservation@@QAE@XZ', ['0x00655465', '0x00000000', '0x00000000', '0x00657138', '0x0041D9F0', '0x0041D930', '0x00000000']), ('0x00412E50', 83, 'code', '??1ExplicitSharedReleaseObservation@@QAE@XZ', ['0x006550A0', '0x00000000', '0x00000000', '0x0040AE40', '0x00000000']), ('0x00531CE0', 153, 'code', '?clear@?$list@UCharacterReleaseValueObservation@@V?$allocator@UCharacterReleaseValueObservation@@@std@@@std@@QAEXXZ', ['0x00531D80', '0x00531D80', '0x00531D90', '0x00531D80', '0x005320F0', '0x005320D0']), ('0x00531C40', 19, 'code', '??1?$list@UCharacterReleaseValueObservation@@V?$allocator@UCharacterReleaseValueObservation@@@std@@@std@@QAE@XZ', ['0x00532010']), ('0x0065545A', 21, 'eh-code', '__ehhandler$??1ExplicitArchiveReleaseObservation@@QAE@XZ', ['0x0041D930', '0x006685DC', '0x006407B8']), ('0x0041D9F0', 153, 'code', '?clear@?$list@UArchiveReleaseValueObservation@@V?$allocator@UArchiveReleaseValueObservation@@@std@@@std@@QAEXXZ', ['0x0041E100', '0x0041E100', '0x0041E110', '0x0041E100', '0x0041E360', '0x0041E340']), ('0x0041D930', 19, 'code', '??1?$list@UArchiveReleaseValueObservation@@V?$allocator@UArchiveReleaseValueObservation@@@std@@@std@@QAE@XZ', ['0x0041E280']), ('0x00655095', 21, 'eh-code', '__ehhandler$??1ExplicitSharedReleaseObservation@@QAE@XZ', ['0x0040AE40', '0x0066828C', '0x006407B8']), ('0x00531D80', 8, 'code', '?_Nextnode@?$list@UCharacterReleaseValueObservation@@V?$allocator@UCharacterReleaseValueObservation@@@std@@@std@@KAAAPAU_Node@?$_List_nod@UCharacterReleaseValueObservation@@V?$allocator@UCharacterReleaseValueObservation@@@std@@@2@PAU342@@Z', []), ('0x00531D90', 11, 'code', '?_Prevnode@?$list@UCharacterReleaseValueObservation@@V?$allocator@UCharacterReleaseValueObservation@@@std@@@std@@KAAAPAU_Node@?$_List_nod@UCharacterReleaseValueObservation@@V?$allocator@UCharacterReleaseValueObservation@@@std@@@2@PAU342@@Z', []), ('0x005320F0', 25, 'code', '?destroy@?$allocator@U_Node@?$_List_nod@UCharacterReleaseValueObservation@@V?$allocator@UCharacterReleaseValueObservation@@@std@@@std@@@std@@QAEXPAU_Node@?$_List_nod@UCharacterReleaseValueObservation@@V?$allocator@UCharacterReleaseValueObservation@@@std@@@2@@Z', ['0x00532480']), ('0x005320D0', 25, 'code', '?deallocate@?$allocator@U_Node@?$_List_nod@UCharacterReleaseValueObservation@@V?$allocator@UCharacterReleaseValueObservation@@@std@@@std@@@std@@QAEXPAU_Node@?$_List_nod@UCharacterReleaseValueObservation@@V?$allocator@UCharacterReleaseValueObservation@@@std@@@2@I@Z', ['0x00640F15']), ('0x00532010', 100, 'code', '?_Tidy@?$list@UCharacterReleaseValueObservation@@V?$allocator@UCharacterReleaseValueObservation@@@std@@@std@@IAEXXZ', ['0x00531CE0', '0x00531D80', '0x005322E0', '0x00531D90', '0x005322E0', '0x005320D0']), ('0x006685D4', 36, 'state-data', '$T6851', ['0x0065545A', '0x006685D4']), ('0x0041E100', 8, 'code', '?_Nextnode@?$list@UArchiveReleaseValueObservation@@V?$allocator@UArchiveReleaseValueObservation@@@std@@@std@@KAAAPAU_Node@?$_List_nod@UArchiveReleaseValueObservation@@V?$allocator@UArchiveReleaseValueObservation@@@std@@@2@PAU342@@Z', []), ('0x0041E110', 11, 'code', '?_Prevnode@?$list@UArchiveReleaseValueObservation@@V?$allocator@UArchiveReleaseValueObservation@@@std@@@std@@KAAAPAU_Node@?$_List_nod@UArchiveReleaseValueObservation@@V?$allocator@UArchiveReleaseValueObservation@@@std@@@2@PAU342@@Z', []), ('0x0041E360', 25, 'code', '?destroy@?$allocator@U_Node@?$_List_nod@UArchiveReleaseValueObservation@@V?$allocator@UArchiveReleaseValueObservation@@@std@@@std@@@std@@QAEXPAU_Node@?$_List_nod@UArchiveReleaseValueObservation@@V?$allocator@UArchiveReleaseValueObservation@@@std@@@2@@Z', ['0x0041F9F0']), ('0x0041E340', 25, 'code', '?deallocate@?$allocator@U_Node@?$_List_nod@UArchiveReleaseValueObservation@@V?$allocator@UArchiveReleaseValueObservation@@@std@@@std@@@std@@QAEXPAU_Node@?$_List_nod@UArchiveReleaseValueObservation@@V?$allocator@UArchiveReleaseValueObservation@@@std@@@2@I@Z', ['0x00640F15']), ('0x0041E280', 100, 'code', '?_Tidy@?$list@UArchiveReleaseValueObservation@@V?$allocator@UArchiveReleaseValueObservation@@@std@@@std@@IAEXXZ', ['0x0041D9F0', '0x0041E100', '0x0041F130', '0x0041E110', '0x0041F130', '0x0041E340']), ('0x00668284', 36, 'state-data', '$T6873', ['0x00655095', '0x00668284']), ('0x00532480', 5, 'code', '??$_Destroy@U_Node@?$_List_nod@UCharacterReleaseValueObservation@@V?$allocator@UCharacterReleaseValueObservation@@@std@@@std@@@std@@YAXPAU_Node@?$_List_nod@UCharacterReleaseValueObservation@@V?$allocator@UCharacterReleaseValueObservation@@@std@@@0@@Z', []), ('0x005322E0', 25, 'code', '?destroy@?$allocator@PAU_Node@?$_List_nod@UCharacterReleaseValueObservation@@V?$allocator@UCharacterReleaseValueObservation@@@std@@@std@@@std@@QAEXPAPAU_Node@?$_List_nod@UCharacterReleaseValueObservation@@V?$allocator@UCharacterReleaseValueObservation@@@std@@@2@@Z', ['0x00532500']), ('0x0041F9F0', 5, 'code', '??$_Destroy@U_Node@?$_List_nod@UArchiveReleaseValueObservation@@V?$allocator@UArchiveReleaseValueObservation@@@std@@@std@@@std@@YAXPAU_Node@?$_List_nod@UArchiveReleaseValueObservation@@V?$allocator@UArchiveReleaseValueObservation@@@std@@@0@@Z', []), ('0x0041F130', 25, 'code', '?destroy@?$allocator@PAU_Node@?$_List_nod@UArchiveReleaseValueObservation@@V?$allocator@UArchiveReleaseValueObservation@@@std@@@std@@@std@@QAEXPAPAU_Node@?$_List_nod@UArchiveReleaseValueObservation@@V?$allocator@UArchiveReleaseValueObservation@@@std@@@2@@Z', ['0x0041FDF0']), ('0x00532500', 5, 'code', '??$_Destroy@PAU_Node@?$_List_nod@UCharacterReleaseValueObservation@@V?$allocator@UCharacterReleaseValueObservation@@@std@@@std@@@std@@YAXPAPAU_Node@?$_List_nod@UCharacterReleaseValueObservation@@V?$allocator@UCharacterReleaseValueObservation@@@std@@@0@@Z', []), ('0x0041FDF0', 5, 'code', '??$_Destroy@PAU_Node@?$_List_nod@UArchiveReleaseValueObservation@@V?$allocator@UArchiveReleaseValueObservation@@@std@@@std@@@std@@YAXPAPAU_Node@?$_List_nod@UArchiveReleaseValueObservation@@V?$allocator@UArchiveReleaseValueObservation@@@std@@@0@@Z', []), ('0x0041D930', 19, 'code', '?finish@OrdinaryArchiveTidyObservation@@QAEXXZ', ['0x0041E280']), ('0x00531C40', 19, 'code', '?finish@OrdinaryCharacterTidyObservation@@QAEXXZ', ['0x00532010'])]
ALTERNATIVE_CALLS=[['??1?$list@UArchiveReleaseValueObservation@@V?$allocator@UArchiveReleaseValueObservation@@@std@@@std@@QAE@XZ'], ['??1TextureReleaseObservation@@QAE@XZ'], ['?clear@?$list@UCharacterReleaseValueObservation@@V?$allocator@UCharacterReleaseValueObservation@@@std@@@std@@QAEXXZ', '??1?$list@UCharacterReleaseValueObservation@@V?$allocator@UCharacterReleaseValueObservation@@@std@@@std@@QAE@XZ', '??1ReleaseBaseObservation@@QAE@XZ'], ['??1?$list@UCharacterReleaseValueObservation@@V?$allocator@UCharacterReleaseValueObservation@@@std@@@std@@QAE@XZ', '??1ReleaseBaseObservation@@QAE@XZ']]


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
    if (m['evidence_id']!='R175' or m['target_sha256']!=PRIOR.manifest()['target_sha256']
            or m['probe']!='probes/VC7ResourceReleasePolicies.cpp' or m['profile']!=SDK.PROFILE
            or len(m['headers'])!=28 or len(m['functions'])!=13 or {r['address']:r['size'] for r in m['functions']}!=KEYS
            or len(m['controls'])!=28 or sum(r['size'] for r in m['controls'])!=1085
            or sum(len(r['bindings']) for r in m['controls'])!=56 or len(m['emission'])!=52
            or sum(r['size'] for r in m['emission'])!=1858 or len(m['snapshots'])!=68 or len(m['retained'])!=5
            or m['layout'] not in m['emission'] or m['layout']['size']!=44 or m['layout_values']!=LAYOUT
            or m['external']!=EXTERNAL or m['protected']!=PROTECTED):
        raise ValueError('resource release loses bounded whole source/field/emission/layout scope')
    mutable={'proposed_name','module','status','owner','evidence','notes'}
    for r in m['functions']:
        a=r['address'];old,new=r['original_function'],r['accepted_function'];decision='authored' if a in AUTHORED else 'library';owner='ResourceReleasePolicy' if a in AUTHORED else 'VC7STL'
        confidence='complete-explicit-resource-policy-and-whole-lifetime-controls' if a in AUTHORED else 'complete-vc7-list-cleanup-graph-and-whole-explicit-game-policy'
        if (r['decision']!=decision or r['original_origin']['origin']!='unknown' or old['address']!=a or int(old['size'])!=r['size']
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['module']!=owner or new['status']!=('unclassified' if a in AUTHORED else 'excluded') or new['owner']!=decision
                or new['source_file'] or new['signature'] or new['calling_convention'] or new['match_percent']!='0.00'
                or r['accepted_origin']!=dict(address=a,origin=decision,subsystem=owner,disposition='authored' if a in AUTHORED else 'exclude',confidence=confidence,evidence_id='R175') or not r['witnesses']):
            raise ValueError('resource release loses independent owner or adds false source/private ABI/exact credit')
        if a in AUTHORED and r['accepted_authored_record']!=dict(address=a,size=str(r['size']),body_sha256=r['body_sha256'],inferred_role=new['proposed_name'],return_count=str(r['cfg'][0]),internal_branch_count=str(r['cfg'][1]),external_branch_count='0',evidence_id='R175'):
            raise ValueError('resource release loses entire accepted authored evidence')
        if a=='0x0052D020':
            if 'symbol' in r:raise ValueError('character release falsely claims source-byte reproduction')
        else:
            control=next(x for x in m['controls'][:26] if x['address']==a)
            if r['symbol']!=control['source_definition']['symbol'] or r['body_sha256']!=control['body_sha256'] or r['cfg']!=control['cfg']:
                raise ValueError('resource release replaces its entire actual defining source')
    actual=[]
    for i,r in enumerate(m['controls']):
        ss,d=r['section'],r['source_definition'];actual.append((r['address'],r['size'],r['kind'],d['symbol'],[b['target_address'] for b in r['bindings']]))
        if (ss not in m['emission'] or ss['size']!=r['size'] or d not in ss['definitions']
                or ss['source_sha256']!=r['source_sha256'] or len(ss['fields'])!=len(r['bindings'])
                or r['kind']=='code' and (d['offset'] or d['type']!=32 or d['storage']!=2)):
            raise ValueError('resource release slices full defining source or substitutes owner')
        for f,b in zip(ss['fields'],r['bindings']):
            if b!=dict(offset=f['offset'],type=f['type'],symbol=f['symbol']['symbol'],addend=f['addend'],target_address=b['target_address']) or f['type'] not in ('REL32','DIR32') or f['offset']+4>r['size']:
                raise ValueError('resource release drops, substitutes or masks a real field')
    if actual!=ROUTES:raise ValueError('resource release overrides actual closed source/ordinary/EH routes')
    if [(r['address'],r['size'],r['target_size'],r['role']) for r in m['alternatives']]!=[
            ('0x0041D1F0',22,98,'whole-implicit-release-negative'),('0x00412E50',22,83,'whole-implicit-release-negative'),
            ('0x0052D020',99,105,'whole-small-explicit-order-control'),('0x0052D020',75,105,'whole-small-implicit-order-control')]:
        raise ValueError('resource release loses whole implicit/explicit alternatives')
    for r,calls in zip(m['alternatives'],ALTERNATIVE_CALLS):
        ss,d=r['section'],r['source_definition']
        if (ss not in m['emission'] or ss['size']!=r['size'] or ss['source_sha256']!=r['source_sha256'] or d not in ss['definitions']
                or d['offset'] or d['type']!=32 or d['storage']!=2 or r['call_symbols']!=calls
                or [f['symbol']['symbol'] for f in ss['fields'] if f['type']=='REL32']!=calls or not r['witnesses']):
            raise ValueError('resource release replaces whole lifetime order/implicit fields')
    snapshots={r['address']:r for r in m['snapshots']}
    for a,size in PROTECTED.items():
        r=snapshots.get(a)
        if not r or r['size']!=size or r['origin']['origin']!='unknown':raise ValueError('resource release resolves independent opaque ownership')
    if {r['address']:r['size'] for r in m['anchors']}!={'0x0040AE40':434,'0x00456910':588} or any(r['origin']['origin']!='authored' or r['record']['evidence_id']!=r['origin']['evidence_id'] for r in m['anchors']):
        raise ValueError('resource release loses full independent game release policies')
    if [(r['address'],r.get('collection')) for r in m['retained']]!=[('0x0041EF60','functions'),('0x00532110','functions'),('0x0041A110',None),('0x0041D8C0',None),('0x00531BD0',None)]:
        raise ValueError('resource release loses previous node/complete deleting evidence')
    if [r['handler_address'] for r in m['retained_frames']]!=['0x006550A0','0x00655465','0x006564E8'] or any(r['evidence_id']!='R020' for r in m['retained_frames']):
        raise ValueError('resource release loses original complete registered frames')
    if m['import_slot']!=dict(address='0x00657138',dll='KERNEL32.dll',name='CloseHandle') or m['selected_slot']['address']!='0x006598D0' or m['selected_slot']['size']!=4:
        raise ValueError('resource release substitutes actual import or expands selected slot')
    records={r['address']:r for r in m['functions']}
    required={'0x00412E50':[('0x00412E80','call','dword ptr [ecx + 8]'),('0x00412E90','call','0x40ae40')],
              '0x0041D1F0':[('0x0041D216','cmp','dword ptr [eax], 0'),('0x0041D219','je','0x41d227'),('0x0041D221','call','dword ptr [0x657138]'),('0x0041D22D','call','0x41d9f0'),('0x0041D23F','call','0x41d930')],
              '0x0052D020':[('0x0052D03F','mov','dword ptr [eax], 0x6598d0'),('0x0052D04F','add','ecx, 0xfec'),('0x0052D055','call','0x531ce0'),('0x0052D061','add','ecx, 0xfec'),('0x0052D067','call','0x531c40'),('0x0052D076','call','0x456910')]}
    for a,expected in required.items():
        observed={(r['site'],r['mnemonic'],r['operands']) for r in records[a]['witnesses']}
        if not set(expected)<=observed:raise ValueError('resource release loses actual explicit policy or destruction order')


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
    if {a for a,r in authored.items() if r['evidence_id']=='R175'}!=(set() if args.evidence_only else AUTHORED):raise ValueError('resource release authored extent registry differs')
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
    slot=m['selected_slot']
    if digest(c.pe_bytes_at(target,int(slot['address'],16),4))!=slot['body_sha256']:raise ValueError('resource release selected readonly slot differs')
    scratch=ROOT/'build/origin-resource-release-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as dirname:
        path=Path(dirname)/'ResourceReleasePolicies.obj';result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/m['probe']),str(path),*m['profile']],cwd=ROOT,capture_output=True,text=True)
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
            if r['kind']=='code':
                if extent.complete_aux_section_size(data,r['source_definition']['symbol'],c.coff_name)!=r['size']:raise ValueError('resource release full own primary AUX differs')
                if list(cfg.verify_body(actual,int(r['address'],16)))!=r['cfg']:raise ValueError('resource release full positive CFG differs')
            elif r['kind']=='eh-code':
                ins=list(decoder.disasm(actual,int(r['address'],16)))
                if sum(x.size for x in ins)!=r['size'] or r['size']!=21 or r['source_definition']['offset']!=11 or ins[-1].mnemonic!='jmp' or ins[-1].op_str!='0x6407b8':raise ValueError('resource release slices shared cleanup/handler carrier')
            elif r['kind']=='state-data':
                if r['size']!=36 or r['source_definition']['offset']!=8:raise ValueError('resource release slices full unwind/FuncInfo data')
            else:raise ValueError('resource release unknown defining source kind')
        for r in m['alternatives']:
            ss=r['section'];header=struct.unpack_from('<8sIIIIIIHHI',data,20+(ss['section']-1)*40);raw=data[header[4]:header[4]+header[3]]
            if len(raw)!=r['size'] or digest(raw)!=r['source_sha256'] or witnesses(raw,'0x00000000')!=r['witnesses'] or list(cfg.verify_body(raw,0))!=r['cfg']:raise ValueError('resource release whole source-order alternative differs')
            if r['role']=='whole-small-explicit-order-control':
                if extent.complete_aux_section_size(data,r['source_definition']['symbol'],c.coff_name)!=r['size']:raise ValueError('resource release explicit order control lacks full own AUX')
            else:module('resource_release_implicit','verify-game-parent-policy-origins.py').verify_implicit_extent(r,data,c.coff_name)
        raw,_=coff.readonly_section(data,m['layout']['section'],c.coff_name)
        if list(struct.unpack('<11I',raw))!=LAYOUT:raise ValueError('replay complete readonly layout differs')
    print('R175 origins OK: three entire explicit release policies / 286 bytes and ten whole SDK cleanup dependencies / 644 bytes; two whole custom policies and closed SDK/EH graph compare unmasked across 28 controls / 1085 bytes and 56 real fields; small99/75-byte character controls explain explicit/implicit order without source-byte credit; full22/22-byte implicit negatives; all52 cold ordinary sections /1858 bytes,28 actual SDK headers and whole44-byte layout; full R017/R045 contexts /1022 bytes, three original EH frames, five prior records and68 canonical/body snapshots preserved; genuine CloseHandle IAT verified; getters/destruction children remain unknown; exact stays60.')
    return 0


if __name__=='__main__':
    try:raise SystemExit(main())
    except (OSError,KeyError,IndexError,StopIteration,ValueError,struct.error,json.JSONDecodeError) as error:
        print('error: '+str(error),file=sys.stderr);raise SystemExit(1)
