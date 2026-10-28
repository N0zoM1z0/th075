// Native-observed FighterBase ctor and derived vtable installation; only
// explicit independently observed +0x4C..0x98 native zero fields here.
class NativeFighterBaseF300 {
public:
 NativeFighterBaseF300();
 virtual void Slot0();
};
class BattleObjectDefaultsF300 : public NativeFighterBaseF300 {
public:
 BattleObjectDefaultsF300();
 virtual void Slot0();
};
#define FIELD(type,offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(offset)))
BattleObjectDefaultsF300::BattleObjectDefaultsF300()
{
 FIELD(short,0x80)=0;
 FIELD(unsigned int,0x7c)=0;
 FIELD(short,0x82)=0;
 FIELD(unsigned int,0x8c)=0;
 FIELD(unsigned int,0x90)=0;
 FIELD(unsigned int,0x94)=0;
 FIELD(unsigned int,0x98)=0;
 FIELD(unsigned int,0x50)=0;
 FIELD(unsigned int,0x54)=0;
 FIELD(unsigned int,0x58)=0;
 FIELD(unsigned int,0x5c)=0;
 FIELD(unsigned int,0x4c)=0;
 FIELD(short,0x84)=0;
 FIELD(short,0x86)=0;
 FIELD(short,0x88)=0;
}
#undef FIELD
