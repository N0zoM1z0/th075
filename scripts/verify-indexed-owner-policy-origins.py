#!/usr/bin/env python3
"""Replay full custom copies and owner operations without truncating dependencies."""
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
spec=importlib.util.spec_from_file_location('indexed_owner_prior',ROOT/'scripts/verify-file-resource-policy-origins.py')
PRIOR=importlib.util.module_from_spec(spec);spec.loader.exec_module(PRIOR)
SDK=PRIOR.SDK;module=PRIOR.module;digest=PRIOR.digest
EVIDENCE='config/indexed-owner-policy-origin-evidence.json'
MANIFEST_SHA256='d425763795da7d53ca1d403d8576471bd85501b6fc76f0c3355e002b546b59dc'
KEYS={'0x00416E20':84,'0x00416E80':85,'0x004204D0':84,'0x0041D190':90}
OWNERS={'0x00416E20':'ProfileSelection','0x00416E80':'ProfileSelection','0x004204D0':'FighterResources','0x0041D190':'DataArchive'}
LAYOUT=[8,8,4,20,20,20,108,12,16,16]
PENDING={'0x0041D8F0':56,'0x0041E330':14,'0x0041E2F0':53,'0x0041E1A0':143}
POLICIES=[('store-eight-bytes',31,'?store@IndexedWorkingObservation@@QAEXAAUIndexedEightByteObservation@@@Z',False),('load-eight-bytes',31,'?load@IndexedWorkingObservation@@QAEXABUIndexedEightByteObservation@@@Z',False),('explicit-queue-clear',72,'??1ExplicitIndexedQueueOwner@@QAE@XZ',False),('implicit-queue-destruction',19,'??1ImplicitIndexedQueueOwner@@QAE@XZ',True),('explicit-archive-defaults',90,'??0ExplicitIndexedArchiveOwner@@QAE@XZ',False),('implicit-archive-construction',25,'??0ImplicitIndexedArchiveOwner@@QAE@XZ',True)]

def manifest():return json.loads((ROOT/EVIDENCE).read_text())

def accepted_pending_snapshot(snapshot,function,origin):
    if function['address'] not in {'0x0041D8F0','0x0041E2F0','0x0041E1A0'}:return False
    return module('indexed_list_transition','verify-list-construction-origins.py').accepted_snapshot(snapshot,function,origin)

def verify_plan(m):
    if (m['evidence_id']!='R180' or m['target_sha256']!=PRIOR.manifest()['target_sha256']
            or m['probe']!='probes/VC7IndexedOwnerPolicies.cpp' or m['profile']!=SDK.PROFILE
            or len(m['functions'])!=4 or {r['address']:r['size'] for r in m['functions']}!=KEYS
            or len(m['policies'])!=6 or sum(r['size'] for r in m['policies'])!=268
            or len(m['emission'])!=61 or sum(r['size'] for r in m['emission'])!=2497 or len(m['headers'])!=29
            or len(m['snapshots'])!=157 or len({r['address'] for r in m['snapshots']})!=157
            or {r['address']:r['size'] for r in m['anchors']}!={'0x0042A180':315,'0x0042A340':541,'0x00456910':588,'0x0041CF80':245}
            or len(m['retained'])!=3 or len(m['frames'])!=2 or {r['handler_address'] for r in m['frames']}!={'0x00655566','0x00655450'}
            or m['layout'] not in m['emission'] or m['layout']['size']!=40 or m['layout_values']!=LAYOUT
            or m['protected']!=PRIOR.manifest()['protected'] or len(m['pending'])!=4 or {r['address']:r['size'] for r in m['pending']}!=PENDING):
        raise ValueError('indexed owner loses bounded full policy/source/context scope')
    mutable={'proposed_name','module','status','owner','evidence','notes'}
    for r in m['functions']:
        a=r['address'];old,new=r['original_function'],r['accepted_function'];owner=OWNERS[a]
        if (r['decision']!='authored' or r['original_origin']['origin']!='unknown' or old['address']!=a or int(old['size'])!=r['size']
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['module']!=owner or new['owner']!='authored' or new['status']!='unclassified'
                or new['source_file'] or new['calling_convention'] or new['signature'] or new['match_percent']!='0.00' or 'symbol' in r
                or r['accepted_origin']!=dict(address=a,origin='authored',subsystem=owner,disposition='authored',confidence='complete-custom-indexed-copy-and-explicit-owner-policy-context',evidence_id='R180')
                or r['accepted_authored_record']!=dict(address=a,size=str(r['size']),body_sha256=r['body_sha256'],inferred_role=new['proposed_name'],return_count=str(r['cfg'][0]),internal_branch_count=str(r['cfg'][1]),external_branch_count='0',evidence_id='R180')):
            raise ValueError('indexed owner loses independent ownership or adds false source/private ABI/exact credit')
    records={r['address']:r for r in m['functions']}
    expected_calls={'0x00416E20':['0x640f20'],'0x00416E80':['0x640f20'],'0x004204D0':['0x4216d0','0x421530'],'0x0041D190':['0x41d8f0','0x41d9f0']}
    for a,expected in expected_calls.items():
        if [r['operands'] for r in records[a]['witnesses'] if r['mnemonic']=='call']!=expected:raise ValueError('indexed owner loses actual copy/clear/construction order')
    required={'0x00416E20':[('0x00416E27','push','8'),('0x00416E2C','add','eax, 0x16a94'),('0x00416E35','movsx','edx, byte ptr [ecx + 0x16ac4]'),('0x00416E3C','imul','edx, edx, 0x17f0'),('0x00416E48','movsx','ecx, byte ptr [eax + 0x16ac5]'),('0x00416E4F','imul','ecx, ecx, 0x5fc'),('0x00416E57','movsx','eax, byte ptr [ebp + 8]'),('0x00416E5B','shl','eax, 4'),('0x00416E5E','lea','ecx, [edx + eax + 0x55c]')],
              '0x00416E80':[('0x00416E87','push','8'),('0x00416E8C','movsx','ecx, byte ptr [eax + 0x16ac4]'),('0x00416E93','imul','ecx, ecx, 0x17f0'),('0x00416E9F','movsx','eax, byte ptr [edx + 0x16ac5]'),('0x00416EA6','imul','eax, eax, 0x5fc'),('0x00416EAE','movsx','edx, byte ptr [ebp + 8]'),('0x00416EB2','shl','edx, 4'),('0x00416EB5','lea','eax, [ecx + edx + 0x55c]'),('0x00416EC0','add','ecx, 0x16a94')],
              '0x004204D0':[('0x004204F6','add','ecx, 0x7d0'),('0x0042050B','add','ecx, 0x7d0')],
              '0x0041D190':[('0x0041D1AF','add','ecx, 4'),('0x0041D1C1','mov','dword ptr [eax], 0'),('0x0041D1CA','add','ecx, 4')]}
    for a,expected in required.items():
        if not set(expected)<={(r['site'],r['mnemonic'],r['operands']) for r in records[a]['witnesses']}:raise ValueError('indexed owner loses signed selectors/strides/direction or explicit owner operation')
    for r,(role,size,symbol,implicit) in zip(m['policies'],POLICIES):
        if (r['role'],r['size'],r['source_definition']['symbol'],r['implicit'])!=(role,size,symbol,implicit) or r['section'] not in m['emission'] or 'target_positive' in r:
            raise ValueError('indexed owner loses entire source-operation control or invents byte credit')
        if r['call_symbols']!=[q['symbol']['symbol'] for q in r['section']['fields'] if q['type']=='REL32']:raise ValueError('indexed owner source order loses real fields')
    p=m['policies'];clear='?clear@?$deque@UIndexedQueueValueObservation@@V?$allocator@UIndexedQueueValueObservation@@@std@@@std@@QAEXXZ'
    if p[0]['call_symbols']!=['_memcpy'] or p[1]['call_symbols']!=['_memcpy'] or p[2]['call_symbols']!=[clear]+p[3]['call_symbols'] or len(p[3]['call_symbols'])!=1:
        raise ValueError('indexed owner loses directional copy or explicit versus implicit queue cleanup')
    clear='?clear@?$list@UIndexedArchiveEntryObservation@@V?$allocator@UIndexedArchiveEntryObservation@@@std@@@std@@QAEXXZ'
    if p[4]['call_symbols']!=p[5]['call_symbols']+[clear] or len(p[5]['call_symbols'])!=1:raise ValueError('indexed owner loses explicit versus generated list construction')
    snapshots={r['address']:r for r in m['snapshots']}
    for a,size in m['protected'].items():
        if snapshots[a]['size']!=size or snapshots[a]['origin']['origin']!='unknown':raise ValueError('indexed owner changes protected opaque ownership')
    for r in m['pending']:
        a=r['address']
        if r['origin']['origin']!='unknown' or r['function']['owner'] or 'accepted_origin' in r:raise ValueError('indexed owner classifies unreconciled constructor dependency')
        tails=[dict(site='0x0041E22D',target='0x0041E264')] if a=='0x0041E1A0' else []
        if r['external_tails']!=tails or r['bounded_cfg']!=([0,0] if tails else [1,0]):raise ValueError('indexed owner hides pending node external tail')
    if ('0x0041E22D','jmp','0x41e264') not in {(r['site'],r['mnemonic'],r['operands']) for r in m['pending'][-1]['witnesses']}:
        raise ValueError('indexed owner credits convenient node prefix')

def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args();m=manifest();verify_plan(m)
    for path,expected in [(EVIDENCE,MANIFEST_SHA256),(m['probe'],m['probe_sha256']),*m['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes())!=expected:raise ValueError('indexed owner immutable source/prior evidence differs: '+path)
    c=module('indexed_target','compare-coff-function.py');coff=module('indexed_coff','coff_data.py');cfg=module('indexed_cfg','verify-authored-origins.py');extent=module('indexed_extent','verify-vendor-record-origins.py');target=c.verified_target();rows=cfg.rows
    functions={r['address']:r for r in rows('functions.csv')};origins={r['address']:r for r in rows('function-origins.csv')};authored={r['address']:r for r in rows('authored-origin-evidence.csv')};records={r['address']:r for r in m['functions']};decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    def witness(raw,a):return [dict(site=f'0x{x.address:08X}',mnemonic=x.mnemonic,operands=x.op_str) for x in decoder.disasm(raw,int(a,16))]
    if digest(target)!=m['target_sha256'] or {a for a,r in authored.items() if r['evidence_id']=='R180'}!=(set() if args.evidence_only else set(KEYS)):raise ValueError('indexed owner target/authored registry differs')
    for r in m['functions']:
        a=r['address'];SDK.check_ledger(r,functions[a],origins[a],args.evidence_only)
        if not args.evidence_only and authored[a]!=r['accepted_authored_record']:raise ValueError('indexed owner accepted authored record differs')
    for r in m['snapshots']:
        a=r['address']
        accepted_pending=False
        if a in records:SDK.check_ledger(records[a],functions[a],origins[a],args.evidence_only)
        elif functions[a]!=r['function'] or origins[a]!=r['origin']:
            accepted_pending=accepted_pending_snapshot(dict(function=r['function'],origin=r['origin']),functions[a],origins[a])
            if not accepted_pending:raise ValueError('indexed owner changes unrelated canonical context')
        if (int(functions[a]['size'])!=r['size'] and not accepted_pending) or digest(c.pe_bytes_at(target,int(a,16),r['size']))!=r['body_sha256']:raise ValueError('indexed owner entire target snapshot differs')
    for r in [*m['functions'],*m['anchors']]:
        a=r['address'];raw=c.pe_bytes_at(target,int(a,16),r['size'])
        if digest(raw)!=r['body_sha256'] or witness(raw,a)!=r['witnesses'] or list(cfg.verify_body(raw,int(a,16),r['switches'],lambda a,n:c.pe_bytes_at(target,a,n),r['direct_switches']))!=r['cfg']:raise ValueError('indexed owner whole policy/anchor/CFG differs')
        if any(int(a,16)<int(q,16)<int(a,16)+r['size'] for q in functions):raise ValueError('indexed owner extent contains another function')
        for file,key in [('authored-origin-switches.csv','switches'),('authored-origin-direct-switches.csv','direct_switches')]:
            if [q for q in rows(file) if q['address']==a]!=r[key]:raise ValueError('indexed owner original entire switch evidence differs')
        if 'record' in r and (authored[a]!=r['record'] or functions[a]!=r['function'] or origins[a]!=r['origin']):raise ValueError('indexed owner original whole authored anchor differs')
    bounded=module('indexed_bounded','verify-game-context-origins.py')
    for r in m['pending']:
        raw=c.pe_bytes_at(target,int(r['address'],16),r['size'])
        if witness(raw,r['address'])!=r['witnesses'] or bounded.verify_bounded_context(raw,int(r['address'],16),r['external_tails'])!=r['bounded_cfg']:raise ValueError('indexed owner unresolved entire context/tail differs')
    for r in m['retained']:
        path=ROOT/r['file'];inventory=json.loads(path.read_text())[r['collection']] if path.suffix=='.json' else rows(path.name)
        if r['record'] not in inventory:raise ValueError('indexed owner original full compiler/library record differs')
    eh=module('indexed_eh','compiler_eh.py')
    for frame in m['frames']:
        if frame not in rows('compiler-eh-frames.csv'):raise ValueError('indexed owner original full EH frame differs')
        eh.verify_frame(frame,lambda a,n:c.pe_bytes_at(target,a,n),lambda a,n:c.pe_bytes_at(target,a,n),{int(a,16) for a in functions})
    scratch=ROOT/'build/origin-indexed-owner-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as dirname:
        path=Path(dirname)/'IndexedOwnerPolicies.obj';result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/m['probe']),str(path),*m['profile']],cwd=ROOT,capture_output=True,text=True)
        if result.returncode or PRIOR.PRIOR.PRIOR.included_headers(result.stdout+result.stderr)!=m['headers']:raise ValueError('indexed owner cold source/actual include ownership differs')
        data=path.read_bytes()
        if SDK.PAIRED.BUFFER.inventory(data,c,coff)!=m['emission']:raise ValueError('indexed owner complete ordinary emission differs')
        for r in m['policies']:
            head=struct.unpack_from('<8sIIIIIIHHI',data,20+(r['section']['section']-1)*40);raw=data[head[4]:head[4]+head[3]]
            if len(raw)!=r['size'] or digest(raw)!=r['source_sha256'] or witness(raw,'0x00000000')!=r['witnesses'] or list(cfg.verify_body(raw,0))!=r['cfg']:raise ValueError('indexed owner whole source operation differs')
            if r['implicit']:module('indexed_generated','verify-game-parent-policy-origins.py').verify_implicit_extent(r,data,c.coff_name)
            elif extent.complete_aux_section_size(data,r['source_definition']['symbol'],c.coff_name)!=r['size']:raise ValueError('indexed owner loses own entire primary AUX')
        raw,_=coff.readonly_section(data,m['layout']['section'],c.coff_name)
        if list(struct.unpack('<10I',raw))!=LAYOUT:raise ValueError('indexed owner entire readonly source layout differs')
    print('R180 origins OK: four entire custom copy/owner policies /343 bytes; six whole small-owner operation/implicit controls /268 bytes with no target-byte-positive claim;61 ordinary sections /2497 bytes,29 SDK headers and40-byte layout;157 snapshots,40 protected unknowns,1689 bytes of whole authored anchors,three original library records and two full EH frames preserved; original pending observations retain every byte and external tail, permitting only exact complete R181 transitions;143-byte node prefix is never credited; no source/private ABI/mapping/exact credit, exact stays60.')
    return 0

if __name__=='__main__':
    try:raise SystemExit(main())
    except (OSError,KeyError,IndexError,StopIteration,ValueError,struct.error,json.JSONDecodeError) as error:
        print('error: '+str(error),file=sys.stderr);raise SystemExit(1)
