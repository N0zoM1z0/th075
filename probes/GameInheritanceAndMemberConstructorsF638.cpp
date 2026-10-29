// F638: genuine native TH075 game-use constructors, class names and
// explicitly-written-vs-generated provenance UNKNOWN. Ordinary VC7.1
// natural C++ source without ASM, source patches or synthetic stack.
// Four independent complete original constructor-machine-code probes.

class BaseF638 {
public:
    BaseF638();
    virtual ~BaseF638();
};
class DerivedF638 : public BaseF638 {
public:
    DerivedF638();
    virtual ~DerivedF638();
};
BaseF638::BaseF638() {}
DerivedF638::DerivedF638() {}

class TextureMemberF638 {
public:
    TextureMemberF638();
};
class SceneOwnerF638 {
public:
    SceneOwnerF638();
    virtual ~SceneOwnerF638();
    TextureMemberF638 texture;
};
SceneOwnerF638::SceneOwnerF638() {}

class SpriteMemberF638 {
public:
    SpriteMemberF638();
};
class SpriteContainerF638 {
public:
    SpriteContainerF638();
    unsigned int authenticUnknownPrefix;
    SpriteMemberF638 member;
};
SpriteContainerF638::SpriteContainerF638() {}
