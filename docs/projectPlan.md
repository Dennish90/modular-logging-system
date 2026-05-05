# Project Plan – Modular Logging System with Analyzer

## Purpose
Describe why the project exists and what problem it solves.

## Goal
The goal is to build a demonstrable prototype consisting of:
- a modular C++ logging system
- a demo application that generates logs
- a graphical analyzer that can open and inspect generated log files

## MVP
The minimum viable version must include:
- log levels
- timestamps
- categories/module names
- writing logs to file
- a demo application
- an analyzer that can open a log file
- text search
- filtering by log level

## Nice-to-have
- category filtering
- sorting
- warning/error statistics
- color-coded rows
- export of filtered logs

## Limitations
The project will not include:
- distributed logging
- network-based log collection
- database storage
- advanced monitoring
- full production-grade tooling

## Technical Choices

Initial technical direction:

- Language: C++
- C++ standard: C++20
- Build system: CMake
- GUI framework: Qt
- Testing framework: To be decided during logger implementation
- Version control and planning: Git, GitHub Issues, GitHub Projects and milestones

The logger core will be implemented as a reusable C++ component. The demo application will use the logger to generate structured log files. The analyzer will be implemented as a simple desktop GUI application that can open and inspect generated log files.

The initial log format will use one structured log entry per line:

timestamp | level | category | message

Example:

2026-04-29T10:42:15.123Z | INFO | Network | Connected to server

This format was chosen because it is easy to generate, easy to inspect manually and simple enough to parse in the analyzer.

## 8-Week Roadmap

### Week 1 – Planning & Setup
Planning, MVP, scope, repository structure, technical decisions.

### Week 2 – Logger Core
Basic logger implementation with levels, timestamps, categories and file writing.

### Week 3 – Logger Robustness
Configuration, filtering, error handling, tests and architectural cleanup.

### Week 4 – Demo Application
Small demo program that uses the logger and generates realistic log files.

### Week 5 – Analyzer GUI Basics
Create GUI application that can open and display log files.

### Week 6 – Search & Filtering
Add text search, level filtering and possibly category filtering/sorting.

### Week 7 – Integration & Polish
Connect the whole flow, test, fix bugs, improve usability and documentation.

### Week 8 – Report & Presentation
Finalize report, prepare presentation and demo.

## Risks
- GUI framework takes longer than expected
- Log format changes too late
- Too much time spent on nice-to-have features
- Integration between logger and analyzer is delayed

## Definition of Done
The project is done when:
- the demo app can generate a log file
- the analyzer can open and inspect that log file
- MVP features are implemented
- the code is documented enough to understand
- the final report explains design choices, limitations and future improvements