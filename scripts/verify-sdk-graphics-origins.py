#!/usr/bin/env python3
"""Replay complete original shader, texture and render-surface SDK provenance."""
import argparse
import csv
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import tempfile
import capstone

ROOT = Path(__file__).resolve().parents[1]
EVIDENCE = 'config/sdk-graphics-origin-evidence.json'
MANIFEST_SHA256 = '922cd31ed6c986c5719c42d8a342b38b4ce0e0a722f11e3b6e42ed48e92a5998'
CONFIDENCE = 'whole-original-sdk-graphics-policy-with-complete-source-callees-data-eh-switches-and-public-abi'
KEYS = {'0x00604C82': 100, '0x0060508B': 124, '0x00605B61': 102,
        '0x0060E599': 1219, '0x00605AE8': 40, '0x0060E0E0': 1013,
        '0x0060C263': 310, '0x0061FD22': 232, '0x006057BE': 810,
        '0x0060D291': 1304, '0x0060D7A9': 2188, '0x006051B8': 36,
        '0x006052BF': 226, '0x0060CF9B': 169, '0x0060CAB0': 169,
        '0x0060CB59': 161, '0x0060CBFA': 929, '0x0060EB24': 144}
UNKNOWN = ['0x00609F58', '0x0060C12B', '0x0060C1D4', '0x0061FB37',
           '0x0061FBE7', '0x0061FD1A', '0x006200DA']


def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT/'scripts'/filename)
    result = importlib.util.module_from_spec(spec); spec.loader.exec_module(result)
    return result


def digest(raw):
    return hashlib.sha256(raw).hexdigest()


def contains(tree, record):
    if isinstance(tree, dict):
        return tree == record or any(contains(v, record) for v in tree.values())
    return isinstance(tree, list) and any(contains(v, record) for v in tree)


def check_probe(body, emission, flow):
    expected = {'ProbeDeviceTexture':[80], 'ProbeDeviceContext':[24,28,32,36],
                'ProbeDeviceFormat':[40], 'ProbeBufferData':[12], 'ProbeBufferSize':[16], 'ProbeRelease':[8]}
    api_symbols = {'ProbeAssemble':'_D3DXAssembleShader@24', 'ProbeRender':'_D3DXCreateRenderToSurface@28',
                   'ProbeTexture':'_D3DXCreateTexture@32', 'ProbeRequirements':'_D3DXCheckTextureRequirements@28'}
    observed = set()
    for r in emission:
        primary = [d for d in r['definitions'] if d['type']==32]
        if not primary:
            continue
        if len(primary)!=1 or primary[0]['offset']:
            raise ValueError('Graphics SDK natural ABI control has a partial function')
        name=primary[0]['symbol'].split('@@')[0][1:]; observed.add(name)
        h=struct.unpack_from('<8sIIIIIIHHI',body,20+(r['section']-1)*40)
        raw=body[h[4]:h[4]+h[3]]; ins=flow.instructions(raw,0,len(raw))
        calls=[i for i in ins if i.group(capstone.CS_GRP_CALL)]
        if name in expected:
            if any(i.operands[0].type!=capstone.x86.X86_OP_MEM or not i.operands[0].mem.base or i.operands[0].mem.index for i in calls) or [i.operands[0].mem.disp for i in calls]!=expected[name]:
                raise ValueError('Graphics SDK cold public COM slot order differs')
        elif name in api_symbols:
            if len(calls)!=1 or [f['symbol']['symbol'] for f in r['fields']]!=[api_symbols[name]]:
                raise ValueError('Graphics SDK cold public WINAPI declaration differs')
        elif name=='ProbeDynamicMute':
            if (len(calls)!=2 or calls[-1].operands[0].type!=capstone.x86.X86_OP_MEM
                    or calls[-1].operands[0].mem.base!=capstone.x86.X86_REG_EBP
                    or calls[-1].operands[0].mem.disp!=-4 or calls[-1].operands[0].mem.index
                    or '__imp__GetProcAddress@8' not in [f['symbol']['symbol'] for f in r['fields']]
                    or not any(i.mnemonic=='cmp' and i.op_str=='dword ptr [ebp - 4], 0' for i in ins)
                    or not any(i.mnemonic=='jne' and i.operands[0].imm==32 for i in ins)):
                raise ValueError('Graphics SDK cold guarded dynamic callback differs')
        else:
            raise ValueError('Graphics SDK unreviewed natural control')
    if observed != set(expected)|set(api_symbols)|{'ProbeDynamicMute'}:
        raise ValueError('Graphics SDK missing complete public ABI control')


def verify_plan(m):
    code = [r for r in m['sections'] if r['kind'] == 'code']
    if (m['evidence_id'] != 'R195' or len(m['functions']) != 18
            or {r['address']: r['code_size'] for r in m['functions']} != KEYS
            or m['retained_unknown'] != UNKNOWN or len(m['anchors']) != 27
            or [(k, len([r for r in m['sections'] if r['kind']==k]),
                 sum(r['size'] for r in m['sections'] if r['kind']==k)) for k in ['code','data','bss']]
            != [('code',30,10340),('data',66,4902),('bss',3,3044)]
            or sum(len(r.get('fields',[])) for r in m['sections']) != 511
            or len(m['imports']) != 8 or len(m['interiors']) != 15
            or len(m['game_parents']) != 5):
        raise ValueError('Graphics SDK bounded whole source graph differs')
    controls = {r['base']: r for r in code}
    for r in m['sections']:
        if r['kind']=='bss':
            continue
        if (len(r['fields'])!=len(r['bindings']) or r['source']['size']!=r['size']
                or any(any(b.get(k)!=v for k,v in f.items()) for f,b in zip(r['fields'],r['bindings']))):
            raise ValueError('Graphics SDK omitted or fabricated a genuine source field')
    for a,targets in {
            '0x00604C82':['0x0060C12B','0x0060E599','0x0060C1D4'],
            '0x0060508B':['0x0064159D','0x00609F58','0x00609AC2','0x006049D8'],
            '0x00605B61':['0x00605AE8']}.items():
        if [b['target_address'] for b in controls[a]['bindings']]!=targets:
            raise ValueError('Graphics SDK complete original gateway dependency differs')
    if controls['0x0060EB24']['flow']['tails'] != [dict(offset=137,slot='0x0068E254',runtime_callee='unknown')]:
        raise ValueError('Graphics SDK dynamic cache slot became a fixed callee')
    for r in m['functions']:
        old = r['original_function']; origin = r['original_origin']; control = controls[r['address']]
        if (old != control['function'] or origin != control['origin'] or origin['origin'] != 'unknown'
                or int(old['size']) != r['code_size'] or control['size'] != r['size']
                or old['status'] != 'unclassified' or old['owner'] or old['source_file']
                or old['calling_convention'] or old['signature'] or old['match_percent'] != '0.00'
                or r['accepted_function'] != dict(old, proposed_name=control['symbol'], module='D3DX8',
                    status='excluded', owner='library', evidence='R195', notes=r['notes'])
                or r['accepted_origin'] != dict(address=r['address'], origin='library', subsystem='D3DX8',
                    disposition='exclude', confidence=CONFIDENCE, evidence_id='R195')):
            raise ValueError('Graphics SDK scope/source/ABI/mapping/exact credit differs')
    if {r['base'] for r in code if r['origin'] and r['origin']['origin']=='unknown'} != set(KEYS)|set(UNKNOWN):
        raise ValueError('Graphics SDK retained lifetime/getter alternatives differ')
    for r in code:
        if r['flow']['whole_size'] != r['size'] or r['flow']['code_size']+r['flow']['table_size'] != r['size']:
            raise ValueError('Graphics SDK truncated code or source switch tables')
        if r['base'] in UNKNOWN and r['origin']['origin'] != 'unknown':
            raise ValueError('Graphics SDK compiler-versus-explicit alternative was accepted')
    if ({r['base']: r['flow']['table_size'] for r in code if r['flow']['table_size']}
            != {'0x0060E0E0':196,'0x0060D7A9':171}
            or m['layout'] != dict(section=3,offset=16,size=48,
                values=[212,60,88,92,96,16,12,16,4,3,2,32])
            or len(m['emission']) != 12 or len(m['headers']) != 85):
        raise ValueError('Graphics SDK whole switch/public ABI controls differ')


def replay(m, evidence_only=False):
    c = module('graphics_target','compare-coff-function.py'); coff = module('graphics_coff','coff_data.py')
    rt = module('graphics_archive','verify-runtime-origins.py'); sdk = module('graphics_sdk','verify-sdk-origins.py')
    extra = module('graphics_sections','sdk_x3d_carriers.py'); cr = module('graphics_bss','sdk_code_carriers.py')
    pe = module('graphics_pe','verify-sdk-x3d-origins.py'); binder = module('graphics_fields','verify-sdk-dispatch-origins.py')
    flow = module('graphics_flow','sdk_graphics_carriers.py'); api = module('graphics_api','verify-sdk-interface-origins.py')
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
            owner = dict(old,member_sha256=q['member_sha256']); body = member(owner,'CRT' if r.get('kind')=='CRT' else 'SDK')
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
                    old_bindings = [dict(f,target_address=d) for f,d in zip(fields,old['destinations'])]
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
        # Resolve scoped fields from their real original section/definition. Never
        # populate this catalog from observed native relocation destinations.
        for r in m['sections']:
            for f in r.get('fields',[]):
                key=pe.field_key(r['member_offset'],f); own=(r['member_offset'],f['symbol_section'])
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
            linked,calls,data=binder.bind(raw,fields,r['bindings'],catalog,r['member_offset'],a,data_image=r['kind']=='data')
            if linked!=c.pe_bytes_at(target,a,len(raw)) or digest(linked)!=r['body_sha256']:
                raise ValueError('Graphics SDK entire unmasked code/data comparison differs')
            if r['kind']=='code':
                primary=[d for d in r['source']['definitions'] if d['type']==32 and not d['offset']]
                roots=[0] if primary else sorted({f['symbol_offset']+f['addend'] for q in m['sections'] if q['member_offset']==r['member_offset'] for f in q.get('fields',[]) if f['symbol_section']==r['source']['section'] and f['symbol_type']==0 and f['symbol_storage']==6})
                if roots!=r['roots'] or flow.flow(linked,a,roots,fields,calls,data,r['switch'],0x68e254 if r['base']=='0x0060EB24' else None)!=r['flow']:
                    raise ValueError('Graphics SDK complete normal/EH/switch/indirect flow differs')
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


def retained_digest_matches(path,expected):
    """Keep original pins; allow only frozen R198 End source-replay upgrades."""
    actual=digest((ROOT/path).read_bytes())
    if actual==expected:return True
    allowed={'scripts/verify-sdk-interface-origins.py': ('57f9ded32b394ddff62911e474b269da98c90152fff9a79c2c0a170059f1464c', '75b3979be88b4d60a24a67adc971c161f00086e310b162de4bf2ce2ff0fe42ae'), 'scripts/verify-sdk-destructor-origins.py': ('f48e108a3017def56fb2b69b1e54e72a9d6930277a41806ba7d301d45a58168a', '514f7aa683dc63f072ec4b8c21359619268e9ea4b570afb205d467b35a28b1a9')}
    return allowed.get(path)==(expected,actual)


def main():
    parser=argparse.ArgumentParser(description=__doc__); parser.add_argument('--evidence-only',action='store_true')
    args=parser.parse_args(); m=json.loads((ROOT/EVIDENCE).read_text()); verify_plan(m)
    for path,sha in [(EVIDENCE,MANIFEST_SHA256),(m['probe'],m['probe_sha256']),*m['retained_sha256'].items()]:
        if not retained_digest_matches(path,sha):
            raise ValueError('Graphics SDK immutable source/evidence differs: '+path)
    for filename in ['verify-sdk-interface-origins.py','verify-sdk-debug-parent-origins.py',
                     'verify-sdk-destructor-origins.py','verify-sdk-cpu-eh-origins.py']:
        result=subprocess.run([str(ROOT/'scripts/repo-python'),'scripts/'+filename],cwd=ROOT,capture_output=True,text=True,check=True)
        print('retained '+filename+': '+result.stdout.strip().splitlines()[-1])
    replay(m,args.evidence_only)
    print('R195 origins OK:18 complete SDK library policies /9276 code bytes;whole sections9643 including full367 parser jump/selector bytes;30 code sections10340,66 initialized data4902,three BSS3044;all511 genuine fields,27 independently retained anchors,eight actual imports,five whole game parents;seven lifetime/getter candidates and prior15 interior compiler rows unchanged;11 whole cold public ABI controls454 and readonly64,85 headers;no source/private ABI/mapping/exact credit.')
    return 0


if __name__=='__main__':
    raise SystemExit(main())
