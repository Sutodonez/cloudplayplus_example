# Windows 试用：栈外穿透（out-of-stack punch）

**中文优先 · bilingual how-to**  
**Branch / PR:** [`cursor/trial-out-of-stack-punch-434f`](https://github.com/Sutodonez/cloudplayplus_plus/tree/cursor/trial-out-of-stack-punch-434f) · [#14](https://github.com/Sutodonez/cloudplayplus_plus/pull/14)  
**Tag:** `trial/out-of-stack-punch` @ `bf7f886`  
**Scope:** Windows Desktop first. This is **not** in-stack PortAllocator SymmetricPunch and does **not** authorize merging punch to `main`.

### Alpha 便携包 / Portable alpha

| 项 | 值 |
|----|-----|
| **Version** | `0.1.0-alpha.out-of-stack+bf7f886` |
| **Release** | [v0.1.0-alpha.out-of-stack](https://github.com/Sutodonez/cloudplayplus_plus/releases/tag/v0.1.0-alpha.out-of-stack) (prerelease, overwritten) |
| **Zip** | `cppp-trial-oos-0.1.0-alpha+bf7f886-windows-x64.zip` — 解压后运行 `cloudplayplus.exe` |
| **Binary tip** | `bf7f8865484146e0924a93caedde22b04e1357c5` |
| **相对 +045e380** | Medium+ 加固 + MSVC sscanf 修复 + 0010 SymmetricPunch hunk 校正 |
| **配对约定** | 日后栈内 alpha：`0.1.0-alpha.in-stack+<tip7>`（共享 major.minor `0.1.0`） |

详情：`docs/alpha-out-of-stack-release.md`（仓库 / Project store）。

---

## 这是什么 / What this is

| 中文 | English |
|------|---------|
| 在难 NAT 场景下，用 **ICE 旁路**（防火墙 UDP 探测 + 对称多 socket 突发）提高 P2P 成功率 | Out-of-stack punch: firewall UDP probes + multi-socket bursts **beside** ICE |
| 软 ICE：开启打洞且配置 TURN 时 STUN+TURN 并发 | Soft ICE: concurrent STUN+TURN when punch + TURN |
| `forceRelay`：强制只走 TURN | `forceRelay`: TURN-only (`iceTransportPolicy: relay`) |

Also on this tip (from `main`): privacy blank display, server terminal, file transfer, VHID relative mouse.

---

## 前置条件 / Prerequisites

- Windows 10/11 + **Visual Studio** C++ desktop workload (same as normal Flutter Windows)
- [Flutter](https://docs.flutter.dev/get-started/install/windows) stable on `PATH`
- **Git Bash** (or WSL) for `scripts/*.sh`
- **Python 3** as `python3`, `python`, or `py -3` (LF normalize in `apply-patches.sh`)
- Two machines / networks for a real NAT trial (ideal: Symmetric ↔ Cone). Same LAN is a smoke test only.

---

## 1. 取代码 / Checkout

```bash
git clone --recurse-submodules https://github.com/Sutodonez/cloudplayplus_plus.git
cd cloudplayplus_plus
# Prefer the tag for a frozen trial tip:
git fetch --tags
git checkout trial/out-of-stack-punch
# Or the moving trial branch:
# git checkout cursor/trial-out-of-stack-punch-434f
scripts/submodule-init.sh
```

Vendor pin must be `87c0920…` (see `docs/layout.md`).

---

## 2. 打补丁并编译 Windows / Apply + build

```bash
# Git Bash:
scripts/apply-patches.sh          # expects 10 patches (0001–0010)
scripts/build.sh windows          # apply + flutter pub get + flutter build windows
```

Or interactive:

```bash
scripts/apply-patches.sh
cd vendor/cloudplayplus
flutter pub get
flutter run -d windows
```

Optional unit check (after apply):

```bash
cd vendor/cloudplayplus
flutter test test/ice_policy_test.dart
```

**CI note (FACT):** Windows Desktop check is green on this trial tip — local build should match if VS/Flutter are set up.

---

## 3. 设置开关 / Settings knobs

Open the app → **网络设置 (Network settings)** → section **「NAT 穿透 / 打洞」**:

| Switch | Default | Meaning |
|--------|---------|---------|
| **启用增强打洞 (enablePunch)** | ON | Firewall probes to `119.29.29.29` / `223.5.5.5` + symmetric bursts toward remote `srflx`/`host` |
| **强制中继 (forceRelay)** | OFF | Skip P2P; TURN-only |
| **使用turn中继服务器** (existing) | as configured | With punch ON: soft ladder (STUN+TURN concurrent). Alone: TURN path |

**Suggested first matrix**

1. Punch ON, TURN OFF, forceRelay OFF — pure P2P + punch  
2. Punch ON, TURN ON, forceRelay OFF — soft ICE  
3. forceRelay ON (+ TURN) — relay baseline (control)  
4. Punch OFF — stock-like ICE control  

Change toggles **before** starting a new session (no auto-restart into forceRelay after ICE fail).

---

## 4. 成功长什么样 / What success looks like

| Signal | How to read it |
|--------|----------------|
| Session connects with Punch ON / forceRelay OFF | Punch path did not break ICE |
| Prefer **host/srflx** selected over relay when both exist | Soft ladder preferring P2P |
| Logs contain `NatPunch` firewall / symmetric punch lines | Probes/bursts ran (native MethodChannel or Dart fallback) |
| forceRelay ON → traffic via TURN | Control path works |
| Hard NAT (Symmetric↔Cone) P2P succeeds more often than Punch OFF | Functional win for this trial |

Failure to connect with Punch ON is **not** automatically fixed — UI may suggest turning on **强制中继 (forceRelay)** or TURN; you reconnect manually.

---

## 5. 已知缺口 / Known gaps (do not treat as merge-gate pass)

- **No** in-stack `PortAllocator` SymmetricPunch (prebuilt libwebrtc only) — merge-to-`main` gate unchanged  
- iOS / macOS / Android **native** MethodChannel not wired (Dart `RawDatagramSocket` fallback where `dart:io` works)  
- No automatic session restart into forceRelay after ICE failure  
- Real multi-NAT matrix still requires human networks  
- Do **not** merge [#14](https://github.com/Sutodonez/cloudplayplus_plus/pull/14) to `main` as “punch done”

In-stack exploration: [#15](https://github.com/Sutodonez/cloudplayplus_plus/pull/15) / `docs/handoff/in-stack-punch-plan.md`.

---

## 6. 故障速查 / Troubleshooting

| Symptom | Check |
|---------|--------|
| `apply-patches.sh` fails on Python | Install Python 3; ensure `python3`, `python`, or `py -3` works in Git Bash |
| Patch reject / dirty vendor | `git -C vendor/cloudplayplus reset --hard` then re-run apply |
| Windows build can't find VS | Install VS 2022 C++ desktop workload; use Developer / Flutter doctor |
| No punch effect | Confirm section「NAT 穿透 / 打洞」; restart session after toggle; check logs for `NatPunch` |
| Always relay | Turn **forceRelay** OFF; confirm TURN isn't the only candidate path |

---

## Related docs

- `docs/trial-out-of-stack-punch.md` — trial meaning / absorption  
- `docs/handoff/nat-punch.md` — feature handoff  
- `patches/nat-punch/README.md` — patch ownership  
