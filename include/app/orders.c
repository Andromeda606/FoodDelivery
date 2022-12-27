//
// Created by Ramazan AKBAL on 26.12.2022.
//
#include "ncurses.h"
#include <helper.h>
#include <stdlib.h>
#include "orders.h"
#include "string.h"
#include "database.h"

char *sync_status(int status) {
    switch (status) {
        case 0:
            return "Onaylandı";
        case 1:
            return "Hazırlanıyor";
        case 2:
            return "Yolda";
        case 3:
            return "Teslim edildi";
        default:
            return "Bilinmiyor";
    }
}

void draw_orders(struct Order orders[20], int length, int current_line) {
    int keyboard;
    while (1) {
        clear_screen();
        // Draw header
        printw("Siparişler arasında seçim yapınız.\n");

        // Draw foods
        printw("================================================================\n");
        printw("%7s\t%10s\n", "Masa nu", "Durum");
        for (int i = 0; i < length; i++) {
            struct Order order = orders[i];
            char status[20];
            strcpy(status, sync_status(order.status));

            if (current_line == i) {
                attron(COLOR_PAIR(1));
                printw("%7d\t%15s", order.desk_id, status);
                attroff(COLOR_PAIR(1));
                attron(COLOR_PAIR(2));
                printw("\t%15s", sync_status(order.status + 1));
                attroff(COLOR_PAIR(2));
                printw("\n");
            } else {
                printw("%7d\t%15s\n", order.desk_id, status);
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

        keyboard = getch();
        switch (keyboard) {
            case 65: // Up arrow
                if (current_line != 0) {
                    current_line--;
                }
                break;
            case 66: // down arrow
                if (current_line != length - 1) {
                    current_line++;
                }
                break;
            case 67: // >
                update_status(orders[current_line].desk_id, orders[current_line].status + 1);
                show_orders(current_line);
                break;
            case 101: // "e"
                /*clear_screen();
                sync_card(foods, card, line, card_length, el, desk_id, categories);
                keyboard = 0;*/
                break;
            default:
                break;
        }
    }
}