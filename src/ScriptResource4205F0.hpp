#pragma once

// Methods on the script resource embedded in Fighter at +0x714.
class ScriptResource4205F0 {
public:
    void LoadArchive(const char*, const char*);
    void LoadFile(const char*, signed char, const char*);
    void Parse(char*, unsigned int);
};
