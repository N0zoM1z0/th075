#ifndef TH075_FIGHTER_OVERLAY_DRAWING_F163_HPP
#define TH075_FIGHTER_OVERLAY_DRAWING_F163_HPP

#include "StaffTimeline438D00.hpp"

// Call-only fighter view. Original names and complete owner layout stay unknown.
// Never construct or embed this view.
class FighterOverlayDrawingF163 {
public:
    void RenderSideEffect();
    void DrawFacingSprite(short sprite, float position, float y, DWORD color);
    void RenderFadeOverlay();
};

#endif
