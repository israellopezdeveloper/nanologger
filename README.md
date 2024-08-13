# Nanologger

Nanologger is a minimalistic logger for C/C++ designed to have a minimal impact on your codebase while providing detailed information about what is being executed, when, and in which thread. It enables thorough tracking of the program's flow with minimal overhead.

## Features
- **Macro-based**: Nanologger utilizes macros to integrate seamlessly into your code, minimizing performance impact.
- **Detailed Logging**: Track critical information, errors, warnings, and general logs with precise timestamps.
- **Thread Tracking**: Log which thread is executing at any given time, enabling detailed thread management.

## Installation

To use Nanologger in your project, follow these steps:

1. **Import as a Git Submodule**: Add Nanologger to your project by importing it as a submodule.
   ```bash
   git submodule add <repository-url> path/to/nanologger
   ```
   
2. **Include Path**: Add the path to Nanologger in your project's include directories during compilation.
   ```bash
   -Ipath/to/nanologger
   ```

3. **Configuration**: Create a `config.h` file in your project directory with the following content:
   ```c
   #define DEBUG 2
   #include "logger.h"
   ```
   Adjust the `DEBUG` level as needed:
   - `0`: Logs only CRITICAL messages.
   - `1`: Logs CRITICAL and ERROR messages.
   - `2`: Logs CRITICAL, ERROR, and WARN messages.
   - `3`: Logs CRITICAL, ERROR, WARN, and LOG messages.
   
   If `DEBUG` is not defined, no logs will be generated.

## Usage

### Basic Logging
Nanologger supports different logging levels, each corresponding to a specific severity:
- `CRITICAL`: For critical issues that require immediate attention.
- `ERROR`: For errors that need to be addressed.
- `WARN`: For warnings that may indicate potential issues.
- `LOG`: For general log messages.

### Special Cases
Nanologger provides special log macros for marking the start and end of code sections:
- `LOG_INIT`: Marks the beginning of a code section, logging the timestamp.
- `LOG_END`: Marks the end of a code section, also logging the timestamp.

### Example
Here is a simple example of how to use Nanologger in your code:
```c
#include "config.h"

int main() {
    LOG_INIT("Starting main function");

    CRITICAL("This is a critical message");
    ERROR("This is an error message");
    WARN("This is a warning message");
    LOG("This is a general log message");

    LOG_END("Ending main function");
    return 0;
}
```

All logging functions operate similarly to the standard C `printf` function, allowing formatted output.

## License

Nanologger is licensed under the MIT License. See the `LICENSE` file for more details.
