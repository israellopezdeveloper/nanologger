# Maintainer: Israel López <israel.lopez.developer@gmail.com>

pkgname=nanologger
pkgver=1.0.0
pkgrel=1
pkgdesc="A portable logging library for C projects"
arch=('x86_64')
url="https://github.com/israellopezdeveloper/nanologger"
license=('MIT')
depends=()
source=()
md5sums=()
options=('strip' 'staticlibs')

build() {
  cd "$srcdir"/..
  make all
}

package() {
  cd "$srcdir"/..
  make DESTDIR="$pkgdir" PREFIX="/usr" install
}
