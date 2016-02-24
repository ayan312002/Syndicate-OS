set -e
. ./iso.sh
 
qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom SynOS.iso -serial file:serial.log
