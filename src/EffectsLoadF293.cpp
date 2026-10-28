#include <windows.h>
class EffectsTextureF293 {
public:
 void AllocatePages(int pages,int width);
 void LoadFromArchive(const char* file,const char* root);
};
extern const char g_EffectsLogStartAt0065A078[];
extern const char g_EffectsFileAt0065A090[];
extern const char g_EffectsArchiveRootAt0065A088[];
extern const char g_EffectsLogCompleteAt0065A0A8[];
namespace EffectsLogF293 { void Printf(const char* text); }
class EffectsResourcesF293 {
public:
 void LoadPatternCatalog();
 void LoadResources();
};
void EffectsResourcesF293::LoadResources()
{
 LoadPatternCatalog();
 EffectsLogF293::Printf(g_EffectsLogStartAt0065A078);
 reinterpret_cast<EffectsTextureF293*>(reinterpret_cast<unsigned char*>(this)+0x28)->AllocatePages(0x90,0x10);
 reinterpret_cast<EffectsTextureF293*>(reinterpret_cast<unsigned char*>(this)+0x28)->LoadFromArchive(g_EffectsFileAt0065A090,g_EffectsArchiveRootAt0065A088);
 EffectsLogF293::Printf(g_EffectsLogCompleteAt0065A0A8);
}
