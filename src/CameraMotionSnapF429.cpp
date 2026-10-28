// Independent complete original game camera snap policy: true camera mode,
// borrowed globals and original camera offsets, without owner class guesses.
extern unsigned char g_CameraChooseCurrentAt00671414;
extern float g_CameraCurrentXAt006713E8;
extern float g_CameraCurrentYAt006713BC;
extern float g_CameraAlternateXAt006713F0;
extern float g_CameraAlternateYAt00671400;
extern float g_CameraActualXAt00671404;
extern float g_CameraActualYAt006713C4;
extern float g_CameraInitialXAt006713E4;
extern float g_CameraInitialYAt00671408;
extern float g_CameraCurrentZAt006713F4;
extern float g_CameraAlternateZAt006713C0;
extern float g_CameraActualZAt006713DC;
extern const float g_CameraYOffsetAt0065784C;
namespace CameraSnapF429 {void Snap();}
void CameraSnapF429::Snap() {
 if (g_CameraChooseCurrentAt00671414) {
   g_CameraActualXAt00671404=g_CameraCurrentXAt006713E8;
   g_CameraActualYAt006713C4=g_CameraCurrentYAt006713BC+g_CameraYOffsetAt0065784C;
   g_CameraInitialXAt006713E4=g_CameraCurrentXAt006713E8;
   g_CameraInitialYAt00671408=g_CameraCurrentYAt006713BC;
   g_CameraActualZAt006713DC=g_CameraCurrentZAt006713F4;
 } else {
   g_CameraActualXAt00671404=g_CameraAlternateXAt006713F0;
   g_CameraActualYAt006713C4=g_CameraAlternateYAt00671400+g_CameraYOffsetAt0065784C;
   g_CameraInitialXAt006713E4=g_CameraAlternateXAt006713F0;
   g_CameraInitialYAt00671408=g_CameraAlternateYAt00671400;
   g_CameraActualZAt006713DC=g_CameraAlternateZAt006713C0;
 }
}
