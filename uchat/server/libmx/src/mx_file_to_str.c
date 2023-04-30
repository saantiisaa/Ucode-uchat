#include "../inc/libmx.h"

char *mx_file_to_str(const char *filename) {
    if(filename == NULL)
        return NULL;
    char temp;
    int count = 0;

    int fd = open (filename, O_RDONLY);
    if (fd == -1)
        return NULL;
    while (read (fd, &temp, 1) > 0)
        count++;
    close (fd);
    char *res = mx_strnew(count);
    fd = open (filename, O_RDONLY);
    //for (int i = 0; read (fd, &temp, 1) > 0; i++)
    //    res[i] = temp;
    //if (close (fd) != 0)
    //    return NULL;
    read(fd, res, count);
    close (fd);
    res[count] = '\0';
    return res;
}

