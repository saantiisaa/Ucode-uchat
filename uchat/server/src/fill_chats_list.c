#include "../inc/header.h"

int callback_chats(void *model, int argc, char **argv, char **azColName)
{
    mx_strlen(*azColName);
    int fd = *(int *)model;
    char *str;
    int count = 0;
    for (int i = 0; i < argc; i++)
    {
        count += mx_strlen(argv[i]);
    }
    str = mx_strnew(count + 10 + argc - 1);
    str = mx_strcpy(str, zero_pad(count + argc - 1, 10));
    for (int i = 0; i < argc; i++)
    {
        str = mx_strcat(str, argv[i]);
        if (i < argc - 1)
        {
            str = mx_strcat(str, "|");
        }
    }
    send(fd, str, mx_strlen(str), 0);
    if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
    {
        printf("ck\n");
    }
    printf("%d -- %s\n", fd, str);
    return 0;
}

int fill_chats_list(const char *search, int fd)
{
    int count = count_chats((char *)search);
    printf("ct - %d\n", count);
    if (count == 0)
    {
        send(fd, "0", 1, 0);
        return 0;
    }
    char *temp = zero_pad(count, 10);
    send(fd, temp, mx_strlen(temp), 0);
    free(temp);
    sqlite3 *db;
    int rc = sqlite3_open("server/chat.db", &db);
    if (rc)
    {
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(0);
    }
    // Construct an SQL query to retrieve the data from the database
    char *sql = sqlite3_mprintf("SELECT id, chatname, sender, receiver FROM chats WHERE sender='%q' OR receiver='%q'", search, search);

    // Execute the query and retrieve the results into a callback function
    rc = sqlite3_exec(db, sql, callback_chats, &fd, NULL);
    if (rc != SQLITE_OK)
    {
        printf("Error executing query: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    return 0;
}
