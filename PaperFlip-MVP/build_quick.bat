@echo off
echo === PaperFlip Quick Build ===

REM 使用指定Qt路径
set QT_PATH=D:\Qt\6.9.1\mingw_64\bin
set PATH=%QT_PATH%;%PATH%

echo Qt路径: %QT_PATH%

REM 检查qmake
where qmake >nul 2>nul
if %errorlevel% neq 0 (
    echo qmake 未找到，请检查Qt安装路径: %QT_PATH%
    pause
    exit /b 1
)

echo 清理旧文件...
del moc_*.cpp 2>nul
del *.o 2>nul
del PaperFlip.exe 2>nul

echo 生成MOC文件...
"%QT_PATH%\moc.exe" MainWindow.h -o moc_MainWindow.cpp
"%QT_PATH%\moc.exe" ReaderWidget.h -o moc_ReaderWidget.cpp  
"%QT_PATH%\moc.exe" Views/PreviewBar.h -o moc_PreviewBar.cpp

echo 编译源文件...
g++ -std=c++17 -Wall -fPIC -I. -I"%QT_PATH%\..\include" -I"%QT_PATH%\..\include\QtCore" -I"%QT_PATH%\..\include\QtWidgets" -I"%QT_PATH%\..\include\QtGui" -c main.cpp
if %errorlevel% neq 0 pause & exit /b 1

g++ -std=c++17 -Wall -fPIC -I. -I"%QT_PATH%\..\include" -I"%QT_PATH%\..\include\QtCore" -I"%QT_PATH%\..\include\QtWidgets" -I"%QT_PATH%\..\include\QtGui" -c MainWindow.cpp
if %errorlevel% neq 0 pause & exit /b 1

g++ -std=c++17 -Wall -fPIC -I. -I"%QT_PATH%\..\include" -I"%QT_PATH%\..\include\QtCore" -I"%QT_PATH%\..\include\QtWidgets" -I"%QT_PATH%\..\include\QtGui" -c ReaderWidget.cpp
if %errorlevel% neq 0 pause & exit /b 1

g++ -std=c++17 -Wall -fPIC -I. -I"%QT_PATH%\..\include" -I"%QT_PATH%\..\include\QtCore" -I"%QT_PATH%\..\include\QtWidgets" -I"%QT_PATH%\..\include\QtGui" -c EPUBManager.cpp
if %errorlevel% neq 0 pause & exit /b 1

g++ -std=c++17 -Wall -fPIC -I. -I"%QT_PATH%\..\include" -I"%QT_PATH%\..\include\QtCore" -I"%QT_PATH%\..\include\QtWidgets" -I"%QT_PATH%\..\include\QtGui" -c Views/PreviewBar.cpp
if %errorlevel% neq 0 pause & exit /b 1

g++ -std=c++17 -Wall -fPIC -I. -I"%QT_PATH%\..\include" -I"%QT_PATH%\..\include\QtCore" -I"%QT_PATH%\..\include\QtWidgets" -I"%QT_PATH%\..\include\QtGui" -c moc_MainWindow.cpp
if %errorlevel% neq 0 pause & exit /b 1

g++ -std=c++17 -Wall -fPIC -I. -I"%QT_PATH%\..\include" -I"%QT_PATH%\..\include\QtCore" -I"%QT_PATH%\..\include\QtWidgets" -I"%QT_PATH%\..\include\QtGui" -c moc_ReaderWidget.cpp
if %errorlevel% neq 0 pause & exit /b 1

g++ -std=c++17 -Wall -fPIC -I. -I"%QT_PATH%\..\include" -I"%QT_PATH%\..\include\QtCore" -I"%QT_PATH%\..\include\QtWidgets" -I"%QT_PATH%\..\include\QtGui" -c moc_PreviewBar.cpp
if %errorlevel% neq 0 pause & exit /b 1

echo 链接...
g++ *.o -o PaperFlip.exe -L"%QT_PATH%\..\lib" -lQt6Core -lQt6Widgets -lQt6Gui -lmingw32 -mwindows
if %errorlevel% neq 0 (
    echo 链接失败，尝试Qt5...
    g++ *.o -o PaperFlip.exe -L"%QT_PATH%\..\lib" -lQt5Core -lQt5Widgets -lQt5Gui -lmingw32 -mwindows
)

if exist PaperFlip.exe (
    echo === 构建成功! ===
    echo 文件大小:
    dir PaperFlip.exe
    echo.
    echo 启动应用...
    start PaperFlip.exe
) else (
    echo 构建失败，请检查错误信息
)

pause