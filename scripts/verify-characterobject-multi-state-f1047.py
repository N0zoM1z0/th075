#!/usr/bin/env python3
"""F1047/F1054 check twelve recovered *interior* game states of one 81KB Boss.

Cold compile only the tracked complete one-switch original-shaped parent
prototype (other actions remain markers). Independently read original PE
whole 81KB CODE and original full 567B afterRET DATA, all 92 native DIR32
label partitions, original 199 physical sparse map bytes, all 846 native
instruction mnemonic ordinals and the 62 true external PE destinations.
The original whole callable remains NONEXACT and receives zero credit.
"""
from pathlib import Path
import hashlib,importlib.util,json,os,re,subprocess,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];O=R/'.analysis/f1047-object-multistate';O.mkdir(parents=True,exist_ok=True)
spec=importlib.util.spec_from_file_location('f1047rd',R/'scripts/compare-coff-function.py')
rd=importlib.util.module_from_spec(spec);sys.modules[spec.name]=rd;spec.loader.exec_module(rd)
PE=rd.verified_target();D=Cs(CS_ARCH_X86,CS_MODE_32)
B=next(z for z in json.loads((R/'config/fighter-boss-dispatch-fingerprints.json').read_text())['bosses'] if z['address']==0x0050A580)
BASE=B['address'];CODE=B['size'];DATA=B['postret_size']
assert CODE==81539 and DATA==567 and B['instructions']==17435
orig=rd.pe_bytes_at(PE,BASE,CODE)
assert hashlib.sha256(orig).hexdigest()==B['sha256']
N=list(D.disasm(orig,BASE));assert len(N)==17435 and N[-1].address+N[-1].size==BASE+CODE
assert N[2].op_str=='esp, 0x3a0' and N[3].op_str=='dword ptr [ebp - 0xac], ecx'
original_after=rd.pe_bytes_at(PE,BASE+CODE,DATA)
assert hashlib.sha256(original_after).hexdigest()==B['postret_sha']
table=B['tables'][0];native_dense=rd.pe_bytes_at(PE,table['dense_addr'],table['slots']*4)
native_sparse=rd.pe_bytes_at(PE,table['map_addr'],table['map_length'])
assert (table['slots'],table['map_length'])==(92,199)
assert hashlib.sha256(native_dense).hexdigest()==table['dense_sha']
assert hashlib.sha256(native_sparse).hexdigest()==table['map_sha']
assert native_dense+native_sparse==original_after
original_labels=[int.from_bytes(native_dense[k*4:k*4+4],'little') for k in range(92)]
E=os.environ.copy();E.pop('DISPLAY',None);E.pop('WAYLAND_DISPLAY',None)
E['WINEPREFIX']=str(R/'.analysis/vc71-wine');E['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
obj=O/'F1047-whole-recovered-source.obj'
cp=subprocess.run([str(R/'scripts/compile-probe.sh'),str(R/'probes/CharacterObjectWhole0050A580F1044.cpp'),str(obj),'/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi','/I','src','/I','probes'],cwd=R,env=E,capture_output=True,text=True,timeout=360)
(O/'F1047-whole-source-compile.log').write_text(cp.stdout+cp.stderr)
assert cp.returncode==0,(cp.stdout+cp.stderr)[-900:]
code,refs=rd.object_function(obj,'?Advance@FighterSwitchF569_Boss0050A580@@QAEXXZ')
I=[]
for x in D.disasm(code,0):
 I.append(x)
 if x.mnemonic=='ret':break
end=I[-1].address+I[-1].size
assert (end,len(I),len(code)-end,len(refs))==(4373,1050,DATA,236)
S=sorted([r for r in refs if r['offset']>=end],key=lambda x:x['offset'])
assert len(S)==92 and all(r['offset']==end+4*i and r['type']=='DIR32' and r['addend']==0 and r['local_symbol_offset'] is not None for i,r in enumerate(S))
assert code[end+368:end+567]==native_sparse
# Native branch dispatch and case label equivalence, including original
# default slots, must remain authentic even with not-yet-recovered actions.
assert all((original_labels[i]==original_labels[j])==(S[i]['local_symbol_offset']==S[j]['local_symbol_offset']) for i in range(92) for j in range(92))
rx=re.compile(r'\b(?:[er]?(?:ax|bx|cx|dx|si|di|sp|bp)|[abcd]h|[abcd]l)\b')
roles=lambda x:tuple(rx.findall(x.op_str))
def original_wide_stack_to_real_shallow_stack(original,source):
 # This partial original-shaped function has not yet restored the
 # genuinely large whole-parent 0x3A0 stack. The original saved this
 # at -0xAC and its real integer-to-float scratch at -0xB4/B8/BC;
 # ordinary C++ places those same genuinely used values at -C/-14/18/1C.
 a=re.search(r'\[ebp - (0x[0-9a-f]+|[0-9]+)\]',original.op_str)
 b=re.search(r'\[ebp - (0x[0-9a-f]+|[0-9]+)\]',source.op_str)
 return (a is not None and b is not None and
         int(a.group(1),0)-int(b.group(1),0)==0xa0)
cases=[('320',0x0050A658,0x0050A80F,91,6,91),
       ('321',0x0050A80F,0x0050AC27,229,19,229),
       ('322',0x0050AC27,0x0050AD46,56,4,56),
       ('325',0x0050B654,0x0050B821,100,7,100),
       ('32b',0x0050CCC3,0x0050CD7A,39,3,39),
       ('32c',0x0050CD7A,0x0050CE97,63,4,63),
       ('32d',0x0050CE97,0x0050CF7A,50,3,50),
       ('32e',0x0050CF7A,0x0050D097,63,4,63),
       ('32f',0x0050D097,0x0050D17A,50,3,50),
       ('332',0x0050D88E,0x0050D929,35,3,35),
       ('337',0x0050E9C0,0x0050EA5B,35,3,35),
       ('345',0x00511C8A,0x00511D25,35,3,13)]
rows=[]
for text,start,stop,count,fields,gpr in cases:
 act=int(text,16);action_slot=native_sparse[act-0x320]
 assert original_labels[action_slot]==start
 # This family of original handler slots is contiguous in physical
 # jump-list label order; do not equate unrelated default slots.
 lo,hi=S[action_slot]['local_symbol_offset'],S[action_slot+1]['local_symbol_offset']
 seq=[x for x in I if lo<=x.address<hi]
 orig_seq=[x for x in N if start<=x.address<stop]
 assert len(seq)==len(orig_seq)==count and orig_seq[-1].address+orig_seq[-1].size==stop
 wrong_m=[i for i,(n,s) in enumerate(zip(orig_seq,seq)) if n.mnemonic!=s.mnemonic]
 wrong_w=[i for i,(n,s) in enumerate(zip(orig_seq,seq)) if n.size!=s.size]
 wrong_g=[i for i,(n,s) in enumerate(zip(orig_seq,seq)) if roles(n)!=roles(s)]
 assert wrong_m==[] and count-len(wrong_g)==gpr,(text,len(wrong_g))
 # No post-state GPR regressions survive once native 0x325 3-shot
 # looping logic is present. Both natural loops create genuine source
 # stack locals; the original itself keeps the second loop at EBP-C.
 if text in ('32b','32c','32d','32e','32f','332','337','345'):
  assert all(orig_seq[j].size-seq[j].size==3
             and original_wide_stack_to_real_shallow_stack(orig_seq[j],seq[j]) for j in wrong_w)
  assert stop-start-(hi-lo)==3*len(wrong_w)
 if text in ('320','321','322','325'):
  expected_shortened={'320':2,'321':4,'322':2,'325':2}[text]
  assert sum(orig_seq[j].size-seq[j].size==4 and orig_seq[j].mnemonic in ('je','jne','jg','jge','jle','jl') for j in wrong_w)==expected_shortened
  assert all((orig_seq[j].size-seq[j].size==3 and original_wide_stack_to_real_shallow_stack(orig_seq[j],seq[j]))
             or (orig_seq[j].size-seq[j].size==4 and orig_seq[j].mnemonic in ('je','jne','jg','jge','jle','jl')) for j in wrong_w)
  assert stop-start-(hi-lo)==3*(len(wrong_w)-expected_shortened)+4*expected_shortened
 actual_fields=[r for r in refs if lo<=r['offset']<hi and r['local_symbol_offset'] is None]
 assert len(actual_fields)==fields
 native_fields=[]
 for i,n in enumerate(orig_seq):
  if n.mnemonic=='call' and n.op_str.startswith('0x'):
   native_fields.append((i,'REL32',n.address+1,int(n.op_str,16)))
  elif (n.mnemonic in ('fsub','fcomp','fadd','fld','fmul','fdiv') and re.search(r'\[0x([0-9a-f]+)\]',n.op_str)):
   add=int(re.search(r'\[0x([0-9a-f]+)\]',n.op_str).group(1),16)
   native_fields.append((i,'DIR32',n.address+n.size-4,add))
 assert len(native_fields)==fields,(text,native_fields,fields)
 typed_matches=[]
 for r in actual_fields:
  j=next(i for i,x in enumerate(seq) if x.address<=r['offset']<x.address+x.size)
  delta=r['offset']-seq[j].address
  assert delta+4<=orig_seq[j].size and r['type'] in ('DIR32','REL32') and r['addend']==0
  p=orig_seq[j].address+delta
  native=next((x for x in native_fields if x[:3]==(j,r['type'],p)),None)
  assert native is not None,(text,j,r,p,native_fields)
  disp=int.from_bytes(rd.pe_bytes_at(PE,p,4),'little',signed=r['type']=='REL32')
  target=p+4+disp if r['type']=='REL32' else disp
  assert target==native[3]
  alias=re.search(r'At([0-9A-Fa-f]{8})',r['symbol'])
  assert alias and int(alias.group(1),16)==target,(text,r['symbol'],hex(target))
  typed_matches.append({'instruction_ordinal':j,'original_field_va':hex(p),'original_target':hex(target),'native_kind':r['type'],'source_symbol':r['symbol']})
 rows.append({'action':text,'original_natively_owned_CODE_B':stop-start,'source_inner_CODE_B':hi-lo,
  'original_and_source_x86_count':count,'full_native_mnemonics_equal':count,
  'original_matching_widths':count-len(wrong_w),'original_matching_GPR_roles':count-len(wrong_g),
  'wrong_original_width_ordinals':wrong_w,'wrong_original_GPR_ordinals':wrong_g,
  'original_native_physical_PE_fields_verified':typed_matches,
  'original_whole_boss_exact':False})
 print(f'{text}: original {stop-start}B/{count} x86, natural partial parent {hi-lo}B/{count} x86; original mnemonic {count}/{count}, width {count-len(wrong_w)}/{count}, GPR {count-len(wrong_g)}/{count}, physical PE {len(typed_matches)}/{fields}',flush=True)
assert sum(x['original_and_source_x86_count'] for x in rows)==846
assert sum(len(x['original_native_physical_PE_fields_verified']) for x in rows)==62
assert sum(x['original_natively_owned_CODE_B'] for x in rows)==3907
assert sum(x['source_inner_CODE_B'] for x in rows)==3030
(O/'verified-summary.json').write_text(json.dumps({'original_sha256':hashlib.sha256(orig).hexdigest(),
 'original_Boss':'0x0050A580','original_whole_CODE_B':CODE,'original_whole_x86':17435,
 'current_partial_marker_filled_source_B':end,'current_partial_marker_filled_source_x86':len(I),
 'recovered_original_game_states':['320','321','322','325','32b','32c','32d','32e','32f','332','337','345'],
 'recovered_native_inner_CODE_B_not_new_exact':3907,'recovered_inner_original_x86_mnemonics_correct':846,
 'recovered_true_native_physical_PE_external_targets_correct':62,
 'all_92_original_case_label_equalities_preserved':True,
 'original_199_sparse_index_map_bytes_identical':True,'original_567_afterRET_DATA_B_preserved':True,
 'original_whole_function_exact':False,'new_accepted_exact_whole_GAME_CODE_B':0,
 'remaining_switch_actions_marker_probes':True,'all_979_cold_replay':False,'cases':rows},indent=2)+'\n')
print('F1047: whole 81KB native original remains NONEXACT. Real C++ source recovered 12 states /3907 original interior bytes /846 original x86 mnemonic slots with all 62 physical PE field identities; still not separate exact callable or whole function.')
