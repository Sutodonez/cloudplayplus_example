# 栈内穿透 — 可重建 libwebrtc pin 选项

**In-stack punch — rebuildable libwebrtc pin options**

**状态 / Status：** **选项 A 已由人工选定**（2026-11-25）。B/C 依赖升级**延后**到正式「栈内 vs 栈外」产品选择之后。  
**分支 / Branch：** `cursor/trial-in-stack-punch-434f`（PR [#15](https://github.com/Sutodonez/cloudplayplus_plus/pull/15)）  
**更新 / Updated：** 2026-11-25 Asia/Shanghai（UTC+8）— 中英双语（中文优先）  
**命名 / Naming：** 本仓库项目缩写为 **CPPS**（非 CPPP）；上游源码仍为 **CPP**。

---

## 给人看的判断（先读这里）

| 项 | 决定 |
|----|------|
| **已选定** | **A** — 在 **m125 / 125.6422** 上重建，对齐 flutter-webrtc **0.11.7** |
| **延后** | **B**（m144/m150 bump）、**C**（上游优先）— 待正式栈内/栈外产品抉择后再做 |
| **不采用** | **D**（仅栈外）— 无法关闭合入门禁 |
| **Windows 重建** | 见 [`docs/handoff/in-stack-m125-windows-rebuild.md`](./handoff/in-stack-m125-windows-rebuild.md)；本云端 Linux **不能**出 DLL |
| **版本配对（有二进制后）** | `0.1.0-alpha.in-stack+<tip>` |
| **合入 `main`** | **禁止**，直至门禁与验证满足 |

**Chosen / Status (EN):** Human selected **Option A**. B/C deferred. Do not merge to `main`.

---

## 选项一览（历史 + 当前）

| 选项 | 一句话 | 本轮 |
|------|--------|------|
| **A** | 留在 m125，重建 + PortAllocator SymmetricPunch | **执行中** |
| **B** | 升到 m144/m150 + bump flutter-webrtc | **延后** |
| **C** | 先上游贡献再消费 | **延后** |
| **D** | 只保留栈外 | 不采用（关门禁失败） |

---

## 当前树实况（FACT）

| 项 / Item | 值 / Value | 证据 / Evidence |
|-----------|------------|-----------------|
| CPP vendor pin | `87c0920ad80e2f57ffbbb12545d633058d851c4c` | submodule |
| 捆绑插件 | flutter-webrtc **0.11.7** | `pubspec.yaml` |
| 桌面 libwebrtc | 仍为预编译 DLL（尚无本轮 punch 二进制） | `third_party/libwebrtc/lib/win64/` |
| 冻结 webrtc SHA | `m125_release` @ `db3ba7af86dd6d48174ed35387d11c0794f1a21b` | 见 rebuild playbook |
| 冻结 libwebrtc tag | `125.6422.08` | 见 rebuild playbook |
| cricket 草稿补丁 | `patches/in-stack-punch/external/webrtc-m125-symmetric-punch.patch` | `SymmetricPunchToRemotes` |
| MethodChannel 脚手架 | `patches/0011-in-stack-methodchannel-scaffold.patch` | `rebuild_pending` 桩 + `preferInStackPunch` |

---

## Phase 2 进度（A）

| 步骤 | 状态 |
|------|------|
| 锁定 A + 延后 B/C 文档 | **完成** |
| Windows 重建 playbook + SHA 冻结 | **完成** |
| cricket `SymmetricPunchToRemotes` 外部补丁草稿 | **完成**（待 Windows `git apply` + 链接） |
| MethodChannel / Dart 脚手架（无 DLL） | **完成** — `0011` 桩返回 `rebuild_pending` |
| 新 DLL + 真实 C API 接线 | **进行中** — Aorus sibling；产物后按 `aorus-artifact-sync.md` 同步 → `0012+` |

---

## 选项详情（保留供对照）

### 选项 A — 留在 m125 / 125.6422（ABI 对齐重建）— **已选定**

**形态：** `webrtc-sdk/webrtc@m125_release`（冻结 SHA 见上）+ `libwebrtc` `125.6422.08`，加 PortAllocator SymmetricPunch，重建 Windows `libwebrtc.dll`。

| | |
|--|--|
| **优点** | ABI / 0.11.7 扰动最小；可关门禁 |
| **缺点** | 线较旧；须另寻 CPP HW/GPU 历史差分（首轮可先 stock+punch） |
| **包装** | 主要换 DLL + 薄胶水 |

### 选项 B / C — **延后**

正式栈内 vs 栈外产品选择之后再评估 m144/m150 bump 或上游贡献路径。

### 选项 D — 仅栈外

不满足合入门禁；试用继续走 #14，但不替代 A。

---

## 选定之后的代理下一步

1. Aorus 按 [`in-stack-m125-windows-rebuild.md`](./handoff/in-stack-m125-windows-rebuild.md) 出 DLL。  
2. 按 [`aorus-artifact-sync.md`](../patches/in-stack-punch/aorus-artifact-sync.md) 同步产物 → 根 `0012+`（真实接线；`0011` 脚手架已落地）。  
3. 标注 `0.1.0-alpha.in-stack+<tip>`；NAT 矩阵（栈外关 / 栈内开）。  
4. **仍不** merge → `main`。
