#include "../inc/header.h"

bool description(int fd, char *str, int size)
{
    char **log_pas;
    int res;

    if (str[0] == '0')
    {
        printf("%s", str);
        log_pas = unpack_log(str, size);

        res = add_user(log_pas[0], log_pas[1]);
        free(log_pas[0]);
        free(log_pas[1]);
        free(log_pas);
        printf("%d", res);
        send(fd, mx_itoa(res), mx_strlen(mx_itoa(res)), 0);
    }
    else if (str[0] == '1')
    {
        res = del_user(&str[1]);
        printf("%d\n", res);
        printf("\nDelete user %s\n", &str[1]);
        send(fd, mx_itoa(res), mx_strlen(mx_itoa(res)), 0);
    }
    else if (str[0] == '2')
    {
        log_pas = unpack_log(str, size);
        res = get_user(log_pas[0], log_pas[1]);
        free(log_pas[0]);
        free(log_pas[1]);
        free(log_pas);
        printf("%d\n", res);
        send(fd, mx_itoa(res), mx_strlen(mx_itoa(res)), 0);
    }
    else if (str[0] == '3')
    {
        res = check_username(&str[1]);
        send(fd, mx_itoa(res), mx_strlen(mx_itoa(res)), 0);
    }
    else if (str[0] == '4')
    {
        fill_users_list(&str[1], fd);
    }
    else if (str[0] == '5')
    {
        log_pas = unpack_log(str, size);
        res = del_message(log_pas[0], atoi(log_pas[1]));
        send(fd, mx_itoa(res), mx_strlen(mx_itoa(res)), 0);
    }
    else if (str[0] == '6')
    {
        log_pas = unpack_log(str, size);
        res = add_chat(log_pas[0], log_pas[1]);
        send(fd, mx_itoa(res), mx_strlen(mx_itoa(res)), 0);
        free(log_pas[0]);
        free(log_pas[1]);
        free(log_pas);
    }
    else if (str[0] == '7')
    {
        fill_chats_list(&str[1], fd);
    }
    else if (str[0] == '8')
    {
        log_pas = unpack_log(str, size);
        res = check_chat(log_pas[0], log_pas[1]);
        printf("\n%s\n", log_pas[0]);
        printf("\n%s\n", log_pas[1]);
        send(fd, mx_itoa(res), mx_strlen(mx_itoa(res)), 0);
        free(log_pas[0]);
        free(log_pas[1]);
        free(log_pas);
    }
    else if (str[0] == '9')
    {
        log_pas = unpack_mess(str, size);
        int len_msg = atoi(log_pas[2]);

        printf("\n%s\n", log_pas[0]);
        printf("\n%s\n", log_pas[1]);
        printf("\n%s\n", log_pas[2]);
        printf("\n%s\n", log_pas[3]);

        if (len_msg > mx_strlen(log_pas[3]))
        {
            char *buf = mx_strnew(len_msg - mx_strlen(log_pas[3]));
            int byte = recv(fd, buf, len_msg, 0);
            if (byte < 0)
            {
                perror("server");
                exit(1);
            }
            log_pas[3] = mx_strcat(log_pas[3], buf);
            free(buf);
        }

        res = add_message(log_pas[0], log_pas[1], log_pas[3]);
        send(fd, mx_itoa(res), mx_strlen(mx_itoa(res)), 0);
        printf("%d\n", res);

        free(log_pas[0]);
        free(log_pas[1]);
        free(log_pas[2]);
        free(log_pas[3]);
        free(log_pas);
    }
    else if (str[0] == 'd')
    {
        res = del_chat(&str[1]);
        send(fd, mx_itoa(res), mx_strlen(mx_itoa(res)), 0);
    }
    else if (str[0] == 'u')
    {
        log_pas = unpack_mess(str, size);
        int mes_id = atoi(log_pas[1]);
        int len_msg = atoi(log_pas[2]);

        printf("\n%s\n", log_pas[0]);
        printf("\n%s\n", log_pas[1]);
        printf("\n%s\n", log_pas[2]);
        printf("\n%s\n", log_pas[3]);
        printf("\n%d - %d\n", len_msg, mx_strlen(log_pas[3]));
        if (len_msg > mx_strlen(log_pas[3]))
        {
            printf("k");
            char *buf = mx_strnew(len_msg - mx_strlen(log_pas[3]));
            int byte = recv(fd, buf, len_msg, 0);
            if (byte < 0)
            {
                perror("server");
                exit(1);
            }
            log_pas[3] = mx_strcat(log_pas[3], buf);
            free(buf);
        }
        printf("n");

        res = update_message(log_pas[0], mes_id, log_pas[3]);
        send(fd, mx_itoa(res), mx_strlen(mx_itoa(res)), 0);

        free(log_pas[0]);
        free(log_pas[1]);
        free(log_pas[2]);
        free(log_pas[3]);
        free(log_pas);
    }
    else if (str[0] == 'l')
    {
        fill_messages_list(&str[1], fd);
    }
    else if (str[0] == 'k')
    {
        log_pas = unpack_log(str, size);
        printf("%s\n", log_pas[0]);
        printf("%s\n", log_pas[1]);
        res = change_password(log_pas[0], log_pas[1]);
        send(fd, mx_itoa(res), mx_strlen(mx_itoa(res)), 0);
        free(log_pas[0]);
        free(log_pas[1]);
        free(log_pas);
    }

    return true;
}
