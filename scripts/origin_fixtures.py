"""Resolve source fixtures named by frozen origin evidence."""
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
FIXTURES = Path("tests/origin_probes")


def fixture_path(name: str | Path) -> Path:
    """Resolve source paths recorded before the origin fixtures moved."""
    path = Path(name)
    if len(path.parts) == 2 and path.parts[0] == "probes" and path.suffix == ".cpp":
        path = FIXTURES / path.name
    return ROOT / path


def fixture_evidence_name(path: Path) -> str:
    """Keep the names used in frozen include inventories."""
    relative = path.relative_to(ROOT)
    if relative.parent == FIXTURES and relative.name.startswith("VC7") and relative.suffix == ".cpp":
        return f"probes/{relative.name}"
    return relative.as_posix()
