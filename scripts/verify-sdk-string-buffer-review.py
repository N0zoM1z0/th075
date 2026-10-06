#!/usr/bin/env python3
"""Cold-replay the unresolved StringBuffer special-member contribution review."""
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
EVIDENCE = 'config/sdk-string-buffer-review-evidence.json'
MANIFEST_SHA256 = 'a4c52873a3608bdb30cf14a53b3f512d7ba817fdc36b7d08eeba9f0560f01893'
SCHEMA = 'https://github.com/microsoft/microsoft-pdb/blob/master/include/cvinfo.h'


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    value = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(value)
    return value


PRIOR = module('string_buffer_prior', 'verify-crt-absolute-contribution-origins.py')
digest, rows, linked = PRIOR.digest, PRIOR.rows, PRIOR.PRIOR.linked
C = module('string_buffer_target', 'compare-coff-function.py')
CO = module('string_buffer_coff', 'coff_data.py')
E = module('string_buffer_sections', 'sdk_x3d_carriers.py')
RT = module('string_buffer_archive', 'verify-runtime-origins.py')
F = module('string_buffer_flow', 'sdk_graphics_carriers.py')
COMMON = module('string_buffer_headers', 'verify-sdk-row-deleting-helper-origins.py')
HEADERS = module('string_buffer_sdk_headers', 'verify-sdk-interface-origins.py').included_headers
ORDINARY = module('string_buffer_inventory', 'verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory


def compile_record(kind, payload):
    """Decode Microsoft's COMPILESYM, preserving flags and its whole payload."""
    if kind not in (0x1013, 0x1116) or len(payload) < 19:
        raise ValueError('unsupported/truncated COMPILESYM')
    flags, machine, *versions = struct.unpack_from('<I7H', payload)
    if kind == 0x1013:
        n = payload[18]
        if 19 + n > len(payload):
            raise ValueError('truncated compiler Pascal string')
        name, tail = payload[19:19+n], payload[19+n:]
    else:
        end = payload.index(0, 18)
        name, tail = payload[18:end], payload[end+1:]
    return dict(kind=f'0x{kind:04X}', payload_hex=payload.hex(), flags=flags,
                language=flags & 255, no_debug_info=bool(flags & 512), machine=machine,
                frontend=versions[:3], backend=versions[3:],
                compiler=name.decode('ascii'), trailing_hex=tail.hex())


def source_debug(raw):
    if struct.unpack_from('<I', raw)[0] != 2:
        raise ValueError('original SDK debug record is not C11')
    records, at = [], 4
    while at < len(raw):
        length, kind = struct.unpack_from('<HH', raw, at)
        end = at + 2 + length
        if length < 2 or end > len(raw):
            raise ValueError('truncated original debug record')
        payload = raw[at+4:end]
        r = dict(offset=at, length=length, kind=f'0x{kind:04X}', payload_hex=payload.hex())
        if kind == 0x0009:
            if len(payload) < 5 or 5 + payload[4] != len(payload):
                raise ValueError('original object-name string framing differs')
            r.update(signature=struct.unpack_from('<I', payload)[0], object=payload[5:].decode('ascii'))
        elif kind == 0x1013:
            r['compile'] = compile_record(kind, payload)
        else:
            raise ValueError('unexpected original source/type debug witness')
        records.append(r)
        at = end
    if len(records) != 2 or [r['kind'] for r in records] != ['0x0009', '0x1013']:
        raise ValueError('original object/compiler records differ')
    return dict(signature=2, size=len(raw), sha256=digest(raw), records=records, schema=SCHEMA)


def probe_compile(body):
    """Read the actual C13 compiler record, excluding variable object paths."""
    for n in range(1, struct.unpack_from('<H', body, 2)[0] + 1):
        h = struct.unpack_from('<8sIIIIIIHHI', body, 20 + 40*(n-1))
        if h[0].rstrip(b'\0') != b'.debug$S':
            continue
        raw = body[h[4]:h[4]+h[3]]
        if struct.unpack_from('<I', raw)[0] != 4:
            raise ValueError('probe debug record is not C13')
        at = 4
        while at < len(raw):
            kind, size = struct.unpack_from('<II', raw, at)
            end = at + 8 + size
            if end > len(raw):
                raise ValueError('truncated probe debug subsection')
            if kind == 0xf1:
                pos = at + 8
                while pos < end:
                    length, typ = struct.unpack_from('<HH', raw, pos)
                    stop = pos + 2 + length
                    if length < 2 or stop > end:
                        raise ValueError('truncated probe symbol record')
                    if typ == 0x1116:
                        return compile_record(typ, raw[pos+4:stop])
                    pos = stop
            at = (end + 3) & ~3
    raise ValueError('actual cold probe compiler record absent')


def inventory(body):
    return PRIOR.inventory(body, C, CO, E)


def archive(path, sha):
    raw = (ROOT / path).read_bytes()
    if digest(raw) != sha:
        raise ValueError('pinned source archive differs: ' + path)
    return {o: (n, b) for o, n, b in RT.archive_members(raw)}


def weak_fallbacks(body):
    pointer, count = struct.unpack_from('<II', body, 8)
    strings = body[pointer+18*count:]
    symbols, weak, i = {}, [], 0
    while i < count:
        name, value, section, typ, storage, aux = struct.unpack_from('<8sIhHBB', body, pointer+18*i)
        symbol = C.coff_name(name, strings)
        symbols[i] = symbol
        if storage == 105:
            if aux != 1 or section != 0:
                raise ValueError('unsupported weak external declaration')
            raw = body[pointer+18*(i+1):pointer+18*(i+2)]
            fallback, search = struct.unpack_from('<II', raw)
            weak.append(dict(symbol=symbol, index=i, fallback_index=fallback, search=search, aux_hex=raw.hex()))
        i += aux + 1
    for r in weak:
        r['fallback'] = symbols[r['fallback_index']]
        if r['search'] != 2:
            raise ValueError('original weak external search-library policy differs')
    return weak


def native_record(body, section, address, catalog, target, code):
    raw, fields, source = E.section_carrier(body, section, C, CO)
    bindings = [dict(field=f, target_address=catalog[f['symbol']]) for f in fields]
    a = int(address, 16)
    native = C.pe_bytes_at(target, a, len(raw))
    if linked(raw, fields, bindings, a) != native:
        raise ValueError('whole source/native contribution differs: ' + address)
    r = dict(address=address, size=len(raw), source=source, fields=fields, bindings=bindings,
             source_sha256=digest(raw), body_sha256=digest(native))
    if code:
        calls = {a+f['offset']: int(b['target_address'], 16) for f, b in zip(fields, bindings) if f['type'] == 'REL32'}
        data = {a+f['offset']: int(b['target_address'], 16) for f, b in zip(fields, bindings) if f['type'] == 'DIR32'}
        r['flow'] = F.flow(native, a, [0], fields, calls, data)
    return r


def native_review(plan, target):
    src = plan['source']
    name, body = archive(src['archive'], src['archive_sha256'])[src['member_offset']]
    if name != src['member'] or digest(body) != src['member_sha256']:
        raise ValueError('whole original Buffer object differs')
    report = dict(inventory=inventory(body), weak_fallbacks=weak_fallbacks(body))
    debug, _, _ = E.section_carrier(body, 2, C, CO)
    report['debug'] = source_debug(debug)
    report['code'] = [native_record(body, s, a, plan['catalog'], target, True) for s, a in plan['code_placements']]
    report['data'] = [native_record(body, s, a, plan['catalog'], target, False) for s, a in plan['data_placements']]
    if {r['source']['section'] for r in report['code']} != {r['source']['section'] for r in report['inventory'] if r['source']['flags'] & 32}:
        raise ValueError('original whole code section is omitted')
    # Preserve actual fallback records, rather than interpreting names as aliases.
    for alias in report['weak_fallbacks']:
        if plan['catalog'].get(alias['symbol']) != plan['catalog'].get(alias['fallback']):
            raise ValueError('actual weak reference is not bound to its full fallback')
    report['providers'] = []
    members = archive(plan['crt_archive'], plan['crt_archive_sha256'])
    for p in plan['providers']:
        name, obj = members[p['member_offset']]
        if name != p['member'] or digest(obj) != p['member_sha256']:
            raise ValueError('original complete provider member differs')
        record = native_record(obj, p['section'], p['address'], p['catalog'], target, True)
        if not any(d['symbol'] == p['symbol'] and d['offset'] == 0 and d['type'] == 32 and d['storage'] == 2
                   for d in record['source']['definitions']):
            raise ValueError('provider lacks actual function definition')
        aux = next(r for r in record['source']['aux_records'] if r['symbol'] == p['symbol'])
        if aux['aux_count'] != 1 or struct.unpack_from('<I', bytes.fromhex(aux['aux_hex']), 4)[0] != record['size']:
            raise ValueError('provider is not its complete own-AUX extent')
        report['providers'].append(dict(record=record, inventory=inventory(obj)))
    return report


def control_report(body, stdout, ctl, target):
    emission = ORDINARY(body, C, CO)
    sections, definitions, layout = [], {}, None
    for r in emission:
        n = r.get('section')
        if n is None:
            raise ValueError('whole ordinary section index absent')
        raw, fields, src = E.section_carrier(body, n, C, CO)
        sections.append(dict(source=COMMON.SOURCE.BASE.canonical_source(src, body), fields=fields, source_sha256=digest(raw)))
        for d in src['definitions']:
            if d['type'] == 32 and d['storage'] == 2:
                definitions[d['symbol']] = (d, raw, fields)
            if d['symbol'] == '?StringBufferLayout@@3QBKB':
                layout = list(struct.unpack('<6I', raw))
    comparisons = []
    for symbol, address, target_size in ctl['compare']:
        definition, raw, fields = definitions[symbol]
        a = int(address, 16)
        native = C.pe_bytes_at(target, a, target_size)
        available = all(f['symbol'] in ctl['catalog'] for f in fields)
        bindings = [dict(field=f, target_address=ctl['catalog'][f['symbol']]) for f in fields] if available else None
        complete = bytes(linked(raw, fields, bindings, a)) if available else None
        comparisons.append(dict(symbol=symbol, definition=definition, size=len(raw), fields=fields,
                                source_sha256=digest(raw), target=address, target_size=target_size,
                                target_sha256=digest(native), bindings=bindings,
                                linked_sha256=digest(complete) if available else None,
                                whole_equal=complete == native if available else False,
                                differences=sum(x != y for x, y in zip(complete, native)) if available and len(complete) == len(native) else None,
                                instructions=[dict(offset=i.address, mnemonic=i.mnemonic, operands=i.op_str) for i in F.instructions(raw, 0, len(raw))]))
    if layout != [16, 8, 24, 24, 24, 24]:
        raise ValueError('complete ordinary owner layouts differ')
    return dict(emission=emission, sections=sections, layout=layout, comparisons=comparisons,
                headers=HEADERS(stdout), compiler=probe_compile(body))


def cold_controls(plan, target):
    result = []
    for ctl in plan['controls']:
        if digest((ROOT / ctl['source']).read_bytes()) != ctl['source_sha256']:
            raise ValueError('ordinary special-member source differs')
        with tempfile.TemporaryDirectory(prefix='th075-string-buffer-') as directory:
            obj = Path(directory) / 'StringBuffer.obj'
            compiled = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / ctl['source']), str(obj), *ctl['profile']],
                                      cwd=ROOT, capture_output=True, text=True, check=True)
            result.append(control_report(obj.read_bytes(), compiled.stdout + compiled.stderr, ctl, target))
    return result


def guid_review(target):
    """Recheck the independent UUID member and cold public SDK IID definitions."""
    old = json.loads((ROOT / 'config/sdk-interface-origin-evidence.json').read_text())
    uuid = next(a for a in old['archives'] if a['library'] == 'Uuid.Lib')
    members = archive(uuid['path'], uuid['sha256'])
    with tempfile.TemporaryDirectory(prefix='th075-string-buffer-guid-') as directory:
        obj = Path(directory) / 'Guids.obj'
        compiled = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), str(ROOT / old['probe']), str(obj), *old['profile']],
                                  cwd=ROOT, capture_output=True, text=True, check=True)
        emitted = obj.read_bytes()
        if ORDINARY(emitted, C, CO) != old['emission'] or HEADERS(compiled.stdout + compiled.stderr) != old['headers']:
            raise ValueError('whole public IID cold emission/includes differ')
        result = []
        for r in old['guids']:
            if r['symbol'] not in ['_IID_IUnknown', '_IID_ID3DXBuffer']:
                continue
            if r['symbol'] == '_IID_IUnknown':
                name, body = members[r['member_offset']]
                if name != r['member'] or digest(body) != r['member_sha256']:
                    raise ValueError('whole independent UUID source differs')
            else:
                body = emitted
            raw, definitions = CO.readonly_section(body, r['section'], C.coff_name)
            if len(raw) != 16 or definitions != r['definitions'] or digest(raw) != r['source_sha256'] or raw != C.pe_bytes_at(target, int(r['address'], 16), 16):
                raise ValueError('complete independent/public IID identity differs')
            result.append(dict(symbol=r['symbol'], address=r['address'], source_sha256=digest(raw), definitions=definitions))
        return result


def verify_scope(plan):
    native = plan['native']
    if (len(native['inventory']) != 57 or sum(r['source']['size'] for r in native['inventory']) != 1716
            or len(native['code']) != 25 or sum(r['size'] for r in native['code']) != 1030
            or [(r['source']['section'], r['size']) for r in native['data']] != [(6, 28), (25, 28), (34, 4), (35, 4), (48, 28)]):
        raise ValueError('original full contribution/inventory is omitted or cropped')
    at = 0x61fe0a
    for r in native['code']:
        if r['source']['section'] in [3, 16, 22]:
            continue
        if int(r['address'], 16) != at or r['size'] != r['source']['size'] or r['flow']['whole_size'] != r['size']:
            raise ValueError('source-ordered primary contribution is discontinuous or truncated')
        at += r['size']
    if at != 0x6201df:
        raise ValueError('whole primary981 extent differs')
    compiler = native['debug']['records'][1]['compile']
    if compiler['frontend'] != [13, 0, 9176] or compiler['backend'] != [13, 0, 9178] or not compiler['no_debug_info']:
        raise ValueError('original unit-specific compiler witness differs')
    for cold in plan['cold']:
        if cold['compiler']['frontend'] != [13, 10, 3077] or cold['compiler']['backend'] != [13, 10, 3077]:
            raise ValueError('probe compiler is conflated with original SDK compiler')
        compared = {r['symbol']: r for r in cold['comparisons']}
        for symbol, size in [('??0OrdinaryBuffer@@QAE@XZ', 24), ('??0ImplicitDestructorBuffer@@QAE@XZ', 22),
                             ('??0ExplicitDestructorBuffer@@QAE@XZ', 22), ('??1ImplicitDestructorBuffer@@UAE@XZ', 5),
                             ('??1ImplicitStringBuffer@@UAE@XZ', 5)]:
            if compared[symbol]['size'] != size or not compared[symbol]['whole_equal']:
                raise ValueError('coherent full ordinary ctor/implicit-dtor positive omitted')
        for symbol, size in [('??1OrdinaryBuffer@@UAE@XZ', 16), ('??1ExplicitDestructorBuffer@@UAE@XZ', 11),
                             ('??1ExplicitStringBuffer@@UAE@XZ', 11)]:
            if compared[symbol]['size'] != size or compared[symbol]['whole_equal']:
                raise ValueError('whole explicit/base destructor negative omitted or cropped')
    if len(plan['cold']) != 2 or plan['decision'] != 'unknown; no canonical transition or exact credit':
        raise ValueError('bounded unresolved review loses an alternative or invents acceptance')
    if {r['function']['address']: r['origin']['origin'] for r in plan['protected_pairs']} != {
            '0x006200DA': 'unknown', '0x00620132': 'unknown'}:
        raise ValueError('ambiguous special members acquire unsupported ownership')


def main():
    path = ROOT / EVIDENCE
    if digest(path.read_bytes()) != MANIFEST_SHA256:
        raise ValueError('immutable unresolved review manifest differs')
    plan = json.loads(path.read_text())
    verify_scope(plan)
    for path, sha in plan['retained_sha256'].items():
        if digest((ROOT / path).read_bytes()) != sha:
            raise ValueError('retained independent source proof differs: ' + path)
    for name, expected in plan['canonical_sha256'].items():
        if PRIOR.metadata_digest(rows(name)) != expected:
            raise ValueError('unresolved review changes canonical state: ' + name)
    functions, origins = ({r['address']: r for r in rows(n)} for n in ['functions.csv', 'function-origins.csv'])
    for r in plan['protected_pairs']:
        a = r['function']['address']
        if functions.get(a) != r['function'] or origins.get(a) != r['origin']:
            raise ValueError('unresolved special-member literal pair differs')
    target = C.verified_target()
    if digest(target) != plan['target_sha256'] or native_review(plan, target) != plan['native']:
        raise ValueError('whole original contribution/provider/debug/CFG proof differs')
    if cold_controls(plan, target) != plan['cold']:
        raise ValueError('complete cold ordinary special-member alternatives differ')
    if guid_review(target) != plan['guids']:
        raise ValueError('independent whole IID provider proof differs')
    print('R264 unresolved review OK:25 whole original code sections1030, packed primary981, three vtables84/two constants8;'
          'actual weak search-library fallbacks and complete CRT providers; original C11 FE13.0.9176/BE13.0.9178;'
          'two cold VC7.1 profiles, complete ctor24/derived22/implicit-dtor5 positives and whole explicit11/base16 negatives;'
          'both special members remain unknown; no canonical transition or exact credit.')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
