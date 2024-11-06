# Maintainer: Israel López <israel.lopez.developer@gmail.com>

pkgname=nanologger
pkgver=1.0.0
pkgrel=1
pkgdesc="A portable logging library for C projects"
arch=('x86_64')
url="https://github.com/israellopezdeveloper/nanologger"
license=('MIT') # Cambia a tu licencia si es diferente
depends=()
source=()
md5sums=()

build() {
  cd "$srcdir"/..
  make
}

package() {
  cd "$srcdir"/..
  make DESTDIR="$pkgdir" PREFIX=/usr install
  install -Dm755 lib/libnanologger.a "$pkgdir/usr/lib/libnanologger.a"
  install -Dm755 lib/libnanologger.so "$pkgdir/usr/lib/libnanologger.so"
  install -Dm644 include/nanologger.h "$pkgdir/usr/include/nanologger.h"
  install -Dm644 pkgconfig/nanologger.pc "$pkgdir/usr/lib/pkgconfig/nanologger.pc"
  # Instalar las páginas man
  install -d "$pkgdir/usr/share/man/man3"
  install -Dm644 man/man3/*.3 "$pkgdir/usr/share/man/man3"
  install -d "$pkgdir/usr/share/man/man3.es"
  install -Dm644 man/man3.es/*.3 "$pkgdir/usr/share/man/man3.es"
  install -d "$pkgdir/usr/share/man/man3.zh"
  install -Dm644 man/man3.zh/*.3 "$pkgdir/usr/share/man/man3.zh"
}
