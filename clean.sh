#!/bin/sh
set -e
. ./config.sh
 
for PROJECT in $PROJECTS; do
  $MAKE -C $PROJECT clean
done
 
rm -rfv sysroot
rm -rfv serial.log
rm -rfv isodir
rm -rfv Syn.iso
