#!/usr/bin/env python3
"""Cold-replay complete original vector/deque unchecked-indexing and ordinary graphs."""
import argparse
import csv
import json
from pathlib import Path
import struct
import subprocess
import tempfile
import importlib.util

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('index_source', ROOT/'scripts/verify-vector-insertion-carrier-origins.py')
SOURCE = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(SOURCE)
module = SOURCE.module
digest = SOURCE.digest
EVIDENCE = 'config/unchecked-indexing-origin-evidence.json'
MANIFEST_SHA256 = '9ff22d92b72073bc8ab0d1a62b127ebc6ba1adc6507e2b14f11cadbd2d544113'
PLAN_DIGESTS = {'groups': '33fa5653823f864714f6ecba24359ae5d8344d8718c321948436529708778394', 'sections': '4ecbf47667ab39a377916cbce50a388bb17de05777677cc2b587dbd924382293', 'weak_references': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'evidence_id': 'ebacb8b263f6a7a0f4a34c6046eea444b9c4ebbd4d4fee9b1276473760a112d2', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'functions': '0e2465b5e5d13b513fa5e4b82428250d6d3f4f04a9bf236f8cc983f18ae1cde1', 'parents': 'c6feffd4fb93177c677c2a55939c3908c364f252a270b3045d9a12904b512e82', 'boundaries': '58b7fd16330f5a32b7e8b23203c1f9c3276005fda2c7f6d49aa69cf388d20a81', 'historical_snapshots': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'retained_unknowns': '5160e1c300174957179233f328f1ad44d37b287a1055e372b770cd24c473cd91', 'negative_controls': '72f6cdb7783879f2d19d82cd2f597e980d7024b3fad651f045dbdd0314c711b9', 'header_definitions': '70b95835c374d56772bf2468d4a095bb1f94931ba9379b58fe468e5974349d40', 'canonical': '6a442e4b9ba145d44bd4b885526da4e90bf80ef5485fd00297b82041fe46c5ab', 'public_control': '0c29ccaa4ab046977bfdea6f00a4b9e5ecb5ec7adbca19fa2c10088d16c2e6f5', 'retained_sha256': '59ccd4c45df6687c98076c37d8e0e9a37c37a899cbeeb9c5d05dbe35441d5467', 'interpretation': '5adcc7b11ed82bde1bb1145f3e19dd81b0858f3a83339ebfb7d9a204ae71b62b'}
CONFIDENCE = 'complete-original-unchecked-indexing-scoped-source-and-independent-game-receivers'
WHOLE = {a:49 for a in ['0x00409430','0x0041DB40','0x0041DDC0','0x0042DAF0',
                            '0x0042DBA0','0x00458AF0','0x00458BC0','0x005F7FC0']}
WHOLE.update({'0x0042DCC0':35,'0x0042E080':19,'0x0042E2F0':32,'0x0042E330':83})


def rows(name):
    with (ROOT/'config'/name).open() as source:
        return list(csv.DictReader(source))


def headers(log):
    found = {}
    for line in log.splitlines():
        if 'Note: including file:' not in line: continue
        value = line.split('Note: including file:',1)[1].strip().replace('\\','/')
        if value[:3].lower() != 'z:/': raise ValueError('Unchecked indexing loses original host include mapping')
        path = Path(value[2:]); relative = str(path.relative_to(ROOT))
        if not relative.startswith('.tools/msvc710/Vc7/include/'):
            raise ValueError('Unchecked indexing imports unrelated source')
        found[relative] = digest(path.read_bytes())
    return found


def verify_plan(m):
    for key,sha in PLAN_DIGESTS.items():
        if SOURCE.BASE.metadata_digest(m[key]) != sha:
            raise ValueError('Unchecked indexing complete evidence differs: '+key)
    if m['evidence_id'] != 'R225' or {r['address']:r['size'] for r in m['functions']} != WHOLE:
        raise ValueError('Unchecked indexing loses bounded complete roots and public owners')
    for r in m['functions']:
        f,o,af,ao = [r[k] for k in ['original_function','original_origin','accepted_function','accepted_origin']]
        if (o['origin'] != 'unknown' or af['owner'] != 'library' or af['status'] != 'excluded'
                or any(af[k] != f[k] for k in ['address','size','span_end','current_name'])
                or any(af[k] for k in ['source_file','signature','calling_convention'])
                or af['match_percent'] != '0.00' or ao != dict(address=r['address'],origin='library',
                    subsystem='VC71STL',disposition='exclude',confidence=CONFIDENCE,evidence_id='R225')):
            raise ValueError('Unchecked indexing grants unsupported extent/ABI/source/exact ownership')
    for q in m['retained_unknowns']:
        if q['origin']['origin'] != 'unknown' or q['function']['owner'] or q['function']['status'] != 'unclassified':
            raise ValueError('Unchecked indexing infers original private lifetime ownership')


def verify_native(m,target,c,flow):
    authored = module('index_native_cfg','verify-authored-origins.py')
    owners = m['functions']+m['parents']
    for r in owners:
        a = int(r['address'],16); raw = c.pe_bytes_at(target,a,r['size'])
        if (digest(raw) != r['body_sha256'] or SOURCE.instructions(raw,a,flow) != r['instructions']
                or list(authored.verify_body(raw,a,r.get('switches',[]),lambda x,n:c.pe_bytes_at(target,x,n),
                    r.get('direct_switches',[]))) != r['cfg']):
            raise ValueError('Unchecked indexing complete native owner/CFG differs')
        if 'record' in r:
            if (r['record'] not in rows('authored-origin-evidence.csv')
                    or r['origin']['origin'] != 'authored'
                    or r['record']['body_sha256'] != digest(raw)
                    or [q for q in rows('authored-origin-switches.csv') if q['address']==r['address']] != r.get('switches',[])
                    or [q for q in rows('authored-origin-direct-switches.csv') if q['address']==r['address']] != r.get('direct_switches',[])):
                raise ValueError('Unchecked indexing loses independently accepted complete game context')
        for window in r.get('call_sequences',[]):
            sequence = window['instructions']; ins = r['instructions']
            offset = sequence[0]['offset']; start = next(i for i,q in enumerate(ins) if q['offset']==offset)
            if ins[start:start+len(sequence)] != sequence or not any(
                    q['mnemonic']=='call' and q['operands']==hex(int(window['target'],16))
                    and a+q['offset']==int(window['site'],16) for q in sequence):
                raise ValueError('Unchecked indexing loses actual complete game argument/receiver window')
    for r in m['boundaries']:
        raw = c.pe_bytes_at(target,int(r['address'],16),r['size'])
        if raw.hex() != r['hex'] or digest(raw) != r['sha256'] or raw != b'\xcc'*r['size']:
            raise ValueError('Unchecked indexing folds external alignment into the source owner')


def verify_control(m,body,target,c,coff,flow,shared):
    extra = module('index_sections','sdk_x3d_carriers.py')
    pe = module('index_permissions','verify-sdk-x3d-origins.py')
    inventory = module('index_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    control = m['public_control']
    if inventory(body,c,coff) != control['emission']: raise ValueError('Unchecked indexing omits complete cold ordinary emission')
    raw,_ = coff.readonly_section(body,control['layout']['section'],c.coff_name)
    if list(struct.unpack('<12I',raw)) != control['layout_values']:
        raise ValueError('Unchecked indexing crops complete merged readonly carrier')
    if [SOURCE.weak_record(body,r['symbol'],c,coff) for r in m['weak_references']] != m['weak_references']:
        raise ValueError('Unchecked indexing replaces actual weak AUX/fallback definition')
    decoded = {}
    for r in m['sections']:
        raw,fields,source = extra.section_carrier(body,r['source']['section'],c,coff)
        a = int(r['base'],16)
        if (SOURCE.BASE.canonical_source(source,body) != r['source'] or fields != r['fields']
                or len(raw) != r['size'] or digest(raw) != r['source_sha256']
                or pe.image_permissions(target,a,len(raw)) != source['flags'] & 0xe0000000):
            raise ValueError('Unchecked indexing loses full defining COFF/AUX/lines/fields/permissions')
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
                raise ValueError('Unchecked indexing entire unmasked source/native body differs')
            if r['kind']=='code':
                roots = {0}; roots.update(d['offset'] for d in r['source']['definitions'] if d['type']==32 and d['storage']==3)
                roots.update(f['symbol_offset']+f['addend'] for q in scoped for f in q['fields']
                    if f['symbol_section']==r['source']['section'] and f['symbol_storage']==6)
                if sorted(roots) != r['roots'] or flow.flow(native,a,r['roots'],fields,calls,data,None,None,None) != r['flow']:
                    raise ValueError('Unchecked indexing normal/EH/unwind/shared-exit graph differs')
    for q in m['negative_controls']:
        raw,fields,source = extra.section_carrier(body,q['source']['section'],c,coff)
        if (SOURCE.BASE.canonical_source(source,body) != q['source'] or fields != q['fields']
                or digest(raw) != q['source_sha256'] or SOURCE.instructions(raw,0,flow) != q['instructions']):
            raise ValueError('Unchecked indexing changes whole const/wrong-stride controls')
        scoped = [r for r in m['sections'] if r['group']==q['group']]
        catalog = SOURCE.owned_catalog(scoped,{},q['group'],[])
        if q['kind']=='const-route':
            if not any(f['symbol'] not in catalog for f in fields):
                raise ValueError('Unchecked indexing incorrectly merges const and mutable owners')
        elif q['kind']=='wrong-width':
            a = int(q['native'],16); native = c.pe_bytes_at(target,a,q['native_size'])
            if fields or raw==native or len(raw)!=q['size'] or digest(native)!=q['native_sha256']:
                raise ValueError('Unchecked indexing incorrectly merges distinct whole stride/block policies')
        else: raise ValueError('Unchecked indexing unsupported negative control')


def replay(m,evidence_only=False):
    c = module('index_target','compare-coff-function.py'); coff = module('index_coff','coff_data.py')
    flow = module('index_flow','sdk_image_carriers.py'); target = c.verified_target()
    if digest(target) != m['target_sha256']: raise ValueError('Unchecked indexing target identity differs')
    for path,sha in m['retained_sha256'].items():
        if digest((ROOT/path).read_bytes()) != sha: raise ValueError('Unchecked indexing changes retained evidence/source: '+path)
    for q in m['header_definitions']:
        if ((ROOT/q['path']).read_text().splitlines()[q['start']-1:q['end']] != q['lines']
                or q['path'] not in m['public_control']['headers']):
            raise ValueError('Unchecked indexing loses original public SDK definitions')
    fs = {r['address']:r for r in rows('functions.csv')}; origins = {r['address']:r for r in rows('function-origins.csv')}
    selected = {r['address']:r for r in m['functions']}; state = 'original' if evidence_only else 'accepted'
    for q in m['canonical']:
        key = q['function']['address']; expected = q
        if key in selected: expected = dict(function=selected[key][state+'_function'],origin=selected[key][state+'_origin'])
        if dict(function=fs[key],origin=origins[key]) != expected:
            raise ValueError('Unchecked indexing bounded canonical state differs: '+key)
    for q in m['historical_snapshots']:
        old = json.loads((ROOT/q['path']).read_text())
        for part in q['trail']: old = old[part]
        original = selected[old['function']['address']]['original_function']
        if (old != q['record'] or old['origin'] != selected[old['function']['address']]['original_origin']
                or any(old['function'][key] != original[key] for key in original if key not in ['evidence','notes'])):
            raise ValueError('Unchecked indexing rewrites historical unknown evidence')
    verify_native(m,target,c,flow)
    shared = {}
    scratch = ROOT/'build/origin-unchecked-indexing-verification'; scratch.mkdir(parents=True,exist_ok=True)
    control = m['public_control']
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj = Path(temp)/'UncheckedIndexing.obj'
        result = subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/control['probe']),str(obj),*control['profile']],
            cwd=ROOT,capture_output=True,text=True)
        if result.returncode or headers(result.stdout+result.stderr) != control['headers']:
            raise ValueError('Unchecked indexing cold source/includes differ')
        verify_control(m,obj.read_bytes(),target,c,coff,flow,shared)


def main():
    parser = argparse.ArgumentParser(description=__doc__); parser.add_argument('--evidence-only',action='store_true')
    args = parser.parse_args(); m = json.loads((ROOT/EVIDENCE).read_text()); verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes()) != MANIFEST_SHA256: raise ValueError('Unchecked indexing immutable manifest differs')
    replay(m,args.evidence_only)
    print('R225: twelve complete vector/deque unchecked-indexing origins561; full scoped original and manual source graphs, actual stride/block/const controls and complete game receivers; no source/ABI/exact credit.')


if __name__ == '__main__': main()
