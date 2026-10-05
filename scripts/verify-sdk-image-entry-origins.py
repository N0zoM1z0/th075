#!/usr/bin/env python3
"""Replay complete SDK image/surface/volume/texture entries and real peer distinctions."""
import argparse
import importlib.util
import json
from pathlib import Path
import struct
import capstone

ROOT=Path(__file__).resolve().parents[1]
_SPEC=importlib.util.spec_from_file_location('image_entry_prior',ROOT/'scripts/verify-sdk-presentation-origins.py')
BASE=importlib.util.module_from_spec(_SPEC);_SPEC.loader.exec_module(BASE)
module=BASE.module
digest=BASE.digest
bind_fields=BASE.bind_fields


def metadata_digest(value):
    return digest(json.dumps(value,sort_keys=True,separators=(',',':')).encode())


def verify_plan(m):
    if (m['evidence_id']!='R202' or {r['address']:r['size'] for r in m['functions']}!=KEYS
            or len(m['functions'])!=32):
        raise ValueError('Image entry complete bounded cohort differs')
    for key,expected in PLAN_DIGESTS.items():
        if metadata_digest(m[key])!=expected:
            raise ValueError('Image entry frozen complete provenance differs: '+key)
    code=[r for r in m['sections'] if r['kind']=='code'];by={r['base']:r for r in code}
    if (len(m['sections'])!=44 or len(code)!=41 or len(by)!=41
            or sum(r['size'] for r in m['sections'])!=5899
            or sum(len(r.get('fields',[])) for r in m['sections'])!=174
            or len(m['anchors'])!=23 or len(m['retained_unknown'])!=4
            or sum(r['size'] for r in m['retained_unknown'])!=120
            or len(m['interiors'])!=2 or sum(int(r['function']['size']) for r in m['interiors'])!=16
            or len(m['imports'])!=1 or m['weak_references'] or m['alias_anchors'] or m['foreign_guids']):
        raise ValueError('Image entry complete graph or protected scope differs')
    for r in m['functions']:
        old=r['original_function'];source=by[r['address']]
        confidence='whole-original-sdk-image-surface-volume-texture-entry-policy-with-scoped-source-fields-complete-backward-exits-and-cold-public-abi'
        if (r['original_origin']['origin']!='unknown' or old['status']!='unclassified'
                or old['match_percent']!='0.00' or int(old['size'])!=r['size']
                or any(old[k] for k in ['source_file','owner','calling_convention','signature'])
                or source['function']!=old or source['origin']!=r['original_origin']
                or source['symbol']!=r['symbol'] or r['symbol'].startswith('??')
                or source['flow']['code_size']!=r['size'] or r['code_size']!=r['size']
                or r['accepted_function']!=dict(old,proposed_name=r['symbol'],module='D3DX8',status='excluded',
                    owner='library',evidence='R202',notes=r['notes'])
                or r['accepted_origin']!=dict(address=r['address'],origin='library',subsystem='D3DX8',disposition='exclude',
                    confidence=confidence,evidence_id='R202')):
            raise ValueError('Image entry changes original extent or gives private/lifetime/source/ABI/exact credit')
        refs=[dict(owner=q['base'],kind=q['kind'],field=b) for q in m['sections'] for b in q.get('bindings',[])
              if b['target_address']==r['address'] and b['symbol_type']==32]
        if m['policy_references'][r['address']]!=refs:
            raise ValueError('Image entry genuine typed source references differ')
    if sum(r['size'] for r in m['functions'])!=3121 or len(m['rejected_peers'])!=8:
        raise ValueError('Image entry full policy and peer alternatives differ')
    for r in m['rejected_peers']:
        source=by[r['source_owner']['positive_address']]
        if (source['symbol']!=r['symbol'] or by[r['address']]['symbol']==r['symbol']
                or source['size']!=r['size'] or source['member_offset']!=r['source_owner']['member_offset']
                or source['source']['section']!=r['source_owner']['section']
                or source['source_sha256']!=r['source_owner']['source_sha256']
                or by[r['address']]['body_sha256']!=r['native_sha256']):
            raise ValueError('Image entry source fingerprint peer loses its independent whole owner')


def check_public(body,emission,flow):
    expected=json.loads((ROOT/EVIDENCE).read_text())['public_control']['apis'];seen=set()
    for r in emission:
        defs=[d for d in r['definitions'] if d['type']==32]
        if not defs:continue
        if len(defs)!=1 or defs[0]['offset']:
            raise ValueError('Image entry public control is not one whole function')
        name=defs[0]['symbol'].split('@@')[0][1:];seen.add(name)
        h=struct.unpack_from('<8sIIIIIIHHI',body,20+(r['section']-1)*40)
        raw=body[h[4]:h[4]+h[3]];ins=flow.instructions(raw,0,len(raw))
        calls=[i for i in ins if i.group(capstone.CS_GRP_CALL)]
        fields=[(f['type'],f['symbol']['symbol']) for f in r['fields']]
        if (name not in expected or fields!=[('REL32',expected[name])] or len(calls)!=1
                or calls[0].address+calls[0].imm_offset!=r['fields'][0]['offset']
                or calls[0].mnemonic!='call' or ins[-1].mnemonic!='ret' or ins[-1].operands):
            raise ValueError('Image entry original whole public WINAPI declaration/call differs')
    if seen!=set(expected) or len(seen)!=32:
        raise ValueError('Image entry complete public alternatives absent')


def check_backwards(m,c,flow):
    target=c.verified_target()
    for address,jump,destination,size in [('0x00607005',182,116,184),('0x00607263',186,120,188)]:
        r=next(q for q in m['sections'] if q['base']==address);a=int(address,16)
        raw=c.pe_bytes_at(target,a,size);ins=flow.instructions(raw,a,size)
        if (r['size']!=size or ins[-1].address!=a+jump or ins[-1].mnemonic!='jmp'
                or ins[-1].operands[0].type!=capstone.x86.X86_OP_IMM
                or ins[-1].operands[0].imm!=a+destination
                or not any(i.address==a+destination for i in ins)
                or len(r['flow']['returns'])!=1 or r['flow']['returns'][0]['cleanup']!=36
                or r['flow']['reachable_instruction_count']!=r['flow']['instruction_count']):
            raise ValueError('Image entry complete backward cleanup/return source extent differs')


def check_peers(m,c,coff):
    # Called only after full source/catalog replay. Reopen each entire rejected
    # source carrier, and rebase only its genuine independently owned fields.
    rt=module('image_entry_archive','verify-runtime-origins.py');extra=module('image_entry_sections','sdk_x3d_carriers.py')
    raw_archive=(ROOT/'.tools/msvc710/Vc7/PlatformSDK/Lib/d3dx8.lib').read_bytes()
    if digest(raw_archive)!=m['archive_sha256']:raise ValueError('Image entry peer archive differs')
    members={o:(n,b) for o,n,b in rt.archive_members(raw_archive)};target=c.verified_target();catalog={}
    for r in m['sections']:
        for d in r.get('source',{}).get('definitions',[]):
            if d['storage']==2:catalog[d['symbol']]=int(r['base'],16)+d['offset']
    for r in m['anchors']:
        catalog[r['record'].get('symbol',r['record'].get('coff_symbol'))]=int(r['address'],16)
    for r in m['rejected_peers']:
        owner=r['source_owner'];positive=next(q for q in m['sections'] if q['base']==owner['positive_address'])
        name,body=members[owner['member_offset']]
        raw,fields,source=extra.section_carrier(body,owner['section'],c,coff)
        if (name!=positive['member'] or digest(body)!=positive['member_sha256'] or source!=positive['source']
                or fields!=positive['fields'] or len(raw)!=r['size'] or digest(raw)!=owner['source_sha256']):
            raise ValueError('Image entry peer complete original source/fields differ')
        a=int(r['address'],16);native=c.pe_bytes_at(target,a,len(raw))
        linked,_,_=bind_fields(raw,fields,positive['bindings'],catalog,owner['member_offset'],a)
        actual=[];bad_bytes=set()
        for f,b in zip(fields,positive['bindings']):
            at=f['offset']
            dest=(a+at+4+struct.unpack_from('<i',native,at)[0])&0xffffffff if f['type']=='REL32' else struct.unpack_from('<I',native,at)[0]
            if dest!=int(b['target_address'],16):
                actual.append(dict(symbol=f['symbol'],native=f'0x{dest:08X}',independent=b['source_base']))
                bad_bytes.update(range(at,at+4))
        differences={i for i,(x,y) in enumerate(zip(linked,native)) if x!=y}
        if (digest(native)!=r['native_sha256'] or actual!=r['conflicts'] or not differences
                or not differences.issubset(bad_bytes)):
            raise ValueError('Image entry peer is cropped/masked or lacks its real source-callee distinction')


def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--evidence-only',action='store_true');args=p.parse_args()
    m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    for path,sha in [(EVIDENCE,MANIFEST_SHA256),(m['public_control']['probe'],m['public_control']['probe_sha256']),*m['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes())!=sha:
            raise ValueError('Image entry immutable source or retained provenance differs: '+path)
    BASE.replay(m,args.evidence_only)
    c=module('image_entry_coff','compare-coff-function.py');coff=module('image_entry_data','coff_data.py')
    flow=module('image_entry_flow','sdk_image_carriers.py')
    check_backwards(m,c,flow);check_peers(m,c,coff)
    module('image_entry_cold','verify-sdk-blit-origins.py').cold_control(m['public_control'],'ImageEntry',check_public,c,coff,flow)
    print('R202 origins OK:32 complete SDK image/surface/volume/texture entry policies3121;'
          '44 whole source sections5899/all174 fields,41 complete CFGs;23 whole retained anchors5415/92 fields;one genuine GDI import;'
          'two whole backward cleanup/return extents184/188 and eight complete real surface/volume peer alternatives;'
          'four lifetime alternatives120/two interior compiler rows16 unchanged;'
          '80 cold ordinary sections,32 whole public controls1832,85 original headers and full readonly layout92;'
          'no private owner/layout/source/ABI/mapping/exact credit.')
    return 0


EVIDENCE = 'config/sdk-image-entry-origin-evidence.json'
MANIFEST_SHA256 = '8a89de63380fd8916fcede566c1fbf241f775c45db4f5873f7921b623ca2d8a7'
KEYS = {'0x006053D2': 56, '0x006054EF': 176, '0x006056CE': 176, '0x00606EFF': 63, '0x00606F3E': 63, '0x00606F7D': 68, '0x00606FC1': 68, '0x00607005': 184, '0x00607263': 188, '0x00607C96': 81, '0x00607CE7': 81, '0x00607D38': 86, '0x00607D8E': 86, '0x00607DE4': 81, '0x00607E35': 81, '0x00607E86': 86, '0x00607EDC': 86, '0x006085A5': 64, '0x006085E5': 64, '0x00608625': 65, '0x00608666': 99, '0x006086C9': 99, '0x0060872C': 104, '0x00608794': 104, '0x0060882C': 96, '0x0060888C': 96, '0x006088EC': 101, '0x00608951': 101, '0x006089E6': 102, '0x00608A4C': 102, '0x00608AB2': 107, '0x00608B1D': 107}
PLAN_DIGESTS = {'sections': 'f24265e902f7992d3926299f55ee1598144e0c5b13c8237759a664b5d7c2e384', 'anchors': '4caee721d4b17022245c27b95f700c87b825fcdf7d7dbfb3b6f9bce1aa2fb33d', 'data_anchors': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'foreign_guids': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'alias_anchors': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'interiors': '57f59a67aae31601b322689ae44318c9acf0f7e435ab32bf6164e1697fdc8b80', 'retained_unknown': '259cd60b9fa478592418d2f4ff8b5deb4fb433484fe3005e513c5930c8d0b842', 'policy_references': '156b78f74f631d6a98669ecae16a77dad49cfc9677a64f60b562655f218f2a2f', 'public_control': '31dc632e972172c4d803bdd1d760799a42d766d0427a03bb92f625e635a5c860', 'absolute': '8e1f56739e02ad0900ff6fe1a81eecb7cfcf9597595512608c6e532445948d11', 'imports': 'c5e7ffcf9645b407b6ee44833f925ecea815066344ea8cbf4bf71c3baccc7dec', 'weak_references': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'probe': '16bfe14069eae6a811520523832b62b9df45d057f24e8d0a9f5414b451672a16', 'profile': 'edbcdcf806e9869ccdd785e3c9e574a3734df2e10de3d8a70a694bb4a8e89307', 'headers': 'ea6cb00e0cd7986b212b6e6e1f220319d96b8ff32cb7c1faf5b4a474af61e00a', 'emission': '1a290b8f556201c105733da741889e1e6b6b8aed3422669eae6f858257cfcd92', 'layout': 'd0abe3567d07fd00f58b5b48314d56d6c8af186ae636c674dd8f7a2f1162427a', 'retained_sha256': '1a56eacae9be4a9af6d2a3db48dd3414fc4bcbd5a18c1e1c0ba38d786a6ecffd', 'game_parents': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'uuid_archive_sha256': '89cf9b03328ef4655c6df7206142964a22d95e8e823ad689d3d2e7ab792ad31b', 'rejected_peers': '66e6401ceb183501db70b918a4020441ec3592a21bb4c2a1ee96961459766ea9'}

if __name__=='__main__':
    raise SystemExit(main())
