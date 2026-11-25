# In-stack punch (PortAllocator)

**Root applyable scaffold:** `patches/0011-in-stack-methodchannel-scaffold.patch`  
(stubs + prefer-in-stack Dart — **not** a claim that SymmetricPunch works).

Real PortAllocator punch still needs Aorus / Windows rebuilt `libwebrtc.dll` → future `0012+`.

## Contents

| File | Role |
|------|------|
| [`FILE_LIST.md`](./FILE_LIST.md) | Owned paths for `0011` + provisional DLL paths |
| [`0011-in-stack-portallocator-symmetric-punch.skeleton.md`](./0011-in-stack-portallocator-symmetric-punch.skeleton.md) | Map for **real** punch after binary drop |
| [`aorus-artifact-sync.md`](./aorus-artifact-sync.md) | Sync checklist when Windows rebuild lands |
| [`ci-notes.md`](./ci-notes.md) | Why CI cannot rebuild WebRTC today |
| [`external/`](./external/) | Out-of-tree m125 cricket draft + libwebrtc API notes |
| This README | Apply rules |

## Related docs

- Plan: [`../../docs/handoff/in-stack-punch-plan.md`](../../docs/handoff/in-stack-punch-plan.md)
- Pin: [`../../docs/in-stack-libwebrtc-pin-options.md`](../../docs/in-stack-libwebrtc-pin-options.md)
- Out-of-stack: `patches/0009`–`0010` + [`../nat-punch/`](../nat-punch/)

## Apply

Only `patches/*.patch` are applied by `scripts/apply-patches.sh`.  
Do not renumber `0009`/`0010`. Keep in-stack isolated from out-of-stack commits.
