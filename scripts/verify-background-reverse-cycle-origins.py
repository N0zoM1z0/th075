#!/usr/bin/env python3
"""Replay complete BG05a reverse-cycle callback, independent game context and cold controls."""
import argparse
import csv
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]

def module(name, filename):
    spec = importlib.util.spec_from_file_location(name, ROOT/'scripts'/filename)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result

SOURCE = module('cycle_source', 'verify-vector-insertion-carrier-origins.py')
digest = SOURCE.digest
metadata_digest = SOURCE.BASE.metadata_digest
EVIDENCE = 'config/background-reverse-cycle-origin-evidence.json'
MANIFEST_SHA256 = 'b14741ea79891926aa530c1c731cab38766524086998fc778114907299f29b86'
PLAN_DIGESTS = {'evidence_id': 'cf0c865722374627ec49844963537d435c28c27405b14ff72035307876d7b19f', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'functions': '945717ecbe540288aedbab175ba9ed6fa208a0898292537ffa1612a50e6f86c6', 'contexts': '9445246fa7c0cab77e6ee103e26a209be3ee86da0425131269192594626f26bd', 'constants': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'boundaries': '8e18bd965cc13e8ad178f6eec7642cf70d282713ccc2b50b6d3df6f08f551c25', 'canonical': '940a38119a68253cc0e6370e515ecee844e8d1930b57082d1b76e285be6b8aa8', 'unselected_sha256': '5d6068e462b8ee779ee82062949c0198727182d15de25c51db0944ad2f8e5a1e', 'public_control': 'a50671f8154c59c662e8e67bf1d55aa354ac34f8dff467b5eaebe2c970d3b4c8', 'historical_snapshots': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'retained_sha256': '072dece1a83a4d54810968ae6511ea9e91327b3ca5f553e39569fe883e255370', 'interpretation': '4ec4d260bd6dc607a22d18446219097323e4bd7d3b1e9cbee3a13585efcb7876'}
WHOLE = {'0x0044E3A0': 45}
CONFIDENCE = 'whole-background-cycle-policy-and-independent-asset-callback-render-provenance'


def rows(name):
    with (ROOT/'config'/name).open() as source:
        return list(csv.DictReader(source))


def verify_plan(m):
    if set(m) != set(PLAN_DIGESTS):
        raise ValueError('Cycle immutable schema differs')
    for key, sha in PLAN_DIGESTS.items():
        if metadata_digest(m[key]) != sha:
            raise ValueError('Cycle immutable full evidence differs: '+key)
    if (m['evidence_id'] != 'R232' or {r['address']:r['size'] for r in m['functions']} != WHOLE
            or len(m['contexts']) != 1 or m['constants'] or m['historical_snapshots']
            or [r['value'] for r in m['constants']] != []
            or len(m['public_control']['methods']) != 2):
        raise ValueError('Cycle bounded whole native/source/context scope differs')
    mutable = {'proposed_name','module','owner','evidence','notes'}
    for r in m['functions']:
        old, new = r['original_function'], r['accepted_function']
        if (r['original_origin']['origin'] != 'unknown' or old['owner']
                or {k:v for k,v in old.items() if k not in mutable} != {k:v for k,v in new.items() if k not in mutable}
                or new['owner'] != 'authored' or new['status'] != 'unclassified' or new['match_percent'] != '0.00'
                or any(new[k] for k in ['source_file','signature','calling_convention'])
                or r['accepted_origin'] != dict(address=r['address'],origin='authored',subsystem='BackgroundStage',
                    disposition='authored',confidence=CONFIDENCE,evidence_id='R232')):
            raise ValueError('Cycle gains extent/source/private ABI/mapping/exact credit')


def normalized_policy(raw, address, flow, counter, frame, constants):
    """Compare every ordinary instruction with observed fields, without padding owners."""
    cap = flow.capstone
    x86 = cap.x86
    ins = flow.instructions(raw,address,len(raw))
    indices = {i.address:j for j,i in enumerate(ins)}
    normalized = []
    for i in ins:
        operands = []
        for o in i.operands:
            if o.type == x86.X86_OP_REG:
                operands.append(['reg',i.reg_name(o.reg)])
            elif o.type == x86.X86_OP_IMM:
                if i.group(cap.CS_GRP_JUMP):
                    if o.imm not in indices:
                        raise ValueError('Cycle has an external/shared branch or truncated comparison')
                    operands.append(['branch',indices[o.imm]])
                else:
                    operands.append(['imm',o.imm])
            elif o.type == x86.X86_OP_MEM:
                base, index = i.reg_name(o.mem.base), i.reg_name(o.mem.index)
                displacement = o.mem.disp
                if not base and not index:
                    if i.mnemonic != 'fcomp' or displacement not in constants:
                        raise ValueError('Cycle unknown absolute owner in ordinary policy')
                    operands.append(['constant-double',constants[displacement]])
                else:
                    if base not in ['ebp','esp'] and not index:
                        if displacement == counter: displacement = 'counter'
                        elif displacement == frame: displacement = 'frame'
                        else: raise ValueError('Cycle gains an unexplained receiver field')
                    operands.append(['mem',o.size,base,index,o.mem.scale,displacement])
            else: raise ValueError('Cycle unknown instruction operand')
        normalized.append([i.mnemonic,operands])
    return normalized


def receiver_uses(raw,address,flow):
    x86 = flow.capstone.x86
    return [dict(offset=i.address-address,mnemonic=i.mnemonic,operands=i.op_str)
            for i in flow.instructions(raw,address,len(raw))
            if any(o.type == x86.X86_OP_MEM and i.reg_name(o.mem.base) not in ['ebp','esp']
                   and o.mem.disp in [0x68,0x6c] for o in i.operands)]


def verify_native(m,target,c,flow):
    authored = module('cycle_authored','verify-authored-origins.py')
    background = module('cycle_background','verify-background-origins.py')
    permissions = module('cycle_permissions','verify-sdk-x3d-origins.py')
    old_authored = rows('authored-origin-evidence.csv')
    constants = {}
    for r in m['constants']:
        a = int(r['address'],16);raw = c.pe_bytes_at(target,a,8)
        if (digest(raw) != r['sha256'] or struct.unpack('<d',raw)[0] != r['value']
                or permissions.image_permissions(target,a,8) != 0x40000000):
            raise ValueError('Cycle loses complete independently readonly double owner')
        constants[a] = r['value']
    for r in m['functions']:
        a = int(r['address'],16); raw = c.pe_bytes_at(target,a,r['size'])
        if (digest(raw) != r['body_sha256'] or SOURCE.instructions(raw,a,flow) != r['instructions']
                or list(authored.verify_body(raw,a)) != r['cfg']
                or normalized_policy(raw,a,flow,0x68,0x6c,constants) != r['policy']):
            raise ValueError('Cycle complete native policy/CFG/RET differs')
    for ctx in m['contexts']:
        for owner in ctx['owners']:
            a = int(owner['address'],16);raw = c.pe_bytes_at(target,a,owner['size'])
            if (digest(raw) != owner['body_sha256'] or SOURCE.instructions(raw,a,flow) != owner['instructions']
                    or list(authored.verify_body(raw,a,owner['switches'],lambda x,n:c.pe_bytes_at(target,x,n),owner['direct_switches'])) != owner['cfg']
                    or (owner['authored_record'] is not None and owner['authored_record'] not in old_authored)):
                raise ValueError('Cycle crops/replaces complete independent game/table context')
        owners = {r['address']:r for r in ctx['owners']}
        ctor = owners[ctx['constructor']]; renderer = owners[ctx['renderer']]
        a = int(ctor['address'],16);raw = c.pe_bytes_at(target,a,ctor['size'])
        decoder = flow.capstone.Cs(flow.capstone.CS_ARCH_X86,flow.capstone.CS_MODE_32);decoder.detail=True
        if ctx['asset_witness'] not in background.rows('background-origin-evidence.csv'):
            raise ValueError('Cycle invents independent game asset provenance')
        background.verify_witness(ctx['asset_witness'],raw,target,c,decoder)
        table = ctx['table']; ta = int(table['address'],16);data = c.pe_bytes_at(target,ta,24)
        if (digest(data) != table['sha256'] or list(struct.unpack('<6I',data)) != table['words']
                or table['words'][1] != int(ctx['callback'],16) or table['words'][4] != int(ctx['renderer'],16)
                or permissions.image_permissions(target,ta,24) != 0x40000000
                or digest(c.pe_bytes_at(target,ta+24,8)) != table['following_sha256']):
            raise ValueError('Cycle loses actual six callback words or absorbs adjacent data')
        pairs = [(i['offset'],i['mnemonic'],i['operands']) for i in ctor['instructions']]
        if (46,'mov',f'dword ptr [eax], {hex(ta)}') not in pairs:
            raise ValueError('Cycle callback table is not installed by its full game constructor')
        if (130,'mov','dword ptr [ecx + 0x68], 0') not in pairs:
            raise ValueError('Cycle constructor does not clear its actual runtime field')
        if ctx['callback'] == '0x00450BD0' and (140,'mov','dword ptr [edx + 0x6c], 0') not in pairs:
            raise ValueError('Cycle paired policy lacks independent second-field initialization')
        a = int(renderer['address'],16);raw = c.pe_bytes_at(target,a,renderer['size'])
        observed = receiver_uses(raw,a,flow)
        if not observed or observed != ctx['counter_readers']:
            raise ValueError('Cycle loses real same-owner renderer field consumption')
    for r in m['boundaries']:
        raw = c.pe_bytes_at(target,int(r['address'],16),r['size'])
        if raw != b'\xcc'*r['size'] or raw.hex() != r['hex'] or digest(raw) != r['sha256']:
            raise ValueError('Cycle folds external alignment into its complete function extent')


def verify_control(m,body,c,coff,flow):
    extra = module('cycle_carriers','sdk_x3d_carriers.py')
    authored = module('cycle_cold_cfg','verify-authored-origins.py')
    inventory = module('cycle_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    control = m['public_control']
    if inventory(body,c,coff) != control['emission']:
        raise ValueError('Cycle loses whole ordinary code/data/field emission')
    for r in control['methods']:
        raw,fields,source = extra.section_carrier(body,r['source']['section'],c,coff)
        if (SOURCE.BASE.canonical_source(source,body) != r['source'] or fields != r['fields']
                or len(raw) != r['size'] or digest(raw) != r['sha256']
                or SOURCE.instructions(raw,0,flow) != r['instructions'] or list(authored.verify_body(raw,0)) != r['cfg']):
            raise ValueError('Cycle complete natural source/COFF/AUX/CFG differs')
        if r['role'] == 'ordinary-policy-alternative':
            constants = {}
            for f in fields:
                if f['type'] != 'DIR32' or f['symbol_section'] <= 0 or f['symbol_storage'] != 2 or f['symbol_offset'] != 0:
                    raise ValueError('Cycle cold double has no actual defining readonly owner')
                data,df,desc = extra.section_carrier(body,f['symbol_section'],c,coff)
                defs = [d for d in desc['definitions'] if d['symbol'] == f['symbol']]
                if df or len(data) != 8 or desc['flags'] & 0xe0000000 != 0x40000000 or len(defs) != 1:
                    raise ValueError('Cycle source double is not a complete original object definition')
                constants[struct.unpack_from('<I',raw,f['offset'])[0]] = struct.unpack('<d',data)[0]
            policy = normalized_policy(raw,0,flow,0,4,constants)
            if policy != r['policy']:
                raise ValueError('Cycle cold ordinary full instruction policy differs')
            positives = [q for q in m['functions'] if q['ordinary_symbol'] == r['symbol']]
            if not positives or any(q['policy'] != policy for q in positives):
                raise ValueError('Cycle ordinary policy differs beyond its documented compact-owner field positions')
            if any(q['size'] == len(raw) and q['body_sha256'] == digest(raw) for q in positives):
                raise ValueError('Cycle accidentally claims an exact compact private owner')
        elif r['role'] == 'implicit-copy-alternative':
            if fields or any(i['mnemonic'] in ['add','cmp','fcomp','test'] for i in r['instructions']) or r['cfg'][1]:
                raise ValueError('Cycle ordinary implicit copy becomes a conditional read-modify-reset callback')
        else: raise ValueError('Cycle unreviewed source role')
    data,_ = coff.readonly_section(body,control['layout_section'],c.coff_name)
    if len(data) != 12 or list(struct.unpack('<3I',data)) != [4,4,4]:
        raise ValueError('Cycle ordinary sizeof observations become a padded private game owner')


def verify_canonical(m,evidence_only=False):
    fs={r['address']:r for r in rows('functions.csv')}; origins={r['address']:r for r in rows('function-origins.csv')}
    selected={r['address']:r for r in m['functions']};state='original' if evidence_only else 'accepted'
    if evidence_only:
        for name in ['functions.csv','function-origins.csv']:
            if metadata_digest([r for r in rows(name) if r['address'] not in selected]) != m['unselected_sha256'][name]:
                raise ValueError('Cycle original transition changes unrelated rows')
    for pair in m['canonical']:
        a=pair['function']['address'];expected=pair
        if a in selected:expected=dict(function=selected[a][state+'_function'],origin=selected[a][state+'_origin'])
        if dict(function=fs[a],origin=origins[a]) != expected:
            raise ValueError('Cycle scoped canonical owner differs: '+a)


def replay(m,evidence_only=False):
    c=module('cycle_target','compare-coff-function.py');coff=module('cycle_coff','coff_data.py');flow=module('cycle_flow','sdk_image_carriers.py')
    target=c.verified_target()
    if digest(target) != m['target_sha256']:raise ValueError('Cycle target identity differs')
    for path,sha in m['retained_sha256'].items():
        if digest((ROOT/path).read_bytes()) != sha:raise ValueError('Cycle retained source/evidence differs: '+path)
    verify_canonical(m,evidence_only);verify_native(m,target,c,flow)
    control=m['public_control'];scratch=ROOT/'build/origin-background-reverse-cycle-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj=Path(temp)/'BackgroundReverseCycle.obj'
        result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/control['probe']),str(obj),*control['profile']],cwd=ROOT,capture_output=True,text=True)
        if result.returncode or SOURCE.HEADERS(result.stdout+result.stderr) != control['headers']:
            raise ValueError('Cycle cold compiler/header proof failed; no cached-object fallback')
        verify_control(m,obj.read_bytes(),c,coff,flow)


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true')
    args=parser.parse_args();m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes()) != MANIFEST_SHA256:raise ValueError('Cycle immutable manifest differs')
    replay(m,args.evidence_only)
    print('R232:whole BG05a reverse-cycle callback45; complete independent asset/table/render context and whole compact ordinary/implicit-copy controls; no source/private ABI/mapping/exact credit.')


if __name__ == '__main__': main()
