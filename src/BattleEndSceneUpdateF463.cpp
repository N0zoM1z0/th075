// Entire original 152-byte battle end scene state policy, including the
// real fighter virtual action and mode-specific score return value.
class BattleEndFighterF463 {
public:
    virtual void F0(); virtual void F1(); virtual void F2(); virtual void F3();
    virtual void F4(); virtual void F5(); virtual void F6(); virtual void F7();
    virtual void F8(); virtual void F9(); virtual void F10();virtual void F11();
    virtual void F12();virtual void F13();virtual void F14();virtual void F15();
    virtual void AdvanceEndAction();
};
class BattleEndSceneF463 {
public:
    virtual void V0();virtual void V4();virtual void AdvanceVisuals();
    unsigned short Update();
    void PollInput();
};
extern BattleEndFighterF463* g_CurrentFighterAt00671418;
extern unsigned int g_BestResultScoreAt00671420;
extern signed char g_EndCharacterAt0067161E;
extern void __cdecl RefreshGraphicsAt004028F0();
extern void __cdecl ChooseStageAt00419CB0(int);
extern void __cdecl ConfigureViewportAt00407E60(int,int,int,int);
#define FIGHTER(T,off) (*reinterpret_cast<T*>(reinterpret_cast<unsigned char*>(g_CurrentFighterAt00671418)+(off)))
unsigned short BattleEndSceneF463::Update() {
    PollInput();
    AdvanceVisuals();
    g_CurrentFighterAt00671418->AdvanceEndAction();
    RefreshGraphicsAt004028F0();
    if (FIGHTER(unsigned char,0x6EF)) {
        if (g_EndCharacterAt0067161E==10) return 0x110B;
        ChooseStageAt00419CB0(40);
        ConfigureViewportAt00407E60(-10000,-300,1,1);
        if (g_BestResultScoreAt00671420 < FIGHTER(unsigned int,0x2D0)) return 0x220A;
        return 0x1102;
    }
    return 8;
}
#undef FIGHTER
