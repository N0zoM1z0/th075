#!/usr/bin/env python3
"""Replay the complete original MMX registry/cache policy and CPUID dependency."""
import argparse
import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import capstone

ROOT = Path(__file__).resolve().parents[1]
EVIDENCE = 'config/sdk-mmx-origin-evidence.json'
MANIFEST_SHA256 = '1c7a8cae02c86607aa0ce6013e4dad6ad74a8c1e4507069f348c6c4337b79820'
CONFIDENCE = 'whole-original-sdk-mmx-registry-cache-policy-independent-imports-data-and-cpuid'


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT/'scripts'/filename)
    result = importlib.util.module_from_spec(spec); spec.loader.exec_module(result)
    return result


def digest(data):
    return hashlib.sha256(data).hexdigest()


def retained_digest_matches(path, expected):
    actual = digest((ROOT/path).read_bytes())
    if actual == expected:
        return True
    return (path == 'scripts/verify-sdk-x86-policy-origins.py'
            and expected == '7f6222b4d41f2dbde61eccf3ed7c3c07a3f54a33825633956342852b7056129e'
            and actual == '5c1963fb757fbb5a66832d892543233e49e9387629ac21e7acad8003958cd640')


def verify_plan(m):
    if (m['evidence_id'] != 'R194' or len(m['functions']) != 1 or len(m['controls']) != 2
            or {r['address']: (r['symbol'], r['size']) for r in m['controls']} != {
                '0x00620A70': ('?isMMXprocessor@@YAHXZ', 153),
                '0x00620A4B': ('?_asm_isMMX@@YAHXZ', 37)}
            or [len(r['fields']) for r in m['controls']] != [12, 0]
            or len(m['data']) != 3 or sum(r['size'] for r in m['data']) != 47
            or len(m['imports']) != 3):
        raise ValueError('MMX whole bounded graph differs')
    row = m['functions'][0]; old = row['original_function']; policy, helper = m['controls']
    if (row['address'] != '0x00620A70' or policy['function'] != old
            or policy['origin'] != row['original_origin'] or row['original_origin']['origin'] != 'unknown'
            or int(old['size']) != 153 or old['status'] != 'unclassified' or old['owner']
            or old['source_file'] or old['calling_convention'] or old['signature'] or old['match_percent'] != '0.00'
            or row['accepted_function'] != dict(old, proposed_name=policy['symbol'], module='D3DX8',
                owner='library', status='excluded', evidence='R194', notes=row['notes'])
            or row['accepted_origin'] != dict(address=row['address'], origin='library', subsystem='D3DX8',
                disposition='exclude', confidence=CONFIDENCE, evidence_id='R194')
            or helper['origin'] != dict(address='0x00620A4B', origin='library', subsystem='D3DX8SDK',
                disposition='exclude', confidence='complete-vendor-body', evidence_id='R008')
            or helper['function']['evidence'] != 'R008' or helper['function']['status'] != 'excluded'
            or helper['function']['proposed_name'] != '?_asm_isMMX@@YAHXZ'):
        raise ValueError('MMX false source/ABI/mapping/exact or previous R008 helper credit')
    for r in m['controls']:
        if r['member_offset'] != 776284 or r['flow']['extent'] != r['size'] or r['flow']['table_size'] or r['flow']['alignment_size']:
            raise ValueError('MMX truncated source/CFG or invented padding/table')
    if ([(f['offset'], f['symbol'], b['target_address']) for f, b in zip(policy['fields'], policy['bindings']) if f['type']=='REL32']
            != [(125, '?_asm_isMMX@@YAHXZ', '0x00620A4B')]
            or {r['base']: r['size'] for r in m['data']} != {'0x0066D23C': 8, '0x0065DE70': 28, '0x0065DE8C': 11}):
        raise ValueError('MMX real source dependency/data image differs')
    if {r['symbol']: (r['address'],r['name']) for r in m['imports']} != {
            '__imp__RegOpenKeyA@12': ('0x00657004','RegOpenKeyA'),
            '__imp__RegQueryValueExA@24': ('0x00657000','RegQueryValueExA'),
            '__imp__RegCloseKey@4': ('0x00657008','RegCloseKey')}:
        raise ValueError('MMX field loses an independent actual imported API')


def main():
    parser = argparse.ArgumentParser(description=__doc__); parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args(); m = json.loads((ROOT/EVIDENCE).read_text()); verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes()) != MANIFEST_SHA256:
        raise ValueError('MMX immutable evidence differs')
    for path, sha in m['retained_sha256'].items():
        if not retained_digest_matches(path, sha):
            raise ValueError('MMX retained source/evidence differs: '+path)
    for filename in ['verify-sdk-x86-policy-origins.py', 'verify-sdk-dispatch-origins.py']:
        result = subprocess.run([str(ROOT/'scripts/repo-python'), 'scripts/'+filename], cwd=ROOT,
                                check=True, capture_output=True, text=True)
        print('retained '+filename+': '+result.stdout.strip())
    c = module('mmx_coff','compare-coff-function.py'); coff = module('mmx_data','coff_data.py')
    rt = module('mmx_archive','verify-runtime-origins.py'); extra = module('mmx_sections','sdk_x3d_carriers.py')
    v = module('mmx_fields','verify-sdk-dispatch-origins.py'); pe = module('mmx_pe','verify-sdk-x3d-origins.py')
    target = c.verified_target(); archive = (ROOT/'.tools/msvc710/Vc7/PlatformSDK/Lib/d3dx8.lib').read_bytes()
    if digest(target) != m['target_sha256'] or digest(archive) != m['archive_sha256']:
        raise ValueError('MMX target/archive identity differs')
    members = {o:(n,b) for o,n,b in rt.archive_members(archive)}
    def member(r):
        name, body = members[r['member_offset']]
        if name != r['member'] or digest(body) != r['member_sha256']:
            raise ValueError('MMX original source owner differs')
        return body
    catalog = {r['symbol']: int(r['address'],16) for r in m['controls']}
    for r in m['data']:
        raw, fields, source = extra.section_carrier(member(r),r['source']['section'],c,coff)
        a = int(r['base'],16)
        if (source != r['source'] or fields or len(raw) != r['size'] or source['flags']&0x20 or not source['flags']&0x40
                or digest(raw) != r['source_sha256'] or digest(raw) != r['body_sha256']
                or raw != c.pe_bytes_at(target,a,len(raw)) or pe.image_permissions(target,a,len(raw)) != source['flags']&0xe0000000):
            raise ValueError('MMX whole initialized readonly/cache image/definitions/permissions differs')
        for control in m['controls']:
            for f in control['fields']:
                if f['symbol_type'] == 0 and f['symbol_section'] == source['section'] and control['member_offset'] == r['member_offset']:
                    if not 0 <= f['symbol_offset']+f['addend'] < len(raw):
                        raise ValueError('MMX local field escapes whole original data section')
                    catalog[pe.field_key(r['member_offset'],f)] = a+f['symbol_offset']
    imports = module('mmx_imports','verify-import-origins.py').pe_imports(target,c)
    for r in m['imports']:
        if imports.get(int(r['address'],16)) != (r['dll'],r['name']):
            raise ValueError('MMX actual imported API identity differs')
        catalog[r['symbol']] = int(r['address'],16)
    # The cache is the actual source-initialized -1 field, not BSS or a fabricated private layout.
    if struct.unpack('<i',c.pe_bytes_at(target,0x66d23c,4))[0] != -1:
        raise ValueError('MMX original cache initializer differs')
    functions = {r['address']:r for r in csv.DictReader((ROOT/'config/functions.csv').open())}
    origins = {r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
    row = m['functions'][0]; mode = 'original' if args.evidence_only else 'accepted'
    for r in m['controls']:
        a = int(r['address'],16); raw, fields, source = extra.section_carrier(member(r),r['source']['section'],c,coff)
        if (source != r['source'] or fields != r['fields'] or len(raw) != r['size'] or digest(raw) != r['source_sha256']
                or pe.image_permissions(target,a,len(raw)) != source['flags']&0xe0000000):
            raise ValueError('MMX whole original code/AUX/definition/real fields differ')
        primary = [d for d in source['definitions'] if d['type']==32]
        if len(primary)!=1 or primary[0]['symbol']!=r['symbol'] or primary[0]['offset'] or primary[0]['storage']!=2:
            raise ValueError('MMX actual original source function entry differs')
        linked, calls, data = v.bind(raw,fields,r['bindings'],catalog,r['member_offset'],a)
        if linked != c.pe_bytes_at(target,a,len(raw)) or digest(linked) != r['body_sha256']:
            raise ValueError('MMX entire unmasked linked code differs')
        if extra.flow(linked,a,[0],fields,calls,data) != r['flow']:
            raise ValueError('MMX whole branches/returns/data/CPUID flow differs')
        decoder = capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32); decoder.detail=True
        actual_imports = []
        for i in decoder.disasm(linked,a):
            if not i.group(capstone.CS_GRP_CALL) or i.operands[0].type==capstone.x86.X86_OP_IMM:
                continue
            operand = i.operands[0]
            if (operand.type!=capstone.x86.X86_OP_MEM or operand.mem.base or operand.mem.index
                    or bytes(i.bytes[:2])!=b'\xff\x15' or operand.mem.disp not in imports
                    or data.get(i.address+i.disp_offset)!=operand.mem.disp):
                raise ValueError('MMX indirect call is not an independently bound actual API field')
            actual_imports.append(dict(offset=i.address-a,address=f'0x{operand.mem.disp:08X}'))
        if actual_imports != r['api_calls']:
            raise ValueError('MMX imported call/cleanup coverage differs')
        if r['address']==row['address']:
            expected_function, expected_origin = row[mode+'_function'],row[mode+'_origin']
        else:
            expected_function, expected_origin = r['function'],r['origin']
        if functions.get(r['address']) != expected_function or origins.get(r['address']) != expected_origin:
            raise ValueError('MMX selected/prior R008 snapshot differs')
        if any(a<int(k,16)<a+len(raw) for k in functions):
            raise ValueError('MMX whole source extent hides an inventoried entry')
    print('R194 origins OK:one complete library registry/cache policy153;whole previously accepted R008 CPUID helper37;all12 genuine fields and four actual imported calls;three initialized source data images47 including -1 cache and full DisableMMX11;independent R188/R192 replay;no source/ABI/mapping/exact credit or new R008 acceptance.')
    return 0


if __name__=='__main__':
    raise SystemExit(main())
