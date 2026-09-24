# Decision Log

## Decision 001 – Use pipe-separated structured log lines

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
The format is less flexible than JSON and requires clear rules for separator handling. For the initial prototype, the analyzer will split each log line on the first three separator characters. Any remaining separator characters are treated as part of the message field.

### Reflection
This choice prioritizes implementation simplicity and analyzer compatibility over maximum flexibility.

### Context **Status:** Superseded by Decision 003.
The logger supports log levels through a `LogLevel` enum. However, requiring users to write `Write(LogLevel::Info, "...")` for every common log message makes the API slightly verbose.

---

### Decision - 002 – Add convenience methods for common log levels
**Status:** Partially superseded by Decision 003.

The logger provides convenience methods for the three(Will expand) default log levels:

- `Info(message)`
- `Warning(message)`
- `Error(message)`

The generic `Write(LogLevel level, message)` method remains available for flexibility.

### Reasoning
This keeps common logging simple while still allowing the logger to support additional log levels in the future.

### Consequences
The logger API becomes easier to use for common cases, while custom or extended log levels still require the more explicit `Write(...)` method.

---

### Decision 003 - Use string-based log levels
**Status:** Active. Replaces the enum-based log level design from earlier decisions.

The logger will no longer use an enum for log levels. Instead, the generic `Write()` function will accept a string as the level parameter.

### Reasoning
The logger provides helper functions for the most common log levels, such as `Info(message)`, `Warning(message)` and `Error(message)`. This makes common logging quick and convenient.

Using a string parameter for `Write()` also allows users to define their own custom log levels without modifying the logger source code.

### Consequences
Accepting any string as a log level makes the logger more flexible, but it also removes some type safety. If the user writes a log level manually, spelling mistakes will not be caught by the compiler.

This risk is reduced by providing helper functions for the standard log levels. Users who need custom log levels should define them as string constants and reuse those constants when calling `Write()`.