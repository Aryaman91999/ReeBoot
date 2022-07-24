LD = ld
CC = gcc

LDFLAGS = $(GNUEFI)/x86_64/gnuefi/crt0-efi-x86_64.o -nostdlib -shared -Bsymbolic -L$(GNUEFI)/x86_64/gnuefi/ -L$(GNUEFI)/x86_64/lib/ -lefi -lgnuefi -T$(GNUEFI)/gnuefi/elf_x86_64_efi.lds
GNU_INC = -I$(GNUEFI)/inc/ -I$(GNUEFI)/inc/x86_64 -I$(GNUEFI)/inc/protocol
CFLAGS = -fno-stack-protector -fpic -fshort-wchar -mno-red-zone $(GNU_INC) -DEFI_FUNCTION_WRAPPER -I../include

OBJS = $(addprefix Build/, main.o data.o $(addprefix common/, files.o fs.o utils.o config.o))

BUILDIR = Build

IMG_FILE = $(BUILDIR)/ReeBoot.img
EFI_FILE = $(BUILDIR)/ReeBoot.efi
ISO_DIR = $(BUILDIR)/iso
ISO_FILE = $(BUILDIR)/ReeBoot.iso


Build/%.o: %.c
	@$(MAKE) -C $(GNUEFI)
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
	echo "Hello!" > $(BUILDIR)/REEBOOT.CFG
	mcopy -i $(IMG_FILE) $(BUILDIR)/REEBOOT.CFG ::/  
	mcopy -i $(IMG_FILE) $< ::/EFI/BOOT/BOOTX64.EFI
	mkdir -p $(ISO_DIR)
	cp $(IMG_FILE) $(ISO_DIR)/
	xorriso -as mkisofs -R -f -e ReeBoot.img -no-emul-boot -o $@ $(ISO_DIR)

clean:
	rm -rf $(BUILDIR)
	rm -rf common/

test: $(EFI_FILE)
	dd if=/dev/zero of=$(IMG_FILE) bs=1k count=1440
	mformat -i $(IMG_FILE) -f 1440 ::
	mmd -i $(IMG_FILE) ::/EFI
	mmd -i $(IMG_FILE) ::/EFI/BOOT
	mmd -i $(IMG_FILE) ::/REEBOOT
	mkdir -p $(BUILDIR)/initrd/reeboot
	touch $(BUILDIR)/initrd/reeboot/test
	echo "Hello, World!" > $(BUILDIR)/initrd/reeboot/test
	echo "kernel=hello\nsize=99" > $(BUILDIR)/config
	tar -cf $(BUILDIR)/initrd.tar -C $(BUILDIR)/initrd/ reeboot/
	mcopy -i $(IMG_FILE) $(BUILDIR)/initrd.tar ::/REEBOOT/INITRD
	mcopy -i $(IMG_FILE) $(BUILDIR)/config ::/REEBOOT/CONFIG
	mcopy -i $(IMG_FILE) $(EFI_FILE) ::/EFI/BOOT/BOOTX64.EFI
	mkdir -p $(ISO_DIR)
	cp $(IMG_FILE) $(ISO_DIR)/
	xorriso -as mkisofs -R -f -e ReeBoot.img -no-emul-boot -o $(ISO_FILE) $(ISO_DIR)
