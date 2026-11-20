#!/usr/bin/env python3
"""Check typed Marisa Advance cases against the current Ghidra switch labels.

This is a source-coverage check only. It does not compare machine code,
validate runtime behavior, or confer any exactness/ownership credit.
"""
from __future__ import annotations

import ast
import csv
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
PROBES = ROOT / "probes"
SOURCE = PROBES / "MarisaFighterAdvancePartial.cpp"
DECOMP = ROOT / ".analysis" / "marisa-boss-decomp.txt"
HANDLERS = ROOT / ".analysis" / "marisa-action-handlers.csv"


def expand(text: str, macros: dict[str, str]) -> str:
    for _ in range(16):
        updated = re.sub(
            r"\b[A-Za-z_]\w*\b",
            lambda match: macros.get(match.group(0), match.group(0)),
            text,
        )
        if updated == text:
            return text
        text = updated
    raise ValueError(f"macro expansion did not converge: {text!r}")


def eval_condition(text: str, macros: dict[str, str]) -> bool:
    expression = expand(text, macros)
    expression = expression.replace("&&", " and ").replace("||", " or ")
    expression = re.sub(r"!(?!=)", " not ", expression)
    tree = ast.parse(expression.strip(), mode="eval")

    def visit(node: ast.AST) -> object:
        if isinstance(node, ast.Expression):
            return visit(node.body)
        if isinstance(node, ast.Constant) and isinstance(node.value, (int, bool)):
            return node.value
        if isinstance(node, ast.BoolOp) and isinstance(node.op, (ast.And, ast.Or)):
            values = [bool(visit(value)) for value in node.values]
            return all(values) if isinstance(node.op, ast.And) else any(values)
        if isinstance(node, ast.UnaryOp) and isinstance(node.op, ast.Not):
            return not bool(visit(node.operand))
        if isinstance(node, ast.Compare) and len(node.ops) == len(node.comparators) == 1:
            left, right = visit(node.left), visit(node.comparators[0])
            if isinstance(node.ops[0], ast.Eq):
                return left == right
            if isinstance(node.ops[0], ast.NotEq):
                return left != right
        raise ValueError(f"unsupported preprocessor expression: {text!r}")

    return bool(visit(tree))


def source_cases(path: Path, macros: dict[str, str], seen: list[int]) -> None:
    # (parent-active, condition, else-seen) mirrors the small #if subset used
    # by these fragments; macro state intentionally flows through includes.
    stack: list[tuple[bool, bool, bool]] = []
    active = True
    for line_number, line in enumerate(path.read_text(encoding="utf-8").splitlines(), 1):
        directive = re.match(r"\s*#\s*(\w+)(?:\s+(.*?))?\s*$", line)
        if directive:
            name, argument = directive.group(1), (directive.group(2) or "").strip()
            if name == "if":
                condition = eval_condition(argument, macros) if active else False
                stack.append((active, condition, False))
                active = active and condition
            elif name == "else":
                if not stack or stack[-1][2]:
                    raise ValueError(f"{path}:{line_number}: unmatched/duplicate #else")
                parent, condition, _ = stack[-1]
                stack[-1] = (parent, condition, True)
                active = parent and not condition
            elif name == "endif":
                if not stack:
                    raise ValueError(f"{path}:{line_number}: unmatched #endif")
                parent, _, _ = stack.pop()
                active = parent
            elif not active:
                continue
            elif name == "define":
                match = re.match(r"([A-Za-z_]\w*)\s+(.+)$", argument)
                if match:
                    macros[match.group(1)] = match.group(2).strip()
            elif name == "undef":
                macros.pop(argument, None)
            elif name == "include":
                match = re.fullmatch(r'"([^"\\]+\.inc)"', argument)
                if match:
                    child = (PROBES / match.group(1)).resolve()
                    if child.parent != PROBES.resolve() or not child.is_file():
                        raise ValueError(f"{path}:{line_number}: invalid include {argument}")
                    source_cases(child, macros, seen)
            continue
        if not active:
            continue
        case = re.match(r"\s*case\s+([^:]+):", line)
        if case:
            value = expand(case.group(1).strip(), macros)
            try:
                seen.append(int(value, 0))
            except ValueError as exc:
                raise ValueError(f"{path}:{line_number}: unresolved case {value!r}") from exc
    if stack:
        raise ValueError(f"{path}: unterminated #if block")


def main() -> int:
    for path in (SOURCE, DECOMP, HANDLERS):
        if not path.is_file():
            print(f"missing analysis input: {path.relative_to(ROOT)}", file=sys.stderr)
            return 2
    source: list[int] = []
    source_cases(SOURCE, {}, source)
    with HANDLERS.open(newline="", encoding="utf-8") as stream:
        valid_actions = {int(row["action"], 0) for row in csv.DictReader(stream)}
    top_level: set[int] = set()
    for line in DECOMP.read_text(encoding="utf-8").splitlines():
        match = re.match(r"^ {6}case\s+(0x[0-9a-fA-F]+|\d+)\s*:", line)
        if match:
            value = int(match.group(1), 0)
            if value in valid_actions:
                top_level.add(value)
    implemented = set(source)
    missing = sorted(top_level - implemented)
    print(
        f"Marisa Advance source labels: {len(source)} ({len(implemented)} unique); "
        f"mapped Ghidra top-level labels: {len(top_level)}; "
        f"covered: {len(top_level) - len(missing)}/{len(top_level)}"
    )
    if missing:
        print("missing action IDs: " + ", ".join(f"0x{x:X}" for x in missing))
        return 1
    print("case coverage OK (not an exactness or runtime verdict)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
