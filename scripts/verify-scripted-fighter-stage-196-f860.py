#!/usr/bin/env python3
"""F860: genuine actor196 199B/60-x86/7 physical PE fields in whole fighter.

Actual stage3 source prepares action3, spawns float sprite353
with facing*100 FILD and real Y lvalue/global006581DC, then
starts animationC8. Compare complete native PE against freshly
compiled ONE VC7.1 whole parent, preserving 31 genuine GPR and
two parent epilogue JMP byte negatives. Recheck all 31 earlier
whole source-backed native cases and five real 901B switch tables.
Never mass replay prior 979 exact units; no case-only CODE credit.
"""
from pathlib import Path
import importlib.util,json,os,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f860-scripted-stage196'
SYM='?Advance@FighterSwitchF598_Boss005214B0@@QAEXXZ'
ADDR=0x005214B0
BAD=[1,5,8,12,16,19,23,27,35,38,62,64,68,71,85,89,92,97,101,104,120,123,125,127,130,143,147,150,153,159,162,195,196]
FIELDS={
 13:(0x453e20,'ResetAt453E20'),
 15:(0x40fa30,'GetNativeActionAt40FA30'),
 23:(0x40fac0,'SetNativeActionAt40FAC0'),
 34:(0x453d40,'PrepareActionAt453D40'),
 41:(0x6581dc,'g_F860ShotYAt006581DC'),
 55:(0x453a70,'SpawnFloatXYAt453A70'),
 58:(0x46d000,'StartAnimationAt46D000')
}

def need(ok,msg):
    if not ok:raise ValueError(msg)

def ld(tag,filename):
    sp=importlib.util.spec_from_file_location(tag,R/'scripts'/filename)
    need(sp is not None and sp.loader is not None,'native PE helper missing '+filename)
    m=importlib.util.module_from_spec(sp);sys.modules[tag]=m;sp.loader.exec_module(m)
    return m

def generate_source(reader,pe,d,by):
    O.mkdir(parents=True,exist_ok=True)
    src_path=R/'.analysis/f859-scripted-ground-194/Boss005214B0-F859-whole.cpp'
    receipt=R/'.analysis/f859-scripted-ground-194/verified-summary.json'
    if not src_path.is_file() or not receipt.is_file():
        old=subprocess.run([str(R/'scripts/repo-python'),
           str(R/'scripts/verify-scripted-fighter-ground-194-f859.py')],
           cwd=R,capture_output=True,text=True,timeout=1300)
        (O/'f859-fallback-proof.log').write_text(old.stdout+old.stderr)
        need(old.returncode==0,'prior current 194 native PE proof failed '+(old.stdout+old.stderr)[-700:])
    prior=json.loads(receipt.read_text())
    need(prior['new_current_whole_source_callable_CODE_B']==25972
         and prior['whole_original_game_exact'] is False,
         'prior 194 real whole PE proof receipt changed')
    original=list(d.disasm(reader.pe_bytes_at(pe,by[0x196],by[0x198]-by[0x196]),by[0x196]))
    need(len(original)==60 and by[0x198]-by[0x196]==199
         and original[26].mnemonic=='cmp' and original[26].op_str.endswith(', 3')
         and original[32].mnemonic=='push' and original[32].op_str=='3'
         and original[34].op_str=='0x453d40'
         and original[41].mnemonic=='fadd' and original[41].op_str=='dword ptr [0x6581dc]'
         and original[46].mnemonic=='imul' and original[46].op_str.endswith(', 0x64')
         and original[53].mnemonic=='push' and original[53].op_str=='0x353'
         and original[55].op_str=='0x453a70'
         and original[56].op_str=='0xc8' and original[58].op_str=='0x46d000'
         and original[59].op_str=='0x52cb4f',
         'real actor196 native stage/float/call order changed')
    src=src_path.read_text()
    marker='        case 0x196: g_FighterProbeMarker = 407; break;'
    inc=(R/'probes/FighterScriptedStage196F860.inc').read_text()
    need(src.count(marker)==1 and inc.count('case 0x196:')==1
         and inc.count('return;')==1
         and inc.index('PrepareActionAt453D40(3)')<inc.index('SpawnFloatXYAt453A70(0x353')<inc.index('StartAnimationAt46D000(0xC8)')
         and '(*(&POS48))+g_F860ShotYAt006581DC' in inc,
         'game native 196 normal C++ source AST order changed')
    return 'extern float g_F860ShotYAt006581DC;\n'+src.replace(marker,'#include "FighterScriptedStage196F860.inc"',1)

def compile_one(src):
    cpp=O/'Boss005214B0-F860-whole.cpp'
    obj=O/'Boss005214B0-F860-whole.obj'
    cpp.write_text(src)
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(R/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    p=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
       '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
       cwd=R,env=env,text=True,capture_output=True,timeout=290)
    (O/'compiler.log').write_text(p.stdout+p.stderr)
    need(p.returncode==0,'current 196 full VC7.1 source failed '+(p.stdout+p.stderr)[-700:])
    return obj

def main():
    rd=ld('f860rd','compare-coff-function.py')
    ac=ld('f860ac','report-fighter-action-handlers.py')
    f834=ld('f860f834','verify-scripted-fighter-fourway-c8-f834.py')
    f820=ld('f860f820','verify-scripted-fighter-landing-trio-f820.py')
    f847=ld('f860f847','verify-scripted-fighter-projectile-134135-f847.py')
    f849=ld('f860f849','verify-scripted-fighter-physics-136-f849.py')
    f850=ld('f860f850','verify-scripted-fighter-ground-186187-f850.py')
    f851=ld('f860f851','verify-scripted-fighter-ground-188-f851.py')
    f852=ld('f860f852','verify-scripted-fighter-bounce-189-f852.py')
    f853=ld('f860f853','verify-scripted-fighter-floatshot-18a-f853.py')
    f855=ld('f860f855','verify-scripted-fighter-volley-18b-f855.py')
    f856=ld('f860f856','verify-scripted-fighter-stage-190-f856.py')
    f857=ld('f860f857','verify-scripted-fighter-floatshot-191-f857.py')
    f859=ld('f860f859','verify-scripted-fighter-ground-194-f859.py')
    zero=ld('f860zero','verify-fighter-actionzero-natural-source.py')
    sw=ld('f860sw','verify-fighter-natural-switch-probes.py')
    pe=rd.verified_target();d=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(b for b in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses']
              if b['address']==ADDR)
    need((boss['size'],boss['postret_size'],boss['instructions'])==(46755,901,13230),
         'pinned original 46KB whole fighter/afterRET geometry changed')
    report,mp=ac.report_boss(rd,pe,d,boss)
    by={x['action']:int(x['handler'],16) for x in mp}
    obj=compile_one(generate_source(rd,pe,d,by))
    code,refs=rd.object_function(obj,SYM)
    ins=[]
    for x in d.disasm(code,0):
        ins.append(x)
        if x.mnemonic=='ret':break
    ret=ins[-1].address+ins[-1].size
    need((ret,len(ins),len(refs),len(code)-ret)==(26156,7242,971,901)
         and ins[3].op_str=='dword ptr [ebp - 0x10], ecx',
         'selected actor196 entire normal C++ PE/ABI changed')
    dense,sparse,maps=zero.verify_physical_tables(boss,report,pe,rd,sw,ins,code,refs,ret)
    need(dense>0 and sparse>0 and maps>0,'all five separate 901B original jump tables not checked')
    marker=[j for j,x in enumerate(ins) if x.mnemonic=='mov'
        and x.op_str.endswith(', 0x199')
        and any('g_FighterProbeMarker' in r['symbol']
                and x.address<=r['offset']<x.address+x.size for r in refs)]
    need(len(marker)==1,'next original198 source marker missing')
    k=marker[0]
    src=ins[k-60:k]
    case=f834.physical_case(rd,pe,d,code,refs,src,by,0x196,199,7,BAD,0x198,f820)
    need(case['native_complete_x86']==60
         and case['original_native_enclosing_parent_JMP_exit_ordinals']==[59]
         and src[59].op_str==hex(ret-4)
         and src[32].op_str=='3' and src[53].op_str=='0x353'
         and src[56].op_str=='0xc8'
         and src[40].mnemonic=='fld' and src[40].size==3
         and src[41].mnemonic=='fadd' and src[41].size==6,
         'actor original196 stage3/float Y native instruction order or epilogue wrong')
    orig=list(d.disasm(rd.pe_bytes_at(pe,by[0x196],199),by[0x196]))
    for ordinal,(target,symbol) in FIELDS.items():
        a,b=orig[ordinal],src[ordinal]
        f=[r for r in refs if b.address<=r['offset']<b.address+b.size]
        need(len(f)==1 and f[0]['addend']==0 and f[0]['local_symbol_offset'] is None
             and f[0]['type']==('REL32' if a.mnemonic=='call' else 'DIR32')
             and symbol in f[0]['symbol']
             and f[0]['offset']-src[0].address==a.address-by[0x196]+a.size-4
             and a.op_str==(f'0x{target:x}' if a.mnemonic=='call' else f'dword ptr [0x{target:x}]'),
             'native 196 field target/source physically wrong '+str(ordinal))
    late=[
      (0x136,321,95,10,f849.ORIGINAL_BAD,0x186),
      (0x186,250,74,7,f850.BAD186,0x187),
      (0x187,214,61,6,f850.BAD187,0x188),
      (0x188,214,61,6,f851.WRONG188,0x189),
      (0x189,381,107,11,f852.BAD189,0x18a),
      (0x18a,250,71,6,f853.BAD,0x18b),
      (0x18b,353,99,7,f855.WRONG,0x190),
      (0x190,217,64,6,f856.BAD,0x191),
      (0x191,166,53,5,f857.BAD,0x192),
      (0x192,217,64,6,f856.BAD,0x194),
      (0x194,297,86,7,f859.WRONG,0x196)]
    prev=ins[k-60-sum(x[2] for x in late):k-60]
    cursor=0;previous=[]
    for a,nb,nx,nf,bad,nxt in late:
        sec=prev[cursor:cursor+nx];cursor+=nx
        previous.append(f834.physical_case(rd,pe,d,code,refs,sec,by,a,nb,nf,bad,nxt,f820))
    need(cursor==len(prev),'eleven recent actual native case interiors truncated')
    early=f847.STATES+[(0x134,278,82,7,[274,275],0x135),(0x135,278,82,7,[274,275],0x136)]
    left=k-60-sum(x[2] for x in late)
    older=ins[left-sum(x[2] for x in early):left]
    cursor=0;past=[]
    for a,nb,nx,nf,bad,nxt in early:
        sec=older[cursor:cursor+nx];cursor+=nx
        past.append(f834.physical_case(rd,pe,d,code,refs,sec,by,a,nb,nf,bad,nxt,f820))
    need(cursor==len(older),'20 earlier PE-backed game case sources truncated')
    tail=rd.pe_bytes_at(pe,0x52cb25,46)
    mask=f820.physical_fields(rd,tail,0x52cb25,
          [r for r in refs if ret-46<=r['offset']<ret],ret-46,3)
    wrong_tail=[j for j in range(46) if j not in mask and tail[j]!=code[ret-46+j]]
    need(wrong_tail==[10,12,16,19],'46B shared getter genuine GPR byte negatives changed')
    receipt={'original_whole_fighter':'0x005214B0',
        'original_native_entire_callable_CODE_B':46755,
        'generated_current_whole_source_CODE_B':ret,
        'new_196_complete_native_original_case':case,
        'physical_original_196_field_ordinals':list(FIELDS),
        'true_196_nonparentJMP_GPR_wrong_B':31,
        'native_original_196_giant_epilogue_JMP_wrong_offsets':[195,196],
        'preceding_eleven_GPR_affected_native_case_sources':previous,
        'earlier_twenty_original_PE_sources_rechecked':past,
        'real_46B_default_GPR_wrong_offsets':wrong_tail,
        'original_five_901B_packed_afterRET_tables_checked':True,
        'native_separate_afterRET_DATA_B':901,
        'original_whole_giant_exact':False,
        'new_accepted_whole_callable_CODE_B':0,
        'mass_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(receipt,indent=2)+'\n')
    assert json.loads((O/'verified-summary.json').read_text())['original_whole_giant_exact'] is False
    print('F860 native actor196 199B/60x86/7 physical original PE fields in 26156B/7242-x86 full fighter; prepare3 -> float sprite353 -> animationC8 original order and all widths correct. 31 honest GPR plus 2 original whole-giant JMP bytes still differ; previous 31 PE cases, 46B getter and all five original packed 901B switch tables rechecked. Entire giant NONEXACT.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F860 current original actor196 FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
