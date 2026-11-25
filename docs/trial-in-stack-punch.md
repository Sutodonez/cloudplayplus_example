# Trial: in-stack hole punch (exploration)

| Item | Value |
|------|-------|
| Branch | `cursor/trial-in-stack-punch-434f` |
| Base | out-of-stack trial tip (rebased onto latest `cursor/trial-out-of-stack-punch-434f`; `0011` regenerated vs hardened `0009`/`0010`) |
| Meaning of “trial” | Development lane for **栈内穿透** (PortAllocator SymmetricPunch). Not a claim that in-stack punch works yet. |
| Pin | **A locked** — m125 / 125.6422 · flutter-webrtc 0.11.7 · B/C deferred |
| Plan | `docs/handoff/in-stack-punch-plan.md` |
| Rebuild playbook | `docs/handoff/in-stack-m125-windows-rebuild.md` |
| Pin doc | `docs/in-stack-libwebrtc-pin-options.md`（中文优先） |
| Patches | `0011` MethodChannel scaffold + `patches/in-stack-punch/` (+ external cricket draft) |

Do **not** treat this PR as authorization to merge #1 into `main`.

**Naming:** this project = **CPPS**; upstream = **CPP** (gradual wording; historical paths may still say cppp).

## Progress (2026-11-25 Asia/Shanghai)

| Item | State |
|------|--------|
| Phase 0 scaffold | **Done** |
| Phase 1 pin choice | **Done** — Human selected **A**; B/C deferred |
| Phase 2 cricket draft | **Landed** — external `SymmetricPunchToRemotes` patch for m125 |
| Phase 2 MethodChannel / Dart (`0011`) | **Scaffold landed** — stubs → `rebuild_pending`; prefer-in-stack flag |
| Phase 2 Windows DLL / real C API | **In progress** on Aorus (`bc-37184299-…`); sync later via `aorus-artifact-sync.md` |
| SymmetricPunch “ready for alpha” | **No** — alpha pipeline **not started** |

## Alpha pipeline (locked-in; run **only after** feature ready)

Same as #14 out-of-stack, **after** in-stack SymmetricPunch is shippable for trial alpha:

1. Independent bugbot / security-style review of #15  
2. Auto-fix Medium+  
3. Package Windows portable alpha as `0.1.0-alpha.in-stack+<tip7>` (pair with `0.1.0-alpha.out-of-stack+…`); overwrite/update GitHub Release + store `media/` like #14  

**Gate (not reached):** rebuilt punch-capable `libwebrtc.dll` + real glue (`0012+`) + Windows desktop build that can exercise in-stack with out-of-stack **off**.

## Blocker / parallel

- Aorus sibling runs [`in-stack-m125-windows-rebuild.md`](./handoff/in-stack-m125-windows-rebuild.md).  
- Sync checklist: [`patches/in-stack-punch/aorus-artifact-sync.md`](../patches/in-stack-punch/aorus-artifact-sync.md).
