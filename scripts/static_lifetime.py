"""Check complete VC7-generated global lifetime wrappers and their links."""
from __future__ import annotations

import hashlib
import struct

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86 import X86_OP_IMM, X86_OP_REG

KINDS = {
    "object-init": (28, ["push", "mov", "mov", "call", "push", "call", "add", "pop", "ret"]),
    "init-only": (15, ["push", "mov", "mov", "call", "pop", "ret"]),
    "object-finalizer": (15, ["push", "mov", "mov", "call", "pop", "ret"]),
    "array-init": (42, ["push", "mov", "push", "push", "push", "push", "push", "call", "push", "call", "add", "pop", "ret"]),
    "array-finalizer": (24, ["push", "mov", "push", "push", "push", "push", "call", "pop", "ret"]),
}


def decode(code, address, kind):
    """Return actual global/callback/callee fields from a whole wrapper body."""
    if kind not in KINDS or len(code) != KINDS[kind][0]:
        raise ValueError("unknown or incomplete global lifetime wrapper")
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    decoder.detail = True
    ins = list(decoder.disasm(code, address))
    if sum(item.size for item in ins) != len(code) or [item.mnemonic for item in ins] != KINDS[kind][1]:
        raise ValueError("global lifetime wrapper has different complete instructions")
    if (ins[0].op_str != "ebp" or ins[1].op_str != "ebp, esp"
            or ins[-2].op_str != "ebp" or ins[-1].operands):
        raise ValueError("global lifetime wrapper lacks its complete stack frame")
    def imm(index):
        operand = ins[index].operands[0]
        if operand.type != X86_OP_IMM:
            raise ValueError("wrapper field is not an immediate")
        return operand.imm
    def call(index):
        return imm(index)
    if kind in ("object-init", "init-only", "object-finalizer"):
        if (ins[2].operands[0].type != X86_OP_REG
                or ins[2].reg_name(ins[2].operands[0].reg) != "ecx"):
            raise ValueError("object wrapper has no this pointer")
        result = dict(object_address=ins[2].operands[1].imm,
                      callee_address=call(3))
        if ins[2].operands[1].type != X86_OP_IMM:
            raise ValueError("object wrapper does not use an absolute global")
        if kind == "object-init":
            if ins[6].op_str != "esp, 4":
                raise ValueError("static finalizer registration stack is not restored")
            result.update(registered_callback=imm(4), registration_target=call(5))
        return result
    if kind == "array-init":
        if ins[10].op_str != "esp, 4":
            raise ValueError("array finalizer registration stack is not restored")
        return dict(object_address=imm(6), callee_address=call(7),
                    constructor_callback=imm(3), destructor_callback=imm(2),
                    count=imm(4), stride=imm(5),
                    registered_callback=imm(8), registration_target=call(9))
    return dict(object_address=imm(5), callee_address=call(6),
                destructor_callback=imm(2), count=imm(3), stride=imm(4))


def check_links(records, startup_addresses):
    """No destructor or callback can be credited without its exact owner."""
    if len(startup_addresses) != 11 or len(set(startup_addresses)) != 11:
        raise ValueError("global startup table does not contain eleven distinct entries")
    wrappers = {int(row["address"], 16): row for row in records}
    if len(wrappers) != len(records) or set(startup_addresses) - set(wrappers):
        raise ValueError("missing or duplicate global startup wrapper")
    finals = {}
    for row in records:
        address = int(row["address"], 16)
        is_startup = address in startup_addresses
        if is_startup != bool(row["table_slot"]):
            raise ValueError("wrapper startup table membership differs")
        if is_startup and row["template_kind"] not in ("object-init", "init-only", "array-init"):
            raise ValueError("finalizer cannot run from the startup table")
        if is_startup and int(row["table_slot"], 16) != 0x66C008 + 4 * startup_addresses.index(address):
            raise ValueError("wrapper has a different startup table slot")
        if not is_startup and row["template_kind"] not in ("object-finalizer", "array-finalizer"):
            raise ValueError("unregistered extra initializer")
        if row["registered_callback"]:
            callback = int(row["registered_callback"], 16)
            if callback in finals or callback not in wrappers or callback in startup_addresses:
                raise ValueError("static finalizer is missing, duplicate or runs at startup")
            finals[callback] = row
    if len(wrappers) != 11 + len(finals):
        raise ValueError("orphan static finalizer or incomplete startup table")
    for callback, init in finals.items():
        final = wrappers[callback]
        if int(init["object_address"], 16) != int(final["object_address"], 16):
            raise ValueError("static initializer/finalizer global differs")
        if init["template_kind"] == "object-init" and final["template_kind"] != "object-finalizer":
            raise ValueError("object finalizer has wrong template")
        if init["template_kind"] == "array-init":
            if final["template_kind"] != "array-finalizer":
                raise ValueError("array finalizer has wrong template")
            for field in ("destructor_callback", "count", "stride"):
                if init[field] != final[field]:
                    raise ValueError("array finalizer metadata differs")
    return finals
