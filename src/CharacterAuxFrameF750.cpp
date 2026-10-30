// F750: native R213-authored complete 005FAC60 nested collection frame refresh.
// Source explicitly uses genuine current group/frame selectors, actual
// underlying std::vector::at nested calls, and physical sprite frame members.
// All complete private original class layouts are provisional.
struct CharacterFrameF750 {
    unsigned char actualBytes0To3[4];
    signed short nativeCodeAt4;
};
class InnerFrameCollectionF750 {
public:
    CharacterFrameF750* At(int frame);
    int Size();
};
class OuterFrameCollectionF750 {
public:
    InnerFrameCollectionF750** At(int group);
};
class CharacterAuxFrameF750 {
    unsigned char nativeOriginalOwnerBytes0To7[8];
    CharacterFrameF750* selectedFrameAt8;
    unsigned char nativeOwnerBytesCTo5F[0x60-0x0C];
    signed short groupAt60;
    signed short frameAt62;
    unsigned char nativeOwnerBytes64To6F[0x70-0x64];
    signed short collectionSizeAt70;
    signed short selectedCodeAt72;
    unsigned char nativeOwnerBytes74To7B[0x7C-0x74];
    OuterFrameCollectionF750* collectionsAt7C;
public:
    void RefreshSelectedFrame();
};
void CharacterAuxFrameF750::RefreshSelectedFrame() {
    selectedFrameAt8=(*collectionsAt7C->At(groupAt60))->At(frameAt62);
    selectedCodeAt72=selectedFrameAt8->nativeCodeAt4;
    collectionSizeAt70=static_cast<short>((*collectionsAt7C->At(groupAt60))->Size());
}
