#!/usr/bin/env python3
"""Replay complete BG02 blend callbacks and a bounded current view of R230."""
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
SOURCE=module('blend_source','verify-vector-insertion-carrier-origins.py')
BASE=SOURCE.BASE
digest=SOURCE.digest
metadata_digest=BASE.metadata_digest
EVIDENCE='config/background-blend-origin-evidence.json'
MANIFEST_SHA256='4d8e713940a8f69d4f10bc25a159ddf9e4c550094735cfbd59ffff74a3a82449'
PLAN_DIGESTS={'evidence_id': '598c7e8a40c98b65eb1864749f03a9fdfe0046806d2bcb7271f716870d2a04fb', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'functions': '3d2a13698c063f8f4e2e41db218095549b872bcf8509f3095d5b00f1039f97f8', 'owners': '1e5ba25d6aac7583e77676934e6475348c899a1f0ba8a3c1a85d62e8acc210a8', 'runtime': 'fc7e7b9349e4225cee6a4d0ec0c711921a6ba3a6f837c1eba15d97edd9cb0729', 'data': '8cc72b5107d1753eba57251ef4f866018ae216688008711dd8f08e21359302af', 'boundaries': '81a72456c10ca2aa83eb42760518a024bb9379cec7f32d522d0be82650d8c0c6', 'canonical': '8afc387a92124ec6e00359caa3e80157227822650228f38b5ed3173c35710adb', 'unselected_sha256': '30dcf34e838a9350dda452c5e06a95a2bcc7f089d40448227e19c26f58881928', 'retained_checkpoint': '7cc9ed23039c93dc85e13534c05d6815e02537ddc0bd5f0cd836b7ca30c0e2aa', 'historical_snapshots': 'bf701cef3c1b193fb2cf487a1e6ff69c78d601dbd0d481f2dd218670fbaca555', 'public_control': '217a7d8fcd2a21f00529dafe8e5ffd499e8cbce3a38451be45de915537cbd55e', 'retained_sha256': 'cf1b5cc8343f55f60b8de9e47dacd2732d184c0c203b782375a285db5065eb70', 'interpretation': '258454d613b8c3e576e22455f2dc381dbb38f828a740f5f650f6f031d39eccea'}
WHOLE={'0x0044B980':60,'0x0044BEA0':60,'0x0044C3C0':60}
CONFIDENCE='whole-background-blend-callback-and-independent-asset-camera-render-state-provenance'

def rows(name):
    with (ROOT/'config'/name).open() as source:return list(csv.DictReader(source))


def verify_plan(m):
    if set(m)!=set(PLAN_DIGESTS):raise ValueError('Blend immutable schema differs')
    for key,sha in PLAN_DIGESTS.items():
        if metadata_digest(m[key])!=sha:raise ValueError('Blend immutable whole evidence differs: '+key)
    if (m['evidence_id']!='R231' or {r['address']:r['size'] for r in m['functions']}!=WHOLE
            or len(m['historical_snapshots'])!=3 or len(m['retained_checkpoint']['contexts'])!=3
            or len(m['owners'])!=3 or sum(r['size'] for r in m['owners'])!=307
            or len(m['public_control']['methods'])!=5):raise ValueError('Blend bounded full scope differs')
    mutable={'proposed_name','module','owner','evidence','notes'}
    for r in m['functions']:
        old,new=r['original_function'],r['accepted_function']
        if (r['original_origin']['origin']!='unknown' or old['owner']
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['owner']!='authored' or new['status']!='unclassified' or new['match_percent']!='0.00'
                or any(new[k] for k in ['source_file','signature','calling_convention'])
                or r['accepted_origin']!=dict(address=r['address'],origin='authored',subsystem='BackgroundStage',
                    disposition='authored',confidence=CONFIDENCE,evidence_id='R231')):
            raise ValueError('Blend gains extent/source/private ABI/mapping/exact credit')


def verify_canonical(m,evidence_only=False):
    functions={r['address']:r for r in rows('functions.csv')};origins={r['address']:r for r in rows('function-origins.csv')}
    selected={r['address']:r for r in m['functions']};state='original' if evidence_only else 'accepted'
    if evidence_only:
        for name in ['functions.csv','function-origins.csv']:
            if metadata_digest([r for r in rows(name) if r['address'] not in WHOLE])!=m['unselected_sha256'][name]:
                raise ValueError('Blend original transition changes unrelated canonical records')
    for pair in m['canonical']:
        a=pair['function']['address'];expected=pair
        if a in selected:expected=dict(function=selected[a][state+'_function'],origin=selected[a][state+'_origin'])
        if dict(function=functions[a],origin=origins[a])!=expected:raise ValueError('Blend scoped canonical owner differs: '+a)


def replay_retained(m,evidence_only=False):
    """Project only three fully checked canonical pairs; old source and cold builds stay literal."""
    checkpoint=m['retained_checkpoint'];old=module('blend_retained_r230',Path(checkpoint['script']).name)
    prior=json.loads((ROOT/checkpoint['path']).read_text());old.verify_plan(prior)
    if (digest((ROOT/checkpoint['path']).read_bytes())!=checkpoint['manifest_sha256']
            or old.MANIFEST_SHA256!=checkpoint['manifest_sha256']
            or digest((ROOT/checkpoint['script']).read_bytes())!=checkpoint['script_sha256']
            or metadata_digest(prior)!=checkpoint['plan_sha256']):
        raise ValueError('Blend rewrites the whole retained R230 source/native/cold proof')
    selected={r['address']:r for r in m['functions']};state='original' if evidence_only else 'accepted'
    for snapshot in m['historical_snapshots']:
        value=json.loads((ROOT/snapshot['path']).read_text())
        for key in snapshot['trail']:value=value[key]
        a=value['function']['address'];r=selected[a]
        if value!=snapshot['record'] or value!=dict(function=r['original_function'],origin=r['original_origin']):
            raise ValueError('Blend changes a literal whole old unknown pair')
    for q in checkpoint['contexts']:
        ctx=prior['contexts'][q['index']]
        if metadata_digest(ctx)!=q['sha256'] or ctx['table']['words'][2]!=int(q['callback'],16):
            raise ValueError('Blend callback is not the retained actual BG02 slot-two owner')
        ctor=next(r for r in ctx['owners'] if r['address']==ctx['constructor'])
        if ('add','ecx, 0x18') not in [(i['mnemonic'],i['operands']) for i in ctor['instructions']]:
            raise ValueError('Blend resource field lacks the independent real asset-load receiver')
    original_rows=old.rows
    def current_view(name):
        actual=original_rows(name)
        if name not in ['functions.csv','function-origins.csv']:return actual
        kind='function' if name=='functions.csv' else 'origin'
        out=[]
        for row in actual:
            a=row['address']
            if a in selected:
                if row!=selected[a][state+'_'+kind]:raise ValueError('Blend current-view projection accepts an unapproved transition')
                out.append(selected[a]['original_'+kind])
            else:out.append(row)
        return out
    old.rows=current_view
    try:old.replay(prior,False)
    finally:old.rows=original_rows


def verify_native(m,target,c,flow):
    auth=module('blend_authored','verify-authored-origins.py');permissions=module('blend_permissions','verify-sdk-x3d-origins.py')
    old_authored=rows('authored-origin-evidence.csv')
    for r in m['functions']+m['owners']:
        a=int(r['address'],16);raw=c.pe_bytes_at(target,a,r['size'])
        if (digest(raw)!=r['body_sha256'] or SOURCE.instructions(raw,a,flow)!=r['instructions']
                or list(auth.verify_body(raw,a))!=r['cfg']):raise ValueError('Blend crops/replaces whole selected/helper/camera body or CFG')
        if r.get('authored_record') is not None and r['authored_record'] not in old_authored:
            raise ValueError('Blend changes an independent authored game owner')
    for r in m['functions']:
        pairs=[(i['mnemonic'],i['operands']) for i in r['instructions']]
        if (pairs[4:11]!=[('fld','dword ptr [0x671404]'),('fadd','dword ptr [0x657834]'),
                ('call','0x6406ac'),('mov','dword ptr [ebp - 8], eax'),
                ('fld','dword ptr [0x6713c4]'),('call','0x6406ac'),('mov','dword ptr [ebp - 4], eax')]
                or pairs[11:15]!=[('push','0'),('mov','ecx, dword ptr [ebp - 0xc]'),('add','ecx, 0x18'),('call','0x40c7f0')]
                or pairs[-1]!=('ret','') or len(pairs)!=18):
            raise ValueError('Blend loses native calculations, unused results, zero-mode receiver or full RET')
    for r in m['data']:
        a=int(r['address'],16);raw=c.pe_bytes_at(target,a,4)
        if digest(raw)!=r['sha256'] or permissions.image_permissions(target,a,4)!=r['permissions']:
            raise ValueError('Blend source field loses independently observed whole data owner')
        if r['role']=='readonly-x-offset' and struct.unpack('<f',raw)[0]!=160.0:
            raise ValueError('Blend merges the original160 float offset with another constant')
    by={r['address']:r for r in m['owners']}
    for a in ['0x00412660','0x00412CF0']:
        pairs=[(i['mnemonic'],i['operands']) for i in by[a]['instructions']]
        if not any(mn=='mov' and op.startswith('dword ptr [0x671404],') for mn,op in pairs) or ('fstp','dword ptr [0x6713c4]') not in pairs:
            raise ValueError('Blend camera provenance lacks both real writable-output instructions')
    helper=by['0x0040C7F0']
    if helper['instructions'][-1]['operands']!='4' or [i['operands'] for i in helper['instructions'] if i['mnemonic']=='call']!=['0x402250','0x402250','0x401f50']:
        raise ValueError('Blend full game helper loses actual render-state calls/RET4 protocol')
    for r in m['boundaries']:
        raw=c.pe_bytes_at(target,int(r['address'],16),r['size'])
        if raw!=b'\xcc'*r['size'] or raw.hex()!=r['hex'] or digest(raw)!=r['sha256']:
            raise ValueError('Blend comparison absorbs external INT3 alignment')


def verify_runtime(m,target,c,coff,flow):
    r=m['runtime'];runtime=module('blend_crt_archive','verify-runtime-origins.py');extra=module('blend_crt_carrier','sdk_x3d_carriers.py')
    row=r['record']
    if row not in rows('runtime-origin-evidence.csv'):raise ValueError('Blend rewrites the independently accepted CRT owner')
    archive=(ROOT/r['archive']).read_bytes()
    if digest(archive)!=row['archive_sha256']:raise ValueError('Blend original CRT archive identity differs')
    name,body={o:(n,b) for o,n,b in runtime.archive_members(archive)}[int(row['member_offset'])]
    raw,fields,source=extra.section_carrier(body,r['source']['section'],c,coff);a=int(row['address'],16)
    auth=module('blend_crt_cfg','verify-authored-origins.py')
    if (name!=row['member'] or digest(body)!=r['member_sha256'] or source!=r['source'] or fields or fields!=r['fields']
            or len(raw)!=117 or digest(raw)!=row['body_sha256'] or raw!=c.pe_bytes_at(target,a,117)
            or SOURCE.instructions(raw,a,flow)!=r['instructions'] or list(auth.verify_body(raw,a))!=r['cfg']):
        raise ValueError('Blend runtime loses whole original function/AUX/fields/unmasked identity')
    with tempfile.TemporaryDirectory(dir=ROOT/'build') as temp:
        path=Path(temp)/'ftol2.obj';path.write_bytes(body)
        auxiliary,relocations=c.object_function(path,'__ftol2')
        if auxiliary!=raw or relocations:raise ValueError('Blend117 extent lacks its own complete function AUX definition')


def verify_control(m,body,c,coff,flow):
    extra=module('blend_cold_carriers','sdk_x3d_carriers.py');auth=module('blend_cold_cfg','verify-authored-origins.py')
    inventory=module('blend_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory;control=m['public_control']
    if inventory(body,c,coff)!=control['emission']:raise ValueError('Blend loses full cold code/data/fields')
    routes={'?ObservedBackgroundX@@3MA':0x671404,'?ObservedBackgroundY@@3MA':0x6713c4,
            '__real@43200000':0x657834,'__ftol2':0x6406ac,
            '?SetBlendMode@TextureObservation@@QAEXH@Z':0x40c7f0}
    if control['independent_routes']!={s:f'0x{a:08X}' for s,a in routes.items()}:
        raise ValueError('Blend ordinary routes lack their independently verified owner identities')
    raw_by={}
    for r in control['methods']:
        raw,fields,source=extra.section_carrier(body,r['source']['section'],c,coff)
        if (SOURCE.BASE.canonical_source(source,body)!=r['source'] or fields!=r['fields'] or len(raw)!=r['size']
                or digest(raw)!=r['sha256'] or SOURCE.instructions(raw,0,flow)!=r['instructions']
                or list(auth.verify_body(raw,0))!=r['cfg']):raise ValueError('Blend whole natural source/COFF/AUX/CFG differs')
        raw_by[r['role']]=raw
        for f in fields:
            if f['symbol'] not in control['independent_routes'] or f['addend']!=0:
                raise ValueError('Blend ordinary field has no independent full native owner')
            if f['symbol']=='__real@43200000':
                data,df,desc=extra.section_carrier(body,f['symbol_section'],c,coff)
                if df or len(data)!=4 or struct.unpack('<f',data)[0]!=160.0 or not any(d['symbol']==f['symbol'] and d['offset']==0 for d in desc['definitions']):
                    raise ValueError('Blend source offset lacks an actual defining whole float owner')
        linked=bytearray(raw);calls={};data_fields={}
        for f in fields:
            at=f['offset'];destination=routes[f['symbol']]
            if f['type']=='REL32' and at>0 and raw[at-1]==0xe8:
                struct.pack_into('<I',linked,at,(destination-at-4)&0xffffffff);calls[at]=destination
            elif f['type']=='DIR32':
                struct.pack_into('<I',linked,at,destination);data_fields[at]=destination
            else:raise ValueError('Blend ordinary field is not its complete actual call/data route')
        if (SOURCE.instructions(linked,0,flow)!=r['linked_instructions']
                or flow.flow(linked,0,[0],fields,calls,data_fields)!=r['linked_flow']):
            raise ValueError('Blend ordinary whole unmasked independent route/CFG differs')
        if r['role']=='implicit-copy' and (fields or any(i['mnemonic'] in ['call','fld','fadd'] for i in r['instructions'])):
            raise ValueError('Blend compiler copy alternative becomes a floating/render-state policy')
    differences=[i for i,(a,b) in enumerate(zip(raw_by['zero-mode'],raw_by['one-mode'])) if a!=b]
    if differences!=[8] or len(raw_by['zero-mode'])!=21:raise ValueError('Blend distinct whole zero/one mode controls are merged')
    data,_=coff.readonly_section(body,control['layout_section'],c.coff_name)
    if len(data)!=16 or list(struct.unpack('<4I',data))!=[1,1,4,4]:raise ValueError('Blend compact generic owner is replaced with padded game layout')


def replay(m,evidence_only=False):
    c=module('blend_target','compare-coff-function.py');coff=module('blend_coff','coff_data.py');flow=module('blend_flow','sdk_image_carriers.py')
    target=c.verified_target()
    if digest(target)!=m['target_sha256']:raise ValueError('Blend target identity differs')
    for path,sha in m['retained_sha256'].items():
        if digest((ROOT/path).read_bytes())!=sha:raise ValueError('Blend changes retained input: '+path)
    verify_canonical(m,evidence_only);verify_native(m,target,c,flow);verify_runtime(m,target,c,coff,flow)
    replay_retained(m,evidence_only)
    control=m['public_control'];scratch=ROOT/'build/origin-background-blend-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj=Path(temp)/'BackgroundBlendPolicies.obj'
        result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/control['probe']),str(obj),*control['profile']],cwd=ROOT,capture_output=True,text=True)
        if result.returncode or SOURCE.HEADERS(result.stdout+result.stderr)!=control['headers']:
            raise ValueError('Blend cold compiler/header proof failed; no cached-object fallback')
        verify_control(m,obj.read_bytes(),c,coff,flow)


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args()
    m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes())!=MANIFEST_SHA256:raise ValueError('Blend immutable manifest differs')
    replay(m,args.evidence_only)
    print('R231:three whole BG02 blend callbacks180; whole R230 native/cold graph with three literal canonical projections; original CRT ftol2/AUX117, full mode/camera owners307 and natural controls; no source/private ABI/mapping/exact credit.')


if __name__=='__main__':main()
