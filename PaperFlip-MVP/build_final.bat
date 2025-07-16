@echo off
echo === PaperFlip MVP Build ===

REM Check for Qt in common locations
set QT_PATHS[0]=C:\Qt\6.*\mingw*\bin
set QT_PATHS[1]=C:\Qt\5.*\mingw*\bin  
set QT_PATHS[2]=D:\Qt\6.9.1\mingw_64\bin
set QT_PATHS[3]=D:\Qt\5.*\mingw*\bin

set QT_FOUND=0
for %%i in (%QT_PATHS%) do (
    echo %%i
    if exist "%%~i\qmake.exe" (
        echo Found Qt at: %%~i
        set QT_PATH=%%~i
        set QT_FOUND=1
        goto :found_qt
    )
)

:found_qt
if %QT_FOUND%==0 (
    echo Qt not found in common locations.
    echo Please:
    echo 1. Install Qt from https://www.qt.io/download
    echo 2. Add Qt bin directory to PATH
    echo 3. Or edit this batch file to set QT_PATH manually
    pause
    exit /b 1
)

set PATH=%QT_PATH%;%PATH%
echo Using Qt: %QT_PATH%

echo.
echo === Building PaperFlip ===

qmake PaperFlip.pro
if exist Makefile (
    mingw32-make clean 2>nul
    mingw32-make release
    if %errorlevel%==0 (
        echo.
        echo === Build Success! ===
        dir /b PaperFlip.exe 2>nul
        if %errorlevel%==0 (
            echo.
            echo Starting PaperFlip...
            PaperFlip.exe
        ) else (
            echo Build completed but executable not found
            pause
        )
    ) else (
        echo Build failed - check compiler messages above
        pause
    )
) else (
    echo qmake failed - check Qt installation
    pause
)