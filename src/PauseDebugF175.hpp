#pragma once

// Call-only view of existing storage; complete owner layout and original
// nominal identities remain unknown. Never instantiate or embed this owner.
class PauseDebugF175 {
public:
    void HandlePauseMenu();
    void ProcessDebugKeys();
};
