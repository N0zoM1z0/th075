#!/usr/bin/env python3
"""F1033: native 004AC040 whole 82KB and adjacent 58/59 C++ grammars.

Compile each whole, ordinary VC7.1 fighter; keep genuine game calls and all
case control flow. Original PE is read afresh; no case earns independent CODE.
"""
from pathlib import Path
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
import importlib.util, json, os, re, subprocess, sys
R = Path(__file__).resolve().parents[1]
O = R / '.analysis/f1033-third-59-grammar'
O.mkdir(parents=True, exist_ok=True)
base = (R/'probes/FighterWhole004AC040F1020.cpp').read_text()
fragment = (R/'probes/FighterScriptedBounce59F813.inc').read_text()
anchor = '#include "FighterScriptedBounce59F813.inc"'
assert base.count(anchor) == 1
cases = {'baseline':fragment}
def sub(name,old,new):
    assert fragment.count(old)==1,(name,fragment.count(old))
    cases[name]=fragment.replace(old,new,1)
sub('compound-30','F32(0x30)=F32(0x30)+g_F728_RandomOffsetYAt00657858;',
    'F32(0x30)+=g_F728_RandomOffsetYAt00657858;')
sub('compound-54','POS54=POS54-POS5C;','POS54-=POS5C;')
sub('compound-both', 'F32(0x30)=F32(0x30)+g_F728_RandomOffsetYAt00657858;\n                POS54=POS54-POS5C;',
    'F32(0x30)+=g_F728_RandomOffsetYAt00657858;\n                POS54-=POS5C;')
sub('commuted-30', 'F32(0x30)=F32(0x30)+g_F728_RandomOffsetYAt00657858;',
    'F32(0x30)=g_F728_RandomOffsetYAt00657858+F32(0x30);')
sub('typed-f32-54','POS54=POS54-POS5C;',
    'F32(0x54)=F32(0x54)-F32(0x5C);')
sub('readonly-5c','POS54=POS54-POS5C;',
    'POS54=POS54-*reinterpret_cast<const float*>(RAW+0x5c);')
sub('typed-native-62','if (S16(0x62)==3) {','if (I16(0x62)==3) {')
sub('reversed-condition','if (S16(0x62)==3) {','if (3==S16(0x62)) {')
sub('readonly-62','if (S16(0x62)==3) {',
    'if (*reinterpret_cast<const signed short*>(RAW+0x62)==3) {')
sub('indexed-62','if (S16(0x62)==3) {',
    'if (reinterpret_cast<signed short*>(RAW)[0x31]==3) {')
sub('typed-stage-54','POS54+POS48<=g_ThresholdAt0065782C',
    'F32(0x54)+F32(0x48)<=g_ThresholdAt0065782C')
sub('readonly-condition-48','POS54+POS48<=g_ThresholdAt0065782C',
    'POS54+*reinterpret_cast<const float*>(RAW+0x48)<=g_ThresholdAt0065782C')
sub('compound-30-reversed-62','if (S16(0x62)==3) {\n                F32(0x30)=F32(0x30)+g_F728_RandomOffsetYAt00657858;',
    'if (3==S16(0x62)) {\n                F32(0x30)+=g_F728_RandomOffsetYAt00657858;')
sub('const-real-54','POS54=POS54-POS5C;',
    'POS54=POS54-static_cast<const float&>(POS5C);')
sp=importlib.util.spec_from_file_location('f1033reader',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(sp);sys.modules[sp.name]=rd;sp.loader.exec_module(rd)
D=Cs(CS_ARCH_X86,CS_MODE_32)
PE=rd.verified_target();BASE=0x4ac040;SIZE=82796;AFTER=1126
original=list(D.disasm(rd.pe_bytes_at(PE,BASE,SIZE),BASE));assert len(original)==22721
native_after=rd.pe_bytes_at(PE,BASE+SIZE,AFTER)
REG=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
role=lambda x:tuple(REG.findall(x.op_str))
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine')
E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
rows=[]
for name,inc in cases.items():
    (O/(name+'.inc')).write_text(inc)
    src=base.replace(anchor,'#include "'+name+'.inc"',1)
    cpp=O/(name+'.cpp');obj=O/(name+'.obj');cpp.write_text(src)
    cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(cpp),str(obj),
        '/Od','/Ob0','/Gy','/GR-','/GX','/GS','/Zi','/I','src','/I','probes'],
        cwd=R,env=E,capture_output=True,text=True,timeout=345)
    (O/(name+'.log')).write_text(cp.stdout+cp.stderr)
    if cp.returncode:
        rows.append({'variant':name,'compile_error':(cp.stdout+cp.stderr)[-750:]})
        print(name,'COMPILE FAILED',flush=True);continue
    code,refs=rd.object_function(obj,'?Advance@FighterSwitchF598_Boss004AC040@@QAEXXZ')
    I=[]
    for x in D.disasm(code,0):
        I.append(x)
        if x.mnemonic=='ret':break
    end=I[-1].address+I[-1].size
    row={'variant':name,'source_whole_CODE_B':end,'source_whole_x86':len(I),
         'original_whole_CODE_B':SIZE,'original_whole_x86':len(original),
         'source_frame':I[2].op_str,'source_saved_this':I[4].op_str}
    if len(I)==len(original) and len(code)-end==AFTER:
        table=[r for r in refs if r['offset']>=end]
        mask=set();labels={}
        for r in table:
            k=r['offset']-end
            assert r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None
            assert all(j not in mask for j in range(k,k+4))
            mask.update(range(k,k+4))
            addr=int.from_bytes(native_after[k:k+4],'little')
            assert BASE<=addr<BASE+SIZE
            labels.setdefault(addr,r['local_symbol_offset'])
        assert len(table)==151 and len(mask)==604
        assert all(code[end+k]==native_after[k] for k in range(AFTER) if k not in mask)
        total=lambda fn:sum(fn(n,s) for n,s in zip(original,I))
        row.update({'wrong_whole_mnemonic':total(lambda n,s:n.mnemonic!=s.mnemonic),
                    'wrong_whole_width':total(lambda n,s:n.size!=s.size),
                    'wrong_whole_GPR':total(lambda n,s:role(n)!=role(s)),
                    'native_afterRET_DIR32':len(table),'native_afterRET_literal_equal_B':AFTER-len(mask)})
        for label,a,b in [('58',0x4add25,0x4adefa),('59',0x4adefa,0x4ae05e)]:
            lo,hi=labels[a],labels[b]
            seq=[x for x in I if lo<=x.address<hi]
            ref=[x for x in original if a<=x.address<b]
            row[label]={'source_CODE_B':hi-lo,'source_x86':len(seq),
                'original_CODE_B':b-a,'original_x86':len(ref)}
            if len(seq)==len(ref):
                row[label].update({'wrong_mnemonic':[i for i,(n,s) in enumerate(zip(ref,seq)) if n.mnemonic!=s.mnemonic],
                 'wrong_width':[i for i,(n,s) in enumerate(zip(ref,seq)) if n.size!=s.size],
                 'wrong_GPR':[i for i,(n,s) in enumerate(zip(ref,seq)) if role(n)!=role(s)]})
            fields=[r for r in refs if lo<=r['offset']<hi]
            row[label]['relocation_count']=len(fields)
            # All native call/global targets must remain genuine at their x86 ordinals.
            if len(seq)==len(ref) and all(n.mnemonic==s.mnemonic for n,s in zip(ref,seq)):
                for r in fields:
                    j=next(j for j,x in enumerate(seq) if x.address<=r['offset']<x.address+x.size)
                    d=r['offset']-seq[j].address
                    if ref[j].mnemonic!=seq[j].mnemonic or ref[j].size!=seq[j].size:
                        row[label]['unaligned_native_PE_ordinals']=row[label].get('unaligned_native_PE_ordinals',[])+[j]
                        continue
                    field_addr=ref[j].address+d
                    assert r['type'] in ('REL32','DIR32') and r['addend']==0 and r['local_symbol_offset'] is None
                    value=int.from_bytes(rd.pe_bytes_at(PE,field_addr,4),'little',signed=r['type']=='REL32')
                    actual=field_addr+4+value if r['type']=='REL32' else value
                    match=re.search(r'At([0-9A-Fa-f]{6,8})',r['symbol'])
                    expected=int(match.group(1),16) if match else 0x6406ac if r['symbol']=='__ftol2' else None
                    if actual!=expected:
                        row[label]['mismatched_native_PE_targets']=row[label].get('mismatched_native_PE_targets',[])+[{'ordinal':j,'actual':hex(actual),'expected':hex(expected) if expected else None,'symbol':r['symbol']}]
                    else:row[label]['verified_native_PE_targets']=row[label].get('verified_native_PE_targets',0)+1
    rows.append(row)
    print(name,'whole',end,len(I),'M/W/G',row.get('wrong_whole_mnemonic'),row.get('wrong_whole_width'),row.get('wrong_whole_GPR'),
          '58 GPR',len(row.get('58',{}).get('wrong_GPR',[])),
          '59 GPR',len(row.get('59',{}).get('wrong_GPR',[])),flush=True)
(O/'results.json').write_text(json.dumps(rows,indent=2)+'\n')
assert rows[0]['variant']=='baseline'
assert (rows[0]['source_whole_CODE_B'],rows[0]['source_whole_x86'],rows[0]['wrong_whole_mnemonic'],rows[0]['wrong_whole_width'],rows[0]['wrong_whole_GPR'])==(82796,22721,0,12,6958)
assert len(rows[0]['58']['wrong_GPR'])==0 and len(rows[0]['59']['wrong_GPR'])==19
print('Whole 82KB source C++ controls complete; no cropped native acceptance. See ignored results.json.')
