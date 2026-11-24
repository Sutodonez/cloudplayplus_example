# CloudPlayPlus 增强功能 — 交接包

**Updated:** 2026-11-24 Asia/Shanghai  
**Status:** 本 Project 内 CPP 增强开发**取消**；工作迁至用户新建 Project。  
**Repo:** https://github.com/Sutodonez/cloudplayplus_example  

**跨 Project：** Context / Agent Store 内链无效。请用本目录 [README.md](./README.md)（portable handoff）及下方 sibling 文件；GitHub blob/raw URL 见 README 顶部。  
**Legacy note:** 原 Project store 链接跨 Project 不可用。

## 1. 未合并 PR（请在新 Project 继续审阅 / 合入）

| 功能 | PR | 分支 |
|------|-----|------|
| 增强打洞 + 软 ICE | https://github.com/Sutodonez/cloudplayplus_example/pull/1 | `cursor/feat-enhanced-hole-punch-cc1d` |
| 文件传输 | https://github.com/Sutodonez/cloudplayplus_example/pull/2 | `cursor/feat-file-transfer-c757` |
| VHID 相对鼠标 | https://github.com/Sutodonez/cloudplayplus_example/pull/3 | `cursor/vhid-relative-mouse-5758` |

## 2. 决策与约束（必须保留）

1. **打洞为最高优先级**；无足够替代时可改 CPP / flutter-webrtc 核心。  
2. 改动须**可重放到未来 CPP 版本**（patch series / 有界 fork / cherry-pick / rebase playbook）。  
3. 插件优先（能力相当时）；打洞可放在 vendored 传输栈。  
4. GameViewer 公开产品 = **网易 UU 远程**（`uuyc.163.com`），非腾讯。  
5. 迁功能用思路/阶梯设计，**禁止**抄 NetEase 二进制或反编译体。

## 3. 本目录文档（portable pack）

| 文档 | 用途 |
|------|------|
| [README.md](./README.md) | 跨 Project portable 主交接 |
| [cpp-migration-plan.md](./cpp-migration-plan.md) | 三轨计划 |
| [cloudplayplus-vs-gameviewer.md](./cloudplayplus-vs-gameviewer.md) | 功能对比 + 迁移排序 |
| [gameviewer-public-features.md](./gameviewer-public-features.md) | 官网/社区公开功能 |
| [cpp-punch-replay.md](./cpp-punch-replay.md) | 打洞重放/rebase 手册 |
| [gameviewer-tech-notes-plain.md](./gameviewer-tech-notes-plain.md) | 打洞/相对鼠标白话说明 |
| [internal-cpp-punch-pr-report.md](./internal-cpp-punch-pr-report.md) | 打洞交付笔记 |
| [internal-file-transfer-implementation.md](./internal-file-transfer-implementation.md) | 文件传输交付笔记 |
| [internal-vhid-relative-mouse-pr.md](./internal-vhid-relative-mouse-pr.md) | VHID 交付笔记 |

`gameviewer-analysis.md`（深层 RE）未纳入本 portable pack；仍仅在 REA Project store。

## 4. GUI 挂载（已实现于各 PR）

- **打洞：** 全局 `settings_screen` →「NAT 穿透 / 打洞」`enablePunch` / `forceRelay`  
- **文件：** 远控浮动菜单文件夹图标 → `FileTransferSheet`；主机自动收至 `Downloads/CloudPlayPlusTransfers`  
- **VHID：** 被控「键鼠设置」→「虚拟 HID 相对鼠标」`useVhidMouse`（缺驱动则回退 SendInput）

## 5. 已知缺口

- 打洞：无 PortAllocator 内嵌；移动端原生 channel 未接；无自动 forceRelay 重启；Flutter 测试未在 CI 代理环境跑通  
- 文件：Web 不支持；大文件 sha 默认 ≤4MiB；与 UU「断点续传」对等 **UNKNOWN**  
- VHID：WinUHid 驱动/DLL 未捆绑；绝对鼠标仍 SendInput；HS 曾因 fork 403 改为 path 树 + patch

## 6. 原 worker（仅作历史引用，不可跨 Project 转交）

- hole punch: `bc-f905d2bc-2536-5b35-8f7e-aa4c106ccc1d`  
- file transfer: `bc-7eae223a-7dba-5a5e-beff-dc6c0413c757`  
- vhid mouse: `bc-074142da-dee3-5605-b0b2-451abaa35758`

## 7. Subagent / worker 能否转交？

**不能。** Cursor 的 cloud worker / typed subagent 绑定当前 Project 与会话，**无法**迁到另一个 Project。新 Project 应：复制或引用本交接文档与 PR 链接，**新建** worker 继续审阅/合入/改 GUI。PR 与 GitHub 分支与 Project 无关，可直接在新 Project 使用。
