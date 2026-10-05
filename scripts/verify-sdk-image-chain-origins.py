#!/usr/bin/env python3
"""Replay complete original SDK image/JPEG/PNG/zlib policy source and fields."""
import argparse
import csv
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import tempfile
import capstone

ROOT=Path(__file__).resolve().parents[1]
_SPEC=importlib.util.spec_from_file_location('image_blit_prior',ROOT/'scripts/verify-sdk-blit-origins.py')
BASE=importlib.util.module_from_spec(_SPEC);_SPEC.loader.exec_module(BASE)
module=BASE.module
digest=BASE.digest
contains=BASE.contains
check_probe=BASE.check_probe


def metadata_digest(value):
    return digest(json.dumps(value,sort_keys=True,separators=(',',':')).encode())


def verify_plan(m):
    if m['evidence_id']!='R199' or {r['address']:r['size'] for r in m['functions']}!=KEYS or len(m['functions'])!=95:
        raise ValueError('Image complete bounded policy cohort differs')
    for key,expected in PLAN_DIGESTS.items():
        if metadata_digest(m[key])!=expected:raise ValueError('Image frozen complete provenance differs: '+key)
    code={r['base']:r for r in m['sections'] if r['kind']=='code'}
    if (len(m['sections'])!=449 or len(code)!=212 or sum(r['size'] for r in code.values())!=47056
            or sum(len(r.get('fields',[])) for r in m['sections'])!=904 or len(m['anchors'])!=109
            or len(m['retained_unknown'])!=2 or sum(r['size'] for r in m['retained_unknown'])!=100
            or len(m['interiors'])!=1 or m['weak_references']):
        raise ValueError('Image whole source graph or independent lifetime scope differs')
    for r in m['functions']:
        old=r['original_function'];a=int(r['address'],16);source=code[r['address']]
        if (r['symbol'].startswith('??') or r['original_origin']['origin']!='unknown'
                or old['status']!='unclassified' or old['match_percent']!='0.00'
                or any(old[k] for k in ['source_file','owner','calling_convention','signature'])
                or source['function']!=old or source['origin']!=r['original_origin']
                or r['symbol']!=source['symbol'] or r['code_size']!=source['flow']['code_size']
                or r['accepted_function']!=dict(old,size=str(r['size']),span_end=f'0x{a+r["size"]-1:08X}',
                    proposed_name=r['symbol'],module='D3DX8',status='excluded',owner='library',evidence='R199',notes=r['notes'])
                or r['accepted_origin']!=dict(address=r['address'],origin='library',subsystem='D3DX8',disposition='exclude',
                    confidence='whole-original-sdk-image-png-jpeg-zlib-source-scoped-fields-state-switch-and-nonreturn-policy',evidence_id='R199')):
            raise ValueError('Image loses original state or gives source/private ABI/mapping/exact/lifetime credit')
        references=[dict(owner=q['base'],kind=q['kind'],field=b) for q in m['sections'] for b in q.get('bindings',[])
                    if b['target_address']==r['address'] and b['symbol_type']==32]
        if m['policy_references'][r['address']]!=references or (r['size']<=32 and not references):
            raise ValueError('Image short policy lacks its complete genuine typed source references')
    if sum(r['size'] for r in m['functions'])!=24062 or sum(r['code_size'] for r in m['functions'])!=23926:
        raise ValueError('Image truncated code/table/nonreturn source extent')
    changed={r['address'] for r in m['functions'] if int(r['original_function']['size'])!=r['size']}
    if changed!={'0x0060F6FF','0x0062245E','0x00622671','0x00629471','0x0063A903','0x0063D7EC'}:
        raise ValueError('Image changes an unrelated canonical extent')


def check_public(body,emission,flow):
    expected={'ProbeImageJump':('_longjmp','pop','esi'), 'ProbePngJump':('_longjmp','int3',''),
              'ProbeImageExit':('_exit','pop','esi')}
    api={'ProbeImageInfo':'_D3DXGetImageInfoFromFileInMemory@12','ProbeSaveSurface':'_D3DXSaveSurfaceToFileA@20'}
    seen=set()
    for r in emission:
        defs=[d for d in r['definitions'] if d['type']==32]
        if not defs:continue
        if len(defs)!=1 or defs[0]['offset']:raise ValueError('Image public observer is not one whole function')
        name=defs[0]['symbol'].split('@@')[0][1:];seen.add(name)
        h=struct.unpack_from('<8sIIIIIIHHI',body,20+(r['section']-1)*40)
        ins=flow.instructions(body[h[4]:h[4]+h[3]],0,h[3]);calls=[i for i in ins if i.group(capstone.CS_GRP_CALL)]
        fields=[(f['type'],f['symbol']['symbol']) for f in r['fields']]
        if name in expected:
            symbol,mnemonic,operands=expected[name]
            if (fields[-1]!=('REL32',symbol) or ins[-2].mnemonic!='call' or ins[-1].mnemonic!=mnemonic
                    or ins[-1].op_str!=operands or ins[-1].size!=1
                    or ins[-1].address!=ins[-2].address+ins[-2].size
                    or any(i.group(capstone.CS_GRP_RET) for i in ins)):
                raise ValueError('Image whole ordinary nonreturn policy/suffix differs')
            if name=='ProbeImageExit' and fields!=[('REL32','_ProbeImageDestroy'),('REL32','_exit')]:
                raise ValueError('Image generic notify/destroy/exit policy differs')
        elif name=='ProbeImageSetJump':
            if fields!=[('REL32','__setjmp3')] or len(calls)!=1 or ins[-1].mnemonic!='ret':
                raise ValueError('Image ordinary original setjmp lowering differs')
        elif name in api:
            if fields!=[('REL32',api[name])] or len(calls)!=1 or ins[-1].mnemonic!='ret':
                raise ValueError('Image complete original public WINAPI declaration differs')
        else:raise ValueError('Image unexpected public observer')
    if seen!=set(expected)|set(api)|{'ProbeImageSetJump'}:
        raise ValueError('Image a complete ordinary/public control is missing')


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args()
    m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m);public=m['public_control']
    for path,sha in [(EVIDENCE,MANIFEST_SHA256),(public['probe'],public['probe_sha256']),*m['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes())!=sha:raise ValueError('Image immutable source or previous provenance differs: '+path)
    for filename in ['verify-runtime-leaf-origins.py','verify-sdk-blit-origins.py']:
        result=subprocess.run([str(ROOT/'scripts/repo-python'),'scripts/'+filename],cwd=ROOT,capture_output=True,text=True,check=True)
        print('retained '+filename+': '+result.stdout.strip().splitlines()[-1],flush=True)
    replay(m,args.evidence_only)
    c=module('image_public_coff','compare-coff-function.py');coff=module('image_public_data','coff_data.py');flow=module('image_public_flow','sdk_image_carriers.py')
    BASE.cold_control(public,'ImagePublic',check_public,c,coff,flow)
    print('R199 origins OK:95 complete original SDK/image/JPEG/PNG/zlib library policies;23926 code plus136 genuine table bytes;'
          '449 whole source sections62866/all904 fields,212 complete CFGs;three state tables34 labels/all paths bounded;'
          'four whole nonreturn source tails retained and three canonical suffix extent fixes;109 whole independent anchors26174/268 fields;'
          'original R107 setjmp3/absolute CRT provenance;two lifetime alternatives100 and one interior compiler row unchanged;'
          'six cold whole public/jump controls132,seven ordinary sections,86 original headers and readonly observation68;'
          'no private owner/layout/source/ABI/mapping/exact credit.')
    return 0


def source_key(owner, field, prior):
    if field['symbol_section']>0 and field['symbol_storage']==3:
        return owner,field['symbol_section'],field['symbol_index']
    return prior.field_key(owner,field)


def bind_fields(raw, fields, bindings, catalog, owner, address, data_image=False):
    v = module('dispatch_bind', 'verify-sdk-x3d-origins.py')
    linked = bytearray(raw); occupied = set(); calls = {}; data = {}
    if len(fields) != len(bindings):
        raise ValueError('SDK dispatch omitted a genuine field')
    for f, b in zip(fields, bindings):
        at = f['offset']; key = source_key(owner, f, v)
        if (any(i in occupied for i in range(at, at+4)) or at < (0 if data_image else 1)
                or at+4 > len(raw) or any(b[k] != value for k, value in f.items())
                or catalog.get(key) != int(b['source_base'], 16)):
            raise ValueError('SDK dispatch real field or source definition differs')
        dest = (catalog[key] + f['addend']) & 0xffffffff
        if dest != int(b['target_address'], 16):
            raise ValueError('SDK dispatch field uses a guessed destination/addend')
        if f['type'] == 'REL32' and not data_image and raw[at-1] in (0xe8, 0xe9):
            struct.pack_into('<I', linked, at, (dest-address-at-4)&0xffffffff); calls[address+at] = dest
        elif f['type'] == 'DIR32':
            struct.pack_into('<I', linked, at, dest); data[address+at] = dest
        else:
            raise ValueError('SDK dispatch unsupported actual field/opcode')
        occupied.update(range(at, at+4))
    return linked, calls, data



def replay(m, evidence_only=False):
    c = module('graphics_target','compare-coff-function.py'); coff = module('graphics_coff','coff_data.py')
    rt = module('graphics_archive','verify-runtime-origins.py'); sdk = module('graphics_sdk','verify-sdk-origins.py')
    extra = module('graphics_sections','sdk_x3d_carriers.py'); cr = module('graphics_bss','sdk_code_carriers.py')
    pe = module('graphics_pe','verify-sdk-x3d-origins.py'); binder = module('graphics_fields','verify-sdk-dispatch-origins.py')
    flow = module('graphics_flow','sdk_image_carriers.py'); api = module('graphics_api','verify-sdk-interface-origins.py')
    target = c.verified_target(); archives = {}
    if digest(target) != m['target_sha256']:
        raise ValueError('Graphics SDK target identity differs')
    for kind,path,key in [('SDK','.tools/msvc710/Vc7/PlatformSDK/Lib/d3dx8.lib','archive_sha256'),
                          ('CRT','.tools/msvc710/Vc7/lib/libcmt.lib','crt_archive_sha256')]:
        raw = (ROOT/path).read_bytes()
        if digest(raw) != m[key]:
            raise ValueError('Graphics SDK original archive differs')
        archives[kind] = {o:(n,b) for o,n,b in rt.archive_members(raw)}
    def member(r, kind='SDK'):
        name, raw = archives[kind][int(r['member_offset'])]
        if name != r['member'] or digest(raw) != r['member_sha256']:
            raise ValueError('Graphics SDK original source owner differs')
        return raw
    functions = {r['address']:r for r in csv.DictReader((ROOT/'config/functions.csv').open())}
    origins = {r['address']:r for r in csv.DictReader((ROOT/'config/function-origins.csv').open())}
    selected = {r['address']:r for r in m['functions']}; state = 'original' if evidence_only else 'accepted'
    catalog = {}; section_bases = {}; decoded = {}; anchor_raw = {}
    def assign(key, address):
        if key in catalog and catalog[key] != address:
            raise ValueError('Graphics SDK independently owned source definitions conflict')
        catalog[key] = address
    imports = module('graphics_imports','verify-import-origins.py').pe_imports(target,c)
    for r in m['imports']:
        if imports.get(int(r['address'],16)) != (r['dll'],r['name']):
            raise ValueError('Graphics SDK actual imported API differs')
        assign(r['symbol'],int(r['address'],16))
    absolute = m['absolute']['__except_list']; body = member(absolute,'CRT')
    if [d for d in coff.parse_symbols(body,c.coff_name)[1] if d['symbol']=='__except_list' and d['section'] != 0] != [absolute['definition']] or absolute['definition']['section'] != -1 or absolute['definition']['offset']:
        raise ValueError('Graphics SDK FS field has no original absolute CRT definition')
    assign('__except_list',0)
    readonly = sdk.verify_readonly_sections(c,rt,target)
    legacy = list(csv.DictReader((ROOT/'config/sdk-origin-evidence.csv').open()))
    legacy_bindings = list(csv.DictReader((ROOT/'config/sdk-origin-relocations.csv').open()))
    legacy_symbols = {int(r['address'],16):r['coff_symbol'] for r in legacy}
    scratch = ROOT/'build/origin-sdk-graphics-verification'; scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj = Path(temp)/'Original.obj'
        for r in m['anchors']:
            old = r['record']; q = r['comparison']; a = int(r['address'],16)
            path = ROOT/r['path']; tree = list(csv.DictReader(path.open())) if path.suffix=='.csv' else json.loads(path.read_text())
            if not contains(tree,old) or functions.get(r['address']) != r['function'] or origins.get(r['address']) != r['origin']:
                raise ValueError('Graphics SDK changes an independently accepted anchor')
            owner = dict(old,member_sha256=q['member_sha256']); body = member(owner,'CRT' if r.get('kind','').startswith('CRT') else 'SDK')
            obj.write_bytes(body)
            size = None if r.get('kind')=='CRT' else sdk.complete_comdat_size(body,q['symbol'],c.coff_name)
            raw, fields = c.object_function(obj,q['symbol'],size)
            if len(raw)!=q['size'] or digest(raw)!=q['source_sha256'] or fields!=q['fields']:
                raise ValueError('Graphics SDK accepted anchor full original extent/fields differ')
            if r.get('kind')=='R008':
                linked,_ = sdk.bind_sdk_function(raw,fields,[z for z in legacy_bindings if z['address']==r['address']],legacy_symbols,a,body,c,rt,target,readonly)
            else:
                old_bindings = old.get('bindings',old.get('relocation_bindings'))
                if r['path']=='config/runtime-leaf-origin-evidence.json':
                    if old['coff_symbol']!='__setjmp3' or len(fields)!=len(old['relocations']) or any({k:f[k] for k in z}!=z for f,z in zip(fields,old['relocations'])):
                        raise ValueError('Image changes the complete original R107 setjmp3 source record')
                    old_bindings=[dict(f,target_address='0x00000000') for f in fields]
                    if any(f['type']!='DIR32' or f['symbol']!='__except_list' or f['addend'] for f in fields):
                        raise ValueError('Image setjmp3 field is not its retained original absolute CRT symbol')
                if old_bindings is None:
                    old_bindings = [dict(f,target_address=d) for f,d in zip(fields,old.get('destinations',[]))]
                if len(old_bindings)!=len(fields):
                    raise ValueError('Graphics SDK anchor omits an original field')
                linked = bytearray(raw)
                for f,b,z in zip(fields,q['bindings'],old_bindings):
                    if any(f[k]!=z[k] or f[k]!=b[k] for k in ['offset','type','symbol','addend','local_symbol_offset']) or b['target_address']!=z['target_address']:
                        raise ValueError('Graphics SDK anchor invents a previous callee/data binding')
                    at=f['offset']; dest=int(z['target_address'],16)
                    struct.pack_into('<I',linked,at,(dest-a-at-4)&0xffffffff if f['type']=='REL32' else dest)
            if linked!=c.pe_bytes_at(target,a,len(raw)) or digest(linked)!=q['body_sha256']:
                raise ValueError('Graphics SDK entire unmasked accepted anchor differs')
            sn = old.get('symbol',old.get('coff_symbol')); assign(sn,a); anchor_raw[sn]=(raw,fields)
        for r in m['data_anchors']:
            q=r['record']; body=member(q); raw, definition, fields=api.vendor_table(body,q['symbol'],c,coff)
            if not contains(json.loads((ROOT/r['path']).read_text()),q) or len(raw)!=q['size'] or digest(raw)!=q['source_sha256'] or definition!=q['definition'] or fields!=[{k:v for k,v in f.items() if k!='target_address'} for f in q['fields']]:
                raise ValueError('Graphics SDK previous entire owning vtable differs')
            linked=bytearray(raw)
            for f in q['fields']:
                struct.pack_into('<I',linked,f['offset'],int(f['target_address'],16))
            if linked!=c.pe_bytes_at(target,int(q['address'],16),len(raw)) or digest(linked)!=q['body_sha256']:
                raise ValueError('Graphics SDK previous unmasked owning vtable differs')
            assign(q['symbol'],int(q['address'],16))
        for r in m['sections']:
            body=member(r); a=int(r['base'],16); number=r['section'] if r['kind']=='bss' else r['source']['section']
            key=(r['member_offset'],number)
            if key in section_bases and section_bases[key]!=a:
                raise ValueError('Graphics SDK actual source section has conflicting placements')
            section_bases[key]=a
            if r['kind']=='bss':
                h=struct.unpack_from('<8sIIIIIIHHI',body,20+(number-1)*40)
                defs=[d for d in coff.parse_symbols(body,c.coff_name)[1] if d['section']==number]
                if h[3]!=r['size'] or h[4] or h[9]!=r['flags'] or not h[9]&0x80 or defs!=r['definitions'] or cr.zero_region(target,a,r['size'])!=r['pe_region']:
                    raise ValueError('Graphics SDK complete BSS definitions/virtual zero-fill differ')
                fields=[]
            else:
                raw,fields,source=extra.section_carrier(body,number,c,coff); defs=source['definitions']
                if source!=r['source'] or fields!=r['fields'] or len(raw)!=r['size'] or digest(raw)!=r['source_sha256'] or pe.image_permissions(target,a,len(raw))!=source['flags']&0xe0000000:
                    raise ValueError('Graphics SDK whole source definitions/AUX/fields/permissions differ')
                decoded[key]=(raw,fields)
            for d in defs:
                if d['storage']==2:
                    assign(d['symbol'],a+d['offset'])
            if r['kind']=='code':
                row=selected.get(r['base']); f=row[state+'_function'] if row else r['function']; o=row[state+'_origin'] if row else r['origin']
                if functions.get(r['base'])!=f or origins.get(r['base'])!=o:
                    raise ValueError('Graphics SDK changes a selected/retained ownership snapshot')
                inner=[z for z in m['interiors'] if z['owner']==r['base']]
                if {z['function']['address'] for z in inner}!={k for k in functions if a<int(k,16)<a+r['size']} or any(functions[z['function']['address']]!=z['function'] or origins[z['function']['address']]!=z['origin'] or z['origin']['origin']!='compiler' for z in inner):
                    raise ValueError('Graphics SDK source extent hides or changes an interior candidate')
        weak = module('blit_weak','verify-standard-exception-origins.py')
        for w in m['weak_references']:
            body=archives['SDK'][w['member_offset']][1]
            if weak.read_weak_reference(body,w['symbol'],c,coff,w['member_offset'])!=w:
                raise ValueError('Blit weak reference lacks its exact original COFF AUX/fallback')
            fallback=w['fallback_definition']; own=(w['member_offset'],fallback['section'])
            if own not in section_bases or w['fallback_symbol'] not in catalog:
                raise ValueError('Blit weak fallback lacks an independently complete original body')
            dest=section_bases[own]+fallback['offset']
            if catalog[w['fallback_symbol']]!=dest:
                raise ValueError('Blit substitutes its actual same-member weak fallback')
            assign(w['symbol'],dest)
        # Resolve scoped fields from their real original section/definition. Never
        # populate this catalog from observed native relocation destinations.
        for r in m['sections']:
            for f in r.get('fields',[]):
                key=source_key(r['member_offset'],f,pe); own=(r['member_offset'],f['symbol_section'])
                if key in catalog:
                    if f['symbol_type']==32 and f['symbol_section']>0 and own not in section_bases:
                        body=member(r); obj.write_bytes(body)
                        raw,z=c.object_function(obj,f['symbol'],sdk.complete_comdat_size(body,f['symbol'],c.coff_name))
                        prior=anchor_raw[f['symbol']]
                        if raw!=prior[0] or z!=prior[1]:
                            raise ValueError('Graphics SDK actual duplicate source COMDAT differs')
                    continue
                if own not in section_bases or f['symbol_section']<=0:
                    raise ValueError('Graphics SDK field has no independently complete original owner')
                assign(key,section_bases[own]+f['symbol_offset'])
        for r in m['sections']:
            if r['kind']=='bss':
                continue
            key=(r['member_offset'],r['source']['section']); raw,fields=decoded[key]; a=int(r['base'],16)
            linked,calls,data=bind_fields(raw,fields,r['bindings'],catalog,r['member_offset'],a,data_image=r['kind']=='data')
            if linked!=c.pe_bytes_at(target,a,len(raw)) or digest(linked)!=r['body_sha256']:
                raise ValueError('Graphics SDK entire unmasked code/data comparison differs')
            if r['kind']=='code':
                primary=[d for d in r['source']['definitions'] if d['type']==32 and not d['offset']]
                roots=[0] if primary else sorted({f['symbol_offset']+f['addend'] for q in m['sections'] if q['member_offset']==r['member_offset'] for f in q.get('fields',[]) if f['symbol_section']==r['source']['section'] and f['symbol_type']==0 and f['symbol_storage']==6})
                if roots!=r['roots'] or flow.flow(linked,a,roots,fields,calls,data,r['switch'],r['dynamic_tail'],r['nonreturn'])!=r['flow']:
                    raise ValueError('Graphics SDK complete normal/EH/switch/indirect flow differs')
                if 'dispatch_paths' in r and flow.dispatch_paths(linked,a,fields,calls,data)!=r['dispatch_paths']:
                    raise ValueError('Blit actual CPU/slot-write/tail alternatives differ')
        authored=module('graphics_authored','verify-authored-origins.py')
        for r in m['game_parents']:
            a=int(r['address'],16); raw=c.pe_bytes_at(target,a,int(r['function']['size'])); site=int(r['call_site'],16); off=site-a
            if (functions[r['address']]!=r['function'] or origins[r['address']]!=r['origin'] or r['origin']['origin']!='authored'
                    or digest(raw)!=r['body_sha256'] or list(authored.verify_body(raw,a))!=r['cfg']
                    or raw[off]!=0xe8 or site+5+struct.unpack_from('<i',raw,off+1)[0]!=int(r['destination'],16)):
                raise ValueError('Graphics SDK independent whole game parent/call differs')
        result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/m['probe']),str(obj),*m['profile']],cwd=ROOT,capture_output=True,text=True)
        inventory=module('graphics_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
        if result.returncode or api.included_headers(result.stdout+result.stderr)!=m['headers'] or inventory(obj.read_bytes(),c,coff)!=m['emission']:
            raise ValueError('Graphics SDK cold public C++ ABI/header/all-section observation differs')
        check_probe(obj.read_bytes(),m['emission'],flow)
        raw,_=coff.readonly_section(obj.read_bytes(),m['layout']['section'],c.coff_name)
        if list(struct.unpack('<12I',raw[16:64]))!=m['layout']['values']:
            raise ValueError('Graphics SDK complete public structure/enum layout differs')



EVIDENCE = 'config/sdk-image-chain-origin-evidence.json'
MANIFEST_SHA256 = '77ea2fe0c65ac983a29b752f1724a6648a2472021fa474074c80c55fceb5504a'
KEYS = {'0x0060F761': 624, '0x0061014E': 1430, '0x006106E4': 833, '0x00610A25': 680, '0x00610CCD': 713, '0x00610FC6': 469, '0x0062256F': 76, '0x0060F6FF': 28, '0x006201DF': 192, '0x0060F71C': 29, '0x0062092E': 193, '0x0062029F': 5, '0x006226EE': 259, '0x006228B1': 371, '0x00622A24': 32, '0x00622E77': 77, '0x006230F6': 129, '0x00605251': 110, '0x0062245E': 27, '0x00628171': 180, '0x006223E1': 125, '0x006277BB': 65, '0x006288C7': 48, '0x00628247': 27, '0x006299A6': 25, '0x00629963': 13, '0x00622671': 30, '0x00629970': 54, '0x006254C6': 83, '0x00625519': 5, '0x0062945A': 23, '0x006253CC': 40, '0x0062551E': 24, '0x00629A49': 26, '0x0062A3A5': 502, '0x0062A59B': 298, '0x0062A6C5': 74, '0x0062A70F': 267, '0x0062A81A': 239, '0x0062A909': 439, '0x0062AAC0': 74, '0x0062A17D': 412, '0x00622A56': 935, '0x00622FC4': 291, '0x0062AE82': 3, '0x0062AE3D': 11, '0x0062AE85': 1, '0x00627811': 252, '0x0062790D': 142, '0x0062799B': 146, '0x00627A2D': 158, '0x00627ACB': 97, '0x00627B2C': 97, '0x00627B8D': 383, '0x00628060': 225, '0x00628141': 48, '0x00627773': 55, '0x00628569': 429, '0x00629375': 229, '0x0062A319': 140, '0x00629AC1': 98, '0x006226A4': 37, '0x00624F73': 275, '0x0062AB0A': 548, '0x00629471': 871, '0x00625086': 440, '0x0062AE53': 11, '0x0062AE69': 5, '0x0062AE5E': 11, '0x0062AE48': 11, '0x006309C5': 135, '0x0062FEA4': 275, '0x0062EEE2': 117, '0x0062E8E9': 289, '0x0062DEF3': 449, '0x0062DA34': 131, '0x0062D799': 116, '0x0062C003': 248, '0x0062B3C4': 211, '0x0063B240': 16, '0x00629A63': 94, '0x006226C9': 37, '0x00624C6A': 777, '0x0063A903': 1947, '0x0062FD93': 258, '0x0062E6CB': 542, '0x0062E1CF': 35, '0x0062D5E2': 439, '0x0062BFC8': 59, '0x0063E268': 47, '0x0063D7EC': 1380, '0x0062E325': 316, '0x0063B7B7': 76, '0x0063B76B': 76, '0x0063FFF4': 693}
PLAN_DIGESTS = {'sections': '2fef9cbab6586dba855318ad347d5cb71ae293d5da6a22de1bef898f2f1d1987', 'anchors': '8d211593aa0068a0e89d35144e06a9f566c24cc38b7d83b895913cf8db706c9b', 'data_anchors': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'interiors': '581d81aec46366d113f68f74bd432028ffdffacecb8e9c32c01ea9965d15f8ea', 'retained_unknown': '7e645583519e7014e66ad016b9432ec55708799e31c7f508523b4491a4457c1d', 'policy_references': '233e577287fed466e0f34614b5ebe260158b2fe7b9713b3080b1f140becfc2a7', 'public_control': 'c287f2de6958675fad2d84542a817399896cae52c8f9f070c18cb7aae5188b69', 'absolute': '8e1f56739e02ad0900ff6fe1a81eecb7cfcf9597595512608c6e532445948d11', 'imports': 'bf438bf955bb35502675edd15740fb16b9724c5a58309c2357b379dddae9c020', 'weak_references': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945'}

if __name__=='__main__':
    raise SystemExit(main())
