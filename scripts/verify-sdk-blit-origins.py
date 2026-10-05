#!/usr/bin/env python3
"""R198 complete source-owned blit/codec graph replay, without masked fields."""
import argparse
import csv
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import tempfile
import capstone

ROOT = Path(__file__).resolve().parents[1]
_SPEC = importlib.util.spec_from_file_location('blit_original_graphics',ROOT/'scripts/verify-sdk-graphics-origins.py')
BASE = importlib.util.module_from_spec(_SPEC)
_SPEC.loader.exec_module(BASE)
module = BASE.module
digest = BASE.digest
contains = BASE.contains
check_probe = BASE.check_probe


def metadata_digest(value):
    return digest(json.dumps(value,sort_keys=True,separators=(',',':')).encode())


def verify_plan(m):
    if m['evidence_id']!='R198' or len(m['functions'])!=108 or {r['address']:r['size'] for r in m['functions']}!=KEYS:
        raise ValueError('Blit bounded function cohort differs')
    for key,expected in PLAN_DIGESTS.items():
        if metadata_digest(m[key])!=expected:
            raise ValueError('Blit complete frozen source/provenance differs: '+key)
    code={r['base']:r for r in m['sections'] if r['kind']=='code'}
    constructors=set(m['constructor_functions'])
    if (len(constructors)!=40 or len(m['retained_unknown'])!=6
            or len(m['sections'])!=371 or len([r for r in m['sections'] if r['kind']=='code'])!=233
            or sum(r['size'] for r in m['sections'] if r['kind']=='code')!=41451
            or sum(len(r.get('fields',[])) for r in m['sections'])!=1363
            or len(m['weak_references'])!=40 or len(m['anchors'])!=81 or len(m['interiors'])!=49):
        raise ValueError('Blit whole source/weak/field/retained scope differs')
    for r in m['functions']:
        old=r['original_function'];source=code[r['address']];a=int(r['address'],16)
        if (source['function']!=old or source['origin']!=r['original_origin']
                or r['original_origin']['origin']!='unknown' or old['status']!='unclassified'
                or any(old[k] for k in ['owner','source_file','calling_convention','signature'])
                or old['match_percent']!='0.00' or r['symbol']!=source['symbol']
                or r['code_size']!=source['flow']['code_size']):
            raise ValueError('Blit loses original canonical complete source/ownership context')
        expected=dict(old,size=str(r['size']),span_end=f'0x{a+r["size"]-1:08X}',
                      proposed_name=r['symbol'],module='D3DX8',status='excluded',owner='library',evidence='R198',notes=r['notes'])
        confidence=('whole-original-sdk-explicit-pointer-constructor-and-independent-cold-default-copy-alternatives'
                    if r['address'] in constructors else
                    'whole-original-sdk-blit-codec-policy-complete-scoped-source-weak-switch-dispatch-and-public-abi')
        if (r['accepted_function']!=expected or r['accepted_origin']!=dict(address=r['address'],origin='library',
                subsystem='D3DX8',disposition='exclude',confidence=confidence,evidence_id='R198')):
            raise ValueError('Blit changes source/private ABI/mapping/exact or ownership scope')
        if r['address'] in constructors:
            callers=[dict(owner=q['base'],field=b) for q in m['sections'] if q['kind']=='code'
                     for b in q['bindings'] if b['type']=='REL32' and b['target_address']==r['address']]
            if m['constructor_callers'][r['address']]!=callers:
                raise ValueError('Blit constructor callers are not the complete genuine source fields')
            if (not r['symbol'].startswith('??0') or 'PAUD3DX_BLT@@' not in r['symbol']
                    or r['size']!=int(old['size']) or not m['constructor_callers'][r['address']]
                    or {q['cleanup'] for q in source['flow']['returns']}!={12 if r['address']=='0x00615C08' else 4}):
                raise ValueError('Blit constructor credit lacks an explicit input signature/full ABI/caller')
        elif r['symbol'].startswith('??'):
            raise ValueError('Blit gives independent lifetime alternatives policy credit')
    end=next(r for r in m['functions'] if r['address']=='0x0060BE10')
    if end['source_record']!=m['retained_end_context'] or metadata_digest(end)!='5e0c2d42efefa57ebf5f4100ae96f0b0354163e02b6246304dd1f9be639af442':
        raise ValueError('Blit changes the exact historical End transition')


def check_public(body, emission, flow):
    apis={'ProbeFilter':'_D3DXFilterTexture@16','ProbeSurfaceCopy':'_D3DXLoadSurfaceFromSurface@32',
          'ProbeVolumeCopy':'_D3DXLoadVolumeFromVolume@32','ProbeSurfaceMemory':'_D3DXLoadSurfaceFromMemory@40',
          'ProbeVolumeMemory':'_D3DXLoadVolumeFromMemory@44'}
    seen=set()
    for r in emission:
        definitions=[d for d in r['definitions'] if d['type']==32]
        if not definitions:continue
        if len(definitions)!=1 or definitions[0]['offset']:
            raise ValueError('Blit cold public control is not one whole function')
        name=definitions[0]['symbol'].split('@@')[0][1:];seen.add(name)
        h=struct.unpack_from('<8sIIIIIIHHI',body,20+(r['section']-1)*40)
        ins=flow.instructions(body[h[4]:h[4]+h[3]],0,h[3]);calls=[i for i in ins if i.group(capstone.CS_GRP_CALL)]
        fields=[(f['type'],f['symbol']['symbol']) for f in r['fields']]
        if name in apis:
            if len(calls)!=1 or fields!=[('REL32',apis[name])]:
                raise ValueError('Blit cold whole original public WINAPI declaration differs')
        elif name=='ProbeEnvEnd':
            if (len(calls)!=1 or fields or calls[0].operands[0].type!=capstone.x86.X86_OP_MEM
                    or not calls[0].operands[0].mem.base or calls[0].operands[0].mem.index
                    or calls[0].operands[0].mem.disp!=40):
                raise ValueError('Blit full original public End slot differs')
        elif name in ('ProbeSelectA','ProbeSelectX'):
            if (len(calls)!=1 or fields[0]!=('REL32','_ProbeCpuChoice') or len(fields)!=7
                    or not any(i.mnemonic=='test' and i.op_str=='eax, eax' for i in ins)
                    or ins[-1].mnemonic!='jmp' or ins[-1].op_str!='eax'
                    or set(s for t,s in fields if t=='DIR32')!=
                       {'_ProbePackedBox','_ProbeScalarA','_ProbeScalarX','?ProbeBoxA@@3P6AJPAI0IIII@ZA',
                        '?ProbeBoxX@@3P6AJPAI0IIII@ZA'}):
                raise ValueError('Blit natural cdecl callback policy/CPU/store/tail differs')
        else:raise ValueError('Blit unexpected public control')
    if seen!=set(apis)|{'ProbeEnvEnd','ProbeSelectA','ProbeSelectX'}:
        raise ValueError('Blit cold whole public controls are missing')
    data=[r for r in emission if any(d['symbol']=='?ProbeBoxA@@3P6AJPAI0IIII@ZA' for d in r['definitions'])]
    if len(data)!=1 or data[0]['size']!=8 or [(f['offset'],f['type'],f['symbol']['symbol']) for f in data[0]['fields']]!=[
            (0,'DIR32','?ProbeSelectA@@YAJPAI0IIII@Z'),(4,'DIR32','?ProbeSelectX@@YAJPAI0IIII@Z')]:
        raise ValueError('Blit ordinary lazy callbacks lose whole initial data/typed fields')


def check_constructor_controls(body, emission, flow):
    expected={'??0PointerConstructorBase@@QAE@PAUProbeInput@@IK@Z':12,
              '??0PointerConstructorDerived@@QAE@PAUProbeInput@@@Z':4,
              '??0DefaultConstructorBase@@QAE@XZ':0,
              '??0ImplicitDefaultObserver@@QAE@XZ':0,
              '??0ImplicitCopyObserver@@QAE@ABV0@@Z':4}
    seen=set()
    for r in emission:
        for d in r['definitions']:
            if not d['symbol'].startswith('??0'):continue
            sn=d['symbol']
            if sn not in expected or d['offset'] or d['type']!=32 or sn in seen:
                raise ValueError('Blit constructor observer has an unexpected definition')
            h=struct.unpack_from('<8sIIIIIIHHI',body,20+(r['section']-1)*40)
            ins=flow.instructions(body[h[4]:h[4]+h[3]],0,h[3]);returns=[i for i in ins if i.group(capstone.CS_GRP_RET)]
            if len(returns)!=1 or (returns[0].operands[0].imm if returns[0].operands else 0)!=expected[sn]:
                raise ValueError('Blit cold pointer/default/copy whole ABI differs')
            seen.add(sn)
    if seen!=set(expected):raise ValueError('Blit implicit/explicit constructor alternative is absent')


def cold_control(control, name, check, c, coff, flow):
    api=module('blit_public_headers','verify-sdk-interface-origins.py')
    inventory=module('blit_public_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    scratch=ROOT/'build/origin-sdk-blit-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj=Path(temp)/(name+'.obj')
        result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/control['probe']),str(obj),*control['profile']],
                              cwd=ROOT,capture_output=True,text=True)
        if (result.returncode or api.included_headers(result.stdout+result.stderr)!=control['headers']
                or inventory(obj.read_bytes(),c,coff)!=control['emission']):
            raise ValueError('Blit cold whole '+name+' emission/header identity differs')
        body=obj.read_bytes();check(body,control['emission'],flow)
        raw,_=coff.readonly_section(body,control['layout']['section'],c.coff_name)
        if len(raw)!=control['layout']['size'] or list(struct.unpack('<'+'I'*(len(raw)//4),raw))!=control['layout']['values']:
            raise ValueError('Blit full '+name+' readonly observer differs')


def check_vector_context(m,c,flow):
    target=c.verified_target();sdk=module('blit_vector_comdat','verify-sdk-origins.py')
    rt=module('blit_vector_archive','verify-runtime-origins.py')
    members={o:b for o,n,b in rt.archive_members((ROOT/'.tools/msvc710/Vc7/lib/libcmt.lib').read_bytes())}
    scratch=ROOT/'build/origin-sdk-blit-verification';scratch.mkdir(parents=True,exist_ok=True)
    for r in m['anchors']:
        if r.get('kind')!='CRT-COMDAT':continue
        q=r['comparison'];body=members[int(r['record']['member_offset'])]
        if sdk.complete_comdat_size(body,q['symbol'],c.coff_name)!=q['size']:
            raise ValueError('Blit vector helper loses its independently whole COMDAT')
        with tempfile.TemporaryDirectory(dir=scratch) as temp:
            obj=Path(temp)/'Original.obj';obj.write_bytes(body)
            source,fields=c.object_function(obj,q['symbol'],q['size'])
        ins=flow.instructions(source,0,len(source));by={i.address for i in ins};sites={f['offset'] for f in fields}
        roots=sorted({0}|{i.operands[0].imm for i in ins if i.mnemonic=='call'
            and i.operands[0].type==capstone.x86.X86_OP_IMM and i.address+i.imm_offset not in sites and i.operands[0].imm in by})
        a=int(r['address'],16)
        calls={a+b['offset']:int(b['target_address'],16) for b in q['bindings'] if b['type']=='REL32'}
        data={a+b['offset']:int(b['target_address'],16) for b in q['bindings'] if b['type']=='DIR32'}
        if roots!=r['source_roots'] or flow.flow(c.pe_bytes_at(target,a,q['size']),a,roots,fields,calls,data)!=r['whole_flow']:
            raise ValueError('Blit vector helper truncates its cleanup/unwind source path')


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true')
    args=parser.parse_args();m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    controls=[m['public_control'],m['constructor_control']]
    for path,sha in [(EVIDENCE,MANIFEST_SHA256),*[(q['probe'],q['probe_sha256']) for q in controls],*m['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes())!=sha:raise ValueError('Blit immutable complete source/provenance differs: '+path)
    # Preserve the complete old floor carrier and all historical source evidence.
    for filename in ['verify-floor-math-origins.py','verify-sdk-x86-policy-origins.py','verify-sdk-mmx-origins.py','verify-sdk-resource-lock-origins.py']:
        result=subprocess.run([str(ROOT/'scripts/repo-python'),'scripts/'+filename],cwd=ROOT,capture_output=True,text=True,check=True)
        print('retained '+filename+': '+result.stdout.strip().splitlines()[-1],flush=True)
    replay(m,args.evidence_only)
    c=module('blit_target_control','compare-coff-function.py');coff=module('blit_data_control','coff_data.py')
    flow=module('blit_flow_control','sdk_blit_carriers.py');check_vector_context(m,c,flow)
    cold_control(controls[0],'Public',check_public,c,coff,flow)
    cold_control(controls[1],'ConstructorRoles',check_constructor_controls,c,coff,flow)
    print('R198 origins OK:108 complete library entries/36143 code bytes plus92 guarded table bytes;'
          '68 policies and40 explicit input constructors,with six independent lifetime alternatives retained;'
          '371 full original source sections43875/all1363 genuine fields,233 whole normal/EH/switch/dispatch CFGs;'
          '40 actual weak AUX/fallbacks,source-static F2IBegin placements,81 full accepted anchors,49 unchanged interior compiler rows;'
          'complete CRT vector98/96 cleanup paths and unchanged floor289 shared carrier;'
          'whole cold original public APIs/cdecl callback policies and complete ordinary default/copy/input-constructor controls;'
          'one exact historical End transition and seven fixed replay-script hash pairs;no private owner/layout/source/ABI/mapping/exact credit.')
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
    flow = module('graphics_flow','sdk_blit_carriers.py'); api = module('graphics_api','verify-sdk-interface-origins.py')
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
                if roots!=r['roots'] or flow.flow(linked,a,roots,fields,calls,data,r['switch'],r['dynamic_tail'])!=r['flow']:
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



EVIDENCE = 'config/sdk-blit-origin-evidence.json'
MANIFEST_SHA256 = '6d537daa5c3605c37ac3e72ba1d09eba6702689f040f6b34f20ae3ba2a3d3b10'
KEYS = {'0x0060BE10': 227, '0x0060BD3C': 177, '0x0060779F': 740, '0x0060B7AF': 1421, '0x006070BD': 422, '0x0060731F': 134, '0x0060A7F4': 3892, '0x00605410': 223, '0x006055FB': 211, '0x00614A33': 282, '0x0061A4CC': 1884, '0x00615E70': 123, '0x00612CCE': 241, '0x00612DBF': 514, '0x00612FC1': 516, '0x006131C5': 1059, '0x006135E8': 1170, '0x00613B7A': 998, '0x00613F60': 1841, '0x00614691': 930, '0x006114F3': 1140, '0x00611C41': 49, '0x00611F2F': 49, '0x00613A7A': 256, '0x00616027': 236, '0x00615EEB': 204, '0x00616113': 291, '0x00616236': 257, '0x00616337': 257, '0x00616438': 257, '0x00616539': 285, '0x00616656': 291, '0x00616779': 254, '0x00616877': 169, '0x00616920': 291, '0x00616A43': 257, '0x00616B44': 291, '0x00616C67': 208, '0x00616D37': 280, '0x0061728F': 261, '0x006171BA': 213, '0x006170CF': 235, '0x00616FD9': 246, '0x00616F14': 197, '0x00617394': 267, '0x006178EF': 199, '0x006177B9': 310, '0x006176AF': 266, '0x006175D9': 214, '0x0061749F': 314, '0x00626D05': 1106, '0x006271D1': 52, '0x00626BF1': 276, '0x0062719D': 52, '0x00619FD6': 681, '0x006157CC': 1018, '0x006179B6': 199, '0x00617C5A': 348, '0x00617B6B': 239, '0x00617A7D': 238, '0x00611E9C': 56, '0x00611F00': 47, '0x00615BC6': 35, '0x0062572C': 35, '0x006260D8': 2052, '0x00625868': 773, '0x00625B6D': 1387, '0x0062576E': 250, '0x00618FA7': 28, '0x006190DC': 28, '0x00619119': 28, '0x00619156': 28, '0x0061937F': 28, '0x006193BC': 28, '0x006196CA': 28, '0x00619707': 28, '0x00619744': 28, '0x00619781': 28, '0x006197BE': 28, '0x00619888': 28, '0x00619934': 28, '0x00619B63': 28, '0x00619DEE': 28, '0x00619DB1': 28, '0x00619C73': 28, '0x00619C1A': 28, '0x00619BDD': 28, '0x00619BA0': 28, '0x00619E2B': 28, '0x00619F5C': 28, '0x00619F1F': 28, '0x00619EE2': 28, '0x00619EA5': 28, '0x00619E68': 28, '0x0061A336': 24, '0x0061A41A': 24, '0x0061A3E1': 24, '0x0061A3A8': 24, '0x0061A4B4': 24, '0x0061A36F': 24, '0x00619F99': 28, '0x0061A49C': 24, '0x0061A2F9': 28, '0x0061A2BC': 28, '0x0061A27F': 28, '0x00615C08': 588, '0x00619971': 498, '0x00618FC3': 248}
PLAN_DIGESTS = {'sections': '498f348443e9a5d92be94d7c8b6b3c511e6c15372616b88a0a3afd70e0c0a2b9', 'anchors': '3a82a54e5013f8e75b4fe708ee939f203d1bba85eb260d7f8f56fd85b24dc899', 'data_anchors': 'dfff353f84c2aa39c95faef71349a26279e03fd8bac49e512a16ad08d3b49185', 'weak_references': '4aff2f4df20a0c78a102223399cfee68df520294c4fded0d81e21c919bcf1d9e', 'interiors': '7f077c5ec0193cb0f50909f004984ea459bcba7fa5721fb98e35cd0d15e9a908', 'retained_unknown': '810aa3837495024c5643b925322081297d51f97daa4f80659d7cbf1a4b39b387', 'constructor_functions': '3eb332dfe25dd6609062a807709d47a198d40ba99caa6e4dd9bb9901df9f853b', 'constructor_callers': 'dcaf99b02d29cc9f728c3768653f27ba3aeb2fe23629ec6f56286d6828b7ad4b', 'floor_carrier': '4dc01d3b1b0f9cfe1de0f5ee7c881c994250f693e9d7f3530dfb9d4045d0b61f', 'replay_script_transitions': '9eb3d747e7f11ccf76de4ad03da67f873d4a998b0c5b2303dd85f932885d1143', 'public_control': '4edc0f119df49bc288dcd6f9fd1fbe437408e894e711c292ef9329af667589b1', 'constructor_control': '9ca654c656d17d65b04ab6ed4cd8d21c731d65f8359a34d6f8ec6fd08cd15e5d', 'retained_end_context': 'd88899da6100e808c609517f4ac4fdb04eac243946d84e82298fd30e37b81ca1'}


if __name__=='__main__':
    raise SystemExit(main())
