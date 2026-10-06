#!/usr/bin/env python3
"""Replay original SDK compilation/frame metadata without assigning ownership."""
import json
from pathlib import Path
import struct

ROOT = Path(__file__).resolve().parents[1]
EVIDENCE = 'config/sdk-compilation-witness-audit-evidence.json'
MANIFEST_SHA256 = 'e82feea7dab8ed0065b7d5a3073db5f0daa3515646dcdbc8907c8f8e4171adfd'

# Reuse the independently checked CodeView/COFF readers; change no old proof.
import importlib.util
spec = importlib.util.spec_from_file_location('sdk_compilation_prior', ROOT / 'scripts/verify-sdk-string-buffer-review.py')
V = importlib.util.module_from_spec(spec)
spec.loader.exec_module(V)


def sections(body):
    machine, count, _, pointer, symbols, optional, flags = struct.unpack_from('<HHIIIHH', body)
    if machine != 0x14c or optional or 20 + count * 40 > len(body):
        raise ValueError('invalid original SDK COFF section table')
    result = []
    for n in range(1, count + 1):
        h = struct.unpack_from('<8sIIIIIIHHI', body, 20 + 40 * (n - 1))
        uninitialized = not h[4] and h[9] & 128 and not h[9] & (32 | 64)
        if h[3] and not uninitialized and (not h[4] or h[4] + h[3] > len(body)):
            raise ValueError('truncated initialized SDK section')
        if h[7] and (not h[5] or h[5] + 10 * h[7] > len(body)):
            raise ValueError('truncated SDK relocation table')
        result.append(dict(section=n, name=h[0].rstrip(b'\0').decode('ascii'), size=h[3],
                           raw_offset=h[4], relocation_offset=h[5], relocations=h[7], flags=h[9]))
    return result


def resource_debug(raw):
    """CVTRES emits C7 framing and the same actual COMPILE2_ST payload layout."""
    if len(raw) < 4 or struct.unpack_from('<I', raw)[0] != 1:
        raise ValueError('resource CodeView signature differs')
    records, at = [], 4
    while at < len(raw):
        if at + 4 > len(raw):
            raise ValueError('truncated resource symbol header')
        size, kind = struct.unpack_from('<HH', raw, at)
        end = at + size + 2
        if size < 2 or end > len(raw):
            raise ValueError('truncated resource symbol payload')
        payload = raw[at+4:end]
        r = dict(offset=at, length=size, kind=f'0x{kind:04X}', payload_hex=payload.hex())
        if kind == 0x0009:
            if len(payload) < 5 or 5 + payload[4] != len(payload):
                raise ValueError('resource object-name framing differs')
            r.update(signature=struct.unpack_from('<I', payload)[0], object=payload[5:].decode('ascii'))
        elif kind == 0x1013:
            r['compile'] = V.compile_record(kind, payload)
        else:
            raise ValueError('new resource source/type witness requires review')
        records.append(r)
        at = end
    if [r['kind'] for r in records] != ['0x0009', '0x1013']:
        raise ValueError('whole resource object/compiler stream differs')
    return dict(signature=1, size=len(raw), sha256=V.digest(raw), records=records)


def frame(raw):
    if len(raw) != 16:
        raise ValueError('FPO record is not its whole16-byte extent')
    start, size, locals_count, params, prolog, flags = struct.unpack('<IIIHBB', raw)
    return dict(start_addend=start, procedure_size=size, locals_dwords=locals_count,
                parameters_dwords=params, prolog_bytes=prolog, saved_registers=flags & 7,
                has_seh=bool(flags & 8), uses_bp=bool(flags & 16), reserved=bool(flags & 32), frame_type=flags >> 6)


def resource_inventory(body, headers):
    """Preserve CVTRES's short-name symbol table and literal zero string size."""
    pointer, count = struct.unpack_from('<II', body, 8)
    end = pointer + 18 * count
    if end + 4 != len(body) or body[end:] != b'\0\0\0\0':
        raise ValueError('original CVTRES zero string table differs')
    symbols, i = [], 0
    while i < count:
        raw, value, section, typ, storage, aux = struct.unpack_from('<8sIhHBB', body, pointer + 18*i)
        if raw[:4] == b'\0\0\0\0' or i + aux >= count:
            raise ValueError('unexpected resource long-name/aux format')
        symbols.append(dict(index=i, symbol=raw.rstrip(b'\0').decode('ascii'), offset=value,
                            section=section, type=typ, storage=storage, aux_count=aux,
                            aux_hex=body[pointer+18*(i+1):pointer+18*(i+1+aux)].hex()))
        i += aux + 1
    inventory = []
    for h in headers:
        if h['flags'] & 32:
            raise ValueError('resource unexpectedly contains a code/type owner')
        raw = body[h['raw_offset']:h['raw_offset']+h['size']]
        at, n = h['relocation_offset'], h['relocations']
        relocations = [dict(offset=o, symbol_index=s, type_id=t) for o, s, t in
                       (struct.unpack_from('<IIH', body, at + 10*i) for i in range(n))]
        inventory.append(dict(header=h, sha256=V.digest(raw), relocations=relocations))
    return dict(symbols=symbols, string_table_size=0, sections=inventory)


def survey(plan):
    members = V.archive(plan['archive'], plan['archive_sha256'])
    units = []
    for off, (name, body) in members.items():
        if len(body) < 20 or body[:2] != b'\x4c\x01':
            continue
        headers = sections(body)
        unit = dict(member_offset=off, member=name, member_sha256=V.digest(body),
                    section_count=len(headers), debug=[], frames=[])
        defs = V.CO.parse_symbols(body, V.C.coff_name)[1] if off != 2148824 else []
        for h in headers:
            if not h['name'].startswith('.debug') or not h['size']:
                continue
            raw = body[h['raw_offset']:h['raw_offset']+h['size']]
            if h['name'] == '.debug$S':
                if h['relocations']:
                    raise ValueError('unexpected source/compiler debug relocation')
                unit['debug'].append(dict(header=h, stream=resource_debug(raw) if off == 2148824 else V.source_debug(raw)))
            elif h['name'] == '.debug$F':
                actual, fields, source = V.E.section_carrier(body, h['section'], V.C, V.CO)
                f = fields[0] if len(fields) == 1 else None
                if f is None or f['offset'] != 0 or f['type_id'] != 7 or f['addend'] != 0:
                    raise ValueError('FPO loses its one actual DIR32NB source field')
                defined = [d for d in defs if d['symbol'] == f['symbol'] and d['type'] == 32
                           and d['storage'] in [2, 3] and d['section'] > 0]
                if len(defined) != 1:
                    raise ValueError('FPO source field lacks one actual same-unit definition')
                definition = defined[0]
                code = headers[definition['section'] - 1]
                decoded = frame(actual)
                if definition['offset'] != 0 or not code['flags'] & 32 or decoded['procedure_size'] != code['size']:
                    raise ValueError('whole FPO/code section extent disagrees')
                unit['frames'].append(dict(section=h['section'], sha256=V.digest(raw), field=f,
                                           definition=definition, code_size=code['size'], frame=decoded,
                                           source_aux=source['aux_records']))
            else:
                raise ValueError('new SDK debug/type section requires independent review')
        if off == 2148824:
            unit['resource'] = resource_inventory(body, headers)
        units.append(unit)
    return units


def candidate_review(plan, units, target):
    members = V.archive(plan['archive'], plan['archive_sha256'])
    indexed = {u['member_offset']: u for u in units}
    result = []
    for r in plan['candidates']:
        name, body = members[r['member_offset']]
        raw, fields, source = V.E.section_carrier(body, r['section'], V.C, V.CO)
        definitions = [d for d in source['definitions'] if d['type'] == 32 and d['storage'] == 2]
        symbol = r['symbol']
        if len(raw) != int(r['function']['size']) or not any(d['symbol'] == symbol and d['offset'] == 0 for d in definitions):
            raise ValueError('pending SDK member is cropped or loses its actual source definition')
        frames = [f for f in indexed[r['member_offset']]['frames'] if f['definition']['symbol'] == symbol]
        if len(frames) != 1 or frames[0]['frame']['procedure_size'] != len(raw):
            raise ValueError('pending SDK member lacks its entire independently framed source extent')
        native = V.C.pe_bytes_at(target, int(r['function']['address'], 16), len(raw))
        mask = set()
        for f in fields:
            if f['type_id'] not in [6, 20] or f['offset'] < 0 or f['offset'] + 4 > len(raw):
                raise ValueError('pending SDK diagnostic has an unsupported actual field')
            extent = set(range(f['offset'], f['offset'] + 4))
            if mask & extent:
                raise ValueError('pending SDK diagnostic fields overlap')
            mask |= extent
        if any(a != b for i, (a, b) in enumerate(zip(raw, native)) if i not in mask) or V.digest(native) != r['body_sha256']:
            raise ValueError('whole pending SDK body/current hash differs')
        result.append(dict(address=r['function']['address'], member=name, source=source, fields=fields,
                           source_sha256=V.digest(raw), body_sha256=V.digest(native), frame=frames[0],
                           debug=indexed[r['member_offset']]['debug'], comparison='whole field-excluded discovery; no origin/exact credit'))
    return result


def compact_units(units):
    """Pin every decoded frame/field while keeping the public audit readable."""
    return [dict({k: value for k, value in u.items() if k != 'frames'},
                 frame_inventory=dict(count=len(u['frames']),
                                      metadata_sha256=V.PRIOR.metadata_digest(u['frames']),
                                      complete_code_bytes=sum(f['code_size'] for f in u['frames']))) for u in units]


def verify_scope(plan):
    units = plan['units']
    if len(units) != 146 or sum(u['frame_inventory']['count'] for u in units) != 2751 or sum(len(u['debug']) for u in units) != 137:
        raise ValueError('complete original SDK metadata corpus is omitted')
    if len(plan['candidates']) != 19 or any(r['origin']['origin'] != 'unknown' for r in plan['candidates']):
        raise ValueError('unresolved cohort is omitted or forcibly assigned ownership')
    candidates = {r['function']['address']: r for r in plan['candidates']}
    if len(candidates) != 19 or sum(int(r['function']['size']) for r in candidates.values()) != 1298:
        raise ValueError('literal whole nineteen-member cohort is substituted')
    if len(plan['reviews']) != 19 or {r['address'] for r in plan['reviews']} != set(candidates):
        raise ValueError('pending source/frame correspondence is omitted or duplicated')
    for r in plan['reviews']:
        size = int(candidates[r['address']]['function']['size'])
        if (r['source']['size'] != size or r['frame']['frame']['procedure_size'] != size
                or r['comparison'] != 'whole field-excluded discovery; no origin/exact credit'):
            raise ValueError('full source/frame extent is cropped or diagnostic gains acceptance')
    if plan['decision'] != 'unknown; no canonical transition or exact credit':
        raise ValueError('metadata absence becomes unsupported ownership/exact evidence')


def main():
    path = ROOT / EVIDENCE
    if V.digest(path.read_bytes()) != MANIFEST_SHA256:
        raise ValueError('immutable complete SDK compilation witness audit differs')
    plan = json.loads(path.read_text())
    verify_scope(plan)
    for path, sha in plan['retained_sha256'].items():
        if V.digest((ROOT / path).read_bytes()) != sha:
            raise ValueError('retained original source/control proof differs: ' + path)
    functions, origins = ({r['address']: r for r in V.rows(n)} for n in ['functions.csv', 'function-origins.csv'])
    for name, sha in plan['canonical_sha256'].items():
        if V.PRIOR.metadata_digest(V.rows(name)) != sha:
            raise ValueError('unresolved metadata audit changes canonical state')
    documents = {}
    for r in plan['candidates']:
        a = r['function']['address']
        if functions.get(a) != r['function'] or origins.get(a) != r['origin']:
            raise ValueError('literal pending SDK pair differs')
        for ref in r['references']:
            p = ROOT / ref['path']
            if ref['path'] not in documents:
                raw = p.read_bytes()
                documents[ref['path']] = (V.digest(raw), json.loads(raw))
            sha, value = documents[ref['path']]
            if sha != ref['manifest_sha256']:
                raise ValueError('old complete alternative proof differs')
            for key in ref['trail']:
                value = value[key]
            if V.PRIOR.metadata_digest(value) != ref['record_sha256']:
                raise ValueError('old complete alternative record is substituted')
    target = V.C.verified_target()
    if V.digest(target) != plan['target_sha256']:
        raise ValueError('pinned target identity differs')
    actual = survey(plan)
    if compact_units(actual) != plan['units'] or candidate_review(plan, actual, target) != plan['reviews']:
        raise ValueError('complete source/compiler/frame/candidate witness proof differs')
    print('R265 witness audit OK:all146 original SDK COFF units;136 whole C11 object/compiler streams and complete C7 CVTRES resource stream;'
          'all2751 whole FPO16 entries bind actual same-unit complete code extents;'
          'nineteen full pending SDK bodies/source sections/current pairs/old alternatives retained;'
          'no private type/declaration witness, no ownership transition or exact credit.')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
