@echo off
echo Building PaperFlip with MinGW...

REM Check if Qt is in PATH or specify manually
set QT_PATH=D:\Qt\6.9.1\mingw_64
set PATH=%QT_PATH%\bin;%PATH%

REM Check for required tools
where g++ >nul 2>nul
if %errorlevel% neq 0 (
    echo g++ not found in PATH
    echo Please install MinGW or use MSYS2
    pause
    exit /b 1
)

where moc >nul 2>nul
if %errorlevel% neq 0 (
    echo Qt tools not found in PATH
    echo Please add Qt bin directory to PATH
    pause
    exit /b 1
)

echo Generating MOC files...
moc MainWindow.h -o moc_MainWindow.cpp
moc ReaderWidget.h -o moc_ReaderWidget.cpp
moc Views/PreviewBar.h -o moc_PreviewBar.cpp

echo Compiling...
g++ -std=c++17 -Wall -fPIC -I. -I%QT_PATH%/include -I%QT_PATH%/include/QtCore -I%QT_PATH%/include/QtWidgets -I%QT_PATH%/include/QtGui -c main.cpp
if %errorlevel% neq 0 pause & exit /b 1

g++ -std=c++17 -Wall -fPIC -I. -I%QT_PATH%/include -I%QT_PATH%/include/QtCore -I%QT_PATH%/include/QtWidgets -I%QT_PATH%/include/QtGui -c MainWindow.cpp
if %errorlevel% neq 0 pause & exit /b 1

g++ -std=c++17 -Wall -fPIC -I. -I%QT_PATH%/include -I%QT_PATH%/include/QtCore -I%QT_PATH%/include/QtWidgets -I%QT_PATH%/include/QtGui -c ReaderWidget.cpp
if %errorlevel% neq 0 pause & exit /b 1

g++ -std=c++17 -Wall -fPIC -I. -I%QT_PATH%/include -I%QT_PATH%/include/QtCore -I%QT_PATH%/include/QtWidgets -I%QT_PATH%/include/QtGui -c EPUBManager.cpp
if %errorlevel% neq 0 pause & exit /b 1

g++ -std=c++17 -Wall -fPIC -I. -I%QT_PATH%/include -I%QT_PATH%/include/QtCore -I%QT_PATH%/include/QtWidgets -I%QT_PATH%/include/QtGui -c Views/PreviewBar.cpp
if %errorlevel% neq 0 pause & exit /b 1

g++ -std=c++17 -Wall -fPIC -I. -I%QT_PATH%/include -I%QT_PATH%/include/QtCore -I%QT_PATH%/include/QtWidgets -I%QT_PATH%/include/QtGui -c moc_MainWindow.cpp
if %errorlevel% neq 0 pause & exit /b 1

g++ -std=c++17 -Wall -fPIC -I. -I%QT_PATH%/include -I%QT_PATH%/include/QtCore -I%QT_PATH%/include/QtWidgets -I%QT_PATH%/include/QtGui -c moc_ReaderWidget.cpp
if %errorlevel% neq 0 pause & exit /b 1

g++ -std=c++17 -Wall -fPIC -I. -I%QT_PATH%/include -I%QT_PATH%/include/QtCore -I%QT_PATH%/include/QtWidgets -I%QT_PATH%/include/QtGui -c moc_PreviewBar.cpp
if %errorlevel% neq 0 pause & exit /b 1

echo Linking...
g++ *.o -o PaperFlip.exe -L%QT_PATH%/lib -lQt5Core -lQt5Widgets -lQt5Gui -lmingw32 -mwindows

if %errorlevel% neq 0 (
    echo Build failed!
    pause
    exit /b 1
)

echo Build completed successfully!
del *.o
pause