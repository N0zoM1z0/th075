#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <string.h>

// A separate pointer-only view preserves all accepted input declarations.
// Never instantiate or embed this incomplete owner.
class AudioStreamRefill408BD0 {
public:
    void Refill(DWORD);
};
extern BYTE archiveReadRequested;
extern BYTE archiveReadActive;
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
#define LOOP_ENABLED STREAM_FIELD(DWORD, 40)
#define STREAM_FILE STREAM_FIELD(HANDLE, 60)

void AudioStreamRefill408BD0::Refill(DWORD count) {
    DWORD position;
    DWORD readBytes;
    if (STREAM_FILE == 0)
        return;
    STREAM_BUFFER->GetCurrentPosition(0, &position);
    if (LOOP_ENABLED == 0 && NEXT_FILE_POSITION > DATA_END) {
        if (HALF_BOUNDARY < ACTIVE_HALF) {
            if (position > HALF_BOUNDARY && position < ACTIVE_HALF)
                STREAM_BUFFER->Stop();
        } else {
            if (position > HALF_BOUNDARY)
                STREAM_BUFFER->Stop();
        }
    }
    if (position > ACTIVE_HALF &&
        position < (HALF_BOUNDARY < ACTIVE_HALF) * BUFFER_BYTES + HALF_BOUNDARY) {
        HANDLE event = CreateEventA(0, 0, 0, 0);
        while (archiveReadRequested)
            WaitForSingleObject(event, 20);
        CloseHandle(event);
        archiveReadActive = 1;
        if (LOOP_ENABLED == 0) {
            void* firstRegion;
            void* buffer2;
            DWORD firstBytes;
            DWORD regionSize2;
            STREAM_BUFFER->Lock(HALF_BOUNDARY, count, &firstRegion, &firstBytes,
                                &buffer2, &regionSize2, DSBLOCK_ENTIREBUFFER);
            SetFilePointer(STREAM_FILE, NEXT_FILE_POSITION, 0, FILE_BEGIN);
            if (NEXT_FILE_POSITION + count >= DATA_END) {
                if (NEXT_FILE_POSITION < DATA_END) {
                    DWORD overflow = NEXT_FILE_POSITION + count - DATA_END;
                    ReadFile(STREAM_FILE, firstRegion, count - overflow, &readBytes, 0);
                    memset(static_cast<char*>(firstRegion) + count - overflow, 0, overflow);
                    ACTIVE_HALF = HALF_BOUNDARY;
                    HALF_BOUNDARY += overflow;
                    if (ACTIVE_HALF >= BUFFER_BYTES)
                        ACTIVE_HALF -= BUFFER_BYTES;
                    if (HALF_BOUNDARY >= BUFFER_BYTES)
                        HALF_BOUNDARY -= BUFFER_BYTES;
                    NEXT_FILE_POSITION += count;
                }
            } else {
                ReadFile(STREAM_FILE, firstRegion, count, &readBytes, 0);
                ACTIVE_HALF = HALF_BOUNDARY;
                HALF_BOUNDARY += count;
                if (ACTIVE_HALF >= BUFFER_BYTES)
                    ACTIVE_HALF -= BUFFER_BYTES;
                if (HALF_BOUNDARY >= BUFFER_BYTES)
                    HALF_BOUNDARY -= BUFFER_BYTES;
                NEXT_FILE_POSITION += count;
            }
            STREAM_BUFFER->Unlock(firstRegion, firstBytes, buffer2, regionSize2);
        } else if (LOOP_END > 0) {
            void* firstRegion;
            void* buffer2;
            DWORD firstBytes;
            DWORD regionSize2;
            STREAM_BUFFER->Lock(HALF_BOUNDARY, count, &firstRegion, &firstBytes,
                                &buffer2, &regionSize2, DSBLOCK_ENTIREBUFFER);
            SetFilePointer(STREAM_FILE, NEXT_FILE_POSITION, 0, FILE_BEGIN);
            if (NEXT_FILE_POSITION + count >= DATA_BEGIN + LOOP_END) {
                DWORD overflow = NEXT_FILE_POSITION + count - (DATA_BEGIN + LOOP_END);
                ReadFile(STREAM_FILE, firstRegion, count - overflow, &readBytes, 0);
                SetFilePointer(STREAM_FILE, DATA_BEGIN + LOOP_END - LOOP_LENGTH, 0, FILE_BEGIN);
                ReadFile(STREAM_FILE, static_cast<char*>(firstRegion) + count - overflow, overflow, &readBytes, 0);
                NEXT_FILE_POSITION = count - LOOP_LENGTH + NEXT_FILE_POSITION;
                ACTIVE_HALF = HALF_BOUNDARY;
                HALF_BOUNDARY += count;
                if (ACTIVE_HALF >= BUFFER_BYTES)
                    ACTIVE_HALF -= BUFFER_BYTES;
                if (HALF_BOUNDARY >= BUFFER_BYTES)
                    HALF_BOUNDARY -= BUFFER_BYTES;
            } else {
                ReadFile(STREAM_FILE, firstRegion, count, &readBytes, 0);
                ACTIVE_HALF = HALF_BOUNDARY;
                HALF_BOUNDARY += count;
                if (ACTIVE_HALF >= BUFFER_BYTES)
                    ACTIVE_HALF -= BUFFER_BYTES;
                if (HALF_BOUNDARY >= BUFFER_BYTES)
                    HALF_BOUNDARY -= BUFFER_BYTES;
                NEXT_FILE_POSITION += count;
            }
            STREAM_BUFFER->Unlock(firstRegion, firstBytes, buffer2, regionSize2);
        } else {
            void* firstRegion;
            void* buffer2;
            DWORD firstBytes;
            DWORD regionSize2;
            STREAM_BUFFER->Lock(HALF_BOUNDARY, count, &firstRegion, &firstBytes,
                                &buffer2, &regionSize2, DSBLOCK_ENTIREBUFFER);
            SetFilePointer(STREAM_FILE, NEXT_FILE_POSITION, 0, FILE_BEGIN);
            if (NEXT_FILE_POSITION + count >= DATA_END) {
                DWORD overflow = NEXT_FILE_POSITION + count - DATA_END;
                ReadFile(STREAM_FILE, firstRegion, count - overflow, &readBytes, 0);
                ReadFile(STREAM_FILE, static_cast<char*>(firstRegion) + count - overflow, overflow, &readBytes, 0);
                ACTIVE_HALF = HALF_BOUNDARY;
                HALF_BOUNDARY += count;
                if (ACTIVE_HALF >= BUFFER_BYTES)
                    ACTIVE_HALF -= BUFFER_BYTES;
                if (HALF_BOUNDARY >= BUFFER_BYTES)
                    HALF_BOUNDARY -= BUFFER_BYTES;
                NEXT_FILE_POSITION = count - DATA_END + NEXT_FILE_POSITION;
            } else {
                ReadFile(STREAM_FILE, firstRegion, count, &readBytes, 0);
                ACTIVE_HALF = HALF_BOUNDARY;
                HALF_BOUNDARY += count;
                if (ACTIVE_HALF >= BUFFER_BYTES)
                    ACTIVE_HALF -= BUFFER_BYTES;
                if (HALF_BOUNDARY >= BUFFER_BYTES)
                    HALF_BOUNDARY -= BUFFER_BYTES;
                NEXT_FILE_POSITION += count;
            }
            STREAM_BUFFER->Unlock(firstRegion, firstBytes, buffer2, regionSize2);
        }
        archiveReadActive = 0;
    }
}

#undef STREAM_FILE
#undef LOOP_ENABLED
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
