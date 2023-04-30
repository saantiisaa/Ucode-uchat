#include "../inc/header.h"

char **unpack_log(char *str, int size)
{
    int delimiter;
    char **res = malloc((sizeof(char *)) * 2);
    delimiter = mx_get_char_index(str, '|');
    res[0] = mx_strnew(delimiter - 1);
    res[0] = mx_strncpy(res[0], &str[1], delimiter - 1);
    res[1] = mx_strnew(size - (delimiter));
    res[1] = mx_strcpy(res[1], &str[delimiter + 1]);
    return (char **)res;
}

char **unpack_mess(char *str, int size)
{
    int delimiter;
    char **res = malloc((sizeof(char *)) * 4);
    delimiter = mx_get_char_index(str, '|');
    printf("-%d-%d\n", delimiter, size);
    res[0] = mx_strnew(delimiter - 1);
    res[0] = mx_strncpy(res[0], &str[1], delimiter - 1);

    int delimiter2 = mx_get_char_index(&str[delimiter + 1], '|');
    printf("-%d-%d\n", delimiter2, size);
    res[1] = mx_strnew(delimiter2);
    res[1] = mx_strncpy(res[1], &str[delimiter + 1], delimiter2);
    int delimiter3 = mx_get_char_index(&str[delimiter2 + delimiter + 2], 'm');
    printf("-%d-%d\n", delimiter3, size);
    res[2] = mx_strnew(delimiter3);
    res[2] = mx_strncpy(res[2], &str[delimiter2 + delimiter + 2], delimiter3);
    printf("\n%s\n", res[2]);
    int mes_size = atoi(res[2]);
    res[3] = mx_strnew(mes_size);
    res[3] = mx_strcpy(res[3], &str[delimiter2 + delimiter + delimiter3 + 3]);
    printf("-%d-%d\n", delimiter3, size);

    return (char **)res;
}

char *zero_pad(int num, int width)
{
    // створюємо строку, в яку будемо записувати число з ведучими нулями
    char *padded = mx_strnew(width);
    for (int i = 0; i < width; i++)
    {
        padded[i] = '0';
    }

    // знаходимо кількість цифр у числі num
    int digits = 0;
    int num_copy = num;
    while (num_copy != 0)
    {
        num_copy /= 10;
        digits++;
    }

    // якщо числом num більше цифр, ніж width, то виводимо помилку
    if (digits > width)
    {
        free(padded);
        return NULL;
    }

    // записуємо цифри числа num з правого боку в строку
    for (int i = width - 1; i >= 0 && num > 0; i--)
    {
        padded[i] = num % 10 + '0';
        num /= 10;
    }

    return padded;
}

int count_messages(const char *chatname)
{
    sqlite3 *db;
    int rc = sqlite3_open("server/chat.db", &db);
    if (rc)
    {
        printf("Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    // Construct an SQL query to retrieve the count of messages for the chat
    char *table_name = sqlite3_mprintf("%s_messages", chatname);
    char *sql = sqlite3_mprintf("SELECT COUNT(*) FROM %s", table_name);

    int count = 0;
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        printf("Error preparing count query: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
        count = sqlite3_column_int(stmt, 0);
    }
    else
    {
        printf("Error getting count result: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return count;
}

int count_users(const char *param)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    int count = 0;

    // Підключення до бази даних
    rc = sqlite3_open("server/chat.db", &db);
    if (rc)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    // Підготовка SQL-запиту
    char *sql = "SELECT COUNT(*) FROM users WHERE UPPER(username) LIKE UPPER('%' || ? || '%');";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    // Прив'язка параметру до запиту
    sqlite3_bind_text(stmt, 1, param, -1, SQLITE_TRANSIENT);

    // Виконання запиту
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        count = sqlite3_column_int(stmt, 0);
    }

    // Звільнення пам'яті та закриття підключення
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return count;
}

int count_chats(char *username)
{
    sqlite3 *db;
    char *sql = "SELECT COUNT(*) FROM chats WHERE sender = ? OR receiver = ?";
    sqlite3_stmt *stmt;
    int rc, count;
    rc = sqlite3_open("server/chat.db", &db);
    if (rc)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Error preparing statement: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, username, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW)
    {
        fprintf(stderr, "Error executing statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }

    count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);

    return count;
}
