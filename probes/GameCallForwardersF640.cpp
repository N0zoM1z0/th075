// F640: natural C++ grammar for true original game-facing 17-byte
// parameter forwarders and small thiscall helper leaves. Original
// C++ symbol/type names and source origin are unknown; do not
// add authored exact credit merely because game callers exist.

float __cdecl NativeFloatTargetAt40D920(float value);
float __cdecl NativeFloatTargetAt40D960(float value);
float __cdecl NativeFloatTargetAt412DB0(float value);
float __cdecl NativeFloatTargetAt428D40(float value);
float __cdecl NativeFloatTargetAt449A80(float value);
float __cdecl NativeFloatTargetAt641FB8(float value);

float __cdecl ForwardFloatAt40D900(float value) {
    return NativeFloatTargetAt40D920(value);
}
float __cdecl ForwardFloatAt40D940(float value) {
    return NativeFloatTargetAt40D960(value);
}
float __cdecl ForwardFloatAt412D90(float value) {
    return NativeFloatTargetAt412DB0(value);
}
float __cdecl ForwardFloatAt428D20(float value) {
    return NativeFloatTargetAt428D40(value);
}
float __cdecl ForwardFloatAt449A60(float value) {
    return NativeFloatTargetAt449A80(value);
}
float __cdecl ForwardFloatAt438A60(float value) {
    return NativeFloatTargetAt641FB8(value);
}

class NoopAt4073A0F640 { public: void Noop(); };
class NoopAt438CF0F640 { public: void Noop(); };
void NoopAt4073A0F640::Noop() {}
void NoopAt438CF0F640::Noop() {}

class ForwardMemberAt40E150F640 { public: void CallTarget(); };
class ForwardMemberAt40E2F0F640 { public: void CallTarget(); };
class ForwardMemberAt41A380F640 { public: void CallTarget(); };
class ForwardObjectAt40DE30F640:public ForwardMemberAt40E150F640 { public: void Forward(); };
class ForwardObjectAt40DF40F640:public ForwardMemberAt40E2F0F640 { public: void Forward(); };
class ForwardObjectAt40D8E0F640:public ForwardMemberAt41A380F640 { public: void Forward(); };
void ForwardObjectAt40DE30F640::Forward() { CallTarget(); }
void ForwardObjectAt40DF40F640::Forward() { CallTarget(); }
void ForwardObjectAt40D8E0F640::Forward() { CallTarget(); }

struct GameNativeFirstMemberF640 { GameNativeFirstMemberF640(); };
struct GameNativeContainerF640 {
    GameNativeContainerF640();
    GameNativeFirstMemberF640 first;
};
GameNativeContainerF640::GameNativeContainerF640() {}
