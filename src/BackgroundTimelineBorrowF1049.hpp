#pragma once
#include "StaffTimeline438D00.hpp"

// Physical TH075 background stage receiver +0x18 is a directly borrowed
// TimelineDrawing438D00 call interface. This is a pointer into the real
// background owner, not a separate owner pointer stored at +0x18.
// Its enclosing background's lifetime and full type remain unknown.
// Do not instantiate or embed this incomplete view or add a fake member.
#define F1049_BACKGROUND_TIMELINE(stage) (*reinterpret_cast<TimelineDrawing438D00*>(reinterpret_cast<unsigned char*>(stage) + 0x18))
