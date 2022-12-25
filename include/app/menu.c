//
// Created by ramoi on 17.12.2022.
//
#include <stdlib.h>
#include <stdio.h>
#include <helper.h>
#include "menu.h"
#include "database.h"
#include "string.h"
#include "ncurses.h"


static void sync_card(struct Food *foods, struct Card *card, int selected_line, int card_length, int el, int desk_id,
                      struct Category *categories) {
    printw("Sepetinizin içeriği, onaylıyor musunuz?\n");
    printw("=============================================\n");
    int plussing = 0;
    printw("%4s\t%20s\t%13s\n", "Adet", "Adı", "Fiyat");
    for (int i = 0; i < 20; i++) {
        struct Card food = card[i];
        if (food.defined != 1 || food.price > 4000 || food.price <= 0 || food.quantity > 5000) {
            continue;
        }
        printw("%4d\t%2s\t%20s\t%4d\n", food.quantity,"", food.name, food.price);
        plussing += food.price * food.quantity;
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
            draw_menu(foods, card, selected_line, card_length, el, desk_id, categories);
            break;
        }
    }

}

struct Tuple {
    struct Card *card;
    int card_length;
} Tuple;

struct Tuple update_card(struct Card *card, int card_length, int m_food_id, int price, char name[20], int num) {
    for (int i = 0; i < card_length; i++) {
        struct Card data = card[i];
        if (data.defined != 1) {
            continue;
        }

        if (data.id == m_food_id) {
            if(num == -1 && card[i].quantity == 1){
                card[i].defined = 0;
                struct Tuple r = {card, card_length - 1};
                return r;
            }
            card[i].quantity = card[i].quantity + num;
            struct Tuple r = {card, card_length};
            return r;
        }
    }
    if(num == -1){
        struct Tuple r = {card, card_length};
        return r;
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

void draw_menu(struct Food *foods, struct Card *card, int line, int card_length, int el, int desk_id,
               struct Category *categories) {
    int keyboard = 0;

    while (1) {
        int category_status = 0;
        int title = 0;
        clear_screen();
        // Draw header
        printw("Menüde İstediğiniz Yemeği Seçiniz.\n");
        printw("Sepetinizde Bulunan Ürün Sayısı: ");
        attron(COLOR_PAIR(2));
        printw(" %d ", card_length);
        attroff(COLOR_PAIR(2));
        printw("\n");

        // Draw foods
        printw("================================================================\n");
        printw("%10s\t%15s\t%20s\n", "id", "Adı", "Fiyatı");
        for (int i = 0; i < el; i++) {
            struct Food food = foods[i];
            if (category_status != food.category) {
                attron(COLOR_PAIR(3));
                printw("\n================================================================\n");
                printw("%35s\n", categories[food.category].text);
                printw("================================================================\n\n");
                category_status = food.category;
                attroff(COLOR_PAIR(3));
            }
            if (line == i) {
                attron(COLOR_PAIR(1));
            }
            printw("%10d\t%20s\t%10d\n", food.id, food.name, food.price);
            if (line == i) {
                attroff(COLOR_PAIR(1));
            }
        }

        printw("================================================================\n");
        // Draw footer
        printw("Çıkış yapmak için \"");
        attron(COLOR_PAIR(3));
        printw("e");
        attroff(COLOR_PAIR(3));
        printw("\"\nürün seçmek için \"");
        attron(COLOR_PAIR(3));
        printw(">");
        attroff(COLOR_PAIR(3));
        printw("\"\nÜrün silmek için \"");
        attron(COLOR_PAIR(3));
        printw("<");
        attroff(COLOR_PAIR(3));
        printw("\" tuşuna basınız.\n");
        // Keyboard Control
        keyboard = getcha();

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
            case 67: // >
                r = update_card(card, card_length, foods[line].id, foods[line].price, foods[line].name, 1);
                card = r.card;
                card_length = r.card_length;
                keyboard = 0;
                break;
            case 68: // <
                r = update_card(card, card_length, foods[line].id, foods[line].price, foods[line].name, -1);
                card = r.card;
                card_length = r.card_length;
                keyboard = 0;
                break;
            case 101: // "e"
                clear_screen();
                sync_card(foods, card, line, card_length, el, desk_id, categories);
                keyboard = 0;
                return;
            default:
                break;
        }
    }
}


