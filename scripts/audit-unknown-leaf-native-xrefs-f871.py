#!/usr/bin/env python3
"""F871 independent PE-wide static original caller/provenance audit.

Rebuild ONLY the three F799/F805 complete unknown native leaf
methods (40B+31B+24B) against pinned th075.exe first.
Independently scan every original PE section for absolute pointers
and EVERY original executable-section byte for direct E8 CALL /
E9 JMP relative operands into these three functions, with three
frequent KNOWN authored game call targets as positive controls.
Do not equate absent direct refs with proof of no indirect call,
and never silently promote unknown origin into authored exact.
No corpus-wide cold replay, no whole-game exact credit.
"""
from pathlib import Path
import csv,importlib.util,json,struct,subprocess,sys

R=Path(__file__).resolve().parents[1]
O=R/'.analysis/f871-native-static-leaf-xrefs'
UNKNOWN={
  0x4135F0:('native owner setter',40,16),
  0x454C00:('native dword reset',24,9),
  0x454F70:('native flag getter',31,15)}
CONTROLS={
  0x40FA30:'original known fighter current action getter',
  0x40FAC0:'original known fighter action setter',
  0x453E20:'original known fighter reset method'}

def need(x,msg):
    if not x:raise ValueError(msg)
def read_reader():
    sp=importlib.util.spec_from_file_location('f871native',R/'scripts/compare-coff-function.py')
    need(sp is not None and sp.loader is not None,'original PE helper missing')
    mod=importlib.util.module_from_spec(sp);sys.modules[sp.name]=mod;sp.loader.exec_module(mod)
    return mod
def sections_from_original(raw):
    coff=struct.unpack_from('<I',raw,0x3c)[0]
    need(raw[coff:coff+4]==b'PE\0\0','original PE header missing')
    count=struct.unpack_from('<H',raw,coff+6)[0]
    optional_size=struct.unpack_from('<H',raw,coff+20)[0]
    base=struct.unpack_from('<I',raw,coff+24+28)[0]
    result=[]
    for j in range(count):
        q=coff+24+optional_size+j*40
        name,virtual,rva,raw_size,raw_offset=struct.unpack_from('<8sIIII',raw,q)
        flags=struct.unpack_from('<I',raw,q+36)[0]
        need(raw_offset+raw_size<=len(raw),'original section raw bytes leave pinned EXE')
        result.append((name.rstrip(b'\0').decode('ascii'),base+rva,
                       raw[raw_offset:raw_offset+raw_size],flags))
    need([r[0] for r in result]==['.text','.rdata','.data','.data1','.rsrc']
         and len(result[0][2])==2449408,
         'Japanese original PE physical sections changed')
    return result

def target_codegen():
    for tag,cmd in [
       ('F799',str(R/'scripts/verify-unknown-owner-field-leaves-f799.py')),
       ('F805',str(R/'scripts/verify-unknown-native-dword-reset-f805.py'))]:
        run=subprocess.run([str(R/'scripts/repo-python'),cmd],
              cwd=R,capture_output=True,text=True,timeout=450)
        (O/(tag+'-native-leaf-only.log')).write_text(run.stdout+run.stderr)
        need(run.returncode==0,'real original small leaf C++ verification failed '+tag+
             (run.stdout+run.stderr)[-700:])
    a=json.loads((R/'.analysis/f799-native-owner-leaves/verified-summary.json').read_text())
    b=json.loads((R/'.analysis/f805-native-borrowed-reset/verified-summary.json').read_text())
    need(len(a['two_complete_original_functions'])==2
         and sorted(x['original_complete_CODE_B'] for x in a['two_complete_original_functions'])==[31,40]
         and a['formal_authored_exact_functions_delta']==0
         and b['original_complete_CODE_B']==24
         and b['three_independent_Cpp_types_same_native_machine_code'] is True
         and b['authored_exact_accepted_delta']==0,
         'native F799/F805 codegen receipt/provenance evidence inconsistent')

def main():
    O.mkdir(parents=True,exist_ok=True)
    rd=read_reader()
    original=rd.verified_target()
    origin={int(row['address'],16):row for row in csv.DictReader((R/'config/function-origins.csv').open())}
    functions={int(row['address'],16):row for row in csv.DictReader((R/'config/functions.csv').open())}
    for addr,(label,size,x86) in UNKNOWN.items():
        need(addr in origin and addr in functions
             and origin[addr]['origin']=='unknown'
             and origin[addr]['disposition']=='review'
             and functions[addr]['status']=='unclassified'
             and int(functions[addr]['size'])==size,
             'candidate native original provenance/whole interval changed '+hex(addr))
    target_codegen()
    sections=sections_from_original(original)
    targets={**UNKNOWN,**CONTROLS}
    receipts={}
    for target in targets:
        abs_uses=[]
        calls=[];jumps=[]
        bytes_target=struct.pack('<I',target)
        for section,start,buf,flags in sections:
            # Search EVERY original byte, including unaligned pointers:
            # a known packed vtable pointer must not be lost to 4-byte
            # alignment assumptions.
            search=0
            while (j:=buf.find(bytes_target,search))>=0:
                abs_uses.append((section,start+j))
                search=j+1
            if not flags&0x20000000:continue
            # Independently inspect EVERY byte as possible E8/E9.
            # Disassembly desynchronization or packed jump DATA in
            # .text cannot hide physical direct relative references.
            for i,opcode in enumerate(buf[:-4]):
                if opcode not in (0xE8,0xE9):continue
                disp=int.from_bytes(buf[i+1:i+5],'little',signed=True)
                dest=(start+i+5+disp)&0xffffffff
                if dest!=target:continue
                (calls if opcode==0xE8 else jumps).append(start+i)
        receipts[hex(target)]={
          'source':UNKNOWN[target][0] if target in UNKNOWN else CONTROLS[target],
          'original_PE_absolute_value_occurrences':len(abs_uses),
          'original_PE_absolute_locations':[hex(addr) for _,addr in abs_uses[:30]],
          'original_CODE_direct_E8_rel32_count':len(calls),
          'original_CODE_direct_E9_rel32_count':len(jumps),
          'sample_direct_calls':[hex(addr) for addr in calls[:8]],
          'sample_direct_jumps':[hex(addr) for addr in jumps[:8]],
          'origin':'unknown' if target in UNKNOWN else 'known game symbol',
          'native_original_complete_CODE_B':UNKNOWN[target][1] if target in UNKNOWN else None}
    for addr in UNKNOWN:
        x=receipts[hex(addr)]
        need(x['original_PE_absolute_value_occurrences']==0
             and x['original_CODE_direct_E8_rel32_count']==0
             and x['original_CODE_direct_E9_rel32_count']==0,
             'new positive original native direct caller or static pointer found '+hex(addr))
    for address in CONTROLS:
        need(receipts[hex(address)]['original_CODE_direct_E8_rel32_count']>500,
             'positive control known native fighter call scan failed '+hex(address))
    out={'target':'SHA-pinned Japanese TH075 v1.11 resources/th075.exe',
       'real_PE_image_base':'0x400000',
       'real_PE_section_bytes_scanned':{name:len(buf) for name,_,buf,_ in sections},
       'original_sections_including_executable_and_nonexecutable_checked':len(sections),
       'three_whole_small_methods_original_Cpp_exact_codegen_replayed':True,
       'unknown_candidate_addresses':[hex(a) for a in UNKNOWN],
       'real_static_original_PE_reference_evidence':receipts,
       'no_direct_reference_does_not_exclude_indirect_or_runtime_call':True,
       'static_original_owner_attribution_proved':False,
       'unknown_provenance_kept_as_unknown_review':True,
       'newly_accepted_authored_whole_CODE_B':0,
       'corpus_wide_cold_replay':False}
    (O/'verified-summary.json').write_text(json.dumps(out,indent=2)+'\n')
    need(json.loads((O/'verified-summary.json').read_text())['unknown_provenance_kept_as_unknown_review'],
         'static attribution receipt failed strict JSON reparse')
    print('F871 three original whole unknown leaves 40B,24B,31B C++ codegen EXACT; every PE section and every possible original .text E8/E9 scanned: zero absolute / direct static xrefs to any. Controls original 40FA30/40FAC0/453E20 each >500 direct calls. Unknown origin STILL UNPROVEN; no accepted exact authored CODE, no all-unit cold replay.')

if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as exc:
        print('F871 original unknown native PE xref audit FAILED:',exc,file=sys.stderr)
        raise SystemExit(1)
