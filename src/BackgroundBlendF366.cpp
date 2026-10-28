// Three independent R231-authored stage camera blend policies share a native
// /Od compiler shape, but each has its own real original 60-byte extent.
// The x/y camera coordinates are genuinely computed and stored in the
// original body even though its immediate caller only sets the blend mode.
class BackgroundDrawerF366 {public: void SetBlendMode(int mode);};
class BackgroundBlendF366 {public:
 void ApplyBG02aBlend();
 void ApplyBG02bBlend();
 void ApplyBG02cBlend();
};
extern float g_BGCameraXAt00671404;
extern float g_BGCameraYAt006713C4;
extern const float g_BGOffsetXAt00657834;
#define CAMERA (*reinterpret_cast<BackgroundDrawerF366*>(reinterpret_cast<unsigned char*>(this)+0x18))
void BackgroundBlendF366::ApplyBG02aBlend() {
 int x=static_cast<int>(g_BGCameraXAt00671404+g_BGOffsetXAt00657834);
 int y=static_cast<int>(g_BGCameraYAt006713C4);
 CAMERA.SetBlendMode(0);
}
void BackgroundBlendF366::ApplyBG02bBlend() {
 int x=static_cast<int>(g_BGCameraXAt00671404+g_BGOffsetXAt00657834);
 int y=static_cast<int>(g_BGCameraYAt006713C4);
 CAMERA.SetBlendMode(0);
}
void BackgroundBlendF366::ApplyBG02cBlend() {
 int x=static_cast<int>(g_BGCameraXAt00671404+g_BGOffsetXAt00657834);
 int y=static_cast<int>(g_BGCameraYAt006713C4);
 CAMERA.SetBlendMode(0);
}
#undef CAMERA
