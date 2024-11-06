# Variables
PREFIX ?= /usr/local
LIBDIR = $(PREFIX)/lib
INCLUDEDIR = $(PREFIX)/include
PKGCONFIGDIR = $(LIBDIR)/pkgconfig

CC = gcc
AR = ar
RANLIB = ranlib
CFLAGS = -fPIC -Wall -Wextra -O2 -g
LDFLAGS = -shared
INCLUDES = -Iinclude

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
LIB_STATIC = lib/libnanologger.a
LIB_SHARED = lib/libnanologger.so
HEADER = include/nanologger.h
PKGCONFIG = pkgconfig/nanologger.pc

# Version para los paquetes
VERSION = 1.0.0

.PHONY: all clean install uninstall package package-arch package-deb package-rpm

all: $(LIB_STATIC) $(LIB_SHARED)

$(LIB_STATIC): $(OBJ)
	@mkdir -p lib
	@$(AR) rcs $@ $(OBJ)
	@$(RANLIB) $@

$(LIB_SHARED): $(OBJ)
	@mkdir -p lib
	@$(CC) $(LDFLAGS) -o $@ $(OBJ)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

install: all
	@mkdir -p $(DESTDIR)$(LIBDIR)
	@mkdir -p $(DESTDIR)$(INCLUDEDIR)
	@mkdir -p $(DESTDIR)$(PKGCONFIGDIR)
	@install -m 0755 $(LIB_STATIC) $(DESTDIR)$(LIBDIR)
	@install -m 0755 $(LIB_SHARED) $(DESTDIR)$(LIBDIR)
	@install -m 0644 $(HEADER) $(DESTDIR)$(INCLUDEDIR)
	@install -m 0644 $(PKGCONFIG) $(DESTDIR)$(PKGCONFIGDIR)

uninstall:
	@rm -f $(DESTDIR)$(LIBDIR)/libnanologger.a
	@rm -f $(DESTDIR)$(LIBDIR)/libnanologger.so
	@rm -f $(DESTDIR)$(INCLUDEDIR)/nanologger.h
	@rm -f $(DESTDIR)$(PKGCONFIGDIR)/nanologger.pc

clean:
	@rm -f $(OBJ) $(LIB_STATIC) $(LIB_SHARED)
	@rm -rf pkg build
	@rm -rf nanologger-*.pkg.tar.zst
	@rm -rf nanologger-*.deb
	@rm -rf nanologger-*.rpm

# Objetivos para paquetes
package: package-arch package-deb package-rpm

# Paquete para Arch Linux
package-arch:
	@echo "Generando paquete para Arch Linux..."
	@mkdir -p pkg/arch
	@cp -r include src pkgconfig PKGBUILD LICENSE README.md Makefile pkg/arch/
	@(cd pkg/arch && makepkg -cf)
	@mv pkg/arch/*.pkg.tar.zst .

# Paquete para Debian/Ubuntu
package-deb:
	@echo "Generando paquete para Debian/Ubuntu..."
	@mkdir -p pkg/debian
	@cp -r include src pkgconfig debian LICENSE README.md Makefile pkg/debian/
	@(cd pkg/debian && dpkg-buildpackage -us -uc)
	@mv pkg/*.deb .

# Paquete para Fedora
package-rpm:
	@echo "Generando paquete para Fedora..."
	@mkdir -p pkg/rpm/{BUILD,RPMS,SOURCES,SPECS,SRPMS}
	@tar czf pkg/rpm/SOURCES/nanologger-1.0.0.tar.gz --exclude='./pkg/rpm/SOURCES/nanologger-1.0.0.tar.gz' --transform "s/^\./nanologger-1.0.0/" .
	@cp -r include src pkgconfig LICENSE README.md Makefile pkg/rpm/SOURCES/
	@cp nanologger.spec pkg/rpm/SPECS/
	@(cd pkg/rpm && rpmbuild --define "_topdir $(PWD)/pkg/rpm" -bb SPECS/nanologger.spec)
	@cp pkg/rpm/RPMS/*/*.rpm .


