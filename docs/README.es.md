# Biblioteca Logger

Una biblioteca de logging portátil para proyectos en C.

## Características

- Diferentes niveles de logging controlados por la macro `DEBUG`.
- Fácil de integrar en otros proyectos.
- Proporciona bibliotecas estáticas y compartidas.
- Compatible con `pkg-config` para facilitar su uso.
- Ofrece paquetes de instalación para Arch Linux, Ubuntu/Debian y Fedora.

## Instalación

### Construir y Instalar

```bash
make
sudo make install
```

Por defecto, la biblioteca se instala en `/usr/local`. Para instalarla en una ruta personalizada:

```bash
sudo make install PREFIX=/ruta/personalizada
```

### Desinstalar

```bash
sudo make uninstall
```

## Uso

Incluye el encabezado en tus archivos fuente:

```c
#include <logger.h>
```

Compila tu programa utilizando `pkg-config`:

```bash
gcc mi_programa.c $(pkg-config --cflags --libs logger) -o mi_programa
```

## Niveles de Depuración

Puedes controlar el nivel de logging definiendo la macro `DEBUG` antes de incluir `logger.h` o al compilar:

```c
#define DEBUG 3
#include <logger.h>
```

O al compilar:

```bash
gcc mi_programa.c -DDEBUG=3 $(pkg-config --cflags --libs logger) -o mi_programa
```

## Generación de Paquetes de Instalación

Puedes generar paquetes para diferentes distribuciones utilizando el `Makefile`.

### Arch Linux

Generar el paquete:

```bash
make package-arch
```

Instalar el paquete:

```bash
sudo pacman -U logger-1.0.0-1-x86_64.pkg.tar.zst
```

### Debian/Ubuntu

Generar el paquete:

```bash
make package-deb
```

Instalar el paquete:

```bash
sudo dpkg -i logger_1.0.0-1_amd64.deb
```

### Fedora

Generar el paquete:

```bash
make package-rpm
```

Instalar el paquete:

```bash
sudo rpm -i logger-1.0.0-1.x86_64.rpm
```

## Usando la Biblioteca Logger en Proyectos con Autotools

Si estás utilizando **Autotools** (`autoconf`, `automake` y `libtool`) en tu proyecto, puedes integrar la biblioteca logger siguiendo estos pasos:

### Paso 1: Asegurar Soporte de `pkg-config`

Asegúrate de que `pkg-config` esté instalado en tu sistema y que las macros `pkg.m4` estén disponibles.

### Paso 2: Modificar `configure.ac`

En tu archivo `configure.ac`, añade las siguientes líneas para comprobar la biblioteca logger:

```m4
PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES([LOGGER], [logger],
                  [],
                  [AC_MSG_ERROR([Biblioteca logger no encontrada. Por favor, instala la biblioteca logger.])])
AC_SUBST([LOGGER_CFLAGS])
AC_SUBST([LOGGER_LIBS])
```

### Paso 3: Modificar `Makefile.am`

En tu `Makefile.am`, utiliza las variables detectadas por `pkg-config`:

```makefile
mi_programa_CFLAGS = @LOGGER_CFLAGS@
mi_programa_LDADD = @LOGGER_LIBS@
```

### Paso 4: Regenerar el Sistema de Construcción

```bash
autoreconf -fi
./configure
make
```

## Licencia

[Tu licencia elegida]
