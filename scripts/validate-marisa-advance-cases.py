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
            continue
        # The native parent has six range-boundary handlers outside its sparse
        # switches.  Keep those if-dispatches in the same coverage set, expanding
        # their per-include F628_CASE macro exactly as the preprocessor does.
        special = re.match(
            r"\s*if\s*\(\s*(?:actionSnapshot|action)\s*==\s*([^\)]+)\)",
            line,
        )
        if special:
            value = expand(special.group(1).strip(), macros)
            try:
                seen.append(int(value, 0))
            except ValueError as exc:
                raise ValueError(f"{path}:{line_number}: unresolved special action {value!r}") from exc
        # Boundary handlers can be dispatched by a positive or negative
        # condition followed by a natural C++ goto to an out-of-line body.
        # Count those label edges as source coverage too (not as switch cases).
        goto = re.match(r"\s*goto\s+([A-Za-z_]\w*)\s*;", line)
        if goto:
            target_action = {
                "action32Special": 0x32,
                "action8CSpecial": 0x8C,
                "action12CSpecial": 0x12C,
                "action186Special": 0x186,
                "action1F4Special": 0x1F4,
                "action2C2Special": 0x2C2,
            }.get(goto.group(1))
            if target_action is not None:
                seen.append(target_action)
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
    # source_cases() has already expanded and included both ordinary case
    # labels and the standalone actionSnapshot/action boundary handlers.
    implemented = set(source)
    missing = sorted(top_level - implemented)

    handler_by_action: dict[int, int] = {}
    with HANDLERS.open(newline="", encoding="utf-8") as stream:
        for row in csv.DictReader(stream):
            handler_by_action[int(row["action"], 0)] = int(row["handler"], 16)
    parent_start = 0x00486550
    parent_end = parent_start + 50735
    handler_actions: dict[int, list[int]] = {}
    for action, handler in handler_by_action.items():
        if parent_start <= handler < parent_end:
            handler_actions.setdefault(handler, []).append(action)
    represented_handlers = {
        handler for handler, actions in handler_actions.items()
        if any(action in implemented for action in actions)
    }
    default_handler = 0x00492B51
    missing_handlers = sorted(set(handler_actions) - represented_handlers - {default_handler})
    has_default = bool(re.search(r"^\s*default\s*:", SOURCE.read_text(encoding="utf-8"), re.M))

    # The source order of this sparse late-card switch is observable in the
    # compiler's emitted handler layout. Guard it against accidental numeric
    # sorting: the original PE handler addresses define the required order.
    late_tail = PROBES / "MarisaFighterCardTail2BC2C1.inc"
    late_order = [
        int(match.group(1), 0)
        for line in late_tail.read_text(encoding="utf-8").splitlines()
        if (match := re.match(r"\s*case\s+(0x[0-9a-fA-F]+|\d+)\s*:", line))
    ]
    if len(late_order) != len(set(late_order)):
        raise ValueError("duplicate action in Marisa late-card handler order")
    if any(action not in handler_by_action for action in late_order):
        raise ValueError("late-card source case is absent from the original handler map")
    expected_late_order = sorted(late_order, key=handler_by_action.__getitem__)
    if late_order != expected_late_order:
        print(
            "late-card handler order mismatch: source="
            + ", ".join(f"0x{x:X}" for x in late_order)
            + "; PE="
            + ", ".join(f"0x{x:X}" for x in expected_late_order)
        )
        return 1

    print(
        f"Marisa Advance source dispatches: {len(source)} (including special if-dispatches); "
        f"mapped Ghidra top-level labels: {len(top_level)}; "
        f"covered: {len(top_level) - len(missing)}/{len(top_level)}"
    )
    print(
        f"in-parent handler addresses: {len(handler_actions)}; "
        f"explicitly covered: {len(represented_handlers)}; "
        f"shared default fallback: {'present' if has_default and default_handler in handler_actions else 'missing'}"
    )
    if missing:
        print("missing action IDs: " + ", ".join(f"0x{x:X}" for x in missing))
    if missing_handlers:
        print("missing handler addresses: " + ", ".join(f"0x{x:08X}" for x in missing_handlers))
    if not has_default or default_handler not in handler_actions:
        print("shared default handler is not represented by the source default:", file=sys.stderr)
        return 1
    if missing or missing_handlers:
        return 1
    print("case/handler coverage OK (not an exactness or runtime verdict)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
