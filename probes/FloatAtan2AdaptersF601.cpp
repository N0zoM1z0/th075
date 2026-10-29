// F601: two complete original PE cdecl float atan2 adapters. Their native
// 21/37-byte original bodies are C++ compiler-reproducible, but historical
// source origin is UNKNOWN. This is a reconstruction PROBE, not author credit.
// The original 0x00483320 calls the real VC7.1 CRT _atan2 at 0x00642240;
// the 0x00483300 forwarder calls this second complete original leaf.
extern "C" double __cdecl atan2(double y, double x);
float __cdecl FloatAtan2ThroughDoubleF601(float y, float x) {
    return static_cast<float>(atan2(y, x));
}
float __cdecl FloatAtan2ForwardF601(float y,float x) {
    return FloatAtan2ThroughDoubleF601(y,x);
}
