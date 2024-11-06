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
  make DESTDIR="$pkgdir" install
}
