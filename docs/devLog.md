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

---

## 2026-05-18

### Work done
- Added initial Qt Designer UI for Anly.
- Implemented manual log file loading from a file path.
- Added Browse button using QFileDialog.
- Parsed pipe-separated log entries.
- Displayed log entries in QTableWidget.
- Added level filter buttons.
- Added text search filter.
- Updated entry count display.

### Reflection
The analyzer progressed faster than expected after the Qt build environment was stabilized. Qt Designer made it possible to build the UI layout quickly, while the C++ code focused on loading, parsing and filtering log entries.

The current analyzer uses QTableWidget, which is suitable for the MVP. For larger log files, a future version may need QTableView with a custom model for better performance.

---

## 2026-09-24

### Work done

- Continued development of the Qt-based log analyzer, now named Ally.
- Added time-based filtering using the timestamp column.
- Added support for filtering by whole seconds.
- Added date-based filtering using the same timestamp column.
- Added separate enable/disable controls for date and time filters.
- Updated the filter logic so level, search, date and time filters work together.
- Added automatic initialization of the date filter range based on the earliest and latest dates found in the loaded log file.
- Improved code documentation in the log analyzer, especially around parsing and filtering logic.
- Added Doxygen-style comments to important helper functions in `MainWindow`.
- Reviewed which comments should belong in header files and which comments should stay close to implementation details in source files.

### Reflection

The analyzer has now moved beyond the original MVP requirements. The first version only needed to load a log file, display entries, filter by level and support text search. The current version also supports date and time filtering while still keeping the timestamp as a single table column.

This design feels cleaner than splitting the timestamp into separate date and time columns. The UI presents the timestamp as one value, while the internal filter logic extracts date and time when needed. This keeps the table simple while still allowing more advanced filtering.

One challenge during this work was handling the timestamp format correctly. The log format includes milliseconds, but the UI filters by whole seconds. The solution was to parse only the `HH:MM:SS` part for time filtering and ignore milliseconds.

Another challenge was keeping the UI layout readable when adding more controls. Some Qt widgets behaved differently in the running application compared to Qt Designer, especially with the dark theme and time edit controls. For now, the focus was kept on functionality rather than perfect visual polish.

### Technical decisions

- Date and time filters use the existing `Timestamp` column instead of adding separate table columns.
- Time filtering works on whole seconds.
- Milliseconds are ignored during time filtering.
- Date filter controls are automatically initialized from the loaded log file.
- All active filters are combined using AND logic.

### Next steps

- Continue improving comments and documentation.
- Add Doxygen comments to the public logger API.
- Review the README before making the repository public.
- Prepare a portable Windows build of Ally using `windeployqt`.
- Add screenshots and possibly a short usage example to the repository.