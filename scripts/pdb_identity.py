"""Read bounded PDB identity metadata; never validate symbols, types or ownership."""
from pathlib import Path
import hashlib
import os
import struct
import uuid

MAGIC = b'Microsoft C/C++ MSF 7.00\r\n\x1aDS\0\0\0'
MAX_DIRECTORY = 16 * 1024 * 1024


class UnsupportedPDB(ValueError):
    """A format/size we deliberately do not interpret as a nonmatch."""


def digest(raw):
    return hashlib.sha256(raw).hexdigest()


def portable_identity(read, size):
    """Portable metadata has a GUID+stamp ID, but no native-PDB age field."""
    header = read(0, 16)
    version_size = struct.unpack_from('<I', header, 12)[0]
    if not 1 <= version_size <= 4096 or version_size % 4:
        raise UnsupportedPDB('unsupported portable version-string extent')
    version = read(16, version_size)
    if b'\0' not in version:
        raise ValueError('unterminated portable version string')
    at = 16 + version_size
    flags, count = struct.unpack('<HH', read(at, 4))
    at += 4
    if flags != 0 or not 2 <= count <= 64:
        raise UnsupportedPDB('unsupported portable stream framing')
    streams = {}
    for _ in range(count):
        offset, length = struct.unpack('<II', read(at, 8))
        at += 8
        name = bytearray()
        for _ in range(32):
            char = read(at, 1)
            at += 1
            if char == b'\0':
                break
            name.extend(char)
        else:
            raise ValueError('unterminated portable stream name')
        at = (at + 3) & ~3
        key = bytes(name).decode('ascii')
        if key in streams or offset + length > size:
            raise ValueError('duplicate/out-of-file portable stream')
        streams[key] = dict(offset=offset, size=length)
    if '#Pdb' not in streams or '#~' not in streams:
        raise ValueError('standalone portable PDB streams absent')
    ranges = sorted((r['offset'], r['offset'] + r['size']) for r in streams.values() if r['size'])
    if any(start < at for start, end in ranges) or any(a[1] > b[0] for a, b in zip(ranges, ranges[1:])):
        raise ValueError('portable streams overlap headers or one another')
    pdb = streams['#Pdb']
    if pdb['size'] < 32:
        raise ValueError('truncated portable PDB identity stream')
    info = read(pdb['offset'], 32)
    tables = struct.unpack_from('<Q', info, 24)[0]
    if pdb['size'] != 32 + 4 * tables.bit_count():
        raise ValueError('portable referenced-table rows do not fill #Pdb stream')
    return dict(format='PortablePDB', size=size, guid=str(uuid.UUID(bytes_le=info[:16])),
                age=None, stamp=struct.unpack_from('<I', info, 16)[0],
                identity_sha256=digest(info[:20]), metadata_header_sha256=digest(read(0, at)),
                pdb_stream_sha256=digest(read(pdb['offset'], pdb['size'])), streams=streams,
                limitation='No native age; an equal GUID needs converted-format investigation.')


def read_identity(path, *, allow_trailing=False):
    path = Path(path)
    with path.open('rb') as stream:
        size = os.fstat(stream.fileno()).st_size

        def read(offset, length):
            if offset < 0 or length < 0 or offset + length > size:
                raise ValueError('PDB read exceeds the physical file')
            stream.seek(offset)
            raw = stream.read(length)
            if len(raw) != length:
                raise ValueError('PDB changed or was truncated during read')
            return raw

        if read(0, min(size, 4)) == b'BSJB':
            return portable_identity(read, size)
        if size < 56:
            raise ValueError('truncated MSF superblock')
        header = read(0, 56)
        if header[:32] != MAGIC:
            raise UnsupportedPDB('not MSF 7; no GUID nonmatch inferred')
        block, free_map, count, directory_size, unknown, block_map = struct.unpack_from('<6I', header, 32)
        if block not in [512, 1024, 2048, 4096]:
            raise UnsupportedPDB('unsupported MSF block size')
        declared_size = count * block
        if free_map not in [1, 2] or declared_size > size or count < 4:
            raise ValueError('invalid MSF block count/free map/physical size')
        if declared_size != size and not allow_trailing:
            raise ValueError('MSF physical file has undeclared trailing bytes')
        if directory_size < 12 or directory_size > MAX_DIRECTORY:
            raise UnsupportedPDB('directory exceeds bounded supported extent')
        directory_blocks = (directory_size + block - 1) // block
        if directory_blocks * 4 > block:
            raise UnsupportedPDB('multi-block directory map requires a separate parser')

        def page(index):
            if index >= count:
                raise ValueError('MSF page index exceeds declared file')
            return read(index * block, block)

        map_bytes = page(block_map)[:4 * directory_blocks]
        indices = list(struct.unpack('<' + str(directory_blocks) + 'I', map_bytes))
        if len(indices) != len(set(indices)):
            raise ValueError('duplicate MSF directory page')
        directory = b''.join(page(i) for i in indices)[:directory_size]
        streams = struct.unpack_from('<I', directory)[0]
        if streams < 2 or 4 + 4 * streams > len(directory):
            raise ValueError('truncated PDB stream-size directory')
        sizes = struct.unpack_from('<' + str(streams) + 'I', directory, 4)
        at, info_pages = 4 + 4 * streams, None
        for index, length in enumerate(sizes):
            n = 0 if length == 0xffffffff else (length + block - 1) // block
            if at + 4 * n > len(directory):
                raise ValueError('truncated PDB stream-page directory')
            pages = list(struct.unpack_from('<' + str(n) + 'I', directory, at)) if n else []
            if any(p >= count for p in pages) or len(pages) != len(set(pages)):
                raise ValueError('invalid/duplicate PDB stream page')
            if index == 1:
                info_pages = pages
            at += 4 * n
        if at != len(directory):
            raise ValueError('unexplained PDB directory bytes')
        if sizes[1] == 0xffffffff or sizes[1] < 28 or not info_pages:
            raise ValueError('complete GUID-bearing PDB info header absent')
        info = page(info_pages[0])[:28]
        version, signature, age = struct.unpack_from('<III', info)
        if version != 20000404:
            raise UnsupportedPDB('PDB info version requires an independent layout check')
        return dict(format='MSF7', size=size, declared_size=declared_size,
                    file_extent_equal=declared_size == size, trailing_bytes=size-declared_size,
                    block_size=block, block_count=count,
                    stream_count=streams, directory_size=directory_size, info_stream_size=sizes[1],
                    version=version, signature=signature, age=age, guid=str(uuid.UUID(bytes_le=info[12:28])),
                    superblock_sha256=digest(header), directory_sha256=digest(directory),
                    info_header_sha256=digest(info))


def matches(identity, reference):
    """Filename, timestamp and compiler profile cannot substitute for GUID+age."""
    if uuid.UUID(identity['guid']) != uuid.UUID(reference['guid']):
        return False
    if identity['age'] is None:
        raise UnsupportedPDB('equal portable GUID has no native age; investigate conversion')
    return identity['age'] == reference['age']
