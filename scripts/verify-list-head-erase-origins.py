#!/usr/bin/env python3
"""Cold-replay complete list head/erase source; preserve ambiguous independent leaves."""
import argparse
import csv
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('list_head_source', ROOT / 'scripts/verify-vector-insertion-carrier-origins.py')
SOURCE = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(SOURCE)
module = SOURCE.module
digest = SOURCE.digest
EVIDENCE = 'config/list-head-erase-origin-evidence.json'
MANIFEST_SHA256 = 'd60078dcb47d90103d3ae25fe1e8645cde568c35f1947567a0fffaf83de74274'
PLAN_DIGESTS = {'groups': '1e4169083edc83c860e7127dffefc8bc19a9795f799a481fc1473ba82fbbaa70', 'sections': '8f5f30bd27b663086edf9209495cf73af9697987d6540e922978703f6ec53ac4', 'weak_references': '810e24bfab07f1aefd1946d6c3681d187695899efcb12ba7cebdcac82fa7784e', 'evidence_id': 'f75083c5d4178d0770c48419b362981c3e05ac06d7d1c48e639510b8898b180e', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'functions': 'c0f1575c347d123def4363124cc77274fc4b192601430bb1e4dd43af56181b83', 'retained_unknowns': '837ab30dd97ce695eb58748b280d8f047e73952d8e8b1b74f1f6207247db2407', 'historical_snapshots': 'ce722519cc564680eaad8735c41d5a03bfd095726e095a28e084e7f5afe62e2b', 'alternatives': 'e68d68b5a34b160464f7531e20f80feab0cadd765b4311c3d12988b4244823f6', 'parents': 'b6b304aed416cb4df3b9111bd710c0b1e1acceaa3a5b06fc4ff25d87c0af5e79', 'recovery': 'b8aeab2997e67c799b43339841a0b10f016f8eae4a0dee41e95221fa8e304358', 'extent': '0fc6e25bf1600089915364ab8c306ae5e3eb5c896d6ba976172b057baa139398', 'public_control': 'ed7f43952d3c302c050675f3f7ce413ba578c9e44feefbef39a5ce0e552e84c0', 'prior': '1fdc7eb449345d0d1b7d4209e2b89d1e8b2893ea985dc3654b7eb68c2bbf9d80', 'retained_sha256': 'b17341be57e690feb2ea5bef836cfd5facf19f0c7749d1d1d8170e40ccba9bd7'}
WHOLE = {'0x00531C00': 56, '0x00531C80': 40, '0x005320C0': 14, '0x00532080': 53, '0x00531F30': 223, '0x00531E70': 186, '0x00532320': 42, '0x005323A0': 22, '0x00532450': 35, '0x00531FBF': 80}

def headers(log):
    found = {}
    for line in log.splitlines():
        if 'Note: including file:' not in line: continue
        value = line.split('Note: including file:', 1)[1].strip().replace('\\', '/')
        if value[:3].lower() != 'z:/': raise ValueError('ListHead original include loses host mapping')
        path = Path(value[2:]); relative = str(path.relative_to(ROOT))
        if not relative.startswith('.tools/msvc710/Vc7/include/'):
            raise ValueError('ListHead original include imports an unrelated source')
        found[relative] = digest(path.read_bytes())
    return found



def verify_plan(m):
    for key, sha in PLAN_DIGESTS.items():
        if SOURCE.BASE.metadata_digest(m[key]) != sha:
            raise ValueError('ListHead immutable whole evidence differs: ' + key)
    if ({r['address']:r['size'] for r in m['functions']} != WHOLE
            or len(m['functions']) != 10 or len(m['groups']) != 1
            or len(m['sections']) != 105 or sum(r['size'] for r in m['sections']) != 5126
            or sum(len(r['fields']) for r in m['sections']) != 254
            or sum(r['kind']=='code' for r in m['sections']) != 86
            or len(m['historical_snapshots']) != 64 or len(m['retained_unknowns']) != 5
            or len(m['weak_references']) != 2
            or len(m['public_control']['emission']) != 110
            or sum(r['size'] for r in m['public_control']['emission']) != 5222
            or m['public_control']['layout_values'] != [16,12,4,4]):
        raise ValueError('ListHead loses bounded complete source and alternatives')
    for r in m['functions']:
        f,o,af,ao=(r[k] for k in ['original_function','original_origin','accepted_function','accepted_origin'])
        if (o['origin']!='unknown' or f['status']!='unclassified' or f['owner']
                or any(f[k] or af[k] for k in ['source_file','signature','calling_convention'])
                or f['match_percent']!='0.00' or af['match_percent']!='0.00'
                or any(af[k]!=f[k] for k in ['address','current_name'])
                or int(f['size'])!=(143 if r['address']=='0x00531F30' else r['size'])
                or int(af['size'])!=r['size']
                or af['span_end']!=f"0x{int(r['address'],16)+r['size']-1:08X}"
                or ao['evidence_id']!='R216' or af['owner']!='library' or af['status']!='excluded'
                or ao['origin']!='library' or ao['disposition']!='exclude'):
            raise ValueError('ListHead gains unsupported source/ABI/exact/extent credit')
    root=next(r for r in m['sections'] if r['base']=='0x00531F30')
    eh=next(r for r in m['sections'] if r['base']=='0x00669E0C')
    rec=m['recovery'];d,field=rec['definition'],rec['eh_field']
    if (root['size']!=223 or root['roots']!=[0,143] or eh['size']!=80
            or root['flow']['code_size']!=223 or m['extent']['unique_policy_bytes']!=671
            or d not in root['source']['definitions'] or field not in eh['fields']
            or d['offset']!=143 or d['storage']!=3 or d['type']!=32
            or field['symbol']!=d['symbol'] or field['symbol_section']!=root['source']['section']
            or field['symbol_offset']!=143 or field['symbol_storage']!=3 or field['addend']!=0
            or rec['address']!='0x00531FBF' or rec['size']!=80 or rec['common_exit']!='0x00531FF4'):
        raise ValueError('ListHead loses complete source-local recovery/EH ownership')


def verify_native(m,target,c,flow):
    auth=module('list_head_authored','verify-authored-origins.py')
    for r in m['functions']:
        a=int(r['address'],16);raw=c.pe_bytes_at(target,a,r['size'])
        if digest(raw)!=r['body_sha256'] or SOURCE.instructions(raw,a,flow)!=r['instructions']:
            raise ValueError('ListHead entire native view differs')
        owner=next(q for q in m['sections'] if q['base']==r['source_owner'])
        if (owner['kind']!='code' or int(owner['base'],16)+r['source_offset']!=a
                or r['source_offset']+r['size']>owner['size']):
            raise ValueError('ListHead interior escapes its complete source owner')
    root=next(r for r in m['functions'] if r['address']=='0x00531F30')
    rec=next(r for r in m['functions'] if r['address']=='0x00531FBF')
    if (not any(i['offset']==141 and i['mnemonic']=='jmp' and i['operands']=='0x531ff4' for i in root['instructions'])
            or not any(i['offset']==48 and i['mnemonic']=='call' and i['operands']=='0x640c12' for i in rec['instructions'])
            or rec['instructions'][-1]['mnemonic']!='ret' or rec['instructions'][-1]['operands']):
        raise ValueError('ListHead truncates rollback/rethrow/shared normal exit/RET')
    p=m['extent']['alignment'];raw=c.pe_bytes_at(target,int(p['address'],16),1)
    if raw!=b'\xcc' or raw.hex()!=p['hex'] or digest(raw)!=p['sha256']:
        raise ValueError('ListHead absorbs alignment')
    for r in m['retained_unknowns']:
        a=int(r['address'],16);raw=c.pe_bytes_at(target,a,r['size'])
        if (digest(raw)!=r['body_sha256'] or SOURCE.instructions(raw,a,flow)!=r['instructions']
                or list(auth.verify_body(raw,a))!=r['cfg']):
            raise ValueError('ListHead protected ambiguous native shape differs')
    for r in m['parents']:
        a=int(r['address'],16);raw=c.pe_bytes_at(target,a,r['size'])
        if (digest(raw)!=r['body_sha256'] or SOURCE.instructions(raw,a,flow)!=r['instructions']
                or list(auth.verify_body(raw,a,r['switches'],lambda x,n:c.pe_bytes_at(target,x,n),r['direct_switches']))!=r['cfg']):
            raise ValueError('ListHead whole reviewed game parent differs')
        actual=[dict(site=f"0x{a+i['offset']:08X}",instructions=r['instructions'][j-4:j+1])
                for j,i in enumerate(r['instructions']) if i['mnemonic']=='call' and i['operands']=='0x531c00']
        if actual!=r['call_sequences'] or len(actual)!=1 or actual[0]['instructions'][-2]['operands']!='ecx, 0xfec':
            raise ValueError('ListHead loses actual complete parent receiver sequence')


def prior_catalog(m,target,c,coff):
    prior=json.loads((ROOT/m['prior']['path']).read_text())
    catalog=SOURCE.BASE.retained_catalog(prior);shared={'__except_list':0}
    # Unchanged snapshots are checkpoint inputs, never new ownership credit.
    for r in m['prior']['external']:
        old=prior['external'][r['index']]
        if old!=r['record']:raise ValueError('ListHead replaces prior external provenance')
        obj=json.loads((ROOT/r['path']).read_text())
        for k in r['trail']:obj=obj[k]
        row=old['record'];a=int(row.get('target_address',old['address']),16)
        if obj!=row or digest(c.pe_bytes_at(target,a,old['size']))!=row['body_sha256']:
            raise ValueError('ListHead crops whole retained external native body')
        if catalog.get(old['symbol'])!=int(old['address'],16):
            raise ValueError('ListHead external native observation overrides source catalog')
        shared[old['symbol']]=catalog[old['symbol']]
    reader=module('list_head_archive','verify-runtime-origins.py')
    archive=(ROOT/'.tools/msvc710/Vc7/lib/libcmt.lib').read_bytes()
    expected='6e2b3742e58245de52149137f64281b73db1487a07a31e165fff269fbf9b2ee8'
    if digest(archive)!=expected:raise ValueError('ListHead whole CRT archive differs')
    members={off:(name,body) for off,name,body in reader.archive_members(archive)}
    absolute=m['prior']['absolute']['__except_list'];name,body=members[absolute['member_offset']]
    _,defs=coff.parse_symbols(body,c.coff_name)
    if (name!=absolute['member'] or digest(body)!=absolute['member_sha256']
            or absolute['definition'] not in defs or absolute['definition']['section']!=-1
            or absolute['definition']['offset']!=0):
        raise ValueError('ListHead invents the absolute FS offset')
    standard=module('list_head_standard','verify-standard-exception-origins.py')
    for r in m['prior']['external']:
        row=r['record']['record']
        if 'member_offset' not in row:continue
        name,body=members[row['member_offset']]
        if name!=row['member'] or digest(body)!=row['member_sha256']:
            raise ValueError('ListHead retained full source member differs')
        if 'source_anchor' in row:
            raw,desc,anchor=standard.whole_defining_section(body,row['symbol'],c,coff)
            if desc!=row['source_section'] or anchor!=row['source_anchor']:
                raise ValueError('ListHead loses complete vtable and interior address point')
            linked=bytearray(raw)
            for f,b in zip(desc['relocations'],row['relocations']):
                if {k:b[k] for k in f}!=f:raise ValueError('ListHead retained source field differs')
                struct.pack_into('<I',linked,f['offset'],(int(b['target_address'],16)+f['addend'])&0xffffffff)
            if linked!=c.pe_bytes_at(target,int(row['target_address'],16),len(raw)) or digest(raw)!=row['source_sha256']:
                raise ValueError('ListHead complete original vtable fields differ')
        else:
            _,defs=coff.parse_symbols(body,c.coff_name)
            if row['source_definition'] not in defs:raise ValueError('ListHead loses actual source definition')
            # The immutable earlier record retains its complete source and all bindings.
            extra=module('list_head_prior_carrier','sdk_x3d_carriers.py')
            raw,fields,source=extra.section_carrier(body,row['source_definition']['section'],c,coff)
            if len(raw)!=row['size'] or digest(raw)!=row['source_sha256']:
                raise ValueError('ListHead retained source owner was cropped')
            linked=bytearray(raw)
            if len(fields)!=len(row['relocation_bindings']):raise ValueError('ListHead drops retained source field')
            for f,b in zip(fields,row['relocation_bindings']):
                if any(f[k]!=b[k] for k in ['offset','type','symbol','addend']):raise ValueError('ListHead retained relocation differs')
                dest=int(b['target_address'],16)+f['addend'];a=int(row['address'],16)
                value=dest-a-f['offset']-4 if f['type']=='REL32' else dest
                struct.pack_into('<I',linked,f['offset'],value&0xffffffff)
            if linked!=c.pe_bytes_at(target,int(row['address'],16),len(raw)):
                raise ValueError('ListHead complete original external source body differs')
    return shared


def replay(m,evidence_only=False):
    c=module('list_head_target','compare-coff-function.py');coff=module('list_head_coff','coff_data.py')
    extra=module('list_head_carriers','sdk_x3d_carriers.py');flow=module('list_head_flow','sdk_image_carriers.py')
    pe=module('list_head_permissions','verify-sdk-x3d-origins.py')
    inventory=module('list_head_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    target=c.verified_target()
    if digest(target)!=m['target_sha256']:raise ValueError('ListHead target identity differs')
    functions={r['address']:r for r in csv.DictReader((ROOT/'config/functions.csv').open())}
    origins={r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
    selected={r['address']:r for r in m['functions']};state='original' if evidence_only else 'accepted'
    for r in m['functions']:
        if functions[r['address']]!=r[state+'_function'] or origins[r['address']]!=r[state+'_origin']:
            raise ValueError('ListHead bounded canonical transition differs')
    for r in m['retained_unknowns']:
        if functions[r['address']]!=r['function'] or origins[r['address']]!=r['origin']:
            raise ValueError('ListHead classifies an independently ambiguous leaf')
    p=m['extent']['next_owner']
    if functions[p['base']]!=p['function'] or origins[p['base']]!=p['origin'] or p['size']!=100:
        raise ValueError('ListHead changes next independently complete Tidy owner')
    for r in m['historical_snapshots']:
        old=json.loads((ROOT/r['path']).read_text())
        for k in r['trail']:old=old[k]
        if old!=r['record'] or old['function']['address'] not in {q['address'] for q in m['retained_unknowns']}:
            raise ValueError('ListHead rewrites old literal unknown snapshots')
    for r in m['prior']['external']:
        key=r['record']['address']
        if r['function'] is not None and (functions.get(key)!=r['function'] or origins.get(key)!=r['origin']):
            raise ValueError('ListHead changes retained external canonical ownership')
    for r in m['parents']:
        if functions[r['address']]!=r['function'] or origins[r['address']]!=r['origin']:
            raise ValueError('ListHead changes whole accepted parent records')
        records=list(csv.DictReader((ROOT/'config/authored-origin-evidence.csv').open()))
        if r['record'] not in records:raise ValueError('ListHead changes accepted parent proof')
        for filename,key in [('authored-origin-switches.csv','switches'),('authored-origin-direct-switches.csv','direct_switches')]:
            current=[q for q in csv.DictReader((ROOT/'config'/filename).open()) if q['address']==r['address']]
            if current!=r[key]:raise ValueError('ListHead changes whole parent switch registry')
    verify_native(m,target,c,flow);shared=prior_catalog(m,target,c,coff)
    scratch = ROOT / 'build/origin-list-head-erase-verification'; scratch.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj = Path(temp) / 'ListHead.obj'; control = m['public_control']
        result = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / control['probe']), str(obj), *control['profile']], cwd=ROOT, capture_output=True, text=True)
        if result.returncode or headers(result.stdout + result.stderr) != control['headers']:
            raise ValueError('ListHead cold generic source/original includes differ')
        body = obj.read_bytes()
        if inventory(body, c, coff) != control['emission']: raise ValueError('ListHead omits ordinary code/data/EH emission')
        layout, _ = coff.readonly_section(body, control['layout']['section'], c.coff_name)
        if len(layout) != 16 or list(struct.unpack('<4I', layout)) != control['layout_values']:
            raise ValueError('ListHead crops the complete byte observation carrier')
        if [SOURCE.weak_record(body, r['symbol'], c, coff) for r in m['weak_references']] != m['weak_references']:
            raise ValueError('ListHead loses actual weak AUX/strong fallback')
        rows = m['sections']; decoded = {}
        for r in rows:
            raw, fields, source = extra.section_carrier(body, r['source']['section'], c, coff); a = int(r['base'], 16)
            if (SOURCE.BASE.canonical_source(source, body) != r['source'] or fields != r['fields']
                    or len(raw) != r['size'] or digest(raw) != r['source_sha256']
                    or pe.image_permissions(target, a, len(raw)) != source['flags'] & 0xe0000000):
                raise ValueError('ListHead complete source/AUX/fields/permissions differ')
            decoded[r['source']['section']] = (raw, fields)
            if r['kind'] == 'code':
                actual = [dict(function=f, origin=origins[k]) for k, f in functions.items() if a <= int(k, 16) < a + r['size']]
                expected = [dict(function=selected[q['function']['address']][state + '_function'],
                                 origin=selected[q['function']['address']][state + '_origin'])
                            if q['function']['address'] in selected else q for q in r['inventory_entries']]
                if actual != expected: raise ValueError('ListHead full source hides an inventory entry')
        for g in m['groups']:
            rows = [r for r in m['sections'] if r['group'] == g['id']]
            catalog = SOURCE.owned_catalog(rows, shared, g['id'], [r for r in m['weak_references'] if r['symbol'] in g['weak_symbols']])
            for r in rows:
                raw, fields = decoded[r['source']['section']]; a = int(r['base'], 16)
                linked, calls, data = SOURCE.BASE.BASE.bind_fields(raw, fields, r['bindings'], catalog, g['id'], a, data_image=r['kind'] == 'data')
                actual = c.pe_bytes_at(target, a, len(raw))
                if linked != actual or digest(actual) != r['body_sha256']: raise ValueError('ListHead complete unmasked body differs')
                if r['kind'] == 'code':
                    roots = {0}; roots.update(d['offset'] for d in r['source']['definitions'] if d['type'] == 32 and d['storage'] == 3)
                    roots.update(f['symbol_offset'] + f['addend'] for q in rows for f in q['fields']
                                 if f['symbol_section'] == r['source']['section'] and f['symbol_storage'] == 6)
                    if sorted(roots) != r['roots'] or flow.flow(actual, a, r['roots'], fields, calls, data, None, None, None) != r['flow']:
                        raise ValueError('ListHead complete normal/EH/unwind/shared-exit CFG differs')

        # Replay original public ordinary alternatives, without reinterpreting historical ownership.
        for plan in m['alternatives']:
            control=plan['public_control']
            result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/control['probe']),str(obj),*control['profile']],cwd=ROOT,capture_output=True,text=True)
            if result.returncode or headers(result.stdout+result.stderr)!=control['headers']:
                raise ValueError('ListHead alternative cold source/includes differ')
            body=obj.read_bytes()
            if inventory(body,c,coff)!=control['emission']:raise ValueError('ListHead alternative whole ordinary emission differs')
            layout,_=coff.readonly_section(body,control['layout']['section'],c.coff_name)
            if list(struct.unpack('<'+str(len(layout)//4)+'I',layout))!=control['layout_values']:
                raise ValueError('ListHead alternative whole layout differs')
            for r in plan['controls']:
                raw,fields,source=extra.section_carrier(body,r['source']['section'],c,coff)
                if (SOURCE.BASE.canonical_source(source,body)!=r['source'] or fields!=r['fields'] or fields
                        or len(raw)!=r['size'] or digest(raw)!=r['source_sha256']):
                    raise ValueError('ListHead full library/ordinary alternative differs')
                key={'next':'0x00531D80','previous':'0x00531D90','value':'0x004124C0'}.get(r.get('role'))
                if key is None and not r.get('role'):key='0x00532350'
                if key and raw!=c.pe_bytes_at(target,int(key,16),r['size']):
                    raise ValueError('ListHead alternative is not entirely unmasked byte equal')


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true')
    args=parser.parse_args();m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    for path,sha in [(EVIDENCE,MANIFEST_SHA256),(m['public_control']['probe'],m['public_control']['probe_sha256']),*m['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes())!=sha:raise ValueError('ListHead immutable input differs: '+path)
    replay(m,args.evidence_only)
    print('R216 origins OK: ten library entries751, nine unique policies671; complete head223/recovery80/source-local EH/all exits; '
          '105 whole code/data owners5126/all254 actual fields/86 CFGs; 110 full ordinary emissions5222/28 original includes/layout16; '
          'two actual weak AUX/strong owners; thirteen unchanged external checkpoints and whole CRT source anchors; '
          'five ambiguous leaves preserved with two original alternative cold probes and64 literal historical snapshots; '
          'whole game parent314/receiver+FEC; single CC alignment/next Tidy100; no source/private ABI/mapping/exact credit.')
    return 0

if __name__=='__main__':raise SystemExit(main())
