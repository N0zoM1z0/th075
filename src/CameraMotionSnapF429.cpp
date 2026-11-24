#include "GeometryConstants.hpp"
#include "CameraMotion.hpp"

// Independent complete original game camera snap policy: true camera mode,
// borrowed globals and original camera offsets, without owner class guesses.
extern unsigned char g_CameraOverrideEnabledAt00671414;
extern float g_CameraHorizontalOverrideAt006713E8;
extern float g_CameraVerticalOverrideAt006713BC;
extern float g_CameraHorizontalTargetAt006713F0;
extern float g_CameraVerticalTargetAt00671400;
extern float g_CombatViewOffsetX;
extern float g_CombatViewOffsetY;
extern float g_CameraHorizontalAt006713E4;
extern float g_CameraVerticalAt00671408;
extern float g_CameraZoomOverrideAt006713F4;
extern float g_CameraZoomTargetAt006713C0;
extern float g_CombatViewSpan;
void CameraSnapF429::Snap() {
 if (g_CameraOverrideEnabledAt00671414) {
   g_CombatViewOffsetX=g_CameraHorizontalOverrideAt006713E8;
   g_CombatViewOffsetY=g_CameraVerticalOverrideAt006713BC+GeometryConstants::ThreeHundred;
   g_CameraHorizontalAt006713E4=g_CameraHorizontalOverrideAt006713E8;
   g_CameraVerticalAt00671408=g_CameraVerticalOverrideAt006713BC;
   g_CombatViewSpan=g_CameraZoomOverrideAt006713F4;
 } else {
   g_CombatViewOffsetX=g_CameraHorizontalTargetAt006713F0;
   g_CombatViewOffsetY=g_CameraVerticalTargetAt00671400+GeometryConstants::ThreeHundred;
   g_CameraHorizontalAt006713E4=g_CameraHorizontalTargetAt006713F0;
   g_CameraVerticalAt00671408=g_CameraVerticalTargetAt00671400;
   g_CombatViewSpan=g_CameraZoomTargetAt006713C0;
 }
}
