#include "ReplaySegmentedQueueF219.hpp"

// The four replay input collections share a 20-byte segmented circular-
// buffer layout. Each iterator stores its owning collection and absolute
// logical index; dereference maps 16-element blocks through the owner map.
// The first collection word remains semantically unknown; the remaining
// offsets are confirmed by the native begin/end/size/dereference helpers.

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

typedef ReplayRecordsLayoutF219<ByteQueueF219,WordQueueF219,DwordQueueF219> ReplayAppendOwnerLayoutF326;
class ReplayAppendF219 : public ReplayAppendOwnerLayoutF326 {
public:
    void AppendRecord();
    void ClearQueues();
};
typedef char ReplayRecordOffsetsCheckF326[((offsetof(ReplayAppendOwnerLayoutF326, fileHeader) + offsetof(ReplayFileHeaderF219, recordOffsets))==0x11c)?1:-1];
typedef char ReplayRecordHeaderCheckF326[(offsetof(ReplayAppendOwnerLayoutF326,header)==0x144)?1:-1];
typedef char ReplayByteInputsCheckF326[(offsetof(ReplayAppendOwnerLayoutF326,byteInputs)==0x154)?1:-1];
typedef char ReplayWordInputsCheckF326[(offsetof(ReplayAppendOwnerLayoutF326,wordInputs)==0x168)?1:-1];
typedef char ReplaySecondaryInputsCheckF326[(offsetof(ReplayAppendOwnerLayoutF326,secondaryInputs)==0x17c)?1:-1];
typedef char ReplayAppendOwnerSizeF326[(sizeof(ReplayAppendOwnerLayoutF326)==0x1a4)?1:-1];

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
    if (!fileHandle) return;
    NativeAppendFrameF326 frame;
    frame.byteIndexBegin.Initialize();
    frame.byteIndexEnd.Initialize();
    frame.wordIndexBegin.Initialize();
    frame.wordIndexEnd.Initialize();
    frame.dwordHead.Initialize();
    frame.dwordIndexEnd.Initialize();
    fileHeader.recordOffsets[fileHeader.recordCount] = SetFilePointer(fileHandle,0,0,FILE_CURRENT);
    WriteFile(fileHandle,&header.field144,1,&frame.written,0);
    WriteFile(fileHandle,&header.field145,1,&frame.written,0);
    WriteFile(fileHandle,&header.field146,1,&frame.written,0);
    WriteFile(fileHandle,&header.field147,1,&frame.written,0);
    WriteFile(fileHandle,&header.field148,1,&frame.written,0);
    WriteFile(fileHandle,&header.field149,1,&frame.written,0);
    WriteFile(fileHandle,&header.field14A,1,&frame.written,0);
    WriteFile(fileHandle,&header.field14C,2,&frame.written,0);
    WriteFile(fileHandle,&header.field14E,1,&frame.written,0);
    WriteFile(fileHandle,&header.field150,4,&frame.written,0);
    frame.byteIndexBegin=byteInputs.Begin();
    frame.byteIndexEnd=byteInputs.End();
    frame.count=byteInputs.Size();
    WriteFile(fileHandle,&frame.count,4,&frame.written,0);
    for (; frame.byteIndexBegin!=frame.byteIndexEnd; frame.byteIndexBegin++)
        WriteFile(fileHandle,&*frame.byteIndexBegin,1,&frame.written,0);
    frame.wordIndexBegin=wordInputs.Begin();
    frame.wordIndexEnd=wordInputs.End();
    frame.count=wordInputs.Size();
    WriteFile(fileHandle,&frame.count,4,&frame.written,0);
    for (; frame.wordIndexBegin!=frame.wordIndexEnd; frame.wordIndexBegin++)
        WriteFile(fileHandle,&*frame.wordIndexBegin,2,&frame.written,0);
    frame.byteIndexBegin=secondaryInputs.Begin();
    frame.byteIndexEnd=secondaryInputs.End();
    frame.count=secondaryInputs.Size();
    WriteFile(fileHandle,&frame.count,4,&frame.written,0);
    for (; frame.byteIndexBegin!=frame.byteIndexEnd; frame.byteIndexBegin++)
        WriteFile(fileHandle,&*frame.byteIndexBegin,1,&frame.written,0);
    frame.dwordHead=dwordInputs.Begin();
    frame.dwordIndexEnd=dwordInputs.End();
    frame.count=dwordInputs.Size();
    WriteFile(fileHandle,&frame.count,4,&frame.written,0);
    for (; frame.dwordHead!=frame.dwordIndexEnd; frame.dwordHead++)
        WriteFile(fileHandle,&*frame.dwordHead,4,&frame.written,0);
    ClearQueues();
    ++fileHeader.recordCount;
}
