#ifndef FILES_H
#define FILES_H

#include <efi.h>
#include <efilib.h>
#include <stdint.h>

/* Get root volume of the EFI image */
EFI_FILE_HANDLE GetRoot(EFI_HANDLE Image);

/* Get size of file */
UINT64 FileSize(EFI_FILE_HANDLE FileHandle);

/* Load file from given root */
EFI_STATUS LoadFile(IN EFI_FILE_HANDLE Root, IN CHAR16 *FileName, OUT UINT8 **FileData, OUT UINT64 *FileLength);
#endif //FILES_H
