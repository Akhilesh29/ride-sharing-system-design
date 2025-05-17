@echo off
echo Compiling the Ride Sharing System...

:: Create bin directory if it doesn't exist
if not exist "bin" mkdir bin

:: Compile all source files
g++ -std=c++17 -I./src ^
    src/main.cpp ^
    src/RideManager.cpp ^
    src/models/Location.cpp ^
    src/models/User.cpp ^
    src/models/Trip.cpp ^
    -o bin/ride_sharing.exe

if %ERRORLEVEL% EQU 0 (
    echo Compilation successful! Running the program...
    echo.
    bin\ride_sharing.exe
) else (
    echo Compilation failed!
) 