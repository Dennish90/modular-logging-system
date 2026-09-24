# Decision Log

## Decision 001 – Use pipe-separated structured log lines

### Status

Active.

### Context

The logger and analyzer need a shared log format that is easy to generate, read manually and parse in the analyzer.

### Options considered

- Plain text log messages
- Pipe-separated structured text
- JSON Lines

### Decision

Use one pipe-separated structured log entry per line:

    timestamp | level | category | message

### Reasoning

Plain text logs are easy to write, but they are harder to filter reliably. JSON Lines would be more flexible and closer to many real-world structured logging formats, but it would also introduce more parsing and dependency complexity.

Pipe-separated structured text provides a reasonable middle ground for this prototype. It is structured enough to support filtering and search, but simple enough to implement within the project timeframe.

### Consequences

The format is less flexible than JSON and requires clear rules for separator handling. For the initial prototype, the analyzer splits each log line on the first three separator characters. Any remaining separator characters are treated as part of the message field.

### Reflection

This choice prioritizes implementation simplicity and analyzer compatibility over maximum flexibility.

---

## Decision 002 – Add convenience methods for common log levels

### Status

Partially superseded by Decision 003.

The convenience methods are still active, but the original enum-based design has been replaced by string-based log levels.

### Context

The logger originally supported log levels through a `LogLevel` enum. However, requiring users to write `Write(LogLevel::Info, "...")` for every common log message made the API slightly verbose.

### Decision

Add convenience methods for the standard log levels:

- `Trace(message)`
- `Debug(message)`
- `Info(message)`
- `Warning(message)`
- `Error(message)`
- `Critical(message)`

The generic `Write(...)` method remains available for more flexible logging.

### Reasoning

This keeps common logging simple while still allowing more flexible logging through the generic `Write(...)` method.

Convenience methods make the logger easier to use in normal cases and reduce repeated boilerplate in application code.

### Consequences

The logger API becomes easier to use for common cases.

After Decision 003, the convenience methods write standard string-based log levels internally, while `Write(...)` allows custom log level strings.

### Reflection

The idea of convenience methods remained useful even after the enum-based design was removed.

---

## Decision 003 – Use string-based log levels

### Status

Active.

This replaces the enum-based log level design from earlier decisions.

### Context

The initial logger design used an enum for log levels. This provided type safety, but made it harder for users to define custom log levels without changing the logger source code.

The project goal is to keep the logger simple, reusable and flexible for small applications and prototypes.

### Options considered

- Keep enum-based log levels
- Add more enum values for all supported levels
- Use string-based log levels

### Decision

Use string-based log levels.

The generic `Write()` function accepts a string as the level parameter.

Standard log levels are still provided through helper methods such as:

- `Trace(message)`
- `Debug(message)`
- `Info(message)`
- `Warning(message)`
- `Error(message)`
- `Critical(message)`

### Reasoning

Using a string parameter for `Write()` allows users to define custom log levels without modifying the logger source code.

The helper methods keep the common log levels easy to use, while the generic `Write()` method provides flexibility.

### Consequences

Accepting any string as a log level makes the logger more flexible, but it also removes some type safety. If the user writes a log level manually, spelling mistakes will not be caught by the compiler.

This risk is reduced by providing helper functions for the standard log levels. Users who need custom log levels should define them as string constants and reuse those constants when calling `Write()`.

### Reflection

This decision favors flexibility and simple extensibility over compile-time validation.

---

## Decision 004 – Keep date and time in a single timestamp column

### Status

Active.

### Context

The analyzer displays each parsed log entry in a table. The logger writes timestamps using the format:

    YYYY-MM-DD HH:MM:SS.mmm

The analyzer needs to support filtering by date and time, but the timestamp is still one logical value in the log format.

### Options considered

- Split the timestamp into separate date and time columns
- Keep one timestamp column and parse date/time internally
- Store hidden date and time columns only for filtering

### Decision

Keep date and time together in a single `Timestamp` column.

The analyzer extracts date and time from the timestamp internally when applying filters.

### Reasoning

Keeping a single timestamp column makes the table easier to read and keeps the UI closer to the actual log format.

Separating date and time into different visible columns could make filtering simpler internally, but it would also make the table more cluttered and less representative of the original log entry.

Parsing date and time internally keeps the UI simple while still allowing more advanced filtering.

### Consequences

The analyzer needs helper functions to extract date and time from the timestamp string.

The timestamp format must remain consistent for filtering to work correctly.

### Reflection

This decision separates presentation from filtering logic. The user sees one timestamp value, while the analyzer can still filter by date and time internally.

---

## Decision 005 – Use QTableWidget for the MVP analyzer

### Status

Active for the MVP.

May be reconsidered in a future version.

### Context

The analyzer needs to display parsed log entries in a table and support basic filtering and searching.

Qt provides several possible ways to display table data, including `QTableWidget` and `QTableView` with a custom model.

### Options considered

- `QTableWidget`
- `QTableView` with a custom model
- Plain text display with manual formatting

### Decision

Use `QTableWidget` for the MVP analyzer.

### Reasoning

`QTableWidget` is simple to set up and works well for the current project scope. It allows rows and columns to be added directly and makes it easy to get the first working version of the analyzer running.

A custom model with `QTableView` would likely be more scalable and better suited for very large log files, but it would also add more complexity early in the project.

### Consequences

The current implementation is easy to understand and sufficient for the MVP.

For very large log files, performance may become worse than a model-based solution. A future version may replace `QTableWidget` with `QTableView` and a custom model if larger log files become a priority.

### Reflection

This decision prioritizes implementation speed and MVP stability over maximum scalability.

---

## Decision 006 – Combine filters using AND logic

### Status

Active.

### Context

The analyzer supports multiple filters:

- Log level filter
- Text search
- Date filter
- Time filter

These filters need to work together in a predictable way.

### Options considered

- Combine filters using AND logic
- Combine filters using OR logic
- Let the user choose how filters should be combined

### Decision

Combine all active filters using AND logic.

A row is shown only if it matches all active filters.

### Reasoning

AND logic is the most expected behavior for this kind of filtering interface. If a user selects a date range, a time range, a log level and a search term, they usually expect the table to show entries matching all of those conditions.

OR logic would make the result harder to understand because rows could appear even if they only match one of several active filters.

Letting the user choose between AND and OR could be useful in a more advanced analyzer, but it is unnecessary for the current scope.

### Consequences

The filtering behavior is predictable and easy to explain.

The filter implementation can stay relatively simple because each filter function returns whether a row matches that specific condition, and the final result combines them using AND logic.

### Reflection

This decision keeps the analyzer behavior simple and consistent while still allowing useful combinations of filters.