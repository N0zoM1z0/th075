#!/usr/bin/env python3
"""Attest the installed TH075 compiler, linker, SDK, and analysis tools."""
from __future__ import annotations

import hashlib
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tomllib

ROOT = Path(__file__).resolve().parents[1]


def main() -> int:
    subprocess.run([sys.executable, str(ROOT / "scripts/verify-python-env.py")], check=True)
    locked = tomllib.loads((ROOT / "config/tools.lock.toml").read_text())
    for command in ("wine", "winepath", "git", "curl", "node", "npm", "flock"):
        if not shutil.which(command):
            raise ValueError("missing prerequisite: " + command)
    compiler_root = Path(os.environ.get("TH075_MSVC71_ROOT", ROOT / ".tools/msvc710"))
    for executable, kind in (("cl.exe", "compiler"), ("link.exe", "linker")):
        path = compiler_root / "Vc7/bin" / executable
        expected = locked["msvc71"][kind + "_sha256"]
        if hashlib.sha256(path.read_bytes()).hexdigest() != expected:
            raise ValueError("locked identity mismatch: " + executable)
        result = subprocess.run(["wine", str(path), "/?"], capture_output=True,
                                text=True, timeout=30, env={**os.environ, "WINEDEBUG": "-all"})
        if locked["msvc71"][kind + "_version"] not in result.stdout + result.stderr:
            raise ValueError("unexpected version banner: " + executable)
        print(kind.capitalize() + " OK: " + locked["msvc71"][kind + "_version"] + " (SHA-256 verified)")
    for filename, key in (("c1.dll", "c_frontend_sha256"), ("c1xx.dll", "cpp_frontend_sha256"),
                          ("c2.dll", "optimizer_sha256"), ("mspdb71.dll", "pdb_backend_sha256")):
        if hashlib.sha256((compiler_root / "Vc7/bin" / filename).read_bytes()).hexdigest() != locked["msvc71"][key]:
            raise ValueError("locked compiler component mismatch: " + filename)
    print("C/C++ frontends, optimizer, and PDB backend OK: four SHA-256 identities verified")
    for header in ("Windows.h", "d3d8.h", "d3dx8.h", "d3dx8core.h", "dinput.h"):
        if not (compiler_root / "Vc7/PlatformSDK/Include" / header).is_file():
            raise ValueError("missing Platform SDK header: " + header)
    print("Platform SDK OK: Win32, Direct3D8/D3DX8, DirectInput")
    bridge = ROOT / ".tools/mcp_for_gptweb-ghidra"
    commit = subprocess.check_output(["git", "-C", str(bridge), "rev-parse", "HEAD"], text=True).strip()
    if commit != locked["bash_ghidra_mcp"]["commit"] or not (bridge / "dist/index.js").is_file():
        raise ValueError("MCP bridge revision/build differs from the lock")
    print("Bash + Ghidra MCP OK: locked revision and built entry point")
    java = ROOT / ".tools/jdk/bin/java"
    result = subprocess.run([str(java), "-version"], capture_output=True, text=True, timeout=15)
    if locked["temurin_jdk"]["version"] not in result.stdout + result.stderr:
        raise ValueError("unexpected JDK version")
    properties = (ROOT / ".tools/ghidra/Ghidra/application.properties").read_text()
    if "application.version=" + locked["ghidra"]["version"] not in properties:
        raise ValueError("unexpected Ghidra version")
    if not (ROOT / ".tools/ghidra/support/analyzeHeadless").is_file():
        raise ValueError("Ghidra headless entry point missing")
    print("Ghidra/JDK OK: " + locked["ghidra"]["version"] + " / " + locked["temurin_jdk"]["version"])
    print("Tool preflight passed. Cold replay separately verifies compiler output and SDK emission.")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, ValueError, subprocess.SubprocessError) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
