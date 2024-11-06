# Biblioteca Nanologger

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
#include <nanologger.h>
```

Compila tu programa utilizando `pkg-config`:

```bash
gcc mi_programa.c $(pkg-config --cflags --libs nanologger) -o mi_programa
```

## Niveles de Depuración

Puedes controlar el nivel de logging definiendo la macro `DEBUG` antes de incluir `nanologger.h` o al compilar:

```c
#define DEBUG 3
#include <nanologger.h>
```

O al compilar:

```bash
gcc mi_programa.c -DDEBUG=3 $(pkg-config --cflags --libs nanologger) -o mi_programa
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
sudo pacman -U nanologger-1.0.0-1-x86_64.pkg.tar.zst
```

### Debian/Ubuntu

Generar el paquete:

```bash
make package-deb
```

Instalar el paquete:

```bash
sudo dpkg -i nanologger_1.0.0-1_amd64.deb
```

### Fedora

Generar el paquete:

```bash
make package-rpm
```

Instalar el paquete:

```bash
sudo rpm -i nanologger-1.0.0-1.x86_64.rpm
```

## Usando la Biblioteca nanologger en Proyectos con Autotools

Si estás utilizando **Autotools** (`autoconf`, `automake` y `libtool`) en tu proyecto, puedes integrar la biblioteca nanologger siguiendo estos pasos:

### Paso 1: Asegurar Soporte de `pkg-config`

Asegúrate de que `pkg-config` esté instalado en tu sistema y que las macros `pkg.m4` estén disponibles.

### Paso 2: Modificar `configure.ac`

En tu archivo `configure.ac`, añade las siguientes líneas para comprobar la biblioteca nanologger:

```m4
PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES([NANOLOGGER], [nanologger],
                  [],
                  [AC_MSG_ERROR([Biblioteca nanologger no encontrada. Por favor, instala la biblioteca nanologger.])])
AC_SUBST([NANOLOGGER_CFLAGS])
AC_SUBST([NANOLOGGER_LIBS])
```

### Paso 3: Modificar `Makefile.am`

En tu `Makefile.am`, utiliza las variables detectadas por `pkg-config`:

```makefile
mi_programa_CFLAGS = @NANOLOGGER_CFLAGS@
mi_programa_LDADD = @NANOLOGGER_LIBS@
```

### Paso 4: Regenerar el Sistema de Construcción

```bash
autoreconf -fi
./configure
make
```

## Licencia

[Tu licencia elegida]
