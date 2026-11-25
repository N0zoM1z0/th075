#include "audio/AudioStream.hpp"
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <string.h>

// A separate pointer-only view preserves all accepted input declarations.
// Never instantiate or embed this incomplete owner.
extern BYTE archiveReadRequested;
extern BYTE archiveReadActive;

void AudioStream::Refill(DWORD count) {
    DWORD writeCursor;
    DWORD readBytes;
    if (file == 0)
        return;
    buffer->GetCurrentPosition(0, &writeCursor);
    if (loopEnabled == 0 && nextFilePosition > dataEnd) {
        if (nextRefillOffset < lastRefillOffset) {
            if (writeCursor > nextRefillOffset && writeCursor < lastRefillOffset)
                buffer->Stop();
        } else {
            if (writeCursor > nextRefillOffset)
                buffer->Stop();
        }
    }
    if (writeCursor > lastRefillOffset &&
        writeCursor < (nextRefillOffset < lastRefillOffset) * bufferBytes + nextRefillOffset) {
        HANDLE event = CreateEventA(0, 0, 0, 0);
        while (archiveReadRequested)
            WaitForSingleObject(event, 20);
        CloseHandle(event);
        archiveReadActive = 1;
        if (loopEnabled == 0) {
            void* firstRegion;
            void* buffer2;
            DWORD firstBytes;
            DWORD regionSize2;
            buffer->Lock(nextRefillOffset, count, &firstRegion, &firstBytes,
                                &buffer2, &regionSize2, DSBLOCK_ENTIREBUFFER);
            SetFilePointer(file, nextFilePosition, 0, FILE_BEGIN);
            if (nextFilePosition + count >= dataEnd) {
                if (nextFilePosition < dataEnd) {
                    DWORD overflow = nextFilePosition + count - dataEnd;
                    ReadFile(file, firstRegion, count - overflow, &readBytes, 0);
                    memset(static_cast<char*>(firstRegion) + count - overflow, 0, overflow);
                    lastRefillOffset = nextRefillOffset;
                    nextRefillOffset += overflow;
                    if (lastRefillOffset >= bufferBytes)
                        lastRefillOffset -= bufferBytes;
                    if (nextRefillOffset >= bufferBytes)
                        nextRefillOffset -= bufferBytes;
                    nextFilePosition += count;
                }
            } else {
                ReadFile(file, firstRegion, count, &readBytes, 0);
                lastRefillOffset = nextRefillOffset;
                nextRefillOffset += count;
                if (lastRefillOffset >= bufferBytes)
                    lastRefillOffset -= bufferBytes;
                if (nextRefillOffset >= bufferBytes)
                    nextRefillOffset -= bufferBytes;
                nextFilePosition += count;
            }
            buffer->Unlock(firstRegion, firstBytes, buffer2, regionSize2);
        } else if (loopEnd > 0) {
            void* firstRegion;
            void* buffer2;
            DWORD firstBytes;
            DWORD regionSize2;
            buffer->Lock(nextRefillOffset, count, &firstRegion, &firstBytes,
                                &buffer2, &regionSize2, DSBLOCK_ENTIREBUFFER);
            SetFilePointer(file, nextFilePosition, 0, FILE_BEGIN);
            if (nextFilePosition + count >= dataBegin + loopEnd) {
                DWORD overflow = nextFilePosition + count - (dataBegin + loopEnd);
                ReadFile(file, firstRegion, count - overflow, &readBytes, 0);
                SetFilePointer(file, dataBegin + loopEnd - loopLength, 0, FILE_BEGIN);
                ReadFile(file, static_cast<char*>(firstRegion) + count - overflow, overflow, &readBytes, 0);
                nextFilePosition = count - loopLength + nextFilePosition;
                lastRefillOffset = nextRefillOffset;
                nextRefillOffset += count;
                if (lastRefillOffset >= bufferBytes)
                    lastRefillOffset -= bufferBytes;
                if (nextRefillOffset >= bufferBytes)
                    nextRefillOffset -= bufferBytes;
            } else {
                ReadFile(file, firstRegion, count, &readBytes, 0);
                lastRefillOffset = nextRefillOffset;
                nextRefillOffset += count;
                if (lastRefillOffset >= bufferBytes)
                    lastRefillOffset -= bufferBytes;
                if (nextRefillOffset >= bufferBytes)
                    nextRefillOffset -= bufferBytes;
                nextFilePosition += count;
            }
            buffer->Unlock(firstRegion, firstBytes, buffer2, regionSize2);
        } else {
            void* firstRegion;
            void* buffer2;
            DWORD firstBytes;
            DWORD regionSize2;
            buffer->Lock(nextRefillOffset, count, &firstRegion, &firstBytes,
                                &buffer2, &regionSize2, DSBLOCK_ENTIREBUFFER);
            SetFilePointer(file, nextFilePosition, 0, FILE_BEGIN);
            if (nextFilePosition + count >= dataEnd) {
                DWORD overflow = nextFilePosition + count - dataEnd;
                ReadFile(file, firstRegion, count - overflow, &readBytes, 0);
                ReadFile(file, static_cast<char*>(firstRegion) + count - overflow, overflow, &readBytes, 0);
                lastRefillOffset = nextRefillOffset;
                nextRefillOffset += count;
                if (lastRefillOffset >= bufferBytes)
                    lastRefillOffset -= bufferBytes;
                if (nextRefillOffset >= bufferBytes)
                    nextRefillOffset -= bufferBytes;
                nextFilePosition = count - dataEnd + nextFilePosition;
            } else {
                ReadFile(file, firstRegion, count, &readBytes, 0);
                lastRefillOffset = nextRefillOffset;
                nextRefillOffset += count;
                if (lastRefillOffset >= bufferBytes)
                    lastRefillOffset -= bufferBytes;
                if (nextRefillOffset >= bufferBytes)
                    nextRefillOffset -= bufferBytes;
                nextFilePosition += count;
            }
            buffer->Unlock(firstRegion, firstBytes, buffer2, regionSize2);
        }
        archiveReadActive = 0;
    }
}
