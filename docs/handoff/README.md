# CloudPlayPlus enhancement — portable handoff (cross-Project)

**Updated:** 2026-11-25 Asia/Shanghai  
**Important:** Cursor Project Context / Agent Store links **do not open in another Project**. Use this file + GitHub URLs only.

**Repo:** https://github.com/Sutodonez/cloudplayplus_plus  
**Branch:** `main` (after handoff merge; feature docs may land via later PRs)

### GitHub URLs (open from any Project)

| File | blob | raw |
|------|------|-----|
| README (this file) | https://github.com/Sutodonez/cloudplayplus_plus/blob/main/docs/handoff/README.md | https://raw.githubusercontent.com/Sutodonez/cloudplayplus_plus/main/docs/handoff/README.md |
| cpp-migration-plan.md | https://github.com/Sutodonez/cloudplayplus_plus/blob/main/docs/handoff/cpp-migration-plan.md | https://raw.githubusercontent.com/Sutodonez/cloudplayplus_plus/main/docs/handoff/cpp-migration-plan.md |
| cpp-punch-replay.md | https://github.com/Sutodonez/cloudplayplus_plus/blob/main/docs/handoff/cpp-punch-replay.md | https://raw.githubusercontent.com/Sutodonez/cloudplayplus_plus/main/docs/handoff/cpp-punch-replay.md |
| cloudplayplus-vs-gameviewer.md | https://github.com/Sutodonez/cloudplayplus_plus/blob/main/docs/handoff/cloudplayplus-vs-gameviewer.md | https://raw.githubusercontent.com/Sutodonez/cloudplayplus_plus/main/docs/handoff/cloudplayplus-vs-gameviewer.md |
| gameviewer-public-features.md | https://github.com/Sutodonez/cloudplayplus_plus/blob/main/docs/handoff/gameviewer-public-features.md | https://raw.githubusercontent.com/Sutodonez/cloudplayplus_plus/main/docs/handoff/gameviewer-public-features.md |
| gameviewer-tech-notes-plain.md | https://github.com/Sutodonez/cloudplayplus_plus/blob/main/docs/handoff/gameviewer-tech-notes-plain.md | https://raw.githubusercontent.com/Sutodonez/cloudplayplus_plus/main/docs/handoff/gameviewer-tech-notes-plain.md |
| cpp-handoff.md (legacy) | https://github.com/Sutodonez/cloudplayplus_plus/blob/main/docs/handoff/cpp-handoff.md | https://raw.githubusercontent.com/Sutodonez/cloudplayplus_plus/main/docs/handoff/cpp-handoff.md |
| internal-cpp-punch-pr-report.md | https://github.com/Sutodonez/cloudplayplus_plus/blob/main/docs/handoff/internal-cpp-punch-pr-report.md | https://raw.githubusercontent.com/Sutodonez/cloudplayplus_plus/main/docs/handoff/internal-cpp-punch-pr-report.md |
| internal-file-transfer-implementation.md | https://github.com/Sutodonez/cloudplayplus_plus/blob/main/docs/handoff/internal-file-transfer-implementation.md | https://raw.githubusercontent.com/Sutodonez/cloudplayplus_plus/main/docs/handoff/internal-file-transfer-implementation.md |
| internal-vhid-relative-mouse-pr.md | https://github.com/Sutodonez/cloudplayplus_plus/blob/main/docs/handoff/internal-vhid-relative-mouse-pr.md | https://raw.githubusercontent.com/Sutodonez/cloudplayplus_plus/main/docs/handoff/internal-vhid-relative-mouse-pr.md |
| session-file-transfer.md | https://github.com/Sutodonez/cloudplayplus_plus/blob/main/docs/handoff/session-file-transfer.md | https://raw.githubusercontent.com/Sutodonez/cloudplayplus_plus/main/docs/handoff/session-file-transfer.md |
| privacy-blank-display.md | https://github.com/Sutodonez/cloudplayplus_plus/blob/main/docs/handoff/privacy-blank-display.md | https://raw.githubusercontent.com/Sutodonez/cloudplayplus_plus/main/docs/handoff/privacy-blank-display.md |
| nat-punch.md | https://github.com/Sutodonez/cloudplayplus_plus/blob/main/docs/handoff/nat-punch.md | https://raw.githubusercontent.com/Sutodonez/cloudplayplus_plus/main/docs/handoff/nat-punch.md |

**Sibling docs in this folder:** [cpp-migration-plan.md](./cpp-migration-plan.md) · [cpp-punch-replay.md](./cpp-punch-replay.md) · [nat-punch.md](./nat-punch.md) · [cloudplayplus-vs-gameviewer.md](./cloudplayplus-vs-gameviewer.md) · [gameviewer-public-features.md](./gameviewer-public-features.md) · [gameviewer-tech-notes-plain.md](./gameviewer-tech-notes-plain.md) · [cpp-handoff.md](./cpp-handoff.md) · [internal-cpp-punch-pr-report.md](./internal-cpp-punch-pr-report.md) · [internal-file-transfer-implementation.md](./internal-file-transfer-implementation.md) · [internal-vhid-relative-mouse-pr.md](./internal-vhid-relative-mouse-pr.md) · [privacy-blank-display.md](./privacy-blank-display.md) · [session-file-transfer.md](./session-file-transfer.md)

---

## A. Open PRs (work already done)

| Feature | PR | Branch |
|---------|-----|--------|
| Enhanced hole punch + soft ICE | https://github.com/Sutodonez/cloudplayplus_plus/pull/1 | `cursor/feat-enhanced-hole-punch-cc1d` |
| File / folder transfer | https://github.com/Sutodonez/cloudplayplus_plus/pull/2 | `cursor/feat-file-transfer-c757` |
| VHID relative mouse | https://github.com/Sutodonez/cloudplayplus_plus/pull/3 | `cursor/vhid-relative-mouse-5758` |
| Server terminal | https://github.com/Sutodonez/cloudplayplus_plus/pull/8 | `cursor/server-terminal-link-c1a9` |
| Privacy / blank display | https://github.com/Sutodonez/cloudplayplus_plus/pull/9 | `cursor/privacy-blank-display-11c0` |

Workers/subagents **cannot** transfer across Projects. New Project: new workers; reuse these PRs/branches.

---

## B. Binding decisions

1. Hole punch / hard NAT is **priority 1**.
2. Direct CPP / flutter-webrtc edits allowed if no adequate soft alternative.
3. Every such change must be **replayable** on future CPP (patch series, bounded fork, cherry-pick, rebase playbook).
4. Prefer plugins when capability is equal; punch may live in vendored transport.
5. GameViewer remote product publicly = **NetEase UU远程** (`https://uuyc.163.com/`), not Tencent.
6. Migrate ideas/ladder design only — **no** NetEase binaries or decompiled bodies.

---

## C. GUI placement (as implemented in PRs)

- **Punch:** global `settings_screen` section「NAT 穿透 / 打洞」— `enablePunch`, `forceRelay` (with existing TURN).
- **Files:** in-session floating menu folder icon → `FileTransferSheet` (send files/folder + progress). Host default **manual confirm** (`fileXferAutoAccept=false`); optional auto-accept to `Downloads/CloudPlayPlusTransfers`. Authenticated controller = full trust (terminal independent). Web unsupported.
- **VHID:** host「键鼠设置」—「虚拟 HID 相对鼠标」`useVhidMouse`. Falls back to SendInput if WinUHid missing. No controller HUD.
- **Privacy:** host settings + connect picker; opcode `LP_PRIVACY_MODE=68`. See [privacy-blank-display.md](./privacy-blank-display.md).
- **Terminal:** in-session server terminal; opcode `LP_TERMINAL=69` (privacy keeps 68).

---

## D. Migration ranking (excerpt)

1. Enhanced Symmetric Hole Punch / hard-NAT ladder (RE + public pain) — vendored ICE, replayable patches  
2. File transfer (public gap) — plugin / data-channel  
3. VHID relative mouse (RE) — `hardware_simulator`  
4. Soft ICE/TURN ladder — complement to #1, not substitute  
5. Privacy / blank display · 6. Server terminal · 7. WOL · 8. Port mapping · 9. ISP/QoS relay metadata  

---

## E. Punch replay playbook (full)

**Owned paths in repo:** `patches/nat-punch/FILE_LIST.md`

| Layer | Behavior |
|-------|----------|
| Punch | UDP probes to `119.29.29.29` / `223.5.5.5`; multi-socket bursts to remote `srflx`/`host` |
| Soft ICE | Concurrent STUN+TURN when `enablePunch` + turn; `iceTransportPolicy: all` |
| forceRelay | `iceTransportPolicy: relay` + TURN |
| Flags | `StreamingSettings.enablePunch` / `forceRelay` |
| Native | Desktop MethodChannel `natPunchProbeFirewall` / `natPunchSymmetric` (Dart fallback) |

Replay steps:

1. Fetch upstream CPP / update flutter-webrtc pin.  
2. Conflict surface ⊆ `patches/nat-punch/FILE_LIST.md`.  
3. Cherry-pick punch commits in order, or `git am patches/nat-punch/upstream/*.patch`.  
4. Resolve only listed files; do not fold unrelated encode/UI into punch commits.  
5. `flutter test test/ice_policy_test.dart`  
6. Manual NAT matrix when hardware available.  
7. Regenerate format-patch into `patches/nat-punch/upstream/`.

ABI freeze: `IcePunchOptions{enabled, forceRelay, probeHosts, …}`; MethodChannel names above.

Gaps: no in-stack PortAllocator punch (prebuilt libwebrtc only); mobile/Apple native channel not wired; no auto forceRelay session restart.

---

## F. Known gaps (other tracks)

- **Files:** Web unsupported; UU resume parity UNKNOWN; package `plugins/session_file_transfer`; opcode `LP_FILE_CHUNK=67`.  
- **VHID:** WinUHid driver+DLL not bundled; blankDisplay/exclusive temporarily prefers SendInput. HS path tree + `patches/vhid-relative-mouse/`.
- **Privacy:** custom screensaver image deferred; non-Windows native deferred. See [privacy-blank-display.md](./privacy-blank-display.md).
- **Post-merge (main):** channel backpressure / auto-accept default / exclusive+VHID / privacy per-session / floating menu enum — [post-merge-security-hardening.md](./post-merge-security-hardening.md).

---

## G. Related GitHub / public sources (open anywhere)

- UU official: https://uuyc.163.com/  
- UU work features: https://uuyc.163.com/features/work/  
- UU rename blog: https://uuyc.163.com/blog/20241206/41377_1198665.html  
- Fork: https://github.com/Sutodonez/cloudplayplus_plus  

Longer deep-RE writeups (e.g. `gameviewer-analysis.md`) lived in the old Project store only and are **not** published here. Prefer PR descriptions + this portable pack. For deep RE, keep using the REA Project / `.REA_Library\GameViewer` on Aorus_PC separately.

---

## H. Suggested kickoff prompt for the new Project

```
Continue CloudPlayPlus enhancements on https://github.com/Sutodonez/cloudplayplus_plus
Read portable handoff: docs/handoff/README.md (or paste this file).
Open PRs #1 punch, #2 file transfer, #3 vhid — review/merge/fix GUI per user.
Constraints: punch priority 1; replayable patches for future CPP; no NetEase binary copy.
```
