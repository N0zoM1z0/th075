#!/usr/bin/env python3
"""Shared selected-UNIT physical PE checker for 005214B0 after F894.

The source of the 46,755-B original fighter remains NONEXACT.
Recheck all previous 70 source-backed original case interiors in
SAME new VC7.1 whole-father COFF and all 901B afterRET DATA.
Keep original 1FD and 252/254 source-deficit negatives honest;
no accepted whole callable CODE credit or whole corpus replay.
"""
from pathlib import Path
import importlib.util,json,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
ADDR=0x005214B0
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
def need(ok,msg):
    if not ok:raise ValueError(msg)
def load(tag,filename):
    sp=importlib.util.spec_from_file_location(tag,R/'scripts'/filename)
    need(sp is not None and sp.loader is not None,'missing pinned native PE helper '+filename)
    mod=importlib.util.module_from_spec(sp);sys.modules[tag]=mod;sp.loader.exec_module(mod);return mod

def modules():
    names={
      'rd':'compare-coff-function.py',
      'ac':'report-fighter-action-handlers.py',
      'f834':'verify-scripted-fighter-fourway-c8-f834.py',
      'f820':'verify-scripted-fighter-landing-trio-f820.py',
      'f874':'verify-scripted-fighter-owner-dual-f874.py',
      'f875':'verify-scripted-fighter-owner-stages-1ff-f875.py',
      'f877':'verify-scripted-fighter-owner-wave-200-f877.py',
      'f878':'verify-scripted-fighter-stage-201-f878.py',
      'f879':'verify-scripted-fighter-stage-252-254-f879.py',
      'f880':'verify-scripted-fighter-stage255-257-f880.py',
      'f881':'verify-scripted-fighter-floatx-258-f881.py',
      'f883':'verify-scripted-fighter-physical259-f883.py',
      'f884':'verify-scripted-fighter-stage2bc-f884.py',
      'f885':'verify-scripted-fighter-stage2bd-f885.py',
      'f886':'verify-scripted-fighter-stage2be-f886.py',
      'f888':'verify-scripted-fighter-2c0-2c1-f888.py',
      'f890':'verify-scripted-fighter-full2c2-f890.py',
      'f892':'verify-scripted-fighter-stage2db-f892.py',
      'f893':'verify-scripted-fighter-stage2dc-f893.py',
      'f894':'verify-scripted-fighter-physical2dd-f894.py',
      'zero':'verify-fighter-actionzero-natural-source.py',
      'sw':'verify-fighter-natural-switch-probes.py'}
    return {k:load('f895common_'+k,v) for k,v in names.items()}

def parse_coff(rd,d,obj,marker,minimum):
    code,refs=rd.object_function(Path(obj),SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    need(ins and ins[-1].mnemonic=='ret','entire original giant source missing RET')
    ret=ins[-1].address+ins[-1].size
    marks=[j for j,x in enumerate(ins) if x.mnemonic=='mov'
          and x.op_str.endswith(', '+hex(marker))
          and any('g_FighterProbeMarker' in r['symbol']
                 and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marks)==1 and marks[0]>=minimum,
         'next native case original source marker not unique '+hex(marker))
    return code,refs,ins,ret,marks[0]

def native_environment(M,code,refs,ins,ret):
    rd=M['rd'];pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads(
       (R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
       if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==
         (46755,901,13230),'pinned original 46755B fighter or native 901B DATA changed')
    report,mapping=M['ac'].report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mapping}
    need(len(code)-ret==901
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'current whole fighter native saved-this or afterRET DATA changed')
    dense,sparse,maps=M['zero'].verify_physical_tables(
       boss,report,pe,rd,M['sw'],ins,code,refs,ret)
    need(dense>0 and sparse>0 and maps>0,
         'five physical original afterRET 901B packed tables failed')
    return pe,d,by

def verify_previous(M,pe,d,by,code,refs,ins,current_case_start,extra=()):
    """Verify 70 previous original cases plus source-backed extra action tuples.

    extra entries are action,next_action,x86,B,original_PE_fields,wrong_B
    for new original game cases appended beyond original action2DD.
    A case is not an independently callable original function.
    """
    rd=M['rd'];f834=M['f834'];f820=M['f820'];f874=M['f874']
    f875=M['f875'];f877=M['f877'];f878=M['f878']
    f879=M['f879'];f880=M['f880'];f881=M['f881'];f883=M['f883']
    f884=M['f884'];f885=M['f885'];f886=M['f886']
    f888=M['f888'];f890=M['f890'];f892=M['f892'];f893=M['f893'];f894=M['f894']
    earlier_receipt=json.loads(
        (R/'.analysis/f894-scripted2dd/verified-summary.json').read_text())
    older=earlier_receipt['previous_46_original_source_cases_physically_reverified']
    need(len(older)==46 and older[0]['case']=='0xc8'
         and older[-1]['case']=='0x1fc',
         '46 earliest PE-backed original game source receipts missing')
    late=[
      (0x1fe,0x1ff,107,392,9,f874.F874_1FE_BAD),
      (0x1ff,0x200,149,533,9,f875.BAD),
      (0x200,0x201,177,634,10,f877.BAD),
      (0x201,0x252,80,267,8,f878.BAD)]
    for action,nxt,nb,nx,sb,_ in f879.CASES:
        late.append((action,nxt,nx,nb,6,f879.BAD_253 if action==0x253 else None))
    for action,nxt,nb,nx,nf in f880.CASES:
        late.append((action,nxt,nx,nb,nf,f880.BAD[action]))
    late += [
      (0x258,0x259,60,206,6,f881.BAD),
      (0x259,0x2bc,60,206,6,f883.BAD),
      (0x2bc,0x2bd,228,803,22,f884.BAD),
      (0x2bd,0x2be,239,855,24,f885.WRONG),
      (0x2be,0x2bf,136,461,15,f886.BAD),
      (0x2bf,0x2c0,138,473,15,[469,470]),
      (0x2c0,0x2c1,85,288,11,f888.BAD[0x2c0]),
      (0x2c1,0x2c2,81,276,11,f888.BAD[0x2c1]),
      (0x2c2,0x2c3,608,2274,50,f890.EXPECTED_WRONG),
      (0x2c3,0x2db,20,69,4,[65,66]),
      (0x2db,0x2dc,162,556,13,f892.WRONG),
      (0x2dc,0x2dd,188,660,17,f893.BAD),
      (0x2dd,0x2e4,153,535,14,f894.BAD)]
    late=list(late)+list(extra)
    earliest=current_case_start-(107+sum(x[2] for x in late)) - \
             sum(x['native_complete_x86'] for x in older)
    need(earliest>0 and ins[earliest].address<ins[current_case_start].address,
         'complete native original 70-case source ordering impossible')
    cursor=earliest;checks=[]
    for ix,x in enumerate(older):
        act=int(x['case'],16)
        nxt=int(older[ix+1]['case'],16) if ix+1<len(older) else 0x1fd
        n=x['native_complete_x86'];part=ins[cursor:cursor+n];cursor+=n
        r=f834.physical_case(rd,pe,d,code,refs,part,by,act,
             x['native_whole_inner_B'],x['original_typed_PE_fields'],
             x['real_nonrelocation_wrong_offsets'],nxt,f820)
        checks.append(r)
        if act==0x1a0:
            need(part[3].op_str==part[7].op_str==hex(part[22].address),
                 'original native 1A0 true conditional multiplier lost')
    originalfd=list(d.disasm(rd.pe_bytes_at(pe,by[0x1fd],386),by[0x1fd]))
    fd=ins[cursor:cursor+107];cursor+=107
    need(fd[-1].address+fd[-1].size-fd[0].address==385
         and originalfd[99].size==6 and fd[99].size==5
         and fd[100].op_str==hex(fd[104].address),
         'real native 1FD one-byte CMP source deficit not retained')
    shifted=[]
    for action,nxt,n,nb,nf,bad in late:
        part=ins[cursor:cursor+n];cursor+=n
        if action in (0x252,0x254):
            low=part[0].address;hi=part[-1].address+part[-1].size
            f=[r for r in refs if low<=r['offset']<hi]
            original=list(d.disasm(rd.pe_bytes_at(pe,by[action],nb),by[action]))
            need(hi-low==(nb-1 if action==0x252 else nb+1)
                 and len(f)==6
                 and all(r['offset']-low==
                     original[next(j for j,z in enumerate(part) if z.address<=r['offset']<z.address+z.size)].address-by[action]+
                     original[next(j for j,z in enumerate(part) if z.address<=r['offset']<z.address+z.size)].size-4+
                     ((hi-low)-nb)
                     for r in f),
                 '252/254 original physically shifted PE field source phase falsely accepted')
            shifted.append(hex(action))
            continue
        checks.append(f834.physical_case(rd,pe,d,code,refs,
              part,by,action,nb,nf,bad,nxt,f820))
    need(cursor==current_case_start,
         'all prior native case interiors must physically precede new case')
    need(shifted==['0x252','0x254'] and len(checks)==46+len(late)-2,
         'native original 1FD/252/254 negatives not honestly preserved')
    return {'previous_source_case_count':46+1+len(late),
            'physically_checked_cases':len(checks),
            'original_1FD_CMP_width_negative_preserved':True,
            'original_252_254_physically_shifted':shifted,
            'original_afterRET_DATA_901B_verified':True}

def native_getter_result(M,pe,code,refs,ret):
    rd=M['rd'];old=rd.pe_bytes_at(pe,0x52cb25,46)
    r=[x for x in refs if ret-46<=x['offset']<ret]
    mask=M['f820'].physical_fields(rd,old,0x52cb25,r,ret-46,3)
    bad=[j for j in range(46) if j not in mask and old[j]!=code[ret-46+j]]
    need(bad in ([],[10,12,16,19]),'native getter new GPR phase '+str(bad))
    return {'genuine_GPR_wrong_offsets':bad,
            'matching_original_nonfield_B':34-len(bad),
            'physical_original_PE_call_fields':3}

def physical_case(M,pe,d,by,code,refs,ins,action,next_action,size,n,fields,wrong):
    rd=M['rd'];f820=M['f820']
    row=M['f834'].physical_case(rd,pe,d,code,refs,ins,by,action,
                                size,fields,wrong,next_action,f820)
    lo=ins[0].address;end=ins[-1].address+ins[-1].size
    ff=[r for r in refs if lo<=r['offset']<end]
    raw=rd.pe_bytes_at(pe,by[action],size)
    mask=f820.physical_fields(rd,raw,by[action],ff,lo,fields)
    need(len(mask)==4*fields and len(ins)==n,
         'native physical PE mask/count incorrect '+hex(action))
    offsets=[];targets=[]
    orig=list(d.disasm(raw,by[action]))
    for r in ff:
        off=r['offset']-lo
        j=next(j for j,x in enumerate(ins) if x.address<=r['offset']<x.address+x.size)
        x=orig[j]
        need(off==x.address-by[action]+x.size-4
             and r['addend']==0 and r['local_symbol_offset'] is None,
             'original PE field shifted vs original physical instruction '+hex(action))
        v=int.from_bytes(raw[off:off+4],'little',signed=r['type']=='REL32')
        target=(by[action]+off+4+v) if r['type']=='REL32' else v
        offsets.append(off);targets.append(hex(target))
    return row,offsets,targets
