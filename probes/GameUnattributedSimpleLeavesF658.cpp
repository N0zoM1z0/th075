// Diagnostic grammar only: historical class/source owner UNKNOWN.
extern "C" void Empty_00412580() {}
extern "C" void Empty_00412600() {}
extern "C" void Empty_0041F9F0() {}
extern "C" void Empty_0041FDF0() {}
extern "C" void Empty_0042E580() {}
extern "C" void Empty_00532480() {}
extern "C" void Empty_00532500() {}

extern "C" void* IdentityArg_00411E80(void* p) {return p;}
extern "C" void* IdentityArg_0041E100(void* p) {return p;}
extern "C" void* IdentityArg_00531D80(void* p) {return p;}
extern "C" char* Plus4_00411E90(char* p) {return p+4;}
extern "C" char* Plus4_0041E110(char* p) {return p+4;}
extern "C" char* Plus4_00531D90(char* p) {return p+4;}
extern "C" char* Plus8_004124C0(char* p) {return p+8;}

class FirstField_0040E9B0 {public: void* Get();};
class FirstField_0040EA20 {public: void* Get();};
class FirstField_004124B0 {public: void* Get();};
class FirstField_00532350 {public: void* Get();};
void* FirstField_0040E9B0::Get() { return *reinterpret_cast<void**>(this); }
void* FirstField_0040EA20::Get() { return *reinterpret_cast<void**>(this); }
void* FirstField_004124B0::Get() { return *reinterpret_cast<void**>(this); }
void* FirstField_00532350::Get() { return *reinterpret_cast<void**>(this); }
class Receiver_0041E330 {public: Receiver_0041E330* Get();};
Receiver_0041E330* Receiver_0041E330::Get() { return this; }
