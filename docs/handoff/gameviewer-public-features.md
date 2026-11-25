# GameViewer / 网易UU远程 — 公开功能证据附录

**Product:** GameViewer 远程 → **网易UU远程**（2024-12 正式更名）  
**Official site:** https://uuyc.163.com/  
**Access date:** 2026-11-24 Asia/Shanghai  
**Scope:** Official marketing / help / blog / download pages + public community reports only.  
**Not in scope:** Reverse-engineering internals (deep RE `gameviewer-analysis.md` is REA Project store only; plain notes: [gameviewer-tech-notes-plain.md](./gameviewer-tech-notes-plain.md)).

### Evidence labels

| Label | Meaning |
|-------|---------|
| **FACT** | Stated on official NetEase UU pages (or dated official blog/help) as fetched |
| **OBSERVATION** | Directly seen in fetched page text / download version strings |
| **INFERENCE** | Logical combination of official claims; not independently verified |
| **UNKNOWN** | Thin, conflicting, or third-party-only; needs more evidence |

---

## 1. Product identity & clients

| Claim | Label | Source |
|-------|-------|--------|
| GameViewer 远程正式更名为网易UU远程 | FACT | https://uuyc.163.com/blog/20241206/41377_1198665.html (2024-12-10) |
| Clients: Windows, macOS, iOS, Android, Android TV | OBSERVATION | https://uuyc.163.com/download/ |
| Win V4.48.3 (2026.11.23); macOS V4.48.4 (2026.11.23); iOS V4.48.1 (2026.11.24); Android V4.48.2 (2026.11.20); Android TV V3.5.0 (2025.03.03) | OBSERVATION | same download page |
| TV client can control Windows; TV as host (被控) not supported | FACT | download page + https://uuyc.163.com/features/tv/ |
| “腾讯 GameViewer” is a distinct product | UNKNOWN / likely false | No official Tencent product found; all GameViewer→UU hits are NetEase (`uuyc.163.com`) |
| Public Discord / Steam page for UU远程 | UNKNOWN | Not found in this pass; community is mainly CN blogs, Bilibili, V2EX, app reviews |

---

## 2. Connectivity & account model

| Claim | Label | Source |
|-------|-------|--------|
| Basic remote control free; no queue / no ads (current marketing) | FACT | https://uuyc.163.com/ ; VIP blog https://uuyc.163.com/blog/20261118-dwdsa.html |
| Account bind for unattended devices; ID + verification code for assist | FACT | homepage “远程协助”; community mirrors |
| “高速专网直连”、全球节点 / 超200 布点 | FACT (marketing) | homepage; https://uuyc.163.com/features/work/ |
| Prefer P2P; fall back to UDP relay; quality varies by ISP / distance | OBSERVATION (community) | V2EX https://www.v2ex.com/t/1186601 ; SMZDM commentary https://post.smzdm.com/p/am9x487v/ |
| Force / auto relay exists for users | OBSERVATION (community) | V2EX thread (users mention 强制中转 / UDP relay) |
| End-to-end / DTLS + AES protection | FACT (marketing) | features/work privacy section |
| How ICE/punch is implemented | UNKNOWN (public) | Not documented on marketing pages — see RE docs. **Migration ranking** (Human decision): Enhanced punch is CPP priority 1 despite being undocumented publicly; see [cloudplayplus-vs-gameviewer.md](./cloudplayplus-vs-gameviewer.md) §3 / §4.4 |

---

## 3. Display / encode / quality

| Claim | Label | Source |
|-------|-------|--------|
| Up to 4K / 144 fps marketed | FACT | homepage; features/work; features/color |
| 真彩 / 4:4:4 chroma | FACT | rename blog; https://uuyc.163.com/features/color/ |
| Custom bitrate up to 500 Mbps | FACT | features/work |
| HDR (Windows↔Windows; GPU caveats) | FACT | https://uuyc.163.com/help/hdr.html |
| Android control side cannot enable 真彩 | FACT | features/color FAQ |
| AMD host GPU: 真彩 not supported; NVIDIA generally yes; Intel needs encoder/decoder match | FACT | features/color FAQ |
| “原画” and 真彩 cannot both apply on some devices | FACT | rename blog notes |

---

## 4. Multi-device / multi-monitor / virtual display

| Claim | Label | Source |
|-------|-------|--------|
| Multi-device management via same account; unlimited device count (marketing) | FACT | https://uuyc.163.com/features/device/ |
| Multi-monitor: single-tab switch or split windows | FACT | features/device |
| Max **5** screens connected; max **3** virtual screens | FACT | features/device FAQ |
| Wireless secondary display (手机/平板 → PC 扩展屏，非镜像) | FACT | https://uuyc.163.com/features/wireless-screen/ |
| One wireless副屏 only; no audio on副屏 | FACT | wireless-screen FAQ |
| TV remote creates virtual secondary screen (can look like host black screen) | FACT | features/tv FAQ |

---

## 5. Input / gamepad / key mapping

| Claim | Label | Source |
|-------|-------|--------|
| Keyboard / mouse / multi-touch / gamepad | FACT | homepage |
| Official + user 按键映射 schemes; share codes | FACT | https://uuyc.163.com/features/keyboard/ |
| Gamepads: Xbox / PS / Switch Pro (platform matrix); up to 4 on Windows | FACT | https://uuyc.163.com/help/20241203/40221_1197714.html |
| Rumble supported; gyro / touchpad not supported | FACT | same help page |
| “智能游戏鼠标” can be toggled if drift | FACT | features/keyboard FAQ |
| 仿真鼠标 (touch → mouse) called out in community 4.0 notes | OBSERVATION (community) | Bilibili opus comparing peers |

---

## 6. File transfer

| Claim | Label | Source |
|-------|-------|--------|
| Cross-device file transfer (Win/macOS/iOS/Android); files + folders | FACT | rename blog 2024-12-10; homepage |
| No size / type / count limit (marketing) | FACT | homepage; features/work FAQ |
| **断点续传:** rename blog (2024-12) says **not yet**; features/work (current) lists **断点续传** | CONFLICT → treat current marketing as claimed, historical as outdated | https://uuyc.163.com/blog/20241206/41377_1198665.html vs https://uuyc.163.com/features/work/ |
| Leaving transfer UI / backgrounding may interrupt (esp. mobile) | FACT (historical help) + community | rename blog notes; third-party writeups |

---

## 7. Privacy / security UX

| Claim | Label | Source |
|-------|-------|--------|
| 防窥: off / 关闭显示屏 (Win only) / 隐私屏保 (preset or custom image) | FACT | https://uuyc.163.com/help/20241203/40221_1197692.html |
| Host mute + lock after disconnect | FACT | features/work |
| Local hotkey to dismiss 防窥 then auto-lock host | FACT | privacy help (Ctrl+Alt+P / control+option+P) |
| ISMS / privacy certs / penetration test badges on site | OBSERVATION | homepage |

---

## 8. Wake-on-LAN

| Claim | Label | Source |
|-------|-------|--------|
| Remote power-on via WOL for Windows hosts | FACT | https://uuyc.163.com/help/20241203/40220_1197682.html |
| Requires NIC + BIOS WOL, client auto-start, **LAN helper device online** to send magic packet | FACT | same |
| Helper: another UU client (Win/macOS/Android) or selected routers / UU加速盒 | FACT | same |
| Scheduled WOL | UNKNOWN | FAQ-style mirrors say not clearly offered |

---

## 9. Terminal / port mapping / CLI

| Claim | Label | Source |
|-------|-------|--------|
| Remote terminal without full desktop video | FACT | features/work “终端连接”; Mac update blog |
| Multi-session, disconnect-inherit, TUI (htop/vim/coding agents), input box + voice IME | FACT | https://uuyc.163.com/blog/20261010-zdgx.html (2026-10-10) |
| Both ends ≥ V4.39.0 for new terminal | FACT | same |
| Windows default PowerShell; `uuyc-cli lterm` for custom shells / Mac attach | FACT | same |
| Port mapping: TCP tunnel via jump host; GUI; reuse existing remote session | FACT | https://uuyc.163.com/blog/20260507-dkys.html |
| Port mapping initially Windows controller; Mac later gained it | FACT | port-mapping blog + https://uuyc.163.com/blog/20260821-shemeibangyun1.html |
| CLI for connect / cloud PC / terminal scripting | OBSERVATION | Weibo/official social mentions (2026-06); depth UNKNOWN |

---

## 10. Pricing tiers (as of access date)

| Claim | Label | Source |
|-------|-------|--------|
| VIP / SVIP “高阶增值” planned **2026-12-01**; basic remote stays free (no queue/ads) | FACT | https://uuyc.163.com/blog/20261118-dwdsa.html |
| Pre-2026-12-01 registrants: annual card 50% perk | FACT | same |
| Exact VIP feature matrix / price numbers on membership.html | UNKNOWN from fetch | https://uuyc.163.com/help/membership.html returned empty body in this fetch (likely JS-rendered) |
| Third-party summaries (IT之家 / blogs): free → 1080p30; VIP 4K/144/真彩/HDR/多屏; SVIP + global nodes; ~¥238/¥758 year | OBSERVATION (secondary) | https://tech.ifeng.com/c/8yB6uVF7NDr ; https://wanyr.com/2026/11/uu-remote-vip-svip-pricing-dec1.html — treat as **not official** until membership page confirms |
| May 2026 anniversary: “较长一段时间没有收费计划” | FACT (historical) | https://uuyc.163.com/blog/20260528-2year.html — superseded by Nov VIP announcement |

---

## 11. Community strengths vs remote-desktop peers

| Theme | Label | Source |
|-------|-------|--------|
| Strength: LAN / same-ISP low latency; free high fps/quality (pre-VIP split) | OBSERVATION | Bilibili / SMZDM comment digests |
| Strength: game key maps + gamepad; easy mobile game stream | OBSERVATION | features/keyboard; community |
| Weakness: cross-province / cross-ISP P2P unstable; relay quality uneven | OBSERVATION | V2EX; SMZDM |
| Weakness (older reviews): fewer office extras vs ToDesk/向日葵; Linux missing | OBSERVATION | Bilibili peer reviews — some claims outdated after 2025–2026 feature drops |
| Linux / Harmony clients “coming” | OBSERVATION (secondary press) | IT之家 VIP coverage — confirm on official roadmap when available |

---

## 12. Features **not** claimed publicly (or thin)

| Topic | Status |
|-------|--------|
| Enhanced Symmetric Hole Punching / `PunchCheckFireWall` / vhid internals | **Not in public docs** — RE only |
| Recording / session replay | UNKNOWN — not found on main feature pages this pass |
| UAC elevation UX | UNKNOWN |
| Clipboard (explicit marketing) | UNKNOWN (likely present; not featured) |
| LAN discovery without account | UNKNOWN |
| Multi-user simultaneous control of one host | Third-party says no — treat UNKNOWN/weak |

---

## 13. Citation index (primary)

| URL | Role |
|-----|------|
| https://uuyc.163.com/ | Homepage feature list |
| https://uuyc.163.com/download/ | Clients / versions |
| https://uuyc.163.com/blog/20241206/41377_1198665.html | Rename + file transfer + 真彩 launch |
| https://uuyc.163.com/features/work/ | Office feature set |
| https://uuyc.163.com/features/color/ | 真彩 details |
| https://uuyc.163.com/features/device/ | Multi-screen / virtual screen |
| https://uuyc.163.com/features/keyboard/ | Key map / game controls |
| https://uuyc.163.com/features/wireless-screen/ | Wireless副屏 |
| https://uuyc.163.com/features/tv/ | Android TV |
| https://uuyc.163.com/help/20241203/40221_1197692.html | 防窥 |
| https://uuyc.163.com/help/20241203/40220_1197682.html | WOL |
| https://uuyc.163.com/help/20241203/40221_1197714.html | Gamepad matrix |
| https://uuyc.163.com/help/hdr.html | HDR |
| https://uuyc.163.com/blog/20260507-dkys.html | Port mapping |
| https://uuyc.163.com/blog/20261010-zdgx.html | Terminal upgrade |
| https://uuyc.163.com/blog/20261118-dwdsa.html | VIP announcement |
| https://www.v2ex.com/t/1186601 | Community NAT/relay |
| https://post.smzdm.com/p/am9x487v/ | Community peer comparison digest |

**Related RE docs:** [gameviewer-tech-notes-plain.md](./gameviewer-tech-notes-plain.md); deep RE `gameviewer-analysis.md` not in this pack  
**Comparison:** [cloudplayplus-vs-gameviewer.md](./cloudplayplus-vs-gameviewer.md)
