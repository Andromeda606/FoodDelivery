#include "database.h"
#include <stdio.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Turkish");
    printf("Restoran Kayıt Sistemi\n");
    init();
    //get_desks();
    print_desk("1");

    /*
    sqlite3 *db;
    sqlite3_stmt *res;
    char *err_msg = 0;

    int rc = sqlite3_open_v2("../restoran.db", &db,SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE,NULL);



    rc = sqlite3_prepare_v2(db, "SELECT SQLITE_VERSION()", -1, &res, 0);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    rc = sqlite3_step(res);

    if (rc == SQLITE_ROW) {
        printf("%s\n", sqlite3_column_text(res, 0));
    }

    rc = sqlite3_exec(db, "SELECT * FROM desk_data;", callback, 0, &err_msg);
    printf("sunc: %d\n",rc);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }
    if (rc == SQLITE_OK) {
        printf("%s\n", sqlite3_column_text(res, 0));
    }

    sqlite3_finalize(res);
    sqlite3_close(db);*/
    return 0;
}
