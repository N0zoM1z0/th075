#pragma once

// Call-only views of existing scenes; original complete owner layout is unknown.
// Never instantiate or embed this partial interface.
class NameEntryInputF182 {
public:
    void PollPlayerInput();
    void PollSharedInput();
};
