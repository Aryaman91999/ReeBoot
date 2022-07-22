#include <fs.h>
#include <utils.h>
#include <string.h>

UINT64 InitrdLoadFile(IN UINT8 *Initrd, IN const char *Filename, OUT UINT8 **FileData) {
    int k = strlena(Filename);
    UINT8 *ptr = Initrd;
    while(!CompareMem(ptr+257, "ustar", 5)) {
        int FileSize = oct2bin(ptr+0x7c, 11);
        if (!CompareMem(ptr, Filename, k+1)) {
            *FileData = ptr + 512;
            return FileSize;
        }
        ptr += (((FileSize + 511) / 512) + 1) * 512;
    }

    return -1;
}
