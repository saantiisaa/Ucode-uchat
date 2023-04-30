#include "../inc/libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
	unsigned char *str = (unsigned char *)s + mx_strlen(s);

	while (n--) {
		if (*str == (unsigned char)c)
			return str;
		str--;
	}
	return NULL;
}

