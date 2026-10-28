// Complete original R049 1757-byte character auxiliary state controller.
// The distinct active-round/two-mode actions and 30/70/57-facing effect
// offsets are independently observed in this original. The opponent call
// interface, inherited effect spawner and round-sound APIs are borrowed.
// Source uses actual native branch direction and a native short predecrement;
// no unused storage, full owner layout or invented control paths.
class CharacterAux004C49C0F371 {public:
 void AdvanceAuxiliary();
 void SpawnTrackedEffect(short,float,float,signed char,signed char,unsigned char);
 void EnableRoundSound(int);
 void InterruptSpecial(int);
};
class OpponentControlF371 {public: void TriggerBlockedAction(int,int,int);};
#define FIELD(type,offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(offset)))
#define FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this)+(offset))
#define OPPONENT_FIELD(type,offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(FIELD(void*,0x2E8))+(offset)))
#define OPPONENT_FLOAT(offset) *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(FIELD(void*,0x2E8))+(offset))
void CharacterAux004C49C0F371::AdvanceAuxiliary() {
    if(FLOAT(0x50)==0.0f && FIELD(signed char,0x3AC)>0) FIELD(signed char,0x3AC)=0;
    if(FIELD(short,0xF0C)>0) {
        if(FIELD(short,0xF0E)<=0) { EnableRoundSound(1);FIELD(short,0xF0E)=1; }
        else { --FIELD(short,0xF0E); }
        FLOAT(0x9C)=0.75f;
        FIELD(short,0xF0C)=FIELD(short,0x3B0);
        if(FIELD(short,0x60)!=0x2C1 && FIELD(short,0x60)!=0x2C3) {
            if(FIELD(signed char,0x39D)==2) {
                if(FIELD(short,0x3B0)>8) InterruptSpecial(8);
                else FIELD(short,0xF0C)=0;
            }
            if(FIELD(signed char,0x39D)==1) {
                if(FIELD(short,0x3B0)>4) InterruptSpecial(4);
                else FIELD(short,0xF0C)=0;
            }
        }
    }
    else FLOAT(0x9C)=1.0f;
    if(FIELD(short,0xF12)>0) {
        FIELD(short,0x84)=2;FIELD(short,0x88)=2;
        if(FIELD(short,0xF10)<=0) {
            FIELD(short,0xF10)=0;FIELD(short,0xF12)=0;
            OPPONENT_FIELD(short,0x3BC)=0;
            OPPONENT_FIELD(unsigned char,0x10)=0;
        }
        if(FIELD(short,0xF10)>0 && FIELD(short,0x60)!=0x2C0 && FIELD(short,0x60)!=0x2C2) {
            FIELD(short,0xF10)=FIELD(short,0x3B0);
            FIELD(short,0x3B8)=2;
            if(FIELD(signed char,0x39D)==2) {
                if(FIELD(short,0x3B0)>8) InterruptSpecial(8);
                else FIELD(short,0xF10)=0;
            }
            if(FIELD(signed char,0x39D)==1) {
                if(FIELD(short,0x3B0)>5) InterruptSpecial(5);
                else FIELD(short,0xF10)=0;
            }
            reinterpret_cast<OpponentControlF371*>(FIELD(void*,0x2E8))->TriggerBlockedAction(0,0,0);
            OPPONENT_FIELD(unsigned char,0x10)=0x82;
        }
    }
    if (FIELD(short, 0x60) > 149 && FIELD(short, 0x60) < 154 && FIELD(short,0x62)==0 && FIELD(short,0x64)==0 && FIELD(short,0xF0A)==0) {
            FIELD(short, 0x2F6) = 0;
            FIELD(short, 0x2F8) = 0;
            FIELD(short, 0x2FA) = 0;
            FLOAT(0x2FC) = 1.0f;
            FLOAT(0x300) = 1.0f;
            FIELD(unsigned char, 0x2F1) = 255;
            FIELD(unsigned char, 0x2F2) = 255;
            FIELD(unsigned char, 0x2F3) = 255;
            FIELD(unsigned char, 0x2F4) = 255;
            FLOAT(0x308) = 0.0f;
            FLOAT(0x30C) = 50.0f;
            FLOAT(0x310) = 0.0f;
            SpawnTrackedEffect(817, FIELD(signed char, 0x66) * 30 + FLOAT(0x44), FLOAT(0x48) + 94.0f, FIELD(signed char, 0x66), 1, 1);
            FIELD(short, 0xF0A) = 1;
        }
    if (FIELD(short, 0x60) > 153 && FIELD(short, 0x60) < 158 && FIELD(short,0x62)==0 && FIELD(short,0x64)==0 && FIELD(short,0xF0A)==0) {
            FIELD(short, 0x2F6) = 0;
            FIELD(short, 0x2F8) = 0;
            FIELD(short, 0x2FA) = 0;
            FLOAT(0x2FC) = 1.0f;
            FLOAT(0x300) = 1.0f;
            FIELD(unsigned char, 0x2F1) = 255;
            FIELD(unsigned char, 0x2F2) = 255;
            FIELD(unsigned char, 0x2F3) = 255;
            FIELD(unsigned char, 0x2F4) = 255;
            FLOAT(0x308) = 0.0f;
            FLOAT(0x30C) = 50.0f;
            FLOAT(0x310) = 0.0f;
            SpawnTrackedEffect(817, FIELD(signed char, 0x66) * 70 + FLOAT(0x44), FLOAT(0x48) + 60.0f, FIELD(signed char, 0x66), 1, 1);
            FIELD(short, 0xF0A) = 1;
        }
    if (FIELD(short, 0x60) == 158 && FIELD(short,0x62)==0 && FIELD(short,0x64)==0 && FIELD(short,0xF0A)==0) {
            FIELD(short, 0x2F6) = 0;
            FIELD(short, 0x2F8) = 0;
            FIELD(short, 0x2FA) = 0;
            FLOAT(0x2FC) = 1.0f;
            FLOAT(0x300) = 1.0f;
            FIELD(unsigned char, 0x2F1) = 255;
            FIELD(unsigned char, 0x2F2) = 255;
            FIELD(unsigned char, 0x2F3) = 255;
            FIELD(unsigned char, 0x2F4) = 255;
            FLOAT(0x308) = 0.0f;
            FLOAT(0x30C) = 50.0f;
            FLOAT(0x310) = 0.0f;
            SpawnTrackedEffect(817, FIELD(signed char, 0x66) * 57 + FLOAT(0x44), FLOAT(0x48) + 100.0f, FIELD(signed char, 0x66), 1, 1);
            FIELD(short, 0xF0A) = 1;
        }
    if(FLOAT(0x44)-OPPONENT_FLOAT(0x44)>540.0f || FLOAT(0x44)-OPPONENT_FLOAT(0x44)<-540.0f) FIELD(short,0xF16)=60;
    if(FLOAT(0x44)-OPPONENT_FLOAT(0x44)>320.0f || FLOAT(0x44)-OPPONENT_FLOAT(0x44)<-320.0f) {
        FIELD(short,0xF16)=FIELD(short,0xF16)+1;
        if(FIELD(short,0xF16)>60) FIELD(short,0xF16)=60;
    } else FIELD(short,0xF16)=0;
}
#undef OPPONENT_FLOAT
#undef OPPONENT_FIELD
#undef FLOAT
#undef FIELD
