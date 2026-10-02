# Reconstruction references

The references below were inspected read-only on 2026-10-02. They supply
hypotheses and workflows; TH075's target establishes accepted bytes, ABI,
state meaning, and ownership. No reference source file was modified.

| Project | Material inspected | Useful transfer | TH075 constraint |
| --- | --- | --- | --- |
| [TH08](https://github.com/N0zoM1z0/th08) | Agent rules, README, `src/ZunMath.hpp`, `src/utils.cpp` | Natural-source matching, readable math types, strict ledger discipline | Shooter engine structures and VC7 source patterns need TH075-local evidence |
| [TH095](https://github.com/N0zoM1z0/th095) | Rules, README/progress, bootstrap, RNG/math sources, Bash + Ghidra bridge | VC7.1/Wine probes, complete COFF comparison, serialized Ghidra, public MCP setup | Different engine; no inherited layouts, assembly exceptions, or exact-profile source splits |
| [TH105](https://github.com/N0zoM1z0/th105) | Rules, architecture, bootstrap/compile scripts, `RenderStatePolicy.cpp`, `RenderModeManager.hpp`, `InputManagerLifetime.cpp` | Related fighting-game rendering/input concepts, ownership investigation, conservative origin accounting | VC8/LTCG and D3D9 differ from TH075's observed VC7.1/D3D8 surface |
| [TH10](https://github.com/N0zoM1z0/th10) | Rules, `scripts/repo-python`, decoder pins | Verify the decoder before selecting Python; consistent Web-side command routing | TH075 uses its own Python environment and target/tool manifests |

## TH105 comparison

TH075 and TH105 are the user's related-engine reference pair. Their PDB paths
both contain Nonotaro's work tree: TH075 records the Immaterial and Missing
Power project, while TH105 records the Scarlet Weather Rhapsody project.
This corroborates prioritizing TH105 for engine archaeology; it does not prove
a shared class layout or source body.

TH105's render-state policy covers source/destination blend factors and depth
gates/compare functions, which correspond to the API concepts observed in
TH075's accepted F002 functions. TH105 maintains cached state on a polymorphic
D3D9 owner and uses transitions based on both old and new blend modes. TH075's
current surface directly writes a shared D3D8 device with a simple mode switch.
The implementations and COM slot layouts are therefore recovered separately.

TH105's compiler bootstrap locks VC8 SP1 14.00.50727.762 and uses optimized
standalone probes while tracking LTCG uncertainty. Those flags are not copied
into TH075. The accepted TH075 batch uses VC7.1 13.10.3077 and `/Od /Ob0`;
the executable's multiple Rich-header builds still require per-unit review.

Next reference lanes are input-device lifetime/selection, texture wrappers,
render transforms, and fighting-game object ownership. Compare producer,
consumer, cleanup, and ABI evidence before promoting a name or declaration.
Keep unselected TH105 retained source as hypotheses, consistent with its rules.

## TH10 Python routing

TH10's wrapper rejects interpreters that cannot import its hash-pinned Capstone
decoder, avoiding a Web shell silently using Ubuntu's different decoder.
TH075 applies that idea through an ignored `.tools/python` virtual environment,
Python 3.12, and isolated-mode execution. Its Capstone 5.0.6 binding/native
identities are checked on every `scripts/repo-python` invocation. No TH10
Factory transport, compiler build, target, or publication policy is inherited.
