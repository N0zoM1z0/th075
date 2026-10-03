#!/usr/bin/env python3
"""Cold-replay R114 shared queue lifetime, callback and retained ambiguities."""
from __future__ import annotations
import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86 import X86_OP_IMM, X86_OP_MEM

ROOT = Path(__file__).resolve().parents[1]
PROFILE = ['/Od', '/Ob0', '/Gy', '/GR-', '/GX', '/Zi', '/GS', '/I', 'src']
ROLES = {'0x004239F0': 'EventQueue::AcquireSharedServiceAt004239F0',
         '0x00423A90': 'EventQueue::ReleaseSharedServiceAt00423A90',
         '0x004239C0': 'EventQueue::LocalAcquireReleaseAt004239C0',
         '0x00603650': 'GameApplication::WindowCallbackAt00603650'}
PENDING = {'0x00423B20', '0x0064232C'}
FIELDS = {
    '0x004239F0': [(9,'0x0068BE30'),(20,'0x0066C23C'),(26,'0x0066C23C'),(35,'0x0066C23C'),
                  (47,'0x00657268'),(52,'0x0068BE44'),(57,'0x00423F30'),(71,'0x00657054'),
                  (76,'0x0068BE34'),(81,'0x0068BE3C'),(90,'0x00423B40'),(100,'0x0065713C'),
                  (105,'0x0068BE38'),(113,'0x0068BE38'),(120,'0x00657140'),(126,'0x0068BE40'),
                  (133,'0x0068BE30'),(142,'0x0068BE30')],
    '0x00423A90': [(10,'0x0068BE30'),(18,'0x0068BE30'),(26,'0x0068BE40'),(35,'0x0068BE38'),
                  (42,'0x00657134'),(65,'0x0068BE44'),(70,'0x00423D40'),(84,'0x0068BE44'),
                  (89,'0x00423DB0'),(98,'0x0065705C'),(105,'0x0068BE44'),(110,'0x00423F30'),
                  (116,'0x0068BE34'),(123,'0x00657138'),(128,'0x0068BE38'),(135,'0x00657138')],
    '0x00603650': [(32,'0x0068D674'),(43,'0x0065723C'),(69,'0x00657240')],
    '0x004239C0': [(15,'0x004239F0'),(23,'0x00423A90')],
    '0x00423B20': [(10,'0x004239F0'),(18,'0x00423A90')],
}


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def initializer_section(data, comparison):
    """Freeze the entire compiler-emitted initializer table and its typed edges."""
    count, symbol_offset, symbol_count = struct.unpack_from('<H', data, 2)[0], *struct.unpack_from('<II', data, 8)
    strings_offset = symbol_offset + symbol_count * 18
    strings = data[strings_offset:strings_offset + struct.unpack_from('<I', data, strings_offset)[0]]
    symbols, index = {}, 0
    while index < symbol_count:
        raw, value, number, typ, storage, aux = struct.unpack_from('<8sIhHBB', data, symbol_offset + index * 18)
        symbols[index] = {'symbol': comparison.coff_name(raw, strings), 'offset': value,
                          'section': number, 'type': typ, 'storage': storage}
        index += aux + 1
    sections = [(i + 1, struct.unpack_from('<8sIIIIIIHHI', data, 20 + i * 40)) for i in range(count)]
    found = [(n, s) for n, s in sections if s[0].rstrip(b'\0') == b'.CRT$XCU']
    if len(found) != 1:
        raise ValueError('compiler initializer lacks its complete registration section')
    number, section = found[0]
    if section[3] != 8 or section[7] != 2 or section[4] + section[3] > len(data):
        raise ValueError('compiler initializer registration extent differs')
    raw = data[section[4]:section[4] + section[3]]
    relocations = []
    for i in range(section[7]):
        offset, target, typ = struct.unpack_from('<IIH', data, section[5] + 10 * i)
        if offset not in (0, 4) or typ != 6 or target not in symbols:
            raise ValueError('compiler initializer registration edge differs')
        relocations.append({'offset': offset, 'type': 'DIR32', 'symbol': symbols[target]['symbol'],
                            'addend': struct.unpack_from('<I', raw, offset)[0]})
    return {'size': len(raw), 'sha256': hashlib.sha256(raw).hexdigest(),
            'relocations': relocations,
            'definitions': [{'symbol': s['symbol'], 'offset': s['offset']} for s in symbols.values()
                            if s['section'] == number and s['storage'] in (2, 3)
                            and not s['symbol'].startswith('.')]}


def verify_decisions(manifest):
    rows = {r['address']: r for r in manifest['functions']}
    if (len(rows) != 6 or set(rows) != set(ROLES) | PENDING
            or sum(r['size'] for r in rows.values()) != 910
            or {k for k, r in rows.items() if r['decision'] == 'authored'} != set(ROLES)
            or any(rows[k]['decision'] != 'pending' for k in PENDING)):
        raise ValueError('R114 bounded decisions or retained ambiguity differ')
    for key, expected in FIELDS.items():
        for alternative in rows[key]['source_alternatives']:
            if [(b['offset'], b['target_address']) for b in alternative['relocations']] != expected:
                raise ValueError('shared queue/callback actual typed fields differ')
    if (len(rows['0x004239C0']['source_alternatives']) != 1
            or rows['0x004239C0']['source_alternatives'][0]['symbol'] != '??0ExplicitConstructProbe@@QAE@XZ'):
        raise ValueError('local construction lacks its complete explicit constructor control')
    alternatives = rows['0x00423B20']['source_alternatives']
    if ({r['symbol'] for r in alternatives} != {'?ExplicitPulseProbe@@YAXXZ', '_$E3'}
            or len(alternatives) != 2 or len({r['body_sha256'] for r in alternatives}) != 1
            or rows['0x00423B20']['uncertainty'] != 'authored-generated-initializer-ambiguity'):
        raise ValueError('short pulse loses its ordinary/compiler-generated whole alternatives')
    startup = rows['0x0064232C']
    if (startup['uncertainty'] != 'crt-startup-bindings-unresolved'
            or startup['source_alternatives'] or startup['archive_source']['symbol'] != '_WinMainCRTStartup'
            or startup['archive_source']['size'] != 469 or len(startup['archive_source']['relocations']) != 37
            or not any(b['binding_status'] == 'unresolved' for b in startup['archive_source']['relocations'])):
        raise ValueError('startup diagnostic cannot become accepted CRT ownership')
    controls = manifest['lifetime_controls']
    expected = {'??0ExplicitConstructProbe@@QAE@XZ':34, '??1ExplicitDestroyProbe@@QAE@XZ':31,
                '??0ImplicitConstructProbe@@QAE@XZ':24, '??1ImplicitConstructProbe@@QAE@XZ':19,
                '??0ExplicitPersistentProbe@@QAE@XZ':24, '??1ExplicitPersistentProbe@@QAE@XZ':19,
                '?ExplicitPulseProbe@@YAXXZ':26, '_$E1':31, '_$E3':26,
                '?Pulse@MemberPulseProbe@@QAEPAU1@XZ':40}
    if len(controls) != 10 or {r['symbol']:r['size'] for r in controls} != expected:
        raise ValueError('complete explicit/implicit/initializer controls differ')
    registration = manifest['initializer_registration']
    if (registration['size'] != 8 or registration['relocations'] != [
            {'offset':0,'type':'DIR32','symbol':'_$E1','addend':0},
            {'offset':4,'type':'DIR32','symbol':'_$E3','addend':0}]
            or registration['definitions'] != [{'symbol':'_$S2','offset':0},{'symbol':'_$S4','offset':4}]):
        raise ValueError('generated source alternatives lack their complete initializer registration')
    contexts = {r['address']: r for r in manifest['contexts']}
    if (set(contexts) != {'0x00602A60','0x00423B40','0x00423C60','0x00423C80'}
            or any(r['origin'] != 'authored' for r in contexts.values())):
        raise ValueError('shared queue policy lacks independent game ownership contexts')
    main = contexts['0x00602A60']
    if (not any(w['site'] == '0x00602B47' and w['operands'] == 'dword ptr [ebp - 0x28], 0x603650'
                for w in main['instruction_witnesses'])
            or not any(w['site'] == '0x00602CE0' and w['operands'] == 'eax, byte ptr [0x68d674]'
                       for w in main['instruction_witnesses'])):
        raise ValueError('window callback lacks actual registration/readiness context')
    calls = main['body_facts']['direct_calls']
    if ([c['site'] for c in calls if c['target'] == '0x004239F0'] != ['0x00602A77']
            or [c['site'] for c in calls if c['target'] == '0x00423A90'] !=
            ['0x00602BE2','0x00602C5F','0x00602CD0','0x006035F1']):
        raise ValueError('shared lifetime lacks the actual independent main-loop call pair')
    expected_imports = {
        '0x004239F0': [('WINMM.dll','timeBeginPeriod'),('KERNEL32.dll','CreateEventA'),
                       ('KERNEL32.dll','CreateThread'),('KERNEL32.dll','SetThreadPriority')],
        '0x00423A90': [('KERNEL32.dll','TerminateThread'),('KERNEL32.dll','SetEvent'),
                       ('KERNEL32.dll','CloseHandle'),('KERNEL32.dll','CloseHandle')],
        '0x00603650': [('USER32.dll','PostQuitMessage'),('USER32.dll','DefWindowProcA')],
    }
    for key, expected in expected_imports.items():
        if [(r.get('dll'),r.get('symbol')) for r in rows[key]['indirect_calls']] != expected:
            raise ValueError('shared lifetime/callback loses actual raw API identities')
    bindings = startup['archive_source']['relocations']
    if ([b['offset'] for b in bindings if b['binding_status'] == 'raw-import'] != [34,111,263,347]
            or [b['offset'] for b in bindings if b['binding_status'] == 'game-main'] != [384]
            or sum(b['binding_status'] == 'unresolved' for b in bindings) != 32):
        raise ValueError('startup diagnostic cannot promote unresolved code/data fields')
    return rows


def check_ledger(row, functions, origins, evidence_only):
    key, address, size = row['address'], int(row['address'], 16), row['size']
    function, origin = functions[key], origins[key]
    if (int(function['size']) != size or function['span_end'] != row['span_end']
            or int(row['span_end'], 16) != address + size - 1
            or any(address < int(k, 16) < address + size for k in functions)):
        raise ValueError('R114 complete extent contains an unresolved interior candidate')
    if function['source_file'] or function['match_percent'] != '0.00':
        raise ValueError('origin probe cannot grant source or exact credit')
    if evidence_only:
        return
    if key in ROLES:
        if (origin['origin'] != 'authored' or origin['evidence_id'] != 'R114'
                or origin['disposition'] != 'authored' or function['owner'] != 'authored'
                or function['status'] != 'unclassified' or function['proposed_name'] != ROLES[key]):
            raise ValueError('R114 accepted authored ledger differs')
    elif (origin['origin'] != 'unknown' or origin['disposition'] != 'review'
            or origin['evidence_id'] != 'R114' or origin['confidence'] != row['uncertainty']
            or function['owner'] or function['status'] != 'unclassified'):
        raise ValueError('R114 pending ambiguity gains unearned origin credit')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only', action='store_true')
    args = parser.parse_args()
    comparison = module('ql_target', 'compare-coff-function.py')
    record = module('ql_record', 'verify-vendor-record-origins.py')
    authored = module('ql_authored', 'verify-authored-origins.py')
    lifetime = module('ql_lifetime', 'verify-game-lifetime-origins.py')
    sdk = module('ql_sdk', 'verify-sdk-origins.py')
    coff = module('ql_coff', 'coff_data.py')
    runtime = module('ql_archive', 'verify-runtime-origins.py')
    imports_module = module('ql_import', 'verify-import-origins.py')
    target = comparison.verified_target()
    pe = struct.unpack_from('<I',target,0x3C)[0]
    if sum(struct.unpack_from('<I',target,pe+24+offset)[0] for offset in (16,28)) != 0x64232C:
        raise ValueError('startup candidate is not the supplied PE entry')
    manifest = json.loads((ROOT / 'config/queue-lifetime-origin-evidence.json').read_text())
    if (manifest['evidence_id'] != 'R114' or manifest['profile'] != PROFILE
            or manifest['target_sha256'] != hashlib.sha256(target).hexdigest()):
        raise ValueError('R114 pinned target/profile differs')
    rows = verify_decisions(manifest)
    functions = {r['address']:r for r in record.rows('functions.csv')}
    origins = {r['address']:r for r in record.rows('function-origins.csv')}
    evidence = {r['address']:r for r in record.rows('authored-origin-evidence.csv')}
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    bodies = {}
    direct_switches = record.rows('authored-origin-direct-switches.csv')
    imports = imports_module.pe_imports(target, comparison)
    for row in manifest['functions'] + manifest['contexts']:
        key, address = row['address'], int(row['address'],16)
        if key in rows:
            check_ledger(row, functions, origins, args.evidence_only)
        else:
            if (origins[key]['origin'] != row['origin'] or origins[key]['evidence_id'] != row['origin_evidence']
                    or int(functions[key]['size']) != row['size'] or functions[key]['span_end'] != row['span_end']):
                raise ValueError('independent game context ledger differs')
        code = comparison.pe_bytes_at(target, address, row['size'])
        cfg = list(authored.verify_body(code, address, [], lambda a,n: comparison.pe_bytes_at(target,a,n),
                                       [s for s in direct_switches if s['address'] == key]))
        instructions = list(decoder.disasm(code,address))
        if (hashlib.sha256(code).hexdigest() != row['body_sha256'] or cfg != row['cfg']
                or lifetime.body_facts(instructions) != row['body_facts']):
            raise ValueError('complete queue lifetime/callback/entry context differs')
        by_site = {f'0x{i.address:08X}':i for i in instructions}
        for witness in row['instruction_witnesses']:
            instruction = by_site[witness['site']]
            if (instruction.mnemonic,instruction.op_str) != (witness['mnemonic'],witness['operands']):
                raise ValueError('queue global, message, indirection or lifetime witness differs')
        indirect = [i for i in instructions if i.mnemonic == 'call' and i.operands[0].type != X86_OP_IMM]
        if [(f'0x{i.address:08X}',i.op_str) for i in indirect] != [(r['site'],r['operand']) for r in row['indirect_calls']]:
            raise ValueError('complete indirect call inventory differs')
        for call in row['indirect_calls']:
            if 'iat_slot' in call and imports.get(int(call['iat_slot'],16)) != (call['dll'],call['symbol']):
                raise ValueError('queue/callback API lacks raw PE import identity')
        bodies[key] = code
        if key in ROLES and not args.evidence_only:
            body = evidence[key]
            if (body['evidence_id'] != 'R114' or body['body_sha256'] != row['body_sha256']
                    or body['inferred_role'] != ROLES[key] or body['external_branch_count'] != '0'
                    or [int(body['return_count']),int(body['internal_branch_count'])] != cfg):
                raise ValueError('R114 authored extent evidence differs')
    scratch = ROOT / 'build/origin-queue-lifetime-verification'
    scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        objects = {}
        for probe in manifest['probes']:
            source = ROOT / probe['path']
            if hashlib.sha256(source.read_bytes()).hexdigest() != probe['sha256']:
                raise ValueError('natural queue lifetime probe differs')
            path = Path(temporary) / (source.stem + '.obj')
            result = subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(source),str(path),*PROFILE],
                                    cwd=ROOT,capture_output=True,text=True)
            if result.returncode:
                raise ValueError('pinned queue lifetime cold build failed: '+result.stdout[-1000:])
            objects[probe['path']] = path
        if initializer_section(objects['probes/VC7QueueLifetimeControls.cpp'].read_bytes(),comparison) != manifest['initializer_registration']:
            raise ValueError('whole compiler initializer registration differs')
        for control in manifest['lifetime_controls']:
            lifetime.complete_definition(objects[control['probe']],control,comparison,coff)
        for row in manifest['functions']:
            for alternative in row['source_alternatives']:
                source, relocations = lifetime.complete_definition(objects[alternative['probe']],alternative,comparison,coff)
                record.compare_complete_body(source,relocations,bodies[row['address']],int(row['address'],16),
                                             alternative['relocations'],comparison,sdk)
                for binding in alternative['relocations']:
                    symbol = binding['symbol']
                    if symbol.startswith('__imp_'):
                        slot = int(binding['target_address'],16)
                        if slot not in imports or symbol != '__imp__'+imports[slot][1]+'@'+str(manifest['import_stack_bytes'][imports[slot][1]]):
                            raise ValueError('source import decoration differs from raw target API')
        for anchor in manifest['library_controls']:
            path = objects[anchor['probe']]
            source, relocations = lifetime.complete_definition(path,anchor,comparison,coff)
            actual = comparison.pe_bytes_at(target,int(anchor['address'],16),anchor['size'])
            if (hashlib.sha256(actual).hexdigest() != anchor['target_sha256']
                    or origins[anchor['address']]['origin'] != 'library'
                    or origins[anchor['address']]['evidence_id'] != anchor['origin_evidence']):
                raise ValueError('queue clear/size/index independent library control differs')
            record.compare_complete_body(source,relocations,actual,int(anchor['address'],16),anchor['relocations'],comparison,sdk)
        startup = rows['0x0064232C']['archive_source']
        raw = (ROOT/'.tools/msvc710/Vc7/lib'/startup['library']).read_bytes()
        if hashlib.sha256(raw).hexdigest() != startup['archive_sha256']:
            raise ValueError('startup diagnostic archive identity differs')
        name, data = next((name,data) for offset,name,data in runtime.archive_members(raw) if offset == startup['member_offset'])
        if name != startup['member'] or hashlib.sha256(data).hexdigest() != startup['member_sha256']:
            raise ValueError('startup whole archive member differs')
        path = Path(temporary)/'StartupMember.obj'
        path.write_bytes(data)
        source, relocations = comparison.object_function(path,startup['symbol'])
        if len(source) != 469 or hashlib.sha256(source).hexdigest() != startup['body_sha256']:
            raise ValueError('startup diagnostic loses its own complete auxiliary extent')
        bindings = [{k:b[k] for k in ('offset','type','symbol','addend','target_address')} for b in startup['relocations']]
        record.compare_complete_body(source,relocations,bodies['0x0064232C'],0x64232C,bindings,comparison,sdk)
        for binding in startup['relocations']:
            if binding['binding_status'] == 'raw-import':
                slot = int(binding['target_address'],16)
                if slot not in imports or binding['symbol'] != '__imp__'+imports[slot][1]+'@'+str(manifest['import_stack_bytes'][imports[slot][1]]):
                    raise ValueError('startup import diagnostic differs')
            elif binding['binding_status'] == 'game-main':
                if binding['offset'] != 384 or binding['symbol'] != '_WinMain@16' or binding['target_address'] != '0x00602A60':
                    raise ValueError('startup game-main callback diagnostic differs')
            elif binding['binding_status'] != 'unresolved':
                raise ValueError('startup diagnostic promotes an unresolved binding')
    # Replays own the full library dependencies and the main loop's embedded table.
    for filename in ('verify-vendor-deque-destructor-origins.py','verify-event-queue-origins.py'):
        result = subprocess.run([str(ROOT/'scripts/repo-python'),'scripts/'+filename],cwd=ROOT,capture_output=True,text=True)
        if result.returncode:
            raise ValueError('independent queue dependency replay failed: '+result.stderr[-1000:])
    print('R114 origins OK: four authored policies / 415 bytes; ten complete lifetime controls / 274 bytes, '
          '37 policy fields, complete clear/size/index controls, four independent game contexts; '
          'ordinary/generated 26-byte pulse and 469-byte CRT startup remain pending; no source or exact credit.')
    return 0


if __name__ == '__main__':
    try:
        raise SystemExit(main())
    except (OSError,KeyError,IndexError,ValueError,struct.error) as error:
        print('error: '+str(error),file=sys.stderr)
        raise SystemExit(1)
