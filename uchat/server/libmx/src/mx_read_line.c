#include "../inc/libmx.h"

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    if (fd < 0 || buf_size < 0 || !delim|| !lineptr) 
        return -2;

    (*lineptr) = (char *)mx_realloc(*lineptr, buf_size);
    mx_memset((*lineptr), '\0', sizeof((*lineptr)));
    size_t size = 0;
    char c;

    if (read(fd, &c, 1)) {
        if (c == delim) 
            return size;
        
        (*lineptr) = (char *)mx_realloc(*lineptr, size + 1);
        (*lineptr)[size] = c;
        size++;
    }
    else{
        return -1;
    }

    while (read(fd, &c, 1)) {
        if (c == delim) 
            break;
        
        if (size >= buf_size){
            (*lineptr) = (char*)mx_realloc(*lineptr, size + 1);
        }
        (*lineptr)[size] = c;
        size++;
    }

    (*lineptr) = (char*)mx_realloc(*lineptr, size + 1);

    size_t free_bytes = sizeof((*lineptr)) - size;
    mx_memset(&(*lineptr)[size], '\0', free_bytes);

    return size + 1;
}


