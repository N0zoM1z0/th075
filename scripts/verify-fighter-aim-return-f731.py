#!/usr/bin/env python3
"""F731: complete original native fighter 1F8 (1471B/422x86/45 COFF).

One entire pinned VC7.1 00543210 boss, with true normal C++ two-angle
stage14 and native integer FIMUL/NEG/FILD, actual 80.0f motion,
1F8 source followed by 1FA original placeholder. All 45 physical
original typed PE fields tested at shifted native ordinals, original
x87 compare/stack/lvalue negatives retained. Genuine 200/201
REGRESSION RECOVERY 67/85->0 in this compiled parent, 2EF and
2D0/2D1/2DD/2DE also independently original-GPR-strict (not
byte-exact entire function). Recheck 1F4-1F7 and full 943B afterRET.
No synthetic frame, graft or 943 accepted-unit mass replay.
"""
from __future__ import annotations
import difflib
import importlib.util
import json
import shutil
import sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f731-fighter-aim-return'
BOSS=0x00543210
SYMBOL=f'?Advance@FighterSwitchF598_Boss{BOSS:08X}@@QAEXXZ'
ACTION=0x1F8
NATIVE_LO=0x0054B43A
NATIVE_HI=0x0054B9F9
NATIVE_CODE=1471
NATIVE_X86=422
NATIVE_FIELD_COUNT=45
SOURCE_START=6404
SOURCE_X86=424
SOURCE_CODE=1455
SOURCE_X87_SLOTS={
 (256,258):('0x100','0x74'),(257,259):('0x100','0x74'),
 (317,319):('0x104','0x78'),(318,320):('0x104','0x78'),
 (344,346):('0x108','0x7c'),(345,347):('0x108','0x7c'),
 (378,380):('0x10c','0x80'),(379,381):('0x10c','0x80')}
EDIT_BLOCKS=(
 ('replace',127,128,127,129),('replace',130,131,131,132),
 ('replace',139,140,140,142),('replace',142,143,144,145),
 ('insert',312,312,314,315),('delete',313,314,316,316))
ORIGINAL_DEST_SYMBOLS={
  0x0040FBB0:'SetMotionStateAt40FBB0',
  0x0040FB70:'MotionAt40FB70',
  0x00483300:'CalculateAngleAt483300',
  0x006406AC:'__ftol2',
  0x00657828:'g_StormAngleDenominatorAt00657828',
  0x00657CBC:'g_F731_AimOffsetAt00657CBC',
  0x00453A70:'SpawnDirectedAt453A70',
}
CONTEXT_ACTIONS=(0x200,0x201,0x2D0,0x2D1,0x2DD,0x2DE,0x2EF)


def need(cond,message):
    if not cond:raise ValueError(message)


def load(name,path):
    sp=importlib.util.spec_from_file_location(name,ROOT/path)
    need(sp is not None and sp.loader is not None,'missing original PE source checker: '+path)
    m=importlib.util.module_from_spec(sp)
    sys.modules[name]=m
    sp.loader.exec_module(m)
    return m


def source_with_aim_return(src):
    mark='        case 0x1F8: g_FighterProbeMarker = 505; break;'
    need(src.count(mark)==1,'original native 1F8 source placeholder absent')
    src=src.replace(mark,'#include "FighterAimReturnF731.inc"')
    decl='void SetMotionStateAt40FBB0(int,float,int);'
    need(src.count(decl)==1,'original target 0040FBB0 C++ receiver declaration missing')
    src=src.replace(decl,decl+' void MotionAt40FB70(float,float);')
    glob='extern float g_F728_PositiveDragAt006583FC;'
    need(src.count(glob)==1,'native original 006583FC float global declaration missing')
    src=src.replace(glob,glob+'\nextern float g_F731_AimOffsetAt00657CBC;')
    need(src.count('#include "FighterAimReturnF731.inc"')==1,
         'whole native 1F8 must appear as exactly one meaningful source handler')
    return src


def verify_complete_native_1f8(reader,pe,decoder,f676,f729,by,ins,refs):
    need(by[ACTION]==NATIVE_LO and by[0x1FA]==NATIVE_HI
         and NATIVE_HI-NATIVE_LO==NATIVE_CODE,
         'original whole native 1F8 physical PE bounds wrong')
    original=list(decoder.disasm(reader.pe_bytes_at(pe,NATIVE_LO,NATIVE_CODE),NATIVE_LO))
    source=ins[SOURCE_START:SOURCE_START+SOURCE_X86]
    need(len(original)==NATIVE_X86 and len(source)==SOURCE_X86
         and sum(x.size for x in original)==NATIVE_CODE
         and sum(x.size for x in source)==SOURCE_CODE
         and original[-1].mnemonic==source[-1].mnemonic=='jmp'
         and original[-1].op_str=='0x5515c2',
         'complete original 1471B/422-x86 source 1455B/424 x86 body not attested')
    native_fields=f676.original_fields(original)
    actual=[r for r in refs if source[0].address<=r['offset']<source[-1].address+source[-1].size]
    need(len(native_fields)==len(actual)==NATIVE_FIELD_COUNT,
         'original 1F8 all 45 typed source-targeted PE references missing')
    all_fields=[]
    for (ordinal,target,mnemonic),reloc in zip(native_fields,actual):
        want=ORIGINAL_DEST_SYMBOLS.get(target,f729.DESTINATIONS.get(target))
        if target==0x00453C80:
            want='SpawnAt453C80' if ordinal==264 else 'SpawnMixedAt453C80'
        owner=next((i for i,x in enumerate(source)
                    if x.address<=reloc['offset']<x.address+x.size),None)
        expected=ordinal+int(ordinal>=127)+int(ordinal>=139)
        need(want is not None and want in reloc['symbol']
             and reloc['type']==('REL32' if mnemonic=='call' else 'DIR32')
             and reloc['addend']==0 and reloc['local_symbol_offset'] is None
             and owner==expected and source[owner].mnemonic==mnemonic,
             f'original 1F8 PE target {target:#x} native ordinal {ordinal} '
             f'actual source field instruction {owner} changed')
        all_fields.append({'original_native_ordinal':ordinal,
                          'source_ordinal':owner,
                          'native_target':f'0x{target:08X}',
                          'source_COFF_symbol':reloc['symbol']})
    edits=tuple((tag,a,b,c,e) for tag,a,b,c,e in
                difflib.SequenceMatcher(a=[x.mnemonic for x in original],
                  b=[x.mnemonic for x in source],autojunk=False).get_opcodes()
                if tag!='equal')
    need(edits==EDIT_BLOCKS
         and original[107].op_str==source[107].op_str=='ah, 5'
         and original[108].mnemonic==source[108].mnemonic=='jp'
         and original[127].mnemonic==original[139].mnemonic=='fcomp'
         and [x.mnemonic for x in source[127:129]]==['fld','fcompp']
         and [x.mnemonic for x in source[140:142]]==['fld','fcompp'],
         'original physical 1F8 exact first boundary, real two nonnative x87 compare edits drift')
    for (ni,ci),(native_slot,source_slot) in SOURCE_X87_SLOTS.items():
        n,s=original[ni],source[ci]
        need(n.mnemonic==s.mnemonic
             and f'[ebp - {native_slot}]' in n.op_str
             and f'[ebp - {source_slot}]' in s.op_str,
             f'original native 1F8 deep physical integer-x87 temporary {ni} shifted')
    need(original[343].mnemonic==source[345].mnemonic=='neg'
         and original[345].mnemonic==source[347].mnemonic=='fild'
         and original[318].mnemonic==source[320].mnemonic=='fimul'
         and original[351].op_str==source[353].op_str=='0x42a00000'
         and original[392].op_str==source[394].op_str=='0x338'
         and original[328].mnemonic==source[330].mnemonic=='call'
         and original[361].mnemonic==source[363].mnemonic=='call',
         'original 1F8 actual 80.0f, NEG/FIMUL, two 00483300 calls, 0x338 shot differ')
    need(source[358].mnemonic=='mov'
         and source[359].mnemonic=='push'
         and source[360].mnemonic=='mov'
         and source[361].mnemonic=='mov'
         and source[362].mnemonic=='push',
         'real native second angle call raw float source lvalue lost')
    need(ins[SOURCE_START+SOURCE_X86].mnemonic=='mov'
         and ins[SOURCE_START+SOURCE_X86].op_str.endswith(', 0x1fb'),
         'real original 1F8 must terminate before source 1FA placeholder')
    return {'native_physical_PE_bounds':[f'0x{NATIVE_LO:08X}',f'0x{NATIVE_HI:08X}'],
       'native_complete_CODE_bytes':NATIVE_CODE,
       'current_source_complete_CODE_bytes':SOURCE_CODE,
       'native_x86':NATIVE_X86,'source_x86':SOURCE_X86,
       'original_typed_PE_COFF_fields':len(all_fields),
       'all_original_source_field_symbols_and_owners':all_fields,
       'real_native_vs_source_instruction_edits':edits,
       'original_vs_source_real_x87_scratch_slots':[
           {'original_x86_ordinal':ni,'generated_x86_ordinal':ci,
            'original_native_EBP':nslot,'compiler_source_EBP':cslot}
           for (ni,ci),(nslot,cslot) in SOURCE_X87_SLOTS.items()],
       'native_whole_original_1F8_byte_exact':False}


def verify_context_restore(reader,pe,real,f676,f598,by,ins,refs,boss,f728):
    ret=ins[-1].address+ins[-1].size
    data=reader.pe_bytes_at(pe,BOSS+boss['size'],boss['postret_size'])
    mapping={}
    for x in refs:
        if x['offset']>=ret:
            off=x['offset']-ret
            native_label=int.from_bytes(data[off:off+4],'little')
            mapping.setdefault(native_label,x['local_symbol_offset'])
    rows=[]
    for action in CONTEXT_ACTIONS:
        lo=by[action]
        hi=min(x for x in by.values() if x>lo)
        native=list(real.disasm(reader.pe_bytes_at(pe,lo,hi-lo),lo))
        addr=mapping.get(lo)
        need(addr is not None,'complete original context action native switch label missing')
        st=next((i for i,x in enumerate(ins) if x.address==addr),None)
        need(st is not None,'native context source target not an x86 instruction')
        source=ins[st:st+len(native)]
        native_fields=f676.original_fields(native)
        actual_fields=[x for x in refs if source[0].address<=x['offset']<source[-1].address+source[-1].size]
        nonfields={i for i,t,m in native_fields if m!='call'}
        wrong=[i for i,(a,b) in enumerate(zip(f598.normalized(native),
                                              f598.normalized(source)))
               if a!=b and i not in nonfields]
        need(not wrong and len(native_fields)==len(actual_fields)
             and all(a.mnemonic==b.mnemonic and a.size==b.size
                     for a,b in zip(native,source))
             and sum(x.size for x in native)==sum(x.size for x in source),
             f'new native 1F8 must genuinely restore exact original source GPR '
             f'context in action {action:#x}; wrong {wrong[:10]}')
        rows.append({'original_native_action':f'0x{action:X}',
             'full_original_internal_CODE_B':hi-lo,
             'native_original_x86':len(native),
             'typed_source_fields_in_native_original_order':len(actual_fields),
             'normalized_native_GPR_CFG_mismatch_count':0,
             'physical_native_context_strict_NOT_whole_function_exact':True})
    need([x['original_native_action'] for x in rows]
         ==[f'0x{a:X}' for a in CONTEXT_ACTIONS],
         'selected original native source context comparison lost an action')
    return rows


def main():
    reader=load('f731_reader','scripts/compare-coff-function.py')
    acts=load('f731_actions','scripts/report-fighter-action-handlers.py')
    f728=load('f731_728','scripts/verify-fighter-random-arcs-f728.py')
    f729=load('f731_729','scripts/verify-fighter-return-boundary-f729.py')
    f676=load('f731_fields','scripts/verify-fighter-cloud-burst-f676.py')
    f598=load('f731_norm','scripts/verify-fighter-singleton-contact-f598.py')
    f701=load('f731_phys','scripts/verify-fighter-four-tier-volley-f701.py')
    pe=reader.verified_target()
    real=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((ROOT/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==BOSS)
    report,mapped=acts.report_boss(reader,pe,real,boss)
    by={x['action']:int(x['handler'],16) for x in mapped}
    src,compiler=f728.source_for_complete_parent(reader,pe,real,boss,report,mapped)
    src=f729.source_with_return_boundaries(src)
    src=source_with_aim_return(src)
    obj=compiler.compile_whole_parent(src)
    OUT.mkdir(parents=True,exist_ok=True)
    (OUT/'Boss00543210-1F8.cpp').write_text(src)
    shutil.copyfile(obj,OUT/'Boss00543210-1F8.obj')
    if obj.with_name('compiler.log').exists():
        shutil.copyfile(obj.with_name('compiler.log'),OUT/'compiler.log')
    code,refs=reader.object_function(obj,SYMBOL)
    ins=[]
    for i in real.disasm(code,0):
        ins.append(i)
        if i.mnemonic=='ret':break
    new=verify_complete_native_1f8(reader,pe,real,f676,f729,by,ins,refs)
    earlier=f728.case_evidence(reader,pe,real,f676,f598,f701,by,
                                ins,refs,following_native_1f6=True)
    prior=f729.real_native_cases(reader,pe,real,f676,f598,by,
                                 ins,refs,following_native_1f8=True)
    retdata=f728.complete_native_switch_DATA(reader,pe,real,boss,code,ins,refs)
    reg=f728.verify_prior_context_regression(reader,pe,real,f676,f598,by,
            ins,refs,boss,source_expected_gpr={0x200:0,0x201:0,0x2EF:0})
    more=verify_context_restore(reader,pe,real,f676,f598,by,ins,refs,boss,f728)
    need(all(x['current_source_nonfield_GPR_CFG_differences']==0 for x in reg)
         and retdata['original_nonrelocation_afterRET_BYTES_equal']==319,
         'true native 200/201 67/85 source GPR errors MUST be corrected '
         'by real 1F8 full code, with entire original afterRET DATA')
    summary={'original_entire_giant':'0x00543210',
       'original_whole_CODE_B_still_NONEXACT':boss['size'],
       'new_whole_original_physically_bounded_action':new,
       'new_source_backed_original_internal_CODE_B_UNCREDITED':NATIVE_CODE,
       'new_native_x86_positions':NATIVE_X86,
       'new_physical_native_typed_PE_COFF_fields':NATIVE_FIELD_COUNT,
       'older_original_1F4_1F5':earlier,
       'older_original_1F6_1F7':prior,
       'original_200_201_2EF_native_GPR_PHASE_RECOVERY':reg,
       'other_selected_original_strict_contexts':more,
       'all_original_native_943B_afterRET_DATA':retdata,
       'whole_original_GAME_function_byte_exact':False,
       'new_accepted_exact_GAME_function_CODE_bytes':0}
    (OUT/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print('F731 authentic native 00543210 action 1F8 original 1471 B/422 '
          'x86/45 physical typed PE fields fully source-backed in one '
          'VC7.1 giant C++: compiler 1455 B/424 x86, native first float '
          'TEST AH,5/JP, two angle 00483300, NEG before FILD, FIMUL '
          'direction, genuine 80.0f motion and 338 projectile, 45/45 '
          'original target/symbol/addend/owner fields. NONEXACT: two '
          'extra FLD/FCOMPP, native deep EBP scratch and first angle '
          'read-order differences. MAJOR compiler phase recovery: original '
          '0x200/0x201 real GPR errors 67/85 -> 0/0; 0x2D0/0x2D1, '
          '0x2DD/0x2DE and 0x2EF also GPR strict in THIS new parent. '
          'Original 1F4-1F7 full source negatives and complete 943-byte '
          'original afterRET DATA with all 156 DIR32 labels and 319 '
          'original sparse bytes rechecked; no whole game function '
          'exact credit and no mass 943-unit cold replay.')


if __name__=='__main__':
    main()
