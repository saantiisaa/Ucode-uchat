#include "../inc/header.h"
int check_username(char* username) {

    sqlite3 *db; 
    int rc; 
 
    rc = sqlite3_open("server/chat.db", &db); 
 
    if (rc != SQLITE_OK) { 
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db)); 
        sqlite3_close(db); 
        return 1; 
    } 

    int result = 0;
    sqlite3_stmt* stmt;
    char* sql = "SELECT COUNT(*) FROM users WHERE username = ?";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);
        
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            int count = sqlite3_column_int(stmt, 0);
            
            if (count > 0) {
                result = 1; // результат 1 означає, що таке ім'я в таблиці є
            }
        }
    }
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return result;
}
