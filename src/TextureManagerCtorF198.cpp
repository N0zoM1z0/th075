// Experiment: physical nesting is independently anchored by the real native
// constructor calls at offsets 0, 8, 24, 40, 56. Original type names and
// container element types remain unproved.
class TextureRefCountF198 {
    unsigned int refCountAt0;
public:
    TextureRefCountF198();
    ~TextureRefCountF198();
};
class TextureNameVectorF198 {
    unsigned int observedStorage[4];
public:
    TextureNameVectorF198();
    ~TextureNameVectorF198();
    void ClearCachedEntries();
};
class TextureSlotVectorF198 {
    unsigned int observedStorage[4];
public:
    TextureSlotVectorF198();
    ~TextureSlotVectorF198();
    void ClearCachedEntries();
};
class TextureQueueF198 {
    unsigned int observedStorage[5];
public:
    TextureQueueF198();
    ~TextureQueueF198();
};
class TextureManagerF198 : public TextureRefCountF198 {
    unsigned int allocatedResourceAt4;
    TextureNameVectorF198 nameVector;
    TextureSlotVectorF198 firstSlotVector;
    TextureSlotVectorF198 secondSlotVector;
    TextureQueueF198 resourceQueue;
    unsigned char defaultDepthAt76;
public:
    TextureManagerF198();
};
typedef char AssertTextureManager80[(sizeof(TextureManagerF198)==80)?1:-1];
TextureManagerF198::TextureManagerF198()
{
    firstSlotVector.ClearCachedEntries();
    secondSlotVector.ClearCachedEntries();
    nameVector.ClearCachedEntries();
    allocatedResourceAt4 = 0;
    defaultDepthAt76 = 16;
}
