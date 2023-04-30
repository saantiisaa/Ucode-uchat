#include "../inc/header.h"

int del_chat(char *chatname)
{
    sqlite3 *db;
    int rc;

    printf("CHATNAME %s\n", chatname);
    rc = sqlite3_open("server/chat.db", &db);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char *sql = sqlite3_mprintf("DELETE FROM chats WHERE chatname = ?");
    sqlite3_stmt *stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    rc = sqlite3_bind_text(stmt, 1, chatname, -1, SQLITE_STATIC);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to bind chatname parameter: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE)
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_finalize(stmt);

    // Drop chatname_messages table
    char *table_name = sqlite3_mprintf("%s_messages", chatname);
    sql = sqlite3_mprintf("DROP TABLE IF EXISTS %s", table_name);
    rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to drop chat messages table: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);

    return 0;
}
