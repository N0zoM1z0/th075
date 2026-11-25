#include "battle/CombatEffects.hpp"
#include "engine/FloatConstants.hpp"
#include "assets/ArchiveCatalog.hpp"
#include "assets/DataArchive.hpp"
#include <windows.h>
#include <new>
extern const char g_ArchiveRootAt0065A0B8[] = "data";
extern const char g_EffectPatPathAt0065A0C0[] = "data\\system\\effect\\effect.pat";
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
#define RECORD patterns[values.slot]->frames[values.recordIndex]
#define DATA RECORD.pose
#define READ(dst,n) ReadFile(values.file,(dst),(n),&values.transferred,0)
void CombatEffects::LoadPatternCatalog()
{

    EffectVarsGroupF294 values;
    FighterFrameInfoHeader scratch;
    values.file=ResourceLookupF217::FindByName(g_ArchiveRootAt0065A0B8)->SeekNamedEntry(g_EffectPatPathAt0065A0C0);
    values.slot=0;
    for (;values.slot<patterns.size();++values.slot) {
        if (patterns[values.slot]) {
            patterns[values.slot]->frames.clear();
            delete patterns[values.slot];
        }
    }
    patterns.clear();

    READ(&values.slot,4);
    patterns.assign(values.slot, static_cast<EffectPatternSequence*>(0));

    READ(&values.fileRows,4);
    for (values.fileIndex=0;values.fileIndex<values.fileRows;++values.fileIndex) {
        READ(&values.slot,4);
        if (!patterns[values.slot])
            patterns[values.slot]=new EffectPatternSequence();

        READ(&values.entryCount,4);
        patterns[values.slot]->frames.assign(values.entryCount, scratch);
        for (values.recordIndex=0;values.recordIndex<values.entryCount;++values.recordIndex) {
            READ(&RECORD.textureIndex,2);
            READ(&RECORD.originX,2);
            READ(&RECORD.originY,2);
            READ(&RECORD.unknown04,2);

            READ(&reinterpret_cast<signed char*>(&values.kindStorage)[3],1);
            if (reinterpret_cast<signed char*>(&values.kindStorage)[3]==0) {
                RECORD.field0C=1;
            } else if (reinterpret_cast<signed char*>(&values.kindStorage)[3]==1) {
                RECORD.field0C=0;
            } else if(reinterpret_cast<signed char*>(&values.kindStorage)[3]==2) {
                RECORD.ResetExtension();
                READ(DATA,2);
                READ(&DATA->color[0],1);
                READ(&DATA->color[1],1);
                READ(&DATA->color[2],1);
                READ(&DATA->color[3],1);

                READ(&values.number,2);
                DATA->scaleX=static_cast<float>(values.number)*FloatConstants::OneHundredth;
                DATA->scaleY=static_cast<float>(values.number)*FloatConstants::OneHundredth;
                DATA->scaleZ=static_cast<float>(values.number)*FloatConstants::OneHundredth;
                READ(&DATA->offsetX,2);
                READ(&DATA->offsetY,2);
                READ(&DATA->offsetZ,2);
                READ(&values.number,2);
                DATA->rotationX=static_cast<float>(values.number);
                READ(&values.number,2);
                DATA->rotationY=static_cast<float>(values.number);
                READ(&values.number,2);
                DATA->rotationZ=static_cast<float>(values.number);
            }
        }
    }
}
#undef READ
#undef DATA
#undef RECORD
