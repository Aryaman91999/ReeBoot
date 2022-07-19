#include <efi.h>
#include <efilib.h>

EFI_FILE_HANDLE GetVolume(EFI_HANDLE Image);
UINT64 FileSize(EFI_FILE_HANDLE FileHandle);

int efi_main(EFI_HANDLE Image, EFI_SYSTEM_TABLE *SystemTable) {
    EFI_FILE_HANDLE RootDir, FileHandle;
    CHAR16 *FILENAME = L"REEBOOT.CFG";
    InitializeLib(Image, SystemTable);
    
    uefi_call_wrapper(SystemTable->ConOut->ClearScreen, 1, SystemTable->ConOut);

    RootDir = GetVolume(Image);
    
    uefi_call_wrapper(RootDir->Open, 5, RootDir, &FileHandle, FILENAME, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY | EFI_FILE_HIDDEN | EFI_FILE_SYSTEM);

    UINT64 ReadSize = FileSize(FileHandle);
    UINT8 *Buffer = AllocatePool(ReadSize);
    
    uefi_call_wrapper(FileHandle->Read, 3, FileHandle, &ReadSize, Buffer);
    for (int i = 0; i < ReadSize; i++) {
        Print(L"%c", (CHAR16) Buffer[i]);
    }
    while(1);
    return EFI_SUCCESS;
}

EFI_FILE_HANDLE GetVolume(EFI_HANDLE Image) {
    EFI_LOADED_IMAGE *LoadedImage = NULL;                  /* image interface */
    EFI_GUID LipGuid = EFI_LOADED_IMAGE_PROTOCOL_GUID;      /* image interface GUID */
    EFI_GUID fsGuid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID; 
    EFI_FILE_HANDLE Volume;                                 /* the volume's interface */
 
    /* get the loaded image protocol interface for our "image" */
    uefi_call_wrapper(BS->HandleProtocol, 3, Image, &LipGuid, (void **) &LoadedImage);
    return LibOpenRoot(LoadedImage->DeviceHandle);
}

UINT64 FileSize(EFI_FILE_HANDLE FileHandle) {
    UINT64 ret;
    EFI_FILE_INFO       *FileInfo;         /* file information structure */
  
    FileInfo = LibFileInfo(FileHandle);
    ret = FileInfo->FileSize;
    FreePool(FileInfo);
    return ret;
}
