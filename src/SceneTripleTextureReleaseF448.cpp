// Independently exact complete 231-byte R054 scene-derived destructor:
// three authentic C++ `delete` expressions generate all 3 native deleting
// temporary pairs and the real /GX exception handler with no grafted bytes.
// Complete original R054 scene-derived 3-resource lifetime probe. Only the
// native observed vtable/base ABI, resource-pointer offsets +8,+44,+48 and
// their physical spacing are borrowed; intervening owner fields unknown.
class SceneBaseF448 {
    void* originalConfig;
public:SceneBaseF448();virtual ~SceneBaseF448();
};
class TextureF448 {public:~TextureF448();};
class TripleTextureSceneF448 : public SceneBaseF448 {
    TextureF448* mainTexture;
    unsigned char opaqueObservedOwnerRegion[0x38];
    TextureF448* optionalTexture;
    TextureF448* tertiaryTexture;
public:TripleTextureSceneF448();virtual ~TripleTextureSceneF448();
};
TripleTextureSceneF448::~TripleTextureSceneF448() {
    if (mainTexture) delete mainTexture;
    if (optionalTexture) delete optionalTexture;
    if (tertiaryTexture) delete tertiaryTexture;
}
