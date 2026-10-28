// Independently exact complete 142-byte R178 static battle FX-resource
// constructor. Two genuine 20-byte list members are a C++ array, so VC7.1
// naturally generates native vector constructor iterator plus EH cleanup.
// Native static two-list resources + physical borrowed graphics objects.
// Source declares only observed storage footprints and actual call interfaces.
class EffectList20F431 {
public: EffectList20F431();~EffectList20F431();void Clear();
private: unsigned char observedStorage[20];
};
class EffectTexture80F431 {
public: EffectTexture80F431();~EffectTexture80F431();
private: unsigned char observedStorage[80];
};
class EffectAuxiliaryF431 {
public: EffectAuxiliaryF431();~EffectAuxiliaryF431(); void Reset();
};
class StaticBattleResourcesF431 {
private:
    EffectList20F431 lists[2];
    EffectTexture80F431 textures;
    EffectAuxiliaryF431 auxiliary;
public:
    StaticBattleResourcesF431();
};
StaticBattleResourcesF431::StaticBattleResourcesF431() {
    lists[0].Clear();
    lists[1].Clear();
    auxiliary.Reset();
}
