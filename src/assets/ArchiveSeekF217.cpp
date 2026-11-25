#include "assets/DataArchive.hpp"
#include <string.h>

HANDLE DataArchiveF481::SeekNamedEntryWithSize(const char* entryName, DWORD* size)
{
    std::list<ArchiveIndexEntry>::iterator current=entries.begin();
    std::list<ArchiveIndexEntry>::iterator last=entries.end();
    while (current != last) {
        if (!strcmp(current->filename,entryName))
            break;
        current++;
    }
    if (current == last)
        return INVALID_HANDLE_VALUE;
    SetFilePointer(archiveHandle,
        current->dataOffset,0,FILE_BEGIN);
    *size = current->dataSize;
    return archiveHandle;
}
