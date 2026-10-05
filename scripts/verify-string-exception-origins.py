#!/usr/bin/env python3
"""Replay original string providers, complete throw graphs and independent SDK callers."""
import argparse
import csv
import json
import os
from pathlib import Path
import struct
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
import importlib.util
SPEC = importlib.util.spec_from_file_location('string_retained', ROOT/'scripts/verify-list-head-erase-origins.py')
RETAINED = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(RETAINED)
SOURCE = RETAINED.SOURCE
module = SOURCE.module
digest = SOURCE.digest
EVIDENCE = 'config/string-exception-origin-evidence.json'
MANIFEST_SHA256 = '3ca89a95bdb3fff016ed80a9c7f4d0caea42023d8fcabb1766192af56c1318ff'
PLAN_DIGESTS = {'evidence_id': 'f7c429c9d8592000993d8dfdcad1184a8837a3146655dd9940fb224a7faec6c1', 'comparison': 'b40cb280495b5b7d6b4c14a83e42c1c095b4a35802645efc5bd058092dfab636', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'crt_archive_sha256': '69d0301fde85b097b2afc8e5732879473468d247ae0b55492fdc2063da1f7f6c', 'functions': 'dce08208af2282349fd598a9d130e1c9a4ef9c2c632fe963af0c0570eab779b5', 'vendor_groups': 'ab4f0eb131fc50b3bfee09105fa30deb53fbab7e23deff693b1bf468a05cdf4a', 'public_groups': '779b151b98831ead2ab4a6f83f7dbb5e9746639f66a7c5bebae44b256c68aeea', 'retained': '574ed34a1cfeeb27e182cde6700e2801735df26afd83854252316890a6203374', 'nested': '44e164354c04279faa46bc2d93662549a6592194b377a8afb243876abe803376', 'eh_prolog': 'cf60287b1b6da3c3836834cc445e7b8eb8837ebeda3016e5db4554178374681f', 'parents': 'b0e281796f2dcd885a0b454730ad493209942cdbf9f5c5f32e84047b450c69f7', 'public_control': '6b6f5a1a579aae10c0cf07fe58683b73e2453a6c974382267835afaba3ca498e', 'canonical': 'a8d2f6cad1f5635a70367edf33abbfe0471366be2eba62cdcad2f04713524337', 'inventory': 'bef0bb7d9bff7d3ca5ce0e4ca8f36f7581e8fd60b0e88ab78e156386a6e73a05', 'historical_snapshots': 'd7259a26d6fdea95fbb1dcda4009fcb1338b07ee273c9f12bd6b7562fd120514', 'retained_sha256': 'e3c8158bd1db0ad09db82adf4e9158d54eafc6026b97f2d719f09f61b7003f6a', 'interpretation': '66e26678f6f0e830fac375ab68e48092267f532414e469973571febe67dd0350'}
KEYS = {'0x00654ACE':64, '0x00654B0E':64}


def headers(log):
    result = {}
    for line in log.splitlines():
        if 'Note: including file:' not in line: continue
        value = line.split('Note: including file:',1)[1].strip().replace('\\','/')
        if value[:3].lower()!='z:/': raise ValueError('String provider include loses host mapping')
        path=Path(os.path.normpath(value[2:])); relative=str(path.relative_to(ROOT))
        if not (relative.startswith('.tools/msvc710/Vc7/include/')
                or relative=='.tools/msvc710/Vc7/crt/src/string.cpp'):
            raise ValueError('String provider imports unrelated source')
        result[relative]=digest(path.read_bytes())
    return result


def provider_flow(raw, address, fields, calls, data, flow):
    """A language throw expression with full source/AUX, not a guessed named callee."""
    ins=flow.instructions(bytes(raw),address,len(raw)); cs=flow.capstone
    if (len(raw)!=64 or len(ins)!=17 or ins[-1].address!=address+63
            or bytes(ins[-1].bytes)!=b'\xcc' or ins[-1].mnemonic!='int3'
            or ins[-2].address!=address+58 or ins[-2].mnemonic!='call'
            or len(fields)!=8 or [f['offset'] for f in fields]!=[1,6,14,22,38,43,54,59]
            or fields[-1]['symbol']!='__CxxThrowException@8' or fields[-1]['type']!='REL32'
            or calls.get(address+59)!=0x640c12):
        raise ValueError('String provider loses actual complete terminal throw and INT3 extent')
    used_calls=set();used_data=set()
    for i in ins[:-1]:
        if i.group(cs.CS_GRP_JUMP) or i.group(cs.CS_GRP_RET):
            raise ValueError('String throw prefix has an unproved exit/branch')
        for off,n in [(i.imm_offset,i.imm_size),(i.disp_offset,i.disp_size)]:
            at=i.address+off
            if at in data and n==4:
                if struct.unpack_from('<I',raw,at-address)[0]!=data[at]:
                    raise ValueError('String provider hides a genuine data field')
                used_data.add(at)
        if i.group(cs.CS_GRP_CALL):
            at=i.address+i.imm_offset
            if i.operands[0].type!=cs.x86.X86_OP_IMM or calls.get(at)!=i.operands[0].imm:
                raise ValueError('String provider call lacks complete independent source ownership')
            used_calls.add(at)
    if used_calls!=set(calls) or used_data!=set(data):
        raise ValueError('String provider has an unconsumed source field')
    return dict(whole_size=64, roots=[0], instruction_count=17, reachable_instruction_count=16,
                terminal_throw=dict(offset=58,field=59,target='0x00640C12',
                    basis='Original active _THROW expands to a C++ throw expression; complete runtime uses noncontinuable RaiseException.'),
                retained_suffix=dict(offset=63,size=1,bytes='cc',mnemonic='int3'),returns=[])


def graph_catalog(rows, shared, group, refs):
    catalog=SOURCE.owned_catalog(rows,shared,group,[])
    for ref in refs:
        d=ref['fallback_definition']; symbol=ref['fallback_symbol']
        if (ref['search_characteristics']!=2 or ref['source_definition']['storage']!=105
                or d['storage']!=2 or d['type']!=32 or d['section']<=0 or d['offset']!=0
                or symbol not in catalog):
            raise ValueError('String actual weak AUX lacks a complete strong COMDAT winner')
        if ref['symbol'] in catalog and catalog[ref['symbol']]!=catalog[symbol]:
            raise ValueError('String weak reference overrides source identity')
        catalog[ref['symbol']]=catalog[symbol]
    return catalog


def replay_graph(body, group, shared, target, c, coff, flow):
    extra=module('string_section','sdk_x3d_carriers.py')
    pe=module('string_permissions','verify-sdk-x3d-origins.py')
    rows=group['sections'];gid=group['id']
    if [SOURCE.weak_record(body,r['symbol'],c,coff) for r in group['weak_references']]!=group['weak_references']:
        raise ValueError('String actual weak/fallback source indices differ')
    catalog=graph_catalog(rows,shared,gid,group['weak_references'])
    for r in rows:
        raw,fields,source=extra.section_carrier(body,r['source']['section'],c,coff);a=int(r['base'],16)
        if (SOURCE.BASE.canonical_source(source,body)!=r['source'] or fields!=r['fields']
                or len(raw)!=r['size'] or digest(raw)!=r['source_sha256']
                or pe.image_permissions(target,a,len(raw))!=source['flags']&0xe0000000):
            raise ValueError('String complete source/AUX/fields/permissions differ')
        linked,calls,data=SOURCE.BASE.BASE.bind_fields(raw,fields,r['bindings'],catalog,gid,a,data_image=r['kind']=='data')
        if linked!=c.pe_bytes_at(target,a,len(raw)) or digest(linked)!=r['body_sha256']:
            raise ValueError('String complete unmasked source body differs')
        if r['kind']=='code':
            roots=sorted({0}|{d['offset'] for d in source['definitions'] if d['storage']==3 and d['type']==32})
            actual=provider_flow(linked,a,fields,calls,data,flow) if r['base'] in KEYS else flow.flow(linked,a,roots,fields,calls,data)
            if roots!=r['roots'] or actual!=r['flow']:
                raise ValueError('String whole normal/cleanup/handler flow differs')
    return catalog


def verify_plan(m):
    for key,sha in PLAN_DIGESTS.items():
        if SOURCE.BASE.metadata_digest(m[key])!=sha:
            raise ValueError('String immutable complete plan differs: '+key)
    if (m['evidence_id']!='R219' or {r['address']:r['size'] for r in m['functions']}!=KEYS
            or len(m['vendor_groups'])!=2 or len(m['public_groups'])!=2
            or any(len(g['sections'])!=32 or sum(r['size'] for r in g['sections'])!=786
                   or sum(len(r['fields']) for r in g['sections'])!=70 for g in m['vendor_groups'])
            or any(len(g['sections'])!=22 or sum(r['size'] for r in g['sections'])!=584
                   or sum(len(r['fields']) for r in g['sections'])!=52 for g in m['public_groups'])
            or len(m['parents'])!=3 or len(m['retained']['sections'])!=105):
        raise ValueError('String bounded whole source/caller/alternative scope differs')
    mutable={'proposed_name','module','status','owner','evidence','notes'}
    for r in m['functions']:
        old,new=r['original_function'],r['accepted_function']
        if (r['original_origin']['origin']!='unknown' or old['status']!='unclassified'
                or old['size']!='64' or old['match_percent']!='0.00'
                or any(old[k] for k in ['source_file','calling_convention','signature','owner'])
                or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
                or new['owner']!='library' or new['status']!='excluded'
                or r['accepted_origin']!=dict(address=r['address'],origin='library',subsystem='VC71STL',disposition='exclude',
                    confidence='complete-original-string-provider-source-and-independent-sdk-callers',evidence_id='R219')):
            raise ValueError('String gains unsupported source/ABI/exact/extent credit')


def current_entries(functions,origins,base,size):
    return [dict(function=f,origin=origins[k]) for k,f in functions.items() if base<=int(k,16)<base+size]


def verify_native(m,target,c,flow):
    for r in m['functions']:
        a=int(r['address'],16);raw=c.pe_bytes_at(target,a,r['size'])
        if digest(raw)!=r['body_sha256'] or SOURCE.instructions(raw,a,flow)!=r['instructions']:
            raise ValueError('String complete native provider differs')
    for p in m['parents']:
        a=int(p['base'],16);raw=c.pe_bytes_at(target,a,p['size'])
        if digest(raw)!=p['body_sha256'] or SOURCE.instructions(raw,a,flow)!=p['instructions']:
            raise ValueError('String independent complete SDK parent differs')
        at=p['call_offset'];field=p['field'];callee=int(p['callee'],16)
        if (field not in p['fields'] or field['offset']!=at+1 or field['type']!='REL32'
                or field['symbol']!=p['provider_symbol'] or field['symbol_section']!=0
                or field['symbol_storage']!=2 or field['symbol_type']!=32 or field['addend']!=0
                or not any(i['offset']==at and i['mnemonic']=='call' and i['operands']==hex(callee) for i in p['instructions'])):
            raise ValueError('String provider identity loses its genuine independent SDK parent field')


def replay(m,evidence_only=False):
    c=module('string_target','compare-coff-function.py');coff=module('string_coff','coff_data.py')
    extra=module('string_sections','sdk_x3d_carriers.py');flow=module('string_flow','sdk_image_carriers.py')
    ar=module('string_archive','verify-runtime-origins.py');extent=module('string_extent','verify-vendor-record-origins.py')
    target=c.verified_target()
    if digest(target)!=m['target_sha256']:raise ValueError('String target identity differs')
    for path,sha in m['retained_sha256'].items():
        if digest((ROOT/path).read_bytes())!=sha:raise ValueError('String changes retained original evidence/input: '+path)
    functions={r['address']:r for r in csv.DictReader((ROOT/'config/functions.csv').open())}
    origins={r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
    selected={r['address']:r for r in m['functions']};state='original' if evidence_only else 'accepted'
    for r in m['functions']:
        if functions[r['address']]!=r[state+'_function'] or origins[r['address']]!=r[state+'_origin']:
            raise ValueError('String bounded canonical transition differs')
    def check_pair(pair):
        key=pair['function']['address'];expected=pair
        if key in selected:expected=dict(function=selected[key][state+'_function'],origin=selected[key][state+'_origin'])
        if dict(function=functions[key],origin=origins[key])!=expected:
            raise ValueError('String changes a retained complete canonical owner')
    for pair in m['canonical']:check_pair(pair)
    for r in m['historical_snapshots']:
        old=json.loads((ROOT/r['path']).read_text())
        for k in r['trail']:old=old[k]
        if old!=r['record']:raise ValueError('String replaces literal historical unknown snapshots')
    verify_native(m,target,c,flow)
    original=json.loads((ROOT/RETAINED.EVIDENCE).read_text())
    shared=RETAINED.prior_catalog(original,target,c,coff)
    crt=(ROOT/'.tools/msvc710/Vc7/lib/libcmt.lib').read_bytes()
    anchor=m['eh_prolog'];name,body={off:(n,b) for off,n,b in ar.archive_members(crt)}[anchor['member_offset']]
    raw,fields,source=extra.section_carrier(body,anchor['source_definition']['section'],c,coff)
    if (digest(crt)!=m['crt_archive_sha256'] or name!=anchor['member'] or digest(body)!=anchor['member_sha256']
            or anchor['source_definition'] not in source['definitions'] or len(raw)!=31 or fields
            or digest(raw)!=anchor['source_sha256'] or raw!=c.pe_bytes_at(target,0x6425a4,31)):
        raise ValueError('String original full EH prolog differs')
    shared['__EH_prolog']=0x6425a4
    with tempfile.TemporaryDirectory(dir=ROOT/'build') as temp:
        obj=Path(temp)/'RetainedString.obj';control=m['retained']['control']
        result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/control['probe']),str(obj),*control['profile']],cwd=ROOT,capture_output=True,text=True)
        inventory=module('string_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
        if result.returncode or RETAINED.headers(result.stdout+result.stderr)!=control['headers']:
            raise ValueError('String original cold SDK parent includes differ')
        body=obj.read_bytes()
        if inventory(body,c,coff)!=control['emission']:raise ValueError('String loses whole retained ordinary emission')
        layout,_=coff.readonly_section(body,control['layout']['section'],c.coff_name)
        if list(struct.unpack('<4I',layout))!=control['layout_values']:raise ValueError('String crops retained layout')
        graph=m['retained'];catalog=replay_graph(body,graph,shared,target,c,coff,flow)
        for r in graph['sections']:
            if r['kind']=='code':
                for d in r['source']['definitions']:
                    if d['storage']==2:shared[d['symbol']]=int(r['base'],16)+d['offset']
        for ref in graph['weak_references']:shared[ref['symbol']]=shared[ref['fallback_symbol']]
        nested=module('string_nested','verify-nested-deque-size-origins.py');nm=json.loads((ROOT/m['nested']['path']).read_text())
        result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/nm['probe']),str(obj),*nm['profile']],cwd=ROOT,capture_output=True,text=True)
        if result.returncode or RETAINED.headers(result.stdout+result.stderr)!=nm['headers']:
            raise ValueError('String independent out_of_range cold includes differ')
        nested.verify_cold_object(nm,obj,c,extent,coff,target)
        for r in nm['code']:shared[r['symbol']]=int(r['address'],16)
        for name,fallback in nm['weak'].items():shared[name]=shared[fallback]
        for group in m['vendor_groups']:
            archive=(ROOT/group['archive']).read_bytes()
            name,body={off:(n,b) for off,n,b in ar.archive_members(archive)}[group['member_offset']]
            if digest(archive)!=group['archive_sha256'] or name!=group['member'] or digest(body)!=group['member_sha256']:
                raise ValueError('String original entire archive/member differs')
            for r in group['sections']:
                if r['base'] in KEYS and extent.complete_aux_section_size(body,r['symbol'],c.coff_name)!=64:
                    raise ValueError('String original own complete AUX extent differs')
            replay_graph(body,group,shared,target,c,coff,flow)
        control=m['public_control']
        result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/control['probe']),str(obj),*control['profile']],cwd=ROOT,capture_output=True,text=True)
        if result.returncode or headers(result.stdout+result.stderr)!=control['headers']:
            raise ValueError('String genuine original provider/ordinary includes differ')
        body=obj.read_bytes()
        if inventory(body,c,coff)!=control['emission']:raise ValueError('String loses complete provider/ordinary emission')
        raw,_=coff.readonly_section(body,control['layout']['section'],c.coff_name)
        if list(struct.unpack('<5I',raw))!=control['layout_values']:
            raise ValueError('String crops public readonly object observations')
        for group in m['public_groups']:
            for r in group['sections']:
                if r['base'] in KEYS and extent.complete_aux_section_size(body,r['symbol'],c.coff_name)!=64:
                    raise ValueError('String public/ordinary own AUX extent differs')
            replay_graph(body,group,shared,target,c,coff,flow)
    for r in m['inventory']:
        actual=current_entries(functions,origins,int(r['base'],16),r['size'])
        expected=[dict(function=selected[p['function']['address']][state+'_function'],origin=selected[p['function']['address']][state+'_origin'])
                  if p['function']['address'] in selected else p for p in r['entries']]
        if actual!=expected:raise ValueError('String whole source hides or reclassifies an inventory interior')


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args()
    m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes())!=MANIFEST_SHA256:raise ValueError('String reviewed manifest differs')
    replay(m,args.evidence_only)
    print('R219: two complete64-byte string providers; both32-section vendor graphs786/all70 fields; full SDK callers, throw/RTTI/EH and actual weak winners; ordinary full graphs also match; three serial cold probes; no exact credit.')
    return 0


if __name__=='__main__':raise SystemExit(main())
