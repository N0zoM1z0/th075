#ifndef TH075_FIGHTER_OVERLAY_DRAWING_F163_HPP
#define TH075_FIGHTER_OVERLAY_DRAWING_F163_HPP

#include "battle/Fighter.hpp"
#include "ui/StaffTimeline438D00.hpp"

class FighterOverlayDrawingF163 : public Fighter {
public:
    void RenderSideEffect();
    void DrawFacingSprite(short sprite, float position, float y, DWORD color);
    void RenderFadeOverlay();
};

#endif
