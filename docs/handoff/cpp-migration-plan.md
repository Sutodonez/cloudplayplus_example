# CloudPlayPlus migration plan — punch / vhid / file transfer

**Updated:** 2026-11-24 Asia/Shanghai  
**Repo:** https://github.com/Sutodonez/cloudplayplus_example  
**Constraint:** Three independent branches + PRs. Prefer plugin-shaped work; punch may touch vendored ICE if **replayable** onto future CPP.

## Tracks

| Track | Goal | Branch hint | Primary touch |
|-------|------|-------------|----------------|
| 1 Punch | Enhanced / hard-NAT hole punch + soft ladder complement | `feat/enhanced-hole-punch` | Vendored `flutter-webrtc` / ICE + thin Dart flags; patch series + rebase notes |
| 2 Mouse | Virtual HID / relative-mouse hardening | `feat/vhid-relative-mouse` | `hardware_simulator` (+ settings); reuse `LP_MOUSEMOVE_RELATIVE` |
| 3 Files | Session file/folder transfer (+ resume if feasible) | `feat/file-transfer` | New plugin or isolated Dart + data-channel opcodes + UI |

## Shared references

- Ranking & replay rules: [cloudplayplus-vs-gameviewer.md](./cloudplayplus-vs-gameviewer.md) (§3, §4.4)
- Public GV/UU features: [gameviewer-public-features.md](./gameviewer-public-features.md)
- RE NAT / mouse (plain): [gameviewer-tech-notes-plain.md](./gameviewer-tech-notes-plain.md); deep RE `gameviewer-analysis.md` not in this pack (REA store only)

## Done when

Each track: working change on its branch, open PR, short replay/rebase notes (punch required), basic verification described honestly.
