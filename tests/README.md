# Tests

These tests cover shared tooling on its success and failure paths: COFF and
relocation comparison (`test_function_workflow`, `test_coff_data`), the exact
ledgers (`test_exact_checkpoint`), progress accounting (`test_status_goal`),
the frontier ratchet (`test_check_frontier`), the repository Python, PDB and
symbol-archive audits, and the libraries the origin verifiers share. They run
in a few seconds without compiler builds:

```bash
scripts/repo-python -m unittest discover -s tests
```

Exact credit comes only from cold replay (`scripts/replay-exact-units.py`).
Do not add a test per function, source-text or spelling assertions, or tests
that pin a nonexact function's current bytes; `config/frontiers.toml` and
`scripts/check-frontier.py` ratchet the giant research parents instead.

Origin decisions are checked by running their verifiers against the real
evidence with `scripts/check-origins.py`. The per-verifier mutation tests
were removed. `origin_probes/` holds probe sources that some verifiers
compile.
