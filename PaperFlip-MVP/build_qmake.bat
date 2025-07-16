@echo off
echo === 使用qmake构建PaperFlip ===

set QT_PATH=D:\Qt\6.9.1\mingw_64\bin
set PATH=%QT_PATH%;%PATH%
echo 使用Qt: %QT_PATH%

REM 使用qmake构建
echo 正在配置项目...
qmake PaperFlip.pro -spec win32-g++
if %errorlevel% neq 0 (
    echo qmake配置失败
    pause
    exit /b 1
)

echo 正在编译...
mingw32-make.exe -j4
if %errorlevel% neq 0 (
    echo make编译失败
    pause
    exit /b 1
)

echo === 构建成功! ===
echo 正在启动...
release\PaperFlip.exe
pause