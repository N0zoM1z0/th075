#!/usr/bin/env python3
"""Cold-replay whole nested insertion/copy policies and explicit lifetime evidence."""
import argparse
import csv
import json
from pathlib import Path
import struct
import subprocess
import tempfile
import importlib.util

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('nested_insertion_prior', ROOT / 'scripts/verify-vector-insertion-carrier-origins.py')
PRIOR = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(PRIOR)
module = PRIOR.module
digest = PRIOR.digest
EVIDENCE = 'config/nested-vector-insertion-origin-evidence.json'
MANIFEST_SHA256 = '8ad6c5215a55ea15f175f800f8f7045bc1bdf8fcedace6aa392f4234438ce97c'
PLAN_DIGESTS = {'groups': 'c40f9fdfd05c8a0e313a61d9ce4c7a3afaa7560652d21f9502b62c0c03cf10be', 'sections': '8051317e12a9aa18913e9f5f7e06bcb0aec38d0da9a14d5cbbdeaaec616f720e', 'weak_references': '9d47a2f0111c3c7413aac91e89e361dea555542bfe285a1deaa4b999f1759f96', 'evidence_id': '26d3635f7b1141b098715c6a415f44720203292d46e00af448f3df659ad87eed', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'prior': 'a7b23b1d43bd98a555cac62c969fcdc5c7dff5dc1ba0a7df7579a17ed8bdac4c', 'functions': '72fdab2e290c5d2ed2291a91e9196e84c3997a4e983dc888b03710bf1f852077', 'interiors': 'fa8e465e436376ccdbbba29cc50969ab1b69650c4c74c245ac02bfd1674b8404', 'retained_unknowns': '9429fc51b4cb1782ac3106eaf86b784a92b0894c4568895cada0ecb587b74d68', 'historical_snapshots': '1f0beb68b2324a9107fd779b740db103824cc1877693212caa98988ec8eafcd5', 'retained_sha256': '4eebc8ac74c26575fded95d633f120e739f2970acaddc0c85cd0b9a4a49f8697', 'public_control': '2c1db3c0db552f1a861eaa64d2b4d71b887d07e4da8a72a1159ff635909c9a05', 'implicit_alternative': '23d3b1bce43794f14b1fbc674ca9de15b2e894f25c93effa86fb8178af6fc4ff', 'authored_policy': 'a904d01b806e7fce5f174e25ecf93525d012a3261fa8c6537f251eb3b1f3c3aa'}
WHOLE = {'0x005F9A10':796,'0x00459CB0':1101,'0x0045A950':38,'0x0045A980':51,
         '0x00459390':208,'0x0045B0C0':48,'0x0045AC50':381,'0x0045B300':189,'0x004588E0':116}


def headers(log):
    found = {}
    for line in log.splitlines():
        if 'Note: including file:' not in line: continue
        value = line.split('Note: including file:',1)[1].strip().replace('\\','/')
        if value[:3].lower() != 'z:/': raise ValueError('Nested insertion header loses actual host mapping')
        path = Path(value[2:]); relative = str(path.relative_to(ROOT))
        if not relative.startswith('.tools/msvc710/Vc7/include/') and relative != 'tests/origin_probes/VectorInsertionCarriers.cpp':
            raise ValueError('Nested insertion imports an unrelated source owner')
        found[relative] = digest(path.read_bytes())
    return found


def verify_plan(m):
    for key, sha in PLAN_DIGESTS.items():
        if PRIOR.BASE.metadata_digest(m[key]) != sha: raise ValueError('Nested insertion immutable whole context differs: '+key)
    if (m['evidence_id'] != 'R209' or len(m['functions']) != 18 or len(m['interiors']) != 9
            or {r['address']:r['size'] for r in m['functions'] if r['offset']==0} != WHOLE
            or len(m['groups']) != 2 or [g['width'] for g in m['groups']] != [4,116]
            or len(m['sections']) != 144 or sum(r['size'] for r in m['sections']) != 9160
            or sum(len(r['fields']) for r in m['sections']) != 367
            or sum(r['kind']=='code' for r in m['sections']) != 119
            or len(m['retained_unknowns']) != 10 or len(m['historical_snapshots']) != 1
            or len(m['public_control']['emission']) != 413 or m['implicit_alternative']['size'] != 90):
        raise ValueError('Nested insertion omits a complete policy/carrier/interior/alternative')
    for r in m['functions']:
        f,o=r['original_function'],r['original_origin'];af,ao=r['accepted_function'],r['accepted_origin']
        authored=r['role']=='authored-explicit-clear-lifetime'
        if (o['origin'] != 'unknown' or f['status'] != 'unclassified' or f['match_percent'] != '0.00'
                or any(f[k] for k in ['owner','source_file','signature','calling_convention'])
                or af['address'] != r['address'] or af['current_name'] != f['current_name']
                or af['size'] != str(r['size']) or af['span_end'] != f"0x{int(r['address'],16)+r['size']-1:08X}"
                or af['match_percent'] != '0.00' or any(af[k] for k in ['source_file','signature','calling_convention'])
                or (r['offset'] and (af['size'] != f['size'] or af['span_end'] != f['span_end']))
                or (authored and (r['address']!='0x004588E0' or af['owner'] or af['status']!='unclassified'
                    or ao['origin']!='authored' or ao['disposition']!='authored'))
                or (not authored and (af['owner']!='library' or af['status']!='excluded'
                    or ao['origin']!='library' or ao['disposition']!='exclude')) or ao['evidence_id']!='R209'):
            raise ValueError('Nested insertion unsupported extent/origin/private declaration/exact transition')
    for r in m['retained_unknowns']:
        if r['origin']['origin']!='unknown' or r['function']['owner'] or r['function']['status']!='unclassified':
            raise ValueError('Nested insertion assigns an opaque short/private source ownership')


def replay(m,evidence_only=False):
    c=module('nested_insertion_target','compare-coff-function.py');coff=module('nested_insertion_coff','coff_data.py')
    extra=module('nested_insertion_carriers','sdk_x3d_carriers.py');flow=module('nested_insertion_flow','sdk_image_carriers.py')
    pe=module('nested_insertion_permissions','verify-sdk-x3d-origins.py');authored=module('nested_insertion_authored','verify-authored-origins.py')
    inventory=module('nested_insertion_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    target=c.verified_target();functions={r['address']:r for r in csv.DictReader((ROOT/'config/functions.csv').open())}
    origins={r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
    selected={r['address']:r for r in m['functions']};state='original' if evidence_only else 'accepted'
    if digest(target)!=m['target_sha256']:raise ValueError('Nested insertion target identity differs')
    for r in m['functions']:
        if functions[r['address']]!=r[state+'_function'] or origins[r['address']]!=r[state+'_origin']:
            raise ValueError('Nested insertion canonical selected transition differs')
    for r in m['retained_unknowns']:
        if functions[r['function']['address']]!=r['function'] or origins[r['origin']['address']]!=r['origin']:
            raise ValueError('Nested insertion changes protected private/short-helper unknown')
    prior=json.loads((ROOT/m['prior']['path']).read_text())
    if (digest((ROOT/m['prior']['path']).read_bytes())!=m['prior']['manifest_sha256']
            or prior['shared']!=m['prior']['shared'] or prior['absolute']!=m['prior']['absolute']
            or prior['crt_archive_sha256']!=m['prior']['crt_archive_sha256']):
        raise ValueError('Nested insertion replaces independently owned original prior graph')
    result=subprocess.run([str(ROOT/'scripts/repo-python'),str(ROOT/'scripts/verify-vector-insertion-carrier-origins.py')],
                          cwd=ROOT,capture_output=True,text=True)
    if result.returncode:raise ValueError('Nested insertion complete retained cold graph failed: '+result.stderr)
    print(result.stdout.strip(),flush=True)
    old=json.loads((ROOT/'config/nested-deque-size-origin-evidence.json').read_text());source_catalog=PRIOR.BASE.retained_catalog(old)
    shared={'__except_list':0}
    for r in m['prior']['shared']:
        owner=r['owner']
        if old[owner['collection']][owner['index']]!=owner['record'] or source_catalog.get(r['symbol'])!=int(r['address'],16):
            raise ValueError('Nested insertion borrowed observation overrides original source definition')
        shared[r['symbol']]=source_catalog[r['symbol']]
    for old in m['historical_snapshots']:
        history=json.loads((ROOT/old['path']).read_text());q=old['record'];r=selected[q['address']]
        if (q not in history['snapshots'] or q['function']!=r['original_function'] or q['origin']!=r['original_origin']
                or digest(c.pe_bytes_at(target,int(q['address'],16),q['size']))!=q['body_sha256']):
            raise ValueError('Nested insertion changes literal original R162 protected history')
    p=m['authored_policy'];a=int(p['address'],16);native=c.pe_bytes_at(target,a,116)
    records=list(csv.DictReader((ROOT/p['path']).open()))
    if (records!=[p['record']] or digest(native)!=p['body_sha256'] or p['record']['body_sha256']!=digest(native)
            or list(authored.verify_body(native,a))!=p['cfg'] or p['cfg']!=[1,0]
            or PRIOR.instructions(native,a,flow)!=p['instructions']):
        raise ValueError('Nested insertion whole authored policy/own evidence/CFG differs')
    for call in p['explicit_clear_calls']+p['automatic_destruction_calls']:
        site=int(call['site'],16);at=site-a
        if native[at]!=0xe8 or site+5+struct.unpack_from('<i',native,at+1)[0]!=int(call['target'],16):
            raise ValueError('Nested insertion loses actual explicit/automatic lifetime call order')
    scratch=ROOT/'build/origin-nested-vector-insertion-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj=Path(temp)/'NestedInsertion.obj';control=m['public_control']
        result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/control['probe']),str(obj),*control['profile']],
                              cwd=ROOT,capture_output=True,text=True)
        if result.returncode or headers(result.stdout+result.stderr)!=control['headers']:
            raise ValueError('Nested insertion cold source/original includes differ')
        body=obj.read_bytes()
        if inventory(body,c,coff)!=control['emission']:raise ValueError('Nested insertion omits ordinary code/data/EH emission')
        layout,_=coff.readonly_section(body,control['layout']['section'],c.coff_name)
        if len(layout)!=64 or list(struct.unpack('<16I',layout))!=control['layout_values']:
            raise ValueError('Nested insertion crops combined original64-byte generic observation carrier')
        if [PRIOR.weak_record(body,r['symbol'],c,coff) for r in m['weak_references']]!=m['weak_references']:
            raise ValueError('Nested insertion actual weak AUX/strong fallback differs')
        decoded={}
        for g in m['groups']:
            rows=[r for r in m['sections'] if r['group']==g['id']]
            for r in rows:
                raw,fields,source=extra.section_carrier(body,r['source']['section'],c,coff)
                source=PRIOR.BASE.canonical_source(source,body);a=int(r['base'],16)
                if (source!=r['source'] or fields!=r['fields'] or len(raw)!=r['size'] or digest(raw)!=r['source_sha256']
                        or pe.image_permissions(target,a,len(raw))!=source['flags']&0xe0000000):
                    raise ValueError('Nested insertion complete source/AUX/fields/permissions differ')
                decoded[(g['id'],source['section'])]=(raw,fields)
                if r['kind']=='code':
                    actual=[dict(function=f,origin=origins[k]) for k,f in functions.items() if a<=int(k,16)<a+r['size']]
                    expected=[dict(function=selected[q['function']['address']][state+'_function'],
                                   origin=selected[q['function']['address']][state+'_origin'])
                              if q['function']['address'] in selected else q for q in r['inventory_entries']]
                    if actual!=expected:raise ValueError('Nested insertion whole source hides an inventory entry')
            catalog=PRIOR.owned_catalog(rows,shared,g['id'],m['weak_references'])
            for r in rows:
                raw,fields=decoded[(g['id'],r['source']['section'])];a=int(r['base'],16)
                linked,calls,data=PRIOR.BASE.BASE.bind_fields(raw,fields,r['bindings'],catalog,g['id'],a,data_image=r['kind']=='data')
                actual=c.pe_bytes_at(target,a,len(raw))
                if linked!=actual or digest(actual)!=r['body_sha256']:raise ValueError('Nested insertion complete unmasked native body differs')
                if r['kind']=='code':
                    roots={0};roots.update(d['offset'] for d in r['source']['definitions'] if d['type']==32 and d['storage']==3)
                    roots.update(f['symbol_offset']+f['addend'] for q in rows for f in q['fields']
                                 if f['symbol_section']==r['source']['section'] and f['symbol_storage']==6)
                    if sorted(roots)!=r['roots'] or flow.flow(actual,a,r['roots'],fields,calls,data,None,None,None)!=r['flow']:
                        raise ValueError('Nested insertion whole normal/catch/unwind/shared-exit CFG differs')
        for r in m['interiors']:
            p=next(q for q in m['sections'] if q['group']==r['group'] and q['base']==r['parent'])
            a=int(r['address'],16);actual=c.pe_bytes_at(target,a,r['size'])
            if (r['offset']+r['size']>p['size'] or digest(actual)!=r['body_sha256']
                    or PRIOR.instructions(actual,a,flow)!=r['instructions']
                    or [d for d in p['source']['definitions'] if d['type']==32 and d['offset']==r['offset']]!=r['source_definitions']):
                raise ValueError('Nested insertion existing recovery inventory is not inside its complete original parent')
        alt=m['implicit_alternative'];raw,fields,source=extra.section_carrier(body,alt['source']['section'],c,coff)
        explicit=next(r for r in m['sections'] if r['base']=='0x004588E0')
        if (PRIOR.BASE.canonical_source(source,body)!=alt['source'] or fields!=alt['fields'] or len(raw)!=90
                or digest(raw)!=alt['source_sha256'] or any(f['symbol'].startswith('?clear@') for f in fields)
                or sum(f['symbol'].startswith('?clear@') for f in explicit['fields'])!=2 or explicit['size']!=116):
            raise ValueError('Nested insertion implicit complete90-byte source can replace explicit two-clear policy116')


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true')
    args=parser.parse_args();m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    for path,sha in [(EVIDENCE,MANIFEST_SHA256),(m['public_control']['probe'],m['public_control']['probe_sha256']),*m['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes())!=sha:raise ValueError('Nested insertion immutable source/evidence differs: '+path)
    replay(m,args.evidence_only)
    print('R209 origins OK: 17 library entries across eight whole public policies2812 and nine recovery interiors; '
          'one authored explicit nested clear lifetime116 distinguished from complete implicit90; 144 complete scoped '
          'code/data sections9160/all367 actual fields/119 CFGs; full413 ordinary emissions26626/28 original includes/whole '
          'combined layout64; full independent R208/R150 retained cold proof; ten private/short controls remain unknown; '
          'literal R162 history/current successor audited; no source/private ABI/mapping/exact credit.')
    return 0


if __name__=='__main__':raise SystemExit(main())
