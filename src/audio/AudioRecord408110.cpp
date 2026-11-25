#include "assets/ArchiveCatalog.hpp"
#include "assets/DataArchive.hpp"
#include "audio/AudioStream.hpp"
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <new>
#include <string.h>

// Partial interfaces and field views only; never instantiate these owners.
namespace SoundCreation406A20 {
    bool __cdecl Create(const WAVEFORMATEX*, const void*, DWORD, IDirectSoundBuffer8**, DWORD);
}
BYTE archiveReadRequested;
BYTE archiveReadActive;
typedef char WaveFormatSize[(sizeof(WAVEFORMATEX) == 18) ? 1 : -1];
#define LOOP_VALUE_AT(i) (static_cast<DWORD>(header[(i) + 16]) + \
    (static_cast<DWORD>(header[(i) + 17]) << 8) + \
    (static_cast<DWORD>(header[(i) + 18]) << 8 << 8) + \
    (static_cast<DWORD>(header[(i) + 19]) << 8 << 8 << 8))

void AudioStream::OpenFile(const char* filename, DWORD requestedBytes) {
    DWORD formatSize;
    DWORD readBytes;
    WAVEFORMATEX format;
    if (file) {
        CloseHandle(file);
        file = 0;
    }
    file = CreateFileA(filename, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (file == INVALID_HANDLE_VALUE)
        return;
    archiveMode = 0;
    SetFilePointer(file, 16, 0, FILE_BEGIN);
    ReadFile(file, &formatSize, 4, &readBytes, 0);
    ReadFile(file, &format, sizeof(format), &readBytes, 0);
    dataBegin = SetFilePointer(file, formatSize + 24, 0, FILE_BEGIN);
    ReadFile(file, &dataEnd, 4, &readBytes, 0);
    dataBegin = SetFilePointer(file, formatSize + 28, 0, FILE_BEGIN);
    dataEnd += dataBegin;
    bufferBytes = requestedBytes;
    if (bufferBytes > dataEnd - dataBegin)
        bufferBytes = 0;
    if (bufferBytes == 0) {
        char* data = new char[dataEnd - dataBegin];
        ReadFile(file, data, dataEnd - dataBegin, &readBytes, 0);
        SoundCreation406A20::Create(&format, data, dataEnd - dataBegin,
            reinterpret_cast<IDirectSoundBuffer8**>(this), 0);
        delete[] data;
    } else {
        void* firstRegion;
        void* buffer2;
        DWORD firstBytes;
        DWORD regionSize2;
        SoundCreation406A20::Create(&format, 0, bufferBytes,
            reinterpret_cast<IDirectSoundBuffer8**>(this), 0);
        buffer->Lock(0, bufferBytes >> 1, &firstRegion, &firstBytes,
                            &buffer2, &regionSize2, DSBLOCK_ENTIREBUFFER);
        ReadFile(file, firstRegion, bufferBytes >> 1, &readBytes, 0);
        activeHalf = 0;
        halfBoundary = bufferBytes >> 1;
        nextFilePosition = halfBoundary + dataBegin;
        buffer->Unlock(firstRegion, firstBytes, buffer2, regionSize2);
    }
}

void AudioStream::OpenArchiveEntry(const char* filename, DWORD requestedBytes, const char* archive) {
    DWORD formatSize;
    DWORD readBytes;
    WAVEFORMATEX format;
    HANDLE waitEvent = CreateEventA(0, 0, 0, 0);
    while (archiveReadActive)
        WaitForSingleObject(waitEvent, 20);
    CloseHandle(waitEvent);
    archiveReadRequested = 1;
    file = ResourceLookupF217::FindByName(archive)->SeekNamedEntry(filename);
    if (file == INVALID_HANDLE_VALUE) {
        archiveReadRequested = 0;
        return;
    }
    archiveMode = 1;
    DWORD dataOffset = SetFilePointer(file, 0, 0, FILE_CURRENT);
    SetFilePointer(file, 16, 0, FILE_CURRENT);
    ReadFile(file, &formatSize, 4, &readBytes, 0);
    ReadFile(file, &format, sizeof(format), &readBytes, 0);
    SetFilePointer(file, dataOffset, 0, FILE_BEGIN);
    dataBegin = SetFilePointer(file, formatSize + 24, 0, FILE_CURRENT);
    ReadFile(file, &dataEnd, 4, &readBytes, 0);
    SetFilePointer(file, dataOffset, 0, FILE_BEGIN);
    dataBegin = SetFilePointer(file, formatSize + 28, 0, FILE_CURRENT);
    dataEnd += dataBegin;
    bufferBytes = requestedBytes;
    if (bufferBytes > dataEnd - dataBegin)
        bufferBytes = 0;
    if (bufferBytes == 0) {
        char* data = new char[dataEnd - dataBegin];
        ReadFile(file, data, dataEnd - dataBegin, &readBytes, 0);
        SoundCreation406A20::Create(&format, data, dataEnd - dataBegin,
            reinterpret_cast<IDirectSoundBuffer8**>(this), 0);
        delete[] data;
    } else {
        void* firstRegion;
        void* buffer2;
        DWORD firstBytes;
        DWORD regionSize2;
        SoundCreation406A20::Create(&format, 0, bufferBytes,
            reinterpret_cast<IDirectSoundBuffer8**>(this), 0);
        buffer->Lock(0, bufferBytes >> 1, &firstRegion, &firstBytes,
                            &buffer2, &regionSize2, DSBLOCK_ENTIREBUFFER);
        ReadFile(file, firstRegion, bufferBytes >> 1, &readBytes, 0);
        activeHalf = 0;
        halfBoundary = bufferBytes >> 1;
        nextFilePosition = halfBoundary + dataBegin;
        buffer->Unlock(firstRegion, firstBytes, buffer2, regionSize2);
    }
    archiveReadRequested = 0;
}

void AudioStream::ReadLoopPointsFromFile(const char* filename) {
    DWORD cuePoint = 0;
    DWORD duration = 0;
    HANDLE loopFile;
    DWORD dwRead;
    BYTE header[320];
    while (archiveReadActive) {}
    archiveReadRequested = 1;
    loopFile = CreateFileA(filename, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (loopFile == INVALID_HANDLE_VALUE || GetFileSize(loopFile, 0) == 0) {
        loopEnd = 0;
        loopLength = 0;
        archiveReadRequested = 0;
        return;
    }
    DWORD size = GetFileSize(loopFile, 0);
    SetFilePointer(loopFile, -320, 0, FILE_END);
    ReadFile(loopFile, header, sizeof(header), &dwRead, 0);
    CloseHandle(loopFile);
    archiveReadRequested = 0;
    for (int i = 0; i < 320; i++) {
        if (header[i] == 'c' && header[i + 1] == 'u' && header[i + 2] == 'e') {
            cuePoint = LOOP_VALUE_AT(i);
        } else if (header[i] == 'a' && header[i + 1] == 'd' && header[i + 2] == 't' && header[i + 3] == 'l') {
            duration = LOOP_VALUE_AT(i);
        }
    }
    if (cuePoint == 0 || duration == 0)
        return;
    loopEnd = (cuePoint + duration) << 2;
    loopLength = duration << 2;
}

void AudioStream::ReadLoopPointsFromArchive(const char* filename, const char* archive) {
    if (strcmp(filename, "wave\\bgm\\59.wav") == 0) {
        loopEnd = 0x60e8ac;
        loopLength = 0x5e0d90;
        return;
    }
    DWORD cuePoint = 0;
    DWORD duration = 0;
    DWORD size;
    DWORD dwRead;
    BYTE header[320];
    HANDLE hWaitEvent = CreateEventA(0, 0, 0, 0);
    while (archiveReadActive)
        WaitForSingleObject(hWaitEvent, 20);
    CloseHandle(hWaitEvent);
    archiveReadRequested = 1;
    HANDLE sourceFile = ResourceLookupF217::FindByName(archive)->SeekNamedEntryWithSize(filename, &size);
    if (sourceFile == INVALID_HANDLE_VALUE || GetFileSize(sourceFile, 0) == 0) {
        loopEnd = 0;
        loopLength = 0;
        archiveReadRequested = 0;
        return;
    }
    SetFilePointer(sourceFile, size - sizeof(header), 0, FILE_CURRENT);
    ReadFile(sourceFile, header, sizeof(header), &dwRead, 0);
    archiveReadRequested = 0;
    for (int i = 0; i < 320; i++) {
        if (header[i] == 'c' && header[i + 1] == 'u' && header[i + 2] == 'e') {
            cuePoint = LOOP_VALUE_AT(i);
        } else if (header[i] == 'a' && header[i + 1] == 'd' && header[i + 2] == 't' && header[i + 3] == 'l') {
            duration = LOOP_VALUE_AT(i);
        }
    }
    if (cuePoint == 0 || duration == 0)
        return;
    loopEnd = (cuePoint + duration) << 2;
    loopLength = duration << 2;
}

#undef LOOP_VALUE_AT
