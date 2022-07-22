#ifndef FS_H
#define FS_H

#include <efi.h>
#include <efilib.h>

UINT64 InitrdLoadFile(IN UINT8 *Initrd, IN const char *Filename, OUT UINT8 **FileData);

#endif //FS_H
