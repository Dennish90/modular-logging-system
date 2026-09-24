## Requirements

This project is currently built and tested on Windows using:

- CMake 3.20 or newer
- GCC / g++ with C++20 support
- Ninja or MinGW Makefiles
- Git

During initial development, the following versions were used:

- CMake 3.31.2
- g++ 15.2.0 from MSYS2

## Installing dependencies on Windows

### CMake

CMake can be installed from the official CMake website or through Windows Package Manager.

Using winget:

    winget install -e --id Kitware.CMake

After installation, verify that CMake is available:

    cmake --version

### GCC / g++ through MSYS2

Install MSYS2 from the official MSYS2 website.

After installation, open the MSYS2 UCRT64 terminal and install the GCC toolchain:

    pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain

Verify that g++ is available:

    g++ --version

If `g++` is not available from PowerShell, make sure the MSYS2 UCRT64 `bin` directory is added to the Windows PATH.

Example path:

    C:\msys64\ucrt64\bin

## Building the project

From the project root:

    cmake -S . -B build -G "Ninja"
    cmake --build build

Alternative using MinGW Makefiles:

    cmake -S . -B build -G "MinGW Makefiles"
    cmake --build build

## Running the demo application

After building, run the demo application.

With Ninja or MinGW, the executable is usually located at:

    .\build\demoApp\demoApp.exe

If the executable is not found, search for it:

    Get-ChildItem -Recurse demoApp.exe

The demo application should create a log file named:

    demoLog.txt

The file is created in the current working directory when the program is run.

To find the generated log file:

    Get-ChildItem -Recurse demoLog.txt

## Running the log analyzer during development

$env:PATH = "C:\Qt\6.11.1\mingw_64\bin;$env:PATH"
.\build\logAnalyzer\logAnalyzer.exe