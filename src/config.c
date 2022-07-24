#include <config.h>

#define CHARPTR(i, x) &(i[x])

UINT64 GetValue(IN unsigned char *Config, IN UINT64 ConfigSize,
        IN const char *Key, OUT unsigned char **Value) {
    int k = strlena(Key);


    for (int i = 0; i < ConfigSize; i++) {
        if (!CompareMem(CHARPTR(Config, i), Key, k)) {
            if (Config[i+k] != '=') {
                return -1;
            }

            i += (k + 1);

            *Value = CHARPTR(Config, i);
            int ret = 0;

            /* count characters till newline */
            while (1) {
                if (Config[i] == '\n' || i == ConfigSize) {
                    break;
                }
                i++;
                ret++;
            }

            return ret;
        }
    }
    
    /* not found */
    return -1;
}
