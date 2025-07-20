# PaperFlip-Reader

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Qt](https://img.shields.io/badge/Qt-5.15%2B-blue.svg)](https://www.qt.io)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20macOS%20%7C%20Linux-lightgrey.svg)](https://github.com/gaoxiaobei/PaperFlip-Reader)

A modern, cross-platform EPUB reader built with Qt and C++. PaperFlip-Reader provides a clean, intuitive interface for reading EPUB files with features like pagination, bookmarks, and customizable themes.

![PaperFlip-Reader Screenshot](docs/screenshots/main-window.png)

## Features

- **📖 EPUB Support**: Full support for EPUB 2.0 and 3.0 formats
- **🎨 Modern UI**: Clean, responsive interface with customizable themes
- **📱 Cross-Platform**: Runs on Windows, macOS, and Linux
- **⚡ Fast Performance**: Optimized for large EPUB files
- **🔖 Bookmarks**: Save and manage your reading positions
- **🔍 Search**: Full-text search within books
- **📊 Reading Progress**: Track your reading progress
- **🌙 Dark Mode**: Built-in dark theme support
- **⌨️ Keyboard Shortcuts**: Efficient keyboard navigation

## Quick Start

### Prerequisites

- **CMake** 3.16 or higher
- **Qt** 5.12+ or Qt 6.x
- **C++17** compatible compiler
- **Git** (for submodules)

### Building from Source

```bash
# Clone the repository
git clone https://github.com/gaoxiaobei/PaperFlip-Reader.git
cd PaperFlip-Reader

# Initialize submodules
git submodule update --init --recursive

# Configure and build
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release

# Run
./bin/PaperFlip-Reader
```

### Windows (Visual Studio)

```cmd
# Configure for Visual Studio
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

### macOS

```bash
# Configure for Xcode
cmake .. -G Xcode
cmake --build . --config Release
```

## Installation

### Pre-built Binaries

Download the latest release for your platform from the [Releases](https://github.com/gaoxiaobei/PaperFlip-Reader/releases) page.

### Package Managers

Coming soon to:
- Windows: Chocolatey, Scoop
- macOS: Homebrew
- Linux: Snap, Flatpak, AppImage

## Development Setup

### Requirements

- **Qt Development Tools**: Qt Creator or your preferred IDE
- **CMake**: Latest stable version
- **Git**: For version control and submodules

### Setup Steps

1. **Clone and Setup**:
   ```bash
   git clone https://github.com/gaoxiaobei/PaperFlip-Reader.git
   cd PaperFlip-Reader
   git submodule update --init --recursive
   ```

2. **Configure with CMake**:
   ```bash
   mkdir build && cd build
   cmake .. -DCMAKE_BUILD_TYPE=Debug
   ```

3. **Open in Qt Creator**:
   - Launch Qt Creator
   - Open `CMakeLists.txt` as a project
   - Configure kit and build

### Development Workflow

1. **Create Feature Branch**:
   ```bash
   git checkout -b feature/your-feature-name
   ```

2. **Make Changes**:
   - Follow the coding standards (see [CONTRIBUTING.md](CONTRIBUTING.md))
   - Add tests for new functionality
   - Update documentation

3. **Test Your Changes**:
   ```bash
   mkdir build-test && cd build-test
   cmake .. -DCMAKE_BUILD_TYPE=Debug
   cmake --build . --config Debug
   ./bin/PaperFlip-Reader
   ```

4. **Submit Pull Request**:
   - Push your branch
   - Create a pull request with clear description
   - Ensure CI passes

## Project Structure

```
PaperFlip-Reader/
├── src/                    # Source code
│   ├── core/              # Core EPUB processing
│   │   ├── EPUBManager.h/cpp
│   │   └── epub_utils.h/cpp
│   ├── ui/                # User interface
│   │   ├── MainWindow.h/cpp
│   │   ├── ReaderWidget.h/cpp
│   │   └── Views/         # UI components
│   └── main.cpp           # Application entry point
├── external/              # External dependencies
│   └── quazip/           # QuaZip submodule for ZIP handling
├── resources/            # Application resources
├── docs/                 # Documentation
├── tests/                # Unit tests
├── CMakeLists.txt        # CMake build configuration
└── README.md            # This file
```

## Configuration

### Build Options

| Option | Description | Default |
|--------|-------------|---------|
| `USE_SYSTEM_QUAZIP` | Use system QuaZip instead of submodule | `OFF` |
| `CMAKE_BUILD_TYPE` | Build type (Debug/Release) | `Release` |

### Environment Variables

- `PAPERFLIP_CONFIG_DIR`: Custom configuration directory
- `PAPERFLIP_CACHE_DIR`: Custom cache directory

## Contributing

We welcome contributions! Please see [CONTRIBUTING.md](CONTRIBUTING.md) for:
- Development setup
- Coding standards
- Pull request process
- Issue reporting guidelines

## Roadmap

### Version 0.2.0 (Next)
- [ ] EPUB 3.0 enhanced support
- [ ] Text-to-speech integration
- [ ] Advanced search with regex
- [ ] Plugin system architecture

### Version 0.3.0
- [ ] Cloud sync support
- [ ] Annotations and highlights
- [ ] Dictionary integration
- [ ] Custom themes

### Future
- [ ] Mobile versions (iOS/Android)
- [ ] EPUB editing capabilities
- [ ] Audiobook support
- [ ] Social reading features

## Troubleshooting

### Common Issues

**Build fails with "QuaZip not found"**:
```bash
git submodule update --init --recursive
```

**Qt not found**:
- Ensure Qt is installed and `CMAKE_PREFIX_PATH` is set
- On Windows: `cmake .. -DCMAKE_PREFIX_PATH=C:\Qt\6.5.0\msvc2019_64`

**Missing dependencies**:
- Install development packages for your platform
- See platform-specific instructions in [docs/BUILD.md](docs/BUILD.md)

### Getting Help

Please use GitHub Issues to report bugs or request features:
- [Bug Report Template](https://github.com/gaoxiaobei/PaperFlip-Reader/issues/new?template=bug_report.md)
- [Feature Request Template](https://github.com/gaoxiaobei/PaperFlip-Reader/issues/new?template=feature_request.md)

- **Issues**: [GitHub Issues](https://github.com/gaoxiaobei/PaperFlip-Reader/issues)
- **Discussions**: [GitHub Discussions](https://github.com/gaoxiaobei/PaperFlip-Reader/discussions)
- **Documentation**: [docs/](docs/)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- **QuaZip team** for excellent ZIP archive handling
- **Qt Project** for the powerful cross-platform framework
- **EPUB Standards** for the open e-book format
- **Contributors** who help make this project better

## Changelog

See [CHANGELOG.md](CHANGELOG.md) for a detailed history of changes.

- **[Latest Release](https://github.com/gaoxiaobei/PaperFlip-Reader/releases/latest)**
- **[Development Builds](https://github.com/gaoxiaobei/PaperFlip-Reader/actions)**

---

**PaperFlip Reader** - Bringing the joy of physical book flipping to the digital age.
