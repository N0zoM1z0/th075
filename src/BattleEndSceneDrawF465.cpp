#include <windows.h>
// Independently exact entire native R053 scene draw. Original borrowed
// overlay helper 00412EB0 has zero arguments; a made-up mode argument
// added a nonnative PUSH and changed complete code length by two bytes.
// Complete native R053 battle-end drawing sequence, original fighter actor
// render modes, 18th virtual call and 640x480 alpha-tinted screen overlay.
class ActorDrawerF464 {
public:
    void SetDepthMode(int mode);
    void SetBlendMode(int mode);
    void DrawOverlay();
};
class BattleActorF464 {
public:
    virtual void V0(); virtual void V1(); virtual void V2(); virtual void V3();
    virtual void V4(); virtual void V5(); virtual void V6(); virtual void V7();
    virtual void V8(); virtual void V9(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void DrawCharacter(unsigned char);
};
extern BattleActorF464* g_BattleEndActorAt00671418;
extern signed char g_BattleEndCharacterAt0067161E;
extern unsigned char g_BattleOverlayAlphaAt006714D1;
extern unsigned int g_BattleOverlayColorAt0067149C;
extern ActorDrawerF464* g_BattleEndOverlayDrawerAt0067143C;
extern unsigned char __cdecl GraphicsBeginAt00402660();
extern void __cdecl GraphicsAdvanceAt004027D0();
extern void __cdecl GraphicsClearOverlayAt00403910(const RECT*,unsigned int);
class BattleEndDrawF464 {public:void Draw();};
#define ACTOR_FIELD(T,o) (*reinterpret_cast<T*>(reinterpret_cast<unsigned char*>(g_BattleEndActorAt00671418)+(o)))
#define ACTOR_DRAWER (*reinterpret_cast<ActorDrawerF464**>(reinterpret_cast<unsigned char*>(g_BattleEndActorAt00671418)+4))
void BattleEndDrawF464::Draw() {
    if(GraphicsBeginAt00402660()) {
        ACTOR_DRAWER->SetDepthMode(0);
        ACTOR_DRAWER->SetBlendMode(0);
        g_BattleEndActorAt00671418->DrawCharacter(g_BattleEndCharacterAt0067161E);
        if(ACTOR_FIELD(unsigned char,0x6EE))
            g_BattleEndOverlayDrawerAt0067143C->DrawOverlay();
        if (g_BattleOverlayAlphaAt006714D1>0) {
            RECT region;
            SetRect(&region,0,0,640,480);
            GraphicsClearOverlayAt00403910(&region, (static_cast<unsigned int>(g_BattleOverlayAlphaAt006714D1)<<24) | g_BattleOverlayColorAt0067149C);
        }
        GraphicsAdvanceAt004027D0();
    }
}
#undef ACTOR_FIELD
#undef ACTOR_DRAWER
