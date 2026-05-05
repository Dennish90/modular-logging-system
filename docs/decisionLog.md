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