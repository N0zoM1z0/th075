#include "engine/GameProgress.hpp"

void GameProgress::UpdateHighestStoryStage(signed char stage)
{
    if (stage > characters[selectedFighter].difficulties[selectedDifficulty].highestStoryStage)
        characters[selectedFighter].difficulties[selectedDifficulty].highestStoryStage = stage;
}

// This method indexes the byte stride of both record dimensions before
// dereferencing the selected record. VC7.1 preserves that evaluation order.
#define SELECTED_RECORD reinterpret_cast<ProgressDifficulty*>( \
    reinterpret_cast<unsigned char*>(characters) + \
    (sizeof(ProgressDifficulty) * selectedDifficulty + sizeof(ProgressCharacter) * selectedFighter))

void GameProgress::RecordStoryAttempt()
{
    SELECTED_RECORD->storyAttempts = SELECTED_RECORD->storyAttempts + 1;
}
#undef SELECTED_RECORD
