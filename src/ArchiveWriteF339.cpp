#include <windows.h>
#include <string.h>

// Physical four-byte VC7 archive-list iterators and borrowed owner interface.
// First Begin/End calls directly use their real 4-byte hidden-sret destination
// slots; later Begin/End calls return into genuine distinct compiler temporary
// slots then copy to existing iterator instances. BeginInto/EndInto are ONLY
// caller-side names for those same actual original native Begin/End entrypoints
// (0041D950/0041D980), not different original methods or implementations.
// Neither original node nor list class layout is inferred.
class ArchiveIteratorF249 {
    void* element;
public:
    bool operator!=(const ArchiveIteratorF249& other) const;
    char* Entry();
    ArchiveIteratorF249 operator++(int);
};
typedef char VerifyIteratorWidthF249[(sizeof(ArchiveIteratorF249)==4)?1:-1];
class ArchiveEntryListF249 {
public:
    void BeginInto(ArchiveIteratorF249* out);
    void EndInto(ArchiveIteratorF249* out);
    ArchiveIteratorF249 Begin();
    ArchiveIteratorF249 End();
    int Count();
};
struct NativeArchiveWriteStateF339 {
    unsigned char* bytes;
    DWORD fileSize;
    DWORD keyStorage;
    DWORD nextOffset;
    unsigned short headerLength;
    unsigned char* header;
    ArchiveIteratorF249 end;
    DWORD stepStorage;
    unsigned int index;
    DWORD bytesWritten;
    HANDLE output;
    HANDLE input;
    unsigned char* contents;
    DWORD bytesRead;
    ArchiveIteratorF249 it;
};
typedef char ArchiveWriteState60F339[(sizeof(NativeArchiveWriteStateF339)==60)?1:-1];
class ArchiveWriterF249 {
public:
    void Write(const char* outputFilename);
};
#define ENTRIES (*reinterpret_cast<ArchiveEntryListF249*>(reinterpret_cast<unsigned char*>(this)+4))
void ArchiveWriterF249::Write(const char* outputFilename)
{
    NativeArchiveWriteStateF339 state;
    state.output=CreateFileA(outputFilename,GENERIC_WRITE,0,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
    if (state.output==INVALID_HANDLE_VALUE) return;
    SetFilePointer(state.output,0,0,FILE_BEGIN);
    ENTRIES.BeginInto(&state.it);
    ENTRIES.EndInto(&state.end);
    state.headerLength=static_cast<unsigned short>(ENTRIES.Count()*108+2);
    state.header=new unsigned char[state.headerLength];
    state.contents=state.header+2;
    *reinterpret_cast<unsigned short*>(state.header)=static_cast<unsigned short>(ENTRIES.Count());
    state.nextOffset=state.headerLength;
    state.index=0;
    while (state.it!=state.end) {
        *reinterpret_cast<DWORD*>(state.contents+state.index*108+104)=state.nextOffset;
        *reinterpret_cast<DWORD*>(state.contents+state.index*108+100)=*reinterpret_cast<DWORD*>(state.it.Entry()+100);
        strcpy(reinterpret_cast<char*>(state.contents+state.index*108),state.it.Entry());
        state.nextOffset+=*reinterpret_cast<DWORD*>(state.it.Entry()+100);
        state.it++;
        ++state.index;
    }
    reinterpret_cast<unsigned char*>(&state.keyStorage)[3]=100;
    reinterpret_cast<unsigned char*>(&state.stepStorage)[3]=100;
    for (state.index=2;state.index<state.headerLength;++state.index) {
        state.header[state.index]=state.header[state.index]^reinterpret_cast<unsigned char*>(&state.keyStorage)[3];
        reinterpret_cast<unsigned char*>(&state.keyStorage)[3]+=reinterpret_cast<unsigned char*>(&state.stepStorage)[3];
        reinterpret_cast<unsigned char*>(&state.stepStorage)[3]+=77;
    }

    WriteFile(state.output,state.header,state.headerLength,&state.bytesWritten,0);
    delete[] state.header;
    state.it=ENTRIES.Begin();
    state.end=ENTRIES.End();
    while (state.it!=state.end) {
        state.input=CreateFileA(state.it.Entry(),GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
        if (state.input!=INVALID_HANDLE_VALUE) {
            state.fileSize=GetFileSize(state.input,0);
            state.bytes=new unsigned char[state.fileSize];

            ReadFile(state.input,state.bytes,state.fileSize,&state.bytesRead,0);
            WriteFile(state.output,state.bytes,state.fileSize,&state.bytesWritten,0);
            CloseHandle(state.input);
            delete[] state.bytes;
        }
        state.it++;
    }
    CloseHandle(state.output);
}
#undef ENTRIES
