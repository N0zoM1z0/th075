#!/usr/bin/env python3
"""Replay complete integer range policies and independent action/AI contexts."""
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
    spec=importlib.util.spec_from_file_location(name,ROOT/'scripts'/filename)
    result=importlib.util.module_from_spec(spec);spec.loader.exec_module(result);return result


SOURCE=module('range_source','verify-vector-insertion-carrier-origins.py')
digest=SOURCE.digest
EVIDENCE='config/integer-range-origin-evidence.json'
MANIFEST_SHA256='8a70ff4514cff6d1d5a686d4ddb7e5ef50f1b3905267e3ba367a1a848c6ab7d2'
PLAN_DIGESTS={'evidence_id': 'f7d3054c93fc243334302034005f035a4855f5c96c7d824bc9617e5a1e51af8e', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'comparison': '97a40894fcdf82cf2b62b19743929c5b69f5a1a458550b912953e90ab4124472', 'functions': '68e630ad882a89580724c40af79f1961694991d8d6fd2a3aefcd87fa0899c51f', 'parents': 'd6d78b2186e5880d8f2d66876ab94f921f5f026552c34bcf11983d9f8dd5cf31', 'boundaries': 'd02e92af9c1c4a8eacd279a98cbfc2070e5938aa090c78b65f3d7caa246069e6', 'canonical': '1b013a0b5bff0c899b6ff571a849a422cf59369a5913203bccad8872892b6695', 'provider': '598e7d3b0689e3a758a370ee9029202ea02381d485606f2f38e39ad6d5abc160', 'public_control': '647d01fa6643cf9ac2c29481602bcdcf18966da419bce63b5d9e347d40f541b8', 'retained_sha256': '946e011e4688d9aa0d803e736cec82f33021a650aaea398d62ed43a3cd492eb2', 'interpretation': 'abb65a86447c3cad47c6e3a3e58365a6f9b931d88ab3f634addc28c187a11dcb'}
KEYS={'0x00410F00':44,'0x00455610':44}
CONFIDENCE='whole-integer-range-policy-and-independent-action-ai-parameter-result-context'


def rows(filename):
    with (ROOT/'config'/filename).open(newline='') as stream:
        return list(csv.DictReader(stream))


def verify_plan(m):
    for key,sha in PLAN_DIGESTS.items():
        if SOURCE.BASE.metadata_digest(m[key])!=sha:raise ValueError('Range immutable evidence differs: '+key)
    if (m['evidence_id']!='R221' or {r['address']:r['size'] for r in m['functions']}!=KEYS
            or [len(p['call_sequences']) for p in m['parents']]!=[63,6]
            or sum(p['size'] for p in m['parents'])!=40223):
        raise ValueError('Range bounded whole candidate/parent scope differs')
    mutable={'proposed_name','module','owner','evidence','notes'}
    for r in m['functions']:
        old,new=r['original_function'],r['accepted_function']
        if (r['original_origin']['origin']!='unknown' or old['owner'] or old['size']!='44'
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['status']!='unclassified' or new['match_percent']!='0.00'
                or any(new[k] for k in ['source_file','signature','calling_convention'])
                or new['owner']!='authored'
                or r['accepted_origin']!=dict(address=r['address'],origin='authored',subsystem=new['module'],
                    disposition='authored',confidence=CONFIDENCE,evidence_id='R221')):
            raise ValueError('Range gains source/private ABI/exact credit or changes its complete extent')


def range_policy(raw,address,flow):
    expected=[('push','ebp'),('mov','ebp, esp'),('push','ecx'),('push','esi'),
        ('mov','dword ptr [ebp - 4], ecx'),('mov','esi, dword ptr [ebp + 0xc]'),
        ('sub','esi, dword ptr [ebp + 8]'),('call','0x6418ab'),('imul','eax, esi'),
        ('cdq',''),('and','edx, 0x7fff'),('add','eax, edx'),('sar','eax, 0xf'),
        ('add','eax, dword ptr [ebp + 8]'),('pop','esi'),('mov','esp, ebp'),('pop','ebp'),('ret','8')]
    ins=flow.instructions(raw,address,len(raw))
    if len(raw)!=44 or [(i.mnemonic,i.op_str) for i in ins]!=expected:
        raise ValueError('Range complete receiver/endpoint/rand/product/signed-bias/RET policy differs')
    call=ins[7]
    if call.address-address!=14 or call.imm_offset!=1 or call.imm_size!=4:
        raise ValueError('Range actual complete direct rand field differs')
    return dict(instruction_count=18,call_offset=14,field_offset=15,rand='0x006418AB',
        endpoint_stack_offsets=[8,12],receiver_saved_at=-4,receiver_used_in_arithmetic=False,
        signed_product_bits=32,signed_divisor=32768,ret_cleanup=8)


def call_sequences(ins,child):
    return [dict(site=f"0x{row['address']:08X}",instructions=ins[max(0,j-5):j+9])
            for j,row in enumerate(ins) if row['mnemonic']=='call' and row['operands']==hex(child)]


def verify_native(m,target,c,flow):
    auth=module('range_authored','verify-authored-origins.py')
    records=rows('authored-origin-evidence.csv')
    switches=rows('authored-origin-switches.csv')
    direct=rows('authored-origin-direct-switches.csv')
    for r in m['functions']:
        a=int(r['address'],16);raw=c.pe_bytes_at(target,a,r['size'])
        if (digest(raw)!=r['body_sha256'] or SOURCE.instructions(raw,a,flow)!=r['instructions']
                or list(auth.verify_body(raw,a))!=r['cfg'] or range_policy(raw,a,flow)!=r['policy']):
            raise ValueError('Range complete native candidate differs')
    for p in m['parents']:
        a=int(p['address'],16);raw=c.pe_bytes_at(target,a,p['size'])
        sw=[r for r in switches if r['address']==p['address']]
        ds=[r for r in direct if r['address']==p['address']]
        if (p['record'] not in records or p['record']['body_sha256']!=digest(raw)
                or digest(raw)!=p['body_sha256'] or sw!=p['switches'] or ds!=p['direct_switches']
                or list(auth.verify_body(raw,a,sw,lambda x,n:c.pe_bytes_at(target,x,n),ds))!=p['cfg']
                or SOURCE.instructions(raw,a,flow)!=p['instructions']):
            raise ValueError('Range crops or substitutes a complete independent game parent/guarded switch')
        observed=[dict(address=a+r['offset'],**r) for r in p['instructions']]
        if call_sequences(observed,int(p['child'],16))!=p['call_sequences']:
            raise ValueError('Range loses actual full parameter/result call context')
        for table in p['tables']:
            data=c.pe_bytes_at(target,int(table['address'],16),table['size'])
            if digest(data)!=table['sha256']:raise ValueError('Range guarded parent table differs')
    for gap in m['boundaries']:
        data=c.pe_bytes_at(target,int(gap['address'],16),gap['size'])
        if data.hex()!=gap['hex'] or digest(data)!=gap['sha256']:
            raise ValueError('Range absorbs external alignment or changes the next owner boundary')


def verify_control(m,body,c,coff,flow):
    control=m['public_control'];extra=module('range_carrier','sdk_x3d_carriers.py')
    inventory=module('range_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    if inventory(body,c,coff)!=control['emission']:raise ValueError('Range omits whole ordinary/SDK emission or field')
    definitions=coff.parse_symbols(body,c.coff_name)[1];code={}
    for r in control['methods']:
        d=next(d for d in definitions if d['symbol']==r['symbol'] and d['section']>0)
        raw,fields,desc=extra.section_carrier(body,d['section'],c,coff)
        if (SOURCE.BASE.canonical_source(desc,body)!=r['source'] or fields!=r['fields']
                or digest(raw)!=r['sha256'] or SOURCE.instructions(raw,0,flow)!=r['instructions']):
            raise ValueError('Range control loses complete source/AUX/line/field provenance')
        code[r['symbol']]=raw
    positive=[code[r['symbol']] for r in control['methods'] if r['role']=='ordinary-range-alternative']
    if len(positive)!=2 or positive[0]!=positive[1] or len(positive[0])!=31:
        raise ValueError('Range ordinary distribution alternative differs')
    # The natural /O1 control uses IDIV, not the target shift/bias lowering.
    # It is an arithmetic/source observation, never a relocation-masked match.
    for r in control['methods']:
        if r['role']=='ordinary-range-alternative':
            if ([i for i in r['instructions'] if i['mnemonic']=='idiv']!=
                    [dict(offset=22,size=2,mnemonic='idiv',operands='ecx')]
                    or len(r['fields'])!=1 or r['fields'][0]['symbol']!='_rand'):
                raise ValueError('Range ordinary signed division/source rand declaration differs')
    raw,_=coff.readonly_section(body,control['layout_section'],c.coff_name)
    if list(struct.unpack('<4I',raw))!=[1,1,4,32767]:raise ValueError('Range ordinary observations invent private layout')


def replay(m,evidence_only=False):
    c=module('range_target','compare-coff-function.py');coff=module('range_coff','coff_data.py')
    flow=module('range_flow','sdk_image_carriers.py');target=c.verified_target()
    if digest(target)!=m['target_sha256']:raise ValueError('Range target identity differs')
    for path,sha in m['retained_sha256'].items():
        if digest((ROOT/path).read_bytes())!=sha:raise ValueError('Range changes original input: '+path)
    fs={r['address']:r for r in rows('functions.csv')}
    origins={r['address']:r for r in rows('function-origins.csv')}
    selected={r['address']:r for r in m['functions']};state='original' if evidence_only else 'accepted'
    for pair in m['canonical']:
        key=pair['function']['address'];expected=pair
        if key in selected:expected=dict(function=selected[key][state+'_function'],origin=selected[key][state+'_origin'])
        if dict(function=fs[key],origin=origins[key])!=expected:raise ValueError('Range canonical bounded transition differs')
    verify_native(m,target,c,flow)
    provider=json.loads((ROOT/m['provider']['manifest']).read_text())
    if next(r for r in provider['functions'] if r['address']=='0x006418AB')!=m['provider']['record']:
        raise ValueError('Range substitutes the retained whole original rand provider')
    # Replay the actual original CRT graph, including the complete thread-state
    # definition/typed provider; a mapped rand name does not establish semantics.
    result=subprocess.run([str(ROOT/'scripts/repo-python'),str(ROOT/m['provider']['verifier'])],
        cwd=ROOT,capture_output=True,text=True)
    if result.returncode:raise ValueError('Range retained whole rand/thread-state source graph failed: '+result.stderr[-1800:])
    print(result.stdout.strip(),flush=True)
    scratch=ROOT/'build/origin-integer-range-verification';scratch.mkdir(parents=True,exist_ok=True)
    control=m['public_control']
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj=Path(temp)/'IntegerRange.obj'
        result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/control['probe']),str(obj),*control['profile']],
            cwd=ROOT,capture_output=True,text=True)
        if result.returncode or SOURCE.HEADERS(result.stdout+result.stderr)!=control['headers']:
            raise ValueError('Range cold natural source/includes differ')
        verify_control(m,obj.read_bytes(),c,coff,flow)


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args()
    m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes())!=MANIFEST_SHA256:raise ValueError('Range reviewed manifest differs')
    replay(m,args.evidence_only)
    print('R221: two complete authored integer range policies88; whole action/AI parents40223, all69 calls and full guarded switch; original rand/thread-state source; cold generic/SDK alternatives differ; no source/ABI/exact credit.')
    return 0


if __name__=='__main__':raise SystemExit(main())
