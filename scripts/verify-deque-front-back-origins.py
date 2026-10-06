#!/usr/bin/env python3
"""Cold-replay complete original deque front/back access and ordinary graphs."""
import argparse
import csv
import json
from pathlib import Path
import struct
import subprocess
import tempfile
import importlib.util

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('ends_source', ROOT/'scripts/verify-vector-insertion-carrier-origins.py')
SOURCE = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(SOURCE)
module = SOURCE.module
digest = SOURCE.digest
EVIDENCE = 'config/deque-front-back-origin-evidence.json'
MANIFEST_SHA256 = '1ac140821d2f2aec5d30ceab655de636f28eff6aa6215d1b8d49b6ffa0764e10'
PLAN_DIGESTS = {'groups': 'f9365ef38568056d0ef99909ca5ea786715764175dcff300235f8f59d841bebc', 'sections': '983be8c37c5f61678218ded5a0641c0615512cbd2fbeee90ea46bbf3f24d97b8', 'weak_references': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'evidence_id': 'e0c70158edcafe96017dd523b863e007ffbab010ec4c22f29871f2b3ec218bcb', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'functions': '4d4330602ed9288ebd88594ecb3c4ccf194a1d14234ca0ac8fdc2a6ca5121fd0', 'parents': '8df23e9345dfd2926fb6e5a267ee879b9fdb528691888b5bd564ffe6dedc5375', 'boundaries': '626666834ae6c5214beafaddf9f30a099250ecbf6e911d9d6560b237cb840870', 'historical_snapshots': 'cc753e4af87dafd1d97ad332684a32bb9697510fa5c33d2216d40ce69b94b782', 'retained_unknowns': '744489724104925dcd102df26213c9cf382272e28b1621e7153750b4c42ef16b', 'negative_controls': '106f289183a9a6a0d36b9dc923229534ed790121145bad41b5ac21d60d295d28', 'header_definitions': '7bd396b53546311aa0a18872a3dccc14c759c0307872e9a36b8955135eb05ea0', 'canonical': '91f631169c1ca502a766bb17e2a3f244978959ca834d9eefd218c68789a0017c', 'public_control': '532ec307621874e040382da4bebc931a0ed2e3eb90e9cdb8df3f81c75b3a5853', 'retained_sha256': 'fe056fb6b35ada45d5a2c40b78e61876213a278fc157593933b43c66118eb38b', 'interpretation': '65a5c8f16b1fb9a69cdea16763cff66b6d17b4e756a4d3dafcc506c1485fee38'}
CONFIDENCE = 'complete-original-deque-front-back-scoped-source-and-independent-game-receivers'
WHOLE = {'0x004094D0':32,'0x004094F0':45,'0x0041DB80':45,'0x0041DE00':45,
         '0x004213B0':45,'0x005F8180':45,'0x004099E0':35,'0x00409A10':41,'0x0040A170':32}


def rows(name):
    with (ROOT/'config'/name).open() as source:
        return list(csv.DictReader(source))


def headers(log):
    found = {}
    for line in log.splitlines():
        if 'Note: including file:' not in line: continue
        value = line.split('Note: including file:',1)[1].strip().replace('\\','/')
        if value[:3].lower() != 'z:/': raise ValueError('Deque front/back loses original host include mapping')
        path = Path(value[2:]); relative = str(path.relative_to(ROOT))
        if not relative.startswith('.tools/msvc710/Vc7/include/'):
            raise ValueError('Deque front/back imports unrelated source')
        found[relative] = digest(path.read_bytes())
    return found


def verify_plan(m):
    for key,sha in PLAN_DIGESTS.items():
        if SOURCE.BASE.metadata_digest(m[key]) != sha:
            raise ValueError('Deque front/back complete evidence differs: '+key)
    if m['evidence_id'] != 'R226' or {r['address']:r['size'] for r in m['functions']} != WHOLE:
        raise ValueError('Deque front/back loses bounded complete roots and public owners')
    for r in m['functions']:
        f,o,af,ao = [r[k] for k in ['original_function','original_origin','accepted_function','accepted_origin']]
        if (o['origin'] != 'unknown' or af['owner'] != 'library' or af['status'] != 'excluded'
                or any(af[k] != f[k] for k in ['address','size','span_end','current_name'])
                or any(af[k] for k in ['source_file','signature','calling_convention'])
                or af['match_percent'] != '0.00' or ao != dict(address=r['address'],origin='library',
                    subsystem='VC71STL',disposition='exclude',confidence=CONFIDENCE,evidence_id='R226')):
            raise ValueError('Deque front/back grants unsupported extent/ABI/source/exact ownership')
    for q in m['retained_unknowns']:
        if q['origin']['origin'] != 'unknown' or q['function']['owner'] or q['function']['status'] != 'unclassified':
            raise ValueError('Deque front/back infers original private lifetime ownership')


def verify_native(m,target,c,flow):
    authored = module('ends_native_cfg','verify-authored-origins.py')
    owners = m['functions']+m['parents']
    for r in owners:
        a = int(r['address'],16); raw = c.pe_bytes_at(target,a,r['size'])
        if (digest(raw) != r['body_sha256'] or SOURCE.instructions(raw,a,flow) != r['instructions']
                or list(authored.verify_body(raw,a,r.get('switches',[]),lambda x,n:c.pe_bytes_at(target,x,n),
                    r.get('direct_switches',[]))) != r['cfg']):
            raise ValueError('Deque front/back complete native owner/CFG differs')
        if 'record' in r:
            if (r['record'] not in rows('authored-origin-evidence.csv')
                    or r['origin']['origin'] != 'authored'
                    or r['record']['body_sha256'] != digest(raw)
                    or [q for q in rows('authored-origin-switches.csv') if q['address']==r['address']] != r.get('switches',[])
                    or [q for q in rows('authored-origin-direct-switches.csv') if q['address']==r['address']] != r.get('direct_switches',[])):
                raise ValueError('Deque front/back loses independently accepted complete game context')
        for window in r.get('call_sequences',[]):
            sequence = window['instructions']; ins = r['instructions']
            offset = sequence[0]['offset']; start = next(i for i,q in enumerate(ins) if q['offset']==offset)
            if ins[start:start+len(sequence)] != sequence or not any(
                    q['mnemonic']=='call' and q['operands']==hex(int(window['target'],16))
                    and a+q['offset']==int(window['site'],16) for q in sequence):
                raise ValueError('Deque front/back loses actual complete game argument/receiver window')
    for r in m['boundaries']:
        raw = c.pe_bytes_at(target,int(r['address'],16),r['size'])
        if raw.hex() != r['hex'] or digest(raw) != r['sha256'] or raw != b'\xcc'*r['size']:
            raise ValueError('Deque front/back folds external alignment into the source owner')


def verify_control(m,body,target,c,coff,flow,shared):
    extra = module('ends_sections','sdk_x3d_carriers.py')
    pe = module('ends_permissions','verify-sdk-x3d-origins.py')
    inventory = module('ends_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    control = m['public_control']
    if inventory(body,c,coff) != control['emission']: raise ValueError('Deque front/back omits complete cold ordinary emission')
    raw,_ = coff.readonly_section(body,control['layout']['section'],c.coff_name)
    if list(struct.unpack('<10I',raw)) != control['layout_values']:
        raise ValueError('Deque front/back crops complete merged readonly carrier')
    if [SOURCE.weak_record(body,r['symbol'],c,coff) for r in m['weak_references']] != m['weak_references']:
        raise ValueError('Deque front/back replaces actual weak AUX/fallback definition')
    decoded = {}
    for r in m['sections']:
        raw,fields,source = extra.section_carrier(body,r['source']['section'],c,coff)
        a = int(r['base'],16)
        if (SOURCE.BASE.canonical_source(source,body) != r['source'] or fields != r['fields']
                or len(raw) != r['size'] or digest(raw) != r['source_sha256']
                or pe.image_permissions(target,a,len(raw)) != source['flags'] & 0xe0000000):
            raise ValueError('Deque front/back loses full defining COFF/AUX/lines/fields/permissions')
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
                raise ValueError('Deque front/back entire unmasked source/native body differs')
            if r['kind']=='code':
                roots = {0}; roots.update(d['offset'] for d in r['source']['definitions'] if d['type']==32 and d['storage']==3)
                roots.update(f['symbol_offset']+f['addend'] for q in scoped for f in q['fields']
                    if f['symbol_section']==r['source']['section'] and f['symbol_storage']==6)
                if sorted(roots) != r['roots'] or flow.flow(native,a,r['roots'],fields,calls,data,None,None,None) != r['flow']:
                    raise ValueError('Deque front/back normal/EH/unwind/shared-exit graph differs')
    for q in m['negative_controls']:
        raw,fields,source = extra.section_carrier(body,q['source']['section'],c,coff)
        if (SOURCE.BASE.canonical_source(source,body) != q['source'] or fields != q['fields']
                or digest(raw) != q['source_sha256'] or SOURCE.instructions(raw,0,flow) != q['instructions']):
            raise ValueError('Deque front/back changes whole const/wrong-stride controls')
        scoped = [r for r in m['sections'] if r['group']==q['group']]
        catalog = SOURCE.owned_catalog(scoped,{},q['group'],[])
        if q['kind']=='const-route':
            if not any(f['symbol'] not in catalog for f in fields):
                raise ValueError('Deque front/back incorrectly merges const and mutable owners')
        elif q['kind']=='predecrement-route':
            if q['size']==q['native_size'] or not any(f['symbol'] not in catalog for f in fields):
                raise ValueError('Deque front/back incorrectly merges predecrement and subtract-one source policies')
        elif q['kind']=='wrong-width':
            a = int(q['native'],16); native = c.pe_bytes_at(target,a,q['native_size'])
            if fields or raw==native or len(raw)!=q['size'] or digest(native)!=q['native_sha256']:
                raise ValueError('Deque front/back incorrectly merges distinct whole stride/block policies')
        else: raise ValueError('Deque front/back unsupported negative control')


def replay(m,evidence_only=False):
    c = module('ends_target','compare-coff-function.py'); coff = module('ends_coff','coff_data.py')
    flow = module('ends_flow','sdk_image_carriers.py'); target = c.verified_target()
    if digest(target) != m['target_sha256']: raise ValueError('Deque front/back target identity differs')
    for path,sha in m['retained_sha256'].items():
        if digest((ROOT/path).read_bytes()) != sha: raise ValueError('Deque front/back changes retained evidence/source: '+path)
    for q in m['header_definitions']:
        if ((ROOT/q['path']).read_text().splitlines()[q['start']-1:q['end']] != q['lines']
                or q['path'] not in m['public_control']['headers']):
            raise ValueError('Deque front/back loses original public SDK definitions')
    fs = {r['address']:r for r in rows('functions.csv')}; origins = {r['address']:r for r in rows('function-origins.csv')}
    selected = {r['address']:r for r in m['functions']}; state = 'original' if evidence_only else 'accepted'
    for q in m['canonical']:
        key = q['function']['address']; expected = q
        if key in selected: expected = dict(function=selected[key][state+'_function'],origin=selected[key][state+'_origin'])
        if dict(function=fs[key],origin=origins[key]) != expected:
            raise ValueError('Deque front/back bounded canonical state differs: '+key)
    for q in m['historical_snapshots']:
        old = json.loads((ROOT/q['path']).read_text())
        for part in q['trail']: old = old[part]
        original = selected[old['function']['address']]['original_function']
        if (old != q['record'] or old['origin'] != selected[old['function']['address']]['original_origin']
                or any(old['function'][key] != original[key] for key in original if key not in ['evidence','notes'])):
            raise ValueError('Deque front/back rewrites historical unknown evidence')
    verify_native(m,target,c,flow)
    shared = {}
    scratch = ROOT/'build/origin-deque-front-back-verification'; scratch.mkdir(parents=True,exist_ok=True)
    control = m['public_control']
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj = Path(temp)/'DequeFrontBack.obj'
        result = subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/control['probe']),str(obj),*control['profile']],
            cwd=ROOT,capture_output=True,text=True)
        if result.returncode or headers(result.stdout+result.stderr) != control['headers']:
            raise ValueError('Deque front/back cold source/includes differ')
        verify_control(m,obj.read_bytes(),target,c,coff,flow,shared)


def main():
    parser = argparse.ArgumentParser(description=__doc__); parser.add_argument('--evidence-only',action='store_true')
    args = parser.parse_args(); m = json.loads((ROOT/EVIDENCE).read_text()); verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes()) != MANIFEST_SHA256: raise ValueError('Deque front/back immutable manifest differs')
    replay(m,args.evidence_only)
    print('R226: nine complete deque front/back/begin/end/iterator origins365; full scoped original and manual source graphs, actual stride/block/const/predecrement controls and whole game receivers; no source/ABI/exact credit.')


if __name__ == '__main__': main()
