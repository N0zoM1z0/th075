// F644: complete original float-to-double CRT invocation adapters.
// The six normal VC7.1 28-byte whole CODE bodies are original game
// functions, but historical source-vs-generated ownership remains UNKNOWN.
// Actual native callee targets are read separately from the pinned PE.
extern double __cdecl NativeDoubleAt641754(double);
extern double __cdecl NativeDoubleAt641804(double);
extern double __cdecl NativeDoubleAt6418CD(double);
extern double __cdecl NativeDoubleAt641E54(double);
extern double __cdecl NativeDoubleAt641FD0(double);
extern double __cdecl NativeDoubleAt642120(double);
float __cdecl FloatAdapterAt40D920(float x) { return static_cast<float>(NativeDoubleAt641754(x)); }
float __cdecl FloatAdapterAt40D960(float x) { return static_cast<float>(NativeDoubleAt641804(x)); }
float __cdecl FloatAdapterAt412DB0(float x) { return static_cast<float>(NativeDoubleAt6418CD(x)); }
float __cdecl FloatAdapterAt428D40(float x) { return static_cast<float>(NativeDoubleAt641E54(x)); }
float __cdecl FloatAdapterAt442040(float x) { return static_cast<float>(NativeDoubleAt641FD0(x)); }
float __cdecl FloatAdapterAt449A80(float x) { return static_cast<float>(NativeDoubleAt642120(x)); }
