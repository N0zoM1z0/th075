// Natural compact source alternatives; none declares a private game owner.
extern float ObservedBackgroundX;
extern float ObservedBackgroundY;
int ConvertBackgroundX() { return static_cast<int>(ObservedBackgroundX + 160.0f); }
int ConvertBackgroundY() { return static_cast<int>(ObservedBackgroundY); }
struct TextureObservation { void SetBlendMode(int mode); };
struct BackgroundBlendObservation {
    TextureObservation texture;
    void ApplyZero();
    void ApplyOne();
};
void BackgroundBlendObservation::ApplyZero() { texture.SetBlendMode(0); }
void BackgroundBlendObservation::ApplyOne() { texture.SetBlendMode(1); }
struct BlendCopyObservation { int mode; };
BlendCopyObservation CopyBlendObservation(const BlendCopyObservation& source) { return source; }
extern const unsigned long BackgroundBlendLayout[] = {
    sizeof(TextureObservation), sizeof(BackgroundBlendObservation),
    sizeof(BlendCopyObservation), sizeof(float)
};
