#include <windows.h>
#include <new>
// This full-function probe borrows only ABI/physical offsets independently
// seen in the original 1,722-byte controller. It does not assert original
// library container class identity, values.file ownership, or private contents.
struct EffectScratchF294 {
 unsigned int original16Bytes[4];
 EffectScratchF294();
 ~EffectScratchF294();
};
typedef char EffectScratch16F294[(sizeof(EffectScratchF294)==16)?1:-1];
class EffectRecordF294 {public: void InitializeGraphics();};
class EffectSequenceF294 {
 unsigned int physicalWords[4];
public:
 EffectSequenceF294();
 ~EffectSequenceF294();
 void Clear();
 void Resize(int count,const EffectScratchF294& value);
 EffectRecordF294* At(int index);
};
typedef char EffectSequence16F294[(sizeof(EffectSequenceF294)==16)?1:-1];
class EffectSlotsF294 {
public:
 unsigned int Size();
 EffectSequenceF294** At(unsigned int index);
 void Clear();
 void Resize(unsigned int count,EffectSequenceF294* const& defaultEntry);
};
class EffectArchiveF294 {public: HANDLE OpenEntry(const char* name);};
extern "C" EffectArchiveF294* __cdecl FindEffectArchiveF294(const char* archiveName);
extern const char g_ArchiveRootAt0065A0B8[];
extern const char g_EffectPatPathAt0065A0C0[];
extern const float g_EffectShortScaleAt00658044;
struct EffectVarsGroupF294 {
    short number;
    int entryCount;
    DWORD kindStorage;
    int recordIndex;
    unsigned int slot;
    int fileRows;
    HANDLE file;
    DWORD transferred;
    int fileIndex;
};
class EffectsCatalogF294 {public: void LoadPatternCatalog();};
#define R(type,p,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(p)+(off)))
#define SLOTS (reinterpret_cast<EffectSlotsF294*>(reinterpret_cast<unsigned char*>(this)+0x78))
#define RECORD ((*SLOTS->At(values.slot))->At(values.recordIndex))
#define DATA (R(void*,RECORD,8))
#define READ(dst,n) ReadFile(values.file,(dst),(n),&values.transferred,0)
void EffectsCatalogF294::LoadPatternCatalog()
{

    EffectVarsGroupF294 values;
    EffectScratchF294 scratch;
    values.file=FindEffectArchiveF294(g_ArchiveRootAt0065A0B8)->OpenEntry(g_EffectPatPathAt0065A0C0);
    values.slot=0;
    for (;values.slot<SLOTS->Size();++values.slot) {
        if (*SLOTS->At(values.slot)) {
            (*SLOTS->At(values.slot))->Clear();
            delete *SLOTS->At(values.slot);
        }
    }
    SLOTS->Clear();

    READ(&values.slot,4);
    SLOTS->Resize(values.slot,static_cast<EffectSequenceF294*>(0));

    READ(&values.fileRows,4);
    for (values.fileIndex=0;values.fileIndex<values.fileRows;++values.fileIndex) {
        READ(&values.slot,4);
        if (!*SLOTS->At(values.slot))
            *SLOTS->At(values.slot)=new EffectSequenceF294();

        READ(&values.entryCount,4);
        (*SLOTS->At(values.slot))->Resize(values.entryCount,scratch);
        for (values.recordIndex=0;values.recordIndex<values.entryCount;++values.recordIndex) {
            READ(reinterpret_cast<unsigned char*>(RECORD)+6,2);
            READ(reinterpret_cast<unsigned char*>(RECORD)+0,2);
            READ(reinterpret_cast<unsigned char*>(RECORD)+2,2);
            READ(reinterpret_cast<unsigned char*>(RECORD)+4,2);

            READ(&R(signed char,&values.kindStorage,3),1);
            if (R(signed char,&values.kindStorage,3)==0) {
                R(unsigned char,RECORD,0xc)=1;
            } else if (R(signed char,&values.kindStorage,3)==1) {
                R(unsigned char,RECORD,0xc)=0;
            } else if(R(signed char,&values.kindStorage,3)==2) {
                RECORD->InitializeGraphics();
                READ(DATA,2);
                READ(reinterpret_cast<unsigned char*>(DATA)+1,1);
                READ(reinterpret_cast<unsigned char*>(DATA)+2,1);
                READ(reinterpret_cast<unsigned char*>(DATA)+3,1);
                READ(reinterpret_cast<unsigned char*>(DATA)+4,1);

                READ(&values.number,2);
                R(float,DATA,0xc)=static_cast<float>(values.number)*g_EffectShortScaleAt00658044;
                R(float,DATA,0x10)=static_cast<float>(values.number)*g_EffectShortScaleAt00658044;
                R(float,DATA,0x14)=static_cast<float>(values.number)*g_EffectShortScaleAt00658044;
                READ(reinterpret_cast<unsigned char*>(DATA)+6,2);
                READ(reinterpret_cast<unsigned char*>(DATA)+8,2);
                READ(reinterpret_cast<unsigned char*>(DATA)+10,2);
                READ(&values.number,2);
                R(float,DATA,0x18)=static_cast<float>(values.number);
                READ(&values.number,2);
                R(float,DATA,0x1c)=static_cast<float>(values.number);
                READ(&values.number,2);
                R(float,DATA,0x20)=static_cast<float>(values.number);
            }
        }
    }
}
#undef READ
#undef DATA
#undef RECORD
#undef SLOTS
#undef R
