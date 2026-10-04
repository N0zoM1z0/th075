#!/usr/bin/env python3
"""Cold-replay complete vector producer observations without inferring unknown owners."""
from __future__ import annotations
import argparse
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
# Reuse complete object inventory, checked relocation linking and pinned target readers.
import importlib.util
spec = importlib.util.spec_from_file_location('producer_prior', ROOT/'scripts/verify-vector-endpoint-origins.py')
PRIOR = importlib.util.module_from_spec(spec); spec.loader.exec_module(PRIOR)
PAIRED = PRIOR.PAIRED
module = PRIOR.module
digest = PAIRED.digest
MANIFEST_SHA256 = '60d5970525df0c05cb0a5ae603daac196e565668fa96a3f88612ed8ffe2dbdd3'
CONFIDENCE = 'complete-vc7-vector-endpoint-with-whole-independent-assignment-and-constructor-context'
CANDIDATES = dict(zip(['0x0040DCE0','0x0040DD00','0x0040E4A0','0x00411CC0','0x004121C0',
 '0x0041D980','0x0041EF00','0x00531DD0','0x00532300','0x005F8490','0x005F8EF0','0x005F95B0',
 '0x005F8B50','0x005F9350','0x005F9600'],[31,31,28,31,28,31,28,31,28,31,31,28,31,31,28]))
KEYS = dict(CANDIDATES, **{'0x0040E000':158,'0x005F84B0':167})
ACCEPTED = {'0x005F8B50','0x005F9350','0x005F9600'}
PROFILE = ['/Od','/Ob0','/Gy','/GR-','/GX','/Zi','/I','src','/showIncludes']
LAYOUT = [44,16,4,4,4,4,16,16,16,16,16,16,4,4,4,4,4,4,4,16,4,16,16]
BOUNDARIES = ['0x0040DDC0','0x0040E5A0','0x005F8F60','0x005F8F30','0x005F93C0','0x005F9390']
BASES = ['0x0040E990','0x00412440','0x0041F770','0x005323C0','0x005F9DB0','0x005F9E00']
OPAQUE = ['0x00411C90','0x00411D30','0x0041D950','0x0041D9C0','0x00531DA0','0x00531CB0','0x00411E80','0x00531D80']


def manifest():
    return json.loads((ROOT/'config/vector-producer-origin-evidence.json').read_text())


def verify_plan(m):
    if (m['evidence_id'] != 'R162' or m['target_sha256'] != PAIRED.manifest()['target_sha256']
            or m['probe'] != 'probes/VC7VectorProducerContexts.cpp' or m['profile'] != PROFILE
            or len(m['headers']) != 27 or {r['address']:r['size'] for r in m['functions']} != KEYS
            or len(m['functions']) != 17 or len(m['controls']) != 43
            or sum(r['size'] for r in m['controls']) != 2039
            or sum(len(r['bindings']) for r in m['controls']) != 95
            or len(m['emission']) != 244 or sum(r['size'] for r in m['emission']) != 13520
            or m['layout_values'] != LAYOUT or m['layout'] not in m['emission'] or m['layout']['size'] != 92
            or len(m['retained']) != 19 or len(m['snapshots']) != 57
            or m['opaque_contexts'] != OPAQUE or len(m['contexts']) != 5
            or [len(r['calls']) for r in m['contexts']] != [2,2,1,2,1]):
        raise ValueError('vector producer omits bounded full source, parent, real fields, ordinary emission or layout')
    mutable = {'proposed_name','module','status','owner','evidence','notes'}
    for row in m['functions']:
        a = row['address']; old,new = row['original_function'],row['accepted_function']
        if (old['address'] != a or int(old['size']) != row['size']
                or {k:v for k,v in old.items() if k not in mutable} != {k:v for k,v in new.items() if k not in mutable}
                or new['source_file'] or new['calling_convention'] or new['signature'] or new['match_percent'] != '0.00'
                or row['original_origin']['origin'] != 'unknown'):
            raise ValueError('vector producer changes full extent or grants source/private ABI/exact credit')
        if a in ACCEPTED:
            if (row['decision'] != 'library' or new['owner'] != 'library' or new['status'] != 'excluded' or new['module'] != 'VC7STL'
                    or row['accepted_origin'] != dict(address=a,origin='library',subsystem='VC7STL',disposition='exclude',confidence=CONFIDENCE,evidence_id='R162')):
                raise ValueError('vector producer changes its three bounded independent library decisions')
        elif (row['decision'] != 'unknown' or row['accepted_origin'] != row['original_origin']
                or any(new[k] != old[k] for k in ('proposed_name','module','status','owner'))):
            raise ValueError('vector producer infers unresolved ownership from an ordinary-equivalent source or reviewed child/caller')
    controls = m['controls']; records = {r['address']:r for r in m['functions']}
    if ([r['address'] for r in controls[:30]] != list(CANDIDATES)+BASES+['0x0040E000','0x005F84B0','0x005F8B70']+BOUNDARIES
            or [r['role'] for r in controls] != ['candidate-sdk-owner']*15+['retained-sdk-base']*6+['whole-assignment-context']*3
              +['retained-sdk-boundary']*6+['byte-equal-ordinary-endpoint']*3+['byte-equal-ordinary-assignment']*2
              +['whole-eh-carrier','whole-eh-state']*4
            or [r['size'] for r in controls[15:]] != [24]*6+[158,167,96]+[99,33]*3+[31,31,28,158,167]+[18,36]*4):
        raise ValueError('vector producer truncates or replaces independent whole code/state/ordinary controls')
    routes = dict(zip(list(CANDIDATES),['0x0040E4A0','0x0040E4A0','0x0040E990','0x004121C0','0x00412440',
         '0x0041EF00','0x0041F770','0x00532300','0x005323C0','0x005F95B0','0x005F95B0','0x005F9DB0',
         '0x005F9600','0x005F9600','0x005F9E00']))
    for index,control in enumerate(controls):
        section,d = control['section'],control['source_definition']
        if (section not in m['emission'] or d not in section['definitions'] or section['size'] != control['size']
                or section['source_sha256'] != control['source_sha256'] or len(section['fields']) != len(control['bindings'])):
            raise ValueError('vector producer loses entire own defining source section or actual fields')
        if control['kind'] == 'code' and (d['offset'] or d['type'] != 32 or d['storage'] != 2):
            raise ValueError('vector producer regular owner lacks its full own positive AUX definition')
        if index < 15 and (d['symbol'] != records[control['address']]['symbol'] or 'Ordinary' in d['symbol']
                or [b['target_address'] for b in control['bindings']] != [routes[control['address']]]):
            raise ValueError('vector producer candidate substitutes ordinary source or actual constructor/base route')
        if 30 <= index < 35 and 'Ordinary' not in d['symbol']:
            raise ValueError('vector producer loses byte-equal independent ordinary alternative')
        if control['kind'] in ('eh-code','state-data') and (d['offset'] != 8 or control['size'] != (18 if control['kind']=='eh-code' else 36)):
            raise ValueError('vector producer truncates cleanup/handler or whole unwind/FuncInfo state')
        for field,binding in zip(section['fields'],control['bindings']):
            if (binding != dict(offset=field['offset'],type=field['type'],symbol=field['symbol']['symbol'],addend=field['addend'],target_address=binding['target_address'])
                    or field['type'] not in ('REL32','DIR32') or field['offset']+4 > control['size']):
                raise ValueError('vector producer masks or replaces a genuine complete source field')
    snapshots = {r['address']:r for r in m['snapshots']}
    for a,origin,evidence,size in [('0x0040D8E0','unknown','R108',19),('0x004588B0','unknown','ghidra-12.1.3-initial-inventory',43),
        ('0x004229D0','unknown','ghidra-12.1.3-initial-inventory',28),('0x0040F9F0','unknown','ghidra-12.1.3-initial-inventory',15),
        ('0x005F8B70','library','R034',96),('0x006407B8','library','R142',54)]:
        r = snapshots.get(a)
        if not r or r['size'] != size or r['origin']['origin'] != origin or r['origin']['evidence_id'] != evidence:
            raise ValueError('vector producer conflates independent protected lifetime, copy, parent or runtime ownership')
    if any(snapshots[a]['origin']['origin'] != 'library' or snapshots[a]['origin']['evidence_id'] != 'R106' for a in BASES):
        raise ValueError('vector producer discards independently accepted constructor family')
    if any(snapshots[a]['origin']['origin'] != 'unknown' or snapshots[a]['size'] != (8 if a in OPAQUE[-2:] else 42) for a in OPAQUE):
        raise ValueError('vector producer awards a short prefix or reviewed child to an unresolved full producer/bridge')
    for r in m['retained']:
        if r['record']['address'] != r['address'] or (r['file'] not in m['retained_sha256'] and r['file'] != 'config/authored-origin-evidence.csv'):
            raise ValueError('vector producer loses independently retained original complete source record')
    if ([r['handler_address'] for r in m['retained_frames']] != ['0x00654F68','0x006566F8']
            or any(r['state_count'] != '1' or r['try_count'] != '0' or r['evidence_id'] != 'R020' for r in m['retained_frames'])):
        raise ValueError('vector producer loses complete original frame registration')
    negative = m['negative_profile']
    if (negative['profile'] != PROFILE+['/GS'] or negative['headers'] != m['headers']
            or len(negative['emission']) != 244 or sum(r['size'] for r in negative['emission']) != 13616
            or [(r['address'],r['target_size'],r['section']['size']) for r in negative['controls']] != [('0x0040E000',158,174),('0x005F84B0',167,183)]):
        raise ValueError('vector producer incorrectly accepts or truncates full cookie-profile alternatives')
    for r in negative['controls']:
        section,d = r['section'],r['source_definition']
        if (section not in negative['emission'] or d not in section['definitions'] or d['offset'] or d['storage'] != 2 or d['type'] != 32
                or not d['symbol'].startswith('?_Assign_n@?$vector@U')
                or [f['symbol']['symbol'] for f in section['fields'] if 'security' in f['symbol']['symbol']] != ['___security_cookie','@__security_check_cookie@4']):
            raise ValueError('vector producer loses full genuine SDK cookie fields in its negative control')


def check_ledger(row, function, origin, evidence_only=False):
    transitions={'0x00411CC0':'verify-list-iterator-policy-origins.py','0x004121C0':'verify-list-iterator-policy-origins.py',
        '0x0041D980':'verify-archive-list-policy-origins.py','0x0041EF00':'verify-archive-list-policy-origins.py',
        '0x00531DD0':'verify-character-list-policy-origins.py','0x00532300':'verify-character-list-policy-origins.py',
        '0x0040DCE0':'verify-texture-vector-access-origins.py','0x0040DD00':'verify-texture-vector-access-origins.py','0x0040E4A0':'verify-texture-vector-access-origins.py'}
    if row['address'] in transitions and row['decision']=='unknown':
        later=module('producer_list_ledger_transition',transitions[row['address']])
        if later.accepted_snapshot(dict(function=row['accepted_function'],origin=row['accepted_origin']),function,origin):return
    PRIOR.check_ledger(row,function,origin,evidence_only)


def accepted_snapshot(snapshot,function,origin):
    m = manifest()
    if digest((ROOT/'config/vector-producer-origin-evidence.json').read_bytes()) != MANIFEST_SHA256:
        raise ValueError('vector producer immutable complete evidence differs')
    verify_plan(m)
    r = next((r for r in m['functions'] if r['address']==function['address']),None)
    return bool(r and snapshot==dict(function=r['original_function'],origin=r['original_origin'])
                and function==r['accepted_function'] and origin==r['accepted_origin'])


def preserved_snapshot(row,function,origin):
    if function==row['function'] and origin==row['origin']:return True
    transitions={'0x00411C90':'verify-list-iterator-policy-origins.py','0x00411D30':'verify-list-iterator-policy-origins.py',
        '0x0041D950':'verify-archive-list-policy-origins.py','0x0041D9C0':'verify-archive-list-policy-origins.py',
        '0x00531DA0':'verify-character-list-policy-origins.py','0x00531CB0':'verify-character-list-policy-origins.py'}
    if row['address'] not in transitions:return False
    later=module('producer_list_snapshot_transition',transitions[row['address']])
    return later.accepted_snapshot(dict(function=row['function'],origin=row['origin']),function,origin)


def main():
    parser = argparse.ArgumentParser(description=__doc__); parser.add_argument('--evidence-only',action='store_true'); args = parser.parse_args()
    m = manifest(); verify_plan(m)
    for path,expected in [('config/vector-producer-origin-evidence.json',MANIFEST_SHA256),(m['probe'],m['probe_sha256']),*m['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes()) != expected:
            raise ValueError('vector producer immutable probe/prior evidence differs: '+path)
    c = module('producer_target','compare-coff-function.py'); coff = module('producer_coff','coff_data.py')
    extent = module('producer_extent','verify-vendor-record-origins.py'); cfg = module('producer_cfg','verify-authored-origins.py')
    eh = module('producer_eh','compiler_eh.py'); target = c.verified_target()
    if digest(target) != m['target_sha256']:
        raise ValueError('vector producer supplied target differs')
    rows = PAIRED.BUFFER.PRIOR.PRIOR.rows
    functions = {r['address']:r for r in rows('functions.csv')}; origins = {r['address']:r for r in rows('function-origins.csv')}
    records = {r['address']:r for r in m['functions']}
    for r in m['functions']: check_ledger(r,functions[r['address']],origins[r['address']],args.evidence_only)
    for r in m['snapshots']:
        a = r['address']
        if a in records: check_ledger(records[a],functions[a],origins[a],args.evidence_only)
        elif not preserved_snapshot(r,functions[a],origins[a]):
            raise ValueError('vector producer changes independent accepted/protected opaque canonical boundary')
        if digest(c.pe_bytes_at(target,int(a,16),r['size'])) != r['body_sha256']:
            raise ValueError('vector producer independent whole boundary differs')
    for r in m['retained']:
        path = ROOT/r['file']
        inventory = json.loads(path.read_text())['functions'] if path.suffix=='.json' else rows(path.name)
        if r['record'] not in inventory:
            raise ValueError('vector producer original full independent source evidence differs')
    decoder = Cs(CS_ARCH_X86,CS_MODE_32)
    for r in m['contexts']:
        a = r['address']; base = int(a,16); body = c.pe_bytes_at(target,base,r['size'])
        if (functions[a] != r['function'] or origins[a] != r['origin'] or r['authored_record'] not in rows('authored-origin-evidence.csv')
                or digest(body) != r['body_sha256']):
            raise ValueError('vector producer whole independently authored game context differs')
        cfg.verify_body(body,base,[x for x in rows('authored-origin-switches.csv') if x['address']==a],
            lambda a,n:c.pe_bytes_at(target,a,n),[x for x in rows('authored-origin-direct-switches.csv') if x['address']==a])
        ins = list(decoder.disasm(body,base))
        for call in r['calls']:
            window = call['instructions']; i = next(i for i,x in enumerate(ins) if x.address==int(window[0]['address'],16))
            actual = [dict(address=f'0x{x.address:08X}',mnemonic=x.mnemonic,operands=x.op_str) for x in ins[i:i+len(window)]]
            if actual != window or not any(x['address']==call['site'] and x['mnemonic']=='call' and int(x['operands'],16)==int(call['candidate'],16) for x in window):
                raise ValueError('vector producer actual typed receiver/result game call differs')
    for a in OPAQUE:
        cfg.verify_body(c.pe_bytes_at(target,int(a,16),int(functions[a]['size'])),int(a,16))
    for frame in m['retained_frames']:
        if frame not in rows('compiler-eh-frames.csv'):
            raise ValueError('vector producer original independently registered frame differs')
        eh.verify_frame(frame,lambda a,n:c.pe_bytes_at(target,a,n),lambda a,n:c.pe_bytes_at(target,a,n),{int(a,16) for a in functions},set())
    scratch = ROOT/'build/origin-vector-producer-verification'; scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as dirname:
        for index,profile in enumerate([m,m['negative_profile']]):
            path = Path(dirname)/f'VectorProducer{index}.obj'
            result = subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/m['probe']),str(path),*profile['profile']],cwd=ROOT,capture_output=True,text=True)
            if result.returncode or 'warning D4002' in result.stdout+result.stderr or PAIRED.BUFFER.PRIOR.PRIOR.included_headers(result.stdout+result.stderr) != profile['headers']:
                raise ValueError('vector producer cold actual compiler options/header ownership differ')
            data = path.read_bytes()
            if PAIRED.BUFFER.inventory(data,c,coff) != profile['emission']:
                raise ValueError('vector producer entire cold ordinary code/data/EH emission differs')
            if index:
                for r in profile['controls']:
                    if extent.complete_aux_section_size(data,r['source_definition']['symbol'],c.coff_name) != r['section']['size'] or r['section']['size']==r['target_size']:
                        raise ValueError('vector producer negative source loses complete own AUX extent')
                continue
            catalog = {}
            def add(symbol,address):
                if symbol in catalog and catalog[symbol] != address:
                    raise ValueError('vector producer actual source symbol overrides an independent full defining section')
                catalog[symbol] = address
            for r in m['controls']:
                for d in r['section']['definitions']:
                    if d['storage'] in (2,3) and not d['symbol'].startswith('.'):
                        add(d['symbol'],int(r['address'],16)+d['offset'])
            snapshots = {r['address']:r for r in m['snapshots']}
            retained = {r['address']:r for r in m['retained']}
            for r in m['controls']:
                for field,b in zip(r['section']['fields'],r['bindings']):
                    name,a = b['symbol'],b['target_address']
                    if name in catalog:
                        if catalog[name] != int(a,16): raise ValueError('vector producer replaces actual complete source operation owner')
                        continue
                    if name=='__except_list':
                        if a!='0x00000000' or field['symbol']!=dict(symbol=name,offset=0,section=0,type=0,storage=2):
                            raise ValueError('vector producer FS offset is not target data storage')
                    elif r['address'] in BOUNDARIES:
                        old = json.loads(retained[r['address']]['record']['relocation_bindings'])
                        if a not in snapshots or not any(x['offset']==b['offset'] and x['type']==b['type'] and x['target_address']==a and x['symbol'].split('@',1)[0]==name.split('@',1)[0] for x in old):
                            raise ValueError('vector producer external SDK field lacks independent full same-family binding')
                    elif a not in ('0x0040D8E0','0x004588B0','0x006407B8') or a not in snapshots:
                        raise ValueError('vector producer external source field lacks independently complete opaque lifetime/runtime boundary')
                    add(name,int(a,16))
            for r in m['controls']:
                raw,linked = PRIOR.link(data,r,catalog,c); actual = c.pe_bytes_at(target,int(r['address'],16),r['size'])
                if digest(raw)!=r['source_sha256'] or digest(actual)!=r['body_sha256'] or linked!=actual:
                    raise ValueError('vector producer full unmasked source/code/state comparison differs: '+r['address'])
                if r['kind']=='code':
                    if extent.complete_aux_section_size(data,r['source_definition']['symbol'],c.coff_name)!=r['size']:
                        raise ValueError('vector producer loses full positive own AUX regular source extent')
                    cfg.verify_body(actual,int(r['address'],16))
                elif r['kind']=='eh-code':
                    ins = list(decoder.disasm(actual,int(r['address'],16)))
                    if (sum(x.size for x in ins)!=18 or [x.mnemonic for x in ins]!=['lea','jmp','mov','jmp']
                            or ins[2].address!=int(r['address'],16)+8 or ins[3].op_str!='0x6407b8'):
                        raise ValueError('vector producer whole cleanup/handler shared-tail carrier differs')
            raw,_ = coff.readonly_section(data,m['layout']['section'],c.coff_name)
            if list(struct.unpack('<23I',raw))!=LAYOUT:
                raise ValueError('vector producer complete SDK/ordinary observation layout differs')
    print('R162 historical evidence OK: three library endpoints/constructor / 90 bytes through unchanged full R034 assignment; twelve short candidates / 357 bytes and both ordinary-equivalent assignment parents / 158,167 were retained as unknown at R162; exact bounded R168/R169/R170/R173 iterator/list/vector transitions are checked separately; 43 complete source/code/EH/state controls / 2039 bytes and 95 genuine unmasked fields; all 244 cold ordinary sections / 13520 bytes, full 92-byte layout and 27 SDK headers; full /GS negative inventory / 13616 bytes retains 174/183-byte parent extents; independent full game, SDK, runtime, registered frames and protected unknown lifetime/copy contexts preserved; no source/private ABI/mapping/exact credit.')
    return 0


if __name__=='__main__':
    try: raise SystemExit(main())
    except (OSError,KeyError,IndexError,StopIteration,ValueError,struct.error,json.JSONDecodeError) as error:
        print('error: '+str(error),file=sys.stderr); raise SystemExit(1)
