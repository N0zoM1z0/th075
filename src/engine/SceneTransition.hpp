#pragma once

// The low byte selects the next scene. The next two nibbles choose the
// outgoing animation and then the incoming animation.
namespace SceneId {
enum Value {
    Battle = 0,
    LoadBattle = 1,
    Title = 2,
    CharacterSelect = 3,
    Logo = 4,
    ReplayBrowser = 5,
    BattleResult = 6,
    ReplayNameEntry = 7,
    BattleEnding = 8,
    Options = 9,
    ScoreNameEntry = 10,
    Credits = 11,
    MusicRoom = 12,
    Opening = 13,
    RecordBrowser = 14,
};
}

namespace SceneTransition {
enum Mask {
    TargetMask = 0x00FF,
    OutMask = 0x0F00,
    InMask = 0xF000,
    EffectsMask = OutMask | InMask,
    KeepAfterOut = InMask | TargetMask,
    KeepBeforeIn = OutMask | TargetMask,
};

enum Animation {
    WhiteOut = 0x0100,
    BlackOut = 0x0200,
    TilesOut = 0x0300,
    SkipOutAnimation = 0x0F00,
    WhiteIn = 0x1000,
    BlackIn = 0x2000,
    TilesIn = 0x3000,
    SkipInAnimation = 0xF000,
};
}
