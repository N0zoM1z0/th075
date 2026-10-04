#!/usr/bin/env python3
"""Replay R148 complete floor wrapper/carrier and independent default/SSE provenance."""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import tempfile

from capstone import Cs, CS_ARCH_X86, CS_MODE_32, CS_GRP_JUMP
from capstone.x86 import X86_OP_IMM

ROOT = Path(__file__).resolve().parents[1]
CONFIDENCE = 'complete-vendor-floor-carrier-default-sse-common-sdk-provenance'
LAYOUT_OBJECTS = [{'symbol': '_FloorMathLayoutProbe',
  'offset': 0,
  'size': 84,
  'storage_span': 84,
  'values': [4, 4, 8, 32, 0, 4, 8, 16, 24, 10, 1, 524319, 16, 768, 0, 256, 512, 768, 32, 1, 0]}]
LAYOUT_HEADERS = {'PlatformSDK/Include/BaseTsd.h',
 'PlatformSDK/Include/CGuid.h',
 'PlatformSDK/Include/CdErr.h',
 'PlatformSDK/Include/CommDlg.h',
 'PlatformSDK/Include/Dde.h',
 'PlatformSDK/Include/Ddeml.h',
 'PlatformSDK/Include/Dlgs.h',
 'PlatformSDK/Include/Guiddef.h',
 'PlatformSDK/Include/Imm.h',
 'PlatformSDK/Include/LZExpand.h',
 'PlatformSDK/Include/MMSystem.h',
 'PlatformSDK/Include/Mcx.h',
 'PlatformSDK/Include/MsXml.h',
 'PlatformSDK/Include/Nb30.h',
 'PlatformSDK/Include/OAIdl.h',
 'PlatformSDK/Include/ObjBase.h',
 'PlatformSDK/Include/ObjIdl.h',
 'PlatformSDK/Include/Ole2.h',
 'PlatformSDK/Include/OleAuto.h',
 'PlatformSDK/Include/OleIdl.h',
 'PlatformSDK/Include/PopPack.h',
 'PlatformSDK/Include/PrSht.h',
 'PlatformSDK/Include/PropIdl.h',
 'PlatformSDK/Include/PshPack1.h',
 'PlatformSDK/Include/PshPack2.h',
 'PlatformSDK/Include/PshPack4.h',
 'PlatformSDK/Include/PshPack8.h',
 'PlatformSDK/Include/Reason.h',
 'PlatformSDK/Include/Rpc.h',
 'PlatformSDK/Include/RpcAsync.h',
 'PlatformSDK/Include/RpcDce.h',
 'PlatformSDK/Include/RpcDceP.h',
 'PlatformSDK/Include/RpcNdr.h',
 'PlatformSDK/Include/RpcNsi.h',
 'PlatformSDK/Include/RpcNsip.h',
 'PlatformSDK/Include/RpcNtErr.h',
 'PlatformSDK/Include/ServProv.h',
 'PlatformSDK/Include/ShellAPI.h',
 'PlatformSDK/Include/StrAlign.h',
 'PlatformSDK/Include/Unknwn.h',
 'PlatformSDK/Include/UrlMon.h',
 'PlatformSDK/Include/WTypes.h',
 'PlatformSDK/Include/WinBase.h',
 'PlatformSDK/Include/WinCon.h',
 'PlatformSDK/Include/WinCrypt.h',
 'PlatformSDK/Include/WinDef.h',
 'PlatformSDK/Include/WinEFS.h',
 'PlatformSDK/Include/WinError.h',
 'PlatformSDK/Include/WinGDI.h',
 'PlatformSDK/Include/WinIoCtl.h',
 'PlatformSDK/Include/WinNT.h',
 'PlatformSDK/Include/WinNetWk.h',
 'PlatformSDK/Include/WinNls.h',
 'PlatformSDK/Include/WinPerf.h',
 'PlatformSDK/Include/WinReg.h',
 'PlatformSDK/Include/WinSCard.h',
 'PlatformSDK/Include/WinSmCrd.h',
 'PlatformSDK/Include/WinSock.h',
 'PlatformSDK/Include/WinSpool.h',
 'PlatformSDK/Include/WinSvc.h',
 'PlatformSDK/Include/WinUser.h',
 'PlatformSDK/Include/WinVer.h',
 'PlatformSDK/Include/Windows.h',
 'crt/src/cruntime.h',
 'crt/src/ctype.h',
 'crt/src/excpt.h',
 'crt/src/float.h',
 'crt/src/fpieee.h',
 'crt/src/malloc.h',
 'crt/src/math.h',
 'crt/src/stdarg.h',
 'crt/src/stddef.h',
 'crt/src/stdlib.h',
 'crt/src/string.h',
 'include/mmintrin.h',
 'include/tvout.h',
 'include/xmmintrin.h'}
METADATA_DIGESTS = {'functions': '8c82abb036ae7d4b27d72c25e932c71b6e0ed10f9722a54242631fb40442fd40',
 'auxiliary_bodies': '9021ca3bb305d42bb6f1db1dc05bc729cfbec0c5647b9b36241d84d26cb52a81',
 'anchors': 'dfb39533ed014a56554c8b659bcac934fe9c39d146b4e69eccde2edad66f7457',
 'state_data': '0bccf92dc58f21e117f4127719e0b26a34d3e1057870ce40d4c465e2378b5106',
 'common_globals': '6cf7ae12695c3ebfc54b96df14fd92cc2e2894e73f2c5fdccdeabb18cf88b29e',
 'common_alternatives': 'e27c1fa9b4182d91c1d698c0fafb74b1de70112ae005d9ce1443ff711e670372',
 'floor_protocol': '5685cc3d663ceb857b06b1c4d36e38d55ed1c542ce5d4d139dcc835be1192744',
 'register_contracts': '19ac8a8b2c9ebe65165850b190d1f863ac53736e1a84416e9be3c25b3a89602d',
 'code_carriers': '4e9146e9a45f1a0e3ecb7e3aca4addff9af8a29cce6cdd62f1735863b5c43f2b',
 'source_alternatives': '7552c284c0af2a03abf901e479be1220738be20db729ae1974f3704a80f60090',
 'extent_reconciliations': '472ae4bee3d919ca88270b12b28b442c48475cb849721272c7b2bc24d3299947',
 'retained_source_controls': '1f04f3a4ad7534880047ffe868337ad9ab44ce7491e7fdda39a63817bd0f3e50',
 'call_controls': 'b2b99a2d7fd100d1a837e278d80c564d2b88de055941a07ac40317ac3b4f05a5',
 'code_definitions': '937f9a0b68b89e420264162e94e6647ef0eb7bd2e849e6166e6093d0d97261a7',
 'state_uses': '2a1aa042839563b88bd5cacb319347ff82dcada3b42aefc4042eb99c0a7a1914'}

def metadata_digest(value):
    return hashlib.sha256(json.dumps(value, sort_keys=True, separators=(',', ':')).encode()).hexdigest()

def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result

prior = module('floor_prior', 'verify-power-math-origins.py')
carrier_prior = prior.carrier_prior
check_code_entry = prior.check_code_entry
whole_defining_section = prior.whole_defining_section
read_weak_reference = prior.read_weak_reference
decode_code = prior.decode_code
check_scope_records = prior.check_scope_records
resolve_state_reference = prior.resolve_state_reference
check_catalog_entry = prior.check_catalog_entry
object_code = prior.object_code
link_complete = prior.link_complete
check_alternative = prior.check_alternative

def manifest():
    m = json.loads((ROOT / 'config/floor-math-origin-evidence.json').read_text())
    identity = module('floor_math_identity', 'origin_reconciliation.py')
    if m['evidence_id'] != 'R148' or m['target_sha256'] != identity.TARGET:
        raise ValueError('floor-math target identity differs')
    return m

def verify_plan(m):
    rows = {r['address']:r for r in m['functions']}
    if len(m['functions']) != 1 or set(rows) != {'0x006439C0'}:
        raise ValueError('bounded complete floor cohort differs')
    row = rows['0x006439C0']
    if (row['coff_symbol'] != '_floor' or row['size'] != 64 or row['code_size'] != 64
            or row['ledger_size'] != 289 or row['decision'] != 'library'
            or row['extent_basis'] != 'function-auxiliary-record'
            or row['code_regions'] != [dict(offset=0,size=64)] or row['span_end'] != '0x006439FF'):
        raise ValueError('floor wrapper loses complete own AUX/whole carrier reconciliation')
    if any(m[k] for k in ('interior_labels','retained_labels','diagnostic_contexts','scope_tables',
                          'range_markers','initializer_registrations','callback_ranges','literal_controls',
                          'retained_thunks','probe_generated_data','probe_generated_code','source_weak_references')):
        raise ValueError('floor graph gains unsupported dependencies')
    if (len(m['auxiliary_bodies']) != 1 or len(m['anchors']) != 2 or len(m['state_data']) != 1
            or m['state_data'][0]['size'] != 80 or len(m['common_globals']) != 1
            or len(m['code_carriers']) != 1 or len(m['source_alternatives']) != 2
            or m['retained_controls'] != [dict(evidence_id='R146',manifest='power-math-origin-evidence.json'),
                                        dict(evidence_id='R139',manifest='floating-operation-origin-evidence.json')]
            or m['sdk_layout']['source_section_size'] != 84
            or m['sdk_layout']['objects'] != LAYOUT_OBJECTS
            or set(m['sdk_layout']['headers']) != LAYOUT_HEADERS or m['vendor_sources']):
        raise ValueError('floor full carrier/constants/SDK/retained inventory differs')
    aux = m['auxiliary_bodies'][0]
    if (aux['address'] != '0x00643A00' or aux['coff_symbol'] != '__floor_pentium4'
            or aux['size'] != 225 or aux['decision'] != 'library-control' or aux['ledger_size'] is not None
            or aux['extent_basis'] != 'function-auxiliary-record'):
        raise ValueError('floor SSE control loses complete own AUX or invents candidate credit')
    for key,digest in METADATA_DIGESTS.items():
        if metadata_digest(m[key]) != digest:
            raise ValueError('reviewed complete floor '+key+' inventory differs')
    graph = {**rows,**{r['address']:r for r in m['auxiliary_bodies']+m['anchors']}}
    for r in m['functions']+m['auxiliary_bodies']:
        if r['code_regions'] != [dict(offset=0,size=r['size'])] or r['indirect_calls'] or r['indirect_jumps']:
            raise ValueError('floor loses full code partition or gains unresolved dispatch')
        for b in r['relocation_bindings']:
            if b['target_kind'] == 'callee':check_code_entry(b,graph)
            elif b['target_kind'] != 'state' or b['type'] != 'DIR32':
                raise ValueError('floor field loses independent complete code/data provenance')
    check_floor_protocol(m,graph)
    return rows


def check_floor_protocol(m,graph):
    wrapper = graph['0x006439C0']; sse = graph['0x00643A00']
    witness = lambda row: {(w['mnemonic'],w['operands']) for w in row['instruction_witnesses']}
    if not {('cmp','dword ptr [0x68fba0], 0'),('je','0x64e980'),
            ('stmxcsr','dword ptr [esp + 4]'),('and','eax, 0x1f80'),('cmp','eax, 0x1f80'),
            ('fnstcw','word ptr [esp]'),('and','ax, 0x7f'),('cmp','ax, 0x7f'),
            ('lea','esp, [esp + 8]'),('jne','0x64e980'),('jmp','0x643a00')} <= witness(wrapper):
        raise ValueError('floor wrapper loses both real mask/default/SSE dispatch routes')
    if not {('movq','xmm0, qword ptr [esp + 4]'),('psrlq','xmm0, 0x34'),
            ('cmp','eax, 0x3ff'),('cmp','eax, 0x432'),('cmp','eax, 0xbff'),('cmp','eax, 0xc32'),
            ('ucomisd','xmm7, xmm7'),('mov','edx, 0x3ed'),('call','0x6485d7'),
            ('cmpltpd','xmm0, xmm1'),('andpd','xmm0, xmmword ptr [0x661190]'),
            ('subsd','xmm1, xmm0'),('fldz',''),('cmpltpd','xmm3, xmmword ptr [0x6611c0]'),
            ('orpd','xmm3, xmmword ptr [0x6611c0]'),('andpd','xmm3, xmmword ptr [0x6611b0]')} <= witness(sse):
        raise ValueError('floor SSE body loses full signed-fraction/zero/NaN/error protocol')
    if sse['body_facts']['returns'] != [dict(site=site,cleanup=0) for site in (
            '0x00643A52','0x00643A81','0x00643AB9','0x00643ABC','0x00643AE0')]:
        raise ValueError('floor SSE body loses a complete return/exception tail')
    table = m['state_data'][0]
    if (table['target_address'] != '0x00661190' or table['size'] != 80
            or table['source_anchor']['symbol'] != '_Bns' or table['source_anchor']['offset'] != 16
            or len(table['source_section']['definitions']) != 5 or table['relocations']):
        raise ValueError('floor constants lose the whole actual section/interior anchor')
    carrier = m['code_carriers'][0]
    if (carrier['size'] != 289 or carrier['address'] != '0x006439C0' or carrier['gaps']
            or carrier['components'] != [dict(owner='0x006439C0',offset=0,size=64),
                                         dict(owner='0x00643A00',offset=64,size=225)]):
        raise ValueError('floor carrier loses its complete contiguous own-AUX partition')


def check_retained_source(m,origins,functions):
    for row in m['anchors']:
        key = row['address']; origin = origins[key]
        if (key not in functions or origin['origin'] != row['origin']
                or origin['evidence_id'] != row['origin_evidence']
                or row['control_flow_basis'] != 'Independent complete runtime/archive controls replayed through R146/R139'):
            raise ValueError('floor retained complete default/error origin differs')
    for control in m['retained_source_controls']:
        previous = json.loads((ROOT/'config'/control['manifest']).read_text())
        row = next(r for r in m['anchors'] if r['address']==control['address'])
        old = next(r for r in previous['functions']+previous['anchors'] if r['address']==control['address'])
        for key in ('member_offset','coff_symbol','size','source_sha256','body_sha256'):
            if row[key] != old[key] or row[key] != control[key]:
                raise ValueError('floor loses full independent retained source owner')


def check_common_provenance(m,members,c,coff):
    previous = json.loads((ROOT/'config/power-math-origin-evidence.json').read_text())
    for row in m['common_globals']:
        proof = next(r for r in m['common_alternatives'] if r['symbol']==row['symbol'])
        old = next(r for r in previous['common_globals'] if r['symbol']==row['symbol'])
        if old != row or old != proof['retained_definition'] or proof['retained_evidence_id'] != 'R146':
            raise ValueError('floor SSE COMMON loses complete independent retained definition')
        actual = []
        for off,(_,data) in members.items():
            try:defs = coff.parse_symbols(data,c.coff_name)[1]
            except ValueError:continue
            actual.extend(dict(member_offset=off,source_definition=d) for d in defs
                          if d['symbol']==row['symbol'] and d['storage']==2
                          and (d['section']!=0 or d['offset']>0))
        if actual != proof['definitions'] or actual != [dict(member_offset=row['member_offset'],source_definition=row['source_definition'])]:
            raise ValueError('floor SSE COMMON has an unreviewed whole-archive alternative')

def check_ledger(row, function, origin):
    if (int(function['size']) != row['size'] or function['span_end'] != row['span_end']
            or function['source_file'] or function['match_percent'] != '0.00'
            or function['calling_convention'] or function['signature']):
        raise ValueError('floor-math loses complete origin-only extent')
    if (origin['evidence_id'] != 'R148' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] != row.get('proposed_name',row['coff_symbol'])):
        raise ValueError('floor-math canonical complete library acceptance differs')

def check_probe_generated(data,path,m,comparison,coff,old,decoder,facts):
    definitions = coff.parse_symbols(data,comparison.coff_name)[1]
    count = struct.unpack_from('<H',data,2)[0]
    headers = [struct.unpack_from('<8sIIIIIIHHI',data,20+i*40) for i in range(count)]
    for row in m['probe_generated_data']:
        raw,desc,anchor = whole_defining_section(data,row['symbol'],comparison,coff)
        if anchor!=row['source_anchor']:
            raise ValueError('cold model whole data source anchor differs')
        if desc != row['source_section'] or hashlib.sha256(raw).hexdigest() != row['source_sha256']:
            raise ValueError('cold natural EH model loses whole generated defining data')
    for row in m['probe_generated_code']:
        entry = next(d for d in definitions if d['symbol']==row['coff_symbol'] and d['section']>0)
        header = headers[entry['section']-1]
        section_defs = [d for d in definitions if d['section']==entry['section'] and d['storage'] in (2,3,6) and not d['symbol'].startswith('.')]
        if (entry != row['source_definition'] or entry['offset'] != 0 or header[3] != row['size']
                or f'0x{header[9]:08X}' != row['flags'] or section_defs != row['source_definitions']
                or row['extent_basis'] != 'whole-defining-code-section-without-AUX'):
            raise ValueError('cold natural EH carrier loses complete no-AUX defining code section')
        symbol_offset,symbol_count = struct.unpack_from('<II',data,8)
        string_offset = symbol_offset + symbol_count*18
        strings = data[string_offset:string_offset+struct.unpack_from('<I',data,string_offset)[0]]
        index = 0
        auxiliary = None
        while index < symbol_count:
            name,_,_,_,_,aux = struct.unpack_from('<8sIhHBB',data,symbol_offset+index*18)
            if comparison.coff_name(name,strings) == row['coff_symbol']:
                auxiliary = aux
                break
            index += 1+aux
        if auxiliary != 0:
            raise ValueError('cold model EH carrier no-AUX provenance differs')
        raw,fields = comparison.object_function(path,row['coff_symbol'],row['size'])
        ins = list(decoder.disasm(raw,0))
        metadata = [{k:f[k] for k in ('offset','type','symbol','addend','local_symbol_offset')} for f in fields]
        if (sum(i.size for i in ins) != len(raw) or metadata != row['relocation_metadata']
                or hashlib.sha256(raw).hexdigest() != row['source_sha256']
                or facts.body_facts(ins) != row['body_facts']):
            raise ValueError('cold natural EH carrier loses full code/typed metadata')
    # Every initialized model section except the whole SDK layout must appear;
    # this prevents accepting a descriptor prefix while dropping its neighbours.
    expected = {next(d['section'] for d in definitions if d['symbol']==r['symbol'])
                for r in m['probe_generated_data']}
    layout_section = next(d['section'] for d in definitions if d['symbol']=='_FloorMathLayoutProbe')
    actual = {i+1 for i,h in enumerate(headers) if h[3] and h[9]&0x40 and h[9]&0x40000000
              and not h[9]&0x20000000 and h[0].rstrip(b'\0') not in (b'.debug$S',b'.debug$T',b'.debug$F',b'.drectve')}
    if actual != expected | {layout_section}:
        raise ValueError('cold natural EH model loses an entire generated initialized section')
    owned = {next(d['section'] for d in definitions if d['symbol']==r['coff_symbol'] and d['section']>0) for r in m['call_controls']}
    carriers = {next(d['section'] for d in definitions if d['symbol']==r['coff_symbol'] and d['section']>0) for r in m['probe_generated_code']}
    code_sections = {i+1 for i,h in enumerate(headers) if h[3] and h[9]&0x20}
    if owned & carriers or owned | carriers != code_sections:
        raise ValueError('cold natural model loses a complete generated code section')

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only',action='store_true')
    args = parser.parse_args()
    old = module('floor_math_old','verify-runtime-error-origins.py')
    c = module('floor_math_target','compare-coff-function.py')
    archive_reader = module('floor_math_archive','verify-runtime-origins.py')
    coff = module('floor_math_coff','coff_data.py')
    startup = module('floor_math_geometry','verify-startup-dependency-origins.py')
    record = module('floor_math_ledger','verify-vendor-record-origins.py')
    facts = module('floor_math_facts','verify-game-lifetime-origins.py')
    imports_module = module('floor_math_imports','verify-import-origins.py')
    literal = module('floor_math_scalar','verify-runtime-external-origins.py')
    sections = module('floor_math_sections','verify-compiler-origins.py')
    target = c.verified_target(); m = manifest(); rows = verify_plan(m)
    functions = {r['address']:r for r in record.rows('functions.csv')}
    origins = {r['address']:r for r in record.rows('function-origins.csv')}
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        key = row['address']; a = int(key,16)
        if row['decision'] == 'library-control' and key in functions:
            raise ValueError('complete floor-math source control gains an invented candidate')
        actual = {k for k in functions if a < int(k,16) < a + row['size']}
        expected = {r['address'] for r in m['interior_labels']+m['retained_labels'] if r['parent'] == key}
        if actual != expected:
            raise ValueError('floor-math complete primary loses an actual interior candidate')
    archive = (ROOT / '.tools/msvc710/Vc7/lib/libcmt.lib').read_bytes()
    if hashlib.sha256(archive).hexdigest() != m['archive_sha256']:
        raise ValueError('pinned whole CRT archive differs')
    members = {off:(name,data) for off,name,data in archive_reader.archive_members(archive)}
    def member(row):
        name,data = members[row['member_offset']]
        if name != row['member'] or hashlib.sha256(data).hexdigest() != row['member_sha256']:
            raise ValueError('complete source member identity differs')
        return data
    target_sections = sections.sections(target); imports = imports_module.pe_imports(target,c)
    state_map = {}; global_state = {}
    for row in m['state_data']:
        raw,desc,anchor = whole_defining_section(member(row),row['symbol'],c,coff)
        if anchor != row['source_anchor']:
            raise ValueError('whole source data changes its actual interior address-point anchor')
        a = int(row['target_address'],16)
        if desc != row['source_section'] or desc['size'] != row['size']:
            raise ValueError('floor-math whole defining data topology differs')
        if row['writable'] != bool(int(desc['flags'],16)&0x80000000):
            raise ValueError('floor-math source data mutability differs')
        for d in desc['definitions']:
            state_map[(row['member_offset'],d['symbol'])] = a + d['offset']
            if d['storage'] == 2:
                global_state.setdefault(d['symbol'],set()).add(a + d['offset'])
        if raw is None:
            if (not int(desc['flags'],16)&0x80 or desc['relocations']
                    or startup.zero_fill_region(target,a,row['size']) != row['zero_fill_region']):
                raise ValueError('floor-math state lacks complete loader zero-fill provenance')
            continue
        actual = c.pe_bytes_at(target,a,len(raw)); linked = bytearray(raw)
        if len(desc['relocations']) != len(row['relocations']):
            raise ValueError('floor-math whole initialized data fields differ')
        for field,binding in zip(desc['relocations'],row['relocations']):
            if {k:binding[k] for k in field} != field:
                raise ValueError('floor-math initialized data relocation metadata differs')
            struct.pack_into('<I',linked,field['offset'],(int(binding['target_address'],16)+field['addend'])&0xffffffff)
        if (linked != actual or hashlib.sha256(raw).hexdigest() != row['source_sha256']
                or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
            raise ValueError('floor-math complete defining data source/target comparison differs')
        if row['writable']:
            if not any(base<=a and a+row['size']<=base+size and flags&0x80000000 and not flags&0x20000000 for base,size,flags in target_sections):
                raise ValueError('floor-math state loses whole writable target storage')
        else:
            literal.check_scalar(linked,actual,row['size'],target_sections,a)
    for row in m['common_globals']:
        definitions=coff.parse_symbols(member(row),c.coff_name)[1]
        actual=next((d for d in definitions if d['symbol']==row['symbol'] and d['section']==0),None)
        a=int(row['target_address'],16)
        if actual!=row['source_definition'] or actual['offset']!=row['size'] or startup.zero_fill_region(target,a,row['size'])!=row['zero_fill_region']:
            raise ValueError('complete COMMON definition/loader zero-fill differs')
        state_map[(row['member_offset'],row['symbol'])]=a
        global_state.setdefault(row['symbol'],set()).add(a)
    for use in m['state_uses']:
        state_map[(use['member_offset'],use['symbol'])] = resolve_state_reference(use,state_map,global_state)
    check_common_provenance(m,members,c,coff)
    check_retained_source(m,origins,functions)
    decoder = Cs(CS_ARCH_X86,CS_MODE_32); decoder.detail = True
    scratch = ROOT / 'build/origin-floor-math-verification'; scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        path = Path(temporary)/'VendorMember.obj'
        layout = m['sdk_layout']; probe = ROOT/layout['probe']
        profile = old.PROFILE+['/D_CRTBLD','/D_MT','/I','.tools/msvc710/Vc7/crt/src','/Zc:wchar_t']
        if (layout['profile'] != profile or hashlib.sha256(probe.read_bytes()).hexdigest() != layout['probe_sha256']
                or set(layout['headers']) != LAYOUT_HEADERS):
            raise ValueError('natural floor-math control source/profile/headers differ')
        for filename,digest in layout['headers'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest() != digest:
                raise ValueError('pinned floor-math control header differs')
        subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(probe),str(path),*profile],cwd=ROOT,capture_output=True,text=True,check=True)
        data = path.read_bytes(); defs = coff.parse_symbols(data,c.coff_name)[1]
        entry = next(d for d in defs if d['symbol'] == '_FloorMathLayoutProbe')
        layout_section = entry['section']
        raw,names = coff.readonly_section(data,layout_section,c.coff_name)
        if (names != layout['definitions'] or len(raw) != layout['source_section_size']
                or hashlib.sha256(raw).hexdigest() != layout['source_sha256']):
            raise ValueError('cold complete natural floor-math data objects/alignment differ')
        for obj in layout['objects']:
            entry = next(d for d in defs if d['symbol'] == obj['symbol'])
            if (entry['offset'] != obj['offset'] or entry['section'] != layout_section
                    or list(struct.unpack_from('<'+'I'*(obj['size']//4),raw,obj['offset'])) != obj['values']):
                raise ValueError('cold natural exception/thread SDK offsets or ABI constants differ')
        for filename,digest in m['vendor_sources'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest()!=digest:
                raise ValueError('pinned complete floor-math vendor source differs')
        for control in m['call_controls']:
            source,fields=c.object_function(path,control['coff_symbol']);ins=list(decoder.disasm(source,0))
            metadata=[{k:f[k] for k in ('offset','type','symbol','addend','local_symbol_offset')} for f in fields]
            if (len(source)!=control['size'] or metadata!=control['relocation_metadata']
                    or hashlib.sha256(source).hexdigest()!=control['source_sha256']
                    or facts.body_facts(ins)!=control['body_facts']
                    or [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]!=control['instructions']):
                raise ValueError('cold complete floor-math ABI/SEH/C++ controls differ')
        check_probe_generated(data,path,m,c,coff,old,decoder,facts)
        observed_catalog = []
        decoded = {}
        for row in m['functions']+m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']:
            a = int(row['address'],16); key = row['address']
            if row['decision'] == 'library' and not args.evidence_only:
                check_ledger(row,functions[key],origins[key])
            data = member(row); path.write_bytes(data)
            source,fields = object_code(path,row,c,coff)
            actual = c.pe_bytes_at(target,a,row['size'])
            defs = coff.parse_symbols(data,c.coff_name)[1]
            primary = next(d for d in defs if d['symbol'] == row['coff_symbol'] and d['section']>0)
            if (primary != row['source_definition'] or len(source) != row['size']
                    or hashlib.sha256(source).hexdigest() != row['source_sha256']
                    or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
                raise ValueError('floor-math complete own source extent/hash differs')
            if row['decision'] == 'anchor':
                old.compare_fields(source,fields,actual,a,row['relocation_bindings'],c)
            elif link_complete(source,fields,row,state_map,imports,startup,graph,m['code_definitions']) != actual:
                raise ValueError('complete power relocated source/target bytes differ')
            if [f['local_symbol_offset'] for f in fields] != [b['local_symbol_offset'] for b in row['relocation_bindings']]:
                raise ValueError('floor-math full local typed field provenance differs')
            for d in defs:
                if (d['section'] == primary['section'] and primary['offset'] <= d['offset'] < primary['offset']+row['size']
                        and d['storage'] in (2,3,6) and not d['symbol'].startswith('.')):
                    observed_catalog.append(dict(owner=key,member_offset=row['member_offset'],source_definition=d,
                                                 target_address=f"0x{a+d['offset']-primary['offset']:08X}",
                                                 source_offset=d['offset']-primary['offset']))
            ins = decode_code(row,actual,a,decoder); decoded[key] = ins
            if sum(i.size for i in ins) != row['code_size'] or facts.body_facts(ins) != row['body_facts']:
                raise ValueError('floor-math whole code instruction/control-flow inventory differs')
            witnesses = [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]
            branches = [dict(site=f'0x{i.address:08X}',target=f'0x{i.operands[0].imm:08X}') for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type == X86_OP_IMM]
            calls = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.mnemonic == 'call' and i.operands[0].type != X86_OP_IMM]
            jumps = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type != X86_OP_IMM]
            if (witnesses != row['instruction_witnesses'] or branches != row['branches']
                    or calls != row['indirect_calls'] or jumps != row['indirect_jumps']):
                raise ValueError('floor-math complete branch/API/ABI/dispatch inventory differs')
            if row['decision'] in ('anchor','pending'):
                continue
            for b in row['relocation_bindings']:
                if b['target_kind'] == 'import':
                    startup.check_import_binding(b,imports)
                elif b['target_kind'] == 'state' and (b['type'] != 'DIR32' or state_map.get((row['member_offset'],b['symbol'])) != int(b['target_address'],16)):
                    raise ValueError('floor-math field lacks member-local/whole strong data provenance')
        for scope in m['scope_tables']:
            data_row = next(r for r in m['state_data'] if r['symbol']==scope['symbol'] and r['member_offset']==scope['member_offset'])
            check_scope_records(scope,data_row,c.pe_bytes_at(target,int(scope['address'],16),scope['size']),graph,decoded)
        for reference in m['source_weak_references']:
            actual_reference = read_weak_reference(members[reference['member_offset']][1],reference['symbol'],c,coff,reference['member_offset'])
            if actual_reference != reference:
                raise ValueError('actual weak source COFF AUX/search/fallback differs')
            strong = []
            for off,(_,data) in members.items():
                try:definitions = coff.parse_symbols(data,c.coff_name)[1]
                except ValueError:continue
                strong.extend(dict(member_offset=off,source_definition=d) for d in definitions if d['symbol']==reference['symbol'] and d['section']>0 and d['storage']==2)
            if strong != reference['strong_archive_definitions']:
                raise ValueError('weak reference gains an unreviewed strong archive alternative')
        for row in m['state_data']:
            for b in row['relocations']:
                if 'source_weak_reference' in b:
                    ref = b['source_weak_reference']
                    if (ref not in m['source_weak_references'] or ref['member_offset']!=row['member_offset']
                            or b['symbol']!=ref['symbol'] or b['code_entry']['source_definition']!=ref['fallback_definition']):
                        raise ValueError('weak vtable callback loses actual fallback source definition')
        catalog_key = lambda r: (r['owner'],r['source_definition']['symbol'],r['member_offset'],r['source_offset'])
        if sorted(observed_catalog,key=catalog_key) != sorted(m['code_definitions'],key=catalog_key):
            raise ValueError('floor-math code entry catalog differs from actual complete source definitions')
        bindings = [b for r in m['functions']+m['auxiliary_bodies'] for b in r['relocation_bindings'] if 'code_entry' in b]
        bindings += [b for r in m['state_data'] for b in r['relocations'] if 'code_entry' in b]
        for b in bindings:
            check_catalog_entry(b,observed_catalog)
        for row in m['functions']+m['auxiliary_bodies']:
            a = int(row['address'],16); ins = decoded[row['address']]; starts = {i.address for i in ins}
            edges = {e['site']:e for e in row['direct_edges']}; observed_sites = set()
            # Direct source branches without relocations must retain the same
            # section and actual complete target owner, including shared tails.
            path.write_bytes(member(row)); code,_ = object_code(path,row,c,coff)
            source_ins = {i.address-row['source_definition']['offset']:i for i in decode_code(row,code,row['source_definition']['offset'],decoder)}
            for i in ins:
                if ((i.mnemonic != 'call' and not i.group(CS_GRP_JUMP)) or not i.operands
                        or i.operands[0].type != X86_OP_IMM):
                    continue
                dest = i.operands[0].imm
                if a <= dest < a+row['size']:
                    if dest not in starts:
                        raise ValueError('floor-math local transfer does not reach an actual instruction start')
                    continue
                site = f'0x{i.address:08X}'; observed_sites.add(site); edge = edges.get(site)
                if not edge or int(edge['target'],16) != dest:
                    raise ValueError('floor-math direct transfer lacks full defining edge provenance')
                if edge['basis'] == 'typed-REL32':
                    field = next((b for b in row['relocation_bindings'] if b['type'] == 'REL32' and b['offset'] == i.address-a+i.imm_offset),None)
                    if (not field or field['target_kind'] != 'callee' or field['offset'] != edge['field_offset']
                            or field['target_address'] != edge['target'] or field['code_entry'] != edge['code_entry']):
                        raise ValueError('floor-math direct transfer loses its actual typed field')
                    owner = graph[field['code_entry']['owner']]
                else:
                    owner = graph[edge['owner']]
                    if source_ins[i.address-a].operands[0].imm != edge['source_target_offset']:
                        raise ValueError('floor-math same-section transfer changes its source-relative target')
                if dest not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('floor-math shared/typed entry does not reach an actual full-owner instruction')
            if observed_sites != set(edges):
                raise ValueError('floor-math complete direct edge inventory differs')
        for data in m['state_data']:
            for b in data['relocations']:
                if b['target_kind']=='state':
                    resolve_state_reference(dict(member_offset=data['member_offset'],symbol=b['symbol'],target_address=b['target_address']),state_map,global_state)
                    continue
                owner = graph[b['code_entry']['owner']]
                if int(b['target_address'],16) not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('floor-math data pointer does not reach a complete actual code entry')
        for carrier in m['code_carriers']:
            data = member(carrier)
            carrier_prior.verify_code_carrier(carrier,data,target,c,coff,old,graph)
            raw,fields = carrier_prior.whole_code_section(data,carrier,c,coff)
            if link_complete(raw,fields,carrier,state_map,imports,startup,graph,m['code_definitions']) != c.pe_bytes_at(target,int(carrier['address'],16),carrier['size']):
                raise ValueError('whole power carrier loses complete independently relocated bytes')
        for alternative in m['source_alternatives']:
            check_alternative(alternative,path,members,c,coff,target)
    for script in ('verify-power-math-origins.py','verify-floating-operation-origins.py'):
        result = subprocess.run([str(ROOT/'scripts/repo-python'),'scripts/'+script],cwd=ROOT,capture_output=True,text=True)
        if result.returncode:
            raise ValueError('retained independent full R146/R139 replay failed: '+result.stderr[-1500:])
    print('R148 origins OK: complete 64-byte floor wrapper / three fields and complete 225-byte non-inventory SSE owner / seven fields in whole 289-byte defining carrier; complete 80-byte five-constant section from real base at interior Bns anchor; unique independently retained SSE COMMON; both complete default and libm-error anchors / 865 bytes / 37 fields preserve prior origins; whole modf/ceil alternative carriers retain same-shaped wrapper ambiguity until full default/SSE operation binding; cold actual 84-byte SDK layout / six controls / 180 bytes / six fields / 77 pinned headers / all emitted code/data sections; full retained R146/R139 cold replay; local origin-only acceptance, no source or exact credit.')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
