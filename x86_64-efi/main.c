#include <efi.h>
#include <efilib.h>
#include <stdbool.h>
 
EFI_STATUS
EFIAPI
efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
  InitializeLib(ImageHandle, SystemTable);
  uefi_call_wrapper(SystemTable->ConOut->ClearScreen, 1, SystemTable->ConOut);
  Print(L"Hello, world!\n");
  while(true);
  return EFI_SUCCESS;
}
