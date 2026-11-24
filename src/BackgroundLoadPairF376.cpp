#include "BackgroundStages.hpp"

extern const char g_BGDirectory00aF376[];
extern const char g_BGFilename00aF376[];
extern const char g_BGDirectory00bF376[];
extern const char g_BGFilename00bF376[];
Background00aF376::Background00aF376()
{
    textureManager.AllocateUnformattedSlots(3);
    textureManager.LoadDefault(g_BGFilename00aF376, g_BGDirectory00aF376);
    parameters.zero.zeroAt0C = 0;
    parameters.zero.zeroAt10 = 0;
    parameters.zero.zeroAt14 = 0;
}

Background00bF376::Background00bF376()
{
    textureManager.AllocateUnformattedSlots(4);
    textureManager.LoadDefault(g_BGFilename00bF376, g_BGDirectory00bF376);
    parameters.zero.zeroAt0C = 0;
    parameters.zero.zeroAt10 = 0;
    parameters.zero.zeroAt14 = 0;
    field68 = 0;
}
