#!/usr/bin/env python3
"""Cold-replay R116 CRT dispatch, shared tails and unresolved cookie evidence."""
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
from capstone import Cs, CS_ARCH_X86, CS_MODE_32, CS_GRP_JUMP
from capstone.x86 import X86_OP_IMM

ROOT=Path(__file__).resolve().parents[1]
PROFILE=['/Od','/Ob0','/Gy','/GR-','/GX','/Zi','/GS','/I','src']
LIBRARY={'0x006440A5':'___crtExitProcess','0x0064FBFE':'___crtMessageBoxA','0x00641B80':'_strcpy'}
PENDING={'0x00648C70':'crt-writer-cookie-chain-unresolved',
         '0x00648E11':'crt-banner-writer-chain-unresolved',
         '0x00640611':'cookie-failure-chain-unresolved'}
CACHE={'MessageBoxA':'0x0068E708','GetActiveWindow':'0x0068E70C',
       'GetLastActivePopup':'0x0068E710','GetProcessWindowStation':'0x0068E714',
       'GetUserObjectInformationA':'0x0068E718'}
DISPATCH_WITNESSES={
    '0x006440A5':('push','0x6611f0'),
    '0x006440AA':('call','dword ptr [0x6570a8]'),
    '0x006440B4':('push','0x6611e0'),
    '0x006440BA':('call','dword ptr [0x6570a0]'),
    '0x006440C8':('call','eax'),
    '0x006440CE':('call','dword ptr [0x65717c]'),
    '0x006440D4':('int3',''),
    '0x0064FC11':('push','0x6673b0'),
    '0x0064FC16':('call','dword ptr [0x6570a4]'),
    '0x0064FC1C':('mov','edi, eax'),
    '0x0064FC26':('mov','esi, dword ptr [0x6570a0]'),
    '0x0064FC2C':('push','0x6673a4'),
    '0x0064FC31':('push','edi'),
    '0x0064FC32':('call','esi'),
    '0x0064FC36':('mov','dword ptr [0x68e708], eax'),
    '0x0064FC3D':('push','0x667394'),
    '0x0064FC42':('push','edi'),
    '0x0064FC43':('call','esi'),
    '0x0064FC45':('push','0x667380'),
    '0x0064FC4A':('push','edi'),
    '0x0064FC4B':('mov','dword ptr [0x68e70c], eax'),
    '0x0064FC50':('call','esi'),
    '0x0064FC52':('cmp','dword ptr [0x68e2e8], 2'),
    '0x0064FC59':('mov','dword ptr [0x68e710], eax'),
    '0x0064FC60':('push','0x667364'),
    '0x0064FC65':('push','edi'),
    '0x0064FC66':('call','esi'),
    '0x0064FC6A':('mov','dword ptr [0x68e718], eax'),
    '0x0064FC6F':('je','0x64fc7e'),
    '0x0064FC71':('push','0x66734c'),
    '0x0064FC76':('push','edi'),
    '0x0064FC77':('call','esi'),
    '0x0064FC79':('mov','dword ptr [0x68e714], eax'),
    '0x0064FC7E':('mov','eax, dword ptr [0x68e714]'),
    '0x0064FC87':('call','eax'),
    '0x0064FC91':('push','0xc'),
    '0x0064FC93':('lea','ecx, [ebp - 0x10]'),
    '0x0064FC97':('push','1'),
    '0x0064FC99':('push','eax'),
    '0x0064FC9A':('call','dword ptr [0x68e718]'),
    '0x0064FCA4':('test','byte ptr [ebp - 8], 1'),
    '0x0064FCAA':('cmp','dword ptr [0x68e2f4], 4'),
    '0x0064FCB3':('or','byte ptr [ebp + 0x12], 0x20'),
    '0x0064FCBD':('or','byte ptr [ebp + 0x12], 4'),
    '0x0064FCC3':('mov','eax, dword ptr [0x68e70c]'),
    '0x0064FCCC':('call','eax'),
    '0x0064FCD4':('mov','eax, dword ptr [0x68e710]'),
    '0x0064FCDE':('call','eax'),
    '0x0064FCEC':('call','dword ptr [0x68e708]'),
}


def module(name,filename):
    spec=importlib.util.spec_from_file_location(name,ROOT/'scripts'/filename)
    result=importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


def whole_section(data,symbol,comparison,coff):
    """Read every byte/definition/relocation of the symbol's defining section."""
    _,entries=coff.parse_symbols(data,comparison.coff_name)
    found=[e for e in entries if e['symbol']==symbol and e['section']>0]
    if len(found)!=1 or found[0]['offset']:
        raise ValueError('source data/carrier lacks one definition at section start')
    number=found[0]['section']
    header=struct.unpack_from('<8sIIIIIIHHI',data,20+(number-1)*40)
    size,offset=header[3],header[4]
    if not size or (offset and offset+size>len(data)):
        raise ValueError('source whole section extent differs')
    raw=data[offset:offset+size] if offset else None
    definitions=[e for e in entries if e['section']==number and e['storage'] in (2,3) and not e['symbol'].startswith('.')]
    symbol_offset,symbol_count=struct.unpack_from('<II',data,8)
    strings_offset=symbol_offset+18*symbol_count
    strings=data[strings_offset:strings_offset+struct.unpack_from('<I',data,strings_offset)[0]]
    indexed,index={},0
    while index<symbol_count:
        name,value,section,typ,storage,aux=struct.unpack_from('<8sIhHBB',data,symbol_offset+18*index)
        indexed[index]=comparison.coff_name(name,strings)
        index+=1+aux
    fields=[]
    for i in range(header[7]):
        field,target,typ=struct.unpack_from('<IIH',data,header[5]+10*i)
        if raw is None or field+4>len(raw) or typ!=6 or target not in indexed:
            raise ValueError('unsupported whole data section relocation')
        fields.append({'offset':field,'type':'DIR32','symbol':indexed[target],
                       'addend':struct.unpack_from('<I',raw,field)[0]})
    return raw,{'size':size,'flags':f'0x{header[9]:08X}','definitions':definitions,'relocations':fields}


def compare_fields(source,relocations,actual,address,bindings,comparison):
    if len(source)!=len(actual) or len(relocations)!=len(bindings):
        raise ValueError('CRT whole extent or field count differs')
    solved=comparison.solved_relocations(source,actual,relocations,address)
    mask=set()
    for r,s,b in zip(relocations,solved,bindings):
        expected={'offset':r['offset'],'type':r['type'],'symbol':r['symbol'],
                  'addend':r['addend'],'target_address':s['solved_destination']}
        if (r['type'] not in ('DIR32','REL32') or {k:b[k] for k in expected}!=expected
                or any(i in mask for i in range(r['offset'],r['offset']+4))):
            raise ValueError('CRT complete typed field differs')
        mask.update(range(r['offset'],r['offset']+4))
    if any(source[i]!=actual[i] for i in range(len(source)) if i not in mask):
        raise ValueError('CRT source differs outside every declared field')


def check_dispatch_literals(literals):
    expected={'0x006611F0':b'mscoree.dll\0','0x006611E0':b'CorExitProcess\0',
              '0x006673B0':b'user32.dll\0','0x006673A4':b'MessageBoxA\0',
              '0x00667394':b'GetActiveWindow\0','0x00667380':b'GetLastActivePopup\0',
              '0x0066734C':b'GetProcessWindowStation\0','0x00667364':b'GetUserObjectInformationA\0'}
    actual={key[2]:value for key,value in literals.items() if key[2] in expected}
    if actual!=expected:
        raise ValueError('dynamic API lookup lacks the complete actual DLL/export strings')


def verify_plan(manifest):
    rows={r['address']:r for r in manifest['functions']}
    if (len(rows)!=6 or set(rows)!=set(LIBRARY)|set(PENDING) or sum(r['size'] for r in rows.values())!=750
            or {k for k,r in rows.items() if r['decision']=='library'}!=set(LIBRARY)
            or any(rows[k]['decision']!='pending' or rows[k]['uncertainty']!=v for k,v in PENDING.items())):
        raise ValueError('R116 bounded decisions or unresolved cookie chain differ')
    for key,symbol in LIBRARY.items():
        if rows[key]['coff_symbol']!=symbol or rows[key]['extent_basis']!='function-auxiliary-record':
            raise ValueError('CRT accepted whole source identity differs')
        if any(b['target_kind'] not in ('import','literal','cache','version-global') for b in rows[key]['relocation_bindings']):
            raise ValueError('accepted dispatch retains an unproved code/data field')
    exit_row=rows['0x006440A5']
    if exit_row['size']!=48 or exit_row['span_end']!='0x006440D4' or exit_row['terminal']!='ExitProcess-followed-by-int3':
        raise ValueError('nonreturning exit drops its own terminal INT3 extent')
    carrier=manifest['copy_carrier']
    if (carrier['size']!=248 or carrier['target_address']!='0x00641B80'
            or carrier['function_definitions']!=[{'symbol':'_strcpy','offset':0,'size':7},{'symbol':'_strcat','offset':16,'size':232}]
            or carrier['shared_tail']!={'site':'0x00641B85','target':'0x00641BF5','owner':'0x00641B90'}
            or carrier['alignment']!={'offset':7,'size':9,'instructions':['lea esp, [esp]','mov edi, edi']}):
        raise ValueError('strcpy lacks its full two-function carrier/shared-tail relationship')
    resolutions=manifest['dynamic_exports']
    expected={'CorExitProcess':('0x006440BA','0x006440C8',None),
              'MessageBoxA':('0x0064FC32','0x0064FCEC',CACHE['MessageBoxA']),
              'GetActiveWindow':('0x0064FC43','0x0064FCCC',CACHE['GetActiveWindow']),
              'GetLastActivePopup':('0x0064FC50','0x0064FCDE',CACHE['GetLastActivePopup']),
              'GetProcessWindowStation':('0x0064FC77','0x0064FC87',CACHE['GetProcessWindowStation']),
              'GetUserObjectInformationA':('0x0064FC66','0x0064FC9A',CACHE['GetUserObjectInformationA'])}
    if (len(resolutions)!=6 or {r['export']:(r['resolve_site'],r['call_site'],r['cache_slot']) for r in resolutions}!=expected
            or any(r['dll']!=('mscoree.dll' if r['export']=='CorExitProcess' else 'user32.dll') for r in resolutions)):
        raise ValueError('dynamic CRT calls lack actual DLL/export/slot provenance')
    if manifest['sdk_layout']['values']!=[12,8,1,1,0x200000,0x40000] or manifest['sdk_layout']['size']!=24:
        raise ValueError('window-station query lacks its full SDK structure/flag control')
    witnesses={w['site']:(w['mnemonic'],w['operands']) for row in rows.values() for w in row['instruction_witnesses']}
    if any(witnesses.get(site)!=operation for site,operation in DISPATCH_WITNESSES.items()):
        raise ValueError('dynamic exports lack concrete lookup/store/call and SDK-policy witnesses')
    if (manifest['cache_data']['size']!=20 or manifest['cache_data']['target_address']!='0x0068E708'
            or len(manifest['cache_data']['definitions'])!=5):
        raise ValueError('dynamic CRT cache lacks its complete defining BSS section')
    cache=manifest['cache_data']
    expected_defs={f'?pfn{name}@?1??__crtMessageBoxA@@9@9':int(address,16)-0x68E708 for name,address in CACHE.items()}
    if (cache['source_section']['flags']!='0xC0300080' or cache['source_section']['relocations']
            or cache['definitions']!=cache['source_section']['definitions']
            or {d['symbol']:d['offset'] for d in cache['definitions']}!=expected_defs):
        raise ValueError('dynamic CRT cache symbols/offsets are not the full uninitialized source definition')
    if [(r['member_offset'],r['symbol'],r['target_address'],r['size']) for r in manifest['state_data']]!=[
            (1756238,'__aenvptr','0x0068E2CC',12),(1756238,'__aexit_rtn','0x0066FF10',8),
            (1679710,'__adbgmsg','0x0068E574',4),(1236214,'___security_cookie','0x0066FE30',4)]:
        raise ValueError('CRT diagnostic state loses complete cookie/application/error definitions')
    table=manifest['error_table']
    if (table['size']!=152 or len(table['relocations'])!=19 or table['target_address']!='0x006706B0'
            or table['codes']!=[2,8,9,10,16,17,18,19,24,25,26,27,28,29,120,121,122,252,255]
            or [b['offset'] for b in table['relocations']]!=list(range(4,152,8))):
        raise ValueError('diagnostic writer loses its whole nineteen-entry error table')
    required={(r['member_offset'],b['symbol'],b['target_address']) for r in rows.values() for b in r['relocation_bindings'] if b['symbol'].startswith('??_C@')}
    required.update((table['member_offset'],b['symbol'],b['target_address']) for b in table['relocations'])
    literals=manifest['literal_controls']
    if len(literals)!=32 or {(r['member_offset'],r['symbol'],r['target_address']) for r in literals}!=required:
        raise ValueError('CRT literal fields lack every complete readonly source definition')
    diagnostics=manifest['diagnostic_contexts']
    if (len(diagnostics)!=3 or sum(r['size'] for r in diagnostics)!=122
            or any(r['decision']!='diagnostic' for r in diagnostics)):
        raise ValueError('unresolved error/failure contexts gain ownership')
    failure=next(r for r in diagnostics if r['address']=='0x006405E0')
    if failure['size']!=49 or failure['ledger_size']!=48 or failure['terminal']!='ExitProcess-followed-by-int3':
        raise ValueError('cookie failure context truncates its own filter/INT3 extent')
    return rows


def check_ledger(row,functions,origins,evidence_only):
    key,address=row['address'],int(row['address'],16)
    function=functions[key]
    size=int(function['size'])
    expected=47 if evidence_only and key=='0x006440A5' else row['size']
    if (size!=expected or int(function['span_end'],16)!=address+size-1
            or any(address<int(k,16)<address+row['size'] for k in functions)):
        raise ValueError('CRT extent reconciliation or unresolved interior differs')
    if function['source_file'] or function['match_percent']!='0.00':
        raise ValueError('CRT origin cannot grant source or exact credit')
    if evidence_only:
        return
    origin=origins[key]
    if key in LIBRARY:
        if (origin['origin']!='library' or origin['evidence_id']!='R116' or origin['disposition']!='exclude'
                or function['owner']!='library' or function['status']!='excluded' or function['proposed_name']!=LIBRARY[key]):
            raise ValueError('R116 accepted library ledger differs')
    elif (origin['origin']!='unknown' or origin['evidence_id']!='R116' or origin['confidence']!=PENDING[key]
            or origin['disposition']!='review' or function['owner'] or function['status']!='unclassified'):
        raise ValueError('pending CRT writer/banner/cookie gains unearned credit')


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only',action='store_true')
    args=parser.parse_args()
    comparison=module('re_target','compare-coff-function.py')
    runtime=module('re_archive','verify-runtime-origins.py')
    record=module('re_ledgers','verify-vendor-record-origins.py')
    coff=module('re_symbols','coff_data.py')
    imports_module=module('re_imports','verify-import-origins.py')
    external=module('re_literal','verify-runtime-external-origins.py')
    compiler=module('re_sections','verify-compiler-origins.py')
    startup=module('re_geometry','verify-startup-dependency-origins.py')
    lifetime=module('re_facts','verify-game-lifetime-origins.py')
    target=comparison.verified_target()
    manifest=json.loads((ROOT/'config/runtime-error-origin-evidence.json').read_text())
    if manifest['evidence_id']!='R116' or manifest['target_sha256']!=hashlib.sha256(target).hexdigest():
        raise ValueError('R116 pinned target differs')
    rows=verify_plan(manifest)
    functions={r['address']:r for r in record.rows('functions.csv')}
    origins={r['address']:r for r in record.rows('function-origins.csv')}
    imports=imports_module.pe_imports(target,comparison)
    sections=compiler.sections(target)
    archive=(ROOT/'.tools/msvc710/Vc7/lib/libcmt.lib').read_bytes()
    if hashlib.sha256(archive).hexdigest()!=manifest['archive_sha256']:
        raise ValueError('CRT archive identity differs')
    members={offset:(name,data) for offset,name,data in runtime.archive_members(archive)}
    def member(row):
        name,data=members[row['member_offset']]
        if name!=row['member'] or hashlib.sha256(data).hexdigest()!=row['member_sha256']:
            raise ValueError('cold complete CRT member differs')
        return data
    literals={}
    for row in manifest['literal_controls']:
        source=external.readonly_member_data(member(row),row['symbol'],row,comparison.coff_name)
        address=int(row['target_address'],16)
        external.check_scalar(source,comparison.pe_bytes_at(target,address,len(source)),len(source),sections,address)
        literals[(row['member_offset'],row['symbol'],row['target_address'])]=source
    check_dispatch_literals(literals)
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    decoder.detail=True
    scratch=ROOT/'build/origin-runtime-error-verification'
    scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        path=Path(temporary)/'VendorMember.obj'
        carrier=manifest['copy_carrier']
        raw,description=whole_section(member(carrier),'_strcpy',comparison,coff)
        if (description!=carrier['source_section'] or description['relocations'] or len(raw)!=248
                or hashlib.sha256(raw).hexdigest()!=carrier['sha256']
                or raw!=comparison.pe_bytes_at(target,0x641B80,248)):
            raise ValueError('whole strcpy/strcat carrier and alignment differ')
        starts={i.address for i in decoder.disasm(raw,0x641B80)}
        for instruction in decoder.disasm(raw,0x641B80):
            if instruction.group(CS_GRP_JUMP) and instruction.operands[0].imm not in starts:
                raise ValueError('shared string carrier has an unresolved external branch')
        for data_row in [manifest['cache_data'],manifest['error_table'],*manifest['state_data']]:
            raw,description=whole_section(member(data_row),data_row['symbol'],comparison,coff)
            if (description!=data_row['source_section'] or description['size']!=data_row['size']
                    or description['definitions']!=data_row['definitions']):
                raise ValueError('whole CRT data definition/topology differs')
            address=int(data_row['target_address'],16)
            if raw is None:
                if (not int(description['flags'],16)&0x80 or description['relocations']
                        or startup.zero_fill_region(target,address,description['size'])!=data_row['zero_fill_region']):
                    raise ValueError('CRT complete BSS is not proved loader zero-fill')
            else:
                actual=comparison.pe_bytes_at(target,address,len(raw))
                linked=bytearray(raw)
                for field,binding in zip(description['relocations'],data_row['relocations']):
                    if {k:binding[k] for k in field}!=field or field['type']!='DIR32':
                        raise ValueError('CRT whole data typed pointer differs')
                    destination=int(binding['target_address'],16)
                    struct.pack_into('<I',linked,field['offset'],destination+field['addend'])
                if (len(description['relocations'])!=len(data_row['relocations']) or linked!=actual
                        or hashlib.sha256(raw).hexdigest()!=data_row['source_sha256']
                        or hashlib.sha256(actual).hexdigest()!=data_row['body_sha256']):
                    raise ValueError('CRT complete initialized data comparison differs')
                if data_row is manifest['error_table']:
                    if [struct.unpack_from('<I',raw,i)[0] for i in range(0,152,8)]!=data_row['codes']:
                        raise ValueError('whole error-table source codes differ')
                    for b in data_row['relocations']:
                        if (data_row['member_offset'],b['symbol'],b['target_address']) not in literals:
                            raise ValueError('error-table pointer lacks its complete vendor message')
        layout=manifest['sdk_layout']
        probe=ROOT/layout['probe']
        if layout['profile']!=PROFILE or hashlib.sha256(probe.read_bytes()).hexdigest()!=layout['probe_sha256']:
            raise ValueError('natural SDK window-station probe differs')
        for filename,digest in layout['headers'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest()!=digest:
                raise ValueError('SDK window-station interpretation header differs')
        subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(probe),str(path),*PROFILE],cwd=ROOT,
                       capture_output=True,text=True,check=True)
        data=path.read_bytes()
        definition=next(s for s in coff.parse_symbols(data,comparison.coff_name)[1] if s['symbol']==layout['symbol'])
        raw,names=coff.readonly_section(data,definition['section'],comparison.coff_name)
        if (definition['offset'] or names!=[{'symbol':layout['symbol'],'offset':0}]
                or len(raw)!=24 or list(struct.unpack('<6I',raw))!=layout['values']):
            raise ValueError('cold SDK layout lacks its whole readonly definition')
        for row in manifest['functions']+manifest['diagnostic_contexts']+manifest['anchors']:
            key,address=row['address'],int(row['address'],16)
            if key in rows:
                check_ledger(row,functions,origins,args.evidence_only)
            elif row['decision']=='anchor':
                if origins[key]['origin']!='library' or origins[key]['evidence_id']!=row['origin_evidence']:
                    raise ValueError('retained string/stack anchor loses its origin')
            elif int(functions[key]['size'])!=row['ledger_size']:
                raise ValueError('unaccepted failure/error context extent differs')
            path.write_bytes(member(row))
            source,fields=comparison.object_function(path,row['coff_symbol'])
            actual=comparison.pe_bytes_at(target,address,row['size'])
            if (len(source)!=row['size'] or hashlib.sha256(source).hexdigest()!=row['source_sha256']
                    or hashlib.sha256(actual).hexdigest()!=row['body_sha256']):
                raise ValueError('own complete CRT auxiliary extent/hash differs')
            compare_fields(source,fields,actual,address,row['relocation_bindings'],comparison)
            instructions=list(decoder.disasm(actual,address))
            if sum(i.size for i in instructions)!=row['size'] or lifetime.body_facts(instructions)!=row['body_facts']:
                raise ValueError('whole CRT instruction/call/return inventory differs')
            starts={i.address for i in instructions}
            branches=[]
            for instruction in instructions:
                if instruction.group(CS_GRP_JUMP):
                    destination=instruction.operands[0].imm
                    branches.append({'site':f'0x{instruction.address:08X}','target':f'0x{destination:08X}'})
                    if row['decision']=='library' and destination not in starts and not (key=='0x00641B80' and destination==0x641BF5):
                        raise ValueError('accepted CRT has an unverified external/shared branch')
            if branches!=row['branches']:
                raise ValueError('CRT complete branch inventory differs')
            indirect=[i for i in instructions if i.mnemonic=='call' and i.operands[0].type!=X86_OP_IMM]
            if [(f'0x{i.address:08X}',i.op_str) for i in indirect]!=[(c['site'],c['operand']) for c in row['indirect_calls']]:
                raise ValueError('CRT complete dynamic/import call inventory differs')
            by_site={f'0x{i.address:08X}':i for i in instructions}
            if key in ('0x006440A5','0x0064FBFE') and len(row['instruction_witnesses'])!=len(instructions):
                raise ValueError('dynamic dispatch witnesses omit a lookup, guard, store or argument')
            for witness in row['instruction_witnesses']:
                instruction=by_site[witness['site']]
                if (instruction.mnemonic,instruction.op_str)!=(witness['mnemonic'],witness['operands']):
                    raise ValueError('CRT lookup/store/call/flag/cookie witness differs')
            for binding in row['relocation_bindings']:
                if binding['target_kind']=='import':
                    startup.check_import_binding(binding,imports)
                elif row['decision']=='library' and binding['target_kind']=='literal':
                    if (row['member_offset'],binding['symbol'],binding['target_address']) not in literals:
                        raise ValueError('accepted dispatch literal lacks its whole definition')
                elif row['decision']=='library' and binding['target_kind']=='cache':
                    definition=next(d for d in manifest['cache_data']['definitions'] if d['symbol']==binding['symbol'])
                    if int(binding['target_address'],16)!=0x68E708+definition['offset']:
                        raise ValueError('dynamic export slot differs from the whole vendor BSS topology')
                elif row['decision']=='library' and binding['target_kind']=='version-global':
                    if startup.GLOBALS.get(binding['symbol'])!=binding['target_address']:
                        raise ValueError('dynamic window policy loses independent version-global provenance')
            if key=='0x006440A5' and (actual[-1]!=0xCC or row['body_facts']['returns']
                    or row['indirect_calls'][-1]['site']!='0x006440CE' or imports.get(0x65717C)!=('KERNEL32.dll','ExitProcess')):
                raise ValueError('nonreturning exit lacks its full ExitProcess/trap terminal')
    result=subprocess.run([str(ROOT/'scripts/repo-python'),'scripts/verify-startup-dependency-origins.py'],cwd=ROOT,capture_output=True,text=True)
    if result.returncode:
        raise ValueError('independent SDK/version/CRT anchor replay failed: '+result.stderr[-1000:])
    print('R116 origins OK: three library bodies / 304 bytes, complete 248-byte strcpy/strcat carrier, six dynamic exports, '
          'whole 20-byte cache and SDK flags; three roots / 446 bytes retain cookie/failure uncertainty; '
          'whole 152-byte error table / 19 messages and all literal definitions verified; no source or exact credit.')
    return 0


if __name__=='__main__':
    try:
        raise SystemExit(main())
    except (OSError,KeyError,IndexError,ValueError,struct.error,subprocess.CalledProcessError) as error:
        print('error: '+str(error),file=sys.stderr)
        raise SystemExit(1)
