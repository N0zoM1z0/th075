"""Inspect whole relocation-free readonly vendor COFF data sections."""
from __future__ import annotations

import struct


def parse_symbols(data, coff_name):
    machine, count, _, symbol_offset, symbol_count, optional, _ = struct.unpack_from(
        "<HHIIIHH", data)
    if machine != 0x14C or optional or not count or 20 + count * 40 > len(data):
        raise ValueError("invalid vendor COFF section table")
    strings_offset = symbol_offset + symbol_count * 18
    if strings_offset + 4 > len(data):
        raise ValueError("truncated vendor COFF symbols")
    strings_size = struct.unpack_from("<I", data, strings_offset)[0]
    if strings_size < 4 or strings_offset + strings_size > len(data):
        raise ValueError("truncated vendor COFF strings")
    strings = data[strings_offset:strings_offset + strings_size]
    symbols = []
    index = 0
    while index < symbol_count:
        raw, value, section, typ, storage, aux = struct.unpack_from(
            "<8sIhHBB", data, symbol_offset + index * 18)
        if index + aux >= symbol_count:
            raise ValueError("truncated vendor COFF auxiliary records")
        symbols.append({"symbol": coff_name(raw, strings), "offset": value,
                        "section": section, "type": typ, "storage": storage})
        index += 1 + aux
    return count, symbols


def readonly_section(data, number, coff_name):
    """Use the entire section, including all definitions, never a chosen prefix."""
    count, symbols = parse_symbols(data, coff_name)
    if not 1 <= number <= count:
        raise ValueError("invalid readonly vendor section number")
    section = struct.unpack_from("<8sIIIIIIHHI", data, 20 + (number - 1) * 40)
    flags, size, offset = section[9], section[3], section[4]
    if (flags & 0x20 or flags & 0x20000000 or flags & 0x80000000
            or not flags & 0x40 or not flags & 0x40000000 or section[7]
            or not size or not offset or offset + size > len(data)):
        raise ValueError("section is not complete relocation-free readonly vendor data")
    definitions = [{"symbol": entry["symbol"], "offset": entry["offset"]}
                   for entry in symbols if entry["section"] == number
                   and entry["type"] != 0x20 and entry["storage"] in (2, 3)
                   and not entry["symbol"].startswith(".")]
    if not definitions or any(entry["offset"] >= size for entry in definitions):
        raise ValueError("readonly section lacks valid complete symbol definitions")
    return data[offset:offset + size], definitions
