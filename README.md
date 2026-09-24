# Modular Logging System

A small C++ logging system with a demo application and a Qt-based log analyzer.

The project consists of three parts:

- `logger` - reusable C++ logging module
- `demoApp` - example application that generates log files
- `logAnalyzer` - Qt desktop application for viewing, searching and filtering logs

---

## Features

- Structured log format
- Log levels
- Categories
- Timestamped log entries
- Demo log generation
- GUI-based log analyzer
- Level filtering
- Text search
- Date and time filtering

---

## Requirements

This project is currently built and tested on Windows.

Required tools:

* CMake 3.20 or newer
* A C++20 compatible compiler
* Git
* Qt 6 with the Widgets module, required for the log analyzer

During initial development, the following versions were used:

* CMake 3.31.2
* Qt 6.11.1
* MinGW / g++ through the Qt toolchain

## Installing dependencies on Windows

### CMake

CMake can be installed from the official CMake website or through Windows Package Manager.

Using winget:

```
winget install -e --id Kitware.CMake
```

After installation, verify that CMake is available:

```
cmake --version
```

### Qt

The log analyzer is built with Qt Widgets.

Install Qt 6 using the Qt online installer and make sure to include a MinGW toolchain.

During development, this project used:

```
C:\Qt\6.11.1\mingw_64
```

and the Qt MinGW compiler from:

```
C:\Qt\Tools\mingw1310_64\bin
```

## Building the project

From the project root, configure the project with CMake.

Example using the Qt MinGW toolchain:

```
cmake -S . -B build -G "MinGW Makefiles" ^
  -DCMAKE_CXX_COMPILER="C:\Qt\Tools\mingw1310_64\bin\g++.exe" ^
  -DCMAKE_MAKE_PROGRAM="C:\Qt\Tools\mingw1310_64\bin\mingw32-make.exe" ^
  -DCMAKE_PREFIX_PATH="C:\Qt\6.11.1\mingw_64"
```

Then build:

```
cmake --build build
```

## Running the demo application

After building, run the demo application:

```
.\build\demoApp\demoApp.exe
```

The demo application creates a log file named:

```
demoLog.txt
```

The file is created in the current working directory when the program is run.

To find the generated log file:

```
Get-ChildItem -Recurse demoLog.txt
```

## Running the log analyzer during development

Before running the analyzer, make sure the Qt runtime DLLs are available in PATH:

```
$env:PATH = "C:\Qt\6.11.1\mingw_64\bin;$env:PATH"
```

Then run:

```
.\build\logAnalyzer\logAnalyzer.exe
```
