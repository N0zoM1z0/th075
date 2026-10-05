#!/usr/bin/env python3
"""Replay whole original SDK presentation policies, UUID and stack/array provenance."""
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
_SPEC=importlib.util.spec_from_file_location('presentation_prior',ROOT/'scripts/verify-sdk-image-chain-origins.py')
BASE=importlib.util.module_from_spec(_SPEC);_SPEC.loader.exec_module(BASE)
module=BASE.module
digest=BASE.digest
contains=BASE.contains
check_probe=BASE.check_probe


def metadata_digest(value):
    return digest(json.dumps(value,sort_keys=True,separators=(',',':')).encode())


def verify_plan(m):
    if (m['evidence_id']!='R200' or {r['address']:r['size'] for r in m['functions']}!=KEYS
            or len(m['functions'])!=11):
        raise ValueError('Presentation complete bounded cohort differs')
    for key,expected in PLAN_DIGESTS.items():
        if metadata_digest(m[key])!=expected:
            raise ValueError('Presentation frozen complete provenance differs: '+key)
    code=[r for r in m['sections'] if r['kind']=='code'];by={r['base']:r for r in code}
    if (len(m['sections'])!=70 or len(code)!=25 or len(by)!=24
            or sum(r['size'] for r in m['sections'])!=8745
            or sum(len(r.get('fields',[])) for r in m['sections'])!=175
            or len(m['anchors'])!=33 or len(m['retained_unknown'])!=4
            or sum(r['size'] for r in m['retained_unknown'])!=189
            or len(m['interiors'])!=4 or m['weak_references']):
        raise ValueError('Presentation complete graph or protected lifetime scope differs')
    for r in m['functions']:
        old=r['original_function'];source=by[r['address']]
        compiler=r['address'] in COMPILER
        origin='compiler' if compiler else 'library';sub='VC71Compiler' if compiler else 'D3DX8'
        confidence=('whole-original-sdk-vector-deleting-source-and-cold-natural-array-lifetime-control' if compiler else
            'whole-original-sdk-texture-text-sprite-policy-with-scoped-fields-public-abi-and-independent-uuid-stack-alias')
        if (r['original_origin']['origin']!='unknown' or old['status']!='unclassified'
                or old['match_percent']!='0.00' or int(old['size'])!=r['size']
                or any(old[k] for k in ['source_file','owner','calling_convention','signature'])
                or source['function']!=old or source['origin']!=r['original_origin']
                or source['symbol']!=r['symbol'] or source['flow']['code_size']!=r['size']
                or r['origin']!=origin or r['subsystem']!=sub or r['confidence']!=confidence
                or (not compiler and r['symbol'].startswith('??'))
                or r['accepted_function']!=dict(old,proposed_name=r['symbol'],module=sub,status='excluded',
                    owner=origin,evidence='R200',notes=r['notes'])
                or r['accepted_origin']!=dict(address=r['address'],origin=origin,subsystem=sub,disposition='exclude',
                    confidence=confidence,evidence_id='R200')):
            raise ValueError('Presentation changes original extent or gives private/lifetime/source/ABI/exact credit')
        refs=[dict(owner=q['base'],kind=q['kind'],field=b) for q in m['sections'] for b in q.get('bindings',[])
              if b['target_address']==r['address'] and b['symbol_type']==32]
        if m['policy_references'][r['address']]!=refs:
            raise ValueError('Presentation genuine typed references differ')
    if sum(r['size'] for r in m['functions'])!=5581 or sum(r['origin']=='compiler' for r in m['functions'])!=2:
        raise ValueError('Presentation complete nine library/two compiler scope differs')


def check_array(raw,fields,flow,destructor,stride):
    """Check the complete generated array/scalar destruction and release protocol.

    Source/object provenance is checked separately. The observed stride is a
    compiler operand, not a declaration of any incomplete SDK owner layout.
    """
    ins=flow.instructions(raw,0,len(raw))
    symbols=[f['symbol'] if isinstance(f['symbol'],str) else f['symbol']['symbol'] for f in fields]
    if (symbols!=[destructor,'??_M@YGXPAXIHP6EX0@Z@Z','??3@YAXPAX@Z',destructor,'??3@YAXPAX@Z']
            or [i.op_str for i in ins if i.mnemonic=='test']!=['bl, 2','bl, 1','bl, 1']
            or not any(i.mnemonic=='lea' and i.op_str=='edi, [esi - 4]' for i in ins)
            or not any(i.mnemonic=='push' and len(i.operands)==1 and i.operands[0].type==capstone.x86.X86_OP_IMM
                       and i.operands[0].imm==stride for i in ins)
            or len([i for i in ins if i.mnemonic=='je'])!=3
            or any(i.op_str!='4' for i in ins if i.group(capstone.CS_GRP_RET))
            or not any(i.group(capstone.CS_GRP_RET) for i in ins)):
        raise ValueError('Presentation complete compiler array flag/cookie/callback/free/ABI protocol differs')
    for f,symbol in zip(fields,symbols):
        at=f['offset']
        if (symbol==destructor and at==fields[0]['offset'] and raw[at-1]!=0x68
                or at!=fields[0]['offset'] and raw[at-1]!=0xe8):
            raise ValueError('Presentation array destructor pointer/direct call opcode differs')


def check_public(body,emission,flow):
    api={'ProbeErrorText':'_D3DXGetErrorStringA@12','ProbeSaveTexture':'_D3DXSaveTextureToFileA@16'}
    seen=set();arrays=set()
    for r in emission:
        defs=[d for d in r['definitions'] if d['type']==32]
        if not defs:continue
        h=struct.unpack_from('<8sIIIIIIHHI',body,20+(r['section']-1)*40)
        raw=body[h[4]:h[4]+h[3]];ins=flow.instructions(raw,0,len(raw));fields=r['fields']
        if not ins:raise ValueError('Presentation omitted a whole cold ordinary function')
        for d in defs:
            sn=d['symbol'];name=sn.split('@@')[0][1:];seen.add(name)
            if name in api and [(f['type'],f['symbol']['symbol']) for f in fields]!=[('REL32',api[name])]:
                raise ValueError('Presentation original public WINAPI declaration differs')
            if name in ('ProbeFontText','ProbeSpriteDraw'):
                indirect=[i for i in ins if i.mnemonic=='call' and i.operands[0].type==capstone.x86.X86_OP_MEM]
                if fields or len(indirect)!=1 or indirect[0].operands[0].mem.disp!=(24 if name=='ProbeFontText' else 20):
                    raise ValueError('Presentation original public COM draw slot differs')
            if name=='ProbeTextStorage':
                if [(f['type'],f['symbol']['symbol']) for f in fields]!=[('REL32','__alloca_probe'),('REL32','_ProbeUseTextStorage')]:
                    raise ValueError('Presentation natural dynamic stack lowering differs')
                call=next(i for i in ins if i.address+1==fields[0]['offset'])
                if (call.mnemonic!='call'
                        or [(i.mnemonic,i.op_str) for i in ins[4:7]]!=[
                            ('mov','eax, esi'),('add','eax, 3'),('and','eax, 0xfffffffc')]):
                    raise ValueError('Presentation stack helper loses actual EAX size protocol')
            if sn.startswith('??_E'):
                cls='DirectArrayObserver' if 'DirectArrayObserver' in sn else 'ArrayLifetimeObserver'
                destructor='??1'+cls+('@@QAE@XZ' if cls=='DirectArrayObserver' else '@@UAE@XZ')
                check_array(raw,fields,flow,destructor,4 if cls=='DirectArrayObserver' else 8);arrays.add(cls)
    if (not set(api)|{'ProbeFontText','ProbeSpriteDraw','ProbeTextStorage','ProbeDirectArrayCreate','ProbeDirectArrayDelete'} <= seen
            or arrays!={'DirectArrayObserver','ArrayLifetimeObserver'}):
        raise ValueError('Presentation complete public and natural compiler alternatives absent')
    m=json.loads((ROOT/EVIDENCE).read_text())
    expected={'?PresentationIUnknown@@3U_GUID@@B':m['foreign_guids'][0]['record']['source_sha256'],
              '_IID_ID3DXSprite':next(r['source_sha256'] for r in m['sections'] if r.get('symbol')=='_IID_ID3DXSprite')}
    for symbol,sha in expected.items():
        rows=[r for r in emission if any(d['symbol']==symbol and not d['offset'] for d in r['definitions'])]
        if len(rows)!=1 or rows[0]['fields'] or rows[0]['size']!=16:
            raise ValueError('Presentation cold full public GUID definition differs')
        h=struct.unpack_from('<8sIIIIIIHHI',body,20+(rows[0]['section']-1)*40)
        if digest(body[h[4]:h[4]+h[3]])!=sha:
            raise ValueError('Presentation public header GUID differs from complete original source')


def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--evidence-only',action='store_true');args=p.parse_args()
    m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    for path,sha in [(EVIDENCE,MANIFEST_SHA256),(m['public_control']['probe'],m['public_control']['probe_sha256']),*m['retained_sha256'].items()]:
        if digest((ROOT/path).read_bytes())!=sha:
            raise ValueError('Presentation immutable source or retained provenance differs: '+path)
    replay(m,args.evidence_only)
    c=module('presentation_public_coff','compare-coff-function.py');coff=module('presentation_public_data','coff_data.py')
    flow=module('presentation_public_flow','sdk_image_carriers.py')
    BASE.BASE.cold_control(m['public_control'],'Presentation',check_public,c,coff,flow)
    print('R200 origins OK:9 complete SDK policies5431 and2 generated vector-deleting wrappers150;'
          '70 complete source sections8745/all175 fields,25 CFGs/24 native code bases;33 complete retained anchors6911/93 fields;'
          'original UUID IUnknown16 and full chkstk/alloca alias61;four lifetime alternatives189/four interior compiler rows unchanged;'
          '69 cold ordinary sections727 code bytes,86 headers and complete public readonly layout40;'
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
                          ('CRT','.tools/msvc710/Vc7/lib/libcmt.lib','crt_archive_sha256'),
                          ('UUID','.tools/msvc710/Vc7/PlatformSDK/Lib/Uuid.Lib','uuid_archive_sha256')]:
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
        # Reopen the original UUID section; SDK symbol spelling supplies no data.
        for r in m['foreign_guids']:
            q=r['record'];body=member(q,'UUID')
            raw,defs=coff.readonly_section(body,q['section'],c.coff_name)
            if (not contains(json.loads((ROOT/r['path']).read_text()),q) or len(raw)!=16
                    or digest(raw)!=q['source_sha256'] or defs!=q['definitions']
                    or raw!=c.pe_bytes_at(target,int(q['address'],16),len(raw))
                    or pe.image_permissions(target,int(q['address'],16),len(raw))!=0x40000000):
                raise ValueError('Presentation original foreign UUID whole section differs')
            assign(q['symbol'],int(q['address'],16))
        for r in m['alias_anchors']:
            q=r['record'];body=member(dict(q['record'],member_sha256=q['member_sha256']),'CRT')
            _,defs=coff.parse_symbols(body,c.coff_name)
            alias=module('presentation_alias','verify-sdk-file-image-origins.py')
            alias.verify_alias(defs,q['primary_symbol'],q['requested_symbol'])
            actual=[d for d in defs if d['symbol'] in (q['primary_symbol'],q['requested_symbol']) and d['section']>0]
            if (not contains(json.loads((ROOT/r['path']).read_text()),q) or actual!=q['alias_definitions']
                    or functions[q['address']]!=q['function'] or origins[q['address']]!=q['origin']
                    or q['fields'] or q['bindings'] or q['source_size']!=61
                    or catalog.get(q['primary_symbol'])!=int(q['address'],16)
                    or digest(anchor_raw[q['primary_symbol']][0])!=q['source_sha256']):
                raise ValueError('Presentation full retained primary/alias protocol differs')
            assign(q['requested_symbol'],catalog[q['primary_symbol']])
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
                if r['base'] in COMPILER:
                    destructor='??1CD3DXLockSurface@@QAE@XZ' if r['base']=='0x00605CDF' else '??1CD3DXLockVolume@@QAE@XZ'
                    check_array(linked,fields,flow,destructor,16 if r['base']=='0x00605CDF' else 4)
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



EVIDENCE = 'config/sdk-presentation-origin-evidence.json'
MANIFEST_SHA256 = '771ae0e2e563cdb35dfbaf46ed752a59f29f15ba6274badb88c621a28a1a4eb1'
KEYS = {'0x00604CE6': 623, '0x0061F45E': 321, '0x0061F59F': 1299, '0x006095FA': 215, '0x006073A5': 960, '0x00607F32': 1651, '0x0061F375': 186, '0x0060501F': 108, '0x00605CDF': 75, '0x00605D2A': 75, '0x00609162': 68}
COMPILER = {'0x00605CDF','0x00605D2A'}
PLAN_DIGESTS = {'sections': '242032640f849ee79c91e0cadbacb470e6d24ca5abf1496c716cc58ac547f0d3', 'anchors': '7d4095703d0afa18f313d7ecb5166c11bf23171edcf3fdad0e243a43900c1ea7', 'data_anchors': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'foreign_guids': '6f5e12af7f2d24e72d80afd3a9248fe6f5fb533b28a9e9e3065a8eb6acb1a4b5', 'alias_anchors': '8cc430d076ec30230e262ce2d4270397acf57c6a9832c412264d553011bfc169', 'interiors': '82be9cc57138e4f47c758f5e9a9c26e327b26d9bcf05972cf9b8bded2cb7d4c4', 'retained_unknown': '9f35bf46725f58dc85fa6e275beb870c484c35a0393e78a0c29ff824538456ab', 'policy_references': '66784480dc6e2a039ba41bfa96fb5fcbbc247ac2f8258324fded9bb9740824d6', 'public_control': '99189f428fa41a8ba0c8c72b364e4ee48fa52556533ebab58b2971d2f1e6bc83', 'absolute': '8e1f56739e02ad0900ff6fe1a81eecb7cfcf9597595512608c6e532445948d11', 'imports': 'ee0b3237f0b2feb7a969d79c9bdfe5da906e014414a96c4b7258f842a6b1af0c', 'weak_references': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'probe': '16bfe14069eae6a811520523832b62b9df45d057f24e8d0a9f5414b451672a16', 'profile': 'edbcdcf806e9869ccdd785e3c9e574a3734df2e10de3d8a70a694bb4a8e89307', 'headers': 'ea6cb00e0cd7986b212b6e6e1f220319d96b8ff32cb7c1faf5b4a474af61e00a', 'emission': '1a290b8f556201c105733da741889e1e6b6b8aed3422669eae6f858257cfcd92', 'layout': 'd0abe3567d07fd00f58b5b48314d56d6c8af186ae636c674dd8f7a2f1162427a', 'retained_sha256': '898ee4e85edd6fe756c6df1fdf218980c159515bc31867a60ca2afafac3156c8', 'game_parents': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'uuid_archive_sha256': '89cf9b03328ef4655c6df7206142964a22d95e8e823ad689d3d2e7ab792ad31b'}

if __name__=='__main__':
    raise SystemExit(main())
