#include <stdio.h>
#include "sqlite3.c"
#include "callback.h"
#include "database.h"

#define TEST    1


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
    char sql[] = "SELECT title, description, status FROM desk_data WHERE desk_id= ";
    strcat(sql,desk_id);
    sqlite3_exec(db, sql, callback, &res, 0);
//printf("who:%s\n", sqlite3_column_text(res, 0));
}

void get_desks() {
    const char* data = "Callback function called";
    printf("%c", sqlite3_exec(db, "SELECT * FROM desk_data;", callback,  (void*)data, &err_msg));
    printf("%s\n", sqlite3_column_text(res, 0));
}

