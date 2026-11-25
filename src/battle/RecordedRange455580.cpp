#include "battle/BattleSessionState.hpp"
#include "replay/ReplaySegmentedQueueF219.hpp"
#include "battle/Actor.hpp"
#include <cstdlib>

int Actor::RecordedRange(int lower, int upper) {
    short sample = 0;
    if (g_ReplayModeAt0066C238 == 2) {
        if (g_ReplayRecords.wordInputs.size() > 0) {
            sample = g_ReplayRecords.wordInputs.front();
            g_ReplayRecords.wordInputs.pop_front();
        }
    } else {
        sample = static_cast<short>(std::rand());
        if (g_ReplayModeAt0066C238 == 1)
            g_ReplayRecords.wordInputs.push_back(sample);
    }
    return (upper - lower) * sample / 32768 + lower;
}
