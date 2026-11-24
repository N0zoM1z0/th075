#include "GameProgress.hpp"
#include "TextOverlay.hpp"
#include <windows.h>
// Scene base, character actor, renderer and profile owner are limited to
// independently observed method ABI and game globals; no full layout.
class SceneBaseF288 {
    void* nativeConfiguration;
public:
    SceneBaseF288();
    virtual ~SceneBaseF288();
};
class FighterActorF288 {
public:
    virtual void Slot0(); virtual void Slot1(); virtual void Slot2(); virtual void Slot3();
    virtual void Slot4(); virtual void Slot5(); virtual void Slot6(); virtual void Slot7();
    virtual void Slot8(); virtual void Slot9(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14();
    virtual void UpdateStage();
    void LoadStageResource();
};
extern FighterActorF288* g_FighterAt00671418;
extern signed char g_StageAt0067161E;
extern signed char g_CharacterAt006714C8;
extern unsigned char g_StatusAt006714CE;
extern const char g_EndTitleAt00657B7B[];
class BattleEndInitF288 : public SceneBaseF288 {
public:
    BattleEndInitF288();
    virtual ~BattleEndInitF288();
};
#define FIELD(type,p,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(p)+(off)))
BattleEndInitF288::BattleEndInitF288()
{
    g_TextRenderer->ConfigureText(35.0f,360.0f,1);
    g_TextRenderer->RenderTextToTexture(g_EndTitleAt00657B7B,120,120,255,16,1,0);
    FIELD(unsigned char,g_FighterAt00671418,0x6EE)=0;
    g_StageAt0067161E=FIELD(signed char,g_FighterAt00671418,0x713);
    g_FighterAt00671418->UpdateStage();
    g_FighterAt00671418->LoadStageResource();
    if (g_StageAt0067161E==8) {
        g_StatusAt006714CE=0;
        g_GameProgress.SetUnlockBit(g_CharacterAt006714C8);
    } else if (g_StageAt0067161E==9) {
        g_StatusAt006714CE=0;
        g_GameProgress.SetUnlockBit(g_CharacterAt006714C8+20);
    } else {
        g_StatusAt006714CE=0xff;
        g_GameProgress.IncrementSelectedRecord();
        g_GameProgress.SetUnlockBit(g_CharacterAt006714C8+40);
    }
}
#undef FIELD
