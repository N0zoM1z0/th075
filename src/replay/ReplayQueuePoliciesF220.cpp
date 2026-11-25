#include "replay/ReplayRecords.hpp"

template<>
void ReplayRecords::ClearFourQueues()
{
    frameInputBits.clear();
    randomSamplesAndAiTimers.clear();
    aiCommandsAndGuardChoices.clear();
    timedBattleCommands.clear();
}

template<>
unsigned char ReplayRecords::IsPrimaryInputQueueEmpty()
{
    if (frameInputBits.size() > 0)
        return 0;
    return 1;
}
