// Eleven independently native-exact original character auxiliary object
// constructors, complete R050 observed 134/146-byte original CODE each.
// Every derived native vtable address and the true borrowed base ctor
// target were physically checked against this original PE. The returned
// pointers and +0xD8..0xE2 shorts retain actual per-character differences.
// Each derived class is a borrowed ABI receiver; exact complete private
// object layouts and the base constructor implementation are NOT asserted.
class FighterObjectBaseF422 {
public:
    FighterObjectBaseF422();
    virtual ~FighterObjectBaseF422();
};

class ReimuObjectF422 : public FighterObjectBaseF422 {public: ReimuObjectF422(void* owner);};
class MarisaObjectF422 : public FighterObjectBaseF422 {public: MarisaObjectF422(void* owner);};
class SakuyaObjectF422 : public FighterObjectBaseF422 {public: SakuyaObjectF422(void* owner);};
class AliceObjectF422 : public FighterObjectBaseF422 {public: AliceObjectF422(void* owner);};
class PatchouliObjectF422 : public FighterObjectBaseF422 {public: PatchouliObjectF422(void* owner);};
class YoumuObjectF422 : public FighterObjectBaseF422 {public: YoumuObjectF422(void* owner);};
class RemiliaObjectF422 : public FighterObjectBaseF422 {public: RemiliaObjectF422(void* owner);};
class YuyukoObjectF422 : public FighterObjectBaseF422 {public: YuyukoObjectF422(void* owner);};
class YukariObjectF422 : public FighterObjectBaseF422 {public: YukariObjectF422(void* owner);};
class SuikaObjectF422 : public FighterObjectBaseF422 {public: SuikaObjectF422(void* owner);};
class MeilingObjectF422 : public FighterObjectBaseF422 {public: MeilingObjectF422(void* owner);};

#define RAW reinterpret_cast<unsigned char*>(this)
#define OWNER reinterpret_cast<unsigned char*>(owner)
#define FIELD(T,offset) (*reinterpret_cast<T*>(RAW+(offset)))

ReimuObjectF422::ReimuObjectF422(void* owner) {
    FIELD(void*,0xE4)=owner;
    FIELD(unsigned int,4)=*reinterpret_cast<unsigned int*>(OWNER+4);
    FIELD(void*,0xC4)=OWNER+0x468;
    FIELD(short,0xD8)=0;
    FIELD(short,0xDA)=0;
    FIELD(short,0xDC)=0;
    FIELD(short,0xDE)=0;
    FIELD(short,0xE0)=0;
}

MarisaObjectF422::MarisaObjectF422(void* owner) {
    FIELD(void*,0xE4)=owner;
    FIELD(unsigned int,4)=*reinterpret_cast<unsigned int*>(OWNER+4);
    FIELD(void*,0xC4)=OWNER+0x468;
    FIELD(short,0xD8)=0;
    FIELD(short,0xDA)=0;
    FIELD(short,0xDC)=0;
    FIELD(short,0xDE)=0;
    FIELD(short,0xE0)=0;
    FIELD(short,0xE2)=0;
}

SakuyaObjectF422::SakuyaObjectF422(void* owner) {
    FIELD(void*,0xE4)=owner;
    FIELD(unsigned int,4)=*reinterpret_cast<unsigned int*>(OWNER+4);
    FIELD(void*,0xC4)=OWNER+0x468;
    FIELD(short,0xD8)=0;
    FIELD(short,0xDA)=0;
    FIELD(short,0xDC)=0;
    FIELD(short,0xDE)=0;
    FIELD(short,0xE0)=0;
    FIELD(short,0xE2)=0;
}

AliceObjectF422::AliceObjectF422(void* owner) {
    FIELD(void*,0xE4)=owner;
    FIELD(unsigned int,4)=*reinterpret_cast<unsigned int*>(OWNER+4);
    FIELD(void*,0xC4)=OWNER+0x468;
    FIELD(short,0xD8)=0;
    FIELD(short,0xDA)=0;
    FIELD(short,0xDC)=0;
    FIELD(short,0xDE)=0;
    FIELD(short,0xE0)=0;
    FIELD(short,0xE2)=0;
}

PatchouliObjectF422::PatchouliObjectF422(void* owner) {
    FIELD(void*,0xE4)=owner;
    FIELD(unsigned int,4)=*reinterpret_cast<unsigned int*>(OWNER+4);
    FIELD(void*,0xC4)=OWNER+0x468;
    FIELD(short,0xD8)=0;
    FIELD(short,0xDA)=0;
    FIELD(short,0xDC)=0;
    FIELD(short,0xDE)=0;
    FIELD(short,0xE0)=0;
    FIELD(short,0xE2)=0;
}

YoumuObjectF422::YoumuObjectF422(void* owner) {
    FIELD(void*,0xE4)=owner;
    FIELD(unsigned int,4)=*reinterpret_cast<unsigned int*>(OWNER+4);
    FIELD(void*,0xC4)=OWNER+0x468;
    FIELD(short,0xD8)=0;
    FIELD(short,0xDA)=0;
    FIELD(short,0xDC)=0;
    FIELD(short,0xDE)=0;
    FIELD(short,0xE0)=0;
    FIELD(short,0xE2)=0;
}

RemiliaObjectF422::RemiliaObjectF422(void* owner) {
    FIELD(void*,0xE4)=owner;
    FIELD(unsigned int,4)=*reinterpret_cast<unsigned int*>(OWNER+4);
    FIELD(void*,0xC4)=OWNER+0x468;
    FIELD(short,0xD8)=0;
    FIELD(short,0xDA)=0;
    FIELD(short,0xDC)=0;
    FIELD(short,0xDE)=0;
    FIELD(short,0xE0)=0;
    FIELD(short,0xE2)=0;
}

YuyukoObjectF422::YuyukoObjectF422(void* owner) {
    FIELD(void*,0xE4)=owner;
    FIELD(unsigned int,4)=*reinterpret_cast<unsigned int*>(OWNER+4);
    FIELD(void*,0xC4)=OWNER+0x468;
    FIELD(short,0xD8)=0;
    FIELD(short,0xDA)=0;
    FIELD(short,0xDC)=0;
    FIELD(short,0xDE)=0;
    FIELD(short,0xE0)=0;
    FIELD(short,0xE2)=0;
}

YukariObjectF422::YukariObjectF422(void* owner) {
    FIELD(void*,0xE4)=owner;
    FIELD(unsigned int,4)=*reinterpret_cast<unsigned int*>(OWNER+4);
    FIELD(void*,0xC4)=OWNER+0x468;
    FIELD(short,0xD8)=0;
    FIELD(short,0xDA)=0;
    FIELD(short,0xDC)=0;
    FIELD(short,0xDE)=0;
    FIELD(short,0xE0)=0;
    FIELD(short,0xE2)=0;
}

SuikaObjectF422::SuikaObjectF422(void* owner) {
    FIELD(void*,0xE4)=owner;
    FIELD(unsigned int,4)=*reinterpret_cast<unsigned int*>(OWNER+4);
    FIELD(void*,0xC4)=OWNER+0x468;
    FIELD(short,0xD8)=0;
    FIELD(short,0xDA)=0;
    FIELD(short,0xDC)=0;
    FIELD(short,0xDE)=0;
    FIELD(short,0xE0)=0;
    FIELD(short,0xE2)=0;
}

MeilingObjectF422::MeilingObjectF422(void* owner) {
    FIELD(void*,0xE4)=owner;
    FIELD(unsigned int,4)=*reinterpret_cast<unsigned int*>(OWNER+4);
    FIELD(void*,0xC4)=OWNER+0x468;
    FIELD(short,0xD8)=0;
    FIELD(short,0xDA)=0;
    FIELD(short,0xDC)=0;
    FIELD(short,0xDE)=0;
    FIELD(short,0xE0)=0;
}

#undef FIELD
#undef OWNER
#undef RAW
