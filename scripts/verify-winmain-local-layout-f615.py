#!/usr/bin/env python3
"""F615: complete native 2987B/654-x86 WinMain source-layout experiments.

Cold build ONLY selected actual 654-instruction WinMain whole source TUs
or the 30 specifically affected useful-local C++ layout alternatives.
Native Japanese 1.11 original full function, separate 60-byte afterRET
scene table, genuine 123 CALLs, all 654 ordered x86 mnemonics and source
physical frame slots are checked; NO whole function exactness assumed.
"""
from __future__ import annotations
import argparse
from pathlib import Path
import os
import re
import json
import importlib.util
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
SOURCE=ROOT/'probes/WinMainLocalLayoutF615.cpp'
OUT=ROOT/'.analysis/f615-winmain-local-layout/verified'
NATIVE=0x00602A60
NATIVE_SIZE=2987
SYMBOL='?GameApplicationRunF455@@YGHPAUHINSTANCE__@@0PADH@Z'


def need(test,message):
    if not test:raise ValueError(message)


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    need(spec is not None and spec.loader is not None,'missing native original source reader')
    m=importlib.util.module_from_spec(spec)
    sys.modules[name]=m
    spec.loader.exec_module(m)
    return m


def create_sources():
    source=SOURCE.read_text()
    split='int WINAPI GameApplicationRunF455('
    need(source.count(split)==1,'native complete WinMain C++ entry unexpectedly changed')
    prefix,body=source.split(split,1)
    body=split+body
    app='    AppModeF455 appMode(16);'
    msg='          MSG msg;'
    main='      HWND main=CreateWindowExA('
    path='    char path[260];'
    wnd='    WNDCLASSEXA win;'
    ready='          HANDLE readyEvent=CreateEventA(0,FALSE,FALSE,0);'
    width='    int windowWidth=GetSystemMetrics(45)+640+GetSystemMetrics(5)+GetSystemMetrics(7);'
    height='    int windowHeight=GetSystemMetrics(46)+480+GetSystemMetrics(6)+GetSystemMetrics(8)+GetSystemMetrics(4);'
    directory="    char* directoryEnd=strrchr(path,'\\\\');"
    items=[app,msg,main,path,wnd,ready,width,height,directory]
    need(all(body.count(item)==1 for item in items),
         'WinMain native useful local declaration/assignment source no longer single')
    results={'baseline':source}
    def scene_path(orientation):
        code=body.replace('    GameScenesF455* currentScene = 0;\n','').replace(path+'\n','')
        code=re.sub(r'\bcurrentScene\b','context.currentScene',code)
        code=re.sub(r'\bpath\b','context.path',code)
        code=code.replace(app,app+'\n    NativeStartupScenePathF500 context;\n    context.currentScene = 0;',1)
        top=prefix
        if orientation=='path-scene':
            a='struct NativeStartupScenePathF500 {GameScenesF455* currentScene; char path[260];};'
            b='struct NativeStartupScenePathF500 {char path[260]; GameScenesF455* currentScene;};'
            need(top.count(a)==1,'real WinMain native scene/path aggregate definition changed')
            top=top.replace(a,b)
        return top+code
    results['scene-path-aggregate']=scene_path('scene-path')
    results['path-scene-aggregate']=scene_path('path-scene')
    def move(src,what,location):
        need(src.count(what)==src.count(location)==1,
             'source chosen actual POD declaration/destination not present once')
        return src.replace(what+'\n','').replace(location,what+'\n'+location,1)
    for label,old,pos in (
        ('path-before-app',path,app),
        ('wnd-before-app',wnd,app),
        ('msg-before-app',msg,app),
        ('wnd-before-graphics',wnd,'    GraphicsClientF455 graphics;'),
        ('path-before-graphics',path,'    GraphicsClientF455 graphics;'),
        ('msg-before-graphics',msg,'    GraphicsClientF455 graphics;'),
        ('path-before-scene',path,'    GameScenesF455* currentScene = 0;'),
        ('wnd-before-path',wnd,path),
        ('msg-before-path',msg,path),
        ('msg-before-wnd',msg,wnd),
    ):
        results[label]=prefix+move(body,old,pos)
    s=body.replace(directory,"    directoryEnd=strrchr(path,'\\\\');")
    results['directory-predeclare']=prefix+s.replace(path,'    char* directoryEnd;\n'+path,1)
    def metrics(s):
        original=width+'\n'+height
        replacement=('    struct NativeWindowMetricsF615 { int width; int height; } metrics;\n'
            '    metrics.width=GetSystemMetrics(45)+640+GetSystemMetrics(5)+GetSystemMetrics(7);\n'
            '    metrics.height=GetSystemMetrics(46)+480+GetSystemMetrics(6)+GetSystemMetrics(8)+GetSystemMetrics(4);')
        need(s.count(original)==1,'both original real window metrics absent')
        return s.replace(original,replacement).replace('windowWidth','metrics.width').replace('windowHeight','metrics.height')
    results['genuine-window-metrics-aggregate']=prefix+metrics(body)
    def move_msg(s,location):
        return move(s,msg,location)
    def move_main(s):
        need(s.count(main)==s.count(app)==1,'real main HWND lifetime no longer single')
        return s.replace(main,'      main=CreateWindowExA(').replace(app,'    HWND main;\n'+app,1)
    def move_event(s):
        need(s.count(ready)==s.count(app)==1,'real ready-event HWND lifetime no longer single')
        return s.replace(ready,'          readyEvent=CreateEventA(0,FALSE,FALSE,0);').replace(app,'    HANDLE readyEvent;\n'+app,1)
    def move_dims(s):
        need(s.count(width)==s.count(height)==s.count(app)==1,
             'real main window metrics computation changed')
        s=s.replace(width,'    windowWidth=GetSystemMetrics(45)+640+GetSystemMetrics(5)+GetSystemMetrics(7);')
        s=s.replace(height,'    windowHeight=GetSystemMetrics(46)+480+GetSystemMetrics(6)+GetSystemMetrics(8)+GetSystemMetrics(4);')
        return s.replace(app,'    int windowWidth;\n    int windowHeight;\n'+app,1)
    scene=results['scene-path-aggregate']
    results.update({
        'scene-path-plus-msg-before-app':move_msg(scene,app),
        'scene-path-plus-msg-before-context':move_msg(scene,'    NativeStartupScenePathF500 context;'),
        'scene-path-plus-metrics':prefix+metrics(scene[len(prefix):]),
        'scene-path-plus-msg-plus-metrics':prefix+metrics(move_msg(scene,app)[len(prefix):]),
        'scene-path-plus-msg-plus-actual-main':move_main(move_msg(scene,app)),
        'scene-path-plus-msg-plus-event':move_event(move_msg(scene,app)),
        'scene-path-plus-msg-plus-two-int':move_dims(move_msg(scene,app)),
        'scene-path-plus-msg-plus-two-int-plus-main':move_main(move_dims(move_msg(scene,app))),
        'scene-path-plus-msg-plus-metrics-plus-main':move_main(prefix+metrics(move_msg(scene,app)[len(prefix):])),
        'msg-before-app-plus-hwnd':prefix+move_main(move_msg(body,app)),
        'msg-before-app-plus-actual-event':prefix+move_event(move_msg(body,app)),
        'msg-before-app-plus-int-two':prefix+move_dims(move_msg(body,app)),
        'msg-before-app-plus-metrics':prefix+metrics(move_msg(body,app)),
        'msg-before-app-plus-hwnd-plus-int':prefix+move_dims(move_main(move_msg(body,app))),
        'msg-before-app-plus-all-hwnd-event-int':prefix+move_dims(move_event(move_main(move_msg(body,app)))),
    })
    need(len(results)==30,'physical complete WinMain useful-source permutation matrix changed')
    return results


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    available=create_sources()
    parser.add_argument('--case',choices=sorted(available),
       help='build only ONE selected affected whole original WinMain C++ source TU')
    opt=parser.parse_args()
    selected={opt.case:available[opt.case]} if opt.case else available
    rd=load('f615_reader',ROOT/'scripts/compare-coff-function.py')
    pe=rd.verified_target()
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    original=list(decoder.disasm(rd.pe_bytes_at(pe,NATIVE,NATIVE_SIZE),NATIVE))
    need(len(original)==654 and sum(x.size for x in original)==NATIVE_SIZE
         and original[-1].mnemonic=='ret' and original[-1].op_str=='0x10'
         and original[2].op_str=='esp, 0x278'
         and sum(x.mnemonic=='call' for x in original)==123
         and original[9].op_str=='dword ptr [ebp - 0x184], 0'
         and original[10].op_str=='ecx, [ebp - 0x189]'
         and original[17].op_str=='eax, [ebp - 0x180]',
         'native original whole 2987-byte author game startup x86/stack/frame source changed')
    need(len(rd.pe_bytes_at(pe,0x60360B,60))==60,
         'actual original separate 15-scene afterRET DATA extent changed')
    OUT.mkdir(parents=True,exist_ok=True)
    env=os.environ.copy();env.pop('DISPLAY',None);env.pop('WAYLAND_DISPLAY',None)
    env['WINEPREFIX']=str(ROOT/'.analysis/vc71-wine')
    env['WINEDLLOVERRIDES']='winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d'
    rows=[]
    for name,source in selected.items():
        cpp=OUT/(name+'.cpp');obj=cpp.with_suffix('.obj')
        cpp.write_text(source)
        build=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(cpp),str(obj),
             '/Od','/Ob0','/Gy','/GR-','/GX-','/GS','/Zi'],
             cwd=ROOT,env=env,capture_output=True,text=True,timeout=180)
        cpp.with_suffix('.log').write_text(build.stdout+build.stderr)
        need(build.returncode==0,
             f'{name}: original 2,987-byte real VC7.1 startup source compilation failed: {build.stderr[-400:]}')
        code,fields=rd.object_function(obj,SYMBOL)
        inst=[]
        for x in decoder.disasm(code,0):
            inst.append(x)
            if x.mnemonic=='ret':break
        size=inst[-1].address+inst[-1].size
        wrong=[i for i,(a,b) in enumerate(zip(original,inst)) if a.mnemonic!=b.mnemonic]
        need(len(inst)==654 and not wrong and len(code)-size==60
             and len(fields)==173 and size in (2930,2945,2954,2969,2981,3017,3026,3041,3053)
             and size!=NATIVE_SIZE,
             f'{name}: genuine WinMain x86/codegen layout hypothesis differs from prior control; inspect native source')
        slots=[inst[i].op_str for i in (7,9,10,12,14,17)]
        if name=='msg-before-app-plus-all-hwnd-event-int':
            need(slots[-1]=='eax, [ebp - 0x180]' and slots[1]!='dword ptr [ebp - 0x184], 0',
                 'original path offset reproducible but still wrong scene owner native slot')
        matchwidth=sum(a.size==b.size for a,b in zip(original,inst))
        row={'variant':name,'original_complete_native_CODE_bytes':NATIVE_SIZE,
             'source_complete_CODE_bytes':size,
             'native_original_x86_instructions':654,'source_ordered_x86_mnemonics_identical':654,
             'original_physical_instruction_widths_equal':matchwidth,
             'original_direct_call_instructions':123,
             'source_physical_COFF_fields_including_15_afterRET_DATA_DWORDS':len(fields),
             'source_afterRET_scene_jump_DATA_bytes':len(code)-size,
             'source_real_local_slots_7_9_10_12_14_17':slots,
             'source_original_path_buffer_slot_matches':slots[-1]=='eax, [ebp - 0x180]',
             'source_original_active_scene_slot_matches':slots[1]=='dword ptr [ebp - 0x184], 0',
             'original_whole_CODE_exact':False,'new_accepted_authored_CODE_bytes':0}
        rows.append(row)
        print(f'F615 {name}: complete native 2987B/654 x86 vs VC7.1 '
              f'{size}B/654 x86, {matchwidth}/654 equal original x86 widths, '
              '173 authentic COFF fields/60 afterRET bytes, whole source NONEXACT',flush=True)
    out=OUT/('summary.json' if not opt.case else f'summary-{opt.case}.json')
    out.write_text(json.dumps(rows,indent=2)+'\n')
    print(f'F615 {len(rows)} selected whole 2987B authored WinMain source TUs, '
          'all genuine original length/EBP nonexact, 0 accepted whole functions, '
          'NO all-unit cold replay.',flush=True)


if __name__=='__main__':
    try:main()
    except (OSError,ValueError,subprocess.TimeoutExpired) as e:
        print('F615 original native WinMain full-function local layout failed:',e,file=sys.stderr)
        raise SystemExit(1)
