#include "DataArchive.hpp"
#include <string.h>

void DataArchiveF481::Write(const char* filename)
{
    DWORD cipherWord;
    DWORD deltaWord;
    HANDLE destinationFile;
    HANDLE sourceMember;
    DWORD membersSize;
    unsigned char* dataBuffer;
    DWORD bytesReceived;
    destinationFile = CreateFileA(filename, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
    if (destinationFile == INVALID_HANDLE_VALUE)
        return;

    SetFilePointer(destinationFile, 0, 0, FILE_BEGIN);
    std::list<ArchiveWireEntryF250>::iterator recordCursor = entries.begin();
    std::list<ArchiveWireEntryF250>::iterator lastMember = entries.end();
    unsigned short lengthHeader = static_cast<unsigned short>(entries.size() * sizeof(ArchiveWireEntryF250) + 2);
    unsigned char* outHeader = new unsigned char[lengthHeader];
    ArchiveWireEntryF250* memberRecords = reinterpret_cast<ArchiveWireEntryF250*>(outHeader + 2);
    *reinterpret_cast<unsigned short*>(outHeader) = static_cast<unsigned short>(entries.size());
    DWORD payloadOffset = lengthHeader;
    unsigned int memberNumber = 0;

    while (recordCursor != lastMember) {
        memberRecords[memberNumber].sourceOffset = payloadOffset;
        memberRecords[memberNumber].sourceSize = recordCursor->sourceSize;
        strcpy(reinterpret_cast<char*>(memberRecords[memberNumber].filename),
            reinterpret_cast<const char*>(recordCursor->filename));
        payloadOffset += recordCursor->sourceSize;
        recordCursor++;
        ++memberNumber;
    }

    // The archive cipher uses the high byte of each word.
    reinterpret_cast<unsigned char*>(&cipherWord)[3] = 100;
    reinterpret_cast<unsigned char*>(&deltaWord)[3] = 100;
    for (memberNumber = 2; memberNumber < lengthHeader; ++memberNumber) {
        outHeader[memberNumber] = outHeader[memberNumber] ^ reinterpret_cast<unsigned char*>(&cipherWord)[3];
        reinterpret_cast<unsigned char*>(&cipherWord)[3] += reinterpret_cast<unsigned char*>(&deltaWord)[3];
        reinterpret_cast<unsigned char*>(&deltaWord)[3] += 77;
    }

    DWORD fileWritten;
    WriteFile(destinationFile, outHeader, lengthHeader, &fileWritten, 0);
    delete[] outHeader;
    recordCursor = entries.begin();
    lastMember = entries.end();
    while (recordCursor != lastMember) {
        sourceMember = CreateFileA(reinterpret_cast<const char*>(recordCursor->filename),
            GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
        if (sourceMember != INVALID_HANDLE_VALUE) {
            membersSize = GetFileSize(sourceMember, 0);
            dataBuffer = new unsigned char[membersSize];
            ReadFile(sourceMember, dataBuffer, membersSize, &bytesReceived, 0);
            WriteFile(destinationFile, dataBuffer, membersSize, &fileWritten, 0);
            CloseHandle(sourceMember);
            delete[] dataBuffer;
        }
        recordCursor++;
    }
    CloseHandle(destinationFile);
}
