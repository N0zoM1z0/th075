#!/usr/bin/env python3
"""F586 native-only proof of original giant 0x330/0x331 EBP temp widths.

NOT a standalone game function, source match or exactness receipt. The
original whole Japanese TH075 1.11 CharacterObject function still lacks
its other cases. These two 274-instruction internal bodies spill three
actual int-to-x87 temporaries each; incomplete normal C++ source has
historically produced six narrow load/store instructions per case.
Adding the genuinely authored C++ game bodies 0x34A/0x34B shifts
source 0x331's final two integer-to-x87 temporaries past the disp8
boundary, leaving ONLY original ordinals 97/98 3-byte wider; adding
genuine action0x34C naturally shifts the first too, removing this
gap altogether. Only three PE-tested source modes are accepted.
No fabricated frame, machine byte patch, all-unit replay or CODE credit.
"""
from __future__ import annotations


def need(ok,msg):
    if not ok:raise ValueError(msg)


def validate_native_wide_frame(native,candidate,f572,action):
    need(action in (0x330,0x331) and len(native)==len(candidate)==274,
         'not real 274-instruction original CharacterObject game action')
    positions=(0x84,0x88,0x8C) if action==0x330 else (0x90,0x94,0x98)
    originals=(97,98,244,245,259,260)
    for idx,slot in zip(originals,(positions[0],positions[0],positions[1],
                                   positions[1],positions[2],positions[2])):
        x,y=native[idx],candidate[idx]
        need(x.mnemonic==y.mnemonic==('mov' if idx in (97,244,259) else 'fild')
             and f'[ebp - 0x{slot:x}]' in x.op_str
             and x.size==6,
             f'native original {action:#x} real temp ordinal {idx} and EBP offset differ')
        need(y.mnemonic==x.mnemonic and '[ebp - 0x' in y.op_str,
             f'C++ source {action:#x} integer FILD temp ordinal changed: {idx}')
    diffs=[(i,x,y,x.size-y.size) for i,(x,y) in enumerate(zip(native,candidate))
           if x.size!=y.size]
    indices=[i for i,*_ in diffs]
    if action==0x330:
        need(indices==list(originals),
             'original 0x330 six actual native width expansions changed')
    else:
        need(indices in (list(originals),[97,98],[]),
             f'original 0x331 width differences are not one of three PE-tested VC7.1 contexts: {indices}')
        if indices==[97,98]:
            # C++ with real action0x34A/34B uses -0x80/-0x84/-0x88.
            need(all(f'[ebp - 0x{slot:x}]' in candidate[i].op_str
                     for i,slot in zip(originals,(0x80,0x80,0x84,0x84,0x88,0x88)))
                 and all(candidate[i].size==(3 if i in (97,98) else 6)
                         for i in originals),
                 'original-specific 0x331 compact-plus-wide EBP slot ownership changed')
        if not indices:
            # Adding *real* native action0x34C makes all three C++
            # temporary locations disp32 naturally, WITHOUT fake locals.
            need(all(f'[ebp - 0x{slot:x}]' in candidate[i].op_str
                     for i,slot in zip(originals,(0x84,0x84,0x88,0x88,0x8c,0x8c)))
                 and all(candidate[i].size==6 for i in originals),
                 'original 0x331 397-insn genuine C++ case context must have -0x84/-0x88/-0x8C source slots')
    need(all(delta==3 for _,_,_,delta in diffs),
         'additional non-stack native instruction size differences are not accepted')
    real=[(mnemonic,operand) for mnemonic,size,operand
          in f572.authentic_grammar(native,action)]
    source=[(mnemonic,operand) for mnemonic,size,operand
            in f572.authentic_grammar(candidate,action)]
    need(real==source,
         f'original {action:#x} genuine per-register/x87/branch grammar differs: '
         f'{[(i,x,y) for i,(x,y) in enumerate(zip(real,source)) if x!=y][:6]}')
    native_bytes=sum(x.size for x in native)
    source_bytes=sum(y.size for y in candidate)
    expected_delta=3*len(indices)
    need(native_bytes==1003 and source_bytes==1003-expected_delta,
         f'original actor {action:#x} real whole case CODE width differs')
    return len(diffs),expected_delta
