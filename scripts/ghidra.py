#!/usr/bin/env python3
"""Run hash-attested TH075 Ghidra headless workflows."""

from __future__ import annotations

import argparse
import fcntl
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tomllib


ROOT = Path(__file__).resolve().parents[1]
PROJECT_DIR = ROOT / "ghidra-project"
PROJECT_NAME = "TH075"
SCRIPT_DIR = ROOT / "scripts" / "ghidra"
CONFIG = ROOT / "config" / "target.toml"
ATTESTATION_PREFIX = "TH075_GHIDRA_ATTESTATION_OK"


def load_target() -> tuple[Path, dict[str, object], dict[str, object]]:
    with CONFIG.open("rb") as stream:
        manifest = tomllib.load(stream)
    target = manifest["target"]
    return ROOT / "resources" / str(target["filename"]), target, manifest["pe"]


def find_analyzer() -> tuple[Path, Path]:
    candidates: list[Path] = []
    configured = os.environ.get("GHIDRA_HOME")
    if configured:
        candidates.append(Path(configured))
    candidates.append(ROOT / ".tools" / "ghidra")
    for ghidra_home in candidates:
        analyzer = ghidra_home / "support" / "analyzeHeadless"
        if analyzer.is_file():
            return ghidra_home.resolve(), analyzer.resolve()
    system = shutil.which("ghidra-analyzeHeadless") or shutil.which("analyzeHeadless")
    if system:
        return Path(system).resolve().parents[1], Path(system).resolve()
    raise FileNotFoundError("Ghidra not found; run scripts/bootstrap-tools.sh")


def environment(ghidra_home: Path) -> dict[str, str]:
    result = os.environ.copy()
    if "JAVA_HOME" not in result:
        local_jdk = ROOT / ".tools" / "jdk"
        if local_jdk.is_dir():
            result["JAVA_HOME"] = str(local_jdk.resolve())
    result["GHIDRA_HOME"] = str(ghidra_home)
    return result


def verify_target(path: Path) -> None:
    subprocess.run(
        [str(ROOT / "scripts/repo-python"), str(ROOT / "scripts" / "verify-target.py"), str(path)],
        cwd=ROOT,
        check=True,
    )


def integer(value: object) -> int:
    if isinstance(value, int):
        return value
    return int(str(value), 0)


def verify_pe_manifest(image: bytes, pe: dict[str, object]) -> None:
    """Verify the manifest's PE32 mapping fields against the canonical file."""
    if len(image) < 0x40:
        raise ValueError("target is too small for a DOS header")
    pe_offset = int.from_bytes(image[0x3C:0x40], "little")
    if image[pe_offset : pe_offset + 4] != b"PE\0\0":
        raise ValueError("target has no PE signature")
    if int.from_bytes(image[pe_offset + 4 : pe_offset + 6], "little") != 0x14C:
        raise ValueError("target PE machine is not i386")

    section_count = int.from_bytes(image[pe_offset + 6 : pe_offset + 8], "little")
    optional_size = int.from_bytes(image[pe_offset + 20 : pe_offset + 22], "little")
    optional = pe_offset + 24
    if int.from_bytes(image[optional : optional + 2], "little") != 0x10B:
        raise ValueError("target optional header is not PE32")
    image_base = int.from_bytes(image[optional + 28 : optional + 32], "little")
    entry_point = image_base + int.from_bytes(
        image[optional + 16 : optional + 20], "little"
    )
    observed = {
        "image_base": image_base,
        "entry_point": entry_point,
        "size_of_image": int.from_bytes(
            image[optional + 56 : optional + 60], "little"
        ),
        "headers_raw_size": int.from_bytes(
            image[optional + 60 : optional + 64], "little"
        ),
    }
    for key, actual in observed.items():
        if actual != integer(pe[key]):
            raise ValueError(
                f"target PE {key} is {actual:#x}, expected {integer(pe[key]):#x}"
            )

    section_table = optional + optional_size
    text: dict[str, int] | None = None
    for index in range(section_count):
        offset = section_table + index * 40
        if offset + 40 > len(image):
            raise ValueError("target PE section table is truncated")
        name = image[offset : offset + 8].split(b"\0", 1)[0]
        if name == b".text":
            text = {
                "virtual_size": int.from_bytes(image[offset + 8 : offset + 12], "little"),
                "rva": int.from_bytes(image[offset + 12 : offset + 16], "little"),
                "raw_size": int.from_bytes(image[offset + 16 : offset + 20], "little"),
                "raw_offset": int.from_bytes(image[offset + 20 : offset + 24], "little"),
            }
            break
    if text is None:
        raise ValueError("target PE has no .text section")

    expected_text = {
        "virtual_size": integer(pe["text_virtual_size"]),
        "rva": integer(pe["text_start"]) - image_base,
        "raw_size": integer(pe["text_raw_size"]),
        "raw_offset": integer(pe["text_raw_offset"]),
    }
    for key, actual in text.items():
        if actual != expected_text[key]:
            raise ValueError(
                f"target .text {key} is {actual:#x}, expected {expected_text[key]:#x}"
            )
    actual_text_end = image_base + text["rva"] + text["virtual_size"] - 1
    if actual_text_end != integer(pe["text_end"]):
        raise ValueError(
            f"target .text end is {actual_text_end:#x}, "
            f"expected {integer(pe['text_end']):#x}"
        )


def mapped_samples(
    target_path: Path, pe: dict[str, object]
) -> list[tuple[int, bytes]]:
    """Return distributed target-file bytes at mapped .text addresses."""
    image = target_path.read_bytes()
    verify_pe_manifest(image, pe)
    text_start = integer(pe["text_start"])
    text_end = integer(pe["text_end"])
    raw_offset = integer(pe["text_raw_offset"])
    raw_size = integer(pe["text_raw_size"])
    sample_size = 16
    mapped_size = text_end - text_start + 1
    available = min(mapped_size, raw_size)
    if available < sample_size:
        raise ValueError("target .text is too small for mapped-byte attestation")

    relative_entry = integer(pe["entry_point"]) - text_start
    offsets = {
        0,
        available // 4,
        available // 2,
        (available * 3) // 4,
        relative_entry,
        available - sample_size,
    }
    normalized = sorted(
        min(max(offset, 0), available - sample_size) for offset in offsets
    )
    samples: list[tuple[int, bytes]] = []
    for offset in normalized:
        start = raw_offset + offset
        sample = image[start : start + sample_size]
        if len(sample) != sample_size:
            raise ValueError("mapped-byte sample extends beyond the target file")
        samples.append((text_start + offset, sample))
    return samples


def attestation_marker(
    target: dict[str, object], pe: dict[str, object], sample_count: int
) -> str:
    return ":".join(
        [
            ATTESTATION_PREFIX,
            str(target["sha256"]).lower(),
            str(target["md5"]).lower(),
            str(integer(target["size"])),
            f"{integer(pe['image_base']):08X}",
            str(integer(pe["size_of_image"])),
            f"{integer(pe['entry_point']):08X}",
            str(sample_count),
        ]
    )


def attestation_args(
    target_path: Path, target: dict[str, object], pe: dict[str, object]
) -> tuple[list[str], str]:
    samples = mapped_samples(target_path, pe)
    marker = attestation_marker(target, pe, len(samples))
    return [
        "-postScript",
        "VerifyTarget.java",
        str(target["sha256"]),
        str(target["md5"]),
        str(target["filename"]),
        str(target["size"]),
        str(pe["image_base"]),
        str(pe["size_of_image"]),
        str(pe["entry_point"]),
        str(pe["text_start"]),
        str(len(samples)),
        *(value for address, sample in samples for value in (hex(address), sample.hex())),
    ], marker


def inventory_args(pe: dict[str, object], destination: Path | None = None) -> list[str]:
    destination = destination or ROOT / "config"
    destination.mkdir(parents=True, exist_ok=True)
    return [
        "-postScript",
        "ExportInventory.java",
        str((destination / "functions.csv").resolve()),
        str((destination / "function-origins.csv").resolve()),
        str(pe["text_start"]),
        str(pe["text_end"]),
        "ghidra-12.1.3-initial-inventory",
    ]


def run_headless(arguments: list[str], required_marker: str, operation_marker: str | None = None) -> None:
    ghidra_home, analyzer = find_analyzer()
    command = [
        str(analyzer),
        str(PROJECT_DIR),
        PROJECT_NAME,
        *arguments,
        "-scriptPath",
        str(SCRIPT_DIR),
        "-log",
        str(ROOT / ".analysis" / "ghidra" / "application.log"),
    ]
    print("Running:", " ".join(command), flush=True)
    completed = subprocess.run(
        command,
        cwd=ROOT,
        env=environment(ghidra_home),
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
        errors="replace",
    )
    if completed.stdout:
        print(completed.stdout, end="" if completed.stdout.endswith("\n") else "\n")
    if completed.stderr:
        print(
            completed.stderr,
            end="" if completed.stderr.endswith("\n") else "\n",
            file=sys.stderr,
        )
    if completed.returncode != 0:
        raise subprocess.CalledProcessError(completed.returncode, command)
    for marker in (required_marker, operation_marker):
        if marker is not None and not re.search(
            r"> " + re.escape(marker) + r"(?: \(GhidraScript\))?\s*$",
            completed.stdout, re.MULTILINE,
        ):
            raise RuntimeError("Ghidra did not emit success marker: " + marker)


def project_exists() -> bool:
    return (PROJECT_DIR / f"{PROJECT_NAME}.gpr").is_file()


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    subparsers = parser.add_subparsers(dest="command", required=True)
    subparsers.add_parser(
        "initialize", help="import, analyze, and attest target without rewriting ledgers"
    )
    subparsers.add_parser("import", help="import, analyze, attest, and inventory target")
    subparsers.add_parser("inventory", help="export candidates below .analysis without overwriting ledgers")
    subparsers.add_parser("check", help="attest existing project without analysis")
    decompile = subparsers.add_parser(
        "decompile", help="write bounded decompiler hypotheses below .analysis"
    )
    decompile.add_argument("output", type=Path)
    decompile.add_argument("addresses", nargs="+")
    query = subparsers.add_parser(
        "query", help="write a bounded read-only program query below .analysis"
    )
    query.add_argument("output", type=Path)
    query.add_argument("operation")
    query.add_argument("query_args", nargs="*")
    return parser.parse_args()


def analysis_output(path: Path) -> Path:
    output = path.expanduser().resolve()
    try:
        output.relative_to((ROOT / ".analysis").resolve())
    except ValueError as exc:
        raise ValueError("analysis output must stay below .analysis/") from exc
    output.parent.mkdir(parents=True, exist_ok=True)
    return output


def query_script_args(operation: str, args: list[str]) -> list[str]:
    result = list(args)
    address_operations = {"function", "callers", "callees"}
    bounded_operations = {"disassemble", "xrefs_to", "xrefs_from"}
    if operation in address_operations:
        result = checked_addresses(result)
    elif operation in bounded_operations:
        if not result or not result[0].isdigit() or not 1 <= int(result[0]) <= 500:
            raise ValueError("query count must be between 1 and 500")
        result = [result[0], *checked_addresses(result[1:])]
    elif operation == "list_functions":
        if len(result) != 3 or not result[0].isdigit() or not 0 <= int(result[0]) <= 1000000:
            raise ValueError("list_functions requires OFFSET LIMIT FILTER")
        if not result[1].isdigit() or not 1 <= int(result[1]) <= 500:
            raise ValueError("list_functions limit must be between 1 and 500")
    elif operation == "search_strings":
        if len(result) != 2 or not result[0].isdigit() or not 1 <= int(result[0]) <= 500 or not result[1].strip():
            raise ValueError("search_strings requires LIMIT NONEMPTY_QUERY")
    else:
        raise ValueError("unsupported query operation: " + operation)
    text_index = {"list_functions": 2, "search_strings": 1}.get(operation)
    if text_index is not None and len(result) > text_index:
        if len(result[text_index]) > 1000 or "\0" in result[text_index]:
            raise ValueError("query text is invalid or too long")
        result[text_index] = "text:" + result[text_index]
    return result


def checked_addresses(values: list[str]) -> list[str]:
    if not 1 <= len(values) <= 16 or any(
        re.fullmatch(r"0x[0-9A-Fa-f]{1,8}", value) is None for value in values
    ):
        raise ValueError("requires 1..16 hexadecimal i386 addresses")
    return [f"0x{int(value, 16):08X}" for value in values]


def main() -> int:
    args = parse_args()
    PROJECT_DIR.mkdir(parents=True, exist_ok=True)
    with (PROJECT_DIR / "workflow.lock").open("a") as lock:
        fcntl.flock(lock, fcntl.LOCK_EX)
        return execute(args)


def execute(args: argparse.Namespace) -> int:
    try:
        target_path, target, pe = load_target()
        verify_target(target_path)
        attestation, marker = attestation_args(target_path, target, pe)
        (ROOT / ".analysis" / "ghidra").mkdir(parents=True, exist_ok=True)
        operation_marker = None
        if args.command in {"initialize", "import"}:
            if project_exists():
                raise ValueError(
                    "Ghidra project already exists; use inventory/check or move the "
                    "private ghidra-project directory aside before a clean import"
                )
            import_args = [
                "-import",
                str(target_path.resolve()),
                "-analysisTimeoutPerFile",
                "1800",
                "-max-cpu",
                "1",
                *attestation,
            ]
            if args.command == "import":
                import_args.extend(inventory_args(pe))
                operation_marker = "TH075_INVENTORY_OK"
            run_headless(import_args, marker, operation_marker)
        else:
            if not project_exists():
                raise ValueError("missing Ghidra project; run scripts/ghidra.py initialize")
            base = [
                "-process",
                str(target["filename"]),
                "-readOnly",
                "-noanalysis",
                *attestation,
            ]
            if args.command == "inventory":
                base.extend(inventory_args(pe, ROOT / ".analysis" / "inventory"))
                operation_marker = "TH075_INVENTORY_OK"
            elif args.command == "decompile":
                output = analysis_output(args.output)
                base.extend(
                    [
                        "-postScript",
                        "DecompileFunctions.java",
                        str(output),
                        *checked_addresses(args.addresses),
                    ]
                )
                operation_marker = "TH075_DECOMPILE_OK"
            elif args.command == "query":
                output = analysis_output(args.output)
                base.extend(
                    [
                        "-postScript",
                        "QueryProgram.java",
                        str(output),
                        args.operation,
                        *query_script_args(args.operation, args.query_args),
                    ]
                )
                operation_marker = "TH075_QUERY_OK"
            run_headless(base, marker, operation_marker)
    except (
        OSError,
        KeyError,
        RuntimeError,
        TypeError,
        ValueError,
        subprocess.CalledProcessError,
    ) as exc:
        print(f"error: Ghidra workflow failed: {exc}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
