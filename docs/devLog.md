# Sprint Retrospective – Week 1 & 2

## Context

Week 1 and Week 2 became partially merged due to Valborg and the long weekend. Some of the initial planning and setup work from Week 1 was completed at the beginning of Week 2.

Even though Sprint 1 was not completed within the originally planned calendar week, the remaining Sprint 1 work and the full Sprint 2 logger core work were completed early during Week 2.

---

## What went well

The project started with a clear focus on planning before implementation. Instead of beginning directly with code, the first work focused on defining the project scope, MVP, limitations, technical direction and a rough 8-week roadmap.

A GitHub Projects board was created with milestones, issues and labels to support sprint-based planning. Rough issues were created for all 8 weeks, while the current sprint tasks were kept more detailed.

The repository structure was set up early with separate folders for the logger component, demo application, analyzer, tests and documentation. This made the project easier to understand and gave the implementation a clearer direction.

Several important technical decisions were documented early, including the initial log format, the use of CMake, the separation between logger, demo application and analyzer, and the decision to keep the logger as a reusable component.

The logger core progressed faster than expected during Week 2. Basic file logging, log levels, timestamps with millisecond precision, categories and convenience methods for common log levels were implemented within a short period of focused work.

---

## What did not go as planned

Sprint 1 was not completed during the originally planned week. The Valborg period and long weekend reduced the available working time, which caused some planning and setup tasks to move into Week 2.

This created some initial stress because the project appeared to be behind schedule at the start of Week 2.

There was also some early uncertainty around the exact API design for the logger, especially regarding log levels, categories and how much responsibility the logger itself should have during initialization.

---

## Adjustments made

The first two sprints were treated as a combined startup phase. Sprint 1 planning tasks were completed first, and then Sprint 2 logger core tasks were started immediately afterward.

The GitHub board and milestone structure made it easier to see what was actually left to do and helped reduce the feeling of being behind.

The logger API was adjusted during implementation as the design became clearer. Convenience methods such as `Info`, `Warning` and `Error` were added to make the logger easier to use, while the generic `Write` method remained available for more flexible logging.

---

## Reflections

The planning work at the beginning of the project felt valuable. Having a written project plan, rough roadmap and issue structure made it easier to start implementation without losing track of the overall goal.

The project is now ahead of the original schedule, despite Sprint 1 being delayed. This is useful because the middle of the project may contain more uncertainty, especially when the graphical analyzer work begins.

One important lesson from the first two weeks is that delays in a sprint do not necessarily mean the project is in trouble, as long as the work is tracked clearly and the plan is adjusted realistically.

Another reflection is that documenting decisions while they are being made is useful. It makes it easier to explain technical choices later and should help when writing the final report.

---

## Action points for next sprint

- Continue documenting technical decisions as they are made.
- Keep the MVP scope stable and avoid adding too many extra features.
- Start Week 3 by reviewing the logger core and improving robustness.
- Add documentation comments to the public logger API.
- Begin thinking about tests for the logger before the analyzer work starts.

---
---

## Toolchain note – Qt and MinGW

During setup of the Qt-based log analyzer, the project initially had build issues when using the MSYS2 MinGW compiler together with the Qt installation.

The issue was resolved by using the MinGW toolchain installed with Qt:

    C:\Qt\Tools\mingw1310_64

This toolchain matches the installed Qt MinGW build and avoids compiler/runtime mismatch problems.

The project should therefore be configured with:

    cmake -S . -B build -G "MinGW Makefiles" ^
      -DCMAKE_CXX_COMPILER="C:\Qt\Tools\mingw1310_64\bin\g++.exe" ^
      -DCMAKE_MAKE_PROGRAM="C:\Qt\Tools\mingw1310_64\bin\mingw32-make.exe" ^
      -DCMAKE_PREFIX_PATH="C:\Qt\6.11.1\mingw_64" ^
      -DCMAKE_EXPORT_COMPILE_COMMANDS=ON