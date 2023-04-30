#include "../inc/header.h"
 
int add_user(char *username, char *password) { 
    sqlite3 *db; 
    //char *error_msg = NULL; 
    int rc; 
 
    rc = sqlite3_open("server/chat.db", &db);
 
    if (rc != SQLITE_OK) { 
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db)); 
        sqlite3_close(db); 
        return 1; 
    } 
 
    char *sql = "INSERT INTO users (username, password) VALUES (?, ?)"; 
    sqlite3_stmt *stmt; 
 
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL); 
 
    if (rc != SQLITE_OK) { 
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db)); 
        sqlite3_close(db); 
        return 1; 
    } 
 
    rc = sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC); 
 
    if (rc != SQLITE_OK) { 
        fprintf(stderr, "Failed to bind username parameter: %s\n", sqlite3_errmsg(db)); 
        sqlite3_close(db); 
        return 1; 
    } 
 
    rc = sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC); 
 
    if (rc != SQLITE_OK) { 
        fprintf(stderr, "Failed to bind password parameter: %s\n", sqlite3_errmsg(db)); 
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
