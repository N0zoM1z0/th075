#!/usr/bin/env python3
"""Replay complete original SDK shader/resource/font policies and public declarations."""
import argparse
import importlib.util
import json
from pathlib import Path
import struct
import capstone

ROOT=Path(__file__).resolve().parents[1]
_SPEC=importlib.util.spec_from_file_location('shader_font_prior',ROOT/'scripts/verify-sdk-presentation-origins.py')
BASE=importlib.util.module_from_spec(_SPEC);_SPEC.loader.exec_module(BASE)
module=BASE.module
digest=BASE.digest
bind_fields=BASE.bind_fields


def metadata_digest(value):
    return digest(json.dumps(value,sort_keys=True,separators=(',',':')).encode())


def verify_plan(m):
    if (m['evidence_id']!='R201' or {r['address']:r['size'] for r in m['functions']}!=KEYS
            or len(m['functions'])!=15):
        raise ValueError('Shader/font complete bounded policy cohort differs')
    for key,expected in PLAN_DIGESTS.items():
        if metadata_digest(m[key])!=expected:
            raise ValueError('Shader/font frozen complete provenance differs: '+key)
    code=[r for r in m['sections'] if r['kind']=='code'];by={r['base']:r for r in code}
    if (len(m['sections'])!=41 or len(code)!=35 or len(by)!=34
            or sum(r['size'] for r in m['sections'])!=5781
            or sum(len(r.get('fields',[])) for r in m['sections'])!=152
            or len(m['anchors'])!=22 or len(m['retained_unknown'])!=8
            or sum(r['size'] for r in m['retained_unknown'])!=685
            or len(m['interiors'])!=14 or sum(int(r['function']['size']) for r in m['interiors'])!=154
            or len(m['imports'])!=12 or m['weak_references']):
        raise ValueError('Shader/font complete source graph or retained lifetime scope differs')
    for r in m['functions']:
        old=r['original_function'];source=by[r['address']]
        confidence='whole-original-sdk-shader-resource-font-policy-with-scoped-fields-original-public-headers-and-independent-uuid-stack-alias'
        if (r['original_origin']['origin']!='unknown' or old['status']!='unclassified'
                or old['match_percent']!='0.00' or int(old['size'])!=r['size']
                or any(old[k] for k in ['source_file','owner','calling_convention','signature'])
                or source['function']!=old or source['origin']!=r['original_origin']
                or source['symbol']!=r['symbol'] or r['symbol'].startswith('??')
                or source['flow']['code_size']!=r['size'] or r['code_size']!=r['size']
                or r['accepted_function']!=dict(old,proposed_name=r['symbol'],module='D3DX8',status='excluded',
                    owner='library',evidence='R201',notes=r['notes'])
                or r['accepted_origin']!=dict(address=r['address'],origin='library',subsystem='D3DX8',disposition='exclude',
                    confidence=confidence,evidence_id='R201')):
            raise ValueError('Shader/font changes original extent or gives private/lifetime/source/ABI/exact credit')
        refs=[dict(owner=q['base'],kind=q['kind'],field=b) for q in m['sections'] for b in q.get('bindings',[])
              if b['target_address']==r['address'] and b['symbol_type']==32]
        if m['policy_references'][r['address']]!=refs or (r['size']<=38 and not refs):
            raise ValueError('Shader/font short policy lacks complete genuine typed source references')
    if sum(r['size'] for r in m['functions'])!=1403:
        raise ValueError('Shader/font full policy extents differ')


def check_public(body,emission,flow):
    external={
        'ProbeShaderFileA':'_D3DXAssembleShaderFromFileA@20',
        'ProbeShaderFileW':'_D3DXAssembleShaderFromFileW@20',
        'ProbeShaderResourceA':'_D3DXAssembleShaderFromResourceA@24',
        'ProbeShaderResourceW':'_D3DXAssembleShaderFromResourceW@24',
        'ProbeErrorTextW':'_D3DXGetErrorStringW@12',
        'ProbeCreateFont':'_D3DXCreateFontIndirect@12',
        'ProbeResourceA':'__imp__FindResourceA@12',
        'ProbeResourceW':'__imp__FindResourceW@12',
        'ProbeResourceLoad':'__imp__LoadResource@8',
        'ProbeResourceSize':'__imp__SizeofResource@8',
        'ProbeResourceLock':'__imp__LockResource@4',
        'ProbeGdiFont':'__imp__CreateFontIndirectA@4',
        'ProbeGdiDelete':'__imp__DeleteObject@4',
        'ProbeToWide':'__imp__MultiByteToWideChar@24',
        'ProbeToAnsi':'__imp__WideCharToMultiByte@32',
    }
    seen=set()
    for r in emission:
        defs=[d for d in r['definitions'] if d['type']==32]
        if not defs:continue
        if len(defs)!=1 or defs[0]['offset']:
            raise ValueError('Shader/font cold control is not a complete ordinary function')
        name=defs[0]['symbol'].split('@@')[0][1:];seen.add(name)
        h=struct.unpack_from('<8sIIIIIIHHI',body,20+(r['section']-1)*40)
        raw=body[h[4]:h[4]+h[3]];ins=flow.instructions(raw,0,len(raw))
        fields=[(f['type'],f['symbol']['symbol']) for f in r['fields']]
        calls=[i for i in ins if i.group(capstone.CS_GRP_CALL)]
        returns=[i for i in ins if i.group(capstone.CS_GRP_RET)]
        if len(returns)!=1 or ins[-1] is not returns[0] or returns[0].operands:
            raise ValueError('Shader/font complete ordinary control return differs')
        if name in external:
            sn=external[name];iat=sn.startswith('__imp__')
            if fields!=[('DIR32' if iat else 'REL32',sn)] or len(calls)!=1:
                raise ValueError('Shader/font original public/import declaration differs')
            call=calls[0];at=r['fields'][0]['offset']
            if (iat and (bytes(call.bytes[:2])!=b'\xff\x15' or call.address+call.disp_offset!=at)
                    or not iat and (call.mnemonic!='call' or raw[at-1]!=0xe8 or call.address+call.imm_offset!=at)):
                raise ValueError('Shader/font cold genuine IAT/direct call opcode differs')
        elif name=='ProbeFontTextW':
            if (fields or len(calls)!=1 or calls[0].operands[0].type!=capstone.x86.X86_OP_MEM
                    or calls[0].operands[0].mem.disp!=28):
                raise ValueError('Shader/font original public wide font draw slot differs')
        elif name=='ProbeWideStorage':
            if fields!=[('REL32','__alloca_probe'),('REL32','_ProbeUseWideStorage')]:
                raise ValueError('Shader/font natural WCHAR storage lowering differs')
            call=next(i for i in ins if i.address+1==r['fields'][0]['offset'])
            if (call.mnemonic!='call' or [(i.mnemonic,i.op_str) for i in ins[4:7]]!=[
                    ('lea','eax, [esi + esi]'),('add','eax, 3'),('and','eax, 0xfffffffc')]):
                raise ValueError('Shader/font dynamic stack helper loses actual EAX WCHAR/alignment protocol')
        else:raise ValueError('Shader/font unexpected public control')
    if seen!=set(external)|{'ProbeFontTextW','ProbeWideStorage'}:
        raise ValueError('Shader/font complete original public controls absent')
    m=json.loads((ROOT/EVIDENCE).read_text())
    expected={'?ShaderFontIUnknown@@3U_GUID@@B':m['foreign_guids'][0]['record']['source_sha256'],
              '_IID_ID3DXFont':next(r['source_sha256'] for r in m['sections'] if r.get('symbol')=='_IID_ID3DXFont')}
    for symbol,sha in expected.items():
        rows=[r for r in emission if any(d['symbol']==symbol and not d['offset'] for d in r['definitions'])]
        if len(rows)!=1 or rows[0]['fields'] or rows[0]['size']!=16:
            raise ValueError('Shader/font cold complete GUID definition differs')
        h=struct.unpack_from('<8sIIIIIIHHI',body,20+(rows[0]['section']-1)*40)
        if digest(body[h[4]:h[4]+h[3]])!=sha:
            raise ValueError('Shader/font public GUID differs from complete original source')


def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--evidence-only',action='store_true');args=p.parse_args()
    m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    for path,sha in [(EVIDENCE,MANIFEST_SHA256),(m['public_control']['probe'],m['public_control']['probe_sha256']),*m['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes())!=sha:
            raise ValueError('Shader/font immutable source or retained provenance differs: '+path)
    # Shared replay independently reopens every source owner and all genuine
    # fields; no native destination is used to populate its source catalog.
    BASE.replay(m,args.evidence_only)
    c=module('shader_font_public_coff','compare-coff-function.py');coff=module('shader_font_public_data','coff_data.py')
    flow=module('shader_font_public_flow','sdk_image_carriers.py')
    control=module('shader_font_cold','verify-sdk-blit-origins.py')
    control.cold_control(m['public_control'],'ShaderFont',check_public,c,coff,flow)
    print('R201 origins OK:15 complete SDK shader/resource/font policies1403;'
          '41 whole source sections5781/all152 fields,35 complete CFGs/34 native code bases;22 complete retained anchors4688/121 fields;'
          '12 genuine imports,original UUID IUnknown16 and full chkstk/alloca alias61;'
          'eight lifetime alternatives685 and14 interior compiler rows154 unchanged;'
          '66 cold ordinary sections,17 whole public controls437,86 original headers and full readonly public layout88;'
          'no private owner/layout/source/ABI/mapping/exact credit.')
    return 0


EVIDENCE = 'config/sdk-shader-font-origin-evidence.json'
MANIFEST_SHA256 = 'ac84edce06f5a9b4381dfe01d3f8f74db3ff087301b77edf7f6a2e484ffed584'
KEYS = {'0x00604A10': 140, '0x00604A9C': 201, '0x00604B65': 142, '0x00604BF3': 143, '0x00604F55': 91, '0x00604FB0': 111, '0x0060EA96': 142, '0x00608DD5': 94, '0x0060EA77': 31, '0x0061FAB2': 117, '0x00608F1F': 68, '0x00608EB2': 38, '0x00608ED8': 38, '0x0061F42F': 35, '0x0061F452': 12}
PLAN_DIGESTS = {'sections': '12168442ce3654816e81a3ebb7b24deff688f2a751110634cc9eed1932273cd6', 'anchors': '4e4976d9340d476db969d75405f202d011d160d6f4451d6314fa188d6e7cb562', 'data_anchors': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'foreign_guids': '6f5e12af7f2d24e72d80afd3a9248fe6f5fb533b28a9e9e3065a8eb6acb1a4b5', 'alias_anchors': '8cc430d076ec30230e262ce2d4270397acf57c6a9832c412264d553011bfc169', 'interiors': '980aa5992ab6a9d61d4cd90316275dc8166596e604eb9a5c085ccc2ac1f97ff5', 'retained_unknown': '3974e81f27863689a8b48901dc135d3419f9683522721e4f0b95c73d19cad0ac', 'policy_references': '57ae12017674b6e6ecfc5c049c10992d80a3dacbe733e922842c57991f787f54', 'public_control': 'c0c38f9db330411a2162655c9739c3117ca43a3e524a82a4d35b86c5fc1420a3', 'absolute': '8e1f56739e02ad0900ff6fe1a81eecb7cfcf9597595512608c6e532445948d11', 'imports': '22b12173fbd7001b525124c715cfb88fb76eed54c22f58516f41fc437fa6ad6d', 'weak_references': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'probe': '16bfe14069eae6a811520523832b62b9df45d057f24e8d0a9f5414b451672a16', 'profile': 'edbcdcf806e9869ccdd785e3c9e574a3734df2e10de3d8a70a694bb4a8e89307', 'headers': 'ea6cb00e0cd7986b212b6e6e1f220319d96b8ff32cb7c1faf5b4a474af61e00a', 'emission': '1a290b8f556201c105733da741889e1e6b6b8aed3422669eae6f858257cfcd92', 'layout': 'd0abe3567d07fd00f58b5b48314d56d6c8af186ae636c674dd8f7a2f1162427a', 'retained_sha256': 'aa7d46846af4bec64b7f9bc93bcfa27a3bb0f1d89dc54a5a8429fa6a8923dfc2', 'game_parents': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'uuid_archive_sha256': '89cf9b03328ef4655c6df7206142964a22d95e8e823ad689d3d2e7ab792ad31b'}

if __name__=='__main__':
    raise SystemExit(main())
