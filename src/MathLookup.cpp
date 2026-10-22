#include "MathLookup.hpp"
#include <math.h>
#include <stdlib.h>

namespace MathLookup
{
    // Only the 3,600-entry used range is established. The original allocation
    // and runtime contents are unknown; no replacement table is embedded here.
    extern float g_CosineTable[];

    void BuildCosTable()
    {
        for (int index = 0; index < 3600; ++index)
            g_CosineTable[index] = static_cast<float>(
                cos(index / 10.0 * 3.1415926535 / 180.0));
    }

    float ReadCosTable(float angle)
    {
        return g_CosineTable[abs(static_cast<int>(angle * 10.0f)) % 3600];
    }

    float ReadPhaseTable(float angle)
    {
        return g_CosineTable[abs(static_cast<int>(angle * 10.0f - 900.0f)) % 3600];
    }

    float ReadRatio(float angle)
    {
        if (ReadCosTable(angle) == 0.0f)
            return 0.0f;
        return ReadPhaseTable(angle) / ReadCosTable(angle);
    }
}
