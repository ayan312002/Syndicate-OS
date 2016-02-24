#!/bin/sh
set -e
. ./build.sh

 
mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub
 
cp sysroot/boot/Synos.kernel isodir/boot/Synos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "SYN-OS" {
	multiboot /boot/Synos.kernel
}
menuentry "SYN-OS Debug" {
    set debug=all
    multiboot /boot/Synos.kernel
    sleep 5
    sleep 5 
}
EOF
grub-mkrescue -o SynOS.iso isodir
