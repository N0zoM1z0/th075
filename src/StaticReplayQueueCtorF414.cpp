#include "ReplaySegmentedQueueF219.hpp"

// The static replay owner has the same observed prefix/header/queue offsets
// as ReplayRecords. The four queue constructors initialize their segmented
// block maps; the owner constructor then clears the file handle.
class NativeByteQueueF414 : public ReplaySegmentedQueueStorageF219<char> {
public: NativeByteQueueF414(); ~NativeByteQueueF414();
};
class NativeWordQueueF414 : public ReplaySegmentedQueueStorageF219<short> {
public: NativeWordQueueF414(); ~NativeWordQueueF414();
};
class NativeDwordQueueF414 : public ReplaySegmentedQueueStorageF219<unsigned int> {
public: NativeDwordQueueF414(); ~NativeDwordQueueF414();
};
class ReplayStaticQueuesF414 {
    HANDLE fileHandle;
    char filePath[0x112];
    signed char field116;
    unsigned char unknown117[5];
    DWORD recordOffsets[10];
    ReplayRecordHeaderF219 header;
    NativeByteQueueF414 first;
    NativeWordQueueF414 second;
    NativeByteQueueF414 third;
    NativeDwordQueueF414 fourth;
public:
    ReplayStaticQueuesF414();
};
typedef char ReplayStaticQueuesSizeF414[(sizeof(ReplayStaticQueuesF414)==0x1a4)?1:-1];
ReplayStaticQueuesF414::ReplayStaticQueuesF414()
{
    fileHandle=0;
}
