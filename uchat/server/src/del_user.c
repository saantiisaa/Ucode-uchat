#include "../inc/header.h"

int del_user(char *username) {
    sqlite3 *db;
    int rc;
    rc = sqlite3_open("server/chat.db", &db);

    char *err_msg = 0;
    char sql[100];
    sprintf(sql, "DELETE FROM users WHERE username='%s'", username);
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Error deleting user: %s\n", err_msg);
        sqlite3_free(err_msg);
        return 1;
    }
    else
    {
        printf("User '%s' deleted successfully.\n", username);
    }

    char *sql2 = sqlite3_mprintf("DELETE FROM chats WHERE sender='%q' OR receiver='%q';", username, username);
    rc = sqlite3_exec(db, sql2, NULL, NULL, NULL);

    // Retrieve all tables in the database
    int num_tables = 0;
    char **tables;
    sqlite3_get_table(db, "SELECT name FROM sqlite_master WHERE type='table'", &tables, &num_tables, NULL, &err_msg);

    // Iterate through all tables and delete those that match the user's chats
    for (int i = 1; i <= num_tables; i++)
    {
        char *table_name = tables[i];
        if (strncmp(table_name, username, strlen(username)) == 0)
        {
            sprintf(sql, "DROP TABLE %s", table_name);
            rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
            if (rc != SQLITE_OK)
            {
                fprintf(stderr, "Error deleting table '%s': %s\n", table_name, err_msg);
                sqlite3_free(err_msg);
                return 1;
            }
            else
            {
                printf("Table '%s' deleted successfully.\n", table_name);
            }
        }
    }

    sqlite3_free_table(tables);
    sqlite3_close(db);
    return 0;
}

