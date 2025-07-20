# PaperFlip-Reader Installation Guide

## Windows Installation

### Method 1: Installer (Recommended)
1. Download `PaperFlip-Reader-Setup.exe`
2. Double-click the installer file
3. Follow the installation wizard:
   - Accept the license agreement
   - Choose installation directory (default: `C:\Program Files\PaperFlip-Reader`)
   - Select components to install
   - Click "Install" to begin installation
4. Launch PaperFlip-Reader from:
   - Start Menu → PaperFlip-Reader
   - Desktop shortcut (if selected during installation)

### Method 2: Portable Version
1. Download `PaperFlip-Reader-Portable.zip`
2. Extract to any folder (e.g., USB drive, local folder)
3. Run `PaperFlip-Reader.exe` directly
4. No installation required - all settings are stored locally

## First Run Setup
1. **Initial Library Setup**: Choose your eBooks folder
2. **Theme Selection**: Choose between light and dark themes
3. **Font Preferences**: Adjust default font size and family
4. **Language**: Select your preferred language

## Troubleshooting

### Common Issues

#### "MSVCP140.dll missing" error
- Install Microsoft Visual C++ Redistributable (included in installer)
- Download from: https://aka.ms/vs/17/release/vc_redist.x64.exe

#### "Application failed to start" error
- Ensure all files are extracted completely
- Check Windows Defender/antivirus hasn't quarantined files
- Run as administrator if needed

#### EPUB files won't open
- Ensure files have `.epub` extension
- Check if files are not corrupted
- Try with different EPUB files to isolate issue

### Performance Tips
- **Large Libraries**: Organize books into folders for better performance
- **Memory Usage**: Close other applications when reading large books
- **Graphics**: Update graphics drivers for better rendering

## Uninstallation

### Standard Installation
1. Windows Settings → Apps → Apps & features
2. Find "PaperFlip-Reader"
3. Click "Uninstall"
4. Follow the uninstall wizard

### Portable Version
Simply delete the folder containing PaperFlip-Reader files.

## File Locations

### Windows (Standard Installation)
- **Application**: `C:\Program Files\PaperFlip-Reader\`
- **Settings**: `%APPDATA%\PaperFlip-Reader\`
- **Library Database**: `%APPDATA%\PaperFlip-Reader\library.db`
- **Cache**: `%LOCALAPPDATA%\PaperFlip-Reader\cache\`

### Portable Version
- **Application**: Extracted folder location
- **Settings**: Same folder as executable
- **Library Database**: Same folder as executable

## Support
For additional help:
- Check [RELEASE_NOTES.md](RELEASE_NOTES.md) for known issues
- Visit our [GitHub Issues](https://github.com/PaperFlip-Reader/PaperFlip-Reader/issues)
- Review the main [README.md](../README.md) for detailed documentation