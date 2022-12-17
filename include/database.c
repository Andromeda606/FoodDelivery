#include <stdio.h>
#include "sqlite3.c"
#include "callback.h"
#include "database.h"


sqlite3 *db;
sqlite3_stmt *res;
char *err_msg = 0;

int callback(void *data, int argc, char **argv,
             char **azColName) {
    int i;
    for(i = 0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

void init() {
    char path[20] = "restoran.db";
    if (TEST) {
        strcpy(path, "../restoran.db");
    }
    sqlite3_open_v2(path, &db, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, NULL);
}

void print_desk(char desk_id[]) {
    char sql[70] = "SELECT title, description, status FROM desk_data WHERE desk_id = ";
    strcat(sql,desk_id);
    sqlite3_exec(db, sql, callback_desk, &res, 0);
    //printf("%sqlite3_stmt",res);
}

void get_desks() {
    const char* data = "Callback function called";
    printf("%c", sqlite3_exec(db, "SELECT * FROM desk_data;", callback_all_desk,  (void*)data, &err_msg));
    printf("%s\n", sqlite3_column_text(res, 0));
}

int login(char username[], char password[]){
    char *sql = "SELECT id FROM users WHERE username = ? and password = ?;";
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_text(res, 1, username,-1,sqlite3_free);
        sqlite3_bind_text(res, 2, password,-1,sqlite3_free);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);
    return step == SQLITE_ROW;
}
