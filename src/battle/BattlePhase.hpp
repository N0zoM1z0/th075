#pragma once

// Values carried by the signed BattleScene phase byte.
namespace BattlePhase {
enum Value {
    RoundIntro = 0,
    Fighting = 1,
    VersusRoundKnockout = 2,
    VersusMatchKnockout = 3,
    VersusRoundRecovery = 4,
    VictoryQuote = 5,
    LeaveBattle = 6,
    StoryDialogue = 7,
    LeaveAndSaveReplay = 8,
    StoryRoundRecovery = 9,
    StoryRoundKnockout = 10,
    StoryMatchKnockout = 11,
    StoryContinuePrompt = 12,
    StoryContinueReset = 13,
    LeaveStory = 14,
};
}
