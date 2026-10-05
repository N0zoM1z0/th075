#!/usr/bin/env python3
"""Reopen the complete 3DNow initializer, every callback and whole math object."""
from __future__ import annotations
import argparse
import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import sys

ROOT=Path(__file__).resolve().parents[1]
EVIDENCE='config/sdk-x3d-origin-evidence.json'
MANIFEST_SHA256='d2a7ef2eeb860ae2e392456a64a59df935f108b95b894a171f8a37a8fa0ca22d'
KEYS={'0x00628BF5':550,'0x00633C36':179,'0x006341DF':108,'0x0063424B':311,
      '0x00634382':141,'0x0063440F':146,'0x00634505':167,'0x006346F3':2649,
      '0x00636B8C':421,'0x00637265':281,'0x00639897':360,'0x00639A1F':518,
      '0x00639C45':307,'0x0063CBC0':245,'0x0063CCC0':247,'0x0063D2A0':281,'0x0063D3C0':283}
CONFIDENCE='whole-pinned-sdk-3dnow-carriers-inline-switches-math-aliases-and-complete-data'


def module(name,filename):
    spec=importlib.util.spec_from_file_location(name,ROOT/'scripts'/filename)
    result=importlib.util.module_from_spec(spec);spec.loader.exec_module(result);return result


def digest(data):return hashlib.sha256(data).hexdigest()


def image_permissions(target,address,size):
    pe=struct.unpack_from('<I',target,0x3c)[0]
    count=struct.unpack_from('<H',target,pe+6)[0];optional=struct.unpack_from('<H',target,pe+20)[0]
    base=struct.unpack_from('<I',target,pe+24+28)[0]
    for i in range(count):
        h=struct.unpack_from('<8sIIIIIIHHI',target,pe+24+optional+40*i)
        if base+h[2]<=address and address+size<=base+h[2]+min(h[1],h[3]):
            return h[9]&0xe0000000
    raise ValueError('3DNow complete image is not entirely backed by a PE section')


def field_key(off,f):
    if f['symbol_section']>0 and f['symbol_type']!=32 and f['symbol_storage'] in (3,6):
        return (off,f['symbol_section'],f['symbol_index'])
    return f['symbol']


def bind(raw,fields,bindings,catalog,off,address):
    linked=bytearray(raw);calls={};data={};used=set()
    if len(fields)!=len(bindings):raise ValueError('3DNow drops a genuine field')
    for f,b in zip(fields,bindings):
        at=f['offset'];dest=int(b['target_address'],16);base=dest-f['addend']
        if (at<1 or at+4>len(raw) or any(j in used for j in range(at,at+4))
                or {k:b[k] for k in f}!=f or catalog.get(field_key(off,f))!=base
                or int(b['source_base'],16)!=base or struct.unpack_from('<I',raw,at)[0]!=f['addend']):
            raise ValueError('3DNow source scope/definition/addend differs or fields overlap')
        used.update(range(at,at+4))
        if f['type']=='DIR32' and f['type_id']==6:value=dest;data[address+at]=dest
        elif f['type']=='REL32' and f['type_id']==20 and not f['addend'] and raw[at-1] in (0xe8,0xe9):
            value=(dest-address-at-4)&0xffffffff;calls[address+at]=dest
        else:raise ValueError('3DNow unsupported real field kind')
        struct.pack_into('<I',linked,at,value)
    return linked,calls,data


def verify_plan(m):
    math=[r for r in m['controls'] if r['kind']=='whole-math-section']
    switches=[r for r in m['controls'] if r['switch']]
    if (m['evidence_id']!='R191' or len(m['functions'])!=17 or {r['address']:r['size'] for r in m['functions']}!=KEYS
            or len(m['controls'])!=69 or sum(r['size'] for r in m['controls'])!=30525
            or sum(len(r['fields']) for r in m['controls'])!=498 or len(math)!=1 or math[0]['size']!=3256
            or math[0]['address']!='0x0063CB00' or len(math[0]['fields'])!=138
            or len(math[0]['flow']['partitions'])!=19
            or sum(p['flow']['extent'] for p in math[0]['flow']['partitions'])!=3002
            or [(r['address'],r['switch']['offset'],r['size']) for r in switches]!=[('0x00639897',360,392),('0x00639A1F',518,550),('0x00639C45',307,339)]
            or len(m['data'])!=2 or [r['size'] for r in m['data']]!=[8,344]
            or [r['source']['flags'] for r in m['data']]!=[0x40400040,0xc0700040]
            or len(m['readonly'])!=3 or len(m['pending'])!=3
            or {r['address']:r['size'] for r in m['pending']}!={'0x00620C9A':221,'0x0061AF34':6,'0x0061CA33':328}
            or m['comparison']!='whole-library-origin-only-no-new-source-abi-mapping-or-exact-credit'):
        raise ValueError('3DNow loses whole code/table/math/data scope or changes pending dispatch')
    aliases=next(p for p in math[0]['flow']['partitions'] if p['offset']==1952)
    if aliases['aliases']!=['_a_cos','_a_sincos']:raise ValueError('3DNow math source alias is duplicated or lost')
    init=next(r for r in m['controls'] if r['address']=='0x00628BF5')
    if (init['size']!=550 or len(init['fields'])!=63 or init['fields'][0]['symbol']!='?get_feature_flags@@YAIXZ'
            or init['fields'][0]['type']!='REL32' or any(f['type']!='DIR32' or f['symbol_type']!=32 for f in init['fields'][1:])):
        raise ValueError('3DNow initializer loses any one of its62 independently owned callback fields')
    mutable={'proposed_name','module','status','owner','evidence','notes'}
    proofs={r['address']:(r['flow']['extent'],[r['symbol']],r['function'],r['origin']) for r in m['controls'] if r['kind']!='whole-math-section'}
    entries={r['address']:r for r in math[0]['entries']}
    for p in math[0]['flow']['partitions']:
        a=f"0x{int(math[0]['address'],16)+p['offset']:08X}"
        snap=entries[a];proofs[a]=(p['flow']['extent'],p['aliases'],snap['function'],snap['origin'])
    for r in m['functions']:
        a=r['address'];old=r['original_function'];new=r['accepted_function']
        if (r['original_origin']['origin']!='unknown' or int(old['size'])!=r['size']
                or proofs[a][0]!=r['size'] or proofs[a][2]!=old or proofs[a][3]!=r['original_origin']
                or new['proposed_name'] not in proofs[a][1]
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['status']!='excluded' or new['owner']!='library' or new['evidence']!='R191' or new['module']!='D3DX8'
                or new['source_file'] or new['calling_convention'] or new['signature'] or new['match_percent']!='0.00'
                or r['accepted_origin']!=dict(address=a,origin='library',subsystem='D3DX8',disposition='exclude',confidence=CONFIDENCE,evidence_id='R191')):
            raise ValueError('3DNow origin changes an extent, pending decision or source/ABI/exact credit')
    for r in m['controls']:
        if len(r['fields'])!=len(r['bindings']) or r['source']['size']!=r['size']:raise ValueError('3DNow whole source fields/extent differ')
        if r['switch'] and r['flow']['table_size']!=32:raise ValueError('3DNow switch table cannot become function/alignment credit')
    for r in m['pending']:
        if r['origin']['origin']!='unknown' or 'bindings' in r or 'target_positive' in r:
            raise ValueError('3DNow incomplete CPU/table/public graph becomes accepted')


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args()
    m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes())!=MANIFEST_SHA256:raise ValueError('3DNow immutable manifest differs')
    for path,sha in m['retained_sha256'].items():
        if digest((ROOT/path).read_bytes())!=sha:raise ValueError('3DNow retained source/evidence differs: '+path)
    c=module('x3d_coff','compare-coff-function.py');coff=module('x3d_data','coff_data.py')
    rt=module('x3d_archive','verify-runtime-origins.py');sdk=module('x3d_sdk','verify-sdk-origins.py')
    carrier=module('x3d_carriers','sdk_code_carriers.py');extra=module('x3d_tables','sdk_x3d_carriers.py')
    target=c.verified_target();archive=(ROOT/'.tools/msvc710/Vc7/PlatformSDK/Lib/d3dx8.lib').read_bytes()
    if digest(target)!=m['target_sha256'] or digest(archive)!=m['archive_sha256']:raise ValueError('3DNow target/archive identity differs')
    members={o:(n,b) for o,n,b in rt.archive_members(archive)}
    def member(r):
        n,b=members[r['member_offset']]
        if n!=r['member'] or digest(b)!=r['member_sha256']:raise ValueError('3DNow original source owner differs')
        return b
    def rows(path):
        with (ROOT/path).open() as stream:return list(csv.DictReader(stream))
    functions={r['address']:r for r in rows('config/functions.csv')};origins={r['address']:r for r in rows('config/function-origins.csv')}
    selected={r['address']:r for r in m['functions']};mode='original' if args.evidence_only else 'accepted'
    for a,r in selected.items():
        if functions[a]!=r[mode+'_function'] or origins[a]!=r[mode+'_origin']:raise ValueError('3DNow selected canonical decision differs')
    readonly=sdk.verify_readonly_sections(c,rt,target);rdrows={r['id']:r for r in rows('config/sdk-origin-data.csv')}
    catalog={};sections={};observed=set();readonly_names=set()
    for r in m['controls']:
        a=int(r['address'],16)
        peers=[d for d in r['source']['definitions'] if d['type']==32] if r['kind']=='whole-math-section' else r['source']['peers']
        for d in peers:
            if d['symbol'] in catalog and catalog[d['symbol']]!=a+d['offset']:raise ValueError('3DNow actual code symbol has conflicting owners')
            catalog[d['symbol']]=a+d['offset']
    for r in m['data']:
        raw,fields,source=extra.section_carrier(member(r),r['source']['section'],c,coff)
        if (fields or source!=r['source'] or len(raw)!=r['size'] or source['flags']&0x20 or not source['flags']&0x40
                or image_permissions(target,int(r['base'],16),len(raw))!=source['flags']&0xe0000000
                or raw!=c.pe_bytes_at(target,int(r['base'],16),len(raw)) or digest(raw)!=r['source_sha256'] or digest(raw)!=r['body_sha256']):
            raise ValueError('3DNow whole initialized readonly/writable image/definitions differ')
        sections[r['member_offset'],source['section']]=r
    for r in m['readonly']:
        if rdrows.get(r['id'])!=r:raise ValueError('3DNow accepted readonly section changes')
        for sn,a in readonly[r['id']]['symbols'].items():catalog[sn]=a;readonly_names.add(sn)
    for r in m['controls']:
        address=int(r['address'],16);off=r['member_offset']
        for f,b in zip(r['fields'],r['bindings']):
            key=field_key(off,f);base=int(b['source_base'],16)
            if f['local_symbol_offset'] is not None:
                if (f['symbol_type'] or f['symbol_section']!=r['source']['section'] or base!=address+f['symbol_offset']):
                    raise ValueError('3DNow local switch label uses a foreign owner')
            elif f['symbol_type']==32:
                if catalog.get(f['symbol'])!=base:raise ValueError('3DNow callback/callee lacks a whole independently defined code owner')
                continue
            elif f['symbol_storage']==2 and f['symbol'] in readonly_names:
                if catalog[key]!=base:raise ValueError('3DNow readonly symbol binding differs')
                if f['symbol_section']>0:
                    image,_=coff.readonly_section(member(r),f['symbol_section'],c.coff_name)
                    if image!=c.pe_bytes_at(target,base-f['symbol_offset'],len(image)):
                        raise ValueError('3DNow defined readonly reference loses its own whole source image')
                observed.add(('readonly',f['symbol']));continue
            else:
                section=sections.get((off,f['symbol_section']))
                if (section is None or base!=int(section['base'],16)+f['symbol_offset']
                        or not 0<=f['symbol_offset']+f['addend']<section['size']):
                    raise ValueError('3DNow data loses its full source member/section/definition')
                observed.add(('data',off,f['symbol_section']))
            if key in catalog and catalog[key]!=base:raise ValueError('3DNow local symbol is inconsistent')
            catalog[key]=base
    if {t for t in observed if t[0]=='data'}!={('data',off,n) for off,n in sections}:
        raise ValueError('3DNow includes an unobserved whole data image')
    old_sdk={r['address']:r for r in rows('config/sdk-origin-evidence.csv')}
    for r in m['controls']:
        address=int(r['address'],16);body=member(r)
        raw,fields,source=(extra.section_carrier(body,2,c,coff) if r['kind']=='whole-math-section' else carrier.code_carrier(body,r['symbol'],c,coff))
        if source!=r['source'] or fields!=r['fields'] or len(raw)!=r['size'] or digest(raw)!=r['source_sha256']:
            raise ValueError('3DNow whole source code/entries/AUX/fields differ')
        if image_permissions(target,address,len(raw))!=source['flags']&0xe0000000:
            raise ValueError('3DNow complete code loses its original PE execute/read permissions')
        linked,calls,data=bind(raw,fields,r['bindings'],catalog,r['member_offset'],address)
        if linked!=c.pe_bytes_at(target,address,len(raw)) or digest(linked)!=r['body_sha256']:raise ValueError('3DNow complete unmasked code carrier differs')
        proof=extra.math_partitions(linked,address,source,fields,data) if r['kind']=='whole-math-section' else extra.flow(linked,address,[p['offset'] for p in source['peers']],fields,calls,data,r['switch'])
        if proof!=r['flow']:raise ValueError('3DNow whole code/table/tail/padding CFG differs')
        snapshots=r['entries'] if r['kind']=='whole-math-section' else [dict(address=r['address'],function=r['function'],origin=r['origin'])]
        for snap in snapshots:
            a=snap['address']
            if a not in selected and (functions.get(a)!=snap['function'] or origins.get(a)!=snap['origin']):raise ValueError('3DNow alters prior/non-inventory source entries')
        extent=len(raw) if r['kind']=='whole-math-section' else proof['extent']
        known={s['address'] for s in snapshots}
        if any(address<int(a,16)<address+extent and a not in known for a in functions):raise ValueError('3DNow whole source extent hides an inventoried entry')
        if r['old_sdk_record'] is not None and old_sdk.get(r['address'])!=r['old_sdk_record']:raise ValueError('3DNow original R008 implementation owner changes')
    for r in m['pending']:
        snapshots_differ=functions[r['address']]!=r['function'] or origins[r['address']]!=r['origin']
        if ((snapshots_differ and not module('x3d_dispatch_transition','verify-sdk-dispatch-origins.py').allows_transition(
                r['address'],r['function'],r['origin'],functions[r['address']],origins[r['address']]))
                or digest(c.pe_bytes_at(target,int(r['address'],16),r['size']))!=r['body_sha256']):
            raise ValueError('3DNow changes deferred CPU/table/public context')
    print('R191 origins OK:17 whole library functions /7194 bytes;69 full source carriers /30525 bytes and498 actual fields;initializer550 with62 callback fields;three full local eight-way switches /96 bytes;whole math code3256/writable data344 with20 real names at19 entries,one source alias and one encoded internal call;whole readonly8 and three prior readonly sections;historical CPU221/public6/328 source/body context retained with immutable R192 snapshot transitions;no source/ABI/mapping/exact credit.')
    return 0


if __name__=='__main__':
    try:raise SystemExit(main())
    except (ValueError,OSError,KeyError,struct.error) as exc:
        print('3DNow origin verification failed: '+str(exc),file=sys.stderr);raise SystemExit(1)
