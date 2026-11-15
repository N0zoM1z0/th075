#include "CharacterObject.hpp"
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
class CharacterProjectileF379 : public CharacterObject {
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
#define OWNER (reinterpret_cast<CharacterFighterF379*>(owner))
#define OWNER_FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(owner)+(off)))
void CharacterProjectileF379::Advance() {
    if (field07C==5) {
        Destroy();
    } else if (OWNER_FIELD(short,0x60)>49 && OWNER_FIELD(short,0x60)<150 && animationStage<2) {
        Destroy();
        for(int i=0;i<1;++i) {
            OWNER->SpawnProjectile(996,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),1,1);
        }
        if (OWNER_FIELD(short,0xEFA)>25) {
            OWNER_FIELD(short,0xEFA)=0;
            OWNER->SpawnProjectile(995,reinterpret_cast<unsigned int&>(x),reinterpret_cast<unsigned int&>(y),1,1);
        }
    } else {
        if (animationStage==0 && animationFrame==0) {
            field0DA=static_cast<short>(field0C8);
            field0DC=static_cast<short>(field0CC);
            TriggerInteraction(0,0,0);
            field080=1;
            field07C=0;
            SetPolarVelocity(static_cast<float>(field0DC),static_cast<float>(field0DA)*g_PolarScaleAt00658044);
            scaleX=1.5f;scaleY=1.5f;
            color[0]=255;
            color[1]=255;
            color[2]=255;
            color[3]=255;
            rotationZ=AngleAt00483300(reinterpret_cast<unsigned int&>(velocityY),reinterpret_cast<unsigned int&>(velocityX))/g_AngleUnitAt00657828;
        }
        if ((field07C==1 || field07C==2 || field07C==4 || field07C==6) && animationStage<2) {
            SetMode(2);
            velocityX=0.0f;
            velocityY=0.0f;
        } else {
            if (animationStage<2) {
                SetPolarVelocity(static_cast<float>(field0DC),static_cast<float>(field0DA)*g_PolarScaleAt00658044);
                x=static_cast<float>(facing)*velocityX+x;
                y=y-velocityY;
            }
            if(animationStage==2) {
                // Parenthesized operand keeps the original x87 order (fld scaleX first).
                scaleX=(scaleX)*g_ProjectScaleF379At00659454;
                reinterpret_cast<unsigned int&>(scaleY)=reinterpret_cast<unsigned int&>(scaleX);
            }
            if(x>g_ProjectMaxXAt00659424 || x<g_ProjectMinXAt006595EC || y>g_ProjectMaxYAt006583B4 || y<g_ProjectMinXAt006595EC)
                Destroy();
            else if (CheckCollision()==field070) Destroy();
        }
    }
}
#undef OWNER_FIELD
#undef OWNER
