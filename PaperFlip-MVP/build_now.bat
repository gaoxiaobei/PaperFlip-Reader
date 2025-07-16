@echo off
echo Building PaperFlip...

REM 设置Qt路径
set QT_BIN=D:\Qt\6.9.1\mingw_64\bin
set QT_INC=D:\Qt\6.9.1\mingw_64\include
set QT_LIB=D:\Qt\6.9.1\mingw_64\lib

REM 检查编译器
"%QT_BIN%\g++" --version >nul 2>&1
if %errorlevel% neq 0 (
    echo Error: Qt MinGW compiler not found
    pause
    exit /b 1
)

echo Qt compiler found

rem Clean old files
del *.exe 2>nul
del moc_*.cpp 2>nul
del *.o 2>nul

rem Generate MOC
"%QT_BIN%\moc.exe" MainWindow.h -o moc_MainWindow.cpp
"%QT_BIN%\moc.exe" ReaderWidget.h -o moc_ReaderWidget.cpp
"%QT_BIN%\moc.exe" Views/PreviewBar.h -o moc_PreviewBar.cpp

rem Compile
"%QT_BIN%\g++.exe" -std=c++17 -Wall -fPIC -I. -I"%QT_INC%" -I"%QT_INC%\QtCore" -I"%QT_INC%\QtWidgets" -I"%QT_INC%\QtGui" -c main.cpp
"%QT_BIN%\g++.exe" -std=c++17 -Wall -fPIC -I. -I"%QT_INC%" -I"%QT_INC%\QtCore" -I"%QT_INC%\QtWidgets" -I"%QT_INC%\QtGui" -c MainWindow.cpp
"%QT_BIN%\g++.exe" -std=c++17 -Wall -fPIC -I. -I"%QT_INC%" -I"%QT_INC%\QtCore" -I"%QT_INC%\QtWidgets" -I"%QT_INC%\QtGui" -c ReaderWidget.cpp
"%QT_BIN%\g++.exe" -std=c++17 -Wall -fPIC -I. -I"%QT_INC%" -I"%QT_INC%\QtCore" -I"%QT_INC%\QtWidgets" -I"%QT_INC%\QtGui" -c EPUBManager.cpp
"%QT_BIN%\g++.exe" -std=c++17 -Wall -fPIC -I. -I"%QT_INC%" -I"%QT_INC%"\QtCore" -I"%QT_INC%"\QtWidgets" -I"%QT_INC%"\QtGui" -c Views/PreviewBar.cpp
"%QT_BIN%\g++.exe" -std=c++17 -Wall -fPIC -I. -I"%QT_INC%" -I"%QT_INC%\QtCore" -I"%QT_INC%\QtWidgets" -I"%QT_INC%\QtGui" -c moc_MainWindow.cpp
"%QT_BIN%\g++.exe" -std=c++17 -Wall -fPIC -I. -I"%QT_INC%" -I"%QT_INC%\QtCore" -I"%QT_INC%\QtWidgets" -I"%QT_INC%"\QtGui" -c moc_ReaderWidget.cpp
"%QT_BIN%\g++.exe" -std=c++17 -Wall -fPIC -I. -I"%QT_INC%" -I"%QT_INC%\QtCore" -I"%QT_INC%\QtWidgets" -I"%QT_INC%\QtGui" -c moc_PreviewBar.cpp

rem Link
"%QT_BIN%\g++.exe" *.o -o PaperFlip.exe -L"%QT_LIB%" -lQt6Core -lQt6Widgets -lQt6Gui -lmingw32 -mwindows

echo Build done!
PaperFlip.exe
pause