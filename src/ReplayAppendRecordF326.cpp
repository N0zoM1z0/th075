#include <stddef.h>
#include <windows.h>

// The four replay input collections share a 20-byte segmented circular-
// buffer layout. Each iterator stores its owning collection and absolute
// logical index; dereference maps 16-element blocks through the owner map.
// The first collection word remains semantically unknown; the remaining
// offsets are confirmed by the native begin/end/size/dereference helpers.

template<class T> struct ReplaySegmentedQueueStorageF219 {
    unsigned int unknown000;             // +0x00 native allocator/control word
    T** blockMap;                        // +0x04 pointers to 16-element blocks
    unsigned int blockCount;             // +0x08 number of block pointers
    unsigned int firstIndex;             // +0x0C logical first element index
    unsigned int size;                   // +0x10 number of queued elements
};
typedef char ReplayByteQueueStorageSizeF219[(sizeof(ReplaySegmentedQueueStorageF219<char>)==20)?1:-1];
typedef char ReplayWordQueueStorageSizeF219[(sizeof(ReplaySegmentedQueueStorageF219<short>)==20)?1:-1];
typedef char ReplayDwordQueueStorageSizeF219[(sizeof(ReplaySegmentedQueueStorageF219<unsigned int>)==20)?1:-1];
typedef char ReplayQueueMapOffsetF219[(offsetof(ReplaySegmentedQueueStorageF219<char>,blockMap)==4)?1:-1];
typedef char ReplayQueueBlockCountOffsetF219[(offsetof(ReplaySegmentedQueueStorageF219<char>,blockCount)==8)?1:-1];
typedef char ReplayQueueFirstOffsetF219[(offsetof(ReplaySegmentedQueueStorageF219<char>,firstIndex)==0x0c)?1:-1];
typedef char ReplayQueueSizeOffsetF219[(offsetof(ReplaySegmentedQueueStorageF219<char>,size)==0x10)?1:-1];

class ByteQueueF219;
class WordQueueF219;
class DwordQueueF219;
class ByteIteratorF219 {
public:
    void Initialize();
    ByteIteratorF219 operator++(int);
    bool operator!=(const ByteIteratorF219&) const;
    char& operator*() const;
private:
    ByteQueueF219* owner;                // iterator owner

    unsigned int index;                  // absolute logical element index
};
class WordIteratorF219 {
public:
    void Initialize();
    WordIteratorF219 operator++(int);
    bool operator!=(const WordIteratorF219&) const;
    short& operator*() const;
private:
    WordQueueF219* owner;                // iterator owner
    unsigned int index;                  // absolute logical element index;
};
class DwordIteratorF219 {
public:
    void Initialize();
    DwordIteratorF219 operator++(int);
    bool operator!=(const DwordIteratorF219&) const;
    unsigned int& operator*() const;
private:
    DwordQueueF219* owner;               // iterator owner
    unsigned int index;                  // absolute logical element index;
};
class ByteQueueF219 : public ReplaySegmentedQueueStorageF219<char> {
public: ByteIteratorF219 Begin(); ByteIteratorF219 End(); unsigned int Size();
};
class WordQueueF219 : public ReplaySegmentedQueueStorageF219<short> {
public: WordIteratorF219 Begin(); WordIteratorF219 End(); unsigned int Size();
};
class DwordQueueF219 : public ReplaySegmentedQueueStorageF219<unsigned int> {
public: DwordIteratorF219 Begin(); DwordIteratorF219 End(); unsigned int Size();
};
typedef char ReplayByteQueueSizeF219[(sizeof(ByteQueueF219)==20)?1:-1];
typedef char ReplayWordQueueSizeF219[(sizeof(WordQueueF219)==20)?1:-1];
typedef char ReplayDwordQueueSizeF219[(sizeof(DwordQueueF219)==20)?1:-1];
typedef char ReplayByteIteratorSizeF219[(sizeof(ByteIteratorF219)==8)?1:-1];
typedef char ReplayWordIteratorSizeF219[(sizeof(WordIteratorF219)==8)?1:-1];
typedef char ReplayDwordIteratorSizeF219[(sizeof(DwordIteratorF219)==8)?1:-1];

// Serialized per-record header at ReplayRecords+0x144. The skipped bytes
// at +0x14B/+0x14F are preserved as named unknown fields, not synthetic code.
struct ReplayRecordHeaderF326 {
    unsigned char field144, field145, field146, field147, field148, field149, field14A;
    unsigned char unknown14B;
    short field14C;
    unsigned char field14E, unknown14F;
    DWORD field150;
};
typedef char ReplayRecordHeaderSizeF326[(sizeof(ReplayRecordHeaderF326)==0x10)?1:-1];
class ReplayAppendF219 {
public:
    void AppendRecord();
    void ClearQueues();
    HANDLE field000;
    unsigned char unknown004[0x112];    // +0x004..+0x115 not yet classified
    signed char field116;               // +0x116 next record-offset slot
    unsigned char unknown117[5];        // +0x117..+0x11B
    DWORD recordOffsets[10];            // +0x11C ten file offsets
    ReplayRecordHeaderF326 header;      // +0x144..+0x153
    ByteQueueF219 byteInputs;
    WordQueueF219 wordInputs;
    ByteQueueF219 secondaryInputs;
    DwordQueueF219 dwordInputs;
};
typedef char ReplayRecordOffsetsCheckF326[(offsetof(ReplayAppendF219,recordOffsets)==0x11c)?1:-1];
typedef char ReplayRecordHeaderCheckF326[(offsetof(ReplayAppendF219,header)==0x144)?1:-1];
typedef char ReplayByteInputsCheckF326[(offsetof(ReplayAppendF219,byteInputs)==0x154)?1:-1];
typedef char ReplayWordInputsCheckF326[(offsetof(ReplayAppendF219,wordInputs)==0x168)?1:-1];
typedef char ReplaySecondaryInputsCheckF326[(offsetof(ReplayAppendF219,secondaryInputs)==0x17c)?1:-1];
typedef char ReplayDwordInputsCheckF326[(offsetof(ReplayAppendF219,dwordInputs)==0x190)?1:-1];
typedef char ReplayAppendOwnerSizeF326[(sizeof(ReplayAppendF219)==0x1a4)?1:-1];

struct NativeAppendFrameF326 {
    ByteIteratorF219 byteIndexBegin;
    DWORD written;
    ByteIteratorF219 byteIndexEnd;
    WordIteratorF219 wordIndexEnd;
    WordIteratorF219 wordIndexBegin;
    unsigned int count;
    DwordIteratorF219 dwordIndexEnd;
    DwordIteratorF219 dwordHead;
};
typedef char NativeFrame56F326[(sizeof(NativeAppendFrameF326)==56)?1:-1];

void ReplayAppendF219::AppendRecord()
{
    if (!field000) return;
    NativeAppendFrameF326 frame;
    frame.byteIndexBegin.Initialize();
    frame.byteIndexEnd.Initialize();
    frame.wordIndexBegin.Initialize();
    frame.wordIndexEnd.Initialize();
    frame.dwordHead.Initialize();
    frame.dwordIndexEnd.Initialize();
    recordOffsets[field116] = SetFilePointer(field000,0,0,FILE_CURRENT);
    WriteFile(field000,&header.field144,1,&frame.written,0);
    WriteFile(field000,&header.field145,1,&frame.written,0);
    WriteFile(field000,&header.field146,1,&frame.written,0);
    WriteFile(field000,&header.field147,1,&frame.written,0);
    WriteFile(field000,&header.field148,1,&frame.written,0);
    WriteFile(field000,&header.field149,1,&frame.written,0);
    WriteFile(field000,&header.field14A,1,&frame.written,0);
    WriteFile(field000,&header.field14C,2,&frame.written,0);
    WriteFile(field000,&header.field14E,1,&frame.written,0);
    WriteFile(field000,&header.field150,4,&frame.written,0);
    frame.byteIndexBegin=byteInputs.Begin();
    frame.byteIndexEnd=byteInputs.End();
    frame.count=byteInputs.Size();
    WriteFile(field000,&frame.count,4,&frame.written,0);
    for (; frame.byteIndexBegin!=frame.byteIndexEnd; frame.byteIndexBegin++)
        WriteFile(field000,&*frame.byteIndexBegin,1,&frame.written,0);
    frame.wordIndexBegin=wordInputs.Begin();
    frame.wordIndexEnd=wordInputs.End();
    frame.count=wordInputs.Size();
    WriteFile(field000,&frame.count,4,&frame.written,0);
    for (; frame.wordIndexBegin!=frame.wordIndexEnd; frame.wordIndexBegin++)
        WriteFile(field000,&*frame.wordIndexBegin,2,&frame.written,0);
    frame.byteIndexBegin=secondaryInputs.Begin();
    frame.byteIndexEnd=secondaryInputs.End();
    frame.count=secondaryInputs.Size();
    WriteFile(field000,&frame.count,4,&frame.written,0);
    for (; frame.byteIndexBegin!=frame.byteIndexEnd; frame.byteIndexBegin++)
        WriteFile(field000,&*frame.byteIndexBegin,1,&frame.written,0);
    frame.dwordHead=dwordInputs.Begin();
    frame.dwordIndexEnd=dwordInputs.End();
    frame.count=dwordInputs.Size();
    WriteFile(field000,&frame.count,4,&frame.written,0);
    for (; frame.dwordHead!=frame.dwordIndexEnd; frame.dwordHead++)
        WriteFile(field000,&*frame.dwordHead,4,&frame.written,0);
    ClearQueues();
    ++field116;
}
