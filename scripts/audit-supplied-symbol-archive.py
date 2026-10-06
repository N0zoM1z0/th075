#!/usr/bin/env python3
"""Read the supplied RAR and directory metadata for symbol-witness discovery."""
import argparse
from collections import Counter
import hashlib
import json
from pathlib import Path
import struct
import subprocess
import tempfile
import uuid
import zlib

ROOT = Path(__file__).resolve().parents[1]
ARCHIVE_SHA256 = '943590ba77a32e7d52e545370b35363bd5e9c83d49d7a8d0f0a5f0fb395fc15e'
TARGET_SHA256 = 'bd441e99075436e8dcad26f86ffcf5e6aac4f58b0ed3ee7442e4cb39d8e22c98'
GUID = '9306058f-6d68-4650-b80b-1e0d05dd1e18'
GZIP_WINDOW = 131072
PATTERNS = dict(msf7=b'Microsoft C/C++ MSF 7.00\r\n\x1aDS\0\0\0', portable=b'BSJB',
                rsds=b'RSDS', original_guid=uuid.UUID(GUID).bytes_le,
                rar3=b'Rar!\x1a\x07\x00', rar5=b'Rar!\x1a\x07\x01\x00',
                zip_local=b'PK\x03\x04', zip_end=b'PK\x05\x06',
                seven_zip=b'7z\xbc\xaf\x27\x1c', cabinet=b'MSCF', gzip=b'\x1f\x8b\x08')


def digest(raw):
    return hashlib.sha256(raw).hexdigest()


def metadata_digest(value):
    return digest(json.dumps(value, sort_keys=True, separators=(',', ':'), ensure_ascii=False).encode())


def projection(report):
    """Publish whole metadata digests, never game payload bytes or DAT filenames."""
    records = []
    for record in report['entries']:
        row = dict(member=record['member'], directory=record['directory'], size=record['size'],
                   metadata_sha256=metadata_digest(record))
        if not record['directory']:
            row.update(sha256=record['sha256'], crc=record['crc'], header_sha256=record['header_sha256'])
        if 'dat_directory' in record:
            directory = record['dat_directory']
            row['dat_directory'] = {k: directory[k] for k in ['count', 'header_size', 'encrypted_sha256', 'decoded_sha256']}
            row['dat_directory']['rows_sha256'] = metadata_digest(directory['rows'])
        records.append(row)
    return dict(archive_sha256=report['archive_sha256'], archive_size=report['archive_size'],
                entry_count=report['entry_count'], file_count=report['file_count'], directory_count=report['directory_count'],
                decompressed_bytes=report['decompressed_bytes'], entries=records,
                signature_counts={k: sum(len(r.get('hits', {}).get(k, [])) for r in report['entries']) for k in PATTERNS},
                gzip_statuses=dict(sorted(Counter(w['status'] for r in report['entries'] for w in r.get('gzip_windows', [])).items())),
                whole_report_sha256=metadata_digest(report))


def directory(prefix, physical_size):
    """TH75 hypothesis: uint16 count, rolling-XOR table, 100+4+4 byte rows."""
    if len(prefix) < 2:
        raise ValueError('missing TH75 count')
    count = struct.unpack_from('<H', prefix)[0]
    end = 2 + count * 108
    if not count or end > len(prefix) or end > physical_size:
        raise ValueError('incomplete TH75 directory')
    encrypted = prefix[2:end]
    plain = bytes(b ^ ((100 + 100*i + 77*i*(i-1)//2) & 255) for i, b in enumerate(encrypted))
    rows = []
    for i in range(count):
        row = plain[i*108:(i+1)*108]
        if b'\0' not in row[:100]:
            raise ValueError('TH75 filename lacks terminator')
        name = row[:100].split(b'\0', 1)[0]
        size, offset = struct.unpack_from('<II', row, 100)
        if not name or offset < end or offset + size > physical_size:
            raise ValueError('TH75 entry name or complete extent invalid')
        rows.append(dict(name=name.decode('cp932'), name_bytes_hex=name.hex(), size=size, offset=offset))
    ranges = sorted((r['offset'], r['offset'] + r['size']) for r in rows)
    if ranges[0][0] != end or ranges[-1][1] != physical_size or any(a[1] != b[0] for a, b in zip(ranges, ranges[1:])):
        raise ValueError('TH75 payload coverage has gaps/overlaps/trailing bytes')
    return dict(count=count, header_size=end, encrypted_sha256=digest(encrypted),
                decoded_sha256=digest(plain), rows=rows,
                limitation='Validated directory framing/ranges only; resource payload schemas are not decoded.')


def gzip_window(raw):
    try:
        decoder = zlib.decompressobj(31)
        output = decoder.decompress(raw, (1 << 20) + 1)
    except zlib.error as exc:
        return dict(status='invalid', error=str(exc), window_sha256=digest(raw))
    status = 'valid' if decoder.eof else 'output-limit-gap' if len(output) > 1 << 20 else 'incomplete-window-gap'
    return dict(status=status, window_sha256=digest(raw), output_size=len(output), output_sha256=digest(output))


def scan(stream):
    size, crc, tail, prefix = 0, 0, b'', b''
    hash_value = hashlib.sha256()
    hits = {k: [] for k in PATTERNS}
    windows = []
    keep = max(map(len, PATTERNS.values())) - 1
    for chunk in iter(lambda: stream.read(1 << 20), b''):
        if len(prefix) < 8 << 20:
            prefix = (prefix + chunk)[:8 << 20]
        for window in windows:
            start = window['offset'] + len(window['raw']) - size
            if len(window['raw']) < GZIP_WINDOW:
                window['raw'] += chunk[max(0, start):max(0, start) + GZIP_WINDOW - len(window['raw'])]
        data, base = tail + chunk, size - len(tail)
        for key, pattern in PATTERNS.items():
            at = 0
            while True:
                at = data.find(pattern, at)
                if at < 0:
                    break
                if at + len(pattern) > len(tail):
                    hits[key].append(base + at)
                    if len(hits[key]) > 4096:
                        raise ValueError('signature count exceeds bounded audit; no absence claim')
                    if key == 'gzip':
                        windows.append(dict(offset=base + at, raw=data[at:at+GZIP_WINDOW]))
                at += 1
        size += len(chunk)
        crc = zlib.crc32(chunk, crc)
        hash_value.update(chunk)
        tail = data[-keep:]
    return dict(size=size, crc=f'{crc:08X}', sha256=hash_value.hexdigest(),
                header_sha256=digest(prefix[:64]), hits=hits,
                gzip_windows=[dict(offset=w['offset'], **gzip_window(w['raw'])) for w in windows]), prefix


def listing(text):
    rows = []
    for group in text.split('----------', 1)[1].split('\n\n'):
        row = dict(line.split(' = ', 1) for line in group.splitlines() if ' = ' in line)
        if row:
            if not {'Path', 'Folder', 'Size', 'CRC'} <= row.keys() or row.get('Encrypted') != '-':
                raise ValueError('unsupported/missing archive metadata')
            rows.append(row)
    if len(rows) != 16 or len({r['Path'] for r in rows}) != 16:
        raise ValueError('whole original sixteen-entry inventory differs')
    return rows


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--archive', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--expected', type=Path)
    args = parser.parse_args()
    if not args.output.resolve().is_relative_to(ROOT / '.analysis'):
        raise ValueError('all reports must remain private under .analysis/')
    before = args.archive.stat()
    with args.archive.open('rb') as stream:
        hash_value = hashlib.sha256()
        for raw in iter(lambda: stream.read(1 << 20), b''):
            hash_value.update(raw)
    if hash_value.hexdigest() != ARCHIVE_SHA256:
        raise ValueError('supplied original archive identity differs')
    result = subprocess.run(['7z', 'l', '-slt', str(args.archive)], capture_output=True, check=True)
    entries, records = listing(result.stdout.decode('utf-8')), []
    for entry in entries:
        if entry['Folder'] == '+':
            if int(entry['Size']) != 0:
                raise ValueError('directory unexpectedly carries data')
            records.append(dict(member=entry['Path'], directory=True, size=0))
            continue
        with tempfile.TemporaryFile() as errors:
            process = subprocess.Popen(['unrar', 'p', '-idq', '-p-', '--', str(args.archive), entry['Path']], stdout=subprocess.PIPE, stderr=errors)
            try:
                record, prefix = scan(process.stdout)
            except BaseException:
                process.kill()
                process.wait()
                raise
            finally:
                process.stdout.close()
            if process.wait() != 0:
                raise ValueError('unrar extraction/CRC failed; no complete-content claim')
        if record['size'] != int(entry['Size']) or record['crc'] != entry['CRC']:
            raise ValueError('whole decompressed entry size/CRC differs')
        record.update(member=entry['Path'], directory=False)
        if Path(entry['Path']).name in ['th075.dat', 'th075bgm.dat', 'th075b.dat', 'th075c.dat']:
            record['dat_directory'] = directory(prefix, record['size'])
        records.append(record)
        print('Entry verified:', Path(entry['Path']).name, record['size'], flush=True)
    japanese = [r for r in records if Path(r['member']).name == 'th075.exe']
    if len(japanese) != 1 or japanese[0]['sha256'] != TARGET_SHA256:
        raise ValueError('Japanese target archive member differs; no substitution allowed')
    after = args.archive.stat()
    if (before.st_dev, before.st_ino, before.st_size, before.st_mtime_ns) != (after.st_dev, after.st_ino, after.st_size, after.st_mtime_ns):
        raise ValueError('original archive changed during audit')
    report = dict(evidence_id='R268', archive_sha256=ARCHIVE_SHA256, archive_size=after.st_size,
                  entry_count=len(records), file_count=sum(not r['directory'] for r in records),
                  directory_count=sum(r['directory'] for r in records), decompressed_bytes=sum(r['size'] for r in records),
                  entries=records, patterns={k: v.hex() for k, v in PATTERNS.items()},
                  limitation='Complete outer streams and DAT directories only; arbitrary inner resource schemas/encoding remain unknown. No foreign reconstruction target or ownership/exact credit.')
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2, ensure_ascii=False) + '\n')
    if args.expected:
        expected = json.loads(args.expected.read_text())
        if projection(report) != expected['archive_projection']:
            raise ValueError('frozen complete R268 archive/directory/signature witness differs')
    print('Archive audit OK:', report['file_count'], 'files;', report['decompressed_bytes'], 'whole decompressed bytes.')
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
