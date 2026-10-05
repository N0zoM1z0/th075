#!/usr/bin/env python3
"""Replay one complete virtual frame policy, game receiver context and source controls."""
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


SOURCE=module('virtual_frame_source','verify-vector-insertion-carrier-origins.py')
digest=SOURCE.digest
EVIDENCE='config/virtual-frame-origin-evidence.json'
MANIFEST_SHA256='c896dc1c16528a6fe448cc6430910322890e63844b52c2291aa8be2787c58199'
PLAN_DIGESTS={'evidence_id': '1ad886b17b920affe886c3917fbdb2c6a794902474d75009cd08c1d5d1320c93', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'comparison': '499e2fb1016a701bfa0f53ee8af30c2e5300d306c4c38e7cdab581a235620da2', 'functions': '461c993c675e80ae5a89ffa1697addce0ac4e90be54da8f970e6ced94fa2e96e', 'owners': '7e3b88f9dbc111656bd93f9e1e06707e46b0fc7ee314a97c964bdbc36c45e132', 'tables': 'd3e2e277ed5cef46363e8287a132b8460073f82a25a6cf74937214943f23bd98', 'boundary': '689d39bd992cf828630b134836c7971ef9130064284cdc59cdc83e29b95c7e2e', 'canonical': '250104a99053d1f7f2105ca190496673ef1418cd8f3deafffda36bf13b993abd', 'public_control': '17a227a0d699af3fe9dbe184c72b66cf53cc1a251ceed6537bb02f89a924df9d', 'historical_snapshots': '456f70719f60d22a566b12a3f084ec9ed88fa5d2cb26290bfe7f491d44a3230c', 'vendor': '9b59e9b42a3112708923c66fe217ebaa803c9b9b5c5974ab5d793657f3922d3c', 'retained_sha256': 'f66882c386d0346ec7c9ef96b44479033811bd6bf4a7469b9fc3cbf3b734ffe6', 'interpretation': '28c7558d1133112d46c59ae73be10296f3b4f1730a0d08fce29b668ece493ec5'}
CONFIDENCE='whole-virtual-frame-selection-and-independent-game-resource-receiver-dispatch-context'


def rows(filename):
    with (ROOT/'config'/filename).open(newline='') as stream:return list(csv.DictReader(stream))


def verify_plan(m):
    for key,sha in PLAN_DIGESTS.items():
        if SOURCE.BASE.metadata_digest(m[key])!=sha:raise ValueError('Virtual frame immutable evidence differs: '+key)
    if (m['evidence_id']!='R222' or [(r['address'],r['size']) for r in m['functions']]!=[('0x0045B880',149)]
            or len(m['owners'])!=8 or sum(r['size'] for r in m['owners'])!=51694
            or len(m['tables'])!=2 or len(m['historical_snapshots'])!=18):
        raise ValueError('Virtual frame bounded whole game/source/history scope differs')
    r=m['functions'][0];old,new=r['original_function'],r['accepted_function']
    mutable={'proposed_name','module','owner','evidence','notes'}
    if (r['original_origin']['origin']!='unknown' or old['owner']
            or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
            or new['owner']!='authored' or new['status']!='unclassified' or new['match_percent']!='0.00'
            or any(new[k] for k in ['source_file','signature','calling_convention'])
            or r['accepted_origin']!=dict(address='0x0045B880',origin='authored',subsystem='BattleObject',
                disposition='authored',confidence=CONFIDENCE,evidence_id='R222')):
        raise ValueError('Virtual frame gains source/private layout/ABI/exact credit or changes extent')


def frame_policy(raw,address,flow):
    ins=flow.instructions(raw,address,len(raw));pairs=[(i.mnemonic,i.op_str) for i in ins]
    calls=[dict(offset=i.address-address,target=f'0x{i.operands[0].imm:08X}',field_offset=i.address-address+i.imm_offset)
           for i in ins if i.mnemonic=='call' and i.operands[0].type==flow.capstone.x86.X86_OP_IMM]
    expected=[(32,'0x004420B0'),(39,'0x00442060'),(96,'0x004420B0'),(103,'0x00442120'),(132,'0x004420B0')]
    required=[('movsx','ecx, word ptr [eax + 0x62]'),('movsx','eax, word ptr [edx + 0x60]'),
        ('mov','ecx, dword ptr [ecx + 0xc4]'),('mov','dword ptr [edx + 0x74], eax'),
        ('mov','dword ptr [eax + 8], edx'),('mov','ax, word ptr [ecx + 4]'),
        ('mov','word ptr [edx + 0x72], ax'),('mov','word ptr [ecx + 0x70], ax'),
        ('mov','dword ptr [edx + 0x78], eax')]
    if (len(raw)!=149 or len(ins)!=48 or [(r['offset'],r['target']) for r in calls]!=expected
            or any(r['field_offset']!=r['offset']+1 for r in calls) or pairs[-1]!=('ret','')
            or not all(p in pairs for p in required)
            or pairs[6:14]!=[('push','ecx'),('mov','edx, dword ptr [ebp - 4]'),
                ('movsx','eax, word ptr [edx + 0x60]'),('push','eax'),('mov','ecx, dword ptr [ebp - 4]'),
                ('mov','ecx, dword ptr [ecx + 0xc4]'),('call','0x4420b0'),('mov','ecx, dword ptr [eax]')]
            or sum(i.mnemonic=='call' for i in ins)!=5):
        raise ValueError('Virtual frame complete indices/nested RET4 stack/data/result policy differs')
    return dict(instruction_count=48,calls=calls,index_fields=[0x60,0x62],resource_pointer_field=0xc4,
        output_fields=[0x74,8,0x72,0x70,0x78],record_word_offset=4,ret_cleanup=0)


def action_sequences(ins,address):
    targets={'0x40fa30','0x40fac0','0x40fb00','0x40fb40'}
    return [dict(site=f"0x{address+r['offset']:08X}",instructions=ins[max(0,j-4):j+3])
            for j,r in enumerate(ins) if r['mnemonic']=='call' and r['operands'] in targets]


def verify_native(m,target,c,flow):
    auth=module('virtual_frame_authored','verify-authored-origins.py');records=rows('authored-origin-evidence.csv')
    switches=rows('authored-origin-switches.csv');direct=rows('authored-origin-direct-switches.csv')
    by={r['address']:r for r in m['owners']}
    for r in m['functions']:
        a=int(r['address'],16);raw=c.pe_bytes_at(target,a,r['size'])
        if (digest(raw)!=r['body_sha256'] or SOURCE.instructions(raw,a,flow)!=r['instructions']
                or list(auth.verify_body(raw,a))!=r['cfg'] or frame_policy(raw,a,flow)!=r['policy']):
            raise ValueError('Virtual frame full native policy differs')
    for r in m['owners']:
        a=int(r['address'],16);raw=c.pe_bytes_at(target,a,r['size']);ins=SOURCE.instructions(raw,a,flow)
        sw=[q for q in switches if q['address']==r['address']];ds=[q for q in direct if q['address']==r['address']]
        if (r['record'] not in records or digest(raw)!=r['record']['body_sha256'] or digest(raw)!=r['body_sha256']
                or sw!=r['switches'] or ds!=r['direct_switches']
                or list(auth.verify_body(raw,a,sw,lambda x,n:c.pe_bytes_at(target,x,n),ds))!=r['cfg']
                or len(ins)!=r['instruction_count'] or SOURCE.BASE.metadata_digest(ins)!=r['instructions_sha256']
                or (r['instructions'] is not None and ins!=r['instructions'])):
            raise ValueError('Virtual frame crops/replaces independent whole game construction/peer/dispatch context')
        for table in r['switch_tables']:
            if digest(c.pe_bytes_at(target,int(table['address'],16),table['size']))!=table['sha256']:
                raise ValueError('Virtual frame loses the full guarded game action data')
        if r['address']=='0x00476A40' and action_sequences(ins,a)!=r['call_sequences']:
            raise ValueError('Virtual frame loses actual game receiver calls to the inherited dispatch methods')
    def pairs(key):return [(r['mnemonic'],r['operands']) for r in by[key]['instructions']]
    ctor=pairs('0x004769B0');peer=pairs('0x00453D80')
    if (ctor[15:19]!=[('mov','eax, dword ptr [ebp + 8]'),('add','eax, 0x468'),
            ('mov','ecx, dword ptr [ebp - 4]'),('mov','dword ptr [ecx + 0xc4], eax')]
            or sum(p==('add','ecx, 0x468') for p in peer)!=3):
        raise ValueError('Virtual frame lookup pointer lacks independent actual game resource ownership')
    pe=module('virtual_frame_permissions','verify-sdk-x3d-origins.py')
    for r in m['tables']:
        a=int(r['address'],16);raw=c.pe_bytes_at(target,a,24)
        if (digest(raw)!=r['sha256'] or list(struct.unpack('<6I',raw))!=r['words']
                or r['words'][0]!=0x45b880 or r['words'][-1]!=0
                or pe.image_permissions(target,a,24)!=0x40000000):
            raise ValueError('Virtual frame loses its selected readonly slot and bounded following words')
        instructions=by[r['constructor']]['instructions']
        if next(i for i in instructions if i['offset']==18)!=dict(offset=18,size=6,mnemonic='mov',operands=f'dword ptr [eax], {hex(a)}'):
            raise ValueError('Virtual frame selected callback is not installed by the complete actual constructor')
    for key in ['0x0040FA30','0x0040FAC0','0x0040FB00','0x0040FB40']:
        ps=pairs(key)
        if ('call','dword ptr [edx]') not in ps or not any(' + 0x62]' in op for _,op in ps):
            raise ValueError('Virtual frame game counter operation loses its regular first-slot dispatch')
    gap=m['boundary'];raw=c.pe_bytes_at(target,int(gap['address'],16),gap['size'])
    if raw.hex()!=gap['hex'] or digest(raw)!=gap['sha256']:raise ValueError('Virtual frame absorbs external alignment')


def verify_control(m,body,c,coff,flow):
    control=m['public_control'];extra=module('virtual_frame_carrier','sdk_x3d_carriers.py')
    inventory=module('virtual_frame_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    if inventory(body,c,coff)!=control['emission']:raise ValueError('Virtual frame omits whole ordinary code/data/EH emission')
    definitions=coff.parse_symbols(body,c.coff_name)[1];codes=[]
    for r in control['methods']:
        d=next(d for d in definitions if d['symbol']==r['symbol'] and d['section']>0)
        raw,fields,source=extra.section_carrier(body,d['section'],c,coff)
        if (SOURCE.BASE.canonical_source(source,body)!=r['source'] or fields!=r['fields']
                or digest(raw)!=r['sha256'] or SOURCE.instructions(raw,0,flow)!=r['instructions']):
            raise ValueError('Virtual frame loses whole natural source/AUX/line/field observations')
        if r['role']=='ordinary-frame-view-alternative':codes.append(raw)
        if r['role']=='implicit-construction-alternative' and len(raw) not in [23,31]:
            raise ValueError('Virtual frame implicit lifetime control becomes a selection policy')
    if len(codes)!=2 or codes[0]!=codes[1] or len(codes[0])!=140:
        raise ValueError('Virtual frame generic asset-view alternative differs')
    raw,_=coff.readonly_section(body,control['layout_section'],c.coff_name)
    if list(struct.unpack('<6I',raw))!=[8,16,16,28,28,28]:raise ValueError('Virtual frame invents a padded private owner/record')


def replay(m,evidence_only=False):
    c=module('virtual_frame_target','compare-coff-function.py');coff=module('virtual_frame_coff','coff_data.py')
    flow=module('virtual_frame_flow','sdk_image_carriers.py');target=c.verified_target()
    if digest(target)!=m['target_sha256']:raise ValueError('Virtual frame target identity differs')
    for path,sha in m['retained_sha256'].items():
        if digest((ROOT/path).read_bytes())!=sha:raise ValueError('Virtual frame changes retained original input: '+path)
    fs={r['address']:r for r in rows('functions.csv')};origins={r['address']:r for r in rows('function-origins.csv')}
    selected=m['functions'][0];state='original' if evidence_only else 'accepted'
    for pair in m['canonical']:
        key=pair['function']['address'];expected=pair
        if key==selected['address']:expected=dict(function=selected[state+'_function'],origin=selected[state+'_origin'])
        if dict(function=fs[key],origin=origins[key])!=expected:raise ValueError('Virtual frame canonical bounded transition differs')
    for r in m['historical_snapshots']:
        prior=json.loads((ROOT/r['path']).read_text())
        for key in r['trail']:prior=prior[key]
        if (prior!=r['record'] or prior['function']!=selected['original_function']
                or prior['origin']!=selected['original_origin'] or prior['body_sha256']!=selected['body_sha256']):
            raise ValueError('Virtual frame rewrites a literal historical unknown snapshot')
    verify_native(m,target,c,flow)
    result=subprocess.run([str(ROOT/'scripts/repo-python'),str(ROOT/m['vendor']['verifier'])],cwd=ROOT,capture_output=True,text=True)
    if result.returncode:raise ValueError('Virtual frame whole original vector-at/size/source graph failed: '+result.stderr[-1800:])
    print(result.stdout.strip(),flush=True)
    scratch=ROOT/'build/origin-virtual-frame-verification';scratch.mkdir(parents=True,exist_ok=True);control=m['public_control']
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj=Path(temp)/'VirtualFrame.obj'
        result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/control['probe']),str(obj),*control['profile']],
            cwd=ROOT,capture_output=True,text=True)
        if result.returncode or SOURCE.HEADERS(result.stdout+result.stderr)!=control['headers']:
            raise ValueError('Virtual frame cold natural source/includes differ')
        verify_control(m,obj.read_bytes(),c,coff,flow)


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args()
    m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes())!=MANIFEST_SHA256:raise ValueError('Virtual frame reviewed manifest differs')
    replay(m,args.evidence_only)
    print('R222: whole authored virtual frame policy149; independent resource receiver, callback construction, peer and full game action/dispatch context51694; full original R205 source; natural generic/implicit alternatives; eighteen old unknown snapshots unchanged; no source/ABI/exact credit.')
    return 0


if __name__=='__main__':raise SystemExit(main())
