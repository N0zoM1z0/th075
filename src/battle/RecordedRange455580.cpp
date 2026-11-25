#include "replay/ReplayMode.hpp"
#include "battle/BattleSessionState.hpp"
#include "replay/ReplayRecords.hpp"
#include "battle/Actor.hpp"
#include <cstdlib>

int Actor::RecordedRange(int lower, int upper) {
    short sample = 0;
    if (g_ReplayModeAt0066C238 == ReplayMode::Playback) {
        if (g_ReplayRecords.randomSamplesAndAiTimers.size() > 0) {
            sample = g_ReplayRecords.randomSamplesAndAiTimers.front();
            g_ReplayRecords.randomSamplesAndAiTimers.pop_front();
        }
    } else {
        sample = static_cast<short>(std::rand());
        if (g_ReplayModeAt0066C238 == ReplayMode::Recording)
            g_ReplayRecords.randomSamplesAndAiTimers.push_back(sample);
    }
    return (upper - lower) * sample / 32768 + lower;
}
