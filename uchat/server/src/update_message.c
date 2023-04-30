#include "../inc/header.h"

int update_message(char *chatname, int message_id, char* new_text) { 
    sqlite3 *db; 
    int rc; 
 
    rc = sqlite3_open("server/chat.db", &db);
 
    if (rc != SQLITE_OK) { 
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db)); 
        sqlite3_close(db); 
        return 1; 
    }

    char *table_name = sqlite3_mprintf("%s_messages", chatname);
    char *sql = sqlite3_mprintf("UPDATE %s SET message = ?, is_edited = '(edited)' WHERE id = ?", table_name);
    sqlite3_stmt *stmt; 
 
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL); 
 
    if (rc != SQLITE_OK) { 
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db)); 
        sqlite3_close(db); 
        return 1; 
    } 
 
    rc = sqlite3_bind_text(stmt, 1, new_text, -1, SQLITE_STATIC); 
 
    if (rc != SQLITE_OK) { 
        fprintf(stderr, "Failed to bind new_text parameter: %s\n", sqlite3_errmsg(db)); 
        sqlite3_close(db); 
        return 1; 
    }

    rc = sqlite3_bind_int(stmt, 2, message_id); 
 
    if (rc != SQLITE_OK) { 
        fprintf(stderr, "Failed to bind new_text parameter: %s\n", sqlite3_errmsg(db)); 
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


