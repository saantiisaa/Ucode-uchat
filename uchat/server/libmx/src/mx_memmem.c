#include "../inc/libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len) {

	if (big_len > 0 && little_len > 0 && big_len >= little_len) {
		char *bc = (char*)big;
		while (*bc) {
			if (mx_memcmp(bc, (char*)little, little_len - 1) == 0) 
                return bc;
			bc++;
		}
	}
    return NULL;
}
/*
int main(){
    char *str = "My name is Neo";
    printf("%s\n",mx_memmem(str,14," is",3));
}*/

