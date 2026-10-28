#include <windows.h>
#include <string.h>

// Borrowed archive index representation: only the wire-record footprint and
// two observed integer slots are modeled; original STL-list owner unknown.
struct ArchiveWireEntryF250 {
    unsigned char filename[100];
    DWORD sourceSize;
    DWORD sourceOffset;
};
typedef char VerifyArchiveEntry108F250[(sizeof(ArchiveWireEntryF250)==108)?1:-1];
class ArchiveIndexListF250 {
public:
    void AddEntry(const ArchiveWireEntryF250& record);
};
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
class ArchiveIndexF250 {
public:
    void OpenAndReadIndex(const char* filename);
};
#define FILE_FIELD (*reinterpret_cast<HANDLE*>(this))
#define ENTRIES (*reinterpret_cast<ArchiveIndexListF250*>(reinterpret_cast<unsigned char*>(this)+4))
void ArchiveIndexF250::OpenAndReadIndex(const char* filename)
{
    if (FILE_FIELD) CloseHandle(FILE_FIELD);
    FILE_FIELD=CreateFileA(filename,GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
    if (FILE_FIELD==INVALID_HANDLE_VALUE) return;
    ArchiveReadStateF338 state;

    ReadFile(FILE_FIELD,&state.count,2,&state.bytesRead,0);
    state.content=new unsigned char[state.count*108];
    state.decoded=state.content;
    ReadFile(FILE_FIELD,state.content,state.count*108,&state.bytesRead,0);

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
        ENTRIES.AddEntry(record);
    }
    delete[] state.content;
}
#undef ENTRIES
#undef FILE_FIELD
