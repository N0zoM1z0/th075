# F568: independent physical COFF addend audit for eight integrated fighters

The previously untracked, separately generated second whole-fighter
source verifier was not skipped or discarded. It was executed against
all eight pinned original Japanese TH075 v1.11 fighters, freshly
compiling one source translation unit per original. All 88 complete
native first-switch case ranges, 4,989 actual original GPR/x87/control
instructions and whole physical original jump DATA passed.

Unlike the earlier F567 canonical verifier, this second native
COFF inspection explicitly checked physical relocation **addends**,
not just native type, source symbol and instruction ordinal.
All **571 actual original case call/global COFF fields** and all
**88 direct first-table handler DWORD source fields** have genuine
zero addends. The full 1,163 original-style DWORD switch fields,
3,335 sparse original bytes and 7,987 after-RET DATA layout bytes
remain separately verified by the canonical original-only controls.

The original uncovered assumption matters: the right native source
symbol and relocation type can still point to an incorrect destination
if a hidden nonzero COFF addend is present. The canonical tracked
scripts/verify-fighter-all-multiswitch-opening-cases.py now rejects
unexpected nonzero addends in both complete inner action cases and
the first original physical 11-slot direct jump table.

The more detailed second verifier, an independently written F567
narrative/report and the full eight-fighter compilation logs were preserved
under ignored .analysis/f567-integrated-fighters/
instead of maintaining two duplicate tracked entrypoints. F568
also recompiled and rechecked the canonical source for Reimu and
wide-frame fighter 00564BE0 after introducing this stricter check.
No dirty work was skipped or reset.

**No entire original giant function is exact**: these 88 native
action subranges still belong to eight unmatched full fighters
totaling 450,809 original CODE bytes. No new accepted whole or
partial source CODE/DATA, no all-unit cold replay and no external
Factory/Oracle receipt.
