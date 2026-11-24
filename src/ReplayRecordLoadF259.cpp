#include "ReplaySegmentedQueueF219.hpp"

template<>
void ReplayRecords::LoadRecord(signed char slot)
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
    unsigned char item;
    {
    DWORD bytesRead;
    {
    handle = CreateFileA(filePath, GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
    entries = 0;
    SetFilePointer(handle, fileHeader.recordOffsets[slot] + 0x3c, 0, FILE_BEGIN);
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
    byteInputs.clear();
    for (i=0;i<entries;++i) {
        ReadFile(handle,&item,1,&bytesRead,0);
        byteInputs.push_back(item);
    }
    ReadFile(handle,&entries,4,&bytesRead,0);
    wordInputs.clear();
    for (i=0;i<entries;++i) {
        ReadFile(handle,&rawWord,2,&bytesRead,0);
        wordInputs.push_back(static_cast<short>(rawWord));
    }
    ReadFile(handle,&entries,4,&bytesRead,0);
    secondaryInputs.clear();
    for (i=0;i<entries;++i) {
        ReadFile(handle,&item,1,&bytesRead,0);
        secondaryInputs.push_back(item);
    }
    ReadFile(handle,&entries,4,&bytesRead,0);
    dwordInputs.clear();
    for (i=0;i<entries;++i) {
        ReadFile(handle,&dwordItem,4,&bytesRead,0);
        dwordInputs.push_back(dwordItem);
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
