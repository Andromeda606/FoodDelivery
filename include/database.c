#include <stdio.h>
#include "sqlite3.h"
#include "callback.h"
#include "database.h"
#include <helper.h>
#include "menu.h"
#include <ncurses.h>
#include <string.h>
#include <locale.h>

sqlite3 *db;
sqlite3_stmt *res;
char *err_msg = 0;

void init() {
    char path[20] = "restoran.db";
    if (TEST) {
        strcpy(path, "../restoran.db");
    }
    sqlite3_open_v2(path, &db, SQLITE_OPEN_READWRITE, NULL);
}

//DESK ALGORITHM
void print_desk(char desk_id[]) {
    char sql[70] = "SELECT title, description, status FROM desk_data WHERE desk_id = ";
    strcat(sql, desk_id);
    sqlite3_exec(db, sql, callback_desk, &res, 0);
    //printf("%sqlite3_stmt",res);
}

void get_desks() {
    const char *data = "Callback function called";
    printf("%c", sqlite3_exec(db, "SELECT * FROM desk_data;", callback_all_desk, (void *) data, &err_msg));
    printf("%s\n", sqlite3_column_text(res, 0));
}

// AUTH

int login(char username[], char password[]) {
    char *sql = "SELECT id FROM users WHERE username = ? and password = ?;";
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_text(res, 1, username, -1, sqlite3_free);
        sqlite3_bind_text(res, 2, password, -1, sqlite3_free);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);
    return step == SQLITE_ROW;
}



// FOOD MENU

void show_menu(int desk_id) {
    struct Food card[50];
    struct Category categories[10];
    struct Food foods[20];

    sqlite3_prepare_v2(db, "SELECT id,name,price,category FROM menu;", -1, &res, 0);

    int i;
    for (i = 0; sqlite3_step(res) != SQLITE_DONE; i++) {
        struct Food food;
        food.id = sqlite3_column_int(res, 0);
        memcpy(food.name, sqlite3_column_text(res, 1), 20);
        food.price = sqlite3_column_int(res, 2);
        food.category = sqlite3_column_int(res, 3);
        food.defined = 1;
        foods[i] = food;
    }


    //added category
    sqlite3_prepare_v2(db, "SELECT id, text FROM category;", -1, &res, 0);

    for (int j = 0; sqlite3_step(res) != SQLITE_DONE; j++) {
        struct Category category;
        category.id = sqlite3_column_int(res, 0);
        memcpy(category.text, sqlite3_column_text(res, 1), 20);
        categories[category.id] = category;
    }


    initscr();
    noecho();

    start_color();

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    draw_menu(foods,
              card,
              0,
              0,
              i,
              desk_id,
              categories);
}

void buy_products(int desk_id, struct Card *cards) {
    char sql[500] = "";

    for (int i = 0; i < 20; i++) {
        struct Card card = cards[i];
        if (card.defined != 1) {
            break;
        }
        char buffer[200] = "";
        sprintf(buffer,
                "INSERT INTO desk_data (desk_id, title, quantity, type_id) VALUES (%d,'%s', %d, %d);",
                desk_id, card.name, card.quantity, card.id);
        strcat(sql, buffer);

    }
    sqlite3_exec(db, sql, 0, 0, 0);
    clear_screen();
    endwin();
}


int get_desk_status(int desk_id) {
    struct DeskData *desks;
    char *sql = "SELECT status FROM desk_data WHERE desk_id = ? LIMIT 1;";
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_int(res, 1, desk_id);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_step(res);
    return sqlite3_column_int(res, 0);

    /*for (int i = 0; sqlite3_step(res) != SQLITE_DONE; i++) {
        struct DeskData desk;
        desk.status = sqlite3_column_int(res, 0);
        desk.type_id = sqlite3_column_int(res, 0);
        desk.quantity = sqlite3_column_int(res, 0);
        desk.defined = 1;
        memcpy(desk.name, sqlite3_column_text(res, 1), 20);
        desks[i] = desk;
    }
    return desks;*/
}

/*
 * void get_note(int desk_id){
    system("cls");
    int keyboard;
    int c;
    for(int i=0;;i++){
        system("cls");

    }
    printf("\t\t%30s\n","Siparişinize Not Geldi!");
    printf("\t%120s\n","Merhaba Bu bir Nottur notlar harikadır bence seçmelisin.");
}
*/