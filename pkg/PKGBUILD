# Maintainer: aixxe <me@aixxe.net>
_pkgname=aimtux
pkgname=aimtux-git
pkgver=v1.0.r703.g9e7c759
pkgrel=1
pkgdesc="Open source internal multi-hack for Counter-Strike: Global Offensive"
arch=("x86_64")
url="https://github.com/AimTuxOfficial/AimTux"
license=("GPL3")
depends=("gdb" "sudo" "procps-ng")
makedepends=("git" "cmake" "make" "gcc" "sdl2")
install="${_pkgname}.install"
source=("${_pkgname}::git+${url}.git" "git://github.com/AimTuxOfficial/imgui.git" "aimtux-load" "aimtux-uload")
sha256sums=('SKIP'
            'SKIP'
            '5ac2581c29337a1a56bbef703d674ac359652d13ecd50975a63256b4d47d322c'
            'd9eb70f4a48ca3d8ab77dcac4fcbbe3044f37f00bed6251408320da4384d45f2')

pkgver() {
	cd "${_pkgname}"
	git describe --long --tags | sed "s/-/.r/;s/-/./g"
}

build() {
	cd "${_pkgname}"

	git submodule init
	git config submodule.ImGUI.url "${_pkgname}/src/ImgGUI"
	git submodule update	

	cmake .
	make
}

package() {
	install -Dm755 aimtux-load "$pkgdir"/usr/bin/aimtux-load
	install -Dm755 aimtux-uload "$pkgdir"/usr/bin/aimtux-uload
	
	cd "${_pkgname}"
	make DESTDIR="$pkgdir/"
	install -Dm755 libAimTux.so "$pkgdir"/usr/lib/libAimTux.so
}
