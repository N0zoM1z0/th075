#pragma once

// The independently reconstructed 80-byte TextureManager receiver.
// Constructor storage is grounded by 0040AD80; the F199 destruction view
// independently confirms the same 80-byte physical extent.
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
    void SetBlendMode(int mode);
};

typedef char AssertTextureManager80F198[
    (sizeof(TextureManagerF198) == 80) ? 1 : -1];
