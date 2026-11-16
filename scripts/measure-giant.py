"""Build a giant research parent and measure how far it is from the original.

usage: scripts/repo-python scripts/measure-giant.py [ADDRESS ...]   (default: every parent)

Each parent in config/frontiers.toml is cold-built with its recorded flags, then its
slot-1 Advance is compared with the original instruction by instruction.
Reports instruction counts, mnemonic and width differences, and positions
whose register operands differ ("GPR debt"), with the first such position.
scripts/check-frontier.py ratchets the same parents byte by byte.
This is a diagnostic: exact credit still needs a complete replay unit.
"""
import importlib.util, re, struct, subprocess, sys, tempfile, tomllib
from pathlib import Path
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parent.parent
spec = importlib.util.spec_from_file_location('c', ROOT / 'scripts/compare-coff-function.py')
c = importlib.util.module_from_spec(spec); spec.loader.exec_module(c)

# Parents and their recorded flags live in config/frontiers.toml.
with (ROOT / 'config/frontiers.toml').open('rb') as stream:
    PARENTS = {e['address']: e for e in tomllib.load(stream)['frontiers'].values()}
REG = re.compile(r'\b(e?[abcd]x|[abcd][lh]|e?[sd]i)\b')


def advance_body(obj):
    d = obj.read_bytes(); _, nsec, _, sp, nsy, opt, _ = struct.unpack_from('<HHIIIHH', d, 0)
    strtab = d[sp + nsy * 18:]
    i = 0
    while i < nsy:
        r = d[sp + i * 18: sp + i * 18 + 18]
        if r[:4] == b'\0\0\0\0':
            o = struct.unpack_from('<I', r, 4)[0]; name = strtab[o:strtab.index(b'\0', o)].decode('latin-1')
        else:
            name = r[:8].rstrip(b'\0').decode('latin-1')
        value, sec, typ, storage, naux = struct.unpack_from('<IhHBB', r, 8)
        if name.startswith('?Advance@') and sec > 0 and storage == 2:
            h = d[20 + opt + (sec - 1) * 40: 20 + opt + sec * 40]
            size, ptr = struct.unpack_from('<II', h, 16)
            return d[ptr:ptr + size]
        i += 1 + naux
    raise SystemExit(f'{obj}: no Advance definition')


def measure(addr):
    e = PARENTS[addr]
    size, char, kind = e['size'], e['character'], e['kind']
    with tempfile.TemporaryDirectory(dir=ROOT / 'build') as tmp:
        obj = Path(tmp) / 'parent.obj'
        p = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), e['source'], str(obj), *e['flags']],
                           cwd=ROOT, capture_output=True, text=True)
        if p.returncode or not obj.exists():
            return f'{addr:08X} {char} {kind}: BUILD FAILED\n{p.stdout[-800:]}{p.stderr[-800:]}'
        body = advance_body(obj)
    dis = Cs(CS_ARCH_X86, CS_MODE_32)
    orig = list(dis.disasm(c.pe_bytes_at(c.verified_target(), addr, size), addr))
    mine = list(dis.disasm(body, addr))
    pairs = list(zip(orig, mine))
    mn = sum(a.mnemonic != b.mnemonic for a, b in pairs)
    width = sum(a.size != b.size for a, b in pairs)
    gpr = [k for k, (a, b) in enumerate(pairs) if a.mnemonic == b.mnemonic and REG.findall(a.op_str) != REG.findall(b.op_str)]
    first = f' first {orig[gpr[0]].address:08X} (#{gpr[0]})' if gpr else ''
    return (f'{addr:08X} {char:9} {kind:7} {size:6}B (section {len(body)}B) | insns {len(orig)}/{len(mine)} '
            f'| mnemonic {mn} | width {width} | GPR {len(gpr)}{first}')


for a in [int(x, 16) for x in sys.argv[1:]] or sorted(PARENTS):
    print(measure(a), flush=True)
