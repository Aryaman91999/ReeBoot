#ifndef CONFIG_H
#define CONFIG_H

#include <efi.h>
#include <efilib.h>

UINT64 GetValue(IN unsigned char *Config, IN UINT64 ConfigSize, 
        IN const char *Key, OUT unsigned char **Value);

#endif //CONFIG_H
