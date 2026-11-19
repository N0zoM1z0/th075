#include "ReplaySegmentedQueueF219.hpp"

// The reader uses the same typed ReplayRecords owner and segmented queue
// layout as AppendRecord. Nested local lifetimes preserve the native VC7.1
// stack objects, including the unsigned file-word to signed queue insertion.
class ReplayByteListF216 : public ReplaySegmentedQueueStorageF219<char> {
public:
    void Clear();
    void Push(const char* item);
};
class ReplayWordListF216 : public ReplaySegmentedQueueStorageF219<short> {
public:
    void Clear();
    void Push(const short& item);
};
class ReplayDwordListF216 : public ReplaySegmentedQueueStorageF219<unsigned int> {
public:
    void Clear();
    void Push(const unsigned int* item);
};
typedef ReplayRecordsLayoutF219<ReplayByteListF216,ReplayWordListF216,ReplayDwordListF216> ReplayLoadOwnerLayoutF216;
class ReplayRecordsF216 : public ReplayLoadOwnerLayoutF216 {
public:
    void LoadRecord(signed char slot);
};
typedef char ReplayLoadOwnerSizeF216[(sizeof(ReplayLoadOwnerLayoutF216)==0x1a4)?1:-1];
void ReplayRecordsF216::LoadRecord(signed char slot)
{
    unsigned int i;
    {
    unsigned int dwordItem;
    {
    // The file contains an unsigned 16-bit word. Insertion into the signed
    // 16-bit collection materializes an actual compiler temporary (EBP-1E).
    unsigned short rawWord;
    {
    unsigned int entries;
    {
    HANDLE handle;
    {
    char item;
    {
    DWORD bytesRead;
    {
    handle = CreateFileA(filePath, GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
    entries = 0;
    SetFilePointer(handle, recordOffsets[slot] + 0x3c, 0, FILE_BEGIN);
    ReadFile(handle,&header.field144,1,&bytesRead,0);
    ReadFile(handle,&header.field145,1,&bytesRead,0);
    ReadFile(handle,&header.field146,1,&bytesRead,0);
    ReadFile(handle,&header.field147,1,&bytesRead,0);
    ReadFile(handle,&header.field148,1,&bytesRead,0);
    ReadFile(handle,&header.field149,1,&bytesRead,0);
    ReadFile(handle,&header.field14A,1,&bytesRead,0);
    ReadFile(handle,&header.field14C,2,&bytesRead,0);
    ReadFile(handle,&header.field14E,1,&bytesRead,0);
    ReadFile(handle,&header.field150,4,&bytesRead,0);
    ReadFile(handle,&entries,4,&bytesRead,0);
    byteInputs.Clear();
    for (i=0;i<entries;++i) {
        ReadFile(handle,&item,1,&bytesRead,0);
        byteInputs.Push(&item);
    }
    ReadFile(handle,&entries,4,&bytesRead,0);
    wordInputs.Clear();
    for (i=0;i<entries;++i) {
        ReadFile(handle,&rawWord,2,&bytesRead,0);
        wordInputs.Push(static_cast<short>(rawWord));
    }
    ReadFile(handle,&entries,4,&bytesRead,0);
    secondaryInputs.Clear();
    for (i=0;i<entries;++i) {
        ReadFile(handle,&item,1,&bytesRead,0);
        secondaryInputs.Push(&item);
    }
    ReadFile(handle,&entries,4,&bytesRead,0);
    dwordInputs.Clear();
    for (i=0;i<entries;++i) {
        ReadFile(handle,&dwordItem,4,&bytesRead,0);
        dwordInputs.Push(&dwordItem);
    }
    CloseHandle(handle);
    }
    }
    }
    }
    }
    }
    }
}
