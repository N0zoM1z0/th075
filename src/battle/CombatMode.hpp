#pragma once

// Values stored in the game mode byte. Replay headers have their own mode codes.
namespace CombatMode {
    enum {
        DuelCpu = 1,
        DuelHuman = 2,
        Story = 3,
        Arcade = 4,
        Practice = 5,
        Attract = 6,
    };
}
