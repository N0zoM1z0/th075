#ifndef TH075_AUDIO_STREAM_HPP
#define TH075_AUDIO_STREAM_HPP
#include <windows.h>

struct IDirectSoundBuffer8;

// One streamed music track: a DirectSound buffer refilled half at a time
// from a file or archive entry, with optional loop points and a volume fade.
// The music queue keeps these by value.
class AudioStream {
public:
    AudioStream();                                                  // 00409290
    ~AudioStream();                                                 // 004092F0
    void OpenFile(const char* filename, DWORD flags);               // 00408110
    void OpenArchiveEntry(const char* name, DWORD flags, const char* archive);  // 00408390
    void ReadLoopPointsFromFile(const char* filename);              // 00408670
    void ReadLoopPointsFromArchive(const char* name, const char* archive);      // 00408900
    void Refill(DWORD bytes);                                       // 00408BD0

    IDirectSoundBuffer8* buffer;        // +0x00
    DWORD field004;                     // +0x04
    DWORD bufferBytes;                  // +0x08 0 when nothing is loaded
    DWORD dataBegin;                    // +0x0C
    DWORD dataEnd;                      // +0x10
    DWORD nextFilePosition;             // +0x14
    DWORD activeHalf;                   // +0x18 which half of the buffer plays
    DWORD halfBoundary;                 // +0x1C
    DWORD loopEnd;                      // +0x20
    DWORD loopLength;                   // +0x24
    DWORD loopEnabled;                  // +0x28
    LONG volume;                        // +0x2C current volume (DirectSound hundredths of dB)
    LONG fadeLimit;                     // +0x30 volume the fade stops at
    LONG fadeStep;                      // +0x34 per-tick change, negative to fade out
    BYTE field038;                      // +0x38
    BYTE field039;                      // +0x39
    BYTE archiveMode;                   // +0x3A read from an archive rather than a file
    BYTE unknown03B;
    HANDLE file;                        // +0x3C
};
#endif
