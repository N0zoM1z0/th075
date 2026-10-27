// Call-only view of the already independently reconstructed audio
// fade scheduler at 00407E60; no stream manager layout assumed.
namespace AudioFadeF205 {
void __cdecl ScheduleFade(long targetVolume, long fadeStep,
                          unsigned char finishFlag, unsigned char startFlag);
}
namespace MusicF205 {
void ScheduleTransitionFade()
{
    AudioFadeF205::ScheduleFade(-6000, -200, 1, 1);
}
}
