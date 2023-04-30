#include "../inc/header.h"
int mes_callback(void *model, int argc, char **argv, char **azColName)
{
    mx_strlen(*azColName);
    int fd = *(int *)model;
    char *str;
    int count = 0;
    printf(" argc - %d\n", argc);
    for (int i = 0; i < argc; i++)
    {
        printf("%s\t", argv[i]);
        count += mx_strlen(argv[i]);
    }
    printf("\n");
    str = mx_strnew(count + 10 + argc - 1);
    str = mx_strcat(str, zero_pad(count + argc - 1, 10));
    for (int i = 0; i < argc; i++)
    {
        str = mx_strcat(str, argv[i]);
        if (i < argc - 1)
        {
            str = mx_strcat(str, "|");
        }
    }
    printf("argv: %s\n", str);
    send(fd, str, mx_strlen(str), 0);

    return 0;
}

int fill_messages_list(const char *chatname, int fd)
{
    int count = count_messages(chatname);
    if (count == 0)
    {
        send(fd, "0", 1, 0);
        return 0;
    }
    char *temp = zero_pad(count, 10);
    int k = send(fd, temp, mx_strlen(temp), 0);
    // perror("server");
    if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
    {
        printf("ck\n");
    }
    if (k == -1)
    {
        perror("callbak");
        exit(1);
    }
    // printf("chatname: %s",chatname);
    sqlite3 *db;
    int rc = sqlite3_open("server/chat.db", &db);
    if (rc)
    {
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(0);
    }
    // Construct an SQL query to retrieve the data from the database
    char *table_name = sqlite3_mprintf("%s_messages", chatname);
    char *sql = sqlite3_mprintf("SELECT id, strftime('%%d.%%m.%%Y %%H:%%M', time, 'localtime'), sender, is_edited, message FROM %s", table_name);

    // Execute the query and retrieve the results into a callback function
    rc = sqlite3_exec(db, sql, mes_callback, &fd, NULL);
    if (rc != SQLITE_OK)
    {
        printf("Error executing messages query: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    sqlite3_close(db);
    return 0;
}
