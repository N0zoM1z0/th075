#!/usr/bin/env python3
"""Verify the observed 8-byte black-surface owner and its authored destructor."""
from __future__ import annotations
import csv, hashlib, importlib.util, json, struct, sys, tomllib
from pathlib import Path
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86 import X86_OP_IMM, X86_OP_MEM
ROOT=Path(__file__).resolve().parents[1]
def module(name,filename):
    spec=importlib.util.spec_from_file_location(name,ROOT/'scripts'/filename)
    mod=importlib.util.module_from_spec(spec);spec.loader.exec_module(mod);return mod
def rows(path):
    with (ROOT/'config'/path).open(newline='',encoding='utf-8') as f:return {r['address']:r for r in csv.DictReader(f)}
def fail(message):raise ValueError(message)
def main():
    manifest=json.loads((ROOT/'config/black-surface-owner-origin-evidence.json').read_text())
    if manifest['evidence_id']!='R107':fail('black-surface evidence ID differs')
    cmp=module('black_surface_target','compare-coff-function.py');target=cmp.verified_target()
    if hashlib.sha256(target).hexdigest()!=manifest['target_sha256']:fail('target image identity differs')
    decoder=Cs(CS_ARCH_X86,CS_MODE_32);decoder.detail=True
    def verify_body(name):
        r=manifest['functions'][name];address=int(r['address'],16);size=r['size']
        raw=cmp.pe_bytes_at(target,address,size)
        if hashlib.sha256(raw).hexdigest()!=r['body_sha256']:fail(name+' complete target body differs')
        ins=list(decoder.disasm(raw,address))
        if not ins or ins[-1].mnemonic not in ('ret','retf','retn') or sum(i.mnemonic.startswith('ret') for i in ins)!=r['return_count']:
            fail(name+' whole-body return shape differs')
        calls=[]
        for i in ins:
            if i.mnemonic!='call':continue
            op=i.operands[0]
            if op.type==X86_OP_IMM:calls.append({'site':f'0x{i.address:08X}','target':f'0x{op.imm:08X}','kind':'direct'})
            elif op.type==X86_OP_MEM:
                m=i.operands[0].mem
                calls.append({'site':f'0x{i.address:08X}','kind':'indirect','base':i.reg_name(m.base) if m.base else None,'index':i.reg_name(m.index) if m.index else None,'disp':m.disp,'operand_size':i.operands[0].size})
        if calls!=r['calls']:fail(name+' complete direct/indirect call graph differs')
        return raw,ins
    bodies={name:verify_body(name) for name in manifest['functions']}
    # The authored destructor performs exactly one COM Release through vtable slot +8.
    dtor=bodies['destructor'][1]
    indirect=[i for i in dtor if i.mnemonic=='call' and i.operands[0].type==X86_OP_MEM]
    if len(indirect)!=1:
        fail('destructor does not contain exactly one indirect COM call')
    op=indirect[0].operands[0]
    if op.size!=4 or op.mem.base==0 or op.mem.index!=0 or op.mem.disp!=8:
        fail('destructor COM Release slot is not the observed vtable +8 call')
    if any(i.mnemonic=='call' and i.operands[0].type==X86_OP_IMM for i in dtor):
        fail('destructor unexpectedly contains a direct helper call')
    # The 44-byte scalar-deleting wrapper is compiler-origin, and delegates to
    # the authored destructor before calling the original operator delete.
    wrapper=bodies['deleting_wrapper'][1]
    direct=[i.operands[0].imm for i in wrapper if i.mnemonic=='call' and i.operands[0].type==X86_OP_IMM]
    if direct!=[0x004170B0,0x00640F15]:fail('scalar-deleting wrapper call order differs')
    # Bind the complete initializer/release parents to the same global pointer.
    units=tomllib.loads((ROOT/'config/match-units.toml').read_text())['units']
    init=units['game-globals-initialize-sound-004175a0'];release=units['game-globals-release-00417430']
    def reloc(unit,offset,typ,target_address):
        hit=[x for x in unit['relocations'] if x['offset']==offset]
        if len(hit)!=1 or hit[0]['type']!=typ or hit[0]['target']!=target_address:
            fail(unit['source']+' lifecycle relocation differs at '+hex(offset))
    reloc(init,128,'REL32',0x0064159D)
    reloc(init,155,'REL32',0x00417000)
    reloc(init,188,'DIR32',0x006714C4)
    reloc(release,270,'DIR32',0x006714C4)
    reloc(release,295,'REL32',0x0041A140)
    if sorted(x['allocation_size'] for x in manifest['allocation_sites'])!=[8,20,120]:
        fail('InitializeSound original new sizes differ')
    if len(manifest['constructor_call_sites'])!=1 or len(manifest['release_wrapper_call_sites'])!=1:
        fail('parent lifecycle call sites differ')
    # The surrounding source-origin decisions are independent and remain reviewed.
    origins=rows('function-origins.csv')
    expected={'0x00417000':('authored','authored','R053'),
              '0x00417430':('authored','authored','R052'),
              '0x004175A0':('authored','authored','R052'),
              '0x0041A140':('compiler','exclude','R037'),
              '0x004170B0':('authored','authored','R107')}
    for address,shape in expected.items():
        r=origins[address]
        if (r['origin'],r['disposition'],r['evidence_id'])!=shape:
            fail('lifecycle origin ledger differs at '+address)
    evidence=rows('authored-origin-evidence.csv')
    e=evidence['0x004170B0']
    d=manifest['functions']['destructor']
    if (int(e['size'])!=27 or e['body_sha256']!=d['body_sha256']
            or e['evidence_id']!='R107' or int(e['return_count'])!=1
            or int(e['internal_branch_count'])!=0 or int(e['external_branch_count'])!=0):
        fail('authored destructor whole-body evidence row differs')
    functions=rows('functions.csv');f=functions['0x004170B0']
    if (f['status']!='matching' or float(f['match_percent'])!=100.0
            or f['owner']!='authored' or f['source_file']!='src/WindowOverlayF212.cpp'):
        fail('authored destructor source/match ledger differs')
    matches=rows('matches.csv');m=matches['0x004170B0']
    if (m['status']!='matching' or float(m['match_percent'])!=100.0
            or int(m['size'],0)!=27 or m['unit']!='game-globals-black-surface-destructor-004170b0'):
        fail('authored destructor exact match row differs')
    source=(ROOT/'src/WindowOverlayF212.cpp').read_text()
    if 'WindowOverlayF212::~WindowOverlayF212()' not in source or 'texture->Release();' not in source:
        fail('natural C++ owner destructor source differs')
    print('R107 black-surface owner origin OK: complete 27-byte authored COM destructor; 8-byte allocation/constructor/release chain; compiler deleting wrapper excluded; nominal class identity and private layout remain inferred.')
    return 0
if __name__=='__main__':
    try:raise SystemExit(main())
    except (OSError,KeyError,IndexError,ValueError,struct.error) as exc:
        print('error: '+str(exc),file=sys.stderr);raise SystemExit(1)
