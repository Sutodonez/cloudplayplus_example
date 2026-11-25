# In-stack SymmetricPunch plan (栈内穿透试用版)

**Branch:** `cursor/trial-in-stack-punch-434f`  
**Status:** Phase 2 under **pin A** (Human-locked 2026-11-25). B/C deferred.  
**Pin doc:** [`../in-stack-libwebrtc-pin-options.md`](../in-stack-libwebrtc-pin-options.md)  
**Rebuild:** [`in-stack-m125-windows-rebuild.md`](./in-stack-m125-windows-rebuild.md)

## Goal

Move hard-NAT punch from **out-of-stack** into **in-stack** (allocator-owned ICE UDP ports), GV-style SymmetricPunch.

## Inventory (FACT)

| Item | State |
|------|--------|
| Out-of-stack | `0009`/`0010` on trial tip |
| flutter-webrtc | **0.11.7** / m125.6422 line |
| Desktop libwebrtc | Still stock prebuilt DLL until Windows rebuild drops punch binary |
| Cricket draft | `patches/in-stack-punch/external/webrtc-m125-symmetric-punch.patch` → `BasicPortAllocatorSession::SymmetricPunchToRemotes` |
| Frozen webrtc SHA | `db3ba7af86dd6d48174ed35387d11c0794f1a21b` (`m125_release`) |
| Frozen libwebrtc | tag `125.6422.08` |

## Phases

### Phase 0 — done

Scaffold, FILE_LIST, CI notes, `0011` skeleton, pin-options doc.

### Phase 1 — done (Human)

| Step | Result |
|------|--------|
| 1.1 Pin | **A** |
| 1.2 B/C | **Deferred** until formal in-stack vs out-of-stack product choice |
| 1.3 SHA freeze | Recorded in rebuild playbook |

### Phase 2 — in progress (A)

| # | Step | Status |
|---|------|--------|
| 2.1 | Cricket SymmetricPunch patch (external) | **Draft landed** (`p2p/client/basic_port_allocator.*`) |
| 2.2 | libwebrtc C API exposure | **Notes** + ready-gate header; real wire needs DLL |
| 2.3 | Windows `gn`/`ninja` → drop DLL | **In progress** on Aorus sibling (`bc-37184299-…`) |
| 2.4–2.5 | MethodChannel + Dart prefer-in-stack | **Scaffold landed** (`0011` stubs → `rebuild_pending`) |
| 2.6 | Root `0011-*.patch` | **Emitted** as scaffold only; real punch → `0012+` after DLL |
| 2.7 | Verify + NAT matrix | **Blocked** on 2.3 + real glue |

### Phase 3 — merge gate

Do **not** merge #1/#15 → `main` until rebuildable in-stack path is Windows-validated.

### Phase 4 — alpha pipeline (locked-in; **do not start early**)

Only when SymmetricPunch trial feature is ready enough to ship alpha (gate in `docs/trial-in-stack-punch.md`):

1. Independent bugbot/security-style review of #15  
2. Auto-fix Medium+  
3. Portable Windows alpha `0.1.0-alpha.in-stack+<tip7>` paired with out-of-stack `0.1.0-alpha.out-of-stack+…`; Release + store media like #14  

## Replayability

- Out-of-stack: `0009`–`0010` + `patches/nat-punch/`  
- In-stack: external webrtc/libwebrtc patches + future root `0011+`; never fold into out-of-stack commits  
