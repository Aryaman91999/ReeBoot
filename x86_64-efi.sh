mkdir -p src/x86_64-efi/common
cp src/*.c src/x86_64-efi/common/

make -C src/x86_64-efi GNUEFI=$(pwd)/gnu-efi $@
