#include <stdio.h>

#define _GNU_SOURCE

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
    sqlite3_open_v2(path, &db, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, NULL);
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

struct Food {
    int id, category, price, defined;
    char name[20];
} Food;

struct Card {
    int id, quantity, defined, price;
    char name[20];

} Card;

struct DeskData {
    int status, type_id, quantity, defined;
    char name[20];
} DeskData;

void show_menu(int desk_id) {
    sqlite3_prepare_v2(db, "SELECT * FROM menu;", -1, &res, 0);
    struct Food foods[20];
    int el;
    for (el = 0; sqlite3_step(res) != SQLITE_DONE; el++) {
        struct Food food;
        food.id = sqlite3_column_int(res, 0);
        memcpy(food.name, sqlite3_column_text(res, 1), 20);
        food.price = sqlite3_column_int(res, 2);
        food.category = sqlite3_column_int(res, 3);
        food.defined = 1;
        foods[el] = food;
    }

    struct Food card[50];
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(2, COLOR_WHITE, COLOR_CYAN);
    draw_menu(foods, card, 0, 0, el, desk_id);
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

static void sync_card(struct Food *foods, struct Card *card, int selected_line, int card_length, int el, int desk_id) {
    printw("Sepetinizin içeriği, onaylıyor musunuz?\n");
    printw("=============================================\n");
    int plussing = 0;
    printw("%4s %30s\t%4s\n", "Adet", "Adı", "Fiyat");
    for (int i = 0; i < 20; i++) {
        struct Card food = card[i];
        if (food.defined != 1) {
            break;
        }
        printw("%4d %30s\t%4d\n", food.quantity, food.name, food.price);
        plussing += food.price;
    }
    printw("=============================================\n");
    printw("TUTAR: %d TL\n", plussing);
    printw("=============================================\n");
    printw("Onaylamak için e, bir önceki menüye dönmek için ise için ise h tuşuna basınız");
    while (1) {
        int keyboard = getcha();
        printw("%d\n", keyboard);
        if (keyboard == 101) { // e
            // Başlat
            buy_products(desk_id, card);
            printw("Siparişiniz başarıyla alınmıştır. Lütfen siparişinizi bekleyiniz.\n");
            return;
        } else if (keyboard == 104) { // h
            draw_menu(foods, card, selected_line, card_length, el, desk_id);
            break;
        }
    }

}

struct Tuple {
    struct Card *card;
    int card_length;
} Tuple;

struct Tuple update_card(struct Card *card, int card_length, int m_food_id, int price, char name[20]) {
    for (int i = 0; i < card_length; i++) {
        struct Card data = card[i];
        if (data.defined != 1) {
            continue;
        }

        if (data.id == m_food_id) {
            card[i].quantity++;
            struct Tuple r = {card, card_length};
            return r;
        }
    }
    card[card_length].defined = 1;
    card[card_length].quantity = 1;
    card[card_length].id = m_food_id;
    card[card_length].price = price;
    strcpy(card[card_length].name, name);
    card_length++;
    struct Tuple r = {card, card_length};
    return r;
}

static void draw_menu(struct Food *foods, struct Card *card, int line, int card_length, int el, int desk_id) {
    int keyboard = 0;


    /* init_pair(1, COLOR_RED, COLOR_GREEN);
   setlocale(LC_ALL, "tr-TR");
    start_color();

    init_pair(1, COLOR_RED, COLOR_GREEN);
    attron(COLOR_PAIR(1));
    printw("Red text + Green back\n");
    attroff(COLOR_PAIR(1));

    init_pair(2, COLOR_GREEN, COLOR_WHITE); // changed id of pair
    attron(COLOR_PAIR(2));
    printw("Green text + white back\n");
    attroff(COLOR_PAIR(2));

    refresh();*/
    while (1) {
        clear_screen();
        printw("%d\n", keyboard);
        // Draw header
        printw("Menüde İstediğiniz Yemeği Seçiniz.\n");
        printw("Sepetinizde Bulunan Ürün Sayısı: ");
        attron(COLOR_PAIR(2));
        printw("%d", card_length);
        attroff(COLOR_PAIR(2));
        printw("\n");

        // Draw foods
        printw("================================================================\n");
        printw("%4s\t%4s\t%5s\t%4s\n", "id", "Kategori", "Adı", "Fiyatı");
        for (int i = 0; i < el; i++) {
            struct Food food = foods[i];
            if (line == i) {
                attron(COLOR_PAIR(1));
            }
            printw("%4d\t%4d\t%15s\t%4d\n", food.id, food.category, food.name, food.price);
            if (line == i) {
                attroff(COLOR_PAIR(1));
            }
        }

        printw("================================================================\n");
        // Draw footer
        printw("Çıkış yapmak için \"e\", ürün seçmek için \"Enter\" tuşuna basınız.\n");
        // Keyboard Control
        keyboard = getcha();

        //initscr();

        printw("%d\n", keyboard);
        struct Tuple r;
        switch (keyboard) {
            case 65: // Up arrow
                if (line != 0) {
                    line--;
                }
                keyboard = 0;
                break;
            case 66: // down arrow
                if (line != el - 1) {
                    line++;
                }
                keyboard = 0;
                break;
            case 10: // Enter
                r = update_card(card, card_length, foods[line].id, foods[line].price, foods[line].name);
                card = r.card;
                card_length = r.card_length;
                keyboard = 0;
                break;
            case 101: // "e"
                clear_screen();
                sync_card(foods, card, line, card_length, el, desk_id);
                keyboard = 0;
                return;
            default:
                break;
        }
    }
}

struct DeskData *get_desk_data(int desk_id) {
    struct DeskData *desks;
    char *sql = "SELECT status, type_id, quantity, title FROM desk_data WHERE desk_id = ? LIMIT 1;";
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_int(res, 1, desk_id);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    for (int i = 0; sqlite3_step(res) != SQLITE_DONE; i++) {
        struct DeskData desk;
        desk.status = sqlite3_column_int(res, 0);
        desk.type_id = sqlite3_column_int(res, 0);
        desk.quantity = sqlite3_column_int(res, 0);
        desk.defined = 1;
        memcpy(desk.name, sqlite3_column_text(res, 1), 20);
        desks[i] = desk;
    }
    return desks;
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