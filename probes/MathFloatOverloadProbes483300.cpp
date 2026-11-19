#include <math.h>

// Native float->float C++ wrapper prototypes, pending authored/library
// provenance review; these are source experiments, not accepted game CODE.
float __cdecl FloatAtanInner483320(float y, float x);
float __cdecl FloatAtanOuter483300(float y, float x) {
    return FloatAtanInner483320(y, x);
}
float __cdecl FloatAtanInner483320(float y, float x) {
    return static_cast<float>(atan2(static_cast<double>(y), static_cast<double>(x)));
}
float __cdecl FloatAbsInner412DB0(float x);
float __cdecl FloatAbsOuter412D90(float x) {
    return FloatAbsInner412DB0(x);
}
float __cdecl FloatAbsInner412DB0(float x) {
    return static_cast<float>(fabs(static_cast<double>(x)));
}
float __cdecl FloatSqrtInner428D40(float x);
float __cdecl FloatSqrtOuter428D20(float x) {
    return FloatSqrtInner428D40(x);
}
float __cdecl FloatSqrtInner428D40(float x) {
    return static_cast<float>(sqrt(static_cast<double>(x)));
}
