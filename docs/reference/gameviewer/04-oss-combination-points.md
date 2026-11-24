# Candidate OSS combination points

Short match list for later reuse (not an integration plan). Pair GameViewer’s **capability shape** with OSS projects that already solve the same layer.

## 1. NAT traversal / hole punching

| GameViewer piece | What to match later | Candidate OSS |
|------------------|---------------------|---------------|
| ICE + STUN/TURN + DTLS-SRTP in `streamer.dll` | Standard WebRTC P2P | [libwebrtc](https://webrtc.googlesource.com/src), [Pion WebRTC](https://github.com/pion/webrtc), [libdatachannel](https://github.com/paullouisageneau/libdatachannel) |
| Signaling separate from media | App-level signaling | coturn (TURN), LiveKit/mediasoup (SFU if relay preferred), custom WS signaling |
| `mix_kcp` / DcKCP | Low-latency reliable UDP | [KCP](https://github.com/skywind3000/kcp), [quic-go](https://github.com/quic-go/quic-go) / msquic |
| `port_mapping_service` | Home-router assist | miniupnpc, libnatpmp |
| Gaming remote desktop overall | End-to-end reference | Sunshine + Moonlight, RustDesk, ToDesk-style stacks (compare only) |

**Combination idea:** Keep OSS ICE/TURN for connectivity; evaluate whether NetEase’s KCP/QUIC mix is worth reimplementing vs tuning WebRTC BWE + FEC.

## 2. Remote mouse / input

| GameViewer piece | What to match later | Candidate OSS |
|------------------|---------------------|---------------|
| `SendInput` soft injection | Simple desktop control | Windows APIs; Barrier/ShareMouse-style layers |
| `uuycinput` VHF HID + mouse filter | Driver-level relative mouse | Windows VHF samples; [ViGEm](https://github.com/ViGEm/ViGEmBus) (already bundled); Interception driver (license caution) |
| ViGEmBus gamepad | Virtual controller | ViGEmBus / ViGEmClient (already OSS) |
| Cursor shape capture/send | Cursor remoting | FreeRDP / RDP cursor patterns; WebRTC datachannel cursor messages |

**Combination idea:** Prefer ViGEm + documented VHF virtual mouse over proprietary filter drivers when integrating into an OSS remote stack.

## 3. Remote terminal

| GameViewer piece | What to match later | Candidate OSS |
|------------------|---------------------|---------------|
| `uuyc-mux` = psmux | Windows tmux-like mux | [psmux](https://github.com/psmux/psmux) (product already based on it) |
| ConPTY + OpenConsole | PTY host | Windows Terminal / OpenConsole / conpty |
| Server session orchestration | Remote attach over existing P2P channel | ttyd, wetty, or pipe PTY over WebRTC datachannel |

**Combination idea:** Reuse psmux + ConPTY locally; transport session I/O over the same P2P data channel chosen for desktop remoting (WebRTC datachannel or KCP).

## 4. Adjacent strong capabilities

| Capability | GameViewer hook | OSS match |
|------------|-----------------|-----------|
| Virtual display | Indirect Display Driver | Microsoft IddCx samples; Virtual Display Driver projects |
| Virtual audio | `nevaudio` | VB-Audio-like / Windows virtual cable OSS |
| Capture + encode | `streamer.dll` codecs | FFmpeg, NVENC/AMF/QuickSync via OBS/Sunshine patterns |
| Cross-platform UI bridge | WebView2 + UUYCBridge | Tauri / Wry, or CEF |

## Suggested later deep-dives (priority)

1. Recover ICE server provisioning + candidate preference from `streamer.dll` / session setup.
2. Map `gv_pb` input + terminal message schemas (protobuf recovery).
3. Confirm soft vs virtual mouse decision tree in `KeyboardMouseRunner`.
4. Trace `conpty_bridge` ↔ Server IPC framing for terminal bytes.
