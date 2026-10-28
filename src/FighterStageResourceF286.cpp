#include <windows.h>
#include <stdio.h>
#include <new>

// Only the physically verified stage texture pointer, fighter name and
// stage-page bytes are represented. No full private FighterState is claimed.
class FighterStageTextureF286 {
    unsigned char observedBytes[80];
public:
    FighterStageTextureF286();
    ~FighterStageTextureF286();
    void AllocateSlots(int count);
    void LoadDefault(const char* filename,const char* root);
};
typedef char AssertStageTex80F286[(sizeof(FighterStageTextureF286)==80)?1:-1];
extern signed char g_CurrentStageAt0067161E;
extern const char g_StageTextureFormatAt00658FC0[];
extern const char g_StageArchiveAt00658FE0[];
class FighterStageF286 {
public:
    void LoadStageResource();
};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
void FighterStageF286::LoadStageResource()
{
    char filename[260];
    if (g_CurrentStageAt0067161E<=0) return;
    {
        if (FIELD(FighterStageTextureF286*,0x700))
            delete FIELD(FighterStageTextureF286*,0x700);
        FIELD(FighterStageTextureF286*,0x700)=new FighterStageTextureF286();
        FIELD(FighterStageTextureF286*,0x700)->AllocateSlots(FIELD(signed char,0x704+g_CurrentStageAt0067161E));
        sprintf(filename,g_StageTextureFormatAt00658FC0,reinterpret_cast<char*>(this)+0xC4,g_CurrentStageAt0067161E);
        FIELD(FighterStageTextureF286*,0x700)->LoadDefault(filename,g_StageArchiveAt00658FE0);
    }
}
#undef FIELD
