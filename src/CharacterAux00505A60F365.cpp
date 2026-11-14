#include "Fighter.hpp"
// F365: independently checked COMPLETE native 1,576-byte extended character special effect
// controller. Like the already exact F062, this uses the same inherited
// effect-spawner ABI, but its effect 817, scale 1.0f, linked flag one and
// +0xF12 distance counter are independently verified for THIS target.
// The original computes signed angular timers, a true signed comparison
// direction, directional random projectiles and three linked effects. The
// compiler register state at the F0E timer depends on authentic compound
// += (not a semantically equivalent ordinary assignment). The direction
// boolean is naturally inlined, not stored in an invented helper local.
// Declaration-only receiver view: full original fighter layout is unknown.
class CharacterAux00505A60F365 : public Fighter {
public:
    void UpdateAuxiliary();
    void SpawnTrackedEffect(short, float, float, signed char, signed char, unsigned char);
    int Rand(int,int);
    void SpawnProjectile(int,float,float,unsigned char,int);
public:
    // Character-specific fields after the shared Fighter layout.
    short fieldF10;
    short fieldF12;
};



extern const float g_SpecialPowerStepAt006590B4;
// Names are provisional. Only these field accesses and receiver ABI are observed.
void CharacterAux00505A60F365::UpdateAuxiliary() {
    if (velocityX == 0.0f && field3AC > 0) {
        field3AC = 0;
    }
    if (field3B8 == 0)
        fieldF0E += facing * 5;
    if (fieldF0E < 0) fieldF0E = 359;
    if (fieldF0E >= 360) fieldF0E = 0;
    if (field3B8 == 0)
        fieldF0C = fieldF0C + 2;
    if (fieldF0C < 0) fieldF0C = 359;
    if (fieldF0C >= 360) fieldF0C = 0;
    if (fieldF10 > 0) {
        field490 = float(fieldF10+20) * g_SpecialPowerStepAt006590B4 * float(facing*opponent->facing) * float(int(((opponent->x - x) * facing > 0.0f))*2-1);
        fieldF10 = fieldF10-2;
        if (Rand(0,100)<50)
            SpawnProjectile(0x38c, float(Rand(0,640)*facing)+x,0.0f,reinterpret_cast<unsigned char&>(facing),1);
        else
            SpawnProjectile(0x38c, x-float(Rand(0,640)*facing),0.0f,-facing,1);
        if (fieldF10<0) fieldF10=0;
    }
    if (fieldF0A != 1) {
        if (action > 149 && action < 154) {
            field2F6 = 0;
            field2F8 = 0;
            field2FA = 0;
            field2FC = 1.0f;
            field300 = 1.0f;
            field2F1 = 255;
            field2F2 = 255;
            field2F3 = 255;
            field2F4 = 255;
            field308 = 0.0f;
            field30C = 50.0f;
            field310 = 0.0f;
            SpawnTrackedEffect(817, facing * 57 + x, y + 94.0f, facing, 1, 1);
            fieldF0A = 1;
        }
        if (action > 153 && action < 158) {
            field2F6 = 0;
            field2F8 = 0;
            field2FA = 0;
            field2FC = 1.0f;
            field300 = 1.0f;
            field2F1 = 255;
            field2F2 = 255;
            field2F3 = 255;
            field2F4 = 255;
            field308 = 0.0f;
            field30C = 50.0f;
            field310 = 0.0f;
            SpawnTrackedEffect(817, facing * 57 + x, y + 60.0f, facing, 1, 1);
            fieldF0A = 1;
        }
        if (action == 158) {
            field2F6 = 0;
            field2F8 = 0;
            field2FA = 0;
            field2FC = 1.0f;
            field300 = 1.0f;
            field2F1 = 255;
            field2F2 = 255;
            field2F3 = 255;
            field2F4 = 255;
            field308 = 0.0f;
            field30C = 50.0f;
            field310 = 0.0f;
            SpawnTrackedEffect(817, facing * 57 + x, y + 100.0f, facing, 1, 1);
            fieldF0A = 1;
        }
    }
    if (x - opponent->x > 540.0f || x - opponent->x < -540.0f) {
        fieldF12 = 60;
    }
    if (x - opponent->x > 320.0f || x - opponent->x < -320.0f) {
        fieldF12 = fieldF12 + 1;
        if (fieldF12 > 60) fieldF12 = 60;
    }
    else {
        fieldF12 = 0;
    }
}
