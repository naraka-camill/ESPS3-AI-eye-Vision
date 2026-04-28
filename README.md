# DOIT AI EYE VISION - ESP32-S3 多模态AI双目开发板

![board](https://img.shields.io/badge/ESP32-S3-blue)
![license](https://img.shields.io/badge/License-MIT-green)
![platform](https://img.shields.io/badge/Platform-ESP--IDF-orange)

# 开发笔记
board代码位于 `main\boards\doit-ai-eye-vision\doit-ai-01-kit-lcd.cc`

小智AI官方 https://xiaozhi.me/xz-docs/docs/tutorial-basics/configure-wifi-and-add-devices#3%E9%87%8D%E6%96%B0%E9%85%8D%E7%BD%91

配网操作 https://mxgc9pajxfs.feishu.cn/wiki/GNahwSMntiRkppkiLtecg6dUnfd?from=from_copylink

ESP32S3双目魔眼视觉开发板编译教程V2:
https://mxgc9pajxfs.feishu.cn/wiki/DRQOwBK4CiejjlkHQ2SccD8gn9g?from=from_copylink

ESP32S3双目魔眼视觉开发板眼睛素材更换教程
https://mxgc9pajxfs.feishu.cn/wiki/FyfjwZfLzioMt2kcWkicZBMbnTe?from=from_copylink

---

## 📺 效果视频

[B站演示视频](https://www.bilibili.com/video/BV1j2TrzmEWu)

---

## 📖 项目简介

**DOIT AI EYE VISION** 是一款基于 **ESP32-S3** 的多模态AI开发板，集成了**双目1.28英寸圆形LCD屏幕**、**摄像头**和**4个触摸节点**，支持完整的**小智AI语音助手**功能。

### ✨ 核心特色

| 特性 | 说明 |
|------|------|
| 🧠 **主控** | ESP32-S3，双核Xtensa LX7 @ 240MHz，内置NPU加速 |
| 👁️ **双目屏幕** | 2× GC9A01 1.28寸圆形LCD (240×240)，支持动态表情动画 |
| 📷 **摄像头** | 支持VGA分辨率摄像头，实现多模态交互 |
| 🎤 **语音交互** | VB6824音频编解码，支持唤醒词和语音识别 |
| 🔘 **触摸节点** | 4个触摸按钮，支持单击/长按/组合操作 |
| 🌐 **无线通信** | 2.4G Wi-Fi，支持OTA远程升级 |
| 🤖 **MCP协议** | 内置MCP Server，支持AI Agent扩展 |
| 🧩 **IoT物联** | 可扩展物联网设备控制 |
| 📜 **多语言** | 支持简体中文、繁体中文、英文、日文等多语言界面 |

### 🏗️ 硬件架构

- **处理器**: ESP32-S3 (Xtensa LX7双核，512KB SRAM，外置PSRAM)
- **屏幕**: 2× GC9A01 SPI接口 1.28寸圆形LCD
- **摄像头**: 并行DVP接口摄像头 (OV2640等)
- **音频**: VB6824 音频编解码芯片（I2S接口）
- **存储**: 外置Flash (16MB) + PSRAM (8MB)
- **扩展**: 4个触摸节点

---

## 📦 硬件资料

本项目的PCB设计文件和原理图完全开源，位于 [PCB/](PCB/) 目录：

- 📄 [AI-EYE原理图](PCB/AI-EYE原理图.pdf)

---

## 🛠️ 软件开发指南

### 环境要求

- **ESP-IDF 版本**: ≥ v5.3.2
- **开发工具**: VS Code + ESP-IDF插件 或 命令行
- **目标芯片**: ESP32-S3

### 快速开始

#### 1️⃣ 获取代码

```bash
git clone https://github.com/naraka-camill/ESPS3-AI-eye-Vision.git
cd ESPS3_AI_EYE_Vision
```

#### 2️⃣ 设置目标芯片

```bash
idf.py set-target esp32s3
```

#### 3️⃣ 配置菜单 (Menuconfig)

```bash
idf.py menuconfig
```

在 **Xiaozhi Assistant → Board Type** 中选择：
```
Doit-AI-EYE-VISION
```

#### 4️⃣ 编译

```bash
idf.py build
```

#### 5️⃣ 烧录

```bash
idf.py flash
```

#### 6️⃣ 查看日志 (可选)

```bash
idf.py monitor
```

---

## 🧩 项目结构

```
ESPS3_AI_EYE_Vision/
├── main/                          # 主程序
│   ├── main.cc                    # 入口文件
│   ├── application.cc/.h          # 应用层
│   ├── mcp_server.cc/.h           # MCP协议服务器
│   ├── ota.cc/.h                  # OTA远程升级
│   ├── settings.cc/.h             # 配置管理
│   ├── system_info.cc/.h          # 系统信息
│   ├── background_task.cc/.h      # 后台任务
│   ├── boards/                    # 板级支持
│   │   └── doit-ai-eye-vision/    # ⭐ 本开发板专属代码
│   │       ├── doit-ai-01-kit-lcd.cc  # 板级初始化
│   │       └── config.h               # GPIO/LCD/摄像头引脚配置
│   ├── display/                   # 显示驱动
│   │   ├── lcd_display.cc/.h      # LCD驱动
│   │   ├── eye_display.cc/.h      # 眼球表情动画
│   │   ├── eyes_data.h            # 表情数据
│   │   └── oled_display.cc/.h     # OLED显示(备用)
│   ├── audio_codecs/              # 音频编解码
│   │   └── vb6824_audio_codec.cc/.h  # VB6824驱动
│   ├── audio_processing/          # 音频处理
│   │   ├── afe_audio_processor.cc/.h  # AFE前处理
│   │   ├── esp_wake_word.cc/.h        # 唤醒词
│   │   └── ...                         # 其他音频处理
│   ├── iot/                       # 物联网
│   │   ├── thing_manager.cc/.h    # Thing管理
│   │   └── things/                # IoT设备实现
│   ├── led/                       # LED控制
│   ├── protocols/                 # 通信协议 (MQTT/WebSocket)
│   └── assets/                    # 多语言资源
│       ├── zh-CN/                 # 简体中文
│       ├── en-US/                 # 英文
│       ├── ja-JP/                 # 日文
│       └── zh-TW/                 # 繁体中文
├── components/                    # 组件库
│   ├── 78__esp-opus-encoder/      # Opus编码器
│   ├── espressif__esp_codec_dev/  # ESP音频编解码设备
│   └── vb6824/                    # VB6824芯片驱动
├── PCB/                           # 硬件设计
│   └── AI-EYE原理图.pdf           # 原理图
├── partitions/                    # Flash分区表
├── scripts/                       # 辅助脚本
│   ├── flash.sh                   # 一键烧录脚本
│   ├── release.py                 # 发布脚本
│   └── gen_lang.py                # 语言资源生成
└── CMakeLists.txt                 # 顶层CMake
```

---

## 🔧 硬件引脚定义

详细引脚定义见 [config.h](main/boards/doit-ai-eye-vision/config.h)

### LCD 显示屏 (双目)

| 功能 | 左眼 (SPI2) | 右眼 (SPI1) |
|------|------------|------------|
| SCLK | GPIO38 | GPIO42 |
| MOSI | GPIO39 | GPIO2 |
| RST  | GPIO40 | GPIO1 |
| DC   | GPIO0  | GPIO41 |

### 摄像头

| 引脚 | GPIO |
|------|------|
| XCLK | GPIO16 |
| PCLK | GPIO8 |
| VSYNC| GPIO6 |
| HREF | GPIO7 |
| D0-D7| GPIO21,9,3,10,47,18,17,15 |
| SIOD | GPIO4 |
| SIOC | GPIO5 |

### 音频

| 功能 | GPIO |
|------|------|
| VB6824 TX | GPIO45 |
| VB6824 RX | GPIO48 |

---

## 🎯 功能操作

| 操作 | 功能 |
|------|------|
| 🗣️ **语音唤醒** | 说"你好小智"唤醒 |
| 📱 **配网** | 首次开机自动进入AP配网模式 (SSID: Xiaozhi-xxx) |
| 📱 **重新配网** | 开机后说"你好小智，开始配网"(连续说)|

---

## 🤝 致谢

- 特别感谢 **[虾哥 (78)](https://github.com/78/xiaozhi-esp32)** 的开源项目 [xiaozhi-esp32](https://github.com/78/xiaozhi-esp32)，本项目基于该优秀开源项目构建。


**Made with by naraka-camill**