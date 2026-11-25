#!/usr/bin/env python3
"""Build TH075 comparison objects, a COFF library, or a Windows executable."""

from __future__ import annotations

import argparse
from collections import defaultdict
import fcntl
import hashlib
import os
from pathlib import Path
import runpy
import shutil
import struct
import subprocess
import sys
from tempfile import TemporaryDirectory
import tomllib


ROOT = Path(__file__).resolve().parents[1]
MANIFEST = ROOT / "config" / "match-units.toml"
TARGET = ROOT / "config" / "target.toml"
PROGRAM = Path("build/program")
# Read-only link data supplied by the pinned PE. Match units record the
# consumers and decorated names, including names that alias one address.
PROGRAM_DATA = {
    0x00657D98, 0x00657DE4, 0x00657E18, 0x00657E70, 0x00657EBC,
    0x00657EDC, 0x00657EFC, 0x00659080, 0x00659088, 0x00659098,
    0x0065909C, 0x00659274, 0x0065928C, 0x00659298, 0x006593F8,
    0x00659414, 0x00659418, 0x00659430, 0x00659438, 0x00659464,
    0x00659468, 0x0065946C, 0x00659478, 0x0065947C, 0x00659480,
    0x00659484, 0x0065948C, 0x00659494, 0x00659498, 0x00659740,
    0x00659748, 0x006598A0, 0x006598A4, 0x006598A8, 0x006598B4,
    0x006598BC, 0x00659920, 0x00659928, 0x00659A14, 0x00659A20,
    0x00659A24, 0x00659A28, 0x00659A2C, 0x00659CA4, 0x00659CAC,
    0x00659E14, 0x00659F3C,
}


def load() -> dict[str, object]:
    with TARGET.open("rb") as stream:
        target = tomllib.load(stream)["target"]
    with MANIFEST.open("rb") as stream:
        manifest = tomllib.load(stream)
    if manifest.get("schema_version") != 1:
        raise ValueError("match-units.toml must use schema_version = 1")
    if str(manifest.get("target_sha256", "")).lower() != str(target["sha256"]).lower():
        raise ValueError("match-unit target hash differs from config/target.toml")
    units = manifest.get("units")
    if not isinstance(units, dict):
        raise ValueError("match-units.toml [units] must be a table")
    for name, raw_unit in units.items():
        if not isinstance(raw_unit, dict):
            raise ValueError(f"unit {name!r} must be a table")
        for field in ("source", "object", "profile", "functions"):
            if field not in raw_unit:
                raise ValueError(f"unit {name!r} lacks {field}")
        source = ROOT / str(raw_unit["source"])
        if not source.is_file():
            raise ValueError(f"unit {name!r} source does not exist: {source}")
        output = (ROOT / str(raw_unit["object"])).resolve()
        output.relative_to((ROOT / "build").resolve())
        if not isinstance(raw_unit["functions"], list) or not raw_unit["functions"]:
            raise ValueError(f"unit {name!r} must contain functions")
    return manifest


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument("--check", action="store_true")
    group.add_argument("--object-name")
    group.add_argument("--unit")
    group.add_argument("--batch-unit", action="append", help="build selected comparison objects in profile groups")
    group.add_argument("--library", action="store_true", help="archive all configured translation units")
    group.add_argument("--program", action="store_true", help="build the library and link a Windows executable")
    return parser.parse_args()


def verify_target() -> None:
    subprocess.run(
        [str(ROOT / "scripts/repo-python"), str(ROOT / "scripts/verify-target.py")],
        cwd=ROOT, check=True,
    )


def compiler_profile(name, unit):
    profile = unit["profile"]
    if not isinstance(profile, list) or not profile or not all(isinstance(flag, str) for flag in profile):
        raise ValueError(f"unit {name!r} has an invalid compiler profile")
    return profile


def program_sources(units):
    profiles = {}
    for name, unit in units.items():
        source = Path(unit["source"])
        profile = tuple(compiler_profile(name, unit))
        if source in profiles and profiles[source] != profile:
            raise ValueError(f"conflicting compiler profiles for {source} ({name})")
        profiles[source] = profile
    if len({source.stem.casefold() for source in profiles}) != len(profiles):
        raise ValueError("translation units collide on a Windows object filename")
    return profiles


def write_program_data(units, destination: Path) -> None:
    """Provide the remaining external data from the user's original image."""
    symbols_at = defaultdict(set)
    for unit in units.values():
        for relocation in unit.get("relocations", []):
            address = relocation.get("target")
            if address in PROGRAM_DATA and relocation["type"] == "DIR32":
                symbols_at[address].add(relocation["symbol"])
    if PROGRAM_DATA - symbols_at.keys():
        raise ValueError("program data address missing from match-unit relocations")

    compare = runpy.run_path(str(ROOT / "scripts/compare-coff-function.py"))
    original = compare["verified_target"]()
    read = compare["pe_bytes_at"]
    data = bytearray()
    symbols = bytearray()
    strings = bytearray(4)
    seen = set()
    for address, names in sorted(symbols_at.items()):
        sizes = []
        for name in sorted(names):
            decorated_type = name.rsplit("@@", 1)[-1]
            if decorated_type == "3QBDB":
                window = read(original, address, 128)
                sizes.append(window.index(b"\0") + 1)
            elif decorated_type in ("3MA", "3MB", "3NB"):
                sizes.append(8 if decorated_type == "3NB" else 4)
            else:
                raise ValueError(f"unsupported program data symbol {name}")
        if len(set(sizes)) != 1 or seen.intersection(names):
            raise ValueError(f"conflicting program data symbols at {address:#x}")
        seen.update(names)

        # All names for the same native address must share one COFF offset.
        data.extend(bytes(-len(data) % 8))
        for name in sorted(names):
            # Long symbol name, section 1, null type, external storage class.
            symbols.extend(struct.pack("<IIIhHBB", 0, len(strings), len(data), 1, 0, 2, 0))
            strings.extend(name.encode("ascii") + b"\0")
        data.extend(read(original, address, sizes[0]))

    # i386 COFF, one aligned, initialized read-only section and no relocations.
    raw_offset = 20 + 40
    header = struct.pack("<HHIIIHH", 0x014C, 1, 0, raw_offset + len(data), len(seen), 0, 0)
    section = struct.pack("<8s6IHHI", b".rdata", 0, 0, len(data), raw_offset, 0, 0, 0, 0, 0x40400040)
    struct.pack_into("<I", strings, 0, len(strings))
    destination.write_bytes(header + section + data + symbols + strings)


def build_program(units, link_program: bool, *, comparison_batch=False) -> None:
    sources = program_sources(units)
    groups = defaultdict(list)
    for source, profile in sorted(sources.items()):
        groups[profile].append(source)

    tools = Path(os.environ.get("TH075_MSVC71_ROOT", ROOT / ".tools/msvc710")).resolve() / "Vc7"
    locked = tomllib.loads((ROOT / "config/tools.lock.toml").read_text())["msvc71"]
    for filename, key in (
        ("cl.exe", "compiler_sha256"), ("link.exe", "linker_sha256"),
        ("c1.dll", "c_frontend_sha256"), ("c1xx.dll", "cpp_frontend_sha256"),
        ("c2.dll", "optimizer_sha256"), ("mspdb71.dll", "pdb_backend_sha256"),
    ):
        if hashlib.sha256((tools / "bin" / filename).read_bytes()).hexdigest() != locked[key]:
            raise ValueError(f"locked identity mismatch: {filename}")

    env = os.environ.copy()
    for name in ("DISPLAY", "WAYLAND_DISPLAY", "WINEPREFIX", "WINEARCH", "CL", "_CL_", "LINK", "_LINK_"):
        env.pop(name, None)
    env.update(WINEDEBUG="-all", WINEDLLOVERRIDES=(
        "winex11.drv,winewayland.drv,winemac.drv=d;winemenubuilder.exe=d"
    ))
    runtime = [sys.executable, str(ROOT / "scripts/shared_runtime.py")]
    output_dir = Path("build/replay-batch") if comparison_batch else PROGRAM
    object_dir = output_dir / "obj"
    objects = [object_dir / (source.stem + ".obj") for source in sorted(sources)]
    matching = {}
    if comparison_batch:
        for unit in units.values():
            output = (ROOT / unit["object"]).resolve()
            obj = object_dir / (Path(unit["source"]).stem + ".obj")
            if matching.setdefault(output, obj) != obj:
                raise ValueError(f"conflicting comparison object destinations: {output}")
    library = PROGRAM / "th075.lib"
    executable = PROGRAM / "th075.exe"
    link_map = PROGRAM / "th075.map"
    program_data = PROGRAM / "supplied-data.obj"
    lock_dir = ROOT / ".analysis/locks"
    lock_dir.mkdir(parents=True, exist_ok=True)

    def wine_path(path):
        return subprocess.check_output(
            [*runtime, "winepath", "--", "-w", str(path)], cwd=ROOT, env=env, text=True,
        ).strip()

    def run(tool, args, log):
        with (ROOT / log).open("ab") as output:
            result = subprocess.run(
                [*runtime, "wine", "--", str(tools / "bin" / tool), *args],
                cwd=ROOT, env=env, stdout=output, stderr=subprocess.STDOUT,
            )
        if result.returncode:
            raise ValueError(f"{tool} exited with status {result.returncode}. See {log}")

    def response(name, options, inputs):
        path = output_dir / name
        # Keep two-token switches such as /I src on one response-file line.
        lines = [subprocess.list2cmdline(options)]
        lines.extend(subprocess.list2cmdline([str(p).replace("/", "\\")]) for p in inputs)
        (ROOT / path).write_bytes(("\r\n".join(lines) + "\r\n").encode("ascii"))
        return "@" + path.as_posix()

    with (lock_dir / "compiler.lock").open("a") as gate:
        fcntl.flock(gate, fcntl.LOCK_EX)
        (ROOT / object_dir).mkdir(parents=True, exist_ok=True)
        vc_win = wine_path(tools)
        env["INCLUDE"] = rf"{vc_win}\include;{vc_win}\PlatformSDK\Include"
        env["LIB"] = rf"{vc_win}\lib;{vc_win}\PlatformSDK\Lib"
        logs = [output_dir / f"{stage}.log" for stage in ("compile", "library", "link")]
        compile_log, library_log, link_log = logs
        outputs = [compile_log, *objects]
        if not comparison_batch:
            outputs.extend([library, library_log, program_data])
        if link_program:
            outputs.extend([executable, link_map, link_log])
        for path in outputs:
            (ROOT / path).unlink(missing_ok=True)
        with TemporaryDirectory(prefix="vc7-", dir=ROOT / output_dir) as scratch:
            env["TMP"] = env["TEMP"] = wine_path(scratch)
            for index, (profile, inputs) in enumerate(groups.items()):
                pdb = output_dir / f"profile-{index}.pdb"
                (ROOT / pdb).unlink(missing_ok=True)
                args = ["/nologo", "/c", *profile, f"/Fo{object_dir}/", f"/Fd{pdb}"]
                print(f"Compiling {len(inputs)} translation units. See {compile_log}", flush=True)
                run("cl.exe", [response(f"profile-{index}.rsp", args, inputs)], compile_log)
            del env["TMP"], env["TEMP"]
        for obj in objects:
            if not (ROOT / obj).is_file():
                raise ValueError(f"compiler did not produce {obj}")
        if comparison_batch:
            for destination, obj in matching.items():
                destination.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(ROOT / obj, destination)
            print(f"Built {len(objects)} comparison objects in {len(groups)} compiler groups", flush=True)
            return
        write_program_data(units, ROOT / program_data)
        objects.append(program_data)
        args = ["/nologo", f"/out:{library}"]
        run("link.exe", ["/lib", response("library.rsp", args, objects)], library_log)
        if not (ROOT / library).is_file():
            raise ValueError(f"librarian did not produce {library}")
        print(f"Built {library} from {len(objects)} objects", flush=True)
        if link_program:
            # The Windows CRT expects the stdcall entry under its C name.
            entry = units["game-application-run-00602a60"]["symbol"]
            # D3DX8 carries a VC6 default-library directive absent from VC7.1.
            args = ["/nologo", "/subsystem:windows,4.0", "/machine:x86", "/incremental:no",
                    "/nodefaultlib:libci.lib", f"/map:{link_map}", f"/out:{executable}",
                    f"/alternatename:_WinMain@16={entry}"]
            libs = [Path(name + ".lib") for name in (
                "dinput8", "winmm", "d3dx8", "d3d8", "dxguid", "dsound",
                "kernel32", "user32", "gdi32", "advapi32", "ole32", "uuid",
            )]
            try:
                run("link.exe", [response("link.rsp", args, [*objects, *libs])], link_log)
                if not (ROOT / executable).is_file() or not (ROOT / link_map).is_file():
                    raise ValueError(f"linker did not produce {executable} and {link_map}")
            except (OSError, ValueError, KeyboardInterrupt):
                (ROOT / executable).unlink(missing_ok=True)
                (ROOT / link_map).unlink(missing_ok=True)
                raise
            print(f"Built {executable} and {link_map}")


def main() -> int:
    args = parse_args()
    try:
        manifest = load()
        units = manifest["units"]
        if args.check:
            print(f"match-unit graph OK: {len(units)} configured units")
            return 0
        if args.program or args.library:
            verify_target()
            build_program(units, link_program=args.program)
            return 0
        if args.batch_unit:
            selected = {name: units[name] for name in args.batch_unit}
            verify_target()
            build_program(selected, link_program=False, comparison_batch=True)
            return 0
        if args.unit is not None:
            matches = [(args.unit, units[args.unit])] if args.unit in units else []
            wanted = args.unit
        else:
            wanted = Path(args.object_name).name
            matches = [
                (name, unit)
                for name, unit in units.items()
                if Path(str(unit["object"])).name == wanted
            ]
        if len(matches) != 1:
            raise ValueError(f"unknown or ambiguous match object: {wanted}")
        name, unit = matches[0]
        verify_target()
        profile = compiler_profile(name, unit)
        output = ROOT / str(unit["object"])
        output.unlink(missing_ok=True)
        subprocess.run(
            [
                str(ROOT / "scripts" / "compile-probe.sh"),
                str(ROOT / str(unit["source"])),
                str(output),
                *profile,
            ],
            cwd=ROOT,
            check=True,
        )
        if not output.is_file():
            raise ValueError(f"unit {name!r} did not produce {output}")
        print(f"built {name}: {output.relative_to(ROOT)}")
        return 0
    except (
        OSError,
        KeyError,
        TypeError,
        ValueError,
        subprocess.CalledProcessError,
        tomllib.TOMLDecodeError,
    ) as exc:
        print(f"error: build routing failed: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
