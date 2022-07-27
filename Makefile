TARGETS = $(addprefix src/, x86_64-efi)

$(TARGETS):
	$(MAKE) -C $< -DGNUEFI=$(pwd)/gnu-efi