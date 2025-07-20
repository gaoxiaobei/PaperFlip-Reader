@echo off
echo Building PaperFlip-Reader Windows Installer...
echo.

REM Check if NSIS is installed
where makensis >nul 2>nul
if %errorlevel% neq 0 (
    echo NSIS (Nullsoft Scriptable Install System) is not installed.
    echo Please install NSIS from: https://nsis.sourceforge.io/Download
    echo Then run this script again.
    echo.
    echo Alternatively, you can use the portable version:
    echo PaperFlip-Reader-Portable-v0.1.0.zip
    pause
    exit /b 1
)

REM Build the installer
echo Building installer with NSIS...
makensis PaperFlip-Reader-Installer.nsi

if %errorlevel% neq 0 (
    echo Error building installer!
    pause
    exit /b 1
)

echo.
echo Installer built successfully!
echo File: PaperFlip-Reader-Setup.exe
echo.
pause