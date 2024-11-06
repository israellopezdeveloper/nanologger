# Maintainer: Israel López <israel.lopez.developer@gmail.com>

pkgname=logger
pkgver=1.0.0
pkgrel=1
pkgdesc="Una biblioteca de logging portátil para proyectos en C"
arch=('x86_64')
url="https://github.com/israellopezdeveloper/nanologger"
license=('MIT') # Cambia a tu licencia si es diferente
depends=()
source=()
md5sums=()

build() {
  cd "$srcdir"
  make
}

package() {
  cd "$srcdir"
  make DESTDIR="$pkgdir" install
}
