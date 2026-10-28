// R067 original complete 855-byte character-specific projectile controller.
// Observed original projectile-owner positional arguments are passed by
// their exact 32-bit float bits, avoiding unintended x87 conversions.
// One direct unparenthesized float lvalue retains the native VC7.1 EDX/EAX
// load ordering before the original FLD/FSUB Y-coordinate operation.
// The type/owner declarations are borrowed caller-side views only.
// Only native observed borrowed game-object fields and call ABIs are declared.
class CharacterFighterF379 {
public:
    void SpawnProjectile(int,unsigned int,unsigned int,unsigned char,int);
};
class CharacterProjectileF379 {
public:
    void Advance();
    void Destroy();
    void TriggerInteraction(int,int,int);
    void SetPolarVelocity(float angle,float speed);
    void SetMode(int);
    short CheckCollision();
};
extern float AngleAt00483300(unsigned int,unsigned int);
extern const float g_PolarScaleAt00658044;
extern const float g_AngleUnitAt00657828;
extern const float g_ProjectMinXAt006595EC;
extern const float g_ProjectMaxXAt00659424;
extern const float g_ProjectMaxYAt006583B4;
extern const float g_ProjectScaleF379At00659454;
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
#define FLOAT(off) (*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this)+(off)))
#define OWNER (reinterpret_cast<CharacterFighterF379*>(FIELD(void*,0xE4)))
#define OWNER_FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(FIELD(void*,0xE4))+(off)))
void CharacterProjectileF379::Advance() {
    if (FIELD(int,0x7C)==5) {
        Destroy();
    } else if (OWNER_FIELD(short,0x60)>49 && OWNER_FIELD(short,0x60)<150 && FIELD(short,0x62)<2) {
        Destroy();
        for(int i=0;i<1;++i) {
            OWNER->SpawnProjectile(996,FIELD(unsigned int,0x44),FIELD(unsigned int,0x48),1,1);
        }
        if (OWNER_FIELD(short,0xEFA)>25) {
            OWNER_FIELD(short,0xEFA)=0;
            OWNER->SpawnProjectile(995,FIELD(unsigned int,0x44),FIELD(unsigned int,0x48),1,1);
        }
    } else {
        if (FIELD(short,0x62)==0 && FIELD(short,0x64)==0) {
            FIELD(short,0xDA)=static_cast<short>(FLOAT(0xC8));
            FIELD(short,0xDC)=static_cast<short>(FLOAT(0xCC));
            TriggerInteraction(0,0,0);
            FIELD(short,0x80)=1;
            FIELD(int,0x7C)=0;
            SetPolarVelocity(static_cast<float>(FIELD(short,0xDC)),static_cast<float>(FIELD(short,0xDA))*g_PolarScaleAt00658044);
            FLOAT(0x1C)=1.5f;FLOAT(0x20)=1.5f;
            FIELD(unsigned char,0x11)=255;
            FIELD(unsigned char,0x12)=255;
            FIELD(unsigned char,0x13)=255;
            FIELD(unsigned char,0x14)=255;
            FLOAT(0x30)=AngleAt00483300(FIELD(unsigned int,0x54),FIELD(unsigned int,0x50))/g_AngleUnitAt00657828;
        }
        if ((FIELD(int,0x7C)==1 || FIELD(int,0x7C)==2 || FIELD(int,0x7C)==4 || FIELD(int,0x7C)==6) && FIELD(short,0x62)<2) {
            SetMode(2);
            FLOAT(0x50)=0.0f;
            FLOAT(0x54)=0.0f;
        } else {
            if (FIELD(short,0x62)<2) {
                SetPolarVelocity(static_cast<float>(FIELD(short,0xDC)),static_cast<float>(FIELD(short,0xDA))*g_PolarScaleAt00658044);
                FLOAT(0x44)=static_cast<float>(FIELD(signed char,0x66))*FLOAT(0x50)+FLOAT(0x44);
                *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this)+0x48)=*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this)+0x48)-*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this)+0x54);
            }
            if(FIELD(short,0x62)==2) {
                FLOAT(0x1C)=FLOAT(0x1C)*g_ProjectScaleF379At00659454;
                FIELD(unsigned int,0x20)=FIELD(unsigned int,0x1C);
            }
            if(FLOAT(0x44)>g_ProjectMaxXAt00659424 || FLOAT(0x44)<g_ProjectMinXAt006595EC || FLOAT(0x48)>g_ProjectMaxYAt006583B4 || FLOAT(0x48)<g_ProjectMinXAt006595EC)
                Destroy();
            else if (CheckCollision()==FIELD(short,0x70)) Destroy();
        }
    }
}
#undef OWNER_FIELD
#undef OWNER
#undef FLOAT
#undef FIELD
