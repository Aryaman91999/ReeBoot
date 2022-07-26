#include <efi.h>
#include <efilib.h>
#include <files.h>
#include <fs.h>
#include <report.h>
#include <config.h>

int efi_main(EFI_HANDLE Image, EFI_SYSTEM_TABLE *SystemTable) {
    InitializeLib(Image, SystemTable);
    UINT64 Size, ConfigSize;
    UINT8 *Content;
    unsigned char *Config;
    EFI_STATUS Status;
    unsigned char *Val;
    CHAR16 *KernelPath;

    Status = LoadFile(GetRoot(Image), L"REEBOOT\\INITRD", &Content, &Size);
    if (EFI_ERROR(Status)) {
        return Report(Status, L"Unable to open initrd");
    }
    
    Status = LoadFile(GetRoot(Image), L"REEBOOT\\CONFIG", &Config, &ConfigSize);
    if (EFI_ERROR(Status)) {
        return Report(Status, L"Unable to open config");
    }
    
    UINT64 ValSize = GetValue(Config, ConfigSize, "kernel", &Val);

    KernelPath = AllocatePool(sizeof(CHAR16) * (ValSize+1));
    KernelPath[ValSize] = (CHAR16)'\0';
    for (int i = 0; i < ValSize; i++) {
        if (Val[i] == '/') {
            KernelPath[i] = (CHAR16)'\\';
        } else {
            KernelPath[i] = Val[i];
        }
    }

    Print(KernelPath);

    UINT8 *test;
    UINT64 TestSize = InitrdLoadFile(Content, "reeboot/test", &test);
    if (0 > TestSize) {
        return -1;
    }
    
    while (1);
    return EFI_SUCCESS;
}
