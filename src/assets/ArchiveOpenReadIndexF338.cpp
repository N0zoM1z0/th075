#include "assets/DataArchive.hpp"
#include <string.h>

DataArchiveF481::DataArchiveF481() {
    originalHandle=0;
    entries.clear();
}
DataArchiveF481::~DataArchiveF481() {
    if(originalHandle) CloseHandle(originalHandle);
    entries.clear();
}

struct ArchiveReadStateF338 {
    DWORD keyStorage;
    unsigned char* decoded;
    unsigned short count;
    DWORD stepStorage;
    unsigned int i;
    DWORD bytesRead;
    unsigned char* content;
};
typedef char CheckArchiveState28F338[(sizeof(ArchiveReadStateF338)==28)?1:-1];
void DataArchiveF481::OpenAndReadIndex(const char* filename)
{
    if (originalHandle) CloseHandle(originalHandle);
    originalHandle=CreateFileA(filename,GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
    if (originalHandle==INVALID_HANDLE_VALUE) return;
    ArchiveReadStateF338 state;

    ReadFile(originalHandle,&state.count,2,&state.bytesRead,0);
    state.content=new unsigned char[state.count*108];
    state.decoded=state.content;
    ReadFile(originalHandle,state.content,state.count*108,&state.bytesRead,0);

    reinterpret_cast<unsigned char*>(&state.keyStorage)[3]=100;
    reinterpret_cast<unsigned char*>(&state.stepStorage)[3]=100;
    for (state.i=0;state.i<state.count*108;++state.i) {
        state.content[state.i]=state.content[state.i]^reinterpret_cast<unsigned char*>(&state.keyStorage)[3];
        reinterpret_cast<unsigned char*>(&state.keyStorage)[3]+=reinterpret_cast<unsigned char*>(&state.stepStorage)[3];
        reinterpret_cast<unsigned char*>(&state.stepStorage)[3]+=77;
    }
    for (state.i=0;state.i<state.count;++state.i) {
        ArchiveWireEntryF250 record;
        record.sourceSize=*reinterpret_cast<DWORD*>(state.decoded+state.i*108+100);
        record.sourceOffset=*reinterpret_cast<DWORD*>(state.decoded+state.i*108+104);
        strcpy(reinterpret_cast<char*>(record.filename),reinterpret_cast<char*>(state.decoded+state.i*108));
        entries.push_back(record);
    }
    delete[] state.content;
}
