#!/usr/bin/env python3
"""F791: independent complete native Archive/Scene destructor owner-lifetime negatives.

Prior simple casts and separate used locals have not reproduced
authentic EBP slots. Test grouped genuinely used resource ownership,
natural aggregate field permutations and lexical timing under true
VC7.1; compare whole original PE functions and authentic COFF
relocations. Not accepted exact; no all-unit replay.
"""
from __future__ import annotations
import importlib.util
import json
import os
from pathlib import Path
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'.analysis/f791-resource-teardown-owners'
ARCHIVE=('??1ArchiveCatalogF343@@QAE@XZ',0x0041CE50,171,51,14)
SCENE=('??1BattleSceneF200@@UAE@XZ',0x0043B0B0,248,75,12)
RELEASE={
    'archive_resource_copy':'*g_ArchiveResourcesAt0068BE08.At(index)',
    'archive_file_copy':'*g_ArchiveNamesAt0068BE1C.At(index)'
}

def load(tag,path):
    sp=importlib.util.spec_from_file_location(tag,ROOT/path)
    if sp is None or sp.loader is None:raise ValueError('missing source/native helper')
    module=importlib.util.module_from_spec(sp)
    sys.modules[tag]=module
    sp.loader.exec_module(module)
    return module

def require(pred,msg):
    if not pred:raise ValueError(msg)

def source_variants():
    base=(ROOT/'probes/ArchiveCatalogNativeLifetimeF584.cpp').read_text()
    old=('            delete *g_ArchiveResourcesAt0068BE08.At(index);\n'
         '            char* filename = *g_ArchiveNamesAt0068BE1C.At(index);\n'
         '            free(filename);')
    require(base.count(old)==1,'original authored archive destructor source-only hypothesis changed')
    variants={}
    for order in ('frd','rdf','drf'):
        fields={'f':'char* filename;','r':'ArchiveResourceF343* resource;',
                'd':'ArchiveResourceF343* forDelete;'}
        decl='struct ArchiveReleaseF791 {'+' '.join(fields[c] for c in order)+'};\n'
        body=('            ArchiveReleaseF791 local;\n'
              '            local.resource=*g_ArchiveResourcesAt0068BE08.At(index);\n'
              '            local.forDelete=local.resource;\n'
              '            delete local.forDelete;\n'
              '            local.filename=*g_ArchiveNamesAt0068BE1C.At(index);\n'
              '            free(local.filename);')
        variants['archive-three-'+order]=base.replace(
            'extern unsigned int g_ArchiveUseCountAt0068BE04;',
            decl+'extern unsigned int g_ArchiveUseCountAt0068BE04;').replace(old,body)
    for order in ('fr','rf'):
        fields={'f':'char* filename;','r':'ArchiveResourceF343* resource;'}
        decl='struct ArchiveReleaseF791 {'+' '.join(fields[c] for c in order)+'};\n'
        body=('            ArchiveReleaseF791 local;\n'
              '            local.resource=*g_ArchiveResourcesAt0068BE08.At(index);\n'
              '            delete local.resource;\n'
              '            local.filename=*g_ArchiveNamesAt0068BE1C.At(index);\n'
              '            free(local.filename);')
        variants['archive-two-'+order]=base.replace(
            'extern unsigned int g_ArchiveUseCountAt0068BE04;',
            decl+'extern unsigned int g_ArchiveUseCountAt0068BE04;').replace(old,body)

    scene=(ROOT/'probes/BattleSceneTextureDeleteF589.cpp').read_text()
    old_layout=('struct CleanupPointersF215 {\n'
                '    void* digitAtlas;\n'
                '    void* firstCombo;\n'
                '    void* secondCombo;\n};')
    old_timing=('    if (FIELD(TextureManagerF200*,0x08))\n'
                '        delete FIELD(TextureManagerF200*,0x08);\n'
                '    CleanupPointersF215 released;')
    require(scene.count(old_layout)==scene.count(old_timing)==1,
            'natural native scene source owner/timing hypotheses changed')
    for order in ('fdc','fcd','dfc','dcf'):
        fields={'f':'digitAtlas','d':'firstCombo','c':'secondCombo'}
        decl=('struct CleanupPointersF215 {\n'+
              ''.join('    void* '+fields[c]+';\n' for c in order)+'};')
        variants['scene-fields-'+order]=scene.replace(old_layout,decl)
    variants['scene-aggregate-before-texture']=scene.replace(old_timing,
        '    CleanupPointersF215 released;\n'
        '    if (FIELD(TextureManagerF200*,0x08))\n'
        '        delete FIELD(TextureManagerF200*,0x08);')
    return variants

def main():
    rd=load('f791_rd','scripts/compare-coff-function.py')
    f584=load('f791_f584','scripts/verify-archive-delete-expressions-f584.py')
    f589=load('f791_f589','scripts/verify-scene-texture-delete-f589.py')
    target=rd.verified_target()
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    n_arc=list(decoder.disasm(rd.pe_bytes_at(target,ARCHIVE[1],ARCHIVE[2]),ARCHIVE[1]))
    n_scene=list(decoder.disasm(rd.pe_bytes_at(target,SCENE[1],SCENE[2]),SCENE[1]))
    require(len(n_arc)==51 and len(n_scene)==75,
            'native original independently decoded full function boundaries changed')
    require([n_arc[i].op_str for i in (22,24,38)]==
            ['dword ptr [ebp - 0xc], eax','dword ptr [ebp - 8], ecx','dword ptr [ebp - 0x10], eax'],
            'actual original archive 3 temporary owner slots changed')
    require([n_scene[i].op_str for i in (26,28,42,52,62)]==
            ['dword ptr [ebp - 0x14], edx','dword ptr [ebp - 0x10], eax',
             'dword ptr [ebp - 0x18], eax','dword ptr [ebp - 0x1c], ecx',
             'dword ptr [ebp - 0x20], edx'],
            'actual native scene five release slot EBP roles changed')
    env=os.environ.copy()
    env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    OUT.mkdir(parents=True,exist_ok=True)
    results=[]
    for name,source in source_variants().items():
        is_archive=name.startswith('archive')
        symbol,addr,expected_bytes,expected_x86,expected_fields=ARCHIVE if is_archive else SCENE
        cpp=OUT/(name+'.cpp')
        obj=OUT/(name+'.obj')
        cpp.write_text(source)
        cp=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
            '/Od','/Ob0','/Gy','/GR-','/GX-' if is_archive else '/GX',
            '/GS','/Zi'],cwd=ROOT,env=env,capture_output=True,text=True,timeout=240)
        (OUT/(name+'.log')).write_text(cp.stdout+cp.stderr)
        require(cp.returncode==0,'full destructor compiler failure '+name+' '+(cp.stdout+cp.stderr)[-550:])
        code,refs=rd.object_function(obj,symbol)
        instructions=list(decoder.disasm(code,0))
        require(sum(x.size for x in instructions)==len(code),
                'invalid or truncated compiled original whole destructor '+name)
        require(len(refs)==expected_fields,
                'complete source native relocation field count changed '+name)
        row={'variant':name,'actual_original_function':hex(addr),
             'native_original_CODE_B':expected_bytes,
             'compiled_original_shaped_CODE_B':len(code),
             'original_x86_count':expected_x86,
             'compiled_x86_count':len(instructions),
             'source_physical_COFF_fields':len(refs),
             'entire_function_exact':False}
        if is_archive:
            require((name.startswith('archive-three') and len(code)==183 and len(instructions)==55)
                 or (name.startswith('archive-two') and len(code)==177 and len(instructions)==53),
                'archive real natural 3/2-member source changes native code unexpectedly')
            row['true_native_resource_delete_filename_slots']=['-0xC','-0x8','-0x10']
            row['comparison_result']='size-mismatch (complete candidate)'
            row['source_resource_and_filename_actually_released']=True
        else:
            require(len(code)==248 and len(instructions)==75,
                    'natural scene field owner variant lost genuine native size')
            fields=f589.ORIGINAL_COFF
            require({r['offset'] for r in refs}==set(fields),
                    'scene original actual 12 PE field offsets not preserved')
            for ref in refs:
                off=int(ref['offset'])
                rtype,targetdest=fields[off]
                nativefield=rd.pe_bytes_at(target,addr,expected_bytes)[off:off+4]
                dest=(int.from_bytes(nativefield,'little') if rtype=='DIR32' else
                      addr+off+4+int.from_bytes(nativefield,'little',signed=True))
                require(ref['addend']==0 and ref['type']==rtype and
                        ref['local_symbol_offset'] is None and dest==targetdest,
                        'source scene original physical PE field mismatch '+name)
            native=rd.pe_bytes_at(target,addr,expected_bytes)
            mask={i for r in refs for i in range(r['offset'],r['offset']+4)}
            overlap=sum(code[i]==native[i] for i in range(expected_bytes) if i not in mask)
            require((name in ('scene-fields-fdc','scene-fields-fcd','scene-aggregate-before-texture')
                     and overlap==191)
                    or (name in ('scene-fields-dfc','scene-fields-dcf') and overlap==189),
                    'native scene physical EBP slots or true nonfield bytes changed '+name)
            row['original_nonfield_byte_overlap']=f'{overlap}/200'
            row['source_slot_ordinals_26_28_42_52_62']=[instructions[j].op_str
                                                         for j in (26,28,42,52,62)]
            row['independently_physical_PE_fields_verified']=12
        print('F791 '+name+': original '+str(expected_bytes)+'B, source '+str(len(code))+
              'B, '+str(len(instructions))+' x86, '+str(len(refs))+' COFF fields'+
              (', physical '+row['original_nonfield_byte_overlap'] if not is_archive else ''),
              flush=True)
        results.append(row)
    require(len(results)==10,'native tests need ten full source variants')
    (OUT/'verified-summary.json').write_text(json.dumps({
        'native_target':'Japanese v1.11 supplied th075.exe',
        'archive_original_game_171B_unmatched':True,
        'scene_original_game_248B_unmatched':True,
        'real_original_archived_source_hypotheses':5,
        'real_original_scene_source_hypotheses':5,
        'all_complete_original_PE_relocs_compared_for_equal_size_scene':True,
        'actual_legacy_original_EBP_owner_temp_evidence_remeasured':True,
        'variants':results,
        'formally_credited_new_callable_game_CODE':0,
        'full_979_cold_replay_run':False
    },indent=2)+'\n')
    print('F791 ten genuine Archive/Scene whole-function VC7.1 teardown variants tested; none native exact, only 2 target functions compiled. No all-unit replay.')
if __name__=='__main__':
    try:main()
    except (ValueError,OSError,subprocess.TimeoutExpired) as e:
        print('F791 native archive/scene owner lifetime research FAILED:',e,file=sys.stderr)
        raise SystemExit(1)
