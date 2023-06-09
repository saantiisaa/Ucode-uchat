#include "../inc/libmx.h" 

int mx_get_substr_index(const char *str, const char *sub) {
    if (str==NULL || sub==NULL)
        return -2;

    int count;
    for (int i = 0; i < mx_strlen(str); i++) {
        count = 0;
        for (int j = 0; j < mx_strlen(sub); j++) {
            if (str[i + j] == sub[j]) {
                count++;
            }
            else {
                continue;
            }
        }
        if (count == mx_strlen(sub)) {
            return i;
        }
    }
    return -1;
}

