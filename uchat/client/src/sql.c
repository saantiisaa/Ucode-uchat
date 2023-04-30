#include "../inc/header.h"

int add_user(char *username, char *password)
{

    char *str = to_serv(username, password);
    printf("%s - %lu\n", str, strlen(str));
    char *res = mx_strnew(strlen(str) + 1);
    res[0] = '0';
    res = strcat(res, str);

    printf("%s\n", res);
    Send(client_fd, res, strlen(res), 0);
    free(res);
    free(str);
    char temp[2];
    int b = recv(client_fd, &temp, 2, 0);
    if (b == -1)
    {
        printf("Error");
    }
    printf("%s\n", temp);
    return atoi(temp);
}

int del_user(char *username)
{
    char *res = mx_strnew(strlen(username) + 1);
    res[0] = '1';
    res = strcat(res, username);
    Send(client_fd, res, strlen(res), 0);
    free(res);

    char temp[5] = "\0\0\0\0\0";
    int b = recv(client_fd, &temp, 1, 0);
    if (b == -1)
    {
        printf("Error");
    }
    printf("%s\n", temp);
    return atoi(temp);
}

int change_password(char *username, char *new_password)
{
    char *str = to_serv(username, new_password);
    printf("%s - %lu\n", str, strlen(str));
    char *res = mx_strnew(strlen(str) + 1);
    res[0] = 'k';
    res = strcat(res, str);
    int k = send(client_fd, res, strlen(res), 0);
    if (k == -1)
    {
        printf("Error sending data: %s\n", strerror(errno));
        free(res);
        free(str);
        return -1;
    }
    free(str);

    char temp[2];
    int b = recv(client_fd, &temp, 1, 0);
    if (b == -1)
    {
        printf("Error receiving data");
        return -1;
    }
    printf("%s\n", temp);
    return atoi(temp);
}

int get_user(char *username, char *password)
{
    char *str = to_serv(username, password);
    printf("%s - %lu\n", str, strlen(str));
    char *res = mx_strnew(strlen(str) + 1);
    res[0] = '2';
    res = strcat(res, str);
    Send(client_fd, res, strlen(res), 0);
    free(res);
    free(str);

    char temp[5] = "\0\0\0\0\0";
    int b = recv(client_fd, &temp, 1, 0);
    if (b == -1)
    {
        printf("Error");
    }
    printf("%s\n", temp);
    return atoi(temp);
}

int check_username(char *username)
{
    char *res = mx_strnew(strlen(username) + 1);
    res[0] = '3';
    res = strcat(res, username);
    Send(client_fd, res, strlen(res), 0);
    free(res);

    char temp[5] = "\0\0\0\0\0";
    int b = recv(client_fd, &temp, 1, 0);
    if (b == -1)
    {
        printf("Error");
    }
    printf("%s\n", temp);
    return atoi(temp);
}

int fill_users_list(const gchar *search, char *username, GtkListStore *users_store)
{

    char *res = mx_strnew(strlen(search) + 1);
    res[0] = '4';
    res = strcat(res, search);
    int k = Send(client_fd, res, strlen(res), 0);
    free(res);

    char *temp = mx_strnew(10);
    k = recv(client_fd, temp, 10, 0);
    int size = atoi(temp);
    free(temp);
    if (size == 0)
    {
        // printf("0 naideno");
        return 0;
    }

    printf("size  - %d;\n", size);
    for (int i = 0; i < size; i++)
    {
        printf("lk\n");
        temp = mx_strnew(10);
        k = recv(client_fd, temp, 10, 0);
        if (k == 0)
        {
            // break;
        }
        if (k == -1)
        {
            printf("Error5");
            exit(1);
        }
        int len = atoi(temp);
        free(temp);
        char *buf = mx_strnew(len + 1);
        buf[len] = '\0';
        k = recv(client_fd, buf, len, 0);
        printf("\n k -%d-\n", k);
        if (strcmp(buf, username) == 0)
        {
            free(buf);
            continue;
        }

        printf("\n%s\n", buf);
        GtkTreeIter iter;
        gtk_list_store_append(GTK_LIST_STORE(users_store), &iter);
        gtk_list_store_set(GTK_LIST_STORE(users_store), &iter,
                           USER_ID_COLUMN, "0",
                           USER_NAME_COLUMN, buf, // buf huinu delaet nepravda
                           -1);

        write(1, buf, k);
        printf("\n%s\n", buf);
        free(buf);
        // send(client, "----", 5, 0);
    }

    return 0;
}

int add_chat(char *sender, char *receiver)
{

    char *str = to_serv(sender, receiver);
    char *res = mx_strnew(strlen(str) + 1);
    res[0] = '6';
    res = strcat(res, str);
    Send(client_fd, res, strlen(res), 0);
    free(res);
    free(str);

    char temp[5] = "\0\0\0\0\0";
    int b = recv(client_fd, &temp, 1, 0);
    if (b == -1)
    {
        printf("Error");
    }
    printf("%s\n", temp);
    return atoi(temp);
}

int del_chat(char *chatname)
{
    char *res = mx_strnew(strlen(chatname) + 1);
    res[0] = 'd';
    res = strcat(res, chatname);
    Send(client_fd, res, strlen(res), 0);
    free(res);

    char temp[5] = "\0\0\0\0\0";
    int b = recv(client_fd, &temp, 1, 0);
    if (b == -1)
    {
        printf("Error");
    }
    printf("%s\n", temp);
    return atoi(temp);
}

int fill_chats_list(const gchar *search, GtkListStore *chats_store)
{
    char *res = mx_strnew(strlen(search) + 1);
    res[0] = '7';
    res = strcat(res, search);
    int k = Send(client_fd, res, strlen(res), 0);
    free(res);

    char *temp = mx_strnew(10);
    k = recv(client_fd, temp, 10, 0);
    int size = atoi(temp);
    free(temp);
    if (size == 0)
    {
        // printf("0 naideno");
        return 0;
    }

    printf("size  - %d;\n", size);
    for (int i = 0; i < size; i++)
    {
        printf("lk - %d\n", client_fd);
        temp = mx_strnew(10);
        k = recv(client_fd, temp, 10, 0);
        if (k == 0)
        {
            // break;
        }
        if (k == -1)
        {
            printf("Error5");
            exit(1);
        }
        int len = atoi(temp);
        free(temp);
        char *buf = mx_strnew(len);
        k = recv(client_fd, buf, len, 0);
        printf("\n-%d-\n", k);
        printf("\nBUF ---   %s\n", buf);
        char **mess = unpack_mess_v3(buf, strlen(buf), 4);
        free(buf);

        GtkTreeIter iter;

        printf("\n\n\n\n%s\n%s\n", mess[1], mess[3]);
        gtk_list_store_append(GTK_LIST_STORE(chats_store), &iter);
        if (strcmp(username, mess[2]) == 0)
        {
            gtk_list_store_set(GTK_LIST_STORE(chats_store), &iter,
                               CHAT_ID_COLUMN, mess[0],
                               CHAT_CHATNAME_COLUMN, mess[1],
                               CHAT_SENDER_COLUMN, mess[2],
                               CHAT_RECEIVER_COLUMN, mess[3],
                               CHAT_CHATS_COLUMN, mess[3],
                               -1);
        }
        if (strcmp(username, mess[3]) == 0)
        {
            gtk_list_store_set(GTK_LIST_STORE(chats_store), &iter,
                               CHAT_ID_COLUMN, mess[0],
                               CHAT_CHATNAME_COLUMN, mess[1],
                               CHAT_SENDER_COLUMN, mess[2],
                               CHAT_RECEIVER_COLUMN, mess[3],
                               CHAT_CHATS_COLUMN, mess[2],
                               -1); // zrobit` pzh
        }
        free(mess[0]);
        free(mess[1]);
        free(mess[2]);
        free(mess[3]);
        free(mess);
    }
    return 0;
}

int check_chat(char *sender, char *receiver)
{
    char *str = to_serv(sender, receiver);
    char *res = mx_strnew(strlen(str) + 1);
    res[0] = '8';
    res = strcat(res, str);
    Send(client_fd, res, strlen(res), 0);
    free(res);
    free(str);

    char temp[5] = "\0\0\0\0\0";
    int b = recv(client_fd, &temp, 1, 0);
    if (b == -1)
    {
        printf("Error");
    }
    printf("%s\n", temp);
    return atoi(temp);
}

// temp = "9kanistrych_11111\\kanistrych\\12mZ Velykodnem";
int add_message(char *chatname, char *sender, char *message)
{

    char *str = to_serv_x2(chatname, sender, mx_itoa(strlen(message)), message);
    char *res = mx_strnew(strlen(str) + 1);
    res[0] = '9';
    res = strcat(res, str);
    Send(client_fd, res, strlen(res), 0);
    free(res);
    free(str);

    char temp[5] = "\0\0\0\0\0";
    int b = recv(client_fd, &temp, 1, 0);
    if (b == -1)
    {
        printf("Error");
    }
    printf("%s\n", temp);
    return atoi(temp);
}

int update_message(char *chatname, int message_id, char *new_text)
{
    char *str = to_serv_x2(chatname, mx_itoa(message_id), mx_itoa(strlen(new_text)), new_text);
    char *res = mx_strnew(strlen(str) + 1);
    res[0] = 'u';
    res = strcat(res, str);
    Send(client_fd, res, strlen(res), 0);
    free(res);
    free(str);

    char temp[5] = "\0\0\0\0\0";
    int b = recv(client_fd, &temp, 1, 0);
    if (b == -1)
    {
        printf("Error");
    }
    printf("%s\n", temp);
    return atoi(temp);
}

int del_message(char *chatname, int message_id)
{
    char *str = to_serv(chatname, mx_itoa(message_id));
    char *res = mx_strnew(strlen(str) + 1);
    res[0] = '5';
    res = strcat(res, str);
    Send(client_fd, res, strlen(res), 0);
    free(res);
    free(str);

    char temp[5] = "\0\0\0\0\0";
    int b = recv(client_fd, &temp, 1, 0);
    if (b == -1)
    {
        printf("Error");
    }
    printf("%s\n", temp);
    return atoi(temp);
}

int fill_messages_list(const char *chatname, GtkListStore *messages_store)
{

    char *res = mx_strnew(strlen(chatname) + 1);
    res[0] = 'l';
    res = strcat(res, chatname);
    int k = Send(client_fd, res, strlen(res), 0);
    free(res);

    char *temp = mx_strnew(10);
    k = recv(client_fd, temp, 10, 0);
    int size = atoi(temp);
    free(temp);
    if (size == 0)
    {
        // printf("0 naideno");
        return 0;
    }

    printf("size  - %d;\n", size);
    for (int i = 0; i < size; i++)
    {
        printf("lk\n");
        temp = mx_strnew(10);
        k = recv(client_fd, temp, 10, 0);
        if (k == 0)
        {
            // break;
        }
        if (k == -1)
        {
            printf("Error5");
            exit(1);
        }
        int len = atoi(temp);
        free(temp);
        char *buf = mx_strnew(len);
        k = recv(client_fd, buf, len, 0);
        printf("\n-%d-\n", k);
        printf("\nBUF ---   %s\n", buf);
        char **mess = unpack_mess_v3(buf, strlen(buf), 5);
        free(buf);

        GtkTreeIter iter;

        gtk_list_store_append(GTK_LIST_STORE(messages_store), &iter);
        gtk_list_store_set(GTK_LIST_STORE(messages_store), &iter,
                           MESSAGE_ID_COLUMN, mess[0],
                           MESSAGE_TIME_COLUMN, mess[1],
                           MESSAGE_SENDER_COLUMN, mess[2],
                           MESSAGE_TEXT_COLUMN, mess[4],
                           MESSAGE_IS_EDITED_COLUMN, mess[3],
                           -1);

        free(mess[0]);
        free(mess[1]);
        free(mess[2]);
        free(mess[3]);
        free(mess[4]);
        free(mess);
    }

    return 0;
}
