#include "../inc/header.h"

int add_message(char *chatname, char *sender, char *message) {
    sqlite3 *db;
    int rc;

    rc = sqlite3_open("server/chat.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // Get current time as Unix time
    time_t now = time(NULL);

    // Convert Unix time to UTC
    struct tm *tm = gmtime(&now);

    // Convert UTC time to DATETIME string
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm);

    char *is_edited = "";
    char *table_name = sqlite3_mprintf("%s_messages", chatname);
    char *sql = sqlite3_mprintf("INSERT INTO %s (time, sender, message, is_edited) VALUES (?, ?, ?, ?)", table_name);
    sqlite3_stmt *stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    rc = sqlite3_bind_text(stmt, 1, time_str, -1, SQLITE_STATIC);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to bind time parameter: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    rc = sqlite3_bind_text(stmt, 2, sender, -1, SQLITE_STATIC);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to bind sender parameter: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    rc = sqlite3_bind_text(stmt, 3, message, -1, SQLITE_STATIC);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to bind message parameter: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    rc = sqlite3_bind_text(stmt, 4, is_edited, -1, SQLITE_STATIC);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to bind is_edited parameter: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    rc = sqlite3_step(stmt); 
 
    if (rc != SQLITE_DONE) { 
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db)); 
        sqlite3_close(db); 
        return 1; 
    } 
 
    sqlite3_finalize(stmt); 
    sqlite3_close(db); 
 
    return 0; 
}




