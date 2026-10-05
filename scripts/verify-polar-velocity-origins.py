#!/usr/bin/env python3
"""Verify complete game polar-velocity composition and independent receiver policies."""
import argparse
import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import struct

ROOT = Path(__file__).resolve().parents[1]
EVIDENCE = 'config/polar-velocity-origin-evidence.json'
MANIFEST_SHA256 = '2ff12ea5f76cf08ee66b4b5a19a4f8ddf286577c0d85e647b05236728b922310'
PLAN_DIGESTS = {'evidence_id': 'd7262a99f3da9ad76efe61b5c4c8ff9a5e2b73783dfd6c4600e27034d4e1213b', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'functions': '815c9ced0a57082022f1bf38e41f2bc44126cdea81c33b782056be28536cbc5e', 'anchors': '54672b2675ebeebe2ff7fa4a3790231d63be65ed063b33a56bf1da902604d712', 'retained_unknowns': 'c1b755536c3aa738e8f4f222b5707f1128781ab97f730118badf744b2b2dcac5', 'historical_snapshots': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'constants': 'a5e905c50d3526cbda06ff2cc21abd498db175e2b7754935df757fd3c534b8ca', 'table_span': '3e5a3f1c145fceadc9b4b427ad68f6c20174ec242680b8c427d968ed4edd413a', 'extent': 'fa2beddc7166f755328c669716fe56d53c61eb31d79324e249fe7d2b3eb756e6', 'authored_path': 'a337a01dc741a49ef7643464c7b9daded558e6004ebc6eec9a2399f11795e425', 'prior': 'e3b64b14a90f23bea60962577e327629920b2ac93026b4685e9a3381727bc78a', 'retained_sha256': 'c661234ebb7ca6ce45d17c51602e340cde8f776fc7f3b23ef958d82739cfba6c', 'external': 'a021d0f0bd6c99239613ca0356dee116d2dd48c081f7340cffec85de32e54697', 'cos_entry': 'd77feb32829473e5606d68eaf878676b2eb2650092a51808d09b9536907e3649'}
def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec); spec.loader.exec_module(result)
    return result


def digest(raw):
    return hashlib.sha256(raw).hexdigest()


def metadata_digest(value):
    return digest(json.dumps(value, sort_keys=True, separators=(',', ':')).encode())


def rows(path):
    with (ROOT / path).open(newline='') as stream: return list(csv.DictReader(stream))


def native_instructions(raw, address):
    from capstone import Cs, CS_ARCH_X86, CS_MODE_32
    decoded = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(raw, address))
    if sum(i.size for i in decoded) != len(raw): raise ValueError('PolarVelocity crops native instructions')
    return [dict(offset=i.address-address, size=i.size, mnemonic=i.mnemonic, operands=i.op_str) for i in decoded]


def verify_native(r, target, c, authored):
    a = int(r['address'], 16); raw = c.pe_bytes_at(target, a, r['size'])
    counts = list(authored.verify_body(raw, a, r.get('switches', []),
                                     lambda x, n: c.pe_bytes_at(target, x, n), r.get('direct_switches', [])))
    if digest(raw) != r['body_sha256'] or native_instructions(raw, a) != r['instructions'] or counts != r['cfg']:
        raise ValueError('PolarVelocity complete native body/instructions/guarded CFG differs: ' + r['address'])
    return raw



def verify_plan(m):
    for key,sha in PLAN_DIGESTS.items():
        if metadata_digest(m[key])!=sha:raise ValueError('PolarVelocity immutable complete evidence differs: '+key)
    if (m['evidence_id']!='R217' or len(m['functions'])!=1
            or [(r['address'],r['size'],r['cfg']) for r in m['functions']]!=[('0x0040FB70',57,[1,0])]
            or len(m['anchors'])!=6 or sum(r['size'] for r in m['anchors'])!=5122
            or sum(len(r['call_sequences']) for r in m['anchors'])!=6
            or len(m['retained_unknowns'])!=1 or m['retained_unknowns'][0]['address']!='0x00641DAA'
            or m['retained_unknowns'][0]['origin']['origin']!='unknown'
            or m['retained_unknowns'][0]['prior_record']['decision']!='pending'
            or m['historical_snapshots'] or len(m['constants'])!=9
            or [(r['address'],r['size']) for r in m['external']]!=[('0x00641740',174),('0x006406AC',117)]):
        raise ValueError('PolarVelocity loses bounded entire policies/dependencies/unknowns')
    r=m['functions'][0];f,o,af,ao=(r[k] for k in ['original_function','original_origin','accepted_function','accepted_origin'])
    mutable={'proposed_name','module','owner','evidence','notes'}
    if (o['origin']!='unknown' or f['status']!='unclassified' or f['owner']
            or {k:v for k,v in f.items() if k not in mutable}!={k:v for k,v in af.items() if k not in mutable}
            or int(f['size'])!=57 or af['owner']!='authored' or ao['origin']!='authored'
            or ao['disposition']!='authored' or ao['evidence_id']!='R217'
            or any(af[k] for k in ['source_file','signature','calling_convention']) or af['match_percent']!='0.00'
            or r['record']!=dict(address=r['address'],size='57',body_sha256=r['body_sha256'],inferred_role=af['proposed_name'],
                                  return_count='1',internal_branch_count='0',external_branch_count='0',evidence_id='R217')):
        raise ValueError('PolarVelocity invents source/private ABI/extent/exact credit')


def verify_context(m):
    r=m['functions'][0];ins=r['instructions'];pairs=[(i['mnemonic'],i['operands']) for i in ins]
    if ([(i['offset'],i['operands']) for i in ins if i['mnemonic']=='call']!=[(11,'0x41cb40'),(32,'0x41cb70')]
            or pairs.count(('fmul','dword ptr [ebp + 0xc]'))!=2 or pairs.count(('fchs',''))!=1
            or ('fstp','dword ptr [ecx + 0x50]') not in pairs or ('fstp','dword ptr [eax + 0x54]') not in pairs
            or pairs[-1]!=('ret','8')
            or pairs[4:7]!=[('mov','eax, dword ptr [ebp + 8]'),('push','eax'),('call','0x41cb40')]
            or pairs[11:14]!=[('mov','edx, dword ptr [ebp + 8]'),('push','edx'),('call','0x41cb70')]):
        raise ValueError('PolarVelocity loses actual x87 order/arguments/stores/RET8')
    for parent in [r for r in m['anchors'] if r['call_sequences']]:
        receiver='ecx, dword ptr [ebp - 8]' if parent['address']=='0x004F4170' else 'ecx, dword ptr [ebp - 4]'
        for seq in parent['call_sequences']:
            index=next(j for j,i in enumerate(parent['instructions']) if int(parent['address'],16)+i['offset']==int(seq['site'],16))
            actual=parent['instructions'][index-14:index+1];pairs=[(i['mnemonic'],i['operands']) for i in actual]
            if (actual!=seq['instructions'] or pairs[-2:]!=[('mov',receiver),('call','0x40fb70')]
                    or pairs.count(('push','ecx'))!=2 or pairs.count(('fstp','dword ptr [esp]'))!=2
                    or sum(mn=='fild' for mn,op in pairs)!=2):
                raise ValueError('PolarVelocity crops actual full receiver/two float argument sequence')
    lookup={r['address']:r for r in m['anchors']}
    for key in ['0x0041CB40','0x0041CB70']:
        pairs=[(i['mnemonic'],i['operands']) for i in lookup[key]['instructions']]
        if ([op for mn,op in pairs if mn=='call']!=['0x6406ac','0x641daa']
                or ('fld','dword ptr [edx*4 + 0x6884c0]') not in pairs):
            raise ValueError('PolarVelocity replaces actual index conversion/abs/table policy')
    if ('fsub','dword ptr [0x657b28]') not in [(i['mnemonic'],i['operands']) for i in lookup['0x0041CB70']['instructions']]:
        raise ValueError('PolarVelocity loses phase subtraction rather than generic sin/cos assumption')


def verify_external(m,target,c,functions,origins):
    reader=module('polar_archive','verify-runtime-origins.py');coff=module('polar_coff','coff_data.py')
    carrier=module('polar_carrier','sdk_x3d_carriers.py')
    archive=(ROOT/'.tools/msvc710/Vc7/lib/libcmt.lib').read_bytes()
    if digest(archive)!='6e2b3742e58245de52149137f64281b73db1487a07a31e165fff269fbf9b2ee8':
        raise ValueError('PolarVelocity pinned CRT archive differs')
    members={off:(name,body) for off,name,body in reader.archive_members(archive)}
    for ref in m['external']:
        record=ref['record'];a=int(ref['address'],16);actual=c.pe_bytes_at(target,a,ref['size'])
        original=rows(ref['file']) if ref['file'].endswith('.csv') else json.loads((ROOT/ref['file']).read_text())[ref['collection']]
        if (record not in original or functions[ref['address']]!=ref['function'] or origins[ref['address']]!=ref['origin']
                or digest(actual)!=ref['body_sha256'] or native_instructions(actual,a)!=ref['instructions']):
            raise ValueError('PolarVelocity replaces full independent CRT source/native checkpoint')
        name,body=members[int(record['member_offset'])]
        if name!=record['member']:raise ValueError('PolarVelocity original archive member name differs')
        if 'member_sha256' in record and digest(body)!=record['member_sha256']:
            raise ValueError('PolarVelocity original member identity differs')
        _,defs=coff.parse_symbols(body,c.coff_name);d=next(d for d in defs if d['symbol']==record['coff_symbol'] and d['section']>0)
        raw,fields,source=carrier.section_carrier(body,d['section'],c,coff)
        if d['offset']!=0 or len(raw)!=ref['size']:raise ValueError('PolarVelocity crops the original source primary')
        bindings=record.get('relocation_bindings',[])
        if len(fields)!=len(bindings):raise ValueError('PolarVelocity omits original CRT fields')
        linked=bytearray(raw)
        for field,b in zip(fields,bindings):
            if any(field[k]!=b[k] for k in ['offset','type','symbol','addend']):raise ValueError('PolarVelocity source field differs')
            dest=int(b['target_address'],16)+field['addend'];value=dest-a-field['offset']-4 if field['type']=='REL32' else dest
            struct.pack_into('<I',linked,field['offset'],value&0xffffffff)
        if linked!=actual:raise ValueError('PolarVelocity full unmasked original vendor body differs')
    ref=m['cos_entry'];old=json.loads((ROOT/ref['file']).read_text())
    r=ref['record']
    if (r not in old[ref['collection']] or r['parent']!='0x00641740' or r['source_offset']!=20
            or r['address']!='0x00641754' or r['size']!=9):
        raise ValueError('PolarVelocity detaches C entry from complete cosine source owner')


def replay(m,evidence_only=False):
    c=module('polar_target','compare-coff-function.py');authored=module('polar_cfg','verify-authored-origins.py')
    pe=module('polar_pe','verify-sdk-x3d-origins.py');target=c.verified_target()
    if digest(target)!=m['target_sha256']:raise ValueError('PolarVelocity target differs')
    functions={r['address']:r for r in rows('config/functions.csv')};origins={r['address']:r for r in rows('config/function-origins.csv')}
    state='original' if evidence_only else 'accepted'
    if rows(m['authored_path'])!=[r['record'] for r in m['functions']]:raise ValueError('PolarVelocity dedicated authored registry differs')
    for r in m['functions']:
        if functions[r['address']]!=r[state+'_function'] or origins[r['address']]!=r[state+'_origin']:
            raise ValueError('PolarVelocity bounded canonical transition differs')
        verify_native(r,target,c,authored)
        expected=[dict(function=r[state+'_function'],origin=r[state+'_origin'])]
        a=int(r['address'],16)
        actual=[dict(function=f,origin=origins[k]) for k,f in functions.items() if a<=int(k,16)<a+r['size']]
        if actual!=expected:raise ValueError('PolarVelocity hides another inventory entry')
    old_authored={r['address']:r for r in rows('config/authored-origin-evidence.csv')}
    for r in m['anchors']+m['retained_unknowns']:
        if functions[r['address']]!=r['function'] or origins[r['address']]!=r['origin']:
            raise ValueError('PolarVelocity changes an independent context/unknown')
        verify_native(r,target,c,authored)
        a=int(r['address'],16)
        current=[dict(function=f,origin=origins[k]) for k,f in functions.items() if a<=int(k,16)<a+r['size']]
        if current!=r['inventory_entries']:raise ValueError('PolarVelocity hides context inventory interiors')
        for filename,key in [('authored-origin-switches.csv','switches'),('authored-origin-direct-switches.csv','direct_switches')]:
            if [q for q in rows('config/'+filename) if q['address']==r['address']]!=r[key]:
                raise ValueError('PolarVelocity changes entire context switch evidence')
        if pe.image_permissions(target,a,r['size'])!=r['permissions']:raise ValueError('PolarVelocity code permissions differ')
        if 'record' in r and old_authored[r['address']]!=r['record']:raise ValueError('PolarVelocity rewrites accepted context record')
    prior=json.loads((ROOT/m['prior']['path']).read_text())
    for r in m['prior']['records']:
        anchor=next(a for a in m['anchors'] if a['address']==r['address'])
        if (r not in prior['functions'] or r['accepted_function']!=anchor['function'] or r['accepted_origin']!=anchor['origin']
                or r['accepted_authored_record']!=anchor['record']):
            raise ValueError('PolarVelocity loses literal complete math-policy provenance')
    unknown=m['retained_unknowns'][0];prior_abs=json.loads((ROOT/m['prior']['absolute_path']).read_text())
    if unknown['prior_record'] not in prior_abs['diagnostic_contexts']:raise ValueError('PolarVelocity resolves abs ambiguity')
    for r in m['constants']:
        raw=c.pe_bytes_at(target,int(r['address'],16),r['size'])
        if (raw.hex()!=r['hex'] or digest(raw)!=r['sha256'] or struct.unpack('<f' if r['size']==4 else '<d',raw)[0]!=r['value']
                or r['permissions']!=0x40000000 or pe.image_permissions(target,int(r['address'],16),r['size'])!=r['permissions']):
            raise ValueError('PolarVelocity full observed readonly scalar differs')
    math=module('polar_table','verify-math-table-policy-origins.py');math.verify_table_span(target,m['table_span'])
    p=m['extent'];align=c.pe_bytes_at(target,int(p['alignment_address'],16),7)
    if align!=b'\xcc'*7 or align.hex()!=p['alignment_hex'] or digest(align)!=p['alignment_sha256']:
        raise ValueError('PolarVelocity absorbs alignment into code')
    verify_context(m);verify_external(m,target,c,functions,origins)


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true')
    args=parser.parse_args();m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    for path,sha in [(EVIDENCE,MANIFEST_SHA256),*m['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes())!=sha:raise ValueError('PolarVelocity immutable evidence/source differs: '+path)
    replay(m,args.evidence_only)
    print('R217 origins OK: complete authored polar-velocity57/RET8; six whole authored contexts5122/six actual float argument and receiver sequences; '
          'two full original CRT source owners291 and real cosine C-entry; nine readonly observed scalars48/used writable table14400; '
          'abs641DAA remains unknown; seven CC alignment/next full owner158; no source/private ABI/mapping/exact credit.')
    return 0

if __name__=='__main__':raise SystemExit(main())
