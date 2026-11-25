#include "battle/CombatEffects.hpp"
#include "platform/DiagnosticLog.hpp"
#include <windows.h>
extern const char g_EffectsLogStartAt0065A078[] = "LoadEffect...\r\n";
extern const char g_EffectsFileAt0065A090[] = "data\\system\\effect.dat";
extern const char g_EffectsArchiveRootAt0065A088[] = "data";
extern const char g_EffectsLogCompleteAt0065A0A8[] = "LoadEffect...\r\n";
void CombatEffects::LoadResources()
{
 LoadPatternCatalog();
 DiagnosticLog::AppendString(g_EffectsLogStartAt0065A078);
 texture.AllocateTextureSlots(0x90,0x10);
 texture.LoadDefault(g_EffectsFileAt0065A090,g_EffectsArchiveRootAt0065A088);
 DiagnosticLog::AppendString(g_EffectsLogCompleteAt0065A0A8);
}
