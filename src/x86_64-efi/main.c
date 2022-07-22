#include <efi.h>
#include <efilib.h>
#include <files.h>
#include <fs.h>
#include <report.h>

int efi_main(EFI_HANDLE Image, EFI_SYSTEM_TABLE *SystemTable) {
    InitializeLib(Image, SystemTable);
    UINT64 Size;
    UINT8 *Content;
    EFI_STATUS Status;

    Status = LoadFile(GetRoot(Image), L"REEBOOT\\INITRD", &Content, &Size);
    
    if (EFI_ERROR(Status)) {
        return Report(Status, L"Unable to open initrd");
    }
    
    UINT8 *test;
    UINT64 TestSize = InitrdLoadFile(Content, "reeboot/test", &test);
    if (0 > TestSize) {
        return -1;
    }

    for (int i = 0; i < TestSize; i++) {
        Print(L"%c", (CHAR16)test[i]);
    }

    while(1);
    return EFI_SUCCESS;
}
