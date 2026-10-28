# Validation scope

Exact function acceptance uses the pinned target, tracking validation and cold
replay of new or affected units. Keep per-function extents, relocations, compiler
profiles and source hashes in the canonical manifests rather than duplicating
them in Python tests. Do not add source-text assertions or allocation-failure,
null-pointer, fault-injection or general robustness tests for reconstructed
functions. Preserve failure branches that actually exist in the target.

`scripts/repo-python scripts/ci.py` runs the shared exact-comparison, checkpoint
and byte-accounting tests without compiler builds. Run it for changes to that
infrastructure or its tests; it is not an extra gate for routine function
acceptance or handoff.

Historical origin tests and `origin_probes/` remain evidence for ownership
decisions. Run a relevant origin test only when changing its evidence or
verifier. Do not run the full historical suite during routine reconstruction.

The former F229–F251 per-function test files duplicated target hashes, physical
relocation lists, accepted source hashes and source text. They were removed;
their canonical manifests, accepted sources and reconstruction evidence remain.
