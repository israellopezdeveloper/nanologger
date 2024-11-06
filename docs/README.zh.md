# 日志库（Logger Library）

一个用于 C 项目的可移植日志库。

## 特性

- 通过 `DEBUG` 宏控制不同的日志级别。
- 易于集成到其他项目中。
- 提供静态和共享库。
- 兼容 `pkg-config`，便于使用。
- 提供适用于 Arch Linux、Ubuntu/Debian 和 Fedora 的安装包。

## 安装

### 构建和安装

```bash
make
sudo make install
```

默认情况下，库安装在 `/usr/local`。要安装到自定义路径：

```bash
sudo make install PREFIX=/自定义/路径
```

### 卸载

```bash
sudo make uninstall
```

## 使用

在你的源文件中包含头文件：

```c
#include <logger.h>
```

使用 `pkg-config` 编译你的程序：

```bash
gcc my_program.c $(pkg-config --cflags --libs logger) -o my_program
```

## 调试级别

你可以在包含 `logger.h` 之前定义 `DEBUG` 宏，或者在编译时设置，以控制日志级别：

```c
#define DEBUG 3
#include <logger.h>
```

或者在编译时：

```bash
gcc my_program.c -DDEBUG=3 $(pkg-config --cflags --libs logger) -o my_program
```

## 生成安装包

你可以使用 `Makefile` 为不同的发行版生成安装包。

### Arch Linux

生成包：

```bash
make package-arch
```

安装包：

```bash
sudo pacman -U logger-1.0.0-1-x86_64.pkg.tar.zst
```

### Debian/Ubuntu

生成包：

```bash
make package-deb
```

安装包：

```bash
sudo dpkg -i logger_1.0.0-1_amd64.deb
```

### Fedora

生成包：

```bash
make package-rpm
```

安装包：

```bash
sudo rpm -i logger-1.0.0-1.x86_64.rpm
```

## 在使用 Autotools 的项目中使用 Logger 库

如果你的项目使用 **Autotools**（`autoconf`、`automake` 和 `libtool`），可以按照以下步骤集成日志库：

### 第一步：确保支持 `pkg-config`

确保你的系统已安装 `pkg-config`，并且 `pkg.m4` 宏可用。

### 第二步：修改 `configure.ac`

在你的 `configure.ac` 文件中，添加以下行以检查日志库：

```m4
PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES([LOGGER], [logger],
                  [],
                  [AC_MSG_ERROR([未找到日志库。请安装日志库。])])
AC_SUBST([LOGGER_CFLAGS])
AC_SUBST([LOGGER_LIBS])
```

### 第三步：修改 `Makefile.am`

在你的 `Makefile.am` 中，使用 `pkg-config` 检测到的变量：

```makefile
my_program_CFLAGS = @LOGGER_CFLAGS@
my_program_LDADD = @LOGGER_LIBS@
```

### 第四步：重新生成构建系统

```bash
autoreconf -fi
./configure
make
```

## 许可证

[你选择的许可证]

