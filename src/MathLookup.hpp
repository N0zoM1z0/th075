#ifndef TH075_MATH_LOOKUP_HPP
#define TH075_MATH_LOOKUP_HPP

namespace MathLookup
{
    void BuildCosTable();
    float ReadCosTable(float angle);
    float ReadPhaseTable(float angle);
    float ReadRatio(float angle);
}

#endif
