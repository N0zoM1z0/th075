// Eight independent native input policies; private owners are pointer-only.
// Original names, types and complete layouts remain provisional.
class CharacterInput4724B0 { public: void PollCommands(); signed char MatchInputPattern(const char*, signed char, signed char); };
class CharacterInput498BE0 { public: void PollCommands(); signed char MatchInputPattern(const char*, signed char, signed char); };
class CharacterInput4C6700 { public: void PollCommands(); signed char MatchInputPattern(const char*, signed char, signed char); };
class CharacterInput4E7A00 { public: void PollCommands(); signed char MatchInputPattern(const char*, signed char, signed char); };
class CharacterInput556FA0 { public: void PollCommands(); signed char MatchInputPattern(const char*, signed char, signed char); };
class CharacterInput579220 { public: void PollCommands(); signed char MatchInputPattern(const char*, signed char, signed char); };
class CharacterInput59CDA0 { public: void PollCommands(); signed char MatchInputPattern(const char*, signed char, signed char); };
class CharacterInput5C5980 { public: void PollCommands(); signed char MatchInputPattern(const char*, signed char, signed char); };

#define COMMAND (*reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(this) + 0x511))

void CharacterInput4724B0::PollCommands() {
    COMMAND = 0;
    if (MatchInputPattern("421B", 4, 15))
        COMMAND = 41;
    else if (MatchInputPattern("421A", 4, 15))
        COMMAND = 40;
    else if (MatchInputPattern("623C", 4, 15))
        COMMAND = 32;
    else if (MatchInputPattern("623B", 4, 15))
        COMMAND = 31;
    else if (MatchInputPattern("623A", 4, 15))
        COMMAND = 30;
    else if (MatchInputPattern("214B", 4, 15))
        COMMAND = 21;
    else if (MatchInputPattern("214A", 4, 15))
        COMMAND = 20;
    else if (MatchInputPattern("236D", 4, 15))
        COMMAND = 13;
    else if (MatchInputPattern("236B", 4, 15))
        COMMAND = 11;
    else if (MatchInputPattern("236A", 4, 15))
        COMMAND = 10;
    else if (MatchInputPattern("2N2D", 4, 15))
        COMMAND = 103;
    else if (MatchInputPattern("2N2C", 4, 15))
        COMMAND = 102;
    else if (MatchInputPattern("2N2B", 4, 15))
        COMMAND = 101;
    else if (MatchInputPattern("2N2A", 4, 15))
        COMMAND = 100;
    else if (MatchInputPattern("NRNR", 4, 15))
        COMMAND = 1;
    else if (MatchInputPattern("NLNL", 4, 15))
        COMMAND = 2;
    else if (MatchInputPattern("N29", 3, 10))
        COMMAND = 5;
    else if (MatchInputPattern("N39", 3, 10))
        COMMAND = 5;
    else if (MatchInputPattern("N19", 3, 10))
        COMMAND = 5;
    else if (MatchInputPattern("N27", 3, 10))
        COMMAND = 4;
    else if (MatchInputPattern("N37", 3, 10))
        COMMAND = 4;
    else if (MatchInputPattern("N17", 3, 10))
        COMMAND = 4;
    else if (MatchInputPattern("N28", 3, 10))
        COMMAND = 3;
    else if (MatchInputPattern("N38", 3, 10))
        COMMAND = 3;
    else if (MatchInputPattern("N18", 3, 10))
        COMMAND = 3;
}

void CharacterInput498BE0::PollCommands() {
    COMMAND = 0;
    if (MatchInputPattern("236236D", 7, 30))
        COMMAND = 113;
    else if (MatchInputPattern("4136B", 5, 15))
        COMMAND = 51;
    else if (MatchInputPattern("4136A", 5, 15))
        COMMAND = 50;
    else if (MatchInputPattern("623B", 4, 15))
        COMMAND = 31;
    else if (MatchInputPattern("623A", 4, 15))
        COMMAND = 30;
    else if (MatchInputPattern("214D", 4, 15))
        COMMAND = 23;
    else if (MatchInputPattern("214C", 4, 15))
        COMMAND = 22;
    else if (MatchInputPattern("214B", 4, 15))
        COMMAND = 21;
    else if (MatchInputPattern("214A", 4, 15))
        COMMAND = 20;
    else if (MatchInputPattern("236D", 4, 15))
        COMMAND = 13;
    else if (MatchInputPattern("236C", 4, 15))
        COMMAND = 12;
    else if (MatchInputPattern("236B", 4, 15))
        COMMAND = 11;
    else if (MatchInputPattern("236A", 4, 15))
        COMMAND = 10;
    else if (MatchInputPattern("2N2D", 4, 15))
        COMMAND = 103;
    else if (MatchInputPattern("2N2C", 4, 15))
        COMMAND = 102;
    else if (MatchInputPattern("2N2B", 4, 15))
        COMMAND = 101;
    else if (MatchInputPattern("2N2A", 4, 15))
        COMMAND = 100;
    else if (MatchInputPattern("N29", 3, 10))
        COMMAND = 5;
    else if (MatchInputPattern("N39", 3, 10))
        COMMAND = 5;
    else if (MatchInputPattern("N19", 3, 10))
        COMMAND = 5;
    else if (MatchInputPattern("N27", 3, 10))
        COMMAND = 4;
    else if (MatchInputPattern("N37", 3, 10))
        COMMAND = 4;
    else if (MatchInputPattern("N17", 3, 10))
        COMMAND = 4;
    else if (MatchInputPattern("N28", 3, 10))
        COMMAND = 3;
    else if (MatchInputPattern("N38", 3, 10))
        COMMAND = 3;
    else if (MatchInputPattern("N18", 3, 10))
        COMMAND = 3;
    else if (MatchInputPattern("NRNR", 4, 15))
        COMMAND = 1;
    else if (MatchInputPattern("NLNL", 4, 15))
        COMMAND = 2;
}

void CharacterInput4C6700::PollCommands() {
    COMMAND = 0;
    if (MatchInputPattern("236236D", 7, 30))
        COMMAND = 113;
    else if (MatchInputPattern("421C", 4, 15))
        COMMAND = 42;
    else if (MatchInputPattern("421B", 4, 15))
        COMMAND = 41;
    else if (MatchInputPattern("421A", 4, 15))
        COMMAND = 40;
    else if (MatchInputPattern("623B", 4, 15))
        COMMAND = 31;
    else if (MatchInputPattern("623A", 4, 15))
        COMMAND = 30;
    else if (MatchInputPattern("214D", 4, 15))
        COMMAND = 23;
    else if (MatchInputPattern("214B", 4, 15))
        COMMAND = 21;
    else if (MatchInputPattern("214A", 4, 15))
        COMMAND = 20;
    else if (MatchInputPattern("236D", 4, 15))
        COMMAND = 13;
    else if (MatchInputPattern("236C", 4, 15))
        COMMAND = 12;
    else if (MatchInputPattern("236B", 4, 15))
        COMMAND = 11;
    else if (MatchInputPattern("236A", 4, 15))
        COMMAND = 10;
    else if (MatchInputPattern("2N2D", 4, 15))
        COMMAND = 103;
    else if (MatchInputPattern("2N2C", 4, 15))
        COMMAND = 102;
    else if (MatchInputPattern("2N2B", 4, 15))
        COMMAND = 101;
    else if (MatchInputPattern("2N2A", 4, 15))
        COMMAND = 100;
    else if (MatchInputPattern("N29", 3, 10))
        COMMAND = 5;
    else if (MatchInputPattern("N39", 3, 10))
        COMMAND = 5;
    else if (MatchInputPattern("N19", 3, 10))
        COMMAND = 5;
    else if (MatchInputPattern("N27", 3, 10))
        COMMAND = 4;
    else if (MatchInputPattern("N37", 3, 10))
        COMMAND = 4;
    else if (MatchInputPattern("N17", 3, 10))
        COMMAND = 4;
    else if (MatchInputPattern("N28", 3, 10))
        COMMAND = 3;
    else if (MatchInputPattern("N38", 3, 10))
        COMMAND = 3;
    else if (MatchInputPattern("N18", 3, 10))
        COMMAND = 3;
    else if (MatchInputPattern("NRNR", 4, 15))
        COMMAND = 1;
    else if (MatchInputPattern("NLNL", 4, 15))
        COMMAND = 2;
}

void CharacterInput4E7A00::PollCommands() {
    COMMAND = 0;
    if (MatchInputPattern("236236D", 7, 30))
        COMMAND = 113;
    else if (MatchInputPattern("623B", 4, 15))
        COMMAND = 31;
    else if (MatchInputPattern("623A", 4, 15))
        COMMAND = 30;
    else if (MatchInputPattern("214C", 4, 15))
        COMMAND = 22;
    else if (MatchInputPattern("214B", 4, 15))
        COMMAND = 21;
    else if (MatchInputPattern("214A", 4, 15))
        COMMAND = 20;
    else if (MatchInputPattern("236D", 4, 15))
        COMMAND = 13;
    else if (MatchInputPattern("236C", 4, 15))
        COMMAND = 12;
    else if (MatchInputPattern("236B", 4, 15))
        COMMAND = 11;
    else if (MatchInputPattern("236A", 4, 15))
        COMMAND = 10;
    else if (MatchInputPattern("2N2D", 4, 15))
        COMMAND = 103;
    else if (MatchInputPattern("2N2C", 4, 15))
        COMMAND = 102;
    else if (MatchInputPattern("2N2B", 4, 15))
        COMMAND = 101;
    else if (MatchInputPattern("2N2A", 4, 15))
        COMMAND = 100;
    else if (MatchInputPattern("N29", 3, 10))
        COMMAND = 5;
    else if (MatchInputPattern("N39", 3, 10))
        COMMAND = 5;
    else if (MatchInputPattern("N19", 3, 10))
        COMMAND = 5;
    else if (MatchInputPattern("N27", 3, 10))
        COMMAND = 4;
    else if (MatchInputPattern("N37", 3, 10))
        COMMAND = 4;
    else if (MatchInputPattern("N17", 3, 10))
        COMMAND = 4;
    else if (MatchInputPattern("N28", 3, 10))
        COMMAND = 3;
    else if (MatchInputPattern("N38", 3, 10))
        COMMAND = 3;
    else if (MatchInputPattern("N18", 3, 10))
        COMMAND = 3;
    else if (MatchInputPattern("NRNR", 4, 15))
        COMMAND = 1;
    else if (MatchInputPattern("NLNL", 4, 15))
        COMMAND = 2;
}

void CharacterInput556FA0::PollCommands() {
    COMMAND = 0;
    if (MatchInputPattern("236236D", 7, 30))
        COMMAND = 113;
    else if (MatchInputPattern("623B", 4, 15))
        COMMAND = 31;
    else if (MatchInputPattern("623A", 4, 15))
        COMMAND = 30;
    else if (MatchInputPattern("214C", 4, 15))
        COMMAND = 22;
    else if (MatchInputPattern("214B", 4, 15))
        COMMAND = 21;
    else if (MatchInputPattern("214A", 4, 15))
        COMMAND = 20;
    else if (MatchInputPattern("236D", 4, 15))
        COMMAND = 13;
    else if (MatchInputPattern("236C", 4, 15))
        COMMAND = 12;
    else if (MatchInputPattern("236B", 4, 15))
        COMMAND = 11;
    else if (MatchInputPattern("236A", 4, 15))
        COMMAND = 10;
    else if (MatchInputPattern("2N2D", 4, 15))
        COMMAND = 103;
    else if (MatchInputPattern("2N2C", 4, 15))
        COMMAND = 102;
    else if (MatchInputPattern("2N2B", 4, 15))
        COMMAND = 101;
    else if (MatchInputPattern("2N2A", 4, 15))
        COMMAND = 100;
    else if (MatchInputPattern("N29", 3, 10))
        COMMAND = 5;
    else if (MatchInputPattern("N39", 3, 10))
        COMMAND = 5;
    else if (MatchInputPattern("N19", 3, 10))
        COMMAND = 5;
    else if (MatchInputPattern("N27", 3, 10))
        COMMAND = 4;
    else if (MatchInputPattern("N37", 3, 10))
        COMMAND = 4;
    else if (MatchInputPattern("N17", 3, 10))
        COMMAND = 4;
    else if (MatchInputPattern("N28", 3, 10))
        COMMAND = 3;
    else if (MatchInputPattern("N38", 3, 10))
        COMMAND = 3;
    else if (MatchInputPattern("N18", 3, 10))
        COMMAND = 3;
    else if (MatchInputPattern("NRNR", 4, 15))
        COMMAND = 1;
    else if (MatchInputPattern("NLNL", 4, 15))
        COMMAND = 2;
}

void CharacterInput579220::PollCommands() {
    COMMAND = 0;
    if (MatchInputPattern("236236D", 7, 30))
        COMMAND = 113;
    else if (MatchInputPattern("623C", 4, 15))
        COMMAND = 32;
    else if (MatchInputPattern("623B", 4, 15))
        COMMAND = 31;
    else if (MatchInputPattern("623A", 4, 15))
        COMMAND = 30;
    else if (MatchInputPattern("214B", 4, 15))
        COMMAND = 21;
    else if (MatchInputPattern("214A", 4, 15))
        COMMAND = 20;
    else if (MatchInputPattern("236D", 4, 15))
        COMMAND = 13;
    else if (MatchInputPattern("236C", 4, 15))
        COMMAND = 12;
    else if (MatchInputPattern("236B", 4, 15))
        COMMAND = 11;
    else if (MatchInputPattern("236A", 4, 15))
        COMMAND = 10;
    else if (MatchInputPattern("412B", 4, 15))
        COMMAND = 71;
    else if (MatchInputPattern("412A", 4, 15))
        COMMAND = 70;
    else if (MatchInputPattern("2N2D", 4, 15))
        COMMAND = 103;
    else if (MatchInputPattern("2N2C", 4, 15))
        COMMAND = 102;
    else if (MatchInputPattern("2N2B", 4, 15))
        COMMAND = 101;
    else if (MatchInputPattern("2N2A", 4, 15))
        COMMAND = 100;
    else if (MatchInputPattern("N29", 3, 10))
        COMMAND = 5;
    else if (MatchInputPattern("N39", 3, 10))
        COMMAND = 5;
    else if (MatchInputPattern("N19", 3, 10))
        COMMAND = 5;
    else if (MatchInputPattern("N27", 3, 10))
        COMMAND = 4;
    else if (MatchInputPattern("N37", 3, 10))
        COMMAND = 4;
    else if (MatchInputPattern("N17", 3, 10))
        COMMAND = 4;
    else if (MatchInputPattern("N28", 3, 10))
        COMMAND = 3;
    else if (MatchInputPattern("N38", 3, 10))
        COMMAND = 3;
    else if (MatchInputPattern("N18", 3, 10))
        COMMAND = 3;
    else if (MatchInputPattern("NRNR", 4, 15))
        COMMAND = 1;
    else if (MatchInputPattern("NLNL", 4, 15))
        COMMAND = 2;
}

void CharacterInput59CDA0::PollCommands() {
    COMMAND = 0;
    if (MatchInputPattern("421C", 4, 15))
        COMMAND = 42;
    else if (MatchInputPattern("421B", 4, 15))
        COMMAND = 41;
    else if (MatchInputPattern("421A", 4, 15))
        COMMAND = 40;
    else if (MatchInputPattern("412C", 4, 15))
        COMMAND = 72;
    else if (MatchInputPattern("412B", 4, 15))
        COMMAND = 71;
    else if (MatchInputPattern("412A", 4, 15))
        COMMAND = 70;
    else if (MatchInputPattern("623B", 4, 15))
        COMMAND = 31;
    else if (MatchInputPattern("623A", 4, 15))
        COMMAND = 30;
    else if (MatchInputPattern("214D", 4, 15))
        COMMAND = 23;
    else if (MatchInputPattern("214B", 4, 15))
        COMMAND = 21;
    else if (MatchInputPattern("214A", 4, 15))
        COMMAND = 20;
    else if (MatchInputPattern("236D", 4, 15))
        COMMAND = 13;
    else if (MatchInputPattern("236C", 4, 15))
        COMMAND = 12;
    else if (MatchInputPattern("236B", 4, 15))
        COMMAND = 11;
    else if (MatchInputPattern("236A", 4, 15))
        COMMAND = 10;
    else if (MatchInputPattern("2N2D", 4, 15))
        COMMAND = 103;
    else if (MatchInputPattern("2N2C", 4, 15))
        COMMAND = 102;
    else if (MatchInputPattern("2N2B", 4, 15))
        COMMAND = 101;
    else if (MatchInputPattern("2N2A", 4, 15))
        COMMAND = 100;
    else if (MatchInputPattern("N29", 3, 10))
        COMMAND = 5;
    else if (MatchInputPattern("N39", 3, 10))
        COMMAND = 5;
    else if (MatchInputPattern("N19", 3, 10))
        COMMAND = 5;
    else if (MatchInputPattern("N27", 3, 10))
        COMMAND = 4;
    else if (MatchInputPattern("N37", 3, 10))
        COMMAND = 4;
    else if (MatchInputPattern("N17", 3, 10))
        COMMAND = 4;
    else if (MatchInputPattern("N28", 3, 10))
        COMMAND = 3;
    else if (MatchInputPattern("N38", 3, 10))
        COMMAND = 3;
    else if (MatchInputPattern("N18", 3, 10))
        COMMAND = 3;
    else if (MatchInputPattern("NRNR", 4, 15))
        COMMAND = 1;
    else if (MatchInputPattern("NLNL", 4, 15))
        COMMAND = 2;
}

void CharacterInput5C5980::PollCommands() {
    COMMAND = 0;
    if (MatchInputPattern("236D", 4, 15))
        COMMAND = 13;
    else if (MatchInputPattern("421B", 4, 15))
        COMMAND = 41;
    else if (MatchInputPattern("421A", 4, 15))
        COMMAND = 40;
    else if (MatchInputPattern("214D", 4, 15))
        COMMAND = 23;
    else if (MatchInputPattern("214B", 4, 15))
        COMMAND = 21;
    else if (MatchInputPattern("214A", 4, 15))
        COMMAND = 20;
    else if (MatchInputPattern("236B", 4, 15))
        COMMAND = 11;
    else if (MatchInputPattern("236A", 4, 15))
        COMMAND = 10;
    else if (MatchInputPattern("2N2D", 4, 15))
        COMMAND = 103;
    else if (MatchInputPattern("2N2C", 4, 15))
        COMMAND = 102;
    else if (MatchInputPattern("2N2B", 4, 15))
        COMMAND = 101;
    else if (MatchInputPattern("2N2A", 4, 15))
        COMMAND = 100;
    else if (MatchInputPattern("N29", 3, 10))
        COMMAND = 5;
    else if (MatchInputPattern("N39", 3, 10))
        COMMAND = 5;
    else if (MatchInputPattern("N19", 3, 10))
        COMMAND = 5;
    else if (MatchInputPattern("N27", 3, 10))
        COMMAND = 4;
    else if (MatchInputPattern("N37", 3, 10))
        COMMAND = 4;
    else if (MatchInputPattern("N17", 3, 10))
        COMMAND = 4;
    else if (MatchInputPattern("N28", 3, 10))
        COMMAND = 3;
    else if (MatchInputPattern("N38", 3, 10))
        COMMAND = 3;
    else if (MatchInputPattern("N18", 3, 10))
        COMMAND = 3;
    else if (MatchInputPattern("NRNR", 4, 15))
        COMMAND = 1;
    else if (MatchInputPattern("NLNL", 4, 15))
        COMMAND = 2;
}

#undef COMMAND
