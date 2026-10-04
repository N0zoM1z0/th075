#!/usr/bin/env python3
"""Replay full SDK/ordinary math chains and preserve unresolved original ownership."""
from __future__ import annotations
import argparse
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('math_prior',ROOT/'scripts/verify-vector-producer-origins.py')
PRIOR=importlib.util.module_from_spec(spec);spec.loader.exec_module(PRIOR)
PAIRED=PRIOR.PAIRED;module=PRIOR.module;digest=PRIOR.digest
MANIFEST_SHA256='370786e3232ada4f77a32f1840086273c09d9d2deef44302d0c3b8960c4b1fa9'
PAIRS=[('0x0040D900','0x0040D920','_cos','0x00641754'),('0x0040D940','0x0040D960','_sin','0x00641804'),
       ('0x00412D90','0x00412DB0','_fabs','0x006418CD'),('0x00428D20','0x00428D40','_sqrt','0x00641E54'),
       ('0x00449A60','0x00449A80','_ceil','0x00642120')]
KEYS={a:17 for a,b,s,t in PAIRS}|{b:28 for a,b,s,t in PAIRS}|{'0x00438A60':17,'0x00641FB8':11}
PROFILE=['/Od','/Ob0','/Gy','/GR-','/GX','/Zi','/GS','/I','src','/showIncludes']


def manifest():
    return json.loads((ROOT/'config/math-overload-origin-evidence.json').read_text())


def verify_plan(m):
    if (m['evidence_id']!='R163' or m['target_sha256']!=PAIRED.manifest()['target_sha256']
            or m['probe']!='probes/VC7MathOverloadContexts.cpp' or m['profile']!=PROFILE
            or {r['address']:r['size'] for r in m['functions']}!=KEYS or len(m['functions'])!=12
            or len(m['controls'])!=22 or sum(r['size'] for r in m['controls'])!=484
            or sum(len(r['bindings']) for r in m['controls'])!=22
            or len(m['emission'])!=29 or sum(r['size'] for r in m['emission'])!=602
            or len(m['headers'])!=6 or m['layout_values']!=[4,8,4,4]
            or m['layout'] not in m['emission'] or m['layout']['size']!=16
            or len(m['snapshots'])!=24 or len(m['retained'])!=11 or len(m['runtime'])!=5
            or len(m['contexts'])!=5 or [len(r['calls']) for r in m['contexts']]!=[2,7,3,2,6]):
        raise ValueError('math overload omits complete bounded code/field/ordinary/header/parent coverage')
    for r in m['functions']:
        old,new=r['original_function'],r['accepted_function']
        if (r['decision']!='unknown' or r['original_origin']['origin']!='unknown' or r['accepted_origin']!=r['original_origin']
                or {k:v for k,v in old.items() if k not in ('evidence','notes')}!={k:v for k,v in new.items() if k not in ('evidence','notes')}
                or old['address']!=r['address'] or int(old['size'])!=r['size']
                or new['source_file'] or new['calling_convention'] or new['signature'] or new['match_percent']!='0.00'):
            raise ValueError('math overload infers original ownership/declaration or grants false extent/source/ABI/exact credit')
    expected=[]
    for a,b,s,t in PAIRS:expected.extend([(a,17,'sdk-overload',b),(b,28,'sdk-float-worker',t)])
    expected.append(('0x00438A60',17,'sdk-long-overload','0x00641FB8'))
    for a,b,s,t in PAIRS:expected.extend([(a,17,'ordinary-overload',b),(b,28,'ordinary-float-worker',t)])
    expected.append(('0x00438A60',17,'ordinary-long-overload','0x00641FB8'))
    for r,(a,size,role,callee) in zip(m['controls'],expected):
        section,d=r['section'],r['source_definition']
        if (r['address']!=a or r['size']!=size or r['role']!=role or section not in m['emission']
                or section['size']!=size or d not in section['definitions'] or d['offset'] or d['type']!=32 or d['storage']!=2
                or section['source_sha256']!=r['source_sha256'] or len(section['fields'])!=1
                or len(r['bindings'])!=1 or (role.startswith('ordinary') != ('Ordinary' in d['symbol']))):
            raise ValueError('math overload truncates or substitutes whole genuine SDK/ordinary definitions')
        field=section['fields'][0];b=r['bindings'][0]
        if (field['offset']!=(14 if size==28 else 8) or field['type']!='REL32' or field['addend']
                or b!=dict(offset=field['offset'],type='REL32',symbol=field['symbol']['symbol'],addend=0,target_address=callee)):
            raise ValueError('math overload masks or substitutes real float/long parameter and return-operation field')
    if ([r['address'] for r in m['runtime']]!=['0x00641740','0x006417F0','0x00641E40','0x006418CD','0x00642120']
            or [r['size'] for r in m['runtime']]!=[174,174,186,177,64]
            or any(r['origin']['origin']!='library' or r['source']['decision']!='library' or r['source']['size']!=r['size'] for r in m['runtime'])):
        raise ValueError('math overload discards complete independently accepted runtime owners/shared tails')
    for symbol,t,parent in [('_cos','0x00641754','0x00641740'),('_sin','0x00641804','0x006417F0'),('_sqrt','0x00641E54','0x00641E40')]:
        labels=[r['record'] for r in m['retained'] if r['collection']=='interior_labels' and r['record']['address']==t]
        if (len(labels)!=1 or labels[0]['parent']!=parent or labels[0]['source_offset']!=20
                or labels[0]['source_definition']['symbol']!=symbol or labels[0]['source_definition']['type']!=0):
            raise ValueError('math overload replaces an existing C entry with the incompatible x87 register entry')
    if ([(r['coff_symbol'],r['size']) for r in m['abs_archive_alternatives']]!=[('_abs',11),('_labs',11)]
            or m['abs_expression_control']['profile']!=['/O1','/Ob0','/Gy','/GR-','/GX','/Zi','/GS','/I','src']
            or [(r['coff_symbol'],r['size']) for r in m['abs_expression_control']['functions']]!=[('_AbsIntExpressionControl',11),('_AbsLongExpressionControl',11)]):
        raise ValueError('math overload loses complete independent int/long SDK and ordinary abs ambiguity')
    snapshots={r['address']:r for r in m['snapshots']}
    for a,evidence,size in [('0x0040D8E0','R108',19),('0x004229D0','ghidra-12.1.3-initial-inventory',28),
             ('0x0040F9F0','ghidra-12.1.3-initial-inventory',15),('0x00641DAA','ghidra-12.1.3-initial-inventory',11)]:
        r=snapshots.get(a)
        if not r or r['size']!=size or r['origin']['origin']!='unknown' or r['origin']['evidence_id']!=evidence:
            raise ValueError('math overload resolves independent protected lifetime/copy/destruction/abs ambiguity')


def check_ledger(row,function,origin,evidence_only=False):
    PRIOR.check_ledger(row,function,origin,evidence_only)


def accepted_snapshot(snapshot,function,origin):
    m=manifest()
    if digest((ROOT/'config/math-overload-origin-evidence.json').read_bytes())!=MANIFEST_SHA256:
        raise ValueError('math overload immutable evidence differs')
    verify_plan(m)
    r=next((r for r in m['functions'] if r['address']==function['address']),None)
    return bool(r and snapshot==dict(function=r['original_function'],origin=r['original_origin'])
                and function==r['accepted_function'] and origin==r['accepted_origin'])


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args()
    m=manifest();verify_plan(m)
    for path,expected in [('config/math-overload-origin-evidence.json',MANIFEST_SHA256),(m['probe'],m['probe_sha256']),*m['retained_sha256'].items(),
                (m['abs_expression_control']['probe'],m['abs_expression_control']['probe_sha256'])]:
        if digest((ROOT/path).read_bytes())!=expected:raise ValueError('math overload immutable source/prior evidence differs: '+path)
    c=module('math_target','compare-coff-function.py');coff=module('math_coff','coff_data.py')
    extent=module('math_extent','verify-vendor-record-origins.py');cfg=module('math_cfg','verify-authored-origins.py')
    archive_reader=module('math_archive','verify-runtime-origins.py');fields_reader=module('math_fields','verify-runtime-error-origins.py')
    target=c.verified_target();rows=PAIRED.BUFFER.PRIOR.PRIOR.rows
    if digest(target)!=m['target_sha256']:raise ValueError('math overload supplied target differs')
    functions={r['address']:r for r in rows('functions.csv')};origins={r['address']:r for r in rows('function-origins.csv')};records={r['address']:r for r in m['functions']}
    for r in m['functions']:check_ledger(r,functions[r['address']],origins[r['address']],args.evidence_only)
    for r in m['snapshots']:
        a=r['address']
        if a in records:check_ledger(records[a],functions[a],origins[a],args.evidence_only)
        elif functions[a]!=r['function'] or origins[a]!=r['origin']:raise ValueError('math overload changes independent canonical runtime/protected ambiguity')
        if digest(c.pe_bytes_at(target,int(a,16),r['size']))!=r['body_sha256']:raise ValueError('math overload independent entire target boundary differs')
    for r in m['retained']:
        prior=json.loads((ROOT/r['file']).read_text());observed=prior[r['collection']]
        if not (r['record'] in observed if isinstance(observed,list) else r['record']==observed):raise ValueError('math overload original full runtime/shared-entry/ordinary record differs')
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    for r in m['contexts']:
        a=r['address'];base=int(a,16);body=c.pe_bytes_at(target,base,r['size'])
        if (functions[a]!=r['function'] or origins[a]!=r['origin'] or r['authored_record'] not in rows('authored-origin-evidence.csv') or digest(body)!=r['body_sha256']):
            raise ValueError('math overload independent whole game owner differs')
        cfg.verify_body(body,base,[x for x in rows('authored-origin-switches.csv') if x['address']==a],lambda a,n:c.pe_bytes_at(target,a,n),
                        [x for x in rows('authored-origin-direct-switches.csv') if x['address']==a])
        ins=list(decoder.disasm(body,base))
        for call in r['calls']:
            window=call['instructions'];i=next(i for i,x in enumerate(ins) if x.address==int(window[0]['address'],16))
            observed=[dict(address=f'0x{x.address:08X}',mnemonic=x.mnemonic,operands=x.op_str) for x in ins[i:i+len(window)]]
            if observed!=window or not any(x['address']==call['site'] and x['mnemonic']=='call' and int(x['operands'],16)==int(call['candidate'],16) for x in window):
                raise ValueError('math overload actual full game argument/return context differs')
    archive=(ROOT/'.tools/msvc710/Vc7/lib/libcmt.lib').read_bytes()
    if digest(archive)!=m['archive_sha256']:raise ValueError('math overload pinned CRT archive differs')
    members={off:(name,data) for off,name,data in archive_reader.archive_members(archive)}
    scratch=ROOT/'build/origin-math-overload-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as dirname:
        path=Path(dirname)/'Control.obj'
        def member(r):
            name,data=members[r['member_offset']]
            if name!=r['member'] or digest(data)!=r['member_sha256']:raise ValueError('math overload independent actual archive member differs')
            path.write_bytes(data);return data
        for r in m['runtime']:
            source=r['source'];data=member(source);raw,fields=c.object_function(path,source['coff_symbol']);actual=c.pe_bytes_at(target,int(r['address'],16),r['size'])
            if len(raw)!=r['size'] or digest(raw)!=source['source_sha256'] or digest(actual)!=source['body_sha256']:
                raise ValueError('math overload full independently accepted runtime primary differs')
            fields_reader.compare_fields(raw,fields,actual,int(r['address'],16),source['relocation_bindings'],c)
            linked=bytearray(raw)
            for field,binding in zip(fields,source['relocation_bindings']):
                value=int(binding['target_address'],16)+field['addend']
                if field['type']=='REL32':value-=int(r['address'],16)+field['offset']+4
                struct.pack_into('<I',linked,field['offset'],value & 0xffffffff)
            if bytes(linked)!=actual:raise ValueError('math overload full runtime carrier fails unmasked original-field linking')
            for a,b,s,t in PAIRS:
                if source['address'] in ['0x00641740','0x006417F0','0x00641E40'] and int(t,16)==int(r['address'],16)+20:
                    d=next(d for d in coff.parse_symbols(data,c.coff_name)[1] if d['symbol']==s)
                    if d['offset']!=20 or d['section']!=source['source_definition']['section'] or d['type']!=0:
                        raise ValueError('math overload C stack-double call is replaced by x87 __CI register ABI entry')
        actual=c.pe_bytes_at(target,0x641FB8,11)
        for r in m['abs_archive_alternatives']:
            data=member(r);raw,fields=c.object_function(path,r['coff_symbol'])
            if len(raw)!=11 or fields or raw!=actual or digest(raw)!=r['source_sha256'] or extent.complete_aux_section_size(data,r['coff_symbol'],c.coff_name)!=11:
                raise ValueError('math overload entire abs/labs source alternative differs')
        for control in [m,m['abs_expression_control']]:
            result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/control['probe']),str(path),*control['profile']],cwd=ROOT,capture_output=True,text=True)
            if result.returncode:raise ValueError('math overload natural complete cold source compile failed')
            data=path.read_bytes()
            if control is not m:
                for r in control['functions']:
                    raw,fields=c.object_function(path,r['coff_symbol'])
                    if raw!=actual or fields or len(raw)!=11 or digest(raw)!=r['source_sha256'] or extent.complete_aux_section_size(data,r['coff_symbol'],c.coff_name)!=11:
                        raise ValueError('math overload cold whole ordinary int/long expression ambiguity differs')
                continue
            if PAIRED.BUFFER.PRIOR.PRIOR.included_headers(result.stdout+result.stderr)!=m['headers'] or PAIRED.BUFFER.inventory(data,c,coff)!=m['emission']:
                raise ValueError('math overload actual SDK headers or entire cold ordinary emission differs')
            catalog={}
            def add(symbol,address):
                if symbol in catalog and catalog[symbol]!=address:raise ValueError('math overload overrides whole genuine source/callee ownership')
                catalog[symbol]=address
            for r in m['controls']:add(r['source_definition']['symbol'],int(r['address'],16))
            for a,b,s,t in PAIRS:add(s,int(t,16))
            add('_labs',0x641FB8)
            for r in m['controls']:
                raw,linked=PRIOR.PRIOR.link(data,r,catalog,c);actual_body=c.pe_bytes_at(target,int(r['address'],16),r['size'])
                if linked!=actual_body or digest(raw)!=r['source_sha256'] or digest(actual_body)!=r['body_sha256'] or extent.complete_aux_section_size(data,r['source_definition']['symbol'],c.coff_name)!=r['size']:
                    raise ValueError('math overload entire genuine SDK/ordinary source or unmasked real fields differ')
                cfg.verify_body(actual_body,int(r['address'],16))
            raw,_=coff.readonly_section(data,m['layout']['section'],c.coff_name)
            if list(struct.unpack('<4I',raw))!=[4,8,4,4]:raise ValueError('math overload full compiler observation layout differs')
    cfg.verify_body(c.pe_bytes_at(target,0x641FB8,11),0x641FB8)
    print('R163 review OK: all twelve candidates / 253 bytes remain unknown; genuine SDK and ordinary five float math chains plus long-abs overload compare as 22 whole controls / 484 bytes / 22 unmasked fields; all 29 cold ordinary sections / 602 bytes, six SDK headers and full 16-byte layout; five independently retained whole runtime primaries / 775 bytes and actual stack-double C shared entries replay from pinned archive; entire abs/labs plus cold ordinary int/long expression / 11 alternatives are byte-equal; five whole authored game parents / 8610 bytes and twenty actual call windows retained; string-length/thunk hypothesis rejected, original ownership/declarations unknown; no origin/source/private ABI/mapping/exact credit.')
    return 0


if __name__=='__main__':
    try:raise SystemExit(main())
    except (OSError,KeyError,IndexError,StopIteration,ValueError,struct.error,json.JSONDecodeError) as error:
        print('error: '+str(error),file=sys.stderr);raise SystemExit(1)
