# CloudPlayPlus vs GameViewer — feature comparison & plugin migration

**Updated:** 2026-11-24 Asia/Shanghai  
**CPP checkout:** `https://github.com/Sutodonez/cloudplayplus_example` (this workspace)  
**GV evidence:**  
- RE: [10-analysis-summary.md](./10-analysis-summary.md), [11-tech-notes-plain.md](./11-tech-notes-plain.md)  
- Public: [12-public-features.md](./12-public-features.md) (官网 / 帮助 / 社区；访问日 2026-11-24 Asia/Shanghai)  
**Product note:** GameViewer 远程 = **网易UU远程**（`uuyc.163.com`）；非腾讯产品。  
**Scope:** Analysis and plan only — no plugin / ICE implementation in this pass.

### Evidence confidence

| Claim class | Basis |
|-------------|--------|
| GV NAT / mouse / terminal internals | Ghidra **FACT** / **INFERENCE** as labeled in GV store docs (**RE**) |
| GV product features (file xfer, 防窥, WOL, 多屏, 真彩, VIP…) | Official pages **FACT** / community **OBSERVATION** (**public**) |
| CPP architecture / APIs | **OBSERVATION** from this checkout + `CloudPlayPlus/hardware_simulator` upstream |
| Migration rankings | **INFERENCE** from value × feasibility × plugin-fit, **overridden by Human decision** on punch priority (below) |

### Human decision (binding for ranking)

1. **Enhanced hole punching / hard NAT is priority 1** — not deferred for “upstream churn” alone.  
2. If no soft alternative reaches GV-class punch, **direct CPP / flutter-webrtc / ICE changes are allowed**.  
3. **Hard constraint:** any such change must be **re-applicable to future CPP versions** (isolated patch series, bounded fork diffs, cherry-pickable commits, or a documented rebase playbook).

**Plugin preference** still applies when two options are equal in capability; punch **may** live in the vendored transport stack if the replay constraint is met.

---

## 1. CloudPlayPlus architecture (survey)

| Layer | What exists |
|-------|-------------|
| App | Flutter (`lib/`): signaling (`websocket_service`), sessions (`entities/session.dart`), input protocol (`controller/hardware_input_controller.dart`, `entities/messages.dart`), UI/settings |
| Streaming | Custom `plugins/flutter-webrtc` (HW accel / GPU texture fork of flutter-webrtc); screen via `getDisplayMedia` / desktop capturer |
| Input / display | Path plugin `hardware_simulator` (git submodule → CloudPlayPlus org): mouse/keyboard inject, cursor lock, virtual display (Parsec VDD), gamepad, service mode |
| Other path plugins | `window_manager`, `fullscreen_window`, `virtual.keyboard.dart`, `flutter_gamecontroller`, `floating_menu_panel`, … |
| “Plugin / extension” model | **Build-time Flutter plugins only** — no runtime extension host |
| Upstream churn | README + vendored forks: WebRTC and `hardware_simulator` already diverge; main app updates often (`release_note.md`) |

**Implication:** Prefer path plugins / isolated Dart when capability is equal. For **hard NAT punch**, transport-fork work is authorized if packaged as a **replayable** patch (see §4.4).

---

## 2. Feature matrix

Columns **Src**: `public` = official/community claim; `RE` = reverse-engineering; both when corroborated.

| Area | GameViewer / UU远程 | Src | CloudPlayPlus (this repo) | Gap owner |
|------|---------------------|-----|---------------------------|-----------|
| **Symmetric NAT / Enhanced Hole Punch** | `streamer.dll`: Enhanced Hole Punching, `PunchCheckFireWall` (UDP → `119.29.29.29` / `223.5.5.5`), `RandomSymmericPunchToCone`, ICE ufrag/pwd; prefer P2P then `force_relay` / ISP+QoS | **RE** | Standard WebRTC ICE; STUN + optional TURN-only; no Enhanced Punch / SymmetricPunch / firewall probe | **GV ahead** — **#1 migrate** |
| **Relay / 专网 marketing** | “高速专网直连”、全球节点; community: UDP P2P vs UDP relay, force relay | **public** + **RE** (`*_relay_isp`, `force_relay`) | User TURN toggle; when on, STUN list replaced (not concurrent ladder). No `iceTransportPolicy` in `lib/` | Soft gap in CPP; hard punch remains GV |
| **Relative mouse / vhid** | Relative path + **vhid** (`send_input` ↔ `vhid`) | **RE** | `LP_MOUSEMOVE_RELATIVE` + `SendInput`; **no vhid** | Protocol ✓; **vhid gap** |
| **Absolute / desktop mouse** | Present | **RE** | Strong: absl %, multi-monitor mapping, cursor sync, lock | CPP competitive |
| **Server terminal** | conpty / MuxControl (**RE**); public: multi-session, inherit, TUI, `uuyc-cli` (V4.39+) | **public**+**RE** | **Absent** | **GV ahead** |
| **File transfer** | Cross-device files/folders; marketing: unlimited size; 断点续传 claimed on current work page (2024 rename blog said not yet — conflict) | **public** | **Absent** (text clipboard sync only in `session.dart`) | **GV ahead (public)** |
| **防窥 / privacy** | Off / blank display (Win) / custom screensaver; mute; lock after session | **public** | **Absent** | **GV ahead (public)** |
| **Wake-on-LAN** | WOL + LAN helper device / router | **public** | **Absent** | **GV ahead (public)** |
| **Port mapping (TCP tunnel)** | GUI tunnel; reuse remote session | **public** | **Absent** | **GV ahead (public)** |
| **Multi-monitor** | Up to 5 screens; tab / split | **public** | Multi-monitor select / mapping (release_note 1.0.3+) | Soft / parity |
| **Virtual display** | Up to 3 virtual screens; TV auto-creates副屏 | **public** | Parsec VDD via `hardware_simulator` (extend / exclusive) | CPP competitive (**OBS**); UX differs |
| **Wireless副屏** | Phone/tablet as PC extended display | **public** | Not the same product surface | **GV ahead (public)** |
| **真彩 4:4:4 / HDR / 4K144** | Marketed; GPU matrix; VIP may gate high tiers from 2026-12-01 | **public** | 2K@60 / ~40ms claim; NVIDIA encode; H.265 TODO; no 4:4:4 product mode | Partial / encode roadmap |
| **Gamepad / touch / 按键映射** | Official cloud schemes + rumble; 4 pads | **public** | Gamepads, touch modes, pen, on-screen controls | CPP strong for DIY; GV ahead on scheme library |
| **Account / assist** | Account devices + ID/验证码 assist | **public** | Account + web client | Soft |
| **Clients** | Win / macOS / iOS / Android / Android TV | **public** | Desktop hosts + mobile + web; Android TV noted in release_note | Soft |
| **Pricing** | Basic free; VIP/SVIP from 2026-12-01 (high quality / nodes) | **public** | Own product model | N/A |
| **Clipboard / QoS UI** | OnNatInfo / OnQosStats (**RE**); clipboard not heavily marketed | **RE** / **UNKNOWN public** | Text clipboard sync; latency stats 1.0.9 | Partial |

### Conflicts: marketing vs RE

| Topic | Public claim | RE finding | Resolution for planning |
|-------|--------------|------------|-------------------------|
| Connectivity | “专网直连 / 全球节点 / 即点即连” | Custom Enhanced Punch + firewall probes + ISP relay / `force_relay` | Marketing describes **outcome**; RE shows **mechanism**. Plan punch from RE; measure with public P2P/relay user pain |
| File 断点续传 | Current work page: yes; 2024-12 blog: no | Not in RE scope | Assume **resume exists in recent builds**; verify before implementing parity |
| Terminal | First-class product (sessions, TUI, CLI) | conpty_bridge + MuxControl | Aligned — public expands product surface beyond RE skeleton |
| Virtual mouse | 仿真鼠标 / 智能游戏鼠标 (UX) | **vhid** backend for relative inject | Public UX ≠ RE HID; both matter; do not conflate |
| “真免费 4K144” | Homepage still markets; VIP blog moves high tiers to paid | N/A | Pricing shifting 2026-12-01 — don’t treat free 4K as durable |

---

## 3. Migration candidates (re-ranked)

Score axes (1–5): **V**alue · **F**easibility · **P**lugin-fit.  
**Human override:** Enhanced Punch is **Rank 1** even if P is low — transport work allowed if **replayable** (§4.4).

| Rank | Candidate | Src | V | F | P | Verdict |
|------|-----------|-----|---|---|---|---------|
| **1** | **Enhanced Symmetric Hole Punch / hard-NAT ladder** (firewall probe + symmetric punch + P2P-prefer then force_relay) | **RE** (+ public pain) | 5 | 2–3 | 1–2 | **Do first.** Prefer soft ICE experiments *in parallel* only as measurement — not as a substitute that demotes punch. Implement in vendored `flutter-webrtc` / ICE with **replayable patch series** |
| **2** | **File transfer** (session data-channel or side channel; folders + resume) | **public** | 5 | 4 | 5 | Best *product* plugin after punch; CPP has clipboard only |
| **3** | **Virtual HID / relative-mouse hardening** | **RE** | 5 | 4 | 5 | Best *input* plugin; extend `hardware_simulator` |
| **4** | **Soft ICE / TURN ladder** (concurrent STUN+TURN; `iceTransportPolicy: relay` on fail) | both | 4 | 4 | 4 | **Complement** to #1 (ops + fallback), not a replacement |
| **5** | **防窥 privacy mode** (blank display / overlay + optional lock) | **public** | 4 | 4 | 5 | Host plugin + settings; high RD parity |
| **6** | **Server terminal** (conpty / PTY + session inherit) | **public**+**RE** | 4 | 3 | 5 | New `host_terminal` plugin; public raises value vs earlier rank |
| **7** | **Wake-on-LAN** (+ optional LAN helper) | **public** | 3 | 3 | 4 | Isolated Dart/native helper |
| **8** | **Port mapping (TCP)** | **public** | 3 | 3 | 4 | Tunnel plugin; orthogonal to media |
| **9** | **ISP / QoS auto relay metadata** | **RE** | 3 | 2 | 2 | Needs relay fleet inventory; pairs with #1/#4 |

### Top 3 (after public research + Human punch decision)

1. **Enhanced hole punching / hard NAT** (vendored ICE; replayable).  
2. **File transfer** (Flutter/data-channel plugin).  
3. **vhid relative mouse** (`hardware_simulator`).

---

## 4. Plugin migration assessment

### 4.1 What fits plugins vs core

| Feature | Plugin fit | Where to put it | Core change still required? |
|---------|------------|-----------------|------------------------------|
| **Enhanced Symmetric Punch** | **Weak as MethodChannel plugin**; **allowed in transport fork** | Vendored `flutter-webrtc` / libwebrtc PortAllocator / NatTraversal-equivalent; thin Dart knobs (enablePunch, forceRelay) | Yes — ICE stack; must follow §4.4 replay rules |
| Soft ICE / TURN ladder | Medium | Dart next to `createRTCPeerConnection` | Session ICE builder |
| File transfer | **Strong** | New plugin or isolated Dart + data-channel opcodes | Message types + UI |
| Relative mouse + **vhid** | **Strong** | `hardware_simulator` | Minimal protocol reuse |
| 防窥 | **Strong** | Host display plugin + VDD blank path | Settings |
| Server terminal | **Strong** | `host_terminal` + data-channel mux | New opcodes |
| WOL | Medium–strong | Small native/Dart utility + signaling “wake” | Account/device list hook |
| Port mapping | Medium | Tunnel helper process / Dart | Signaling session reuse |
| ISP/QoS relay policy | Weak–medium | Signaling + Dart | Server inventory **UNKNOWN** for CPP cloud |

### 4.2 Risks with frequent upstream updates

1. **`flutter-webrtc` fork:** Already customized for HW encode. Punch work **adds** rebase surface — acceptable only with §4.4 discipline (bounded diffs, patch series).  
2. **`hardware_simulator`:** Keep vhid behind existing `performMouseMoveRelative` API.  
3. **App `lib/` churn:** Keep ICE policy / feature flags in one module; avoid scattering punch toggles across UI.  
4. **No runtime plugin loader:** Still rebuild/pubspec for path plugins.  
5. **Legal:** Migrate **ideas / ladder design** from GV docs; do not copy NetEase binaries or decompiled bodies.

### 4.3 Recommended boundaries

```
┌─────────────────────────────────────────────────────────┐
│ cloudplayplus app (lib/)                                │
│  - signaling, SDP/ICE config builder, data-channel mux  │
│  - settings: enablePunch, icePolicy, useVhidMouse, …    │
└───────────────┬───────────────────────────┬─────────────┘
                │                           │
   ┌────────────▼────────────┐   ┌──────────▼──────────────┐
   │ hardware_simulator      │   │ host_terminal / file_xfer│
   │  mouse: SendInput|vhid  │   │  privacy / WOL helpers   │
   └─────────────────────────┘   └─────────────────────────┘

   ┌─────────────────────────────────────────────────────┐
   │ flutter-webrtc / libwebrtc FORK (PRIORITY for punch)│
   │  Enhanced punch + PortAllocator hooks               │
   │  MUST ship as replayable patch series (§4.4)        │
   └─────────────────────────────────────────────────────┘
```

**Boundary rules**

1. Input backends stay in `hardware_simulator`.  
2. Terminal / file transfer / privacy never share mouse code paths.  
3. **NAT punch is first-class transport work**, not “last resort after soft ladder.” Soft ladder remains a **parallel** fallback and ops control.  
4. Stable MethodChannel / Dart setting names; feature-flag punch so hosts without the fork build still compile.

### 4.4 Replay onto future CPP — punch strategy

**Goal:** After any CloudPlayPlus / flutter-webrtc upstream bump, re-apply hard-NAT work without archaeology.

| Practice | Requirement |
|----------|-------------|
| **Isolated patch series** | One topic per commit/patch: (1) probe / PunchCheckFireWall equivalent, (2) symmetric punch to remote STUN candidate, (3) ICE config / ufrag wiring, (4) force_relay / policy hooks, (5) Dart/FFI feature flags. No drive-by encode/UI edits in the same series |
| **Bounded fork diff** | Touch only PortAllocator / P2P transport / NAT traversal–adjacent files; keep a `docs/patches/nat-punch/FILE_LIST.md` of owned paths |
| **Cherry-pickable commits** | Prefer linear commits on a dedicated branch `cursor/nat-punch-*`; each commit builds; no squash of unrelated submodule noise |
| **Quilt / git format-patch** | Maintain `patches/nat-punch/*.patch` regenerated after each successful rebase; CI or script applies `git am` / `patch -p1` onto tagged upstream flutter-webrtc |
| **Rebase playbook** | Short runbook in-repo: fetch upstream → apply series → resolve only listed conflict files → run NAT test matrix (Symmetric↔Cone, firewall on/off, force_relay) → bump submodule pin |
| **ABI / API freeze** | Dart surface: e.g. `IcePunchOptions{enabled, forceRelay, probeHosts}` — do not rename casually; native exports versioned |
| **Anti-pattern** | One-off edits inside generated bindings, unmarked binary drops, or “fix while rebasing encode” that cannot be replayed |

Soft ICE ladder changes in pure Dart should also live in one module (`ice_policy.dart` or similar) so they rebase independently of the native punch series.

---

## 5. Public-only vs RE-only (migration lens)

### 5.1 Public-only (or public-first) — worth migrating for product parity

| Feature | Why | Plugin note |
|---------|-----|-------------|
| File transfer (+ resume) | Office + game-mod workflows; CPP gap | Strong plugin |
| 防窥 / privacy screen | Competitive RD hygiene | Strong plugin |
| WOL + helper | Unattended gaming PC | Medium plugin |
| Port mapping | Dev / NAS without separate frp | Medium plugin |
| Cloud 按键映射 library | Mobile game UX polish | Dart + assets; optional |
| Wireless副屏 | Distinct product; lower for core game stream | Defer unless roadmap |
| 真彩 / HDR product modes | Encode pipeline; partial overlap with CPP HW path | Core encode, not MethodChannel |

### 5.2 RE-only (undocumented internals) — still critical

| Feature | Why | Note |
|---------|-----|------|
| **Enhanced Hole Punch / SymmetricPunch / firewall DNS probes** | Explains hard-NAT edge; **#1 priority** | Not marketed as such; implement from ladder **design**, not code copy |
| **vhid** relative mouse backend | Stubborn Raw Input games | Extend HS plugin |
| MuxControl / conpty_bridge wiring details | Informs terminal plugin design | Public now describes *product*; RE informs *host spawn* |
| `*_relay_isp` / OnNatInfo / OnQosStats plumbing | Relay quality automation | Needs CPP relay metadata (**UNKNOWN**) |

---

## 6. Ranked recommendation (executive)

1. **Priority 1 — Enhanced hole punching / hard NAT** in the vendored WebRTC stack, shipped as a **replayable patch series** (§4.4). Soft ICE ladder is complementary measurement/fallback, not a demotion of punch.  
2. **Next product plugin — file transfer** (public gap; high user value; survives app churn).  
3. **Next input plugin — vhid** relative mouse in `hardware_simulator`.  
4. Then: 防窥 → host terminal → WOL → port mapping → QoS/ISP relay policy (as fleet data allows).  
5. Encode/真彩/HDR: track on CPP encode roadmap; not a MethodChannel plugin.

### Explicit non-goals for this analysis pass

- No implementation PRs / ICE patches in this pass.  
- Do not copy NetEase binaries or decompiled functions.  
- Do not treat VIP pricing tables from secondary press as FACT until official membership page content is readable.

---

## 7. Sources

| Doc / code | Use |
|------------|-----|
| [12-public-features.md](./12-public-features.md) | Official + community claims (FACT/OBS/INFERENCE/UNKNOWN) |
| [10-analysis-summary.md](./10-analysis-summary.md) | GV NAT / mouse / terminal RE FACT |
| [11-tech-notes-plain.md](./11-tech-notes-plain.md) | Plain-language GV ladder |
| `/workspace/README.md`, `lib/entities/session.dart`, `lib/controller/hardware_input_controller.dart`, `lib/entities/messages.dart`, `release_note.md` | CPP ICE + input + clipboard |
| `design docs/连接掉线管理.md`, `guidance/install_coturn.sh` | CPP punch-fail / TURN ops |
| `https://github.com/CloudPlayPlus/hardware_simulator` | Host inject: `SendInput` (no vhid in surveyed sources) |
| https://uuyc.163.com/ and linked help/blog pages | Public feature matrix (access 2026-11-24 Asia/Shanghai) |
