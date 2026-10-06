#!/usr/bin/env python3
"""Replay one scene-value setter, its complete independent consumer and cold type alternatives."""
import argparse
import csv
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import tempfile

ROOT=Path(__file__).resolve().parents[1]
def module(name,filename):
    spec=importlib.util.spec_from_file_location(name,ROOT/'scripts'/filename)
    result=importlib.util.module_from_spec(spec);spec.loader.exec_module(result);return result
SOURCE=module('shared_source','verify-vector-insertion-carrier-origins.py')
digest=SOURCE.digest
metadata_digest=SOURCE.BASE.metadata_digest
EVIDENCE='config/scene-shared-value-origin-evidence.json'
MANIFEST_SHA256='d6d0f4579f374515459d797980f94ff2a8f3d5d868f7c36a396b769f1d5a23fe'
PLAN_DIGESTS={'evidence_id': '26efbaf3cc837a8fe7ed68acedfc7772e00a592157da4e9eb58b6358f62bc811', 'target_sha256': '543d63ac4cd7fcf9a8d1e4a2b2c92e45ae8d1b6f8d3500aea0cb88f5562196ab', 'functions': '3549f65b788cd87e70ff70e7b929b9db2c2cad2540719022a041d4e7049a45c5', 'held': '24d4e8fc1f79b9d13525bbfd50c8947d74d8676203fa0b32d80ac5e59e5f6233', 'parent': '7d42f3c01fc52662ccb7b2f6186bb941051fe19c3e13432e3b73ca2eaa446a23', 'data': '78a4acf47513e72d33d86ecce707636646cc6be1c3e7dac62c3e16cbfee4333a', 'boundaries': 'cf1ba58e025b0e0d0ae34da33dabacb2ddd4ed493d9dd552b5d9b412d6104d30', 'canonical': '4419cce3f3aa04512ff7eabe317e2214d561431a392052da8a32303be9ea6635', 'unselected_sha256': '024236a1a7925ee952c71850510241a4c204367f2088f68fce1d78eb61fe17a9', 'public_control': 'f3e088c9c218ae16c7e11455a923203f1a2af82c61fcebad4dc59f436f9491a6', 'historical_snapshots': '4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945', 'retained_sha256': '5af497e61aa050ca741cccb41048f9050aa6f68fcea7afb8074d105703eaaa7d', 'interpretation': 'f86e9b93674dfa3687d3b4d7b62026ce97877c5f1f701258d1717dbeb7962e01'}
WHOLE={'0x004557E0':21}
CONFIDENCE='whole-shared-scene-value-store-and-independent-complete-game-decay-policy'


def rows(name):
    with (ROOT/'config'/name).open() as source:return list(csv.DictReader(source))


def verify_plan(m):
    if set(m)!=set(PLAN_DIGESTS):raise ValueError('Scene value immutable schema differs')
    for key,sha in PLAN_DIGESTS.items():
        if metadata_digest(m[key])!=sha:raise ValueError('Scene value complete immutable evidence differs: '+key)
    if (m['evidence_id']!='R233' or {r['address']:r['size'] for r in m['functions']}!=WHOLE
            or m['parent']['address']!='0x0043B610' or m['parent']['size']!=4764
            or len(m['parent']['direct_switches'])!=1 or m['historical_snapshots']
            or len(m['held'])!=2 or len(m['public_control']['methods'])!=3):
        raise ValueError('Scene value bounded whole native/context/alternative scope differs')
    r=m['functions'][0];old,new=r['original_function'],r['accepted_function']
    mutable={'proposed_name','module','owner','evidence','notes'}
    if (r['original_origin']['origin']!='unknown' or old['owner']
            or {k:v for k,v in old.items() if k not in mutable}!={k:v for k,v in new.items() if k not in mutable}
            or new['owner']!='authored' or new['status']!='unclassified' or new['match_percent']!='0.00'
            or any(new[k] for k in ['source_file','signature','calling_convention'])
            or r['accepted_origin']!=dict(address=r['address'],origin='authored',subsystem='BattleScene',
                disposition='authored',confidence=CONFIDENCE,evidence_id='R233')):
        raise ValueError('Scene value gains extent/source/private ABI/mapping/exact credit')
    if any(r['origin']['origin']!='unknown' or r['function']['owner'] for r in m['held']):
        raise ValueError('Scene value assigns an unrelated receiver-only policy without ownership evidence')


def verify_canonical(m,evidence_only=False):
    fs={r['address']:r for r in rows('functions.csv')};origins={r['address']:r for r in rows('function-origins.csv')}
    selected=m['functions'][0];state='original' if evidence_only else 'accepted'
    if evidence_only:
        for name in ['functions.csv','function-origins.csv']:
            if metadata_digest([r for r in rows(name) if r['address'] not in WHOLE])!=m['unselected_sha256'][name]:
                raise ValueError('Scene value original transition changes unrelated records')
    for pair in m['canonical']:
        a=pair['function']['address'];expected=pair
        if a==selected['address']:expected=dict(function=selected[state+'_function'],origin=selected[state+'_origin'])
        if dict(function=fs[a],origin=origins[a])!=expected:raise ValueError('Scene value scoped canonical owner differs: '+a)


def consumer_address(instructions):
    """The independent game's complete consumer/writer establishes this data owner."""
    stores=[i for i in instructions if i['mnemonic']=='fstp' and i['offset']==4400]
    if len(stores)!=1 or stores[0]['operands']!='dword ptr [0x671628]':
        raise ValueError('Scene value has no independently identified native writable owner')
    required={4369:('fld','dword ptr [0x671628]'),4375:('fcomp','dword ptr [0x65782c]'),
              4383:('test','ah, 0x41'),4388:('fld','dword ptr [0x671628]'),
              4394:('fsub','dword ptr [0x658044]'),4406:('fld','dword ptr [0x671628]'),
              4412:('fcomp','dword ptr [0x65782c]'),4420:('test','ah, 5'),
              4423:('jp','0x43c763'),4425:('mov','dword ptr [0x671628], 0')}
    by={i['offset']:(i['mnemonic'],i['operands']) for i in instructions}
    if any(by.get(at)!=pair for at,pair in required.items()):
        raise ValueError('Scene value loses ordered decay, negative clamp or unordered behavior')
    return 0x671628


def verify_native(m,target,c,flow):
    auth=module('shared_authored','verify-authored-origins.py');permissions=module('shared_permissions','verify-sdk-x3d-origins.py')
    for r in m['functions']+m['held']:
        a=int(r['address'],16);raw=c.pe_bytes_at(target,a,r['size'])
        if (digest(raw)!=r['body_sha256'] or SOURCE.instructions(raw,a,flow)!=r['instructions']
                or list(auth.verify_body(raw,a))!=r['cfg']):raise ValueError('Scene value selected/protected whole native body or CFG differs')
    p=m['parent'];a=int(p['address'],16);raw=c.pe_bytes_at(target,a,p['size'])
    if (p['authored_record'] not in rows('authored-origin-evidence.csv')
            or p['switches']!=[r for r in rows('authored-origin-switches.csv') if r['address']==p['address']]
            or p['direct_switches']!=[r for r in rows('authored-origin-direct-switches.csv') if r['address']==p['address']]
            or digest(raw)!=p['body_sha256'] or SOURCE.instructions(raw,a,flow)!=p['instructions']
            or list(auth.verify_body(raw,a,p['switches'],lambda x,n:c.pe_bytes_at(target,x,n),p['direct_switches']))!=p['cfg']):
        raise ValueError('Scene value crops/replaces the complete independent game state/guarded-switch owner')
    for table in p['tables']:
        raw=c.pe_bytes_at(target,int(table['address'],16),table['size'])
        if digest(raw)!=table['sha256'] or list(struct.unpack('<15I',raw))!=table['words']:
            raise ValueError('Scene value loses the full original guarded state jump table')
    owner=consumer_address(p['instructions'])
    r=m['functions'][0];pairs=[(i['mnemonic'],i['operands']) for i in r['instructions']]
    if pairs!=[('push','ebp'),('mov','ebp, esp'),('push','ecx'),('mov','dword ptr [ebp - 4], ecx'),
              ('mov','eax, dword ptr [ebp + 8]'),('mov',f'dword ptr [{hex(owner)}], eax'),
              ('mov','esp, ebp'),('pop','ebp'),('ret','4')]:
        raise ValueError('Scene value setter gains a private receiver field or loses the full RET4 word store')
    for r in m['data']:
        a=int(r['address'],16);raw=c.pe_bytes_at(target,a,4)
        if digest(raw)!=r['sha256'] or permissions.image_permissions(target,a,4)!=r['permissions']:
            raise ValueError('Scene value complete independent data extent/permissions differ')
        if 'value' in r and struct.unpack('<f',raw)[0]!=r['value']:
            raise ValueError('Scene value replaces the original full float threshold/step')
    for b in m['boundaries']:
        raw=c.pe_bytes_at(target,int(b['address'],16),b['size'])
        if raw!=b'\xcc'*b['size'] or digest(raw)!=b['sha256'] or raw.hex()!=b['hex']:
            raise ValueError('Scene value includes external alignment in a selected full extent')


def verify_control(m,body,target,c,coff,flow):
    extra=module('shared_carriers','sdk_x3d_carriers.py');auth=module('shared_cold_cfg','verify-authored-origins.py')
    inventory=module('shared_inventory','verify-sdk-dependency-origins.py').PAIRED.BUFFER.inventory
    ctl=m['public_control']
    if inventory(body,c,coff)!=ctl['emission']:raise ValueError('Scene value omits whole ordinary code/data/field emission')
    owner=consumer_address(m['parent']['instructions']);root=m['functions'][0];native=c.pe_bytes_at(target,int(root['address'],16),root['size'])
    linked_controls=[]
    for r in ctl['methods']:
        raw,fields,source=extra.section_carrier(body,r['source']['section'],c,coff)
        if (SOURCE.BASE.canonical_source(source,body)!=r['source'] or fields!=r['fields']
                or len(raw)!=r['size'] or digest(raw)!=r['sha256'] or SOURCE.instructions(raw,0,flow)!=r['instructions']
                or list(auth.verify_body(raw,0))!=r['cfg']):raise ValueError('Scene value whole natural source/COFF/AUX/CFG differs')
        if r['role'] in ['word-type-alternative','float-type-alternative']:
            expected='?ObservedSharedWord@@3IA' if r['role']=='word-type-alternative' else '?ObservedSharedFloat@@3MA'
            if (len(fields)!=1 or fields[0]['symbol']!=expected or fields[0]['offset']!=11
                    or fields[0]['type']!='DIR32' or fields[0]['addend']!=0
                    or fields[0]['symbol_storage']!=2 or fields[0]['symbol_section']!=0):
                raise ValueError('Scene value alternative lacks its complete actual external word/float data field')
            linked=bytearray(raw);struct.pack_into('<I',linked,fields[0]['offset'],owner)
            if len(linked)!=21 or linked!=native or not r['whole_native_byte_equal']:
                raise ValueError('Scene value whole unmasked alternative/native comparison differs')
            if flow.flow(linked,int(root['address'],16),[0],fields,{},
                         {int(root['address'],16)+11:owner})!=r['linked_flow']:
                raise ValueError('Scene value full ordinary source/data/RET4 flow differs')
            linked_controls.append(linked)
        elif r['role']=='implicit-copy-alternative':
            if fields or any('0x671628' in i['operands'] for i in r['instructions']):
                raise ValueError('Scene value compiler copy alternative writes an unrelated shared static value')
        else:raise ValueError('Scene value unknown ordinary role')
    if len(linked_controls)!=2 or linked_controls[0]!=linked_controls[1]:
        raise ValueError('Scene value promotes one source type from byte-equal alternatives')
    raw,_=coff.readonly_section(body,ctl['layout_section'],c.coff_name)
    if len(raw)!=12 or list(struct.unpack('<3I',raw))!=[1,4,4]:
        raise ValueError('Scene value compact observation becomes a padded private owner')


def replay(m,evidence_only=False):
    c=module('shared_target','compare-coff-function.py');coff=module('shared_coff','coff_data.py');flow=module('shared_flow','sdk_image_carriers.py')
    target=c.verified_target()
    if digest(target)!=m['target_sha256']:raise ValueError('Scene value target identity differs')
    for path,sha in m['retained_sha256'].items():
        if digest((ROOT/path).read_bytes())!=sha:raise ValueError('Scene value changes retained input: '+path)
    verify_canonical(m,evidence_only);verify_native(m,target,c,flow)
    ctl=m['public_control'];scratch=ROOT/'build/origin-scene-shared-value-verification';scratch.mkdir(parents=True,exist_ok=True)
    with tempfile.TemporaryDirectory(dir=scratch) as temp:
        obj=Path(temp)/'SceneSharedValue.obj'
        result=subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/ctl['probe']),str(obj),*ctl['profile']],cwd=ROOT,capture_output=True,text=True)
        if result.returncode or SOURCE.HEADERS(result.stdout+result.stderr)!=ctl['headers']:
            raise ValueError('Scene value cold compiler/header proof failed; no cached-object fallback')
        verify_control(m,obj.read_bytes(),target,c,coff,flow)


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--evidence-only',action='store_true');args=parser.parse_args()
    m=json.loads((ROOT/EVIDENCE).read_text());verify_plan(m)
    if digest((ROOT/EVIDENCE).read_bytes())!=MANIFEST_SHA256:raise ValueError('Scene value immutable manifest differs')
    replay(m,args.evidence_only)
    print('R233:whole scene-value store21; independent full game state4764 and guarded table60; two whole byte-equal word/float alternatives and implicit copy; two receiver policies stay unknown; no source/private ABI/mapping/exact credit.')


if __name__=='__main__':main()
