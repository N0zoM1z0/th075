#include "assets/DataArchive.hpp"
#include <string.h>

DataArchiveF481::DataArchiveF481() {
    archiveHandle=0;
    entries.clear();
}
DataArchiveF481::~DataArchiveF481() {
    if(archiveHandle) CloseHandle(archiveHandle);
    entries.clear();
}

struct ArchiveIndexReadState {
    DWORD keyStorage;
    ArchiveIndexEntry* decoded;
    unsigned short entryCount;
    DWORD stepStorage;
    unsigned int i;
    DWORD bytesRead;
    unsigned char* content;
};
typedef char ArchiveIndexReadStateSize[(sizeof(ArchiveIndexReadState)==28)?1:-1];
void DataArchiveF481::OpenAndReadIndex(const char* filename)
{
    if (archiveHandle) CloseHandle(archiveHandle);
    archiveHandle=CreateFileA(filename,GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
    if (archiveHandle==INVALID_HANDLE_VALUE) return;
    ArchiveIndexReadState state;

    ReadFile(archiveHandle,&state.entryCount,2,&state.bytesRead,0);
    state.content=new unsigned char[state.entryCount * static_cast<int>(sizeof(ArchiveIndexEntry))];
    state.decoded = reinterpret_cast<ArchiveIndexEntry*>(state.content);
    ReadFile(archiveHandle,state.content,state.entryCount * static_cast<int>(sizeof(ArchiveIndexEntry)),&state.bytesRead,0);

    reinterpret_cast<unsigned char*>(&state.keyStorage)[3]=ArchiveIndexCipher::InitialKey;
    reinterpret_cast<unsigned char*>(&state.stepStorage)[3]=ArchiveIndexCipher::InitialStep;
    for (state.i=0;state.i<state.entryCount * static_cast<int>(sizeof(ArchiveIndexEntry));++state.i) {
        state.content[state.i]=state.content[state.i]^reinterpret_cast<unsigned char*>(&state.keyStorage)[3];
        reinterpret_cast<unsigned char*>(&state.keyStorage)[3]+=reinterpret_cast<unsigned char*>(&state.stepStorage)[3];
        reinterpret_cast<unsigned char*>(&state.stepStorage)[3]+=ArchiveIndexCipher::StepIncrement;
    }
    for (state.i=0;state.i<state.entryCount;++state.i) {
        ArchiveIndexEntry record;
        record.dataSize=state.decoded[state.i].dataSize;
        record.dataOffset=state.decoded[state.i].dataOffset;
        strcpy(record.filename,state.decoded[state.i].filename);
        entries.push_back(record);
    }
    delete[] state.content;
}
