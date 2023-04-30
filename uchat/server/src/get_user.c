#include "../inc/header.h"
 
int get_user(char *username, char *password) { 
    sqlite3 *db; 
    //char *error_msg = NULL; 
    int rc; 
 
    rc = sqlite3_open("server/chat.db", &db);
 
    if (rc != SQLITE_OK) { 
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db)); 
        sqlite3_close(db); 
        return 0; 
    } 
 
    char *sql = "SELECT password FROM users WHERE username = ?"; 
    sqlite3_stmt *stmt; 
 
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL); 
 
    if (rc != SQLITE_OK) { 
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db)); 
        sqlite3_close(db); 
        return 0; 
    } 
 
    rc = sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC); 
 
    if (rc != SQLITE_OK) { 
        fprintf(stderr, "Failed to bind username parameter: %s\n", sqlite3_errmsg(db)); 
        sqlite3_close(db); 
        return 0; 
    } 
 
    rc = sqlite3_step(stmt); 
    int res = 0;
 
    if (rc == SQLITE_ROW) { 
        const unsigned char *pass = sqlite3_column_text(stmt, 0); 
        if (mx_strcmp((const char *)pass, password) == 0) { 
            printf("User authenticated.\n"); 
            res = 1;
        } else { 
            printf("Incorrect password.\n"); 
            res = 0;
        } 
    } else { 
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db)); 
        sqlite3_close(db); 
        return 0; 
    } 
 
    sqlite3_finalize(stmt); 
    sqlite3_close(db); 
 
    return res; 
}
