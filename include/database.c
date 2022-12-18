#include <stdio.h>
#include "sqlite3.c"
#include "callback.h"
#include "database.h"
#include <conio.h>
#include <helper.h>
#include "menu.h"

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
    printf("\n");


}

static void sync_card(struct Food *foods, struct Card *card, int selected_line, int card_length, int el, int desk_id) {
    printf("Sepetinizin içeriği, onaylıyor musunuz?\n");
    printf("=============================================\n");
    int plussing = 0;
    printf("%4s %30s\t%4s\n", "Adet", "Adı", "Fiyat");
    for (int i = 0; i < 20; i++) {
        struct Card food = card[i];
        if (food.defined != 1) {
            break;
        }
        printf("%4d %30s\t%4d\n", food.quantity, food.name, food.price);
        plussing += food.price;
    }
    printf("=============================================\n");
    printf("TUTAR: %d TL\n", plussing);
    printf("=============================================\n");
    printf("Onaylamak için e, bir önceki menüye dönmek için ise için ise h tuşuna basınız");
    while (1) {
        int keyboard = getch();
        if (keyboard == 101) { // e
            // Başlat
            buy_products(desk_id, card);
            printf("Siparişiniz başarıyla alınmıştır. Lütfen siparişinizi bekleyiniz.\n");
            return;
        } else if (keyboard == 104) { // h
            draw_menu(foods, card, selected_line, card_length, el, desk_id);
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
    while (1) {
        system("cls");
        // Draw header
        printf("Menüde İstediğiniz Yemeği Seçiniz.\n");
        printf("Sepetinizde Bulunan Ürün Sayısı: "ANSI_COLOR_CYAN "%d" ANSI_COLOR_RESET "\n", card_length);

        // Draw foods
        printf("================================================================\n");
        printf("%4s\t%4s\t%5s\t%4s\n", "id", "Kategori", "Adı", "Fiyatı");
        for (int i = 0; i < el; i++) {
            struct Food food = foods[i];
            if (line == i) {
                printf(ANSI_COLOR_GREEN);
            }
            printf("%4d\t%4d\t%15s\t%4d\n", food.id, food.category, food.name, food.price);
            if (line == i) {
                printf(ANSI_COLOR_RESET);
            }
        }

        printf("================================================================\n");
        // Draw footer
        printf("Çıkış yapmak için \"e\", ürün seçmek için \"Enter\" tuşuna basınız.\n");
        // Keyboard Control
        int keyboard = getch();
        system("cls");
        printf("%d\n", keyboard);
        struct Tuple r;
        switch (keyboard) {
            case 72: // Up arrow
                if (line != 0) {
                    line--;
                }
                break;
            case 80: // down arrow
                if (line != el - 1) {
                    line++;
                }
                break;
            case 13: // Enter
                r = update_card(card, card_length, foods[line].id, foods[line].price, foods[line].name);
                card = r.card;
                card_length = r.card_length;
                break;
            case 101: // "e"
                system("cls");
                sync_card(foods, card, line, card_length, el, desk_id);
                return;
            default:
                break;
        }
    }
}

struct DeskData *get_desk_data(int desk_id){
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