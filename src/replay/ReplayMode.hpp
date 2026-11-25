#pragma once

// Runtime input and dialogue states. Replay files encode the game mode separately.
namespace ReplayMode {
    enum {
        Recording = 1,
        Playback = 2,
        LiveDialogue = 3,
        ReplayDialogue = 4,
    };
}
