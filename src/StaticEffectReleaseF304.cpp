#include <windows.h>
// Physical subobject addresses and the actual lifetime-bearing owner are
// borrowed from 0x005F6FF0, not an assertion of private gameplay contents.
class ResourceSideEffectsF304 {
 unsigned int physicallyObservedWords[5];
public: ~ResourceSideEffectsF304();
};
typedef char CheckResourceSide20F304[(sizeof(ResourceSideEffectsF304)==0x14)?1:-1];
class ResourceTextureF304 {
 unsigned int physicallyObservedWords[20];
public: ~ResourceTextureF304();
};
typedef char CheckTexture80F304[(sizeof(ResourceTextureF304)==0x50)?1:-1];
class EffectRecordListF304 {
public:
    ~EffectRecordListF304();
    unsigned int Size();
    void** At(unsigned int index);
    void Clear();
};
class EffectCatalogF304 {
public:
    ~EffectCatalogF304();
    void CleanupGraphics();
private:
    ResourceSideEffectsF304 sides[2];
    ResourceTextureF304 texture;
    EffectRecordListF304 records;
};
class EffectRecordF304 {public: ~EffectRecordF304();};
EffectCatalogF304::~EffectCatalogF304()
{
    CleanupGraphics();
    for (unsigned int index=0; index<records.Size(); ++index) {
        if (*records.At(index))
            delete static_cast<EffectRecordF304*>(*records.At(index));
    }
    records.Clear();
}
