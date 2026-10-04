#!/usr/bin/env python3
"""Replay R145 complete small-block heap integrity origin and full vendor C reproduction."""
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
CONFIDENCE = 'complete-vendor-small-heap-common-sdk-cold-source-provenance'
LAYOUT_OBJECTS = [{'symbol': '_SmallHeapIntegrityLayoutProbe',
  'offset': 0,
  'size': 152,
  'storage_span': 152,
  'values': [4,
             4,
             20,
             0,
             4,
             8,
             12,
             16,
             16836,
             0,
             4,
             68,
             196,
             324,
             516,
             0,
             4,
             8,
             0,
             4,
             12,
             0,
             4,
             8,
             4,
             0,
             16,
             4096,
             32768,
             1048576,
             32,
             8,
             12,
             16,
             4080,
             1024,
             4,
             4]}]
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
 'crt/src/stdarg.h',
 'crt/src/stddef.h',
 'crt/src/stdlib.h',
 'crt/src/string.h',
 'crt/src/winheap.h',
 'include/tvout.h'}
METADATA_DIGESTS = {'functions': '378c6c97e841209bb2da2643a9c37eb6192a9df6e98b7e1176f549810100b118',
 'common_globals': '4632fbe151cb2fd233ddce383c2f94c9a620cfe22ca03eb15ebe72a5a0de7021',
 'common_alternatives': '01df441db843ef73fab2244fe6371a2b81fe880c8ad9fd940cbbec3e0f907d67',
 'heap_protocol': '10f694476dac713ba176d82180153eb2cf9b80b050bb1753082396f84f69ced7',
 'register_contracts': 'e75565279b33da4f9cc8bcd8638daac7465319b26902dcb71a4b3fa849cc7e21',
 'vendor_reproduction': '93e14e4ea187049fca8dad463da2aeacd7d1a02a5cbb02e623d96cb2111c45fe',
 'call_controls': '24ed23f47765bb41cdc04e853935dcb8b4391a51723bb91cecef603fa9e5541e',
 'code_definitions': '89e36cd973031fdbe02a35b5f91804fa05da331edf5c6fff358b26a94237dce9',
 'state_uses': '5d529d6ba69d96b9a29c17771faba7f0b8c19ff6147176b9839fc72349979360'}

def metadata_digest(value):
    return hashlib.sha256(json.dumps(value, sort_keys=True, separators=(',', ':')).encode()).hexdigest()

def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result

prior = module('small_heap_prior', 'verify-standard-exception-origins.py')
check_code_entry = prior.check_code_entry
whole_defining_section = prior.whole_defining_section
read_weak_reference = prior.read_weak_reference
decode_code = prior.decode_code
check_scope_records = prior.check_scope_records
resolve_state_reference = prior.resolve_state_reference
check_catalog_entry = prior.check_catalog_entry
object_code = prior.object_code

def manifest():
    m = json.loads((ROOT / 'config/small-heap-integrity-origin-evidence.json').read_text())
    identity = module('small_heap_identity', 'origin_reconciliation.py')
    if m['evidence_id'] != 'R145' or m['target_sha256'] != identity.TARGET:
        raise ValueError('small-heap-integrity target identity differs')
    return m

def verify_plan(m):
    """Freeze the bounded review and require the complete source-defined extent."""
    rows = {r['address']:r for r in m['functions']}
    if len(m['functions']) != 1 or set(rows) != {'0x0064AFC5'}:
        raise ValueError('small-heap review gains or loses inventory credit')
    row = rows['0x0064AFC5']
    if (row['coff_symbol'] != '___sbh_heap_check' or row['size'] != 793
            or row['code_size'] != 793 or row['ledger_size'] != 793
            or row['span_end'] != '0x0064B2DD' or row['decision'] != 'library'
            or row['extent_basis'] != 'function-auxiliary-record'
            or row['code_regions'] != [dict(offset=0,size=793)]
            or row['member_offset'] != 827680):
        raise ValueError('small-heap review loses complete 793-byte own AUX')
    if any(m[k] for k in ('auxiliary_bodies','anchors','state_data','interior_labels',
                          'retained_labels','diagnostic_contexts','scope_tables','range_markers',
                          'initializer_registrations','callback_ranges','literal_controls',
                          'code_carriers','source_alternatives','retained_thunks',
                          'probe_generated_data','probe_generated_code','source_weak_references',
                          'extent_reconciliations')):
        raise ValueError('small-heap graph gains unsupported dependencies')
    if (m['retained_controls'] != [dict(evidence_id='R120',manifest='runtime-cycle-origin-evidence.json')]
            or len(m['common_globals']) != 2 or m['sdk_layout']['source_section_size'] != 152
            or m['sdk_layout']['objects'] != LAYOUT_OBJECTS
            or set(m['sdk_layout']['headers']) != LAYOUT_HEADERS
            or set(m['vendor_sources']) != {'crt/src/sbheap.c','crt/src/winheap.h'}):
        raise ValueError('small-heap complete COMMON/SDK/vendor provenance differs')
    if row['direct_edges'] or row['indirect_jumps']:
        raise ValueError('small-heap root gains unresolved dispatch')
    for key,digest in METADATA_DIGESTS.items():
        if metadata_digest(m[key]) != digest:
            raise ValueError('reviewed complete small-heap '+key+' inventory differs')
    return rows


def link_complete(source, fields, row, state_map, imports, startup):
    """Link every independently resolved field and compare every byte, unmasked."""
    metadata = [{k:f[k] for k in ('offset','type','symbol','addend','local_symbol_offset')} for f in fields]
    expected = [{k:b[k] for k in ('offset','type','symbol','addend','local_symbol_offset')}
                for b in row['relocation_bindings']]
    if len(source) != row['size'] or metadata != expected:
        raise ValueError('complete small-heap typed field topology differs')
    linked = bytearray(source); covered = set()
    for field,binding in zip(fields,row['relocation_bindings']):
        off = field['offset']; span = set(range(off,off+4))
        if field['type'] != 'DIR32' or off < 0 or off+4 > len(source) or covered & span:
            raise ValueError('small-heap typed field range/type overlaps or differs')
        covered |= span
        if binding['target_kind'] == 'import':
            startup.check_import_binding(binding,imports)
            dest = int(binding['target_address'],16)
        elif binding['target_kind'] == 'state':
            dest = state_map.get((row['member_offset'],field['symbol']))
            if dest != int(binding['target_address'],16):
                raise ValueError('small-heap field lacks an independently resolved COMMON')
        else:
            raise ValueError('small-heap typed field has no complete independent binding')
        struct.pack_into('<I',linked,off,(dest+field['addend']) & 0xffffffff)
    return bytes(linked)


def check_common_provenance(m,members,c,coff):
    retained = json.loads((ROOT/'config/runtime-cycle-origin-evidence.json').read_text())
    for row in m['common_globals']:
        provenance = next(r for r in m['common_alternatives'] if r['symbol']==row['symbol'])
        old = next(r for r in retained['common_globals'] if r['symbol']==row['symbol'])
        if old != provenance['retained_definition'] or provenance['retained_evidence_id'] != 'R120':
            raise ValueError('small-heap COMMON loses independent full R120 provenance')
        for key in ('member_offset','member','member_sha256','source_definition','target_address','zero_fill_region'):
            if row[key] != old[key]:
                raise ValueError('small-heap COMMON differs from independently accepted definition')
        definitions = []
        for off,(_,data) in members.items():
            try:entries = coff.parse_symbols(data,c.coff_name)[1]
            except ValueError:continue
            definitions.extend(dict(member_offset=off,source_definition=d) for d in entries
                               if d['symbol']==row['symbol'] and d['storage']==2
                               and (d['section']!=0 or d['offset']!=0))
        if (definitions != provenance['definitions'] or definitions != [dict(
                member_offset=row['member_offset'],source_definition=row['source_definition'])]
                or row['source_definition']['section'] != 0
                or row['source_definition']['offset'] != 4 or row['size'] != 4):
            raise ValueError('small-heap COMMON lacks a unique whole-archive tentative definition')


def check_vendor_reproduction(m,path,c,coff,target,state_map,imports,startup):
    """Cold-compile the supplied full vendor C and compare the complete selected AUX."""
    vendor = m['vendor_reproduction']; source = ROOT/vendor['source']
    if hashlib.sha256(source.read_bytes()).hexdigest() != vendor['source_sha256']:
        raise ValueError('cold small-heap vendor C identity differs')
    for filename,digest in vendor['headers'].items():
        if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest() != digest:
            raise ValueError('cold small-heap vendor included header differs')
    subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(source),str(path),*vendor['profile']],
                   cwd=ROOT,capture_output=True,text=True,check=True)
    body,fields = c.object_function(path,vendor['coff_symbol'])
    row = m['functions'][0]
    metadata = [{k:f[k] for k in ('offset','type','symbol','addend','local_symbol_offset')} for f in fields]
    if (len(body) != vendor['size'] or len(body) != row['size']
            or hashlib.sha256(body).hexdigest() != vendor['source_sha256_body']
            or vendor['source_sha256_body'] != row['source_sha256']
            or metadata != vendor['relocation_metadata']):
        raise ValueError('cold full vendor own-AUX body or typed fields differ')
    linked = link_complete(body,fields,row,state_map,imports,startup)
    if linked != c.pe_bytes_at(target,int(row['address'],16),row['size']):
        raise ValueError('cold small-heap complete relocated 793-byte comparison differs')

def check_ledger(row, function, origin):
    if (int(function['size']) != row['size'] or function['span_end'] != row['span_end']
            or function['source_file'] or function['match_percent'] != '0.00'
            or function['calling_convention'] or function['signature']):
        raise ValueError('small-heap-integrity loses complete origin-only extent')
    if (origin['evidence_id'] != 'R145' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] != row.get('proposed_name',row['coff_symbol'])):
        raise ValueError('small-heap-integrity canonical complete library acceptance differs')

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
    layout_section = next(d['section'] for d in definitions if d['symbol']=='_SmallHeapIntegrityLayoutProbe')
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
    old = module('small_heap_old','verify-runtime-error-origins.py')
    c = module('small_heap_target','compare-coff-function.py')
    archive_reader = module('small_heap_archive','verify-runtime-origins.py')
    coff = module('small_heap_coff','coff_data.py')
    startup = module('small_heap_geometry','verify-startup-dependency-origins.py')
    record = module('small_heap_ledger','verify-vendor-record-origins.py')
    facts = module('small_heap_facts','verify-game-lifetime-origins.py')
    imports_module = module('small_heap_imports','verify-import-origins.py')
    literal = module('small_heap_scalar','verify-runtime-external-origins.py')
    sections = module('small_heap_sections','verify-compiler-origins.py')
    target = c.verified_target(); m = manifest(); rows = verify_plan(m)
    functions = {r['address']:r for r in record.rows('functions.csv')}
    origins = {r['address']:r for r in record.rows('function-origins.csv')}
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        key = row['address']; a = int(key,16)
        if row['decision'] == 'library-control' and key in functions:
            raise ValueError('complete small-heap-integrity source control gains an invented candidate')
        actual = {k for k in functions if a < int(k,16) < a + row['size']}
        expected = {r['address'] for r in m['interior_labels']+m['retained_labels'] if r['parent'] == key}
        if actual != expected:
            raise ValueError('small-heap-integrity complete primary loses an actual interior candidate')
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
            raise ValueError('small-heap-integrity whole defining data topology differs')
        if row['writable'] != bool(int(desc['flags'],16)&0x80000000):
            raise ValueError('small-heap-integrity source data mutability differs')
        for d in desc['definitions']:
            state_map[(row['member_offset'],d['symbol'])] = a + d['offset']
            if d['storage'] == 2:
                global_state.setdefault(d['symbol'],set()).add(a + d['offset'])
        if raw is None:
            if (not int(desc['flags'],16)&0x80 or desc['relocations']
                    or startup.zero_fill_region(target,a,row['size']) != row['zero_fill_region']):
                raise ValueError('small-heap-integrity state lacks complete loader zero-fill provenance')
            continue
        actual = c.pe_bytes_at(target,a,len(raw)); linked = bytearray(raw)
        if len(desc['relocations']) != len(row['relocations']):
            raise ValueError('small-heap-integrity whole initialized data fields differ')
        for field,binding in zip(desc['relocations'],row['relocations']):
            if {k:binding[k] for k in field} != field:
                raise ValueError('small-heap-integrity initialized data relocation metadata differs')
            struct.pack_into('<I',linked,field['offset'],(int(binding['target_address'],16)+field['addend'])&0xffffffff)
        if (linked != actual or hashlib.sha256(raw).hexdigest() != row['source_sha256']
                or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
            raise ValueError('small-heap-integrity complete defining data source/target comparison differs')
        if row['writable']:
            if not any(base<=a and a+row['size']<=base+size and flags&0x80000000 and not flags&0x20000000 for base,size,flags in target_sections):
                raise ValueError('small-heap-integrity state loses whole writable target storage')
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
    decoder = Cs(CS_ARCH_X86,CS_MODE_32); decoder.detail = True
    scratch = ROOT / 'build/origin-small-heap-integrity-verification'; scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        path = Path(temporary)/'VendorMember.obj'
        layout = m['sdk_layout']; probe = ROOT/layout['probe']
        profile = old.PROFILE+['/D_CRTBLD','/D_MT','/I','.tools/msvc710/Vc7/crt/src','/Zc:wchar_t']
        if (layout['profile'] != profile or hashlib.sha256(probe.read_bytes()).hexdigest() != layout['probe_sha256']
                or set(layout['headers']) != LAYOUT_HEADERS):
            raise ValueError('natural small-heap-integrity control source/profile/headers differ')
        for filename,digest in layout['headers'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest() != digest:
                raise ValueError('pinned small-heap-integrity control header differs')
        subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(probe),str(path),*profile],cwd=ROOT,capture_output=True,text=True,check=True)
        data = path.read_bytes(); defs = coff.parse_symbols(data,c.coff_name)[1]
        entry = next(d for d in defs if d['symbol'] == '_SmallHeapIntegrityLayoutProbe')
        layout_section = entry['section']
        raw,names = coff.readonly_section(data,layout_section,c.coff_name)
        if (names != layout['definitions'] or len(raw) != layout['source_section_size']
                or hashlib.sha256(raw).hexdigest() != layout['source_sha256']):
            raise ValueError('cold complete natural small-heap-integrity data objects/alignment differ')
        for obj in layout['objects']:
            entry = next(d for d in defs if d['symbol'] == obj['symbol'])
            if (entry['offset'] != obj['offset'] or entry['section'] != layout_section
                    or list(struct.unpack_from('<'+'I'*(obj['size']//4),raw,obj['offset'])) != obj['values']):
                raise ValueError('cold natural exception/thread SDK offsets or ABI constants differ')
        for filename,digest in m['vendor_sources'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest()!=digest:
                raise ValueError('pinned complete small-heap-integrity vendor source differs')
        for control in m['call_controls']:
            source,fields=c.object_function(path,control['coff_symbol']);ins=list(decoder.disasm(source,0))
            metadata=[{k:f[k] for k in ('offset','type','symbol','addend','local_symbol_offset')} for f in fields]
            if (len(source)!=control['size'] or metadata!=control['relocation_metadata']
                    or hashlib.sha256(source).hexdigest()!=control['source_sha256']
                    or facts.body_facts(ins)!=control['body_facts']
                    or [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]!=control['instructions']):
                raise ValueError('cold complete small-heap-integrity ABI/SEH/C++ controls differ')
        check_probe_generated(data,path,m,c,coff,old,decoder,facts)
        check_vendor_reproduction(m,path,c,coff,target,state_map,imports,startup)
        observed_catalog = []
        decoded = {}
        for row in m['functions']+m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']:
            a = int(row['address'],16); key = row['address']
            if row['decision'] == 'library' and not args.evidence_only:
                check_ledger(row,functions[key],origins[key])
            if row['decision'] == 'anchor':
                if (origins[key]['origin'] != row['origin'] or origins[key]['evidence_id'] != row['origin_evidence']
                        or row['control_flow_basis'] != 'Independent complete runtime/archive controls replayed through R141'):
                    raise ValueError('small-heap-integrity retained independent complete code origin differs')
            data = member(row); path.write_bytes(data)
            source,fields = object_code(path,row,c,coff)
            actual = c.pe_bytes_at(target,a,row['size'])
            defs = coff.parse_symbols(data,c.coff_name)[1]
            primary = next(d for d in defs if d['symbol'] == row['coff_symbol'] and d['section']>0)
            if (primary != row['source_definition'] or len(source) != row['size']
                    or hashlib.sha256(source).hexdigest() != row['source_sha256']
                    or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
                raise ValueError('small-heap-integrity complete own source extent/hash differs')
            if link_complete(source,fields,row,state_map,imports,startup) != actual:
                raise ValueError('full archive small-heap relocated byte comparison differs')
            if [f['local_symbol_offset'] for f in fields] != [b['local_symbol_offset'] for b in row['relocation_bindings']]:
                raise ValueError('small-heap-integrity full local typed field provenance differs')
            for d in defs:
                if (d['section'] == primary['section'] and primary['offset'] <= d['offset'] < primary['offset']+row['size']
                        and d['storage'] in (2,3,6) and not d['symbol'].startswith('.')):
                    observed_catalog.append(dict(owner=key,member_offset=row['member_offset'],source_definition=d,
                                                 target_address=f"0x{a+d['offset']-primary['offset']:08X}",
                                                 source_offset=d['offset']-primary['offset']))
            ins = decode_code(row,actual,a,decoder); decoded[key] = ins
            if sum(i.size for i in ins) != row['code_size'] or facts.body_facts(ins) != row['body_facts']:
                raise ValueError('small-heap-integrity whole code instruction/control-flow inventory differs')
            witnesses = [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]
            branches = [dict(site=f'0x{i.address:08X}',target=f'0x{i.operands[0].imm:08X}') for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type == X86_OP_IMM]
            calls = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.mnemonic == 'call' and i.operands[0].type != X86_OP_IMM]
            jumps = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type != X86_OP_IMM]
            if (witnesses != row['instruction_witnesses'] or branches != row['branches']
                    or calls != row['indirect_calls'] or jumps != row['indirect_jumps']):
                raise ValueError('small-heap-integrity complete branch/API/ABI/dispatch inventory differs')
            if row['decision'] in ('anchor','pending'):
                continue
            for b in row['relocation_bindings']:
                if b['target_kind'] == 'import':
                    startup.check_import_binding(b,imports)
                elif b['target_kind'] == 'state' and (b['type'] != 'DIR32' or state_map.get((row['member_offset'],b['symbol'])) != int(b['target_address'],16)):
                    raise ValueError('small-heap-integrity field lacks member-local/whole strong data provenance')
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
            raise ValueError('small-heap-integrity code entry catalog differs from actual complete source definitions')
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
                        raise ValueError('small-heap-integrity local transfer does not reach an actual instruction start')
                    continue
                site = f'0x{i.address:08X}'; observed_sites.add(site); edge = edges.get(site)
                if not edge or int(edge['target'],16) != dest:
                    raise ValueError('small-heap-integrity direct transfer lacks full defining edge provenance')
                if edge['basis'] == 'typed-REL32':
                    field = next((b for b in row['relocation_bindings'] if b['type'] == 'REL32' and b['offset'] == i.address-a+i.imm_offset),None)
                    if (not field or field['target_kind'] != 'callee' or field['offset'] != edge['field_offset']
                            or field['target_address'] != edge['target'] or field['code_entry'] != edge['code_entry']):
                        raise ValueError('small-heap-integrity direct transfer loses its actual typed field')
                    owner = graph[field['code_entry']['owner']]
                else:
                    owner = graph[edge['owner']]
                    if source_ins[i.address-a].operands[0].imm != edge['source_target_offset']:
                        raise ValueError('small-heap-integrity same-section transfer changes its source-relative target')
                if dest not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('small-heap-integrity shared/typed entry does not reach an actual full-owner instruction')
            if observed_sites != set(edges):
                raise ValueError('small-heap-integrity complete direct edge inventory differs')
        for data in m['state_data']:
            for b in data['relocations']:
                if b['target_kind']=='state':
                    resolve_state_reference(dict(member_offset=data['member_offset'],symbol=b['symbol'],target_address=b['target_address']),state_map,global_state)
                    continue
                owner = graph[b['code_entry']['owner']]
                if int(b['target_address'],16) not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('small-heap-integrity data pointer does not reach a complete actual code entry')
    for script in ('verify-runtime-cycle-origins.py',):
        result = subprocess.run([str(ROOT/'scripts/repo-python'),'scripts/'+script],cwd=ROOT,capture_output=True,text=True)
        if result.returncode:
            raise ValueError('retained independent full R120 replay failed: '+result.stderr[-1500:])
    print('R145 origins OK: complete small-block heap integrity primary / 793 bytes / eight independently bound fields / 61 complete branches / both epilogues; unique whole-archive tentative definitions and complete loader zero-fill for two COMMON globals retained through full R120 cold replay; three actual IsBadWritePtr IAT calls; cold supplied full sbheap.c reproduces the complete selected own AUX and every relocated target byte; actual 152-byte SDK layout and six whole natural controls; local origin-only acceptance, no source or exact credit.')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
