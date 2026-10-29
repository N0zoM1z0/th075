// F648 original full game object tiny state and forwarding C++ source.
// Historical class identity/explicit-vs-generated origin UNKNOWN.
// Only real observed member accesses, no fabricated stack or assembly.
class ModeSetterF648 {
public:
    void Set(short value);
};
void ModeSetterF648::Set(short value) {
    *reinterpret_cast<short*>(reinterpret_cast<char*>(this)+0x12)=value;
}
class PointerAdvanceF648 {
public:
    char* current;
    PointerAdvanceF648* Advance();
};
PointerAdvanceF648* PointerAdvanceF648::Advance() {
    current += 0x10;
    return this;
}
class StateMemberF648 {public: void ResetAt411C70();};
class StateOwnerF648 {public: void ResetMember();};
void StateOwnerF648::ResetMember() {
    reinterpret_cast<StateMemberF648*>(reinterpret_cast<char*>(this)+4)->ResetAt411C70();
}
class StatefulMemberF648 {public: void InitializeAt422A50(int);};
class StatefulOwnerF648: public StatefulMemberF648 {
public: StatefulOwnerF648(int argument);
};
StatefulOwnerF648::StatefulOwnerF648(int argument) { InitializeAt422A50(argument); }

class ObjectAt40FA00F648 {public: void Invoke(int);};
class ObjectAt422A20F648 {public: void Invoke(int);};
class ObjectAt45B6C0F648 {public: void Invoke(int);};
class ObjectAt5FAAE0F648 {public: void Invoke(int);};
void __cdecl ForwardAt40F9F0(ObjectAt40FA00F648* receiver) {receiver->Invoke(0);}
void __cdecl ForwardAt4229C0(ObjectAt422A20F648* receiver) {receiver->Invoke(0);}
void __cdecl ForwardAt45B6B0(ObjectAt45B6C0F648* receiver) {receiver->Invoke(0);}
void __cdecl ForwardAt5FAAD0(ObjectAt5FAAE0F648* receiver) {receiver->Invoke(0);}
