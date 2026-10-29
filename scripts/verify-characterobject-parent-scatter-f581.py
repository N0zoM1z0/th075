#!/usr/bin/env python3
"""F581: full original 127/101-insn CharacterObject actions0x33E/0x33F.

Verify SHA-pinned entire original Japanese TH075 1.11 giant 004EBDA0,
its physical 60-slot jump table and 198 sparse-index DATA bytes. Fresh
compile one natural VC7.1 switch TU implementing 27 actual original
gameplay action bodies 0x320..0x33F; unimplemented rest remain markers.
For all native cases verify complete per-fighter x86/CFG/x87 roles and
true typed physical COFF call/global destinations and zero addends.
Original 0x33E has stage-six random float interpolation via real
006578C0/006581E0; original 0x33F uses distinct parent state 0x2C1.
Three previously proved independent read-read source order exceptions,
plus two real deep EBP width differences, remain explicitly nonexact.
No whole/split CODE accepted or all-unit cold replay.
"""
from __future__ import annotations

import hashlib
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys

from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
SOURCE=ROOT/'probes/CharacterObjectActionsF572.cpp'
OUT=ROOT/'.analysis/f581-characterobject-scatter-source'
MANIFEST=ROOT/'config/fighter-boss-dispatch-fingerprints.json'
ADDR=0x004EBDA0
START=0x320
END=0x33F
TYPED={
   0x0040FBB0:('REL32','ResetStateAt40FBB0'),
   0x00453E60:('REL32','SetupAt453E60'),
   0x0045B830:('REL32','ResetAt45B830'),
   0x0040FA30:('REL32','GetStateAt40FA30'),
   0x0040FB40:('REL32','SetStateAt40FB40'),
   0x00453A70:('REL32','SpawnAt453A70'),
   0x00453D40:('REL32','ModifyAt453D40'),
   0x0040FB70:('REL32','MotionRawAt40FB70'),
   0x0040FAC0:('REL32','SetActionAt40FAC0'),
   0x0065972C:('DIR32','gCurveAt0065972C'),
   0x00658044:('DIR32','gStepAt00658044'),
   0x00657CC0:('DIR32','gLiftAt00657CC0'),
   0x0065782C:('DIR32','gCompareAt0065782C'),
   0x006583F8:('DIR32','gFadeAt006583F8'),
   0x00659428:('DIR32','gFadeAt00659428'),
   0x00659738:('DIR32','gAddAt00659738'),
   0x006583FC:('DIR32','gAddAt006583FC'),
   0x00659730:('DIR32','gMulDoubleAt00659730'),
   0x00659090:('DIR32','gSubAt00659090'),
   0x00455580:('REL32','RandomAt455580'),
   0x00657CBC:('DIR32','gGrowAt00657CBC'),
   0x00657478:('DIR32','gGrowAt00657478'),
   0x00657888:('DIR32','gCollisionAt00657888'),
   0x00659728:('DIR32','gSubtractAt00659728'),
   0x006581DC:('DIR32','gOffsetAt006581DC'),
   0x00659454:('DIR32','gVelocityDragAt00659454'),
   0x0065912C:('DIR32','gMaxPositionAt0065912C'),
   0x006590AC:('DIR32','gStageOffsetAt006590AC'),
   0x006578C0:('DIR32','gScatterRateAt006578C0'),
   0x006581E0:('DIR32','gScatterBaseAt006581E0'),
   0x00659094:('DIR32','gShrinkAt00659094'),
}


def need(ok,message):
    if not ok:raise ValueError(message)


def module(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None,
         f'missing tracked original-backed source verifier {path}')
    mod=importlib.util.module_from_spec(spec)
    sys.modules[name]=mod
    spec.loader.exec_module(mod)
    return mod


def actual_typed_fields(native,candidate,relocations,action):
    first,last=candidate[0].address,candidate[-1].address+candidate[-1].size
    physical=[r for r in relocations if first<=r['offset']<last]
    observed=[]
    for ordinal,n in enumerate(native):
        if n.mnemonic=='call' and n.op_str.startswith('0x'):
            kind='REL32';address=int(n.op_str,16)
        elif n.mnemonic.startswith('f') and 'ptr [0x' in n.op_str:
            kind='DIR32';address=int(n.op_str.split('[0x',1)[1].split(']',1)[0],16)
        else:continue
        need(address in TYPED,
             f'original {action:#x} unexpected native call/global {address:#x}, instruction {ordinal}')
        expected_kind,expected_symbol=TYPED[address]
        need(kind==expected_kind,'native original float/call field type changed')
        if (action==0x32C and address==0x00453A70 and ordinal in (138,152)) or (action in (0x330,0x331,0x332) and address==0x00453A70 and ordinal==(273 if action==0x332 else 268)) or (action==0x338 and address==0x00453A70 and ordinal in (58,128)):
            expected_symbol='SpawnMovedAt453A70' if action in (0x330,0x331,0x332) else 'SpawnDirectedAt453A70'
        # Native action0x33B passes a true pair of floats to 0040FB70;
        # earlier game cases with the same physical callee pass raw C8 bits.
        if action==0x33B and address==0x0040FB70 and ordinal==38:
            expected_symbol='MotionAt40FB70'
        generated=candidate[ordinal]
        need(n.mnemonic==generated.mnemonic,
             f'physical original COFF instruction moved at {action:#x} ordinal {ordinal}')
        refs=[r for r in physical if generated.address<=r['offset']<generated.address+generated.size]
        need(len(refs)==1 and refs[0]['type']==kind
             and refs[0]['addend']==0 and expected_symbol in refs[0]['symbol'],
             f'C++ COFF real original call/global field mismatch at {action:#x} ordinal {ordinal}: {refs}')
        observed.append((ordinal,kind,address))
    expected={0x32B:9,0x32C:13,0x32D:6,0x32E:5,0x330:16,0x331:16,0x332:16,0x335:17,0x338:9,0x339:6,0x33A:6,0x33B:11,0x33C:7,0x33D:7,0x33E:10,0x33F:6}[action]
    need(len(observed)==len(physical)==expected,
         f'original {action:#x} physical source COFF field count incorrect')
    if action==0x32B:
        need([k for k,x in enumerate(native) if x.mnemonic=='fimul']==[58,77]
             and [k for k,x in enumerate(candidate) if x.mnemonic=='fimul']==[58,77],
             'native 0x32B second integer-to-float multiply/update missing')
    return observed


def native_32c_read_swap(native,candidate,f572):
    """Only permitted exception: one adjacent, independent memory READ pair.

    Native: MOV EAX,[saved_this]; FLD [EDX+0x48]
    Source: FLD [EDX+0x48]; MOV EAX,[saved_this].
    No write, branch or external relocation separates the two; neither
    reads the register written by the other. This is semantic equivalence,
    NOT physical instruction-order exactness or CODE credit.
    """
    need(len(native)==len(candidate)==176,'original x86 case32C length drift')
    a=f572.authentic_grammar(native,0x32C)
    b=f572.authentic_grammar(candidate,0x32C)
    diffs=[k for k,(x,y) in enumerate(zip(a,b)) if x!=y]
    need(diffs==[114,115],
         f'case32C previously independently bounded adjacent MOV/FLD mismatch changed: {diffs[:9]}')
    need(native[114].mnemonic=='mov'
         and native[114].op_str.startswith('eax, dword ptr [ebp - ')
         and native[115].mnemonic=='fld'
         and native[115].op_str=='dword ptr [edx + 0x48]'
         and candidate[114].mnemonic=='fld'
         and candidate[114].op_str=='dword ptr [edx + 0x48]'
         and candidate[115].mnemonic=='mov'
         and candidate[115].op_str.startswith('eax, dword ptr [ebp - '),
         'one independent actual native MOV/FLD pair is not the original')
    b[114],b[115]=b[115],b[114]
    need(a==b,'extra original x87/branch/GPR difference after independently proven read swap')
    return diffs


def validate_native_wide_frame(native,candidate,f572,action):
    """Use original F586 PE-attested integer-to-FPU EBP source slots."""
    helper=module('f586_ebp_native',ROOT/'scripts/verify-characterobject-native-frame-f586.py')
    return helper.validate_native_wide_frame(native,candidate,f572,action)


def validate_original_signed_direction_case(native,candidate,f572):
    """All 279 native ops/CFG match, except real giant EBP temp width.

    Original stage1 direction reversal adds a genuine signed byte
    MOVSX/NEG/MOV sequence and a separate saved owner reload.
    It is not present in previous 274-instruction character cases.
    """
    need(len(native)==len(candidate)==279,
         'original signed-direction case0x332 whole native instruction extent changed')
    native_code=sum(x.size for x in native)
    candidate_code=sum(x.size for x in candidate)
    need(native_code==1019 and candidate_code in (1013,1019),
         'actual original 1019-byte native case or independently valid source size drift')
    wide=[(i,x,y,x.size-y.size) for i,(x,y) in enumerate(zip(native,candidate))
          if x.size!=y.size]
    need(native[97].mnemonic==candidate[97].mnemonic=='mov' and
         native[98].mnemonic==candidate[98].mnemonic=='fild' and
         '[ebp - 0x9c]' in native[97].op_str and
         '[ebp - 0x9c]' in native[98].op_str,
         'original native signed-direction FILD temporary at EBP-0x9C changed')
    if candidate_code==1013:
        need([x[0] for x in wide]==[97,98] and
             all(x[3]==3 for x in wide) and
             '[ebp - 0x80]' in candidate[97].op_str and
             '[ebp - 0x80]' in candidate[98].op_str,
             'earlier compact F577 source must have exactly two authentic widened EBP operations')
    else:
        need(not wide and
             any(all(f'[ebp - 0x{slot:x}]' in candidate[k].op_str
                     for k in (97,98)) for slot in (0x84,0x8c,0x90,0x9c)),
             'true original game C++ source context requires EBP-0x84 or EBP-0x8C genuine disp32 temp')
    need(native[189].mnemonic==candidate[189].mnemonic=='movsx'
         and native[189].op_str.endswith('byte ptr [edx + 0x66]')
         and candidate[189].op_str==native[189].op_str
         and native[190].mnemonic==candidate[190].mnemonic=='neg'
         and native[190].op_str==candidate[190].op_str=='eax'
         and native[192].mnemonic==candidate[192].mnemonic=='mov'
         and native[192].op_str==candidate[192].op_str=='byte ptr [ecx + 0x66], al',
         'native stage1 signed facing reversal has wrong MOVSX/NEG/write x86 source')
    na=[(n,o) for n,size,o in f572.authentic_grammar(native,0x332)]
    nb=[(n,o) for n,size,o in f572.authentic_grammar(candidate,0x332)]
    need(na==nb,
         f'original 279-insn signed-direction GPR/x87/branch/operand grammar changed: '
         f'{[(i,x,y) for i,(x,y) in enumerate(zip(na,nb)) if x!=y][:6]}')
    return len(wide),native_code-candidate_code


def validate_original_contact335(native,candidate,f572):
    """The only machine-order difference is adjacent independent MOV/FLD.

    Original ord146 MOV EDX,[saved_this] and ord147 FLD [ECX+0x48].
    Ordinary C++ reverses them. Both perform memory reads, MOV writes
    only EDX and FLD uses ECX and x87; no branch, shared register
    dependency, memory modification or COFF field lies between them.
    It does not make original machine CODE byte-exact.
    """
    need(len(native)==len(candidate)==269 and
         sum(x.size for x in native)==sum(x.size for x in candidate)==1022,
         'not the original 269-insn 1022-byte full case0x335')
    a=f572.authentic_grammar(native,0x335)
    b=f572.authentic_grammar(candidate,0x335)
    diff=[i for i,(x,y) in enumerate(zip(a,b)) if x!=y]
    need(diff==[146,147],
         f'unrecognized true original 0x335 x87, GPR or branch mismatch: {diff[:10]}')
    need(native[146].mnemonic=='mov'
         and native[146].op_str.startswith('edx, dword ptr [ebp - ')
         and native[147].mnemonic=='fld'
         and native[147].op_str=='dword ptr [ecx + 0x48]'
         and candidate[146].mnemonic=='fld'
         and candidate[146].op_str=='dword ptr [ecx + 0x48]'
         and candidate[147].mnemonic=='mov'
         and candidate[147].op_str.startswith('edx, dword ptr [ebp - '),
         'native original 0x335 one read-read commutation is not the verified independent pair')
    b[146],b[147]=b[147],b[146]
    need(a==b,'native 0x335 GPR/x87/branch graph differs outside verified swap')
    need(native[238].mnemonic==candidate[238].mnemonic=='fld'
         and native[238].op_str=='dword ptr [0x65782c]'
         and candidate[238].op_str=='dword ptr [0]'
         and native[239].mnemonic==candidate[239].mnemonic=='fadd'
         and native[239].op_str==candidate[239].op_str=='dword ptr [eax + 0xcc]',
         'actual original x87 global-first operand computation/order is wrong')
    need(native[149].op_str=='dword ptr [0x657888]'
         and native[149].mnemonic==candidate[149].mnemonic=='fcomp',
         'actual native float contact threshold is not original global 00657888')
    return diff


def validate_original_fade_spawn(native,candidate,f572,action):
    """Strict original native machine codegen for stage fade/spawn cases.

    Action0x338 has two different original parent effects IDs 0x33A,
    0x339 at actual call sites. Action0x339 uses source-native scale
    1.3f and U8 byte opacity decrement 40 (not copied 0x338's 20).
    No special expression normalization or swap is allowed here.
    """
    expected=(130,478) if action==0x338 else (80,309)
    need(len(native)==len(candidate)==expected[0] and
         sum(x.size for x in native)==sum(x.size for x in candidate)==expected[1],
         f'original genuine native game-action {action:#x} full byte/insn extent differs')
    a=f572.authentic_grammar(native,action)
    b=f572.authentic_grammar(candidate,action)
    need(a==b,
         f'original complete fade/source {action:#x} register/x87/branch difference: '
         f'{[(i,x,y) for i,(x,y) in enumerate(zip(a,b)) if x!=y][:5]}')
    need(native[24].mnemonic==candidate[24].mnemonic=='mov'
         and ('0x3f800000' if action==0x338 else '0x3fa66666')
             in native[24].op_str
         and native[24].op_str.rsplit(', ',1)[-1]==candidate[24].op_str.rsplit(', ',1)[-1],
         'native actor scale initializers are not independently source-backed')
    if action==0x338:
        need(native[55].mnemonic==candidate[55].mnemonic=='push'
             and native[55].op_str==candidate[55].op_str=='0x33a'
             and native[125].mnemonic==candidate[125].mnemonic=='push'
             and native[125].op_str==candidate[125].op_str=='0x339'
             and native[58].mnemonic==candidate[58].mnemonic=='call'
             and native[128].mnemonic==candidate[128].mnemonic=='call',
             'original 0x338 real two effect-spawn identities changed')
    else:
        need(native[57].mnemonic==candidate[57].mnemonic=='cmp'
             and native[57].op_str==candidate[57].op_str=='eax, 0x28',
             'original 0x339 fade threshold not native 40')
    return True


def validate_original_four_cases(native,candidate,f572,action):
    """Physical full game state, not a cropped prefix or a mnemonic bag."""
    geometry={0x33A:(66,229),0x33B:(84,301),
              0x33C:(127,472),0x33D:(127,472)}
    count,size=geometry[action]
    need(len(native)==len(candidate)==count and
         sum(x.size for x in native)==sum(x.size for x in candidate)==size,
         f'original {action:#x} complete physical native CODE/insn extent differs')
    before=f572.authentic_grammar(native,action)
    after=f572.authentic_grammar(candidate,action)
    need(before==after,
         f'original {action:#x} real GPR/x87/CFG grammar differs: '
         f'{[(i,x,y) for i,(x,y) in enumerate(zip(before,after)) if x!=y][:8]}')
    if action==0x33A:
        need(native[25].mnemonic==candidate[25].mnemonic=='mov'
             and native[25].op_str.endswith('dword ptr [eax + 0x1a]') is False
             and native[26].op_str.endswith('0x4e2')
             and native[28].op_str.endswith('0xc2960000')
             and native[45].op_str=='eax, 0x14',
             'original 0x33A stage sprite 0x4E2, -75f motion and 20 fade differ')
    elif action==0x33B:
        need([(native[k].mnemonic,native[k].op_str,
               candidate[k].mnemonic,candidate[k].op_str) for k in (67,69,70)]==[
               ('fcomp','dword ptr [0x65912c]','fcomp','dword ptr [0]'),
               ('test','ah, 5','test','ah, 5'),
               ('jp',native[70].op_str,'jp',candidate[70].op_str)],
             '0x33B true x87 FCOMP TEST AH,5 and JP branch not restored')
        need(native[25].op_str=='0x41900000'
             and native[26].op_str=='0x2d'
             and native[32].op_str=='dword ptr [0x659728]'
             and native[33].op_str=='dword ptr [0x6581dc]',
             '0x33B native random motion float order/values differ')
    else:
        first=0x2BE if action==0x33C else 0x2C1
        third=0x2BE
        need(native[3].mnemonic==candidate[3].mnemonic=='cmp'
             and native[24].mnemonic==candidate[24].mnemonic=='cmp'
             and native[34].mnemonic==candidate[34].mnemonic=='cmp'
             and all(int(x.op_str.rsplit(', ',1)[-1],0)==ref
                     for x,ref in [(native[3],first),(native[24],first),
                                   (native[34],third),(candidate[3],first),
                                   (candidate[24],first),(candidate[34],third)]),
             'original 0x33D third compare is 0x2BE even though first two are 0x2C1')
        need(native[9].mnemonic==candidate[9].mnemonic=='imul'
             and native[9].op_str.endswith(', 0x41')
             and candidate[9].op_str==native[9].op_str
             and native[11].mnemonic==candidate[11].mnemonic=='fild',
             'native parent x-direction multiply by 65 and integer x87 conversion absent')
    return True


def validate_original_parent_scatter(native,candidate,f572,action):
    """Two complete original nondefault 0x33E/0x33F gameplay bodies."""
    need(action in (0x33E,0x33F),'unknown original native parent scatter action')
    count,size=((127,489) if action==0x33E else (101,381))
    need(len(native)==len(candidate)==count and
         sum(x.size for x in native)==sum(x.size for x in candidate)==size,
         f'original case {action:#x} whole physical size/instruction geometry wrong')
    before=f572.authentic_grammar(native,action)
    after=f572.authentic_grammar(candidate,action)
    need(before==after,
         f'original {action:#x} GPR/x87/branch/operand source mismatch: '
         f'{[(i,x,y) for i,(x,y) in enumerate(zip(before,after)) if x!=y][:6]}')
    parent=(0x2BE if action==0x33E else 0x2C1)
    multiplier=(0x8C if action==0x33E else 0xB4)
    frame_limit=(7 if action==0x33E else 17)
    for ins in (native,candidate):
        need(ins[3].mnemonic=='cmp' and
             int(ins[3].op_str.rsplit(', ',1)[-1],0)==parent
             and ins[9].mnemonic=='imul' and
             int(ins[9].op_str.rsplit(', ',1)[-1],0)==multiplier
             and ins[24].mnemonic=='cmp' and
             int(ins[24].op_str.rsplit(', ',1)[-1],0)==parent
             and ins[28].mnemonic=='cmp' and
             int(ins[28].op_str.rsplit(', ',1)[-1],0)==frame_limit
             and ins[30].mnemonic=='push' and
             int(ins[30].op_str,0)==frame_limit,
             f'original action {action:#x} physical parent/motion/callback differs')
    if action==0x33E:
        need(native[56].op_str.endswith('0x3fc00000') and
             native[78].mnemonic==candidate[78].mnemonic=='call'
             and native[82].op_str=='dword ptr [0x6578c0]'
             and native[83].op_str=='dword ptr [0x6581e0]'
             and native[92].op_str=='dword ptr [0x659094]'
             and native[118].mnemonic==candidate[118].mnemonic=='call',
             'native stage-six original x87 random scatter source/global order differs')
    else:
        need(native[50].op_str.endswith('0x40000000')
             and native[52].op_str.endswith('0x3fc00000')
             and native[64].op_str.endswith('0x19')
             and native[92].op_str=='6',
             'native 0x33F true 2.0/1.5f, 25-frame and callback argument differs')
    return True


def build_one():
    OUT.mkdir(parents=True,exist_ok=True)
    src=SOURCE.read_text()
    need('F572/F573/F574/F575/F576/F577/F578/F579/F580/F581' in src and
         all(src.count(f'case 0x{k:X}:')==1 for k in range(START,END+1) if k not in (0x32F,0x333,0x334,0x336,0x337))
         and 'case 0x3E3: g_FighterProbeMarker = 996; break;' in src,
         'actual F581 source must implement 27 real game actions and keep next 0x340 diagnostic')
    need(src.count('gCurveAt0065972C')>=3 and src.count('MotionRawAt40FB70')>=2,
         'real source must include native polynomial and raw-float input')
    obj=OUT/'CharacterObjectF581.obj'
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv=d;winemenubuilder.exe=d'
    proc=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(SOURCE),str(obj),
         '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src'],
         cwd=ROOT,env=env,capture_output=True,text=True,timeout=120)
    (OUT/'compiler.log').write_text(proc.stdout+proc.stderr)
    need(proc.returncode==0,f'fresh selected native profile VC7.1 compile failed: {proc.stderr}')
    return obj


def main():
    reader=module('f581_reader',ROOT/'scripts/compare-coff-function.py')
    actions=module('f581_actions',ROOT/'scripts/report-fighter-action-handlers.py')
    switch=module('f581_switch',ROOT/'scripts/verify-fighter-natural-switch-probes.py')
    f572=module('f581_firstten',ROOT/'scripts/verify-characterobject-action-family-f572.py')
    f573=module('f581_previous',ROOT/'scripts/verify-characterobject-extended-action-f573.py')
    pe=reader.verified_target();decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    boss=next(x for x in json.loads(MANIFEST.read_text())['bosses'] if x['address']==ADDR)
    need(boss['size']==33293 and boss['postret_size']==438,
         'original complete giant function CODE or post-RET DATA drift')
    report,mapped=actions.report_boss(reader,pe,decoder,boss)
    allcases={r['action']:int(r['handler'],16) for r in mapped}
    tab=boss['tables'][0]
    need(tab['slots']==60 and tab['map_length']==198 and tab['map_addr'] is not None,
         'original native one-switch compressed table geometry changed')
    original_dense=reader.pe_bytes_at(pe,tab['dense_addr'],4*tab['slots'])
    original_map=reader.pe_bytes_at(pe,tab['map_addr'],tab['map_length'])
    need(hashlib.sha256(original_dense).hexdigest()==tab['dense_sha'] and
         hashlib.sha256(original_map).hexdigest()==tab['map_sha'],
         'actual original PE switch SHA controls do not match')
    obj=build_one()
    code,refs=reader.object_function(obj,'?Advance@FighterSwitchF572_Boss004EBDA0@@QAEXXZ')
    allins=[]
    for x in decoder.disasm(code,0):
        allins.append(x)
        if x.mnemonic=='ret':break
    need(allins and allins[-1].mnemonic=='ret','candidate whole fighter switch no normal RET')
    ret=allins[-1].address+allins[-1].size
    need(len(code)-ret==boss['postret_size'],
         'original candidate full after-RET jump DATA size differs')
    physical=sorted((r for r in refs if ret<=r['offset']<ret+4*tab['slots']),
                    key=lambda r:r['offset'])
    need(len(physical)==tab['slots'] and all(r['type']=='DIR32'
         and r['addend']==0 and r['offset']==ret+4*k
         and r['local_symbol_offset'] is not None for k,r in enumerate(physical)),
         'one-switch physical original direct handler COFF fields incorrect')
    nslots=[int.from_bytes(original_dense[4*k:4*k+4],'little')
            for k in range(tab['slots'])]
    cslots=[r['local_symbol_offset'] for r in physical]
    need(switch.canonical_partitions(nslots)==switch.canonical_partitions(cslots),
         'actual default/repeated switch handler partitions mismatch')
    need(code[ret+4*tab['slots']:]==original_map,'original literal sparse index bytes differ')
    ja=[int(x.op_str,16) for x in allins if x.mnemonic=='ja' and x.op_str.startswith('0x')]
    need(ja and [x==int(report['default'],16) for x in nslots]==[x==ja[0] for x in cslots],
         'native shared default physical jump slots differ')
    rows=[];total_coff=0;native_frame_extra=0
    cases=[k for k in range(START,END+1) if k not in (0x32F,0x333,0x334,0x336,0x337)]
    need(len(cases)==27 and cases[-6:]==[0x33A,0x33B,0x33C,0x33D,0x33E,0x33F],
         'original 0x32F default handler must never be counted as action body')
    for action in cases:
        first=allcases[action];last=allcases[0x330 if action==0x32E else 0x335 if action==0x332 else 0x338 if action==0x335 else action+1]
        need(boss['address']<=first<last<boss['address']+boss['size'],
             'actual original game case outside giant source range')
        orig=list(decoder.disasm(reader.pe_bytes_at(pe,first,last-first),first))
        cfirst=cslots[original_map[action-START]]
        clast=cslots[original_map[(0x330 if action==0x32E else 0x335 if action==0x332 else 0x338 if action==0x335 else action+1)-START]]
        need(0<=cfirst<clast<ret,'candidate complete case source outside normal CODE')
        cand=list(decoder.disasm(code[cfirst:clast],cfirst))
        need(orig and orig[0].address==first and orig[-1].address+orig[-1].size==last
             and cand and cand[0].address==cfirst and cand[-1].address+cand[-1].size==clast,
             f'actual whole native actor case {action:#x} is truncated/discontinuous')
        need(len(orig)==len(cand) and (
             (last-first==clast-cfirst and all(x.size==y.size for x,y in zip(orig,cand)))
             if action<0x330 or action>=0x338 else (last-first==clast-cfirst if action in (0x332,0x335) else last-first-clast+cfirst in (0,6,18) if action==0x331 else last-first-clast+cfirst in (0,18))),
             f'whole native actor {action:#x} instruction/codebyte grammar differs')
        if action<=0x329:
            fields=f572.compare_actual_case(orig,cand,refs,action)
            changes=[]
        elif action==0x32A:
            fields=f573.actual_case32a_fields(orig,cand,refs)
            changes=f573.equivalent_independent_reads(orig,cand,f572)
        else:
            fields=actual_typed_fields(orig,cand,refs,action)
            if action in (0x32B,0x32D,0x32E):
                a=f572.authentic_grammar(orig,action)
                b=f572.authentic_grammar(cand,action)
                need(a==b,'full native stage/curve action32B has incorrect original register/x87/CFG roles')
                changes=[]
            elif action==0x32C:
                changes=native_32c_read_swap(orig,cand,f572)
            elif action in (0x330,0x331):
                widened,excess=validate_native_wide_frame(orig,cand,f572,action)
                need((widened,excess) in ((6,18),(0,0)) if action==0x330 else
                     (widened,excess) in ((6,18),(2,6),(0,0)),
                     'original real EBP source widths must be six or two PE-grounded temp operations')
                native_frame_extra+=excess
                changes=[]
            elif action==0x332:
                widened,excess=validate_original_signed_direction_case(orig,cand,f572)
                need((widened,excess)==(0,0),
                     'F578 richer natural switch must move signed-direction source into genuine disp32 width')
                native_frame_extra+=excess
                changes=[]
            elif action==0x335:
                changes=validate_original_contact335(orig,cand,f572)
                need(len(changes)==2,'not precisely the original 0x335 source read-read swap')
            elif action in (0x338,0x339):
                need(validate_original_fade_spawn(orig,cand,f572,action),
                     'native original later state fade/spawn x86 source changed')
                changes=[]
            elif action in (0x33A,0x33B,0x33C,0x33D):
                need(validate_original_four_cases(orig,cand,f572,action),
                     'older four original native source C++ case grammar not strictly reproduced')
                changes=[]
            else:
                need(action in (0x33E,0x33F) and
                     validate_original_parent_scatter(orig,cand,f572,action),
                     'new full native parent/scatter source case differs')
                changes=[]
        total_coff+=len(fields)
        rows.append({'action':f'0x{action:X}', 'native_x86_instructions':len(orig),
                     'native_original_CODE_bytes':last-first,
                     'genuine_physical_COFF_fields':len(fields),
                     'explicit_nonidentical_read_only_swap_indices':changes,
                     'native_deep_frame_extra_bytes':excess if action in (0x330,0x331) else 0})
        print(f'{action:#05x}: whole original {len(orig)} x86 instructions / '
              f'{last-first} CODE bytes, {len(fields)} genuine COFF fields, '
              f'independent read-only source-order exceptions {changes}',flush=True)
    need(len(rows)==27 and sum(x['native_x86_instructions'] for x in rows)==3444
         and sum(x['native_original_CODE_bytes'] for x in rows)==12765
         and total_coff==240 and native_frame_extra in (0,18,24,36)
         and [r['native_x86_instructions'] for r in rows[-6:]]==[66,84,127,127,127,101]
         and [r['native_original_CODE_bytes'] for r in rows[-6:]]==[229,301,472,472,489,381],
         'original case family 27 physically complete nondefault native actions/fields differs')
    OUT.mkdir(parents=True,exist_ok=True)
    summary={'original_giant':f'0x{ADDR:08X}','whole_original_CODE_unaccepted':boss['size'],
             'native_complete_real_action_count':len(rows),
             'case_details':rows,
             'original_native_x86_insns':3444,
             'original_inner_CODE_bytes':12765,
             'integrated_action332_now_disp32_same_size':native_frame_extra in (0,18,24,36),
             'genuine_typed_COFF_fields':240,
             'new_native_scatter_cases':[0x33E,0x33F],
             'new_four_cases_strict_native_grammar':[0x33A,0x33B,0x33C,0x33D],
             'new_fade_spawn_cases_strict_native_grammar':[0x338,0x339],
             'source_action332_native_disp32_now_identical_width':True,
             'action335_independent_readonly_swaps':[146,147],
             'genuine_original_deep_frame_extra_bytes':native_frame_extra,
             'original_dense_DWORD_COFF_slots':len(physical),
             'byte_identical_sparse_index_bytes':len(original_map),
             'complete_native_afterret_DATA_shape':len(code)-ret}
    (OUT/'summary.json').write_text(json.dumps(summary,indent=2)+'\n')
    print(f'F581 original 0x{ADDR:08X}: 27 complete action bodies, '
          f'3444 native x86 source roles, 12765 whole original inner CODE bytes, '
          f'{total_coff}/240 genuine typed COFF records, 60 native-style jump '
          f'DWORD fields, 198 byte-identical original sparse bytes; '
          f'three bounded read-only swaps; actual native-minus-source deep-frame width +{native_frame_extra} bytes across 0x330/0x331; case0x332 native disp32, '
          f'whole 33293-byte giant still NONEXACT')
    print('Only one affected VC7.1 C++ TU freshly compiled; no full cold '
          'replay or accepted whole/partial CODE/DATA exactness credit')


if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('TH075 original CharacterObject source0x33E/33F action verification failed:',exc,file=sys.stderr)
        raise SystemExit(1)
