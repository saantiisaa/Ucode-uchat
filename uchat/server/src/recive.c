#include "../inc/header.h"

void *recive(void *sock)
{
    int c_sock = *(int *)sock;
    bool to_exit = false;

    ssize_t size;
    while (!to_exit)
    {
        char *buf = mx_strnew(100);
        size = recv(c_sock, buf, 100, 0);
        if (size == -1)
        {
            printf("%s\n", buf);
            free(buf);
            perror("server");

            exit(1);
        }
        else if (size == 0)
        {
            free(buf);
            printf("End");
            close(c_sock);
            break;
        }
        else
        {
            description(c_sock, buf, size);
            free(buf);
        }
    }
    return (void *)to_exit;
}
