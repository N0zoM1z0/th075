#!/usr/bin/env python3
"""Cold-replay complete original list recovery owners and actual source-local EH references."""
import argparse
import csv
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('list_recovery_source',ROOT/'scripts/verify-vector-insertion-carrier-origins.py')
SOURCE = importlib.util.module_from_spec(SPEC);SPEC.loader.exec_module(SOURCE)
module = SOURCE.module
digest = SOURCE.digest
EVIDENCE = 'config/list-recovery-origin-evidence.json'
MANIFEST_SHA256 = '51cf1923801853c8952f25135a57d198b65e49c896a3e90da892c40f077988bf'
PLAN_DIGESTS = {'groups': 'bcb562289f502fa29ef8aa23c55a2bf1d3a199f81744213b0f704bb9682779a0', 'sections': '94007d156ce2e46f2a1a40880067c6edc546f9d9b83bec61b2c3b62d62cad117', 'weak_references': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'evidence_id': '279416228d2e4996807d697dc229a8dedf3705411179b987ce96b4e0ba930931', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'functions': 'f5f4b157b48b56de131140b9b8f0aeaff233d0a3cac94c6c99a6d3cc644835b5', 'recoveries': 'b887da507a20cc9fffde9981bf6af7c76fb68eb7b1aa0f841bf8af2f4bebf23d', 'retained_unknowns': '4d40e70ccdf4adb69e9534f3247a16b5a6e3c5f7ce1ec138a49a76115f94b5f6', 'historical_snapshots': '1a4730bfa70deb94e3347f8d9c0a3245b1459c7733e6a3c6d0970bde385918d4', 'boundaries': 'd5f0bdfe2199997ccc73c796a69056d6ec4d2f18342c9fdb218cd327e51f636c', 'retained_frames': '55480e3f42509effd7f4f2bd4e0b848cccebfd518083652ded18cc65d0f9b999', 'retained_sha256': '715bd3d609ee625d8db5c3e8f162238b7283d54a48cb2dbfc0e8604b1e2f1f83', 'prior': '7eb410cbb244ca978cc651af5503f53a4317d4a0646a1bccb281b27712adbb1d'}
KEYS = {'0x0041206F': 80, '0x004122C9': 52, '0x0041EFE6': 52, '0x00532196': 52}


def rows(path):
    with (ROOT/path).open(newline='') as stream:return list(csv.DictReader(stream))


def headers(log):
    found={}
    for line in log.splitlines():
        if 'Note: including file:' not in line:continue
        value=line.split('Note: including file:',1)[1].strip().replace('\\','/')
        if value[:3].lower()!='z:/':raise ValueError('ListRecovery original include loses host mapping')
        path=Path(value[2:]);found[str(path.relative_to(ROOT))]=digest(path.read_bytes())
    return found


def verify_plan(m):
    for key,sha in PLAN_DIGESTS.items():
        if SOURCE.BASE.metadata_digest(m[key])!=sha:raise ValueError('ListRecovery immutable whole evidence differs: '+key)
    if (m['evidence_id']!='R218' or {r['address']:r['size'] for r in m['functions']}!=KEYS
            or len(m['functions'])!=4 or len(m['recoveries'])!=4 or len(m['groups'])!=4
            or len(m['sections'])!=40 or sum(r['size'] for r in m['sections'])!=1866
            or sum(len(r['fields']) for r in m['sections'])!=85 or sum(r['kind']=='code' for r in m['sections'])!=36
            or m['weak_references'] or len(m['historical_snapshots'])!=63 or len(m['retained_unknowns'])!=3
            or sum(len(g['control']['emission']) for g in m['groups'])!=767
            or sum(r['size'] for g in m['groups'] for r in g['control']['emission'])!=34542
            or [g['control']['layout']['size'] for g in m['groups']]!=[56,76,88,16]
            or [len(g['control']['headers']) for g in m['groups']]!=[30,31,32,28]):
        raise ValueError('ListRecovery loses scoped full source closures and controls')
    mutable={'proposed_name','module','status','owner','evidence','notes'}
    for r in m['functions']:
        f,o,af,ao=(r[k] for k in ['original_function','original_origin','accepted_function','accepted_origin'])
        if (o['origin']!='unknown' or f['status']!='unclassified' or f['owner']
                or {k:v for k,v in f.items() if k not in mutable}!={k:v for k,v in af.items() if k not in mutable}
                or int(f['size'])!=r['size'] or af['owner']!='library' or af['status']!='excluded'
                or ao['origin']!='library' or ao['disposition']!='exclude' or ao['evidence_id']!='R218'
                or any(af[k] for k in ['source_file','signature','calling_convention']) or af['match_percent']!='0.00'):
            raise ValueError('ListRecovery grants false independent extent/source/ABI/exact credit')
    for rec,n,off in zip(m['recoveries'],[223,189,186,186],[143,137,134,134]):
        root=next(r for r in m['sections'] if r['group']==rec['group'] and r['base']==rec['source_owner'])
        eh=next(r for r in m['sections'] if r['group']==rec['group'] and r['base']==rec['eh_owner'])
        d,field=rec['definition'],rec['eh_field']
        if (root['size']!=n or root['roots']!=[0,off] or root['flow']['code_size']!=n
                or root['flow']['reachable_instruction_count']!=root['flow']['instruction_count']
                or rec['offset']!=off or off+rec['size']!=n
                or eh['size']!=(80 if rec['group']==0 else 88)
                or d not in root['source']['definitions'] or field not in eh['fields']
                or d['offset']!=off or d['storage']!=3 or d['type']!=32
                or field['symbol']!=d['symbol'] or field['symbol_section']!=root['source']['section']
                or field['symbol_offset']!=off or field['symbol_storage']!=3 or field['symbol_type']!=32
                or field['type']!='DIR32' or field['addend']!=0
                or int(rec['address'],16)!=int(root['base'],16)+off
                or rec['parent_origin']['origin']!='library' or int(rec['parent_function']['size'])!=n):
            raise ValueError('ListRecovery loses actual source-local/EH/full-parent ownership')


def verify_native(m,target,c,flow):
    for r in m['functions']:
        a=int(r['address'],16);raw=c.pe_bytes_at(target,a,r['size'])
        if digest(raw)!=r['body_sha256'] or SOURCE.instructions(raw,a,flow)!=r['instructions']:
            raise ValueError('ListRecovery full native recovery/shared exit view differs')
        owner=next(q for q in m['sections'] if q['group']==r['group'] and q['base']==r['source_owner'])
        if (owner['kind']!='code' or int(owner['base'],16)+r['source_offset']!=a
                or r['source_offset']+r['size']!=owner['size']):
            raise ValueError('ListRecovery detaches interior from complete parent')
    for rec in m['recoveries']:
        r=next(q for q in m['functions'] if q['address']==rec['address']);ins=r['instructions']
        throw=48 if rec['group']==0 else 18
        cleanup='0x412180' if rec['group']<2 else ('0x41e340' if rec['group']==2 else '0x5320d0')
        expected_calls=([(10,'0x411e80'),(25,'0x412420'),(39,cleanup),(throw,'0x640c12')] if rec['group']==0
                        else [(9,cleanup),(throw,'0x640c12')])
        if ([(i['offset'],i['operands']) for i in ins if i['mnemonic']=='call']!=expected_calls
                or ins[-1]['mnemonic']!='ret' or ins[-1]['operands']!=('' if rec['group']==0 else '0xc')
                or not any(i['offset']==throw+5 and i['mnemonic']=='mov' and i['operands']=='dword ptr [ebp - 4], 0xffffffff' for i in ins)
                or int(rec['common_exit'],16)!=int(rec['address'],16)+throw+5):
            raise ValueError('ListRecovery truncates rollback/rethrow/shared exit/real return')
        root=next(q for q in m['sections'] if q['group']==rec['group'] and q['base']==rec['source_owner'])
        a=int(root['base'],16);raw=c.pe_bytes_at(target,a,root['size']);all_ins=SOURCE.instructions(raw,a,flow)
        at=141 if rec['group']==0 else rec['offset']-2
        if not any(i['offset']==at and i['mnemonic']=='jmp' and int(i['operands'],16)==int(rec['common_exit'],16) for i in all_ins):
            raise ValueError('ListRecovery loses original normal-path shared-exit edge')
    for boundary,n in zip(m['boundaries'],[1,3,6,6]):
        raw=c.pe_bytes_at(target,int(boundary['alignment_address'],16),boundary['alignment_size'])
        next_=boundary['next_owner'];a=int(next_['address'],16);native=c.pe_bytes_at(target,a,next_['size'])
        if (boundary['alignment_size']!=n or raw!=b'\xcc'*n or raw.hex()!=boundary['alignment_hex']
                or digest(raw)!=boundary['alignment_sha256'] or int(boundary['alignment_address'],16)+n!=a
                or digest(native)!=next_['body_sha256'] or SOURCE.instructions(native,a,flow)!=next_['instructions']):
            raise ValueError('ListRecovery absorbs alignment or crops the next complete owner')
    for r in m['retained_unknowns']:
        a=int(r['address'],16);raw=c.pe_bytes_at(target,a,r['size'])
        if digest(raw)!=r['body_sha256'] or SOURCE.instructions(raw,a,flow)!=r['instructions']:
            raise ValueError('ListRecovery changes a protected ambiguous shape')


def replay(m,evidence_only=False):
    c=module('list_recovery_target','compare-coff-function.py');coff=module('list_recovery_coff','coff_data.py')
    extra=module('list_recovery_carrier','sdk_x3d_carriers.py');flow=module('list_recovery_flow','sdk_image_carriers.py')
    pe=module('list_recovery_permissions','verify-sdk-x3d-origins.py')
    inventory=module('list_recovery_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    extent=module('list_recovery_aux','verify-vendor-record-origins.py');eh=module('list_recovery_eh','compiler_eh.py')
    target=c.verified_target()
    if digest(target)!=m['target_sha256']:raise ValueError('ListRecovery target differs')
    functions={r['address']:r for r in rows('config/functions.csv')};origins={r['address']:r for r in rows('config/function-origins.csv')}
    selected={r['address']:r for r in m['functions']};state='original' if evidence_only else 'accepted'
    for r in m['functions']:
        if functions[r['address']]!=r[state+'_function'] or origins[r['address']]!=r[state+'_origin']:
            raise ValueError('ListRecovery bounded canonical transition differs')
    for r in m['recoveries']:
        if functions[r['source_owner']]!=r['parent_function'] or origins[r['source_owner']]!=r['parent_origin']:
            raise ValueError('ListRecovery changes existing complete library owner')
    for boundary in m['boundaries']:
        r=boundary['next_owner']
        if functions[r['address']]!=r['function'] or origins[r['address']]!=r['origin']:
            raise ValueError('ListRecovery changes independent next owner records')
    for r in m['retained_unknowns']:
        if functions[r['address']]!=r['function'] or origins[r['address']]!=r['origin'] or r['origin']['origin']!='unknown':
            raise ValueError('ListRecovery classifies unrelated getter/empty destruction')
    for r in m['historical_snapshots']:
        old=json.loads((ROOT/r['path']).read_text())
        for key in r['trail']:old=old[key]
        if old!=r['record'] or old['function']['address'] not in selected:
            raise ValueError('ListRecovery rewrites historical literal unknown context')
    for r in m['retained_frames']:
        frame=r['record'];root=next(q for q in m['sections'] if q['group']==r['group'] and q['base']==m['groups'][r['group']]['root'])
        if (frame not in rows('config/compiler-eh-frames.csv') or r['source_field'] not in root['fields']
                or r['source_binding'] not in root['bindings'] or r['source_binding']['target_address']!=frame['handler_address']):
            raise ValueError('ListRecovery substitutes an EH registration/native observed pointer')
        eh.verify_frame(frame,lambda a,n:c.pe_bytes_at(target,a,n),lambda a,n:c.pe_bytes_at(target,a,n),{int(a,16) for a in functions},set())
    verify_native(m,target,c,flow)
    # Reuse unchanged independently owned external checkpoints; no unrelated cold tree is claimed.
    prior=json.loads((ROOT/m['prior']['path']).read_text());prior_verifier=module('list_recovery_prior','verify-list-head-erase-origins.py')
    for ref in prior['prior']['external']:
        key=ref['record']['address']
        if ref['function'] is not None and (functions[key]!=ref['function'] or origins[key]!=ref['origin']):
            raise ValueError('ListRecovery changes retained external canonical provenance')
    shared=prior_verifier.prior_catalog(prior,target,c,coff)
    scratch=ROOT/'build/origin-list-recovery-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as dirname:
        obj=Path(dirname)/'Recovery.obj'
        for group in m['groups']:
            old=json.loads((ROOT/group['path']).read_text());original=old.get('public_control',old);control=group['control']
            if any(original[k]!=control[k] for k in control):raise ValueError('ListRecovery changes original public control')
            candidates=old.get('controls',old.get('sections',[]))
            if group['prior_control'] not in candidates:raise ValueError('ListRecovery source root is not a literal complete prior control')
            result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/control['probe']),str(obj),*control['profile']],cwd=ROOT,capture_output=True,text=True)
            if result.returncode or headers(result.stdout+result.stderr)!=control['headers']:
                raise ValueError('ListRecovery cold natural source/include provenance differs')
            body=obj.read_bytes()
            if inventory(body,c,coff)!=control['emission']:raise ValueError('ListRecovery omits complete ordinary code/data/EH emission')
            layout,_=coff.readonly_section(body,control['layout']['section'],c.coff_name)
            if len(layout)!=control['layout']['size'] or list(struct.unpack('<'+str(len(layout)//4)+'I',layout))!=control['layout_values']:
                raise ValueError('ListRecovery crops full original readonly observation')
            owned=[r for r in m['sections'] if r['group']==group['id']];decoded={}
            catalog=SOURCE.owned_catalog(owned,shared,group['id'],[])
            for r in owned:
                raw,fields,source=extra.section_carrier(body,r['source']['section'],c,coff);a=int(r['base'],16)
                if (SOURCE.BASE.canonical_source(source,body)!=r['source'] or fields!=r['fields'] or len(raw)!=r['size']
                        or digest(raw)!=r['source_sha256'] or pe.image_permissions(target,a,len(raw))!=source['flags']&0xe0000000):
                    raise ValueError('ListRecovery full actual source/AUX/indices/fields/permissions differ')
                decoded[r['source']['section']]=(raw,fields)
                if r['kind']=='code':
                    actual=[dict(function=f,origin=origins[key]) for key,f in functions.items() if a<=int(key,16)<a+r['size']]
                    expected=[dict(function=selected[q['function']['address']][state+'_function'],origin=selected[q['function']['address']][state+'_origin'])
                              if q['function']['address'] in selected else q for q in r['inventory_entries']]
                    if actual!=expected:raise ValueError('ListRecovery hides an inventory entry in its whole source')
            for r in owned:
                raw,fields=decoded[r['source']['section']];a=int(r['base'],16)
                linked,calls,data=SOURCE.BASE.BASE.bind_fields(raw,fields,r['bindings'],catalog,group['id'],a,data_image=r['kind']=='data')
                actual=c.pe_bytes_at(target,a,len(raw))
                if linked!=actual or digest(actual)!=r['body_sha256']:raise ValueError('ListRecovery full unmasked source/native comparison differs')
                if r['kind']=='code':
                    roots={0};roots.update(d['offset'] for d in r['source']['definitions'] if d['storage']==3 and d['type']==32)
                    roots.update(f['symbol_offset']+f['addend'] for q in owned for f in q['fields'] if f['symbol_section']==r['source']['section'] and f['symbol_storage']==6)
                    if sorted(roots)!=r['roots'] or flow.flow(actual,a,r['roots'],fields,calls,data,None,None,None)!=r['flow']:
                        raise ValueError('ListRecovery full normal/catch/cleanup/handler/shared-exit CFG differs')
            root=next(r for r in owned if r['base']==group['root'])
            if (group['symbol'] not in [d['symbol'] for d in root['source']['definitions'] if d['storage']==2 and d['type']==32 and d['offset']==0]
                    or extent.complete_aux_section_size(body,group['symbol'],c.coff_name)!=root['size']):
                raise ValueError('ListRecovery source root lacks its actual complete primary AUX')


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true')
    args=parser.parse_args();m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    for path,sha in [(EVIDENCE,MANIFEST_SHA256),*m['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes())!=sha:raise ValueError('ListRecovery immutable original evidence/probe differs: '+path)
    replay(m,args.evidence_only)
    print('R218 origins OK: four source-owned list recovery interiors236 in unchanged complete parents223/189/186/186; '
          'four actual local catch/EH references and full normal/recovery/shared exits/RET0 or RET12; '
          'four fresh original cold controls767 ordinary emissions34542/full layouts56/76/88/16; '
          '40 whole code/data owners1866/all85 actual fields/36 CFGs; four original EH registrations; '
          '63 literal historical snapshots/three independent unknowns preserved; '
          'alignment1/3/6/6 and next full owners100/5/126/126; no extra unique source bytes/source/private ABI/mapping/exact credit.')
    return 0

if __name__=='__main__':raise SystemExit(main())
