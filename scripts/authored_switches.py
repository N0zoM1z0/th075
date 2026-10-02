"""Verify complete guarded byte-remap switches without hiding instruction fields."""
from __future__ import annotations

import hashlib
import struct

from capstone import Cs, CS_ARCH_X86, CS_MODE_32, CS_GRP_JUMP
from capstone.x86 import X86_OP_IMM, X86_OP_MEM, X86_OP_REG, X86_REG_EBP


def verify_switches(code, address, records, read):
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    instructions = list(decoder.disasm(code, address))
    positions = {item.address: index for index, item in enumerate(instructions)}
    starts = set(positions)
    result = {}
    for record in records:
        site = int(record["jump_site"], 16)
        index = positions[site]
        if site in result or index < 4:
            raise ValueError("duplicate or incomplete bounded switch dispatch")
        compare, guard, load, remap_load, jump = instructions[index - 4:index + 1]
        if [item.mnemonic for item in [compare, guard, load, remap_load, jump]] != ["cmp", "ja", "mov", "movzx", "jmp"]:
            raise ValueError("unsupported bounded switch dispatch instructions")
        slot, limit = compare.operands
        if (slot.type != X86_OP_MEM or slot.mem.base != X86_REG_EBP or slot.mem.index
                or slot.mem.segment or slot.size != 4 or limit.type != X86_OP_IMM
                or not 0 <= limit.imm <= 255 or guard.operands[0].type != X86_OP_IMM
                or guard.operands[0].imm not in starts):
            raise ValueError("switch lacks an unsigned bounded frame selector")
        loaded_register, loaded_slot = load.operands
        if (loaded_register.type != X86_OP_REG or loaded_slot.type != X86_OP_MEM
                or loaded_slot.mem.base != slot.mem.base or loaded_slot.mem.index
                or loaded_slot.mem.segment or loaded_slot.mem.disp != slot.mem.disp
                or loaded_slot.size != 4):
            raise ValueError("switch range guard and selector load disagree")
        case_register, remap_operand = remap_load.operands
        if (case_register.type != X86_OP_REG or remap_operand.type != X86_OP_MEM
                or remap_operand.size != 1 or remap_operand.mem.index or remap_operand.mem.segment
                or remap_operand.mem.base != loaded_register.reg):
            raise ValueError("switch remap does not consume the bounded selector")
        operand = jump.operands[0]
        if (operand.type != X86_OP_MEM or operand.size != 4 or operand.mem.base
                or operand.mem.segment or operand.mem.scale != 4
                or operand.mem.index != case_register.reg):
            raise ValueError("switch jump does not consume the remapped case index")
        if (compare.address != int(record["range_site"], 16)
                or limit.imm + 1 != int(record["remap_size"])
                or remap_operand.mem.disp != int(record["remap_address"], 16)
                or operand.mem.disp != int(record["table_address"], 16)
                or guard.operands[0].imm != int(record["default_target"], 16)):
            raise ValueError("switch instruction fields differ from recorded evidence")
        forbidden = {item.address for item in [guard, load, remap_load, jump]}
        for other in instructions:
            if (other.group(CS_GRP_JUMP) and other.operands[0].type == X86_OP_IMM
                    and other.operands[0].imm in forbidden):
                raise ValueError("incoming branch bypasses the switch range guard")
        remap = read(remap_operand.mem.disp, limit.imm + 1)
        table_size = (max(remap) + 1) * 4
        if len(remap) != limit.imm + 1 or table_size != int(record["table_size"]):
            raise ValueError("switch does not retain the complete reachable jump table")
        table = read(operand.mem.disp, table_size)
        if (len(table) != table_size or hashlib.sha256(remap).hexdigest() != record["remap_sha256"]
                or hashlib.sha256(table).hexdigest() != record["table_sha256"]):
            raise ValueError("complete switch table or remap hash mismatch")
        destinations = list(struct.unpack("<" + "I" * (table_size // 4), table))
        if any(value not in starts or value in forbidden for value in destinations):
            raise ValueError("switch targets an external tail, guard interior or non-instruction")
        result[site] = destinations
    return result
