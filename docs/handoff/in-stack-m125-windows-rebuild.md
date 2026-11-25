# Windows rebuild playbook — Option A (m125 / 125.6422)

**状态：** 人工已选定 **选项 A**（2026-11-25）。B/C 依赖升级延后到正式「栈内 vs 栈外」产品选择之后。  
**目标产物：** `plugins/flutter-webrtc/third_party/libwebrtc/lib/win64/libwebrtc.dll`（+ `.lib`），内含栈内 `SymmetricPunchToRemotes`。  
**版本配对（有二进制后）：** `0.1.0-alpha.in-stack+<CPPS-tip-sha>`  
**不要**把结果合进 `main`，直到门禁与产品验证完成。

---

## 冻结 pin（选定当时）

| 组件 | 冻结值 | 说明 |
|------|--------|------|
| 路线 | **A** | 对齐 flutter-webrtc **0.11.7** / m125 |
| CPP vendor | `87c0920ad80e2f57ffbbb12545d633058d851c4c` | 不变 |
| `webrtc-sdk/webrtc` | 分支 `m125_release` @ **`db3ba7af86dd6d48174ed35387d11c0794f1a21b`**（2025-07-25） | 重建前再 `git fetch` 核对；若 tip 漂移，以本表 SHA 为准或人工改冻结 |
| `webrtc-sdk/libwebrtc` | 标签 **`125.6422.08`** @ `1d159832b7c6…` | 与 Android `125.6422.03` / CHANGELOG m125 同线 |
| 栈内 cricket 草稿补丁 | `patches/in-stack-punch/external/webrtc-m125-symmetric-punch.patch` | 对上述 webrtc SHA 的 `p2p/client/basic_port_allocator.*` |
| B / C | **延后** | 不在本试用轮升级 m144/m150 或上游优先 |

**UNKNOWN（仍须在 Windows 宿主上解决）：** CloudPlayPlus 现有硬编/GPU 差分的精确补丁集（PDB 显示曾在 `G:\CloudPlayPlus\webrtc\src\…` 构建）。首轮可先做「stock m125 + punch」验证栈内 API，再叠 HW 差分。

---

## 宿主要求（Windows）

| 项 | 要求 |
|----|------|
| OS | Windows 10/11 x64 |
| IDE | Visual Studio 2022（含 C++ 桌面、Windows SDK） |
| 工具 | [depot_tools](https://commondatastorage.googleapis.com/chrome-infra-docs/flat/depot_tools/docs/html/depot_tools_tutorial.html) 在 PATH |
| 磁盘 | 建议 ≥ 50 GB 空闲（gclient sync + out） |
| 网络 | 可访问 GitHub / Google 源码镜像（按本地策略） |

本云端 Linux runner **不能**产出 `libwebrtc.dll`。仓库可见自托管 Windows 机（如 Aorus_PC），但当前会话未挂载为带 depot_tools 的重建环境 — **请在 Windows 宿主按下列步骤执行，或授权专用重建会话**。

---

## 步骤（在 Windows 宿主）

### 1. 检出 webrtc（m125）

```bat
mkdir C:\cpps-webrtc-a && cd C:\cpps-webrtc-a
:: .gclient — target_os win, url pinned to frozen SHA
```

`.gclient` 示例：

```python
solutions = [
  {
    "name": "src",
    "url": "https://github.com/webrtc-sdk/webrtc.git@db3ba7af86dd6d48174ed35387d11c0794f1a21b",
    "deps_file": "DEPS",
    "managed": False,
    "custom_deps": {},
    "custom_vars": {},
  },
]
target_os = ["win"]
```

```bat
gclient sync
cd src
git checkout db3ba7af86dd6d48174ed35387d11c0794f1a21b
```

### 2. 嵌入 libwebrtc wrapper（125.6422.08）

```bat
git clone --branch 125.6422.08 https://github.com/webrtc-sdk/libwebrtc.git libwebrtc
:: 按该 tag 的 README / patches 应用 audio 等必要补丁（若有）
:: 将 //libwebrtc 加入 src/BUILD.gn 的 group("default") deps
```

### 3. 应用 CPPS 栈内 cricket 草稿补丁

从本仓库拷贝：

`patches/in-stack-punch/external/webrtc-m125-symmetric-punch.patch`

```bat
git apply --whitespace=nowarn path\to\webrtc-m125-symmetric-punch.patch
```

### 4. GN + Ninja（Release x64）

```bat
set DEPOT_TOOLS_WIN_TOOLCHAIN=0
set GYP_MSVS_VERSION=2022
gn gen out-release/Windows-x64 --args=^
"target_os=\"win\" target_cpu=\"x64\" is_debug=false is_component_build=false is_clang=true rtc_use_h264=true ffmpeg_branding=\"Chrome\" rtc_include_tests=false rtc_build_examples=false libwebrtc_desktop_capture=true"
ninja -C out-release/Windows-x64 libwebrtc
```

（参数若与历史 CloudPlayPlus HW 构建不一致，以能链接 flutter-webrtc 0.11.7 为准微调。）

### 5. 投放二进制到 CPPS trial 分支

复制到：

```text
vendor/cloudplayplus/plugins/flutter-webrtc/third_party/libwebrtc/lib/win64/libwebrtc.dll
vendor/cloudplayplus/plugins/flutter-webrtc/third_party/libwebrtc/lib/win64/libwebrtc.dll.lib
```

然后：

1. 实现 / 应用 libwebrtc C API 胶水（见 `external/libwebrtc-punch-api-NOTES.md`）与 flutter-webrtc MethodChannel（`0011`）。  
2. 在 CPPS 记录版本：`0.1.0-alpha.in-stack+<git-rev-parse --short HEAD>`。  
3. `scripts/apply-patches.sh` + Windows Flutter 构建；NAT 矩阵时 **关闭** 栈外、**打开** 栈内。

### 6. 已知技术风险（首轮重建时验证）

`PortInterface::SendTo` 文档写明目标地址通常须已是 connection / 曾发来过包。若对陌生 `srflx`/`host` 发送失败，下一补丁改为经 `UDPPort` 底层 socket 或 `EnablePortPackets` 路径发送 — 仍保持「ICE 同源本地绑定」约束。

---

## 完成后更新

- `patches/in-stack-punch/FILE_LIST.md` — 填入真实拥有路径  
- 生成根目录 `patches/0011-….patch`（薄胶水；大二进制可另附 release 资产说明）  
- `docs/trial-in-stack-punch.md` / store `docs/trial-readiness.md`  
- **仍不要** merge #15 / #1 → `main`
