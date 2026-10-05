#!/usr/bin/env python3
"""Reopen whole SDK CPU parents, subordinate EH entries and actual source ABI."""
from __future__ import annotations
import argparse
import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]
EVIDENCE = 'config/sdk-cpu-eh-origin-evidence.json'
MANIFEST_SHA256 = '9eaa1c1ae5d532e9982f9b582cb77b4f2a98839f5bd88eae078674576e54433c'
KEYS = {'0x00620B41': 165, '0x00620B7B': 12, '0x00620B87': 95, '0x00620BE6': 180}
ROLES = ['whole-library-parent', 'generated-catch-return-entry', 'library-parent-continuation', 'whole-library-caller']
CONFIDENCES = ['whole-pinned-sdk-cpu-parent-with-complete-eh-source-abi',
               'generated-catch-return-entry-in-complete-sdk-cpu-parent',
               'continuation-in-complete-sdk-cpu-parent',
               'whole-pinned-sdk-feature-policy-with-closed-cpu-eh-and-imports']


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT/'scripts'/filename)
    result = importlib.util.module_from_spec(spec); spec.loader.exec_module(result)
    return result


def digest(data):
    return hashlib.sha256(data).hexdigest()


def rows(path):
    with (ROOT/path).open() as stream:
        return list(csv.DictReader(stream))


def flow(raw, address, roots, sdk, external_tails=None):
    """Account for every instruction from independent normal/EH/resume entries."""
    decoder = sdk.capstone.Cs(sdk.capstone.CS_ARCH_X86, sdk.capstone.CS_MODE_32)
    decoder.detail = True; ins = list(decoder.disasm(bytes(raw), address))
    by = {i.address: i for i in ins}; tails = external_tails or {}
    if sum(i.size for i in ins) != len(raw) or any(address+r not in by for r in roots):
        raise ValueError('CPU whole code has incomplete decoding or a non-instruction entry')
    pending = [address+r for r in roots]; seen = set(); used = set()
    while pending:
        at = pending.pop()
        if at in seen: continue
        if at not in by: raise ValueError('CPU code falls through its full source extent')
        seen.add(at); i = by[at]
        if i.group(sdk.capstone.CS_GRP_RET): continue
        if i.group(sdk.capstone.CS_GRP_JUMP):
            if len(i.operands) != 1 or i.operands[0].type != sdk.capstone.x86.X86_OP_IMM:
                raise ValueError('CPU code contains an unresolved branch')
            dest = i.operands[0].imm
            if dest in by: pending.append(dest)
            elif i.mnemonic == 'jmp' and tails.get(at+i.imm_offset) == dest:
                used.add(at+i.imm_offset)
            else: raise ValueError('CPU code contains an unbound external branch')
            if i.mnemonic == 'jmp': continue
        pending.append(at+i.size)
    if seen != set(by) or used != set(tails):
        raise ValueError('CPU code hides unreachable instructions or unproved tails')
    return dict(roots=roots, instruction_count=len(ins),
                returns=[i.address-address for i in ins if i.group(sdk.capstone.CS_GRP_RET)],
                witnesses=[dict(offset=i.address-address, mnemonic=i.mnemonic, operands=i.op_str) for i in ins])


def link(raw, fields, bindings, address, catalog):
    if len(fields) != len(bindings): raise ValueError('CPU field coverage differs')
    linked = bytearray(raw); calls = {}; constants = {}; seen = set()
    for f,b in zip(fields,bindings):
        off=f['offset']; name=f['symbol']['symbol']; dest=int(b['target_address'],16)
        if (off in seen or off < 0 or off+4 > len(raw) or f['addend']
                or struct.unpack_from('<I',raw,off)[0] or b['field'] != f or catalog.get(name) != dest):
            raise ValueError('CPU binding overrides an actual source field/definition')
        seen.add(off)
        if f['type']=='REL32':
            if off < 1 or raw[off-1] not in (0xe8,0xe9): raise ValueError('CPU REL32 is not a direct code transfer')
            value=(dest-address-off-4)&0xffffffff; calls[address+off]=dest
        elif f['type']=='DIR32': value=dest; constants[address+off]=dest
        else: raise ValueError('CPU unsupported real field')
        struct.pack_into('<I',linked,off,value)
    return linked,calls,constants


def verify_plan(m):
    if (m['evidence_id'] != 'R190' or len(m['functions']) != 4
            or {r['address']:r['size'] for r in m['functions']} != KEYS
            or [r['role'] for r in m['functions']] != ROLES
            or [r['source']['size'] for r in m['sections']] != [165,180,13,10,80]
            or [len(r['source']['fields']) for r in m['sections']] != [5,5,0,2,4]
            or [r['address'] for r in m['sections']] != ['0x00620B41','0x00620BE6','0x0065DE98','0x00656CC6','0x0066A918']
            or m['sections'][0]['flow']['roots'] != [0,58,76]
            or m['absolute']['definition'] != dict(symbol='__except_list', offset=0, section=-1, type=0, storage=2)
            or len(m['headers']) != 85 or m['layout']['values'] != [4,6,7,10,148,4,8,12,16]
            or m['profile'] != ['/O1','/Ob0','/Gy','/GR-','/GX','/Zi','/GS','/showIncludes']
            or [(r['address'],r['size']) for r in m['anchors']] != [('0x00620B09',56),('0x006425A4',31),('0x006407B8',54),('0x006460BB',162)]
            or [(r['iat_address'],r['dll'].upper(),r['name']) for r in m['imports']] != [('0x00657090','KERNEL32.DLL','GetVersionExA'),('0x006570C0','KERNEL32.DLL','IsProcessorFeaturePresent')]
            or [r['size'] for r in m['emission']] != [36,58,10,80,54,10,80]
            or [len(r['fields']) for r in m['emission']] != [0,5,2,4,5,2,4]
            or m['comparison'] != 'origin-only-whole-source-and-subordinate-labels-no-exact-credit'):
        raise ValueError('CPU/EH scope loses whole parents, subordinate entries, actual ABI or controls')
    mutable={'proposed_name','module','status','owner','evidence','notes'}
    for i,r in enumerate(m['functions']):
        a=r['address']; old=r['original_function']; new=r['accepted_function']; decision='compiler' if i==1 else 'library'
        allowed=mutable | ({'size','span_end'} if i==0 else set())
        if (r['original_origin']['origin'] != 'unknown'
                or {k:v for k,v in old.items() if k not in allowed} != {k:v for k,v in new.items() if k not in allowed}
                or int(old['size']) != [58,12,95,180][i]
                or int(new['size']) != r['size'] or int(new['span_end'],16) != int(a,16)+r['size']-1
                or new['status']!='excluded' or new['owner']!=decision or new['evidence']!='R190'
                or new['source_file'] or new['signature'] or new['calling_convention'] or new['match_percent']!='0.00'
                or r['accepted_origin'] != dict(address=a,origin=decision,subsystem='D3DX8' if decision=='library' else 'VC7EH',disposition='exclude',confidence=CONFIDENCES[i],evidence_id='R190')):
            raise ValueError('CPU origin changes unrelated extent/ABI or grants duplicate/source/exact credit')
    parent=m['sections'][0]['source']; defs=parent['definitions']
    if (dict(symbol='?IsIntelSSEProcessor@@YAKXZ',offset=0,section=14,type=32,storage=3) not in defs
            or dict(symbol='$L48085',offset=58,section=14,type=0,storage=6) not in defs
            or dict(symbol='$L48087',offset=76,section=14,type=0,storage=6) not in defs
            or any(d['type']==32 and d['offset'] for d in defs)
            or [(f['offset'],f['symbol']['symbol']) for f in parent['fields']] != [(1,'$L48090'),(6,'__EH_prolog'),(25,'??_C@_0N@BDDFKIGD@GenuineIntel?$AA@'),(65,'$L48087'),(156,'__except_list')]):
        raise ValueError('CPU primary/catch/resume source definitions or whole fields differ')
    catalog=m['catalog']
    required={'$L48085':'0x00620B7B','$L48087':'0x00620B8D','$L48090':'0x00656CC6',
              '$T48093':'0x0066A918','$T48095':'0x0066A928','$T48094':'0x0066A938','$T48089':'0x0066A94C',
              '__except_list':'0x00000000','___CxxFrameHandler':'0x006407B8','__EH_prolog':'0x006425A4',
              '?IsIntelSSEProcessor@@YAKXZ':'0x00620B41','?isX3Dprocessor@@YAHXZ':'0x00620B09',
              '__imp__GetVersionExA@4':'0x00657090','__imp__IsProcessorFeaturePresent@4':'0x006570C0',
              '??_C@_0N@BDDFKIGD@GenuineIntel?$AA@':'0x0065DE98'}
    if catalog != required: raise ValueError('CPU actual local/absolute/import/owner catalog differs')
    for r in m['sections']:
        if len(r['bindings']) != len(r['source']['fields']): raise ValueError('CPU drops a genuine field')
        for f,b in zip(r['source']['fields'],r['bindings']):
            if b != dict(field=f,target_address=catalog[f['symbol']['symbol']]): raise ValueError('CPU field is bound to an unrelated owner')
    if m['sections'][4]['topology'] != {'unwind_map':[0,16], 'handler_type':[16,16], 'try_map':[32,20], 'func_info':[52,28]}:
        raise ValueError('CPU full EH topology is truncated')
    if (m['anchors'][1]['origin']['origin']!='compiler'
            or any(r['origin']['origin']!='library' for i,r in enumerate(m['anchors']) if i!=1)
            or any(len(r['fields'])!=len(r['destinations']) for r in m['anchors'])):
        raise ValueError('CPU changes independently accepted compiler/library owners or drops fields')


def check_eh(raw):
    words=list(struct.unpack('<20I',raw))
    if words != [0xffffffff,0,0xffffffff,0,0,0,0,0x620b7b,0,0,1,1,0x66a928,0x19930520,2,0x66a918,1,0x66a938,0,0]:
        raise ValueError('CPU whole catch-all/state/try/unwind/FuncInfo topology differs')


def check_generated(data, emission, sdk):
    """The two explicit return policies retain the same generated resume ABI."""
    for number,catch,resume in [(4,34,40),(9,31,37)]:
        r=next(r for r in emission if r['section']==number)
        labels=[d for d in r['definitions'] if d['offset']==catch and d['type']==32 and d['storage']==3]
        fields=[f for f in r['fields'] if f['offset']==catch+1]
        if (len(labels)!=1 or len(fields)!=1 or fields[0]['type']!='DIR32'
                or fields[0]['symbol']['offset']!=resume or fields[0]['symbol']['section']!=number
                or fields[0]['symbol']['type'] or fields[0]['symbol']['storage']!=3):
            raise ValueError('CPU natural catch loses an actual generated return/resume label')
        h=struct.unpack_from('<8sIIIIIIHHI',data,20+(number-1)*40);raw=data[h[4]:h[4]+h[3]]
        result=flow(raw,0,[0,catch,resume],sdk)
        stub=[i for i in result['witnesses'] if catch<=i['offset']<resume]
        if [(i['mnemonic'],i['operands']) for i in stub]!=[('mov','eax, 0'),('ret','')]:
            raise ValueError('CPU generated catch is confused with explicit return policy')
        policy=next(i for i in result['witnesses'] if i['offset']==resume)
        expected=('mov','eax, dword ptr [ebp + 8]') if number==4 else ('xor','eax, eax')
        if (policy['mnemonic'],policy['operands'])!=expected:
            raise ValueError('CPU natural saved-flag/fixed-zero policies have been conflated')


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args()
    m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes()) != MANIFEST_SHA256: raise ValueError('CPU immutable manifest differs')
    for path,h in [(m['probe'],m['probe_sha256']),*m['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes()) != h: raise ValueError('CPU retained source/evidence changes: '+path)
    c=module('cpu_target','compare-coff-function.py'); rt=module('cpu_archive','verify-runtime-origins.py')
    coff=module('cpu_coff','coff_data.py');sdk=module('cpu_sdk','verify-sdk-origins.py')
    api=module('cpu_headers','verify-sdk-interface-origins.py')
    inventory=module('cpu_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    target=c.verified_target(); functions={r['address']:r for r in rows('config/functions.csv')};origins={r['address']:r for r in rows('config/function-origins.csv')}
    if digest(target)!=m['target_sha256']: raise ValueError('CPU target identity differs')
    state='original' if args.evidence_only else 'accepted'
    for r in m['functions']:
        a=r['address']
        if functions[a]!=r[state+'_function'] or origins[a]!=r[state+'_origin']: raise ValueError('CPU canonical decision differs')
    if {a for a in functions if 0x620b41<int(a,16)<0x620be6} != {'0x00620B7B','0x00620B87'}:
        raise ValueError('CPU full extent hides an unreviewed inventoried entry')
    archives={}
    for path,h in m['archive_sha256'].items():
        b=(ROOT/path).read_bytes()
        if digest(b)!=h: raise ValueError('CPU source archive identity differs')
        archives[path]={o:(n,b) for o,n,b in rt.archive_members(b)}
    catalog={k:int(v,16) for k,v in m['catalog'].items()}
    member=m['member'];name,body=archives[member['archive']][member['member_offset']]
    if name!=member['member'] or digest(body)!=member['member_sha256']: raise ValueError('CPU SDK actual source owner differs')
    ordinary={r['section']:r for r in inventory(body,c,coff)}
    scratch=ROOT/'build/origin-sdk-cpu-eh-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj=Path(temp)/'Cpu.obj';obj.write_bytes(body)
        for r in m['sections']:
            source=r['source'];number=source['section'];address=int(r['address'],16)
            if ordinary[number]!=source: raise ValueError('CPU drops an entire ordinary source section/definition/field')
            h=struct.unpack_from('<8sIIIIIIHHI',body,20+(number-1)*40);raw=body[h[4]:h[4]+h[3]]
            linked,calls,constants=link(raw,source['fields'],r['bindings'],address,catalog)
            if linked!=c.pe_bytes_at(target,address,len(raw)) or digest(linked)!=r['body_sha256']: raise ValueError('CPU whole unmasked source comparison differs')
            if number in (14,19):
                symbol='?IsIntelSSEProcessor@@YAKXZ' if number==14 else '?D3DXIsProcessorFeaturePresent@@YAHI@Z'
                if sdk.complete_comdat_size(body,symbol,c.coff_name)!=len(raw): raise ValueError('CPU function loses independently derived COMDAT')
                if sdk.verify_control_flow(linked,address,calls,constants)!=r['indirect_calls']: raise ValueError('CPU typed code fields differ')
            if 'flow' in r:
                tails=calls if number==16 else {}
                if flow(linked,address,r['flow']['roots'],sdk,tails)!=r['flow']: raise ValueError('CPU complete normal/EH/resume CFG differs')
            if number==17: check_eh(linked)
        absolute=m['absolute'];name,b=archives[absolute['archive']][absolute['member_offset']]
        if name!=absolute['member'] or digest(b)!=absolute['member_sha256'] or [d for d in coff.parse_symbols(b,c.coff_name)[1] if d['symbol']=='__except_list' and d['section']!=0] != [absolute['definition']]:
            raise ValueError('CPU FS displacement lacks actual absolute CRT definition')
        prior=json.loads((ROOT/'config/standard-exception-origin-evidence.json').read_text())
        for r in m['anchors']:
            a=r['address']; name,b=archives[r['archive']][r['member_offset']]
            if name!=r['member'] or digest(b)!=r['member_sha256'] or functions[a]!=r['function'] or origins[a]!=r['origin']: raise ValueError('CPU changes an accepted runtime/SDK owner')
            obj.write_bytes(b);raw,fields=c.object_function(obj,r['symbol'],r['size'])
            if fields!=r['fields'] or digest(raw)!=r['source_sha256']: raise ValueError('CPU retained complete source/fields differ')
            if a=='0x00620B09' and sdk.complete_comdat_size(b,r['symbol'],c.coff_name)!=r['size']: raise ValueError('CPU retained isX3D source extent differs')
            if a in ('0x006407B8','0x006460BB'):
                old=next(q for q in [*prior['functions'],*prior['anchors']] if q['address']==a)
                if (old['member_offset']!=r['member_offset'] or old['size']!=r['size'] or old['source_sha256']!=r['source_sha256']
                        or old['body_sha256']!=r['body_sha256'] or [f['target_address'] for f in old['relocation_bindings']]!=r['destinations']):
                    raise ValueError('CPU retained EH linkage no longer has independent R142 evidence')
            linked=bytearray(raw)
            for f,dest in zip(fields,r['destinations']):
                off=f['offset'];value=(int(dest,16)-int(a,16)-off-4)&0xffffffff if f['type']=='REL32' else int(dest,16)
                struct.pack_into('<I',linked,off,value)
            if linked!=c.pe_bytes_at(target,int(a,16),r['size']) or digest(linked)!=r['body_sha256']: raise ValueError('CPU retained whole owner comparison differs')
        imports=module('cpu_imports','verify-import-origins.py').pe_imports(target,c)
        for r in m['imports']:
            if list(imports[int(r['iat_address'],16)])!=r['record']: raise ValueError('CPU actual independently parsed PE import differs')
        result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/m['probe']),str(obj),*m['profile']],cwd=ROOT,capture_output=True,text=True)
        if result.returncode or api.included_headers(result.stdout+result.stderr)!=m['headers']: raise ValueError('CPU cold natural C++/actual SDK headers differ')
        emitted=obj.read_bytes()
        if inventory(emitted,c,coff)!=m['emission']: raise ValueError('CPU ordinary generated code/EH/data emission differs')
        check_generated(emitted,m['emission'],sdk)
        raw,_=coff.readonly_section(emitted,m['layout']['section'],c.coff_name)
        if list(struct.unpack('<9I',raw))!=m['layout']['values']: raise ValueError('CPU complete SDK feature/OSVERSIONINFOA layout differs')
    print('R190 origins OK: four inventory decisions; two whole library parents /345 bytes; one generated catch12 and one continuation95 are subordinate overlapping entries; complete helper10, EH80 and literal13; all16 real fields and actual absolute FS/import/runtime owners; seven whole natural code/EH/data controls /328 bytes,85 headers; no source/ABI/mapping or exact credit.')
    return 0


if __name__=='__main__':
    try: raise SystemExit(main())
    except (ValueError,OSError,KeyError,struct.error) as exc:
        print('SDK CPU/EH verification failed: '+str(exc),file=sys.stderr);raise SystemExit(1)
