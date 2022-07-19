#include <files.h>
#include <report.h>

EFI_FILE_HANDLE GetRoot(EFI_HANDLE Image) {
    EFI_LOADED_IMAGE *LoadedImage = NULL;
    EFI_GUID LipGuid = EFI_LOADED_IMAGE_PROTOCOL_GUID;
    EFI_FILE_HANDLE Root;

    uefi_call_wrapper(BS->HandleProtocol, 3, Image, &LipGuid, (void**) &LoadedImage);

    return LibOpenRoot(LoadedImage->DeviceHandle);
}

UINT64 FileSize(EFI_FILE_HANDLE FileHandle) {
    UINT64 Size;
    EFI_FILE_INFO       *FileInfo;
    FileInfo = LibFileInfo(FileHandle);
    
    if (FileInfo == NULL) {
        uefi_call_wrapper(FileHandle->Close, 1, FileHandle);
        return Report(EFI_NOT_FOUND, L"FileInfo Error");
    }

    Size = FileInfo->FileSize;
    FreePool(FileInfo);
    return Size;
}

EFI_STATUS LoadFile(IN EFI_FILE_HANDLE Root, IN CHAR16 *FileName, OUT UINT8 **FileData, OUT UINT64 *FileLength) {
    EFI_FILE_HANDLE File;
    EFI_STATUS Status;
    UINT64 ReadSize;
    UINT8 *Buffer;

    Status = uefi_call_wrapper(Root->Open, 5, Root, &File, FileName, 
            EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY | EFI_FILE_HIDDEN | EFI_FILE_SYSTEM);

    if (EFI_ERROR(Status)) {
        return Status;
    }

    ReadSize = FileSize(File);
    Buffer = AllocatePool(ReadSize);

    if (Buffer == NULL) {
        uefi_call_wrapper(File->Close, 1, File);
        return Report(EFI_OUT_OF_RESOURCES, L"AllocatePool");
    }

    Status = uefi_call_wrapper(File->Read, 3, File, &ReadSize, Buffer);
    uefi_call_wrapper(File->Close, 1, File);

    if (EFI_ERROR(Status)) {
        FreePool(Buffer);
        return Report(Status, L"Read Error");
    }

    *(FileData) = Buffer;
    *(FileLength) = ReadSize;
    return EFI_SUCCESS;
}
