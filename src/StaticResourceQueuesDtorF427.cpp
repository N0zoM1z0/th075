#include <windows.h>
#include "ReplaySegmentedQueueF219.hpp"

// The static replay owner carries the same typed file/header/segmented-queue
// layout as the record reader/writer. Member destruction remains compiler
// managed in reverse declaration order under the original /GX profile.
class ByteQueueF426 : public ReplaySegmentedQueueStorageF219<char> {
public: ByteQueueF426(); ~ByteQueueF426();
};
class WordQueueF426 : public ReplaySegmentedQueueStorageF219<short> {
public: WordQueueF426(); ~WordQueueF426();
};
class DwordQueueF426 : public ReplaySegmentedQueueStorageF219<unsigned int> {
public: DwordQueueF426(); ~DwordQueueF426();
};
class StaticResourceQueueF426 {
    HANDLE fileHandle;
    char filePath[0x112];
    signed char field116;
    unsigned char unknown117[5];
    DWORD recordOffsets[10];
    ReplayRecordHeaderF219 header;
    ByteQueueF426 first;
    WordQueueF426 second;
    ByteQueueF426 third;
    DwordQueueF426 fourth;
public:
    ~StaticResourceQueueF426();
    void ReleaseOwnedQueueItems();
};
typedef char StaticResourceQueueSizeF426[(sizeof(StaticResourceQueueF426)==0x1a4)?1:-1];
StaticResourceQueueF426::~StaticResourceQueueF426()
{
    ReleaseOwnedQueueItems();
    if (fileHandle) {
        CloseHandle(fileHandle);
        fileHandle=0;
    }
}
