// F634: original complete game-facing tiny functions with source origin
// UNKNOWN. Natural VC7.1 x86 source alternatives only; neither
// original historical classes nor explicit user-written source is
// established. No authored match ledger acceptance.
class SpriteSelfReferenceF634 {
public:
    SpriteSelfReferenceF634* Self();
};
class AtlasSelfReferenceF634 {
public:
    AtlasSelfReferenceF634* Self();
};
class CharacterNoopActionF634 {
public:
    void AcceptAction(int action);
};

SpriteSelfReferenceF634* SpriteSelfReferenceF634::Self() {
    return this;
}
AtlasSelfReferenceF634* AtlasSelfReferenceF634::Self() {
    return this;
}
void CharacterNoopActionF634::AcceptAction(int) {
}
