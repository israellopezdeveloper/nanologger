# Logger Library

A portable logging library for C projects.

## Features

- Different logging levels controlled by the `DEBUG` macro.
- Easy to integrate into other projects.
- Provides static and shared libraries.
- Compatible with `pkg-config` to facilitate usage.
- Offers installation packages for Arch Linux, Ubuntu/Debian, and Fedora.

## Installation

### Build and Install

```bash
make
sudo make install
```

By default, the library is installed in `/usr/local`. To install it in a custom path:

```bash
sudo make install PREFIX=/custom/path
```

### Uninstall

```bash
sudo make uninstall
```

## Usage

Include the header in your source files:

```c
#include <logger.h>
```

Compile your program using `pkg-config`:

```bash
gcc my_program.c $(pkg-config --cflags --libs logger) -o my_program
```

## Debug Levels

You can control the logging level by defining the `DEBUG` macro before including `logger.h` or at compile time:

```c
#define DEBUG 3
#include <logger.h>
```

Or at compile time:

```bash
gcc my_program.c -DDEBUG=3 $(pkg-config --cflags --libs logger) -o my_program
```

## Generating Installation Packages

You can generate installation packages for different distributions using the `Makefile`.

### Arch Linux

Generate the package:

```bash
make package-arch
```

Install the package:

```bash
sudo pacman -U logger-1.0.0-1-x86_64.pkg.tar.zst
```

### Debian/Ubuntu

Generate the package:

```bash
make package-deb
```

Install the package:

```bash
sudo dpkg -i logger_1.0.0-1_amd64.deb
```

### Fedora

Generate the package:

```bash
make package-rpm
```

Install the package:

```bash
sudo rpm -i logger-1.0.0-1.x86_64.rpm
```

## Using the Logger Library in Projects with Autotools

If you are using **Autotools** (`autoconf`, `automake`, and `libtool`) in your project, you can integrate the logger library by following these steps:

### Step 1: Ensure `pkg-config` Support

Make sure that `pkg-config` is installed on your system and that the `pkg.m4` macros are available.

### Step 2: Modify `configure.ac`

In your `configure.ac` file, add the following lines to check for the logger library:

```m4
PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES([LOGGER], [logger],
                  [],
                  [AC_MSG_ERROR([Logger library not found. Please install the logger library.])])
AC_SUBST([LOGGER_CFLAGS])
AC_SUBST([LOGGER_LIBS])
```

### Step 3: Modify `Makefile.am`

In your `Makefile.am`, use the variables detected by `pkg-config`:

```makefile
my_program_CFLAGS = @LOGGER_CFLAGS@
my_program_LDADD = @LOGGER_LIBS@
```

### Step 4: Regenerate the Build System

```bash
autoreconf -fi
./configure
make
```

## License

[Your chosen license]

