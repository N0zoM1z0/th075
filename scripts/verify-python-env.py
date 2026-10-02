#!/usr/bin/env python3
"""Verify the repository interpreter and decoder without consulting shell PATH."""
from __future__ import annotations

import hashlib
import importlib.util
from pathlib import Path
import sys
import tomllib

ROOT = Path(__file__).resolve().parents[1]


def main() -> int:
    locked = tomllib.loads((ROOT / "config/tools.lock.toml").read_text())
    expected = (locked["python"]["major"], locked["python"]["minor"])
    if sys.version_info[:2] != expected:
        raise ValueError("repository Python must be " + ".".join(map(str, expected)))
    if Path(sys.prefix).resolve() != (ROOT / ".tools/python").resolve():
        raise ValueError("interpreter is outside the repository virtual environment")
    spec = importlib.util.find_spec("capstone")
    if spec is None or not spec.origin:
        raise ValueError("Capstone missing; run scripts/bootstrap-python.sh")
    package = Path(spec.origin).parent.resolve()
    package.relative_to(Path(sys.prefix).resolve())
    paths = {"python_wrapper_sha256": "__init__.py", "x86_wrapper_sha256": "x86.py",
             "x86_constants_sha256": "x86_const.py", "native_library_sha256": "lib/libcapstone.so"}
    for key, filename in paths.items():
        digest = hashlib.sha256((package / filename).read_bytes()).hexdigest()
        if digest != locked["capstone"][key]:
            raise ValueError("locked Capstone identity mismatch: " + filename)
    import capstone
    if capstone.__version__ != locked["capstone"]["version"]:
        raise ValueError("unexpected Capstone version")
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    instruction = next(decoder.disasm(b"\xc3", 0x1000))
    if instruction.mnemonic != "ret" or instruction.size != 1:
        raise ValueError("Capstone native x86 decoder smoke check failed")
    print(f"Repository Python OK: {sys.version.split()[0]}; Capstone {capstone.__version__}, four SHA-256 identities verified.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, ValueError, StopIteration) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
