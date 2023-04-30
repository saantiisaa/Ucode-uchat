#include "../inc/header.h"

int callback(void *model, int argc, char **argv, char **azColName)
{
    mx_strlen(*azColName);
    // GtkTreeIter iter;
    int fd = *(int *)model;
    char *str;
    int count = 0;
    for (int i = 0; i < argc; i++)
    {
        count += mx_strlen(argv[i]);
    }
    printf("\n");
    str = mx_strnew(count + 10);
    printf("lenght  - %d\n", count);
    str = mx_strcpy(str, zero_pad(count, 10));
    for (int i = 0; i < argc; i++)
    {
        str = mx_strcat(str, argv[i]);
    }
    printf("%s\n", str);
    send(fd, str, mx_strlen(str), 0);
    printf("%d\n", fd);
    return 0;
}

int fill_users_list(const char *search, int fd)
{
    int count = count_users(search);
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
    char *sql = sqlite3_mprintf("SELECT username FROM users WHERE username LIKE '%%%q%%'", search);

    // Execute the query and retrieve the results into a callback function
    rc = sqlite3_exec(db, sql, callback, &fd, NULL);
    if (rc != SQLITE_OK)
    {
        printf("Error executing query: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    return 0;
}
