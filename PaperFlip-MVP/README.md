# PaperFlip - 沉浸式PC端电子阅读器 (MVP)

一个专注于提供纸质书般沉浸式快速翻阅体验的PC端电子阅读器。

## ✨ 核心特性

- **🖱️ 沉浸式快速翻阅**: 鼠标拖拽实现流畅的页码切换
- **⚡ 平滑动画**: 60fps惯性滑动效果
- **🎯 精准着陆**: 拖拽停止后自动渲染完整内容
- **📊 实时预览**: 底部显示章节标题和页码进度
- **📖 EPUB支持**: 基础EPUB格式文件加载

## 🚀 快速开始

### 环境要求
- Qt 5.15+ 或 Qt 6.x
- C++17编译器
- MinGW 或 MSVC

### 构建方法

#### 1. 使用Qt Creator (推荐)
1. 安装Qt Creator和Qt库
2. 打开 `PaperFlip.pro`
3. 点击Run按钮

#### 2. 命令行构建 (Windows)
```bash
qmake
mingw32-make release
# 或
nmake release
```

#### 3. 使用Makefile
```bash
make
./PaperFlip
```

### 运行测试
构建完成后运行：
- Windows: `PaperFlip.exe`
- Linux/Mac: `./PaperFlip`

## 🎮 使用方法

1. **打开文件**: File → Open 或工具栏按钮
2. **快速翻阅**: 
   - 按住鼠标左键拖拽页面
   - 拖拽时底部显示预览进度条
   - 松开鼠标精准着陆到目标页
3. **基础导航**: 
   - 使用菜单中的Open功能打开EPUB文件

## 🏗️ 技术架构

- **框架**: Qt (跨平台原生性能)
- **语言**: C++17
- **界面**: Qt Widgets
- **动画**: QTimer + 手动插值

## 📁 项目结构

```
PaperFlip-MVP/
├── PaperFlip.pro          # Qt项目文件
├── CMakeLists.txt         # CMake构建文件  
├── *.cpp/*.h             # 源代码文件
├── Views/                # UI组件
├── build_simple.bat      # Windows构建脚本
└── README.md
```

## 🎯 MVP验证要点

✅ **已完成**:
- PC端Qt应用程序框架
- 基础文件打开功能
- 鼠标拖拽翻页交互
- 平滑的惯性动画效果
- 实时预览和章节显示
- 跨平台兼容性

## 🔮 后续扩展

下一阶段可添加：
- 真实EPUB内容解析
- 字体和主题设置
- 书签和笔记功能
- 全文搜索
- 更丰富的翻页动画效果
- PDF格式支持

## 🐛 已知问题

构建时如出现Qt路径问题，请调整：
- Windows: 修改build_simple.bat中的QT_PATH变量
- Linux/Mac: 确保qmake在PATH中

---

享受纸质书般的沉浸式数字阅读体验！