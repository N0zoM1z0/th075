#!/usr/bin/env python3
"""Cold-replay complete original vector count-assignment and ordinary graphs."""
import argparse
import csv
import json
from pathlib import Path
import struct
import subprocess
import tempfile
import importlib.util

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('count_source', ROOT/'scripts/verify-vector-insertion-carrier-origins.py')
SOURCE = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(SOURCE)
module = SOURCE.module
digest = SOURCE.digest
EVIDENCE = 'config/vector-count-assignment-origin-evidence.json'
MANIFEST_SHA256 = 'f410ceed8099574af4d9fe71546474c3aecfc5a2d3fbf76ac942f817046419c5'
PLAN_DIGESTS = {'groups': '38b29713b29cc97190426ad55db7f9ba5562bf6c2141ac7b6cb894d17e9fe95d', 'sections': '56698e3d8bc7c2733027425c387375035c9d7e4c16a9f2efe5bc294ed040e042', 'weak_references': 'a5bef64abfb306c21174da20c67d2bb21688653abfd3e0d38f3185cd7d637d05', 'evidence_id': '0ced346a50effdc7b2c7d0d0992124405e3352e9348594f6416625bd9f4d35c6', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'functions': 'da0f64b6386dad5a756aaa749d32ff06793c8279d065c43b3f0e032ace6b6226', 'parents': 'ea1dfd5ac093ad0e1221979c75ba4e2c51b5dd32343d5288599cbe46ec38f607', 'boundaries': '5fb707a716ca19be03835fc012cdab141150391f826dc12c6d7406582df2425b', 'historical_snapshots': '3968c08466d497de1cd260d29d1c2d618010aa0c9f69851a0a336f40590958e0', 'retained_unknowns': '1bfe738a5af19c48c2f19fb89eddda4962274badbac06df13bc1f609f07a4837', 'implicit_controls': '35af372664fe40d799ffe15dcf4577555b0880867263a5769b1d82dbd2b8bc76', 'shared': 'f110ddebfdd8f17bd3e6b705ba61f31fd66559a3ca3cb3e35c349eb0514ad423', 'absolute': '8e1f56739e02ad0900ff6fe1a81eecb7cfcf9597595512608c6e532445948d11', 'opaque_api': '4c2e3a4b426101ab5fd67c8b5a8c01d87825fbbde734e4005e5980d7aa614e27', 'crt_archive_sha256': '69d0301fde85b097b2afc8e5732879473468d247ae0b55492fdc2063da1f7f6c', 'canonical': '5c477b8a358cf24f3381a4653ae7d0ed53b4e553e000c7e2677fbbbbf14124ec', 'public_control': 'b40da0892da90679cec761dd32cc9dab78147e547871a02213481ba02b0a0f0d', 'retained_sha256': '7d761bef95f7969d16eff1f6d2f40031d7b7dcfd880563975d52d23344993d78', 'interpretation': '7a638f6418c5b5fc0af75398daa5afd55f43b3851ee54aa51ae1c13425917b54'}
CONFIDENCE = 'complete-original-vector-count-assignment-scoped-source-and-independent-game-receivers'
WHOLE = {'0x0040E000':158, '0x0040DDA0':29, '0x005F84B0':167,
         '0x005F8000':29, '0x005F8EF0':31}


def rows(name):
    return list(csv.DictReader((ROOT/'config'/name).open()))


def headers(log):
    found = {}
    for line in log.splitlines():
        if 'Note: including file:' not in line: continue
        value = line.split('Note: including file:',1)[1].strip().replace('\\','/')
        if value[:3].lower() != 'z:/': raise ValueError('Count assignment loses original host include mapping')
        path = Path(value[2:]); relative = str(path.relative_to(ROOT))
        if not relative.startswith('.tools/msvc710/Vc7/include/') and relative != 'tests/origin_probes/VectorInsertionCarriers.cpp':
            raise ValueError('Count assignment imports unrelated source')
        found[relative] = digest(path.read_bytes())
    return found


def verify_plan(m):
    for key,sha in PLAN_DIGESTS.items():
        if SOURCE.BASE.metadata_digest(m[key]) != sha:
            raise ValueError('Count assignment complete evidence differs: '+key)
    if m['evidence_id'] != 'R223' or {r['address']:r['size'] for r in m['functions']} != WHOLE:
        raise ValueError('Count assignment loses bounded complete roots and public owners')
    for r in m['functions']:
        f,o,af,ao = [r[k] for k in ['original_function','original_origin','accepted_function','accepted_origin']]
        if (o['origin'] != 'unknown' or af['owner'] != 'library' or af['status'] != 'excluded'
                or any(af[k] != f[k] for k in ['address','size','span_end','current_name'])
                or any(af[k] for k in ['source_file','signature','calling_convention'])
                or af['match_percent'] != '0.00' or ao != dict(address=r['address'],origin='library',
                    subsystem='VC71STL',disposition='exclude',confidence=CONFIDENCE,evidence_id='R223')):
            raise ValueError('Count assignment grants unsupported extent/ABI/source/exact ownership')
    for q in m['retained_unknowns']:
        if q['origin']['origin'] != 'unknown' or q['function']['owner'] or q['function']['status'] != 'unclassified':
            raise ValueError('Count assignment infers original private lifetime ownership')


def verify_native(m,target,c,flow):
    authored = module('count_native_cfg','verify-authored-origins.py')
    owners = m['functions']+m['parents']+[m['opaque_api']]
    for r in owners:
        a = int(r['address'],16); raw = c.pe_bytes_at(target,a,r['size'])
        if (digest(raw) != r['body_sha256'] or SOURCE.instructions(raw,a,flow) != r['instructions']
                or list(authored.verify_body(raw,a,r.get('switches',[]),lambda x,n:c.pe_bytes_at(target,x,n),
                    r.get('direct_switches',[]))) != r['cfg']):
            raise ValueError('Count assignment complete native owner/CFG differs')
        if 'record' in r:
            if (r['record'] not in rows('authored-origin-evidence.csv')
                    or r['origin']['origin'] != 'authored'
                    or r['record']['body_sha256'] != digest(raw)
                    or [q for q in rows('authored-origin-switches.csv') if q['address']==r['address']] != r.get('switches',[])
                    or [q for q in rows('authored-origin-direct-switches.csv') if q['address']==r['address']] != r.get('direct_switches',[])):
                raise ValueError('Count assignment loses independently accepted complete game context')
        for window in r.get('call_sequences',[]):
            sequence = window['instructions']; ins = r['instructions']
            offset = sequence[0]['offset']; start = next(i for i,q in enumerate(ins) if q['offset']==offset)
            if ins[start:start+len(sequence)] != sequence or not any(
                    q['mnemonic']=='call' and q['operands']==hex(int(window['target'],16))
                    and a+q['offset']==int(window['site'],16) for q in sequence):
                raise ValueError('Count assignment loses actual complete game argument/receiver window')
    for r in m['boundaries']:
        raw = c.pe_bytes_at(target,int(r['address'],16),r['size'])
        if raw.hex() != r['hex'] or digest(raw) != r['sha256'] or raw != b'\xcc'*r['size']:
            raise ValueError('Count assignment folds external alignment into the source owner')


def verify_control(m,body,target,c,coff,flow,shared):
    extra = module('count_sections','sdk_x3d_carriers.py')
    pe = module('count_permissions','verify-sdk-x3d-origins.py')
    inventory = module('count_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    control = m['public_control']
    if inventory(body,c,coff) != control['emission']: raise ValueError('Count assignment omits complete cold ordinary emission')
    raw,_ = coff.readonly_section(body,control['layout']['section'],c.coff_name)
    if list(struct.unpack('<16I',raw)) != control['layout_values']:
        raise ValueError('Count assignment crops complete merged readonly carrier')
    if [SOURCE.weak_record(body,r['symbol'],c,coff) for r in m['weak_references']] != m['weak_references']:
        raise ValueError('Count assignment replaces actual weak AUX/fallback definition')
    decoded = {}
    for r in m['sections']:
        raw,fields,source = extra.section_carrier(body,r['source']['section'],c,coff)
        a = int(r['base'],16)
        if (SOURCE.BASE.canonical_source(source,body) != r['source'] or fields != r['fields']
                or len(raw) != r['size'] or digest(raw) != r['source_sha256']
                or pe.image_permissions(target,a,len(raw)) != source['flags'] & 0xe0000000):
            raise ValueError('Count assignment loses full defining COFF/AUX/lines/fields/permissions')
        decoded[r['source']['section']] = (raw,fields)
    for g in m['groups']:
        scoped = [r for r in m['sections'] if r['group']==g['id']]
        refs = [r for r in m['weak_references'] if r['symbol'] in g['weak_symbols']]
        catalog = SOURCE.owned_catalog(scoped,shared,g['id'],refs)
        for r in scoped:
            raw,fields = decoded[r['source']['section']]; a = int(r['base'],16)
            linked,calls,data = SOURCE.BASE.BASE.bind_fields(raw,fields,r['bindings'],catalog,g['id'],a,
                data_image=r['kind']=='data')
            native = c.pe_bytes_at(target,a,len(raw))
            if linked != native or digest(native) != r['body_sha256']:
                raise ValueError('Count assignment entire unmasked source/native body differs')
            if r['kind']=='code':
                roots = {0}; roots.update(d['offset'] for d in r['source']['definitions'] if d['type']==32 and d['storage']==3)
                roots.update(f['symbol_offset']+f['addend'] for q in scoped for f in q['fields']
                    if f['symbol_section']==r['source']['section'] and f['symbol_storage']==6)
                if sorted(roots) != r['roots'] or flow.flow(native,a,r['roots'],fields,calls,data,None,None,None) != r['flow']:
                    raise ValueError('Count assignment normal/EH/unwind/shared-exit graph differs')
    for q in m['implicit_controls']:
        raw,fields,source = extra.section_carrier(body,q['source']['section'],c,coff)
        if (SOURCE.BASE.canonical_source(source,body) != q['source'] or fields != q['fields']
                or digest(raw) != q['source_sha256'] or SOURCE.instructions(raw,0,flow) != q['instructions']):
            raise ValueError('Count assignment changes whole implicit copy controls')
        if any(f['symbol'].startswith(('?erase@','?insert@')) for f in fields):
            raise ValueError('Count assignment substitutes range policy for implicit value assignment')


def replay(m,evidence_only=False):
    c = module('count_target','compare-coff-function.py'); coff = module('count_coff','coff_data.py')
    flow = module('count_flow','sdk_image_carriers.py'); target = c.verified_target()
    if digest(target) != m['target_sha256']: raise ValueError('Count assignment target identity differs')
    for path,sha in m['retained_sha256'].items():
        if digest((ROOT/path).read_bytes()) != sha: raise ValueError('Count assignment changes retained evidence/source: '+path)
    fs = {r['address']:r for r in rows('functions.csv')}; origins = {r['address']:r for r in rows('function-origins.csv')}
    selected = {r['address']:r for r in m['functions']}; state = 'original' if evidence_only else 'accepted'
    for q in m['canonical']:
        key = q['function']['address']; expected = q
        if key in selected: expected = dict(function=selected[key][state+'_function'],origin=selected[key][state+'_origin'])
        if dict(function=fs[key],origin=origins[key]) != expected:
            raise ValueError('Count assignment bounded canonical state differs: '+key)
    for q in m['historical_snapshots']:
        old = json.loads((ROOT/q['path']).read_text())
        for part in q['trail']: old = old[part]
        original = selected[old['function']['address']]['original_function']
        if (old != q['record'] or old['origin'] != selected[old['function']['address']]['original_origin']
                or any(old['function'][key] != original[key] for key in original if key not in ['evidence','notes'])):
            raise ValueError('Count assignment rewrites historical unknown evidence')
    verify_native(m,target,c,flow)
    result = subprocess.run([str(ROOT/'scripts/repo-python'),str(ROOT/'scripts/verify-nested-deque-size-origins.py')],
        cwd=ROOT,capture_output=True,text=True)
    if result.returncode: raise ValueError('Count assignment independent original runtime/exception graph failed: '+result.stderr[-1800:])
    print(result.stdout.strip(),flush=True)
    prior = json.loads((ROOT/'config/nested-deque-size-origin-evidence.json').read_text())
    catalog = SOURCE.BASE.retained_catalog(prior); shared = {}
    for q in m['shared']:
        owner = q['owner']
        if prior[owner['collection']][owner['index']] != owner['record'] or catalog.get(q['symbol']) != int(q['address'],16):
            raise ValueError('Count assignment field destinations override original source-defined owners')
        shared[q['symbol']] = catalog[q['symbol']]
    rt = module('count_crt','verify-runtime-origins.py')
    crt = (ROOT/'.tools/msvc710/Vc7/lib/libcmt.lib').read_bytes()
    if digest(crt) != m['crt_archive_sha256']: raise ValueError('Count assignment original CRT archive differs')
    absolute = m['absolute']['__except_list']
    name,member = {a:(n,b) for a,n,b in rt.archive_members(crt)}[absolute['member_offset']]
    if (name != absolute['member'] or digest(member) != absolute['member_sha256']
            or [d for d in coff.parse_symbols(member,c.coff_name)[1] if d['symbol']=='__except_list' and d['section']!=0]
                != [absolute['definition']] or absolute['definition']['section'] != -1 or absolute['definition']['offset']):
        raise ValueError('Count assignment absolute FS field lacks original source definition')
    shared['__except_list'] = 0
    opaque = m['opaque_api']
    if opaque['record'] not in rows('authored-origin-evidence.csv'):
        raise ValueError('Count assignment compatible opaque receiver loses independent whole game proof')
    shared[opaque['symbol']] = int(opaque['address'],16)
    scratch = ROOT/'build/origin-vector-count-assignment-verification'; scratch.mkdir(parents=True,exist_ok=True)
    control = m['public_control']
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj = Path(temp)/'CountAssignment.obj'
        result = subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/control['probe']),str(obj),*control['profile']],
            cwd=ROOT,capture_output=True,text=True)
        if result.returncode or headers(result.stdout+result.stderr) != control['headers']:
            raise ValueError('Count assignment cold source/includes differ')
        verify_control(m,obj.read_bytes(),target,c,coff,flow,shared)


def main():
    parser = argparse.ArgumentParser(description=__doc__); parser.add_argument('--evidence-only',action='store_true')
    args = parser.parse_args(); m = json.loads((ROOT/EVIDENCE).read_text()); verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes()) != MANIFEST_SHA256: raise ValueError('Count assignment immutable manifest differs')
    replay(m,args.evidence_only)
    print('R223: five complete original vector count-assignment/public/end origins414; full scoped source and ordinary normal/EH/data graphs; complete independent game receivers; private lifetime controls remain unknown; no source/ABI/exact credit.')


if __name__ == '__main__': main()
