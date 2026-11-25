#pragma once

// The pattern loader reads two separate 32-bit flag words.

namespace FrameFlags {
enum Value {
    StandingHitReaction = 0x1,
    CrouchingHitReaction = 0x2,
    AirborneReaction = 0x4,
    CanGuard = 0x10,
    CanCancel = 0x20,
    CounterHitVulnerable = 0x40,
    AlwaysAllowsConditionalHit = 0x80,
    AllowsConditionalHitWithStock = 0x100,
    RejectsThrow = 0x800,
    RefreshesThrowInvulnerability = 0x1000,
    HitInvulnerable = 0x2000,
    Grazing = 0x4000,
    DisablesAirRecovery = 0x100000,
};
}

namespace AttackFlags {
enum Value {
    AlternateStandingHitReaction = 0x1,
    MatchesStandingGuard = 0x2,
    MatchesCrouchingGuard = 0x4,
    MatchesAirGuard = 0x8,
    Unguardable = 0x10,
    BypassesConditionalHit = 0x20,
    ChecksThrowInvulnerability = 0x80,
    FixedHitstun = 0x100,
    CanCounterHit = 0x400,
    BypassesGraze = 0x40000,
    CrushesWrongGroundGuard = 0x80000,
    ForcesGroundStagger = 0x100000,
    GuardableWithDepletedSpirit = 0x200000,
    BypassesHitInvulnerability = 0x400000,
};
}
