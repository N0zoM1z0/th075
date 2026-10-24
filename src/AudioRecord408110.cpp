#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <new>
#include <string.h>

// Partial interfaces and field views only; never instantiate these owners.
class AudioStreamRecord408110 {
public:
    void OpenFile(const char*, DWORD);
    void OpenArchiveEntry(const char*, DWORD, const char*);
    void ReadLoopPointsFromFile(const char*);
    void ReadLoopPointsFromArchive(const char*, const char*);
};
class ArchiveContextWithSize41D800 {
public:
    HANDLE Seek(const char*, DWORD*);
};
class ArchiveContextWithoutSize41D750 {
public:
    HANDLE Seek(const char*);
};
namespace SizedArchiveLookup41CF00 {
    ArchiveContextWithSize41D800* __cdecl Find(const char*);
}
namespace SoundArchiveLookup41CF00 {
    ArchiveContextWithoutSize41D750* __cdecl Find(const char*);
}
namespace SoundCreation406A20 {
    bool __cdecl Create(const WAVEFORMATEX*, const void*, DWORD, IDirectSoundBuffer8**, DWORD);
}
extern BYTE archiveReadRequested;
extern BYTE archiveReadActive;
typedef char WaveFormatSize[(sizeof(WAVEFORMATEX) == 18) ? 1 : -1];
#define STREAM_FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<char*>(this) + offset))
#define STREAM_BUFFER STREAM_FIELD(IDirectSoundBuffer8*, 0)
#define BUFFER_BYTES STREAM_FIELD(DWORD, 8)
#define DATA_BEGIN STREAM_FIELD(DWORD, 12)
#define DATA_END STREAM_FIELD(DWORD, 16)
#define NEXT_FILE_POSITION STREAM_FIELD(DWORD, 20)
#define ACTIVE_HALF STREAM_FIELD(DWORD, 24)
#define HALF_BOUNDARY STREAM_FIELD(DWORD, 28)
#define LOOP_END STREAM_FIELD(DWORD, 32)
#define LOOP_LENGTH STREAM_FIELD(DWORD, 36)
#define ARCHIVE_MODE STREAM_FIELD(BYTE, 58)
#define STREAM_FILE STREAM_FIELD(HANDLE, 60)
#define LOOP_VALUE_AT(i) (static_cast<DWORD>(buffer[(i) + 16]) + \
    (static_cast<DWORD>(buffer[(i) + 17]) << 8) + \
    (static_cast<DWORD>(buffer[(i) + 18]) << 8 << 8) + \
    (static_cast<DWORD>(buffer[(i) + 19]) << 8 << 8 << 8))

void AudioStreamRecord408110::OpenFile(const char* filename, DWORD bufferBytes) {
    DWORD formatSize;
    DWORD readBytes;
    WAVEFORMATEX format;
    if (STREAM_FILE) {
        CloseHandle(STREAM_FILE);
        STREAM_FILE = 0;
    }
    STREAM_FILE = CreateFileA(filename, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (STREAM_FILE == INVALID_HANDLE_VALUE)
        return;
    ARCHIVE_MODE = 0;
    SetFilePointer(STREAM_FILE, 16, 0, FILE_BEGIN);
    ReadFile(STREAM_FILE, &formatSize, 4, &readBytes, 0);
    ReadFile(STREAM_FILE, &format, sizeof(format), &readBytes, 0);
    DATA_BEGIN = SetFilePointer(STREAM_FILE, formatSize + 24, 0, FILE_BEGIN);
    ReadFile(STREAM_FILE, &DATA_END, 4, &readBytes, 0);
    DATA_BEGIN = SetFilePointer(STREAM_FILE, formatSize + 28, 0, FILE_BEGIN);
    DATA_END += DATA_BEGIN;
    BUFFER_BYTES = bufferBytes;
    if (BUFFER_BYTES > DATA_END - DATA_BEGIN)
        BUFFER_BYTES = 0;
    if (BUFFER_BYTES == 0) {
        char* data = new char[DATA_END - DATA_BEGIN];
        ReadFile(STREAM_FILE, data, DATA_END - DATA_BEGIN, &readBytes, 0);
        SoundCreation406A20::Create(&format, data, DATA_END - DATA_BEGIN,
            reinterpret_cast<IDirectSoundBuffer8**>(this), 0);
        delete[] data;
    } else {
        void* firstRegion;
        void* buffer2;
        DWORD firstBytes;
        DWORD regionSize2;
        SoundCreation406A20::Create(&format, 0, BUFFER_BYTES,
            reinterpret_cast<IDirectSoundBuffer8**>(this), 0);
        STREAM_BUFFER->Lock(0, BUFFER_BYTES >> 1, &firstRegion, &firstBytes,
                            &buffer2, &regionSize2, DSBLOCK_ENTIREBUFFER);
        ReadFile(STREAM_FILE, firstRegion, BUFFER_BYTES >> 1, &readBytes, 0);
        ACTIVE_HALF = 0;
        HALF_BOUNDARY = BUFFER_BYTES >> 1;
        NEXT_FILE_POSITION = HALF_BOUNDARY + DATA_BEGIN;
        STREAM_BUFFER->Unlock(firstRegion, firstBytes, buffer2, regionSize2);
    }
}

void AudioStreamRecord408110::OpenArchiveEntry(const char* filename, DWORD bufferBytes, const char* archive) {
    DWORD formatSize;
    DWORD readBytes;
    WAVEFORMATEX format;
    HANDLE waitEvent = CreateEventA(0, 0, 0, 0);
    while (archiveReadActive)
        WaitForSingleObject(waitEvent, 20);
    CloseHandle(waitEvent);
    archiveReadRequested = 1;
    STREAM_FILE = SoundArchiveLookup41CF00::Find(archive)->Seek(filename);
    if (STREAM_FILE == INVALID_HANDLE_VALUE) {
        archiveReadRequested = 0;
        return;
    }
    ARCHIVE_MODE = 1;
    DWORD dataOffset = SetFilePointer(STREAM_FILE, 0, 0, FILE_CURRENT);
    SetFilePointer(STREAM_FILE, 16, 0, FILE_CURRENT);
    ReadFile(STREAM_FILE, &formatSize, 4, &readBytes, 0);
    ReadFile(STREAM_FILE, &format, sizeof(format), &readBytes, 0);
    SetFilePointer(STREAM_FILE, dataOffset, 0, FILE_BEGIN);
    DATA_BEGIN = SetFilePointer(STREAM_FILE, formatSize + 24, 0, FILE_CURRENT);
    ReadFile(STREAM_FILE, &DATA_END, 4, &readBytes, 0);
    SetFilePointer(STREAM_FILE, dataOffset, 0, FILE_BEGIN);
    DATA_BEGIN = SetFilePointer(STREAM_FILE, formatSize + 28, 0, FILE_CURRENT);
    DATA_END += DATA_BEGIN;
    BUFFER_BYTES = bufferBytes;
    if (BUFFER_BYTES > DATA_END - DATA_BEGIN)
        BUFFER_BYTES = 0;
    if (BUFFER_BYTES == 0) {
        char* data = new char[DATA_END - DATA_BEGIN];
        ReadFile(STREAM_FILE, data, DATA_END - DATA_BEGIN, &readBytes, 0);
        SoundCreation406A20::Create(&format, data, DATA_END - DATA_BEGIN,
            reinterpret_cast<IDirectSoundBuffer8**>(this), 0);
        delete[] data;
    } else {
        void* firstRegion;
        void* buffer2;
        DWORD firstBytes;
        DWORD regionSize2;
        SoundCreation406A20::Create(&format, 0, BUFFER_BYTES,
            reinterpret_cast<IDirectSoundBuffer8**>(this), 0);
        STREAM_BUFFER->Lock(0, BUFFER_BYTES >> 1, &firstRegion, &firstBytes,
                            &buffer2, &regionSize2, DSBLOCK_ENTIREBUFFER);
        ReadFile(STREAM_FILE, firstRegion, BUFFER_BYTES >> 1, &readBytes, 0);
        ACTIVE_HALF = 0;
        HALF_BOUNDARY = BUFFER_BYTES >> 1;
        NEXT_FILE_POSITION = HALF_BOUNDARY + DATA_BEGIN;
        STREAM_BUFFER->Unlock(firstRegion, firstBytes, buffer2, regionSize2);
    }
    archiveReadRequested = 0;
}

void AudioStreamRecord408110::ReadLoopPointsFromFile(const char* filename) {
    DWORD cuePoint = 0;
    DWORD duration = 0;
    HANDLE file;
    DWORD dwRead;
    BYTE buffer[320];
    while (archiveReadActive) {}
    archiveReadRequested = 1;
    file = CreateFileA(filename, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (file == INVALID_HANDLE_VALUE || GetFileSize(file, 0) == 0) {
        LOOP_END = 0;
        LOOP_LENGTH = 0;
        archiveReadRequested = 0;
        return;
    }
    DWORD size = GetFileSize(file, 0);
    SetFilePointer(file, -320, 0, FILE_END);
    ReadFile(file, buffer, sizeof(buffer), &dwRead, 0);
    CloseHandle(file);
    archiveReadRequested = 0;
    for (int i = 0; i < 320; i++) {
        if (buffer[i] == 'c' && buffer[i + 1] == 'u' && buffer[i + 2] == 'e') {
            cuePoint = LOOP_VALUE_AT(i);
        } else if (buffer[i] == 'a' && buffer[i + 1] == 'd' && buffer[i + 2] == 't' && buffer[i + 3] == 'l') {
            duration = LOOP_VALUE_AT(i);
        }
    }
    if (cuePoint == 0 || duration == 0)
        return;
    LOOP_END = (cuePoint + duration) << 2;
    LOOP_LENGTH = duration << 2;
}

void AudioStreamRecord408110::ReadLoopPointsFromArchive(const char* filename, const char* archive) {
    if (strcmp(filename, "wave\\bgm\\59.wav") == 0) {
        LOOP_END = 0x60e8ac;
        LOOP_LENGTH = 0x5e0d90;
        return;
    }
    DWORD cuePoint = 0;
    DWORD duration = 0;
    DWORD size;
    DWORD dwRead;
    BYTE buffer[320];
    HANDLE hWaitEvent = CreateEventA(0, 0, 0, 0);
    while (archiveReadActive)
        WaitForSingleObject(hWaitEvent, 20);
    CloseHandle(hWaitEvent);
    archiveReadRequested = 1;
    HANDLE sourceFile = SizedArchiveLookup41CF00::Find(archive)->Seek(filename, &size);
    if (sourceFile == INVALID_HANDLE_VALUE || GetFileSize(sourceFile, 0) == 0) {
        LOOP_END = 0;
        LOOP_LENGTH = 0;
        archiveReadRequested = 0;
        return;
    }
    SetFilePointer(sourceFile, size - sizeof(buffer), 0, FILE_CURRENT);
    ReadFile(sourceFile, buffer, sizeof(buffer), &dwRead, 0);
    archiveReadRequested = 0;
    for (int i = 0; i < 320; i++) {
        if (buffer[i] == 'c' && buffer[i + 1] == 'u' && buffer[i + 2] == 'e') {
            cuePoint = LOOP_VALUE_AT(i);
        } else if (buffer[i] == 'a' && buffer[i + 1] == 'd' && buffer[i + 2] == 't' && buffer[i + 3] == 'l') {
            duration = LOOP_VALUE_AT(i);
        }
    }
    if (cuePoint == 0 || duration == 0)
        return;
    LOOP_END = (cuePoint + duration) << 2;
    LOOP_LENGTH = duration << 2;
}

#undef LOOP_VALUE_AT
#undef STREAM_FILE
#undef ARCHIVE_MODE
#undef LOOP_LENGTH
#undef LOOP_END
#undef HALF_BOUNDARY
#undef ACTIVE_HALF
#undef NEXT_FILE_POSITION
#undef DATA_END
#undef DATA_BEGIN
#undef BUFFER_BYTES
#undef STREAM_BUFFER
#undef STREAM_FIELD
