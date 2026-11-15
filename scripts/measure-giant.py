"""Build a giant research parent and measure how far it is from the original.

usage: scripts/repo-python scripts/measure-giant.py [ADDRESS ...]   (default: every parent)

Each parent is cold-built from probes/ with its recorded flags, then its
slot-1 Advance is compared with the original instruction by instruction.
Reports instruction counts, mnemonic and width differences, and positions
whose register operands differ ("GPR debt"), with the first such position.
This is a diagnostic: exact credit still needs a complete replay unit.
"""
import importlib.util, re, struct, subprocess, sys, tempfile
from pathlib import Path
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parent.parent
spec = importlib.util.spec_from_file_location('c', ROOT / 'scripts/compare-coff-function.py')
c = importlib.util.module_from_spec(spec); spec.loader.exec_module(c)

BASE = ['/Od', '/Ob0', '/Gy', '/GR-', '/GX-', '/GS', '/Zi', '/I', 'src', '/I', 'probes']
# original address: (size, character, kind, research source, flags)
PARENTS = {
    0x0045DD70: (60999, 'Reimu', 'fighter', 'FighterWhole0045DD70F1183.cpp', BASE),
    0x004AC040: (82796, 'Sakuya', 'fighter', 'FighterWhole004AC040F1020.cpp',
                 [f if f != '/GX-' else '/GX' for f in BASE]),
    0x005214B0: (46755, 'Youmu', 'fighter', 'FighterWhole005214B0F1040.cpp', BASE),
    0x00543210: (58294, 'Remilia', 'fighter', 'FighterWhole00543210F1041.cpp', BASE),
    0x004EBDA0: (33293, 'Alice', 'object', 'CharacterObjectActionsF572.cpp', BASE),
    0x0050A580: (81539, 'Patchouli', 'object', 'CharacterObjectWhole0050A580F1044.cpp', BASE),
    0x00536400: (39999, 'Youmu', 'object', 'CharacterObjectActions00536400F1211.cpp', BASE),
    0x0055AC80: (28432, 'Remilia', 'object', 'CharacterObjectWhole0055AC80F1194.cpp', BASE),
    0x0057D580: (43845, 'Yuyuko', 'object', 'CharacterObjectActions0057D580F1237.cpp', BASE),
    0x005A1600: (43599, 'Yukari', 'object', 'CharacterObjectActions005A1600F1231.cpp', BASE),
    0x005C9CC0: (43501, 'Suika', 'object', 'CharacterObjectActions005C9CC0F1216.cpp', BASE),
    0x004CA6E0: (42511, 'Sakuya', 'object', 'CharacterObjectActions004CA6E0F1222.cpp', BASE),
    0x005EB520: (34434, 'Meiling', 'object', 'CharacterObjectWhole005EB520F1207.cpp',
                 [f for f in BASE if f not in ('/GS',)]),
}
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
    size, char, kind, src, flags = PARENTS[addr]
    with tempfile.TemporaryDirectory(dir=ROOT / 'build') as tmp:
        obj = Path(tmp) / 'parent.obj'
        p = subprocess.run([str(ROOT / 'scripts/compile-probe.sh'), f'probes/{src}', str(obj), *flags],
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
