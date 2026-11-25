#include "battle/Fighter.hpp"
#include "engine/GeometryConstants.hpp"

extern float g_CombatOutputXAt006714A8;
extern float g_CombatOutputYAt0067142C;

void Fighter::MapWorldToScreen(float x, float y) {
    float width = viewRight - cameraState.viewLeft;
    float height = viewTop - viewBottom;
    g_CombatOutputXAt006714A8 = (x - cameraState.viewLeft) / width * GeometryConstants::SixHundredForty;
    g_CombatOutputYAt0067142C = (viewTop - y) / height * GeometryConstants::FourHundredEighty;
}
