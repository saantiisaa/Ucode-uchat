#include "../inc/header.h"

int check_chat(char* sender, char* receiver) {
    sqlite3* db;
    int rc = sqlite3_open("server/chat.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    int result = 0;
    sqlite3_stmt* stmt;
    char* sql = "SELECT COUNT(*) FROM chats WHERE chatname = ?";
    char* chatname = sqlite3_mprintf("%s_%s", sender, receiver);
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, chatname, -1, SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            int count = sqlite3_column_int(stmt, 0);
            if (count > 0) {
                result = 1;
            }
        }
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    sqlite3_free(chatname);
    return result;
}

