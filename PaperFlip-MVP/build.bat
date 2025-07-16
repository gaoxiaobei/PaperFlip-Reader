@echo off
echo Building PaperFlip MVP...

if not exist "build" mkdir build
cd build

if exist "CMakeCache.txt" del CMakeCache.txt

cmake -G "MinGW Makefiles" ..
if %errorlevel% neq 0 (
    echo CMake configuration failed
    pause
    exit /b 1
)

cmake --build .
if %errorlevel% neq 0 (
    echo Build failed
    pause
    exit /b 1
)

echo Build completed successfully!
pause
cd ..