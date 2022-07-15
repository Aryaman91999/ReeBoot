LD = ld
CC = gcc

LDFLAGS = ../gnu-efi/x86_64/gnuefi/crt0-efi-x86_64.o -nostdlib -shared -Bsymbolic -L../gnu-efi/x86_64/gnuefi/ -L../gnu-efi/x86_64/lib/ -lefi -lgnuefi -T../gnu-efi/gnuefi/elf_x86_64_efi.lds
GNU_INC = -I../gnu-efi/inc/ -I../gnu-efi/inc/x86_64 -I../gnu-efi/inc/protocol
CFLAGS = -fno-stack-protector -fpic -fshort-wchar -mno-red-zone $(GNU_INC) -DEFI_FUNCTION_WRAPPER

OBJS = $(addprefix Build/, main.o data.o)

BUILDIR = Build

IMG_FILE = $(BUILDIR)/ReeBoot.img
EFI_FILE = $(BUILDIR)/ReeBoot.efi
ISO_DIR = $(BUILDIR)/iso
ISO_FILE = $(BUILDIR)/ReeBoot.iso

all: $(ISO_FILE)

Build/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

Build/ReeBoot.so: $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o Build/ReeBoot.so

$(EFI_FILE): Build/ReeBoot.so
	objcopy -j .text -j .sdata -j .data -j .dynamic -j .dynsym \
		-j .rel -j .rela -j .reloc --target=efi-app-x86_64 $< $@

$(ISO_FILE): $(EFI_FILE)
	dd if=/dev/zero of=$(IMG_FILE) bs=1k count=1440
	mformat -i $(IMG_FILE) -f 1440 ::
	mmd -i $(IMG_FILE) ::/EFI
	mmd -i $(IMG_FILE) ::/EFI/BOOT
	mcopy -i $(IMG_FILE) $< ::/EFI/BOOT/BOOTX64.EFI
	mkdir -p $(ISO_DIR)
	cp $(IMG_FILE) $(ISO_DIR)/
	xorriso -as mkisofs -R -f -e ReeBoot.img -no-emul-boot -o $@ $(ISO_DIR)

clean:
	rm -rf $(BUILDIR)
