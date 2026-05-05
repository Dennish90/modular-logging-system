# Architecture Overview

## System Overview

The project consists of three main parts:

- `logger` - a reusable C++ logging component
- `demoApp` - a small application that uses the logger to generate log files
- `logAnalyzer` - a graphical application that opens and analyzes generated log files

The logger writes structured log entries to a local file. The demo application is used to demonstrate how another program can use the logger. The analyzer reads the generated log file and allows the user to inspect, search and filter the log entries.

## High-Level Data Flow

    demoApp
       |
       | uses
       v
    logger
       |
       | writes
       v
    logFile
       |
       | opened by
       v
    logAnalyzer

## Component Responsibilities

### logger

The logger component is responsible for:

- creating structured log entries
- adding timestamps
- adding log levels
- adding categories/module names
- writing log entries to file
- filtering messages based on minimum log level

The logger should not depend on the demo application or the analyzer.

### demoApp

The demo application is responsible for:

- demonstrating how the logger is used
- generating realistic log entries
- creating log files that can be opened by the analyzer

The demo application depends on the logger.

### logAnalyzer

The log analyzer is responsible for:

- opening generated log files
- parsing log entries
- displaying log entries in a graphical interface
- searching log messages
- filtering entries by log level

The analyzer reads the log file format produced by the logger, but it should not depend directly on the logger implementation.

## Dependency Direction

    demoApp ---> logger

    logger ---> logFile

    logAnalyzer ---> logFile

The analyzer should depend on the log file format, not on the logger's internal implementation. This keeps the logger and analyzer separated and makes the logging component more reusable.

## Initial Log Entry Structure

Each log entry will use the following structure:

    timestamp | level | category | message

Example:

    2026-04-29T10:42:15.123Z | INFO | Network | Connected to server

The analyzer will parse the first three separators. Any additional separator characters are treated as part of the message field.

## Initial Design Principles

- Keep the logger reusable
- Keep the log format simple and readable
- Separate log generation from log analysis
- Avoid unnecessary dependencies in the logger core
- Prefer clear structure over premature optimization