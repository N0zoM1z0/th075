#!/usr/bin/env python3
"""Replay complete R144 longjmp/SEH read-probe and absolute-symbol provenance."""
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
from capstone.x86 import X86_OP_IMM, X86_OP_MEM

ROOT = Path(__file__).resolve().parents[1]
CONFIDENCE = 'complete-vendor-jump-unwind-seh-scope-absolute-sdk-abi-provenance'
ACCEPTED = {'0x00643604': ('_longjmp', 121), '0x0064DC10': ('__rt_probe_read4@4', 66)}
LEDGER_SIZES = {'0x00643604': 120, '0x0064DC10': 66}
AUXILIARIES = {}
LABELS = {}
ANCHORS = [('0x00640B24', '__global_unwind2', 32, 1210238, 'R117', 'library'),
 ('0x00640B66', '__local_unwind2', 104, 1210238, 'R025', 'library'),
 ('0x00640BFA', '__NLG_Notify', 24, 1210238, 'R117', 'library'),
 ('0x00645414', '__SEH_prolog', 59, 1244382, 'R117', 'library'),
 ('0x0064544F', '__SEH_epilog', 17, 1244382, 'R115', 'library')]
STATE = {(1245828, '$T19221', '0x006639E8', 12)}
LAYOUT_OBJECTS = [{'symbol': '_JumpUnwindLayoutProbe',
  'offset': 0,
  'size': 88,
  'storage_span': 88,
  'values': [4, 4, 64, 64, 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 24, 0, 4, 3221225477, 1, 0, 4294967295]}]
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
 'crt/src/setjmp.h',
 'crt/src/stdarg.h',
 'crt/src/stddef.h',
 'crt/src/stdlib.h',
 'crt/src/string.h',
 'include/tvout.h'}
UNWIND_PROTOCOL = {'jump_buffer_size': 64,
 'jump_buffer_sdk_offsets': [0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40],
 'jump_buffer_cookie': 1447244336,
 'fs_exception_list_offset': 0,
 'source_absolute_section': -1,
 'read_probe_cleanup': 4,
 'read_probe_scope_size': 12,
 'read_probe_filter_offset': 29,
 'read_probe_handler_offset': 49,
 'read_probe_access_code': 3221225477,
 'read_probe_filter_returns': [0, 1],
 'read_probe_success_result': 1,
 'read_probe_handler_result': 0,
 'longjmp_complete_size': 121,
 'longjmp_original_size': 120,
 'longjmp_final_ret_offset': 120,
 'longjmp_saved_return_offset': 20,
 'longjmp_stack_restore_offset': 16,
 'longjmp_return_normalization': 'Zero becomes one; every nonzero signed input is retained',
 'private_source_status': 'Original longjmp.asm/sehsupp.c implementations are unavailable; full supplied '
                          'COFF and exsup.inc plus actual SDK headers are evidence',
 'runtime_unknowns': 'Live saved jump/exception registration state, saved callback identity and ABI, '
                     'exception outcome, original private unwind/NLG declarations and complete linker '
                     'inputs; no complete game owner inferred'}
REGISTER_CONTRACTS = {'0x00643604': {'incoming': ['SDK cdecl buffer pointer at ESP+4 and return value at ESP+8',
                             'Saved EBP and registration loaded before unwind'],
                'outgoing': ['Saved-context UnwindFunc is opaque: push buffer and call EAX',
                             'NLG receives saved EIP in EAX, saved EBP and stack code zero',
                             'Restore EBX/EDI/ESI/ESP; increment restored ESP by four then jump saved EIP',
                             'Own AUX retains final RET after the indirect saved-return jump'],
                'basis': 'Whole supplied longjmp code plus complete retained unwind/NLG workers and real SDK '
                         'layout; no invented private callback prototype'},
 '0x00640BFA': {'incoming': ['EAX supplies destination and EBP supplies saved frame',
                             'Stack DWORD supplies NLG code'],
                'outgoing': ['Complete source NLG shared tail records destination/frame/code and returns '
                             'with four callee bytes'],
                'basis': 'Whole R117 NLG owner/shared source entry and all fields replayed through R141; not '
                         'a conventional three-stack-argument declaration'}}
SOURCE_WEAK_REFERENCES = []
METADATA_DIGESTS = {'scope_tables': 'fde6af4d50bbb5c9212f57e2341480eac46e471148d59e3191c16792bf7fc12a',
 'call_controls': '4b00faef2364377a0f6c9679fbd6976ed810cc75d4211f082e6594daeb10edfc',
 'probe_generated_data': '0c5623ce45f829c0b3e741127e3603583e550c5fe582d3d123656237bed412a9',
 'probe_generated_code': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945',
 'runtime_dispatch': '3f7490712a07a0cd944681f7b3aa593f33791a5d85a360c2e5fe7dc397e033a2',
 'extent_reconciliations': '0e93853f1fde501046bdbfe372355fe2738adfbb547f08a1f7d3ee53788a627b',
 'absolute_symbols': '0688ce486e848a7a85e162dfd374b14d500a4776411d7b11c15a09f769f0a9f6'}

def metadata_digest(value):
    return hashlib.sha256(json.dumps(value, sort_keys=True, separators=(',', ':')).encode()).hexdigest()

def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT / 'scripts' / filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result

prior = module('jump_unwind_prior', 'verify-standard-exception-origins.py')
check_code_entry = prior.check_code_entry
whole_defining_section = prior.whole_defining_section
read_weak_reference = prior.read_weak_reference
decode_code = prior.decode_code
check_scope_records = prior.check_scope_records
resolve_state_reference = prior.resolve_state_reference
check_catalog_entry = prior.check_catalog_entry
object_code = prior.object_code

def manifest():
    m = json.loads((ROOT / 'config/jump-unwind-origin-evidence.json').read_text())
    identity = module('jump_unwind_identity', 'origin_reconciliation.py')
    if m['evidence_id'] != 'R144' or m['target_sha256'] != identity.TARGET:
        raise ValueError('jump-unwind target identity differs')
    return m


def verify_plan(m):
    rows = {r['address']: r for r in m['functions']}
    if len(rows) != 2 or len(m['functions']) != 2 or set(rows) != set(ACCEPTED):
        raise ValueError('bounded complete jump-unwind cohort differs')
    for key, (symbol, size) in ACCEPTED.items():
        row = rows[key]
        if (row['coff_symbol'] != symbol or row['size'] != size or row['code_size'] != size
                or row['ledger_size'] != LEDGER_SIZES[key] or row['decision'] != 'library'
                or row['extent_basis'] != 'function-auxiliary-record'
                or int(row['span_end'], 16) != int(key, 16) + size - 1):
            raise ValueError('jump-unwind function loses complete own AUX extent')
    aux = {r['address']: (r['coff_symbol'], r['size']) for r in m['auxiliary_bodies']}
    if len(m['auxiliary_bodies']) != 0 or aux != AUXILIARIES or any(
            r['decision'] != 'library-control' or r['extent_basis'] != 'function-auxiliary-record'
            or r['code_size'] != r['size'] or r['ledger_size'] is not None
            or int(r['span_end'],16) != int(r['address'],16) + r['size'] - 1
            for r in m['auxiliary_bodies']):
        raise ValueError('jump-unwind auxiliary controls gain invented inventory credit')
    if (len(m['interior_labels']) != 0 or
            {r['address']: (r['parent'], r['size'], r['source_offset'], r['source_symbol'])
             for r in m['interior_labels']} != LABELS or any(
            r['decision'] != 'library' or r['extent_basis'] != 'interior-entry-in-complete-vendor-primary'
            for r in m['interior_labels'])):
        raise ValueError('jump-unwind labels lose complete source parents')
    if [(r['address'],r['coff_symbol'],r['size'],r['member_offset'],r['origin_evidence'],r['origin'])
            for r in m['anchors']] != ANCHORS:
        raise ValueError('jump-unwind independent full anchors differ')
    if any(m[k] for k in ('range_markers','initializer_registrations','callback_ranges',
                          'literal_controls','retained_labels','diagnostic_contexts','common_globals',
                          'code_carriers','source_alternatives')):
        raise ValueError('jump-unwind graph gains unresolved or fabricated dependencies')
    if (len(m['state_data']) != 1 or sum(r['size'] for r in m['state_data']) != 12 or
            {(r['member_offset'],r['symbol'],r['target_address'],r['size'])
             for r in m['state_data']} != STATE):
        raise ValueError('jump-unwind loses complete defining data sections')
    if (m['sdk_layout']['source_section_size'] != 88 or m['sdk_layout']['objects'] != LAYOUT_OBJECTS
            or set(m['sdk_layout']['headers']) != LAYOUT_HEADERS
            or set(m['vendor_sources']) != {'crt/src/exsup.inc'}):
        raise ValueError('jump-unwind loses actual SDK or available source context')
    if m['retained_controls'] != [dict(evidence_id='R141',manifest='exception-frame-origin-evidence.json')]:
        raise ValueError('jump-unwind loses full retained independent R141 graph')
    if m['unwind_protocol'] != UNWIND_PROTOCOL or m['register_contracts'] != REGISTER_CONTRACTS:
        raise ValueError('jump-unwind private ABI/SDK facts or unknowns differ')
    if m['retained_thunks']:
        raise ValueError('jump-unwind changes independent compiler thunk ownership')
    for key, digest in METADATA_DIGESTS.items():
        if metadata_digest(m[key]) != digest:
            raise ValueError('jump-unwind reviewed complete '+key+' inventory differs')
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies'] + m['anchors']}}
    for row in graph.values():
        if row['code_regions'] != [dict(offset=0,size=row['size'])] or row['code_size'] != row['size']:
            raise ValueError('jump-unwind loses complete code partition')
    for row in m['functions'] + m['auxiliary_bodies']:
        for b in row['relocation_bindings']:
            if b['target_kind'] in ('callee','code-entry'):
                check_code_entry(b, graph)
            elif b['target_kind'] == 'import-thunk':
                raise ValueError('standard exception has no reviewed new import thunk')
            elif b['target_kind'] not in ('state','import','absolute'):
                raise ValueError('jump-unwind field lacks typed code/data/API provenance')
        for edge in row['direct_edges']:
            if edge['basis'] == 'same-section-shared-entry':
                owner = graph.get(edge['owner'])
                if (not owner or row['member_offset'] != owner['member_offset']
                        or edge['source_section'] != row['source_definition']['section']
                        or edge['source_section'] != owner['source_definition']['section']
                        or not 0 <= edge['source_offset'] < owner['size']
                        or edge['source_target_offset'] != owner['source_definition']['offset'] + edge['source_offset']
                        or int(edge['target'],16) != int(owner['address'],16) + edge['source_offset']):
                    raise ValueError('jump-unwind shared branch loses complete same-section owner')
            elif edge['basis'] != 'typed-REL32':
                raise ValueError('jump-unwind edge loses actual typed transfer')
    for row in m['state_data']:
        for b in row['relocations']:
            if b['target_kind'] not in ('code-entry','state') or b['type'] != 'DIR32':
                raise ValueError('jump-unwind defining data loses full typed provenance')
            if b['target_kind'] == 'code-entry':
                check_code_entry(b,graph)
    if m['source_weak_references'] != SOURCE_WEAK_REFERENCES:
        raise ValueError('jump-unwind actual weak fallback records differ')
    check_unwind_protocol(m, graph)
    return rows

def check_ledger(row, function, origin):
    if (int(function['size']) != row['size'] or function['span_end'] != row['span_end']
            or function['source_file'] or function['match_percent'] != '0.00'
            or function['calling_convention'] or function['signature']):
        raise ValueError('jump-unwind loses complete origin-only extent')
    if (origin['evidence_id'] != 'R144' or origin['origin'] != 'library'
            or origin['disposition'] != 'exclude' or origin['subsystem'] != 'VC71CRT'
            or origin['confidence'] != CONFIDENCE or function['owner'] != 'library'
            or function['module'] != 'VC71CRT' or function['status'] != 'excluded'
            or function['proposed_name'] != row.get('proposed_name',row['coff_symbol'])):
        raise ValueError('jump-unwind canonical complete library acceptance differs')

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
    layout_section = next(d['section'] for d in definitions if d['symbol']=='_JumpUnwindLayoutProbe')
    actual = {i+1 for i,h in enumerate(headers) if h[3] and h[9]&0x40 and h[9]&0x40000000
              and not h[9]&0x20000000 and h[0].rstrip(b'\0') not in (b'.debug$S',b'.debug$T',b'.debug$F',b'.drectve')}
    if actual != expected | {layout_section}:
        raise ValueError('cold natural EH model loses an entire generated initialized section')
    owned = {next(d['section'] for d in definitions if d['symbol']==r['coff_symbol'] and d['section']>0) for r in m['call_controls']}
    carriers = {next(d['section'] for d in definitions if d['symbol']==r['coff_symbol'] and d['section']>0) for r in m['probe_generated_code']}
    code_sections = {i+1 for i,h in enumerate(headers) if h[3] and h[9]&0x20}
    if owned & carriers or owned | carriers != code_sections:
        raise ValueError('cold natural model loses a complete generated code section')

def check_unwind_protocol(m,graph):
    jump = graph['0x00643604']; probe = graph['0x0064DC10']
    witnesses = lambda row: {(w['mnemonic'],w['operands']) for w in row['instruction_witnesses']}
    required_jump = {('mov','ebx, dword ptr [esp + 4]'),('mov','ebp, dword ptr [ebx]'),
                     ('mov','esi, dword ptr [ebx + 0x18]'),('cmp','esi, dword ptr fs:[0]'),
                     ('lea','eax, [ebx + 0x20]'),('cmp','eax, 0x56433230'),
                     ('mov','eax, dword ptr [ebx + 0x24]'),('call','eax'),
                     ('mov','eax, dword ptr [ebx + 0x1c]'),('mov','eax, dword ptr [ebx + 0x14]'),
                     ('mov','ebx, dword ptr [edx + 4]'),('mov','edi, dword ptr [edx + 8]'),
                     ('mov','esi, dword ptr [edx + 0xc]'),('mov','eax, dword ptr [esp + 8]'),
                     ('cmp','eax, 1'),('adc','eax, 0'),('mov','esp, dword ptr [edx + 0x10]'),
                     ('add','esp, 4'),('jmp','dword ptr [edx + 0x14]'),('ret','')}
    if (not required_jump<=witnesses(jump) or jump['instruction_witnesses'][-1]!=
            dict(site='0x0064367C',mnemonic='ret',operands='')
            or jump['body_facts']['returns']!=[dict(site='0x0064367C',cleanup=0)]):
        raise ValueError('longjmp loses full saved-context/register/normalization/final RET protocol')
    required_probe = {('push','0xc'),('and','dword ptr [ebp - 4], 0'),
                      ('mov','eax, dword ptr [ebp + 8]'),('mov','eax, dword ptr [eax]'),
                      ('inc','eax'),('mov','dword ptr [ebp - 0x1c], eax'),
                      ('mov','eax, dword ptr [ebp - 0x14]'),('cmp','eax, 0xc0000005'),
                      ('sete','cl'),('mov','eax, ecx'),('mov','esp, dword ptr [ebp - 0x18]'),
                      ('xor','eax, eax'),('or','dword ptr [ebp - 4], 0xffffffff'),('ret','4')}
    if (not required_probe<=witnesses(probe) or probe['body_facts']['returns']!=
            [dict(site='0x0064DC40',cleanup=0),dict(site='0x0064DC4F',cleanup=4)]):
        raise ValueError('read probe loses full load/success/filter/handler/callee-cleanup protocol')
    absolute = jump['relocation_bindings'][0]
    if (absolute['target_kind']!='absolute' or absolute['symbol']!='__except_list'
            or absolute['offset']!=12 or absolute['type']!='DIR32' or absolute['addend']!=0
            or absolute['target_address']!='0x00000000'
            or absolute['absolute_definition']!=dict(member_offset=1210238,source_definition=
                dict(symbol='__except_list',offset=0,section=-1,type=0,storage=2))):
        raise ValueError('longjmp FS field loses actual external ABS definition')
    actual = [dict(owner=r['address'],calls=r['indirect_calls'],jumps=r['indirect_jumps'])
              for r in m['functions'] if r['indirect_calls'] or r['indirect_jumps']]
    if (actual!=m['runtime_dispatch'] or actual!=[dict(owner='0x00643604',
            calls=[dict(site='0x00643643',operand='eax')],
            jumps=[dict(site='0x00643679',operand='dword ptr [edx + 0x14]')])]):
        raise ValueError('longjmp loses opaque saved callback or saved-return dispatch')
    scope = m['scope_tables'][0]
    if (scope['owner']!='0x0064DC10' or scope['symbol']!='$T19221' or scope['member_offset']!=1245828
            or scope['address']!='0x006639E8' or scope['size']!=12 or scope['record_size']!=12
            or scope['records']!=[dict(index=0,enclosing=-1,filter='0x0064DC2D',handler='0x0064DC41')]
            or [b['code_entry']['source_offset'] for b in scope['callbacks']]!=[29,49]):
        raise ValueError('read probe loses full scope filter/handler entry topology')
    if (len(m['absolute_symbols'])!=1 or m['absolute_symbols'][0]['source_definition']!=
            dict(symbol='__except_list',offset=0,section=-1,type=0,storage=2)
            or m['absolute_symbols'][0]['target_value']!=0):
        raise ValueError('unwind graph loses full independent ABS provenance')


def check_absolute_symbols(m,members,comparison,coff,decoded):
    """Resolve an actual external ABS symbol, never a virtual-address-zero object."""
    for row in m['absolute_symbols']:
        name,data = members[row['member_offset']]
        if name!=row['member'] or hashlib.sha256(data).hexdigest()!=row['member_sha256']:
            raise ValueError('ABS provenance loses complete defining member identity')
        definitions=[]
        for off,(_,body) in members.items():
            try:entries=coff.parse_symbols(body,comparison.coff_name)[1]
            except ValueError:continue
            definitions.extend((off,d) for d in entries if d['symbol']==row['symbol'] and d['storage']==2 and d['section']!=0)
        if definitions!=[(row['member_offset'],row['source_definition'])]:
            raise ValueError('ABS provenance has no unique actual whole-archive definition')
        if row['source_definition']['section']!=-1 or row['source_definition']['offset']!=row['target_value']:
            raise ValueError('ABS definition changes external absolute value')
        graph={r['address']:r for r in m['functions']}
        for use in row['uses']:
            owner=graph[use['owner']]
            field=next((b for b in owner['relocation_bindings'] if b['offset']==use['offset']),None)
            if (not field or field['target_kind']!='absolute' or field['symbol']!=row['symbol']
                    or field['type']!=use['type'] or int(field['target_address'],16)!=row['target_value']
                    or field['absolute_definition']!=dict(member_offset=row['member_offset'],source_definition=row['source_definition'])):
                raise ValueError('ABS field loses actual defining source symbol')
            source=coff.parse_symbols(members[owner['member_offset']][1],comparison.coff_name)[1]
            refs=[d for d in source if d['symbol']==row['symbol']]
            if refs!=[dict(symbol=row['symbol'],offset=0,section=0,type=0,storage=2)]:
                raise ValueError('ABS field loses actual external referring source record')
            ins=next((i for i in decoded[use['owner']] if i.address-int(use['owner'],16)==use['instruction_offset']),None)
            if (not ins or use['segment']!='fs' or not ins.operands
                    or ins.disp_offset+use['instruction_offset']!=use['offset']
                    or not any(o.type==X86_OP_MEM and ins.reg_name(o.mem.segment)=='fs'
                               and o.mem.disp==row['target_value'] for o in ins.operands)):
                raise ValueError('ABS zero lacks actual FS segment/displacement instruction provenance')

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--evidence-only',action='store_true')
    args = parser.parse_args()
    old = module('jump_unwind_old','verify-runtime-error-origins.py')
    c = module('jump_unwind_target','compare-coff-function.py')
    archive_reader = module('jump_unwind_archive','verify-runtime-origins.py')
    coff = module('jump_unwind_coff','coff_data.py')
    startup = module('jump_unwind_geometry','verify-startup-dependency-origins.py')
    record = module('jump_unwind_ledger','verify-vendor-record-origins.py')
    facts = module('jump_unwind_facts','verify-game-lifetime-origins.py')
    imports_module = module('jump_unwind_imports','verify-import-origins.py')
    literal = module('jump_unwind_scalar','verify-runtime-external-origins.py')
    sections = module('jump_unwind_sections','verify-compiler-origins.py')
    target = c.verified_target(); m = manifest(); rows = verify_plan(m)
    functions = {r['address']:r for r in record.rows('functions.csv')}
    origins = {r['address']:r for r in record.rows('function-origins.csv')}
    graph = {**rows, **{r['address']:r for r in m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']}}
    for row in m['functions'] + m['auxiliary_bodies']:
        key = row['address']; a = int(key,16)
        if row['decision'] == 'library-control' and key in functions:
            raise ValueError('complete jump-unwind source control gains an invented candidate')
        actual = {k for k in functions if a < int(k,16) < a + row['size']}
        expected = {r['address'] for r in m['interior_labels']+m['retained_labels'] if r['parent'] == key}
        if actual != expected:
            raise ValueError('jump-unwind complete primary loses an actual interior candidate')
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
            raise ValueError('jump-unwind whole defining data topology differs')
        if row['writable'] != bool(int(desc['flags'],16)&0x80000000):
            raise ValueError('jump-unwind source data mutability differs')
        for d in desc['definitions']:
            state_map[(row['member_offset'],d['symbol'])] = a + d['offset']
            if d['storage'] == 2:
                global_state.setdefault(d['symbol'],set()).add(a + d['offset'])
        if raw is None:
            if (not int(desc['flags'],16)&0x80 or desc['relocations']
                    or startup.zero_fill_region(target,a,row['size']) != row['zero_fill_region']):
                raise ValueError('jump-unwind state lacks complete loader zero-fill provenance')
            continue
        actual = c.pe_bytes_at(target,a,len(raw)); linked = bytearray(raw)
        if len(desc['relocations']) != len(row['relocations']):
            raise ValueError('jump-unwind whole initialized data fields differ')
        for field,binding in zip(desc['relocations'],row['relocations']):
            if {k:binding[k] for k in field} != field:
                raise ValueError('jump-unwind initialized data relocation metadata differs')
            struct.pack_into('<I',linked,field['offset'],(int(binding['target_address'],16)+field['addend'])&0xffffffff)
        if (linked != actual or hashlib.sha256(raw).hexdigest() != row['source_sha256']
                or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
            raise ValueError('jump-unwind complete defining data source/target comparison differs')
        if row['writable']:
            if not any(base<=a and a+row['size']<=base+size and flags&0x80000000 and not flags&0x20000000 for base,size,flags in target_sections):
                raise ValueError('jump-unwind state loses whole writable target storage')
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
    decoder = Cs(CS_ARCH_X86,CS_MODE_32); decoder.detail = True
    scratch = ROOT / 'build/origin-jump-unwind-verification'; scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temporary:
        path = Path(temporary)/'VendorMember.obj'
        layout = m['sdk_layout']; probe = ROOT/layout['probe']
        profile = old.PROFILE+['/D_CRTBLD','/D_MT','/I','.tools/msvc710/Vc7/crt/src','/Zc:wchar_t']
        if (layout['profile'] != profile or hashlib.sha256(probe.read_bytes()).hexdigest() != layout['probe_sha256']
                or set(layout['headers']) != LAYOUT_HEADERS):
            raise ValueError('natural jump-unwind control source/profile/headers differ')
        for filename,digest in layout['headers'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest() != digest:
                raise ValueError('pinned jump-unwind control header differs')
        subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(probe),str(path),*profile],cwd=ROOT,capture_output=True,text=True,check=True)
        data = path.read_bytes(); defs = coff.parse_symbols(data,c.coff_name)[1]
        entry = next(d for d in defs if d['symbol'] == '_JumpUnwindLayoutProbe')
        layout_section = entry['section']
        raw,names = coff.readonly_section(data,layout_section,c.coff_name)
        if (names != layout['definitions'] or len(raw) != layout['source_section_size']
                or hashlib.sha256(raw).hexdigest() != layout['source_sha256']):
            raise ValueError('cold complete natural jump-unwind data objects/alignment differ')
        for obj in layout['objects']:
            entry = next(d for d in defs if d['symbol'] == obj['symbol'])
            if (entry['offset'] != obj['offset'] or entry['section'] != layout_section
                    or list(struct.unpack_from('<'+'I'*(obj['size']//4),raw,obj['offset'])) != obj['values']):
                raise ValueError('cold natural exception/thread SDK offsets or ABI constants differ')
        for filename,digest in m['vendor_sources'].items():
            if hashlib.sha256((ROOT/'.tools/msvc710/Vc7'/filename).read_bytes()).hexdigest()!=digest:
                raise ValueError('pinned complete jump-unwind vendor source differs')
        for control in m['call_controls']:
            source,fields=c.object_function(path,control['coff_symbol']);ins=list(decoder.disasm(source,0))
            metadata=[{k:f[k] for k in ('offset','type','symbol','addend','local_symbol_offset')} for f in fields]
            if (len(source)!=control['size'] or metadata!=control['relocation_metadata']
                    or hashlib.sha256(source).hexdigest()!=control['source_sha256']
                    or facts.body_facts(ins)!=control['body_facts']
                    or [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]!=control['instructions']):
                raise ValueError('cold complete jump-unwind ABI/SEH/C++ controls differ')
        check_probe_generated(data,path,m,c,coff,old,decoder,facts)
        observed_catalog = []
        decoded = {}
        for row in m['functions']+m['auxiliary_bodies']+m['anchors']+m['diagnostic_contexts']:
            a = int(row['address'],16); key = row['address']
            if row['decision'] == 'library' and not args.evidence_only:
                check_ledger(row,functions[key],origins[key])
            if row['decision'] == 'anchor':
                if (origins[key]['origin'] != row['origin'] or origins[key]['evidence_id'] != row['origin_evidence']
                        or row['control_flow_basis'] != 'Independent complete runtime/archive controls replayed through R141'):
                    raise ValueError('jump-unwind retained independent complete code origin differs')
            data = member(row); path.write_bytes(data)
            source,fields = object_code(path,row,c,coff)
            actual = c.pe_bytes_at(target,a,row['size'])
            defs = coff.parse_symbols(data,c.coff_name)[1]
            primary = next(d for d in defs if d['symbol'] == row['coff_symbol'] and d['section']>0)
            if (primary != row['source_definition'] or len(source) != row['size']
                    or hashlib.sha256(source).hexdigest() != row['source_sha256']
                    or hashlib.sha256(actual).hexdigest() != row['body_sha256']):
                raise ValueError('jump-unwind complete own source extent/hash differs')
            old.compare_fields(source,fields,actual,a,row['relocation_bindings'],c)
            if [f['local_symbol_offset'] for f in fields] != [b['local_symbol_offset'] for b in row['relocation_bindings']]:
                raise ValueError('jump-unwind full local typed field provenance differs')
            for d in defs:
                if (d['section'] == primary['section'] and primary['offset'] <= d['offset'] < primary['offset']+row['size']
                        and d['storage'] in (2,3,6) and not d['symbol'].startswith('.')):
                    observed_catalog.append(dict(owner=key,member_offset=row['member_offset'],source_definition=d,
                                                 target_address=f"0x{a+d['offset']-primary['offset']:08X}",
                                                 source_offset=d['offset']-primary['offset']))
            ins = decode_code(row,actual,a,decoder); decoded[key] = ins
            if sum(i.size for i in ins) != row['code_size'] or facts.body_facts(ins) != row['body_facts']:
                raise ValueError('jump-unwind whole code instruction/control-flow inventory differs')
            witnesses = [dict(site=f'0x{i.address:08X}',mnemonic=i.mnemonic,operands=i.op_str) for i in ins]
            branches = [dict(site=f'0x{i.address:08X}',target=f'0x{i.operands[0].imm:08X}') for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type == X86_OP_IMM]
            calls = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.mnemonic == 'call' and i.operands[0].type != X86_OP_IMM]
            jumps = [dict(site=f'0x{i.address:08X}',operand=i.op_str) for i in ins if i.group(CS_GRP_JUMP) and i.operands[0].type != X86_OP_IMM]
            if (witnesses != row['instruction_witnesses'] or branches != row['branches']
                    or calls != row['indirect_calls'] or jumps != row['indirect_jumps']):
                raise ValueError('jump-unwind complete branch/API/ABI/dispatch inventory differs')
            if row['decision'] in ('anchor','pending'):
                continue
            for b in row['relocation_bindings']:
                if b['target_kind'] == 'import':
                    startup.check_import_binding(b,imports)
                elif b['target_kind'] == 'state' and (b['type'] != 'DIR32' or state_map.get((row['member_offset'],b['symbol'])) != int(b['target_address'],16)):
                    raise ValueError('jump-unwind field lacks member-local/whole strong data provenance')
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
            raise ValueError('jump-unwind code entry catalog differs from actual complete source definitions')
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
                        raise ValueError('jump-unwind local transfer does not reach an actual instruction start')
                    continue
                site = f'0x{i.address:08X}'; observed_sites.add(site); edge = edges.get(site)
                if not edge or int(edge['target'],16) != dest:
                    raise ValueError('jump-unwind direct transfer lacks full defining edge provenance')
                if edge['basis'] == 'typed-REL32':
                    field = next((b for b in row['relocation_bindings'] if b['type'] == 'REL32' and b['offset'] == i.address-a+i.imm_offset),None)
                    if (not field or field['target_kind'] != 'callee' or field['offset'] != edge['field_offset']
                            or field['target_address'] != edge['target'] or field['code_entry'] != edge['code_entry']):
                        raise ValueError('jump-unwind direct transfer loses its actual typed field')
                    owner = graph[field['code_entry']['owner']]
                else:
                    owner = graph[edge['owner']]
                    if source_ins[i.address-a].operands[0].imm != edge['source_target_offset']:
                        raise ValueError('jump-unwind same-section transfer changes its source-relative target')
                if dest not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('jump-unwind shared/typed entry does not reach an actual full-owner instruction')
            if observed_sites != set(edges):
                raise ValueError('jump-unwind complete direct edge inventory differs')
        for data in m['state_data']:
            for b in data['relocations']:
                if b['target_kind']=='state':
                    resolve_state_reference(dict(member_offset=data['member_offset'],symbol=b['symbol'],target_address=b['target_address']),state_map,global_state)
                    continue
                owner = graph[b['code_entry']['owner']]
                if int(b['target_address'],16) not in {i.address for i in decoded[owner['address']]}:
                    raise ValueError('jump-unwind data pointer does not reach a complete actual code entry')
        check_absolute_symbols(m,members,c,coff,decoded)
    for script in ('verify-exception-frame-origins.py',):
        result = subprocess.run([str(ROOT/'scripts/repo-python'),'scripts/'+script],cwd=ROOT,capture_output=True,text=True)
        if result.returncode:
            raise ValueError('retained independent full R141 replay failed: '+result.stderr[-1500:])
    print('R144 origins OK: two complete longjmp/read-probe primaries / 187 bytes / eight fields; final longjmp RET retained in full 121-byte AUX; five full independent unwind/NLG/SEH anchors / 236 bytes / five fields; whole 12-byte filter/handler scope with both actual interior entries; independently resolved whole-archive external ABS __except_list definition and FS displacement; exact saved-context/opaque callback/register-return protocol; cold real 88-byte SDK jump-buffer/SEH layout and all natural control/code/data sections; full retained R141 dependency replay; local origin-only acceptance, no source or exact credit.')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
