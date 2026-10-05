#!/usr/bin/env python3
"""Replay whole original PNG/YCbCr policy source and source-scoped mutable packed data."""
import argparse
import collections
import importlib.util
import json
from pathlib import Path
import struct
import capstone

ROOT=Path(__file__).resolve().parents[1]
_SPEC=importlib.util.spec_from_file_location('png_packed_prior',ROOT/'scripts/verify-sdk-presentation-origins.py')
BASE=importlib.util.module_from_spec(_SPEC);_SPEC.loader.exec_module(BASE)
module=BASE.module
digest=BASE.digest
bind_fields=BASE.bind_fields


def metadata_digest(value):
    return digest(json.dumps(value,sort_keys=True,separators=(',',':')).encode())


def verify_plan(m):
    if (m['evidence_id']!='R203' or {r['address']:r['size'] for r in m['functions']}!=KEYS
            or len(m['functions'])!=6):
        raise ValueError('PNG/packed complete bounded cohort differs')
    for key,expected in PLAN_DIGESTS.items():
        if metadata_digest(m[key])!=expected:
            raise ValueError('PNG/packed frozen complete provenance differs: '+key)
    code=[r for r in m['sections'] if r['kind']=='code'];by={r['base']:r for r in code}
    if (len(m['sections'])!=14 or len(code)!=6 or len(by)!=6
            or sum(r['size'] for r in m['sections'])!=3056
            or sum(len(r.get('fields',[])) for r in m['sections'])!=72
            or len(m['anchors'])!=20 or m['retained_unknown'] or m['interiors']
            or m['imports'] or m['weak_references'] or m['alias_anchors'] or m['foreign_guids']):
        raise ValueError('PNG/packed complete source graph or preserved scope differs')
    for r in m['functions']:
        old=r['original_function'];source=by[r['address']]
        confidence='whole-original-sdk-png-read-quantize-and-packed-ycbcr-policy-with-scoped-fields-complete-source-data-and-cold-pointer-only-interfaces'
        if (r['original_origin']['origin']!='unknown' or old['status']!='unclassified'
                or old['match_percent']!='0.00' or int(old['size'])!=r['size']
                or any(old[k] for k in ['source_file','owner','calling_convention','signature'])
                or source['function']!=old or source['origin']!=r['original_origin']
                or source['symbol']!=r['symbol'] or r['symbol'].startswith('??')
                or source['flow']['code_size']!=r['size'] or r['code_size']!=r['size']
                or r['accepted_function']!=dict(old,proposed_name=r['symbol'],module='D3DX8',status='excluded',
                    owner='library',evidence='R203',notes=r['notes'])
                or r['accepted_origin']!=dict(address=r['address'],origin='library',subsystem='D3DX8',disposition='exclude',
                    confidence=confidence,evidence_id='R203')):
            raise ValueError('PNG/packed changes original extent or gives private/source/ABI/exact credit')
        refs=[dict(owner=q['base'],kind=q['kind'],field=b) for q in m['sections'] for b in q.get('bindings',[])
              if b['target_address']==r['address'] and b['symbol_type']==32]
        if m['policy_references'][r['address']]!=refs:
            raise ValueError('PNG/packed genuine typed source references differ')
    if sum(r['size'] for r in m['functions'])!=2807 or len(m['packed_observations'])!=2:
        raise ValueError('PNG/packed complete policy and opcode observations differ')


def check_public(body,emission,flow):
    original={
        'ProbePngReadInit':'?png_read_init@D3DX@@YAXPAUpng_struct_def@1@@Z',
        'ProbePngReadRows':'?png_read_rows@D3DX@@YAXPAUpng_struct_def@1@PAPAE1K@Z',
        'ProbePngReadEnd':'?png_read_end@D3DX@@YAXPAUpng_struct_def@1@PAUpng_info_struct@1@@Z',
        'ProbePngDither':'?png_set_dither@D3DX@@YAXPAUpng_struct_def@1@PAUpng_color_struct@1@HHPAGH@Z',
        'ProbeYcbcr':'?MYCbCrA2RGBA@D3DX@@YAXHPAE0000@Z',
        'ProbeYcbcrLegacy':'?MYCbCrA2RGBALegacy@D3DX@@YAXHPAE0000@Z',
    }
    packed={'ProbePackedCenter':['psubsw'],'ProbePackedDot':['pmaddwd'],'ProbePackedHalf':['psrad'],
            'ProbePackedNarrow':['packssdw','packuswb'],'ProbePackedInterleave':['punpcklbw'],
            'ProbePackedKeepState':['psubsw']}
    seen=set()
    for r in emission:
        defs=[d for d in r['definitions'] if d['type']==32]
        if not defs:continue
        if len(defs)!=1 or defs[0]['offset']:
            raise ValueError('PNG/packed cold control is not one whole function')
        name=defs[0]['symbol'].split('@@')[0][1:];seen.add(name)
        h=struct.unpack_from('<8sIIIIIIHHI',body,20+(r['section']-1)*40)
        raw=body[h[4]:h[4]+h[3]];ins=flow.instructions(raw,0,len(raw))
        fields=[(f['type'],f['symbol']['symbol']) for f in r['fields']]
        if name in original:
            if fields!=[('REL32',original[name])] or len(ins)!=1 or ins[0].mnemonic!='jmp' or len(raw)!=5:
                raise ValueError('PNG/packed pointer-only original COFF interface/tail lowering differs')
        elif name in packed:
            if (any(not any(i.mnemonic==op for i in ins) for op in packed[name])
                    or len([i for i in ins if i.mnemonic=='emms'])!=(0 if name=='ProbePackedKeepState' else 1)
                    or fields!=[('DIR32','___security_cookie'),('REL32','@__security_check_cookie@4')]
                    or ins[-1].mnemonic!='ret' or ins[-1].operands
                    or not any(i.mnemonic=='movq' and i.operands[0].type==capstone.x86.X86_OP_MEM for i in ins)):
                raise ValueError('PNG/packed complete generic intrinsic/reset/cookie/store control differs')
            if name=='ProbePackedHalf' and not any(i.mnemonic=='psrad' and i.operands[-1].imm==1 for i in ins):
                raise ValueError('PNG/packed generic half policy differs')
        else:raise ValueError('PNG/packed unexpected cold observation')
    if seen!=set(original)|set(packed):
        raise ValueError('PNG/packed complete original interfaces/intrinsic alternatives absent')


def check_packed(m,c,flow):
    target=c.verified_target()
    for q in m['packed_observations']:
        r=next(r for r in m['sections'] if r['base']==q['address']);a=int(q['address'],16)
        raw=c.pe_bytes_at(target,a,r['size']);ins=flow.instructions(raw,a,r['size'])
        if (dict(sorted(collections.Counter(i.mnemonic for i in ins).items()))!=q['instruction_mnemonics']
                or [i.address-a for i in ins if i.mnemonic=='emms']!=q['emms_offsets'] or q['emms_offsets']
                or q['whole_data_references']!=r['bindings'] or q['return_cleanup']!=r['flow']['returns']
                or any(f['type']!='DIR32' or f['symbol_storage']!=3 for f in r['fields'])):
            raise ValueError('PNG/packed whole original MMX state/scoped data observation differs')
        invert=[f['symbol_offset'] for f in r['fields'] if f['symbol']=='_const_invert']
        if invert!=([40,40] if q['address']=='0x0062E58F' else []):
            raise ValueError('PNG/packed legacy actual scoped invert fields differ')
    for a,size,kind in [('0x0066E2A8',48,'data'),('0x0068E280',8,'bss')]:
        r=next(r for r in m['sections'] if r['base']==a)
        flags=r['source']['flags'] if kind=='data' else r['flags']
        if (r['kind']!=kind or r['size']!=size or flags&0xe0000000!=0xc0000000
                or any(d['storage']!=3 for d in r.get('source',{}).get('definitions',r.get('definitions',[])))):
            raise ValueError('PNG/packed full writable source-static initial data differs')


def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--evidence-only',action='store_true');args=p.parse_args()
    m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    for path,sha in [(EVIDENCE,MANIFEST_SHA256),(m['public_control']['probe'],m['public_control']['probe_sha256']),*m['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes())!=sha:
            raise ValueError('PNG/packed immutable source or retained provenance differs: '+path)
    BASE.replay(m,args.evidence_only)
    c=module('png_packed_coff','compare-coff-function.py');coff=module('png_packed_data','coff_data.py')
    flow=module('png_packed_flow','sdk_image_carriers.py')
    check_packed(m,c,flow)
    module('png_packed_cold','verify-sdk-blit-origins.py').cold_control(m['public_control'],'PngPacked',check_public,c,coff,flow)
    print('R203 origins OK:6 complete SDK/bundled PNG/YCbCr library policies2807;'
          '14 whole source sections3056/all72 fields,six complete CFGs;20 complete retained anchors3376/161 fields;'
          'full source-scoped writable coefficient48/BSS8 initial images,legacy invert fields and original MMX state retained;'
          '13 cold ordinary sections,12 full interface/intrinsic controls359,two original headers and readonly observation24;'
          'private PNG tags are pointer-only;no private layout/source/canonical ABI/mapping/exact credit.')
    return 0


EVIDENCE = 'config/sdk-png-packed-origin-evidence.json'
MANIFEST_SHA256 = 'c3112e66bfce14d918e18c666ba26220ee70bae92b79875fa02f8ffbbb13d532'
KEYS = {'0x0062E461': 302, '0x0062E58F': 316, '0x006227F1': 192, '0x00622DFD': 122, '0x00622EC4': 256, '0x006235B9': 1619}
PLAN_DIGESTS = {'sections': '237836d5cf9077fb9f4bac1c9accd2556ac148556965b3e96e8eb381b646f3a6', 'anchors': '30869cdeba155d5cfbdabb4d13bbeb1270b9a14d0550b35d2398b12e023d1f99', 'data_anchors': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'foreign_guids': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'alias_anchors': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'interiors': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'retained_unknown': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'policy_references': '8c1e841847a62f3ba75be1da56dc17303600900c05ef73c7a8925d214620c215', 'public_control': '9561b9d4f90e9f72fc0a92b33844bfcee15a703c0d579787aa9eb811cbe7b7c4', 'absolute': '8e1f56739e02ad0900ff6fe1a81eecb7cfcf9597595512608c6e532445948d11', 'imports': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'weak_references': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'probe': '16bfe14069eae6a811520523832b62b9df45d057f24e8d0a9f5414b451672a16', 'profile': 'edbcdcf806e9869ccdd785e3c9e574a3734df2e10de3d8a70a694bb4a8e89307', 'headers': 'ea6cb00e0cd7986b212b6e6e1f220319d96b8ff32cb7c1faf5b4a474af61e00a', 'emission': '1a290b8f556201c105733da741889e1e6b6b8aed3422669eae6f858257cfcd92', 'layout': 'd0abe3567d07fd00f58b5b48314d56d6c8af186ae636c674dd8f7a2f1162427a', 'retained_sha256': '782652192ca017bd69d2d040fdf8743bfee98c70106762cc87a8681bc67e2a05', 'game_parents': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'uuid_archive_sha256': '89cf9b03328ef4655c6df7206142964a22d95e8e823ad689d3d2e7ab792ad31b', 'packed_observations': '655e07c4c68de53f5d5fecc6e08740ddc28d9a39e01c6ffe3dbc0c6d347c886d'}

if __name__=='__main__':
    raise SystemExit(main())
