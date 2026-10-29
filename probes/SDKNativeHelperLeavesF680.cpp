// F680: five entire original unknown-origin optimized native helper bodies.
// All C++ owner/method names are compiler grammar only, not attribution.
// Natural source and real ABI; no ASM, source byte grafts, fake locals.
extern "C" __declspec(dllimport) void __stdcall ImportedFree(void*);
extern "C" void __cdecl SDKCFree(void*);
class FreeImportedMember { public: void* ptr; void Cleanup(); };
class FreeDirectMember { public: void* ptr; void Cleanup(); };
class ClearReturnMember { public: unsigned int flags; ClearReturnMember* Reset(); };
class SentinelMember { public: unsigned int tag; void Finish(); void MaybeFinish(); };
class NativeForwarder { public: void Target(); void Forward(); };
void FreeImportedMember::Cleanup() { if (ptr) ImportedFree(ptr); }
void FreeDirectMember::Cleanup() { if (ptr) SDKCFree(ptr); }
ClearReturnMember* ClearReturnMember::Reset() { flags = 0; return this; }
void SentinelMember::MaybeFinish() { if (tag != static_cast<unsigned int>(-1)) Finish(); }
void NativeForwarder::Forward() { Target(); }
