#!/usr/bin/env python3
"""Cold-replay complete original vector endpoints and strict historical current-state graphs."""
import argparse
import csv
import json
from pathlib import Path
import struct
import subprocess
import tempfile
import importlib.util
import copy
import contextlib
import io
from types import SimpleNamespace

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location('endpoint_source', ROOT/'scripts/verify-vector-insertion-carrier-origins.py')
SOURCE = importlib.util.module_from_spec(SPEC); SPEC.loader.exec_module(SOURCE)
module = SOURCE.module
digest = SOURCE.digest
EVIDENCE = 'config/vector-endpoint-route-origin-evidence.json'
MANIFEST_SHA256 = 'f60a3fdfad9c7cf1ffddfe902114059102b9c26d06e4f5c63709a8346af313ec'
PLAN_DIGESTS = {'groups': '4810b5868163f495e08a490f37c4f3adae371aa009f70969512d7461cc99e4cb', 'sections': '9057c7f944ec1d64bd76c0f703034b613a7da7ef50efe2051cfb06a7e4784dbb', 'weak_references': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'evidence_id': '87934cdf62cbdd5ace89a5a2798fc0bf7d9ee5ce97e34dcc2b30f0b7e19c298b', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'functions': 'c16345ee4cf39569bb8fde7f58a11deffc10b94e7f8b0e5be4115407fc60c090', 'parents': '755a544bba8ad829f2f48f7f6820039a6f8680617714bcdac4cdf966babbd912', 'boundaries': '4057cd4f61b22c33874682a6378a1572f2e3c4e52bf760787f69147536485fa5', 'historical_snapshots': 'b46b63d165ec56dba21210f8c0369dfcdb252ff9a4fb155d1b3693acb11b1a29', 'retained_unknowns': '2c16084b1609c104bf37b81424803d15d27f573480e4b0926176f32d412afeee', 'negative_controls': 'e1859f38dacf72d39f69b97eb402ef7d2a47b36d577890eb5129a6e438b6409c', 'header_definitions': '1e0948ec87495db605a53e942aa3252d853d57cf789dc8013a28bf8928b1640e', 'retained_replays': '48c4091804f0b19f0c9d378b4ec61c57a9b057dd52ac53c5c121bd9589d6caf8', 'canonical': 'cb98a2222d698d7b28c72d5d5f794f3dededdb2fd5e62883a98adf5ae84537f5', 'public_control': '7f365636e24b8bc6617a78464d8bea6af81c2222ff19445ec3ca773b236b782d', 'retained_sha256': '9d55bdddf190cb5b61219249c0b258b900d9a195c3af216023c2b2d7c8564575', 'interpretation': '56cf1142b1e87fdbff581a7078a93a75329c8e28d9ab3821819c0ed5172c5886'}
CONFIDENCE = 'complete-original-vector-endpoint-source-and-retained-assignment-copy-receivers'
WHOLE = {'0x00459890':31,'0x00459A50':31,'0x00459C40':31,'0x00459C60':31}


def rows(name):
    with (ROOT/'config'/name).open() as source:
        return list(csv.DictReader(source))


def headers(log):
    found = {}
    for line in log.splitlines():
        if 'Note: including file:' not in line: continue
        value = line.split('Note: including file:',1)[1].strip().replace('\\','/')
        if value[:3].lower() != 'z:/': raise ValueError('Vector endpoint loses original host include mapping')
        path = Path(value[2:]); relative = str(path.relative_to(ROOT))
        if not relative.startswith('.tools/msvc710/Vc7/include/'):
            raise ValueError('Vector endpoint imports unrelated source')
        found[relative] = digest(path.read_bytes())
    return found


def verify_plan(m):
    for key,sha in PLAN_DIGESTS.items():
        if SOURCE.BASE.metadata_digest(m[key]) != sha:
            raise ValueError('Vector endpoint complete evidence differs: '+key)
    if m['evidence_id'] != 'R227' or {r['address']:r['size'] for r in m['functions']} != WHOLE:
        raise ValueError('Vector endpoint loses bounded complete roots and public owners')
    if (len(m['groups']) != 8 or len(m['sections']) != 20
            or sum(r['size'] for r in m['sections']) != 552
            or sum(len(r['fields']) for r in m['sections']) != 12
            or len(m['parents']) != 3 or sum(r['size'] for r in m['parents']) != 499
            or len(m['historical_snapshots']) != 15 or len(m['retained_unknowns']) != 15
            or len(m['negative_controls']) != 8 or set(m['retained_replays']) != {'R209', 'R210', 'R211'}):
        raise ValueError('Vector endpoint omits complete source/receiver/history coverage')
    for r in m['functions']:
        f,o,af,ao = [r[k] for k in ['original_function','original_origin','accepted_function','accepted_origin']]
        if (o['origin'] != 'unknown' or af['owner'] != 'library' or af['status'] != 'excluded'
                or any(af[k] != f[k] for k in ['address','size','span_end','current_name'])
                or any(af[k] for k in ['source_file','signature','calling_convention'])
                or af['match_percent'] != '0.00' or ao != dict(address=r['address'],origin='library',
                    subsystem='VC71STL',disposition='exclude',confidence=CONFIDENCE,evidence_id='R227')):
            raise ValueError('Vector endpoint grants unsupported extent/ABI/source/exact ownership')
    for q in m['retained_unknowns']:
        if q['origin']['origin'] != 'unknown' or q['function']['owner'] or q['function']['status'] != 'unclassified':
            raise ValueError('Vector endpoint infers original private lifetime ownership')


def verify_native(m,target,c,flow):
    authored = module('ends_native_cfg','verify-authored-origins.py')
    owners = m['functions']+m['parents']
    for r in owners:
        a = int(r['address'],16); raw = c.pe_bytes_at(target,a,r['size'])
        if (digest(raw) != r['body_sha256'] or SOURCE.instructions(raw,a,flow) != r['instructions']
                or list(authored.verify_body(raw,a,r.get('switches',[]),lambda x,n:c.pe_bytes_at(target,x,n),
                    r.get('direct_switches',[]))) != r['cfg']):
            raise ValueError('Vector endpoint complete native owner/CFG differs')
        if 'record' in r:
            if (r['record'] not in rows('authored-origin-evidence.csv')
                    or r['origin']['origin'] != 'authored'
                    or r['record']['body_sha256'] != digest(raw)
                    or [q for q in rows('authored-origin-switches.csv') if q['address']==r['address']] != r.get('switches',[])
                    or [q for q in rows('authored-origin-direct-switches.csv') if q['address']==r['address']] != r.get('direct_switches',[])):
                raise ValueError('Vector endpoint loses independently accepted complete game context')
        for window in r.get('call_sequences',[]):
            sequence = window['instructions']; ins = r['instructions']
            offset = sequence[0]['offset']; start = next(i for i,q in enumerate(ins) if q['offset']==offset)
            if ins[start:start+len(sequence)] != sequence or not any(
                    q['mnemonic']=='call' and q['operands']==hex(int(window['target'],16))
                    and a+q['offset']==int(window['site'],16) for q in sequence):
                raise ValueError('Vector endpoint loses actual complete game argument/receiver window')
    for r in m['boundaries']:
        raw = c.pe_bytes_at(target,int(r['address'],16),r['size'])
        if raw.hex() != r['hex'] or digest(raw) != r['sha256'] or raw != b'\xcc'*r['size']:
            raise ValueError('Vector endpoint folds external alignment into the source owner')


def verify_control(m,body,target,c,coff,flow,shared):
    extra = module('ends_sections','sdk_x3d_carriers.py')
    pe = module('ends_permissions','verify-sdk-x3d-origins.py')
    inventory = module('ends_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    control = m['public_control']
    if inventory(body,c,coff) != control['emission']: raise ValueError('Vector endpoint omits complete cold ordinary emission')
    raw,_ = coff.readonly_section(body,control['layout']['section'],c.coff_name)
    if list(struct.unpack('<9I',raw)) != control['layout_values']:
        raise ValueError('Vector endpoint crops complete merged readonly carrier')
    if [SOURCE.weak_record(body,r['symbol'],c,coff) for r in m['weak_references']] != m['weak_references']:
        raise ValueError('Vector endpoint replaces actual weak AUX/fallback definition')
    decoded = {}
    for r in m['sections']:
        raw,fields,source = extra.section_carrier(body,r['source']['section'],c,coff)
        a = int(r['base'],16)
        if (SOURCE.BASE.canonical_source(source,body) != r['source'] or fields != r['fields']
                or len(raw) != r['size'] or digest(raw) != r['source_sha256']
                or pe.image_permissions(target,a,len(raw)) != source['flags'] & 0xe0000000):
            raise ValueError('Vector endpoint loses full defining COFF/AUX/lines/fields/permissions')
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
                raise ValueError('Vector endpoint entire unmasked source/native body differs')
            if r['kind']=='code':
                roots = {0}; roots.update(d['offset'] for d in r['source']['definitions'] if d['type']==32 and d['storage']==3)
                roots.update(f['symbol_offset']+f['addend'] for q in scoped for f in q['fields']
                    if f['symbol_section']==r['source']['section'] and f['symbol_storage']==6)
                if sorted(roots) != r['roots'] or flow.flow(native,a,r['roots'],fields,calls,data,None,None,None) != r['flow']:
                    raise ValueError('Vector endpoint normal/EH/unwind/shared-exit graph differs')
    for q in m['negative_controls']:
        raw,fields,source = extra.section_carrier(body,q['source']['section'],c,coff)
        if (SOURCE.BASE.canonical_source(source,body) != q['source'] or fields != q['fields']
                or digest(raw) != q['source_sha256'] or SOURCE.instructions(raw,0,flow) != q['instructions']):
            raise ValueError('Vector endpoint changes whole const/wrong-stride controls')
        scoped = [r for r in m['sections'] if r['group']==q['group']]
        catalog = SOURCE.owned_catalog(scoped,{},q['group'],[])
        if q['kind'] in ['wrong-endpoint-field','wrong-const-route']:
            a = int(q['native'],16)
            linked,_,_ = SOURCE.BASE.BASE.bind_fields(raw,fields,q['bindings'],catalog,q['group'],a)
            native = c.pe_bytes_at(target,a,q['native_size'])
            if len(raw)!=q['native_size'] or linked==native or digest(native)!=q['native_sha256']:
                raise ValueError('Vector endpoint merges whole first/last or constructor routes')
        elif q['kind']=='mutable-route':
            if not any(f['symbol'] not in catalog for f in fields):
                raise ValueError('Vector endpoint merges const and mutable defining constructors')
        else: raise ValueError('Vector endpoint unsupported whole negative control')



def occurrences(value, trail=()):
    """Locate canonical pairs without treating field destinations as owners."""
    if isinstance(value, dict):
        if isinstance(value.get('function'), dict) and isinstance(value.get('origin'), dict):
            yield trail, value
        for key, child in value.items():
            yield from occurrences(child, trail + (key,))
    elif isinstance(value, list):
        for index, child in enumerate(value):
            yield from occurrences(child, trail + (index,))


def project_retained(m, key, original, evidence_only=False):
    """Project only checked canonical expectations; all old source evidence stays literal."""
    verify_plan(m)
    descriptor = m['retained_replays'][key]
    if SOURCE.BASE.metadata_digest(original) != descriptor['plan_sha256']:
        raise ValueError('Vector endpoint changes the immutable retained source plan')
    selected = {r['address']: r for r in m['functions']}
    snapshots = [q for q in m['historical_snapshots'] if q['path'] == descriptor['path']]
    found = {trail: row for trail, row in occurrences(original)
             if row['function'].get('address') in selected}
    if set(found) != {tuple(q['trail']) for q in snapshots}:
        raise ValueError('Vector endpoint omits a retained canonical expectation')
    for q in snapshots:
        old = found[tuple(q['trail'])]
        row = selected[old['function']['address']]
        if (old != q['record'] or old['function'] != row['original_function']
                or old['origin'] != row['original_origin']):
            raise ValueError('Vector endpoint rewrites a literal old unknown snapshot')
    projected = copy.deepcopy(original)
    state = 'original' if evidence_only else 'accepted'
    for q in snapshots:
        entry = projected
        for part in q['trail']:
            entry = entry[part]
        row = selected[entry['function']['address']]
        entry['function'] = copy.deepcopy(row[state + '_function'])
        entry['origin'] = copy.deepcopy(row[state + '_origin'])
    return projected


def replay_retained(m, key, evidence_only=False):
    """Cold-replay pinned old verifiers with bounded current canonical expectations."""
    verify_plan(m)
    state = 'original' if evidence_only else 'accepted'
    fs = {r['address']: r for r in rows('functions.csv')}
    origins = {r['address']: r for r in rows('function-origins.csv')}
    for row in m['functions']:
        a = row['address']
        if fs[a] != row[state + '_function'] or origins[a] != row[state + '_origin']:
            raise ValueError('Vector endpoint retained replay loses checked successor state')
    descriptor = m['retained_replays'][key]
    for path, sha in [(descriptor['script'], descriptor['script_sha256']),
                      (descriptor['path'], descriptor['manifest_sha256'])]:
        if digest((ROOT/path).read_bytes()) != sha:
            raise ValueError('Vector endpoint retained verifier/source identity differs')
    old = module('endpoint_retained_' + key, Path(descriptor['script']).name)
    original = json.loads((ROOT/descriptor['path']).read_text())
    old.verify_plan(original)
    if old.EVIDENCE != descriptor['path'] or old.MANIFEST_SHA256 != descriptor['manifest_sha256']:
        raise ValueError('Vector endpoint retained entry identity differs')
    control = original['public_control']
    for path, sha in [(control['probe'], control['probe_sha256']),
                      *original['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes()) != sha:
            raise ValueError('Vector endpoint retains changed original source inputs: ' + path)
    projected = project_retained(m, key, original, evidence_only)
    known = {str((ROOT/q['script']).resolve()): name
             for name, q in m['retained_replays'].items()}

    def run(command, **kwargs):
        if isinstance(command, (list, tuple)) and len(command) > 1 and str(command[1]) in known:
            if (len(command) != 2 or str(command[0]) != str(ROOT/'scripts/repo-python')
                    or set(kwargs) != {'cwd', 'capture_output', 'text'}
                    or kwargs['cwd'] != ROOT or not kwargs['capture_output'] or not kwargs['text']):
                raise ValueError('Vector endpoint changes a retained dependency invocation')
            output = io.StringIO()
            with contextlib.redirect_stdout(output):
                replay_retained(m, known[str(command[1])], evidence_only)
            return subprocess.CompletedProcess(command, 0, output.getvalue(), '')
        return subprocess.run(command, **kwargs)

    # Keep all old files and standard subprocess behavior intact. Only this
    # isolated verifier module routes the two declared retained dependencies.
    old.subprocess = SimpleNamespace(run=run)
    old.replay(projected)
    print(key + ' retained whole cold source proof passes; exact bounded current canonical successors checked.', flush=True)


def replay(m,evidence_only=False):
    c = module('ends_target','compare-coff-function.py'); coff = module('ends_coff','coff_data.py')
    flow = module('ends_flow','sdk_image_carriers.py'); target = c.verified_target()
    if digest(target) != m['target_sha256']: raise ValueError('Vector endpoint target identity differs')
    for path,sha in m['retained_sha256'].items():
        if digest((ROOT/path).read_bytes()) != sha: raise ValueError('Vector endpoint changes retained evidence/source: '+path)
    for q in m['header_definitions']:
        if ((ROOT/q['path']).read_text().splitlines()[q['start']-1:q['end']] != q['lines']
                or q['path'] not in m['public_control']['headers']):
            raise ValueError('Vector endpoint loses original public SDK definitions')
    fs = {r['address']:r for r in rows('functions.csv')}; origins = {r['address']:r for r in rows('function-origins.csv')}
    selected = {r['address']:r for r in m['functions']}; state = 'original' if evidence_only else 'accepted'
    for q in m['canonical']:
        key = q['function']['address']; expected = q
        if key in selected: expected = dict(function=selected[key][state+'_function'],origin=selected[key][state+'_origin'])
        if dict(function=fs[key],origin=origins[key]) != expected:
            raise ValueError('Vector endpoint bounded canonical state differs: '+key)
    for q in m['historical_snapshots']:
        old = json.loads((ROOT/q['path']).read_text())
        for part in q['trail']: old = old[part]
        original = selected[old['function']['address']]['original_function']
        if (old != q['record'] or old['origin'] != selected[old['function']['address']]['original_origin']
                or any(old['function'][key] != original[key] for key in original if key not in ['evidence','notes'])):
            raise ValueError('Vector endpoint rewrites historical unknown evidence')
    verify_native(m,target,c,flow)
    shared = {}
    scratch = ROOT/'build/origin-vector-endpoint-route-verification'; scratch.mkdir(parents=True,exist_ok=True)
    control = m['public_control']
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj = Path(temp)/'VectorEndpointRoutes.obj'
        result = subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/control['probe']),str(obj),*control['profile']],
            cwd=ROOT,capture_output=True,text=True)
        if result.returncode or headers(result.stdout+result.stderr) != control['headers']:
            raise ValueError('Vector endpoint cold source/includes differ')
        verify_control(m,obj.read_bytes(),target,c,coff,flow,shared)
    replay_retained(m,'R211',evidence_only)


def main():
    parser = argparse.ArgumentParser(description=__doc__); parser.add_argument('--evidence-only',action='store_true')
    args = parser.parse_args(); m = json.loads((ROOT/EVIDENCE).read_text()); verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes()) != MANIFEST_SHA256: raise ValueError('Vector endpoint immutable manifest differs')
    replay(m,args.evidence_only)
    print('R227: four complete vector begin/end origins124; full original/manual endpoints, distinct first/last and constructor routes, retained whole assignment/copy graphs with strict canonical successors; five opaque leaves remain unknown; no source/ABI/exact credit.')


if __name__ == '__main__': main()
