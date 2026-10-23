#pragma once

// Declaration-only receiver; never construct or embed this partial owner.
class CharacterInput5E6F70 {
public:
    void PollCommands();
    signed char MatchInputPattern(const char*, signed char, signed char);
};
