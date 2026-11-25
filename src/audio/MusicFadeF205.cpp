#include "audio/AudioControl.hpp"
namespace MusicF205 {
void ScheduleTransitionFade()
{
    AudioControl407CA0::ScheduleFade(-6000, -200, 1, 1);
}
}
