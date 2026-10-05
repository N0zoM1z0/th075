#!/usr/bin/env python3
"""Verify background animation counter callbacks; preserve six SDK lifetime alternatives."""
import argparse
import csv
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import tempfile

ROOT=Path(__file__).resolve().parents[1]

def module(name,filename):
    s=importlib.util.spec_from_file_location(name,ROOT/'scripts'/filename)
    v=importlib.util.module_from_spec(s);s.loader.exec_module(v);return v

SOURCE=module('counter_source','verify-vector-insertion-carrier-origins.py')
digest=SOURCE.digest
EVIDENCE='config/background-counter-origin-evidence.json'
MANIFEST_SHA256='494fbb61c77d06cdb21f97916909aa023e6bdb05703688feb13f491dc9512e37'
PLAN_DIGESTS={'evidence_id': 'c6966e83fedea2dccfb0501088f91d7518fc6826f305241b725821717bdf395a', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'comparison': '21be3770ae8527e62f1450d51298d6bec9ca6c9c4989a24f1c8526e353b8d176', 'functions': '41a0f31a512fcace740f4a2b39b3f57f913448ffbb1986474c5518fd47209e7a', 'contexts': '620ac4c63a1447305b13131b39854c6338e471427f8ea6bf5c7ef1257b0b2216', 'canonical': 'a17460a5058dd9386a64f012581499ade7af81467be0cc1378dd66425620981a', 'boundaries': 'c1b70f722e208025efaf8bc03e99c34047577ca7d00034b2ee9f79bbe60fd2c4', 'reviewed_sdk': '4d74d9a74415533280b82e1b55e0fc6b083500476a626977818d240226e00f8a', 'sdk_archive': 'fe32977e1506a0be67b9966237a92f90159f681a496f6a14a49bc0c58a9e3c10', 'debug_observations': 'e0c7549f7a687d76b6dbe2cc20dc3109afc3237d4eaaa5968e26fc2f5ff9896e', 'public_control': 'f2da04ad732558de6c0537faf766524fc7376a24ae8b6c8c8fedb3a03af34e83', 'historical_snapshots': '0887899e580ea432da9a5448e0e9aca874fbcd22a27159250e9465f81e30dff1', 'retained_sha256': 'e3fa918bfffc671b8a2765433fe222838b24ae0ca3cbb500c0db1b81080b306c', 'interpretation': '7716254be9d5053031d3e81ea21d7e6df56531ce045ff2b7b6ffe4ad3a517d0f'}
KEYS={'0x00449EC0':26,'0x0044DA70':26,'0x0044F830':26,'0x00451420':26}
CONFIDENCE='whole-background-counter-callback-and-independent-asset-vtable-render-context'


def verify_plan(m):
    for key,sha in PLAN_DIGESTS.items():
        if SOURCE.BASE.metadata_digest(m[key])!=sha:raise ValueError('Counter immutable whole evidence differs: '+key)
    if (m['evidence_id']!='R220' or {r['address']:r['size'] for r in m['functions']}!=KEYS
            or len(m['contexts'])!=4 or len(m['reviewed_sdk'])!=6
            or sum(r['source']['size'] for r in m['reviewed_sdk'])!=282
            or sum(len(r['source']['fields']) for r in m['reviewed_sdk'])!=9):
        raise ValueError('Counter bounded callback/retained-lifetime scope differs')
    mutable={'proposed_name','module','status','owner','evidence','notes'}
    for r in m['functions']:
        old,new=r['original_function'],r['accepted_function']
        if (r['original_origin']['origin']!='unknown' or old['status']!='unclassified'
                or old['size']!='26' or old['match_percent']!='0.00'
                or any(old[k] for k in ['owner','source_file','signature','calling_convention'])
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['owner']!='authored' or new['status']!='unclassified'
                or r['accepted_origin']!=dict(address=r['address'],origin='authored',subsystem='BackgroundStage',
                    disposition='authored',confidence=CONFIDENCE,evidence_id='R220')):
            raise ValueError('Counter gains unsupported source/layout/ABI/exact/extent credit')
    for r in m['reviewed_sdk']:
        if r['origin']['origin']!='unknown' or r['function']['owner'] or r['decision']!='unknown':
            raise ValueError('Counter assigns an unresolved explicit/implicit SDK lifetime')


def counter_policy(raw,address,flow,field):
    ins=flow.instructions(raw,address,len(raw)); displacement=str(field) if field<10 else hex(field)
    expected=[('push','ebp'),('mov','ebp, esp'),('push','ecx'),('mov','dword ptr [ebp - 4], ecx'),
              ('mov','eax, dword ptr [ebp - 4]'),('mov',f'ecx, dword ptr [eax + {displacement}]'),
              ('add','ecx, 1'),('mov','edx, dword ptr [ebp - 4]'),('mov',f'dword ptr [edx + {displacement}], ecx'),
              ('mov','esp, ebp'),('pop','ebp'),('ret','')]
    # Twelve instructions preserve both real field accesses and the full epilogue.
    if len(raw)!=26 or [(i.mnemonic,i.op_str) for i in ins]!=expected:
        raise ValueError('Counter whole increment/receiver/field/RET policy differs')
    return dict(field_offset=field,increment=1,instruction_count=len(ins),ret_cleanup=0)


def verify_native(m,target,c,flow):
    auth=module('counter_authored','verify-authored-origins.py')
    records=list(csv.DictReader((ROOT/'config/authored-origin-evidence.csv').open()))
    bg=module('counter_background','verify-background-origins.py')
    decoder=flow.capstone.Cs(flow.capstone.CS_ARCH_X86,flow.capstone.CS_MODE_32);decoder.detail=True
    for r in m['functions']:
        a=int(r['address'],16);raw=c.pe_bytes_at(target,a,26)
        if (digest(raw)!=r['body_sha256'] or SOURCE.instructions(raw,a,flow)!=r['instructions']
                or list(auth.verify_body(raw,a))!=r['cfg'] or counter_policy(raw,a,flow,0x68)!=r['policy']):
            raise ValueError('Counter full native callback/CFG differs')
    for ctx in m['contexts']:
        ctor=ctx['constructor'];renderer=ctx['renderer'];a=int(ctor['address'],16)
        for owner in ctx['owners']:
            key=owner['address'];base=int(key,16);raw=c.pe_bytes_at(target,base,owner['size'])
            if (digest(raw)!=owner['body_sha256'] or SOURCE.instructions(raw,base,flow)!=owner['instructions']
                    or list(auth.verify_body(raw,base))!=owner['cfg']):
                raise ValueError('Counter crops a complete independent callback/constructor owner')
            if owner['authored_record'] is not None and owner['authored_record'] not in records:
                raise ValueError('Counter changes prior complete authored evidence')
        raw=c.pe_bytes_at(target,a,ctor['size'])
        if ctor['witness'] not in bg.rows('background-origin-evidence.csv'):
            raise ValueError('Counter invents a prior background asset witness')
        bg.verify_witness(ctor['witness'],raw,target,c,decoder)
        table=int(ctx['table']['address'],16);data=c.pe_bytes_at(target,table,24)
        if (digest(data)!=ctx['table']['sha256'] or list(struct.unpack('<6I',data))!=ctx['table']['slots']
                or ctx['table']['slots'][1]!=int(ctx['callback'],16)
                or ctx['table']['slots'][4]!=int(renderer['address'],16)):
            raise ValueError('Counter loses the six real game callback slots or their owner identity')
        vptr=[i for i in flow.instructions(raw,a,len(raw)) if i.mnemonic=='mov' and len(i.operands)==2
              and i.operands[0].type==flow.capstone.x86.X86_OP_MEM and i.operands[1].type==flow.capstone.x86.X86_OP_IMM
              and i.operands[1].imm==table]
        zero=[i for i in flow.instructions(raw,a,len(raw)) if i.mnemonic=='mov' and len(i.operands)==2
              and i.operands[0].type==flow.capstone.x86.X86_OP_MEM and i.operands[0].mem.disp==0x68
              and i.operands[1].type==flow.capstone.x86.X86_OP_IMM and i.operands[1].imm==0]
        if len(vptr)!=1 or len(zero)!=1 or vptr[0].address-a!=ctx['vptr_store'] or zero[0].address-a!=130:
            raise ValueError('Counter game constructor does not install its table and initialize the same field')
        following=c.pe_bytes_at(target,table+24,8)
        if digest(following)!=ctx['table']['following_sha256']:
            raise ValueError('Counter absorbs adjacent noncallback data')
        rr=c.pe_bytes_at(target,int(renderer['address'],16),renderer['size'])
        observed=[dict(offset=i.address-int(renderer['address'],16),mnemonic=i.mnemonic,operands=i.op_str)
                  for i in flow.instructions(rr,int(renderer['address'],16),len(rr))
                  if any(o.type==flow.capstone.x86.X86_OP_MEM and o.mem.disp==0x68 for o in i.operands)]
        if observed!=ctx['counter_readers'] or not observed or any(r['mnemonic']!='fild' for r in observed[:-1]):
            raise ValueError('Counter reader loses the complete game rendering/animation field context')
        if not any(r['mnemonic']=='fild' for r in observed):
            raise ValueError('Counter context lacks a real integer animation input')


def verify_reviewed_sdk(m,target,c,coff,flow):
    archive=module('counter_sdk_archive','verify-runtime-origins.py');extra=module('counter_sdk_sections','sdk_x3d_carriers.py')
    raw=(ROOT/m['sdk_archive']['path']).read_bytes()
    if digest(raw)!=m['sdk_archive']['sha256']:raise ValueError('Counter original SDK archive differs')
    members={off:(n,b) for off,n,b in archive.archive_members(raw)}
    for r in m['reviewed_sdk']:
        tree=json.loads((ROOT/r['path']).read_text())
        source=tree['sections'][r['index']]
        if source!=r['source']:raise ValueError('Counter rewrites an earlier whole SDK lifetime record')
        name,body=members[source['member_offset']]
        code,fields,desc=extra.section_carrier(body,source['source']['section'],c,coff)
        if (name!=source['member'] or digest(body)!=source['member_sha256'] or desc!=source['source']
                or fields!=source['fields'] or len(code)!=source['size'] or digest(code)!=source['source_sha256']):
            raise ValueError('Counter reviewed lifetime crops original defining source/AUX/fields')
        # This is retained scoped checkpoint comparison, not a new source catalog
        # or a fresh replay of the earlier complete SDK dependency trees.
        linked=bytearray(code);calls={};data={};base=int(source['base'],16)
        if len(fields)!=len(source['bindings']):raise ValueError('Counter reviewed lifetime omits a source field')
        for f,b in zip(fields,source['bindings']):
            if any(b[k]!=value for k,value in f.items()):raise ValueError('Counter SDK retained field provenance differs')
            at=f['offset'];dest=int(b['target_address'],16)
            struct.pack_into('<I',linked,at,(dest-base-at-4)&0xffffffff if f['type']=='REL32' else dest)
            (calls if f['type']=='REL32' else data)[base+at]=dest
        actual_flow=flow.flow(linked,base,source['roots'],fields,calls,data)
        if r['path']=='config/sdk-graphics-origin-evidence.json':
            if actual_flow['reachable_instruction_count']!=actual_flow['instruction_count'] or actual_flow['nonreturn_suffix'] is not None:
                raise ValueError('Counter legacy SDK checkpoint hides an unreachable instruction')
            actual_flow={k:value for k,value in actual_flow.items() if k not in ['reachable_instruction_count','nonreturn_suffix']}
        if (linked!=c.pe_bytes_at(target,base,len(code)) or digest(linked)!=source['body_sha256']
                or actual_flow!=source['flow']):
            raise ValueError('Counter full retained SDK body/flow differs')


def replay(m,evidence_only=False):
    c=module('counter_target','compare-coff-function.py');coff=module('counter_coff','coff_data.py');flow=module('counter_flow','sdk_image_carriers.py')
    target=c.verified_target()
    if digest(target)!=m['target_sha256']:raise ValueError('Counter target identity differs')
    for path,sha in m['retained_sha256'].items():
        if digest((ROOT/path).read_bytes())!=sha:raise ValueError('Counter changes retained original input: '+path)
    fs={r['address']:r for r in csv.DictReader((ROOT/'config/functions.csv').open())}
    origins={r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
    state='original' if evidence_only else 'accepted';selected={r['address']:r for r in m['functions']}
    for r in m['functions']:
        if fs[r['address']]!=r[state+'_function'] or origins[r['address']]!=r[state+'_origin']:
            raise ValueError('Counter canonical bounded transition differs')
    for pair in m['canonical']:
        key=pair['function']['address'];expected=pair
        if key in selected:expected=dict(function=selected[key][state+'_function'],origin=selected[key][state+'_origin'])
        if dict(function=fs[key],origin=origins[key])!=expected:raise ValueError('Counter changes a retained or ambiguous canonical owner')
    for r in m['historical_snapshots']:
        old=json.loads((ROOT/r['path']).read_text())
        for k in r['trail']:old=old[k]
        if old!=r['record']:raise ValueError('Counter rewrites literal old unknown evidence')
    verify_native(m,target,c,flow);verify_reviewed_sdk(m,target,c,coff,flow)
    for r in m['debug_observations']:
        data=(ROOT/r['archive']).read_bytes()
        if digest(data)!=r['archive_sha256']:raise ValueError('Counter original debug SDK archive differs')
        name,body={off:(n,b) for off,n,b in module('counter_debug_archive','verify-runtime-origins.py').archive_members(data)}[r['member_offset']]
        if name!=r['member'] or digest(body)!=r['member_sha256']:raise ValueError('Counter original debug member differs')
        sections=[];count=struct.unpack_from('<H',body,2)[0]
        for i in range(count):
            h=struct.unpack_from('<8sIIIIIIHHI',body,20+i*40)
            if h[0].startswith(b'.debug'):
                sections.append(dict(section=i+1,name=h[0].decode().rstrip('\x00'),size=h[3],sha256=digest(body[h[4]:h[4]+h[3]])))
        if sections!=r['sections'] or any(s['name']=='.debug$T' for s in sections):
            raise ValueError('Counter invents unavailable original private type declarations')
    for boundary in m['boundaries']:
        a=int(boundary['address'],16);raw=c.pe_bytes_at(target,a,boundary['size'])
        if digest(raw)!=boundary['sha256'] or raw.hex()!=boundary['hex']:
            raise ValueError('Counter changes actual external alignment/next boundary')
    scratch=ROOT/'build/origin-background-counter-verification';scratch.mkdir(parents=True,exist_ok=True)
    control=m['public_control']
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj=Path(temp)/'Counter.obj'
        result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/control['probe']),str(obj),*control['profile']],cwd=ROOT,capture_output=True,text=True)
        if result.returncode or SOURCE.HEADERS(result.stdout+result.stderr)!=control['headers']:
            raise ValueError('Counter cold ordinary controls/includes differ')
        body=obj.read_bytes();inventory=module('counter_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
        if inventory(body,c,coff)!=control['emission']:raise ValueError('Counter omits whole ordinary emission')
        extra=module('counter_carrier','sdk_x3d_carriers.py')
        definitions=coff.parse_symbols(body,c.coff_name)[1]
        codes=[]
        for r in control['methods']:
            d=next(d for d in definitions if d['symbol']==r['symbol'] and d['section']>0)
            raw,fields,desc=extra.section_carrier(body,d['section'],c,coff)
            if (fields or SOURCE.BASE.canonical_source(desc,body)!=r['source'] or digest(raw)!=r['sha256']
                    or counter_policy(raw,0,flow,4)!=r['policy']):
                raise ValueError('Counter generic source has a false game layout or incomplete method')
            codes.append(raw)
        if codes[0]!=codes[1]:raise ValueError('Counter generic reference-count alternative differs')
        raw,_=coff.readonly_section(body,control['layout_section'],c.coff_name)
        if list(struct.unpack('<3I',raw))!=[8,8,4]:raise ValueError('Counter generic observations become private layout evidence')


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args()
    m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes())!=MANIFEST_SHA256:raise ValueError('Counter reviewed manifest differs')
    replay(m,args.evidence_only)
    print('R220: four complete game animation counter callbacks104; whole asset/vtable/render context; generic reference-count shape also matches; six SDK lifetime entries282 stay unknown; no exact credit.')
    return 0


if __name__=='__main__':raise SystemExit(main())
