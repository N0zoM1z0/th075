#include "TextureManagerF198.hpp"
#include "DiagnosticLog.hpp"
#include <windows.h>
extern const char g_EffectsLogStartAt0065A078[];
extern const char g_EffectsFileAt0065A090[];
extern const char g_EffectsArchiveRootAt0065A088[];
extern const char g_EffectsLogCompleteAt0065A0A8[];
class EffectsResourcesF293 {
public:
 void LoadPatternCatalog();
 void LoadResources();
private:
 unsigned char unknown000[0x28];
 TextureManagerF198 texture;
};
void EffectsResourcesF293::LoadResources()
{
 LoadPatternCatalog();
 DiagnosticLog::AppendString(g_EffectsLogStartAt0065A078);
 texture.AllocateTextureSlots(0x90,0x10);
 texture.LoadDefault(g_EffectsFileAt0065A090,g_EffectsArchiveRootAt0065A088);
 DiagnosticLog::AppendString(g_EffectsLogCompleteAt0065A0A8);
}
