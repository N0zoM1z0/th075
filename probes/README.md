# Former probe directory

The reconstructed action fragments live under the owning character's
`src/characters/<character>/actions/` directory. Fragments used by several
characters live in [shared/actions](../src/characters/shared/actions/).
Cold-replay the owning functions when editing them.

The [origin fixtures](../tests/origin_probes/) contain the compiler controls
used by the origin verifiers. Frozen evidence can still name these fixtures
under their former `probes/` paths. Earlier one-off experiments can be
retrieved from Git.

Put new local experiments in `.analysis/` and their generated objects under
`build/`.
