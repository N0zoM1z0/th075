# Batch origin review

Run the read-only shortlist builder from the repository root:

```bash
scripts/repo-python scripts/scan-origin-candidates.py
```

The same command can be sent to the existing public MCP `run_command` tool.
It uses the pinned repository environment and target. It reads all candidate
extents and current origins, then writes the private report to
`.analysis/origin-scan/latest.json`. It changes no accepted ledger, database,
reconstruction source or exact result. Override `--output` only with a JSON
path below `.analysis/`. Reports include target and ledger hashes; rerun after
origin or boundary changes rather than trusting a stale shortlist.

The report groups pending candidates by complete body and reviewed context.
Only direct-call displacement fields are normalized, and their actual target
addresses stay in the signature. Vtable/data fields, other instructions and
RET cleanup remain unchanged. Thus a different callee, vtable or unused stack
argument prevents a group match. Full decoding, internal branches, known
switch tables, final RET and overlapping candidates are checked before a
body can supply a group or a reviewed caller witness. A failed check sends
the candidate to the extent-reconciliation queue; it does not prove a bad
function or resolve legitimate vendor tails/tables automatically.

Use the queues to review groups instead of setting up an investigation for
each address. Start with complete reviewed peers and reviewed game callers/
callees. Check explicit policy fields and owner context for every member.
Vendor groups additionally need complete cold source/archive definitions and
typed bindings; tiny identical helpers still need independent family context.
Constructor/destructor shapes need explicit-versus-implicit lifetime evidence.
Ghidra address queries accept at most sixteen addresses, so split larger
query lists while preserving each attestation/completion marker.

The initial R102 scan covered all 1,408 pending candidates and found fifty
whole-body groups. Manual review accepted seventeen game policies from those
queues, with complete call/parent/field context and four whole reviewed peers:

```bash
scripts/repo-python scripts/verify-short-game-origins.py --cohort R102
```

The shared verifier keeps R100 as its default cohort. Its complete switch
context still cold-replays all 495 bytes, including the blend-mode table.
R102 freezes its own seventeen extents and thirty-three independent anchors;
it does not inherit credit from a scan result. The remaining 1,391 candidates
are still pending. The updated scan has forty-seven whole-body groups and
182 extent questions; these numbers are diagnostic queues, not new origins.
Both the scanner and R102 cohort verifier have passed through the existing
no-auth public HTTPS MCP, using `scripts/repo-python` in each Bash request.

R103 reused the same shortlist and verifier for thirty-three further state/
record policies, each with an independently reviewed whole parent. Replay:

```bash
scripts/repo-python scripts/verify-short-game-origins.py --cohort R103
```

This cohort and its four readonly scalar bindings also passed through the
public MCP. There are now 1,358 pending candidates; refresh the private scan
after every accepted batch.

R104 used the same complete-body queues for sixteen small game helpers / 806
bytes. The cohort binds eighteen independently reviewed whole anchors, sixteen
parent edges and 88 selected instructions. It includes animation/state resets,
sprite record operations, hexadecimal digit parsing, HUD/notice policies and
small effect-field updates. R105 then accepted three larger callers / 365
bytes whose ownership became explicit after R104: rectangle-corner assembly,
a battle hit-sequence transition and notice initialization. Replay them with:

```bash
scripts/repo-python scripts/verify-short-game-origins.py --cohort R104
scripts/repo-python scripts/verify-short-game-origins.py --cohort R105
```

Both cohort replays passed locally and through the no-auth public HTTPS MCP.
The refreshed scan covers all 1,339 remaining candidates and retains 47 whole-
body groups and 182 extent questions. Its strongest combined reviewed-game-
callee/parent lane now contains six candidates. Short lifetime wrappers in
that lane remain pending until explicit versus implicit emission is resolved.
