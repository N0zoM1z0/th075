"""Validate VC7 frame metadata and pure compiler-generated cleanup dispatch."""
from __future__ import annotations

import hashlib
import json
import struct

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86 import X86_OP_IMM, X86_OP_MEM, X86_OP_REG, X86_REG_EBP


def reg(instruction, index, name):
    operand = instruction.operands[index]
    return operand.type == X86_OP_REG and instruction.reg_name(operand.reg) == name


def immediate(instruction, index, value=None):
    operand = instruction.operands[index]
    return operand.type == X86_OP_IMM and (value is None or operand.imm == value)


def frame(instruction, index, parameter=False):
    operand = instruction.operands[index]
    return (operand.type == X86_OP_MEM and operand.size == 4
            and operand.mem.base == X86_REG_EBP and not operand.mem.index
            and not operand.mem.segment
            and (operand.mem.disp >= 8 if parameter else operand.mem.disp < 0))


def cleanup_template(code, address, function_entries):
    """Accept only complete dispatch bodies, never arbitrary cleanup policy."""
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(code, address))
    if not instructions or sum(item.size for item in instructions) != len(code):
        raise ValueError("incomplete compiler cleanup extent")
    names = [item.mnemonic for item in instructions]
    kind = None
    transfer = None
    if names in (["mov", "jmp"], ["lea", "jmp"], ["mov", "add", "jmp"]):
        first = instructions[0]
        if (len(instructions) == 2 and first.mnemonic == "lea"
                and reg(first, 0, "ecx") and frame(first, 1, parameter=True)):
            kind, transfer = "parameter-object", instructions[-1]
        if reg(first, 0, "ecx") and frame(first, 1):
            if len(instructions) == 2:
                kind = "local-object" if first.mnemonic == "lea" else "frame-object"
            elif (reg(instructions[1], 0, "ecx")
                  and immediate(instructions[1], 1) and instructions[1].operands[1].imm > 0):
                kind = "member-object"
            transfer = instructions[-1]
    elif names == ["mov", "push", "call", "pop", "ret"]:
        if (reg(instructions[0], 0, "eax") and frame(instructions[0], 1)
                and reg(instructions[1], 0, "eax") and reg(instructions[3], 0, "ecx")
                and not instructions[4].operands):
            kind, transfer = "allocation", instructions[2]
    elif names == ["push", "call", "pop", "ret"]:
        if ((frame(instructions[0], 0) or frame(instructions[0], 0, parameter=True))
                and reg(instructions[2], 0, "ecx")
                and not instructions[3].operands):
            kind = "parameter-allocation" if frame(instructions[0], 0, parameter=True) else "allocation"
            transfer = instructions[1]
    elif names == ["mov", "push", "mov", "push", "call", "add", "ret"]:
        if (reg(instructions[0], 0, "eax")
                and (frame(instructions[0], 1) or frame(instructions[0], 1, parameter=True))
                and reg(instructions[1], 0, "eax") and reg(instructions[2], 0, "ecx")
                and frame(instructions[2], 1) and reg(instructions[3], 0, "ecx")
                and reg(instructions[5], 0, "esp") and immediate(instructions[5], 1, 8)
                and not instructions[6].operands):
            kind, transfer = "placement-allocation", instructions[4]
    elif names in (["push", "push", "push", "mov", "push", "call", "ret"],
                   ["push", "push", "push", "mov", "add", "push", "call", "ret"]):
        if (all(immediate(item, 0) for item in instructions[:3])
                and instructions[0].operands[0].imm in function_entries
                and instructions[1].operands[0].imm > 0 and instructions[2].operands[0].imm > 0
                and reg(instructions[3], 0, "eax") and frame(instructions[3], 1)
                and reg(instructions[-3], 0, "eax") and not instructions[-1].operands):
            if len(instructions) == 7 or (reg(instructions[4], 0, "eax")
                    and immediate(instructions[4], 1) and instructions[4].operands[1].imm > 0):
                kind, transfer = "array-object", instructions[-2]
    if (kind is None or transfer is None or not immediate(transfer, 0)
            or transfer.operands[0].imm not in function_entries):
        raise ValueError("unsupported compiler cleanup policy or unresolved destination")
    return kind, transfer.operands[0].imm


def verify_frame(record, read_code, read_data, function_entries, verified_prologs=()):
    handler, info = int(record["handler_address"], 16), int(record["funcinfo_address"], 16)
    code = read_code(handler, 10)
    if (code[:1] != b"\xb8" or code[5:6] != b"\xe9"
            or struct.unpack_from("<I", code, 1)[0] != info
            or handler + 10 + struct.unpack_from("<i", code, 6)[0] != 0x6407B8):
        raise ValueError("EH handler does not dispatch the recorded FunctionInfo")
    raw = read_data(info, 28)
    magic, states, unwind, tries, trymap, ips, ipmap = struct.unpack("<7I", raw)
    if (magic != 0x19930520 or not 1 <= states <= 1000 or tries > 200
            or ips or ipmap or tries == 0 and trymap != 0
            or states != int(record["state_count"]) or tries != int(record["try_count"])
            or unwind != int(record["unwind_address"], 16)
            or trymap != int(record["trymap_address"], 16)
            or hashlib.sha256(raw).hexdigest() != record["funcinfo_sha256"]):
        raise ValueError("EH FunctionInfo schema or full metadata mismatch")
    table = read_data(unwind, states * 8)
    if hashlib.sha256(table).hexdigest() != record["unwind_sha256"]:
        raise ValueError("EH complete unwind table mismatch")
    entries = []
    for index in range(states):
        to_state, cleanup = struct.unpack_from("<iI", table, index * 8)
        if not -1 <= to_state < index or cleanup and cleanup not in function_entries:
            raise ValueError("invalid EH state transition or cleanup entry")
        entries.append({"state_index": index, "to_state": to_state,
                        "cleanup_address": f"0x{cleanup:08X}"})
    if entries != json.loads(record["entries"]):
        raise ValueError("EH recorded state entries differ from the complete table")
    # Read complete try/handler tables too; ownership of catch code is separate.
    if tries:
        blocks = read_data(trymap, tries * 20)
        for index in range(tries):
            low, high, catch_high, count, handlers = struct.unpack_from("<5I", blocks, index * 20)
            if not low <= high <= catch_high < states or not 1 <= count <= 200:
                raise ValueError("invalid EH try/catch state range")
            read_data(handlers, count * 16)
    owners = json.loads(record["owners"])
    if not owners:
        raise ValueError("EH frame lacks a registered parent")
    for owner in owners:
        start = int(owner["owner_address"], 16)
        if owner.get("registration_kind") == "external-prolog":
            prefix = read_code(start, 10)
            if (start not in function_entries
                    or int(owner["handler_load_site"], 16) != start
                    or prefix[:1] != b"\xb8" or prefix[5:6] != b"\xe8"
                    or struct.unpack_from("<I", prefix, 1)[0] != handler
                    or start + 10 + struct.unpack_from("<i", prefix, 6)[0] not in verified_prologs):
                raise ValueError("EH parent lacks a verified external registration prolog")
            continue
        if owner.get("registration_kind", "inline") != "inline":
            raise ValueError("unsupported EH registration kind")
        site = int(owner["handler_push_site"], 16)
        if (start not in function_entries or site != start + 5
                or read_code(start, 16) != b"\x55\x8b\xec\x6a\xff\x68"
                + struct.pack("<I", handler) + b"\x64\xa1\0\0\0\0"):
            raise ValueError("EH parent lacks the complete compiler registration prefix")
    return entries
