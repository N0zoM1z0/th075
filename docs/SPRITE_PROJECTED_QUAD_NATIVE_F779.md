# F779 — Native projected textured sprite quad (0040CA20)

The complete original R011-authored function occupies
`0040CA20..0040CA7B` (92 CODE bytes and 34 original x86
instructions). The source in `src/SpriteProjectedQuadF779.cpp`
borrows only the physically observed 132-byte quad: four 16-byte
position vectors and 68 bytes of uninterpreted payload. Its entry
copy executes a 33-DWORD `REP MOVSD` using a local 4-byte aligned
quad at `EBP-0x84`. Explicit `__declspec(align(4))` is a real
layout choice: the compiler's inferred alignment otherwise produced
`sub esp,0x8C` instead of the native `0x88`. No synthetic
padding local or whole private sprite class is claimed.

The native `GetTexture` call resolves to original `0040C8C0`
and `Graphics::DrawProjectedTexturedQuad` to `00402D50`.
Both zero-addend REL32 offsets and source symbols are recorded in
`config/match-units.toml`; they are independently typed native
relocations, not masked differences. The complete single-unit
cold build and match was re-run for
`sprite-drawing-projected-quad-native-0040ca20`: **1/1 exact,
92 complete CODE bytes**, original target hash pinned in
`AGENTS.md`. The adjacent `0040C9A0` ordinary quad was later independently accepted
under [F780](SPRITE_ORDINARY_QUAD_NATIVE_F780.md).
