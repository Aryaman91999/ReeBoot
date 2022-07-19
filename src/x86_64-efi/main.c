#include <efi.h>
#include <efilib.h>
#include <files.h>

int efi_main(EFI_HANDLE Image, EFI_SYSTEM_TABLE *SystemTable) {
    InitializeLib(Image, SystemTable);
    UINT64 Size;
    UINT8 *Content;
    
    LoadFile(GetRoot(Image), L"REEBOOT.CFG", &Content, &Size);
    
    for (int i = 0; i < Size; i++) {
        Print(L"%c", (CHAR16)Content[i]);
    }

    FreePool(Content);
    while(1);
    return EFI_SUCCESS;
}
