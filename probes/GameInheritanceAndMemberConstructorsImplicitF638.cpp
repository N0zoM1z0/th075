// F638 second independent, entirely normal C++ source hypothesis:
// NO owner constructors declared; placement-new forces VC7.1's
// implicitly generated special-member constructors. Full identical
// native CODE cannot decide written vs generated original provenance.
class BaseF638 {
public:
    virtual ~BaseF638();
};
class DerivedF638 : public BaseF638 {
public:
    virtual ~DerivedF638();
};
class TextureMemberF638 {
public:
    TextureMemberF638();
};
class SceneOwnerF638 {
public:
    virtual ~SceneOwnerF638();
    TextureMemberF638 texture;
};
class SpriteMemberF638 {
public:
    SpriteMemberF638();
};
class SpriteContainerF638 {
public:
    unsigned int authenticUnknownPrefix;
    SpriteMemberF638 member;
};
#include <new>
void __cdecl F638ForceFourImplicitConstructors(
    BaseF638* base, DerivedF638* derived,
    SceneOwnerF638* scene, SpriteContainerF638* sprite) {
    new (base) BaseF638;
    new (derived) DerivedF638;
    new (scene) SceneOwnerF638;
    new (sprite) SpriteContainerF638;
}
