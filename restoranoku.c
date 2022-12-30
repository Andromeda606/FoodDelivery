//
// Created by Ramazan AKBAL on 27.12.2022.
//
#include <locale.h>
#include <stdlib.h>
#include <unistd.h>
#include "stdio.h"
#include "database.h"
#include "ncurses.h"
#include "helper.h"

int draw_yes_no(int desk_id) {
    int status = 0;
    while (1) {
        clear();
        printw("%30s\n", "Sipariş Geldi!");
        printw("%30s %d\n", "Masa numarası:", desk_id);
        printw("%33s\n", "Onaylıyor musunuz?");
        if (status == 0) {
            attron(COLOR_PAIR(1));
            printw("\t%10s", "Evet");
            attroff(COLOR_PAIR(1));
            printw("\t%10s\n", "Hayır");
        } else {
            printw("\t%10s", "Evet");
            attron(COLOR_PAIR(1));
            printw("\t%10s\n", "Hayır");
            attroff(COLOR_PAIR(1));
        }

        int keyboard = getcha();
        printw("%d", keyboard);
        switch (keyboard) {
            case 67: // >
                if (status == 0) {
                    status++;
                }
                break;
            case 68: // <
                if (status == 1) {
                    status--;
                }
                break;
            case 10: // enter
                return status;
            default:
                printw("%d", keyboard);
                break;
        }
    }

}

int main() {
    setlocale(LC_ALL, "");
    while (1) {
        end();
        system("clear");
        printf("Siparişler ekrana düşecektir..\n");
        sleep(10);
        init();
        int desk_id = check_status();
        if (desk_id == 0 || desk_id == -1) {
            continue;
        }
        initscr();
        start_color();
        init_pair(1, COLOR_CYAN, COLOR_BLACK);
        //noecho();
        int status = draw_yes_no(desk_id);

        endwin();
        setvbuf(stdout, NULL, _IOLBF, 0);
        setvbuf(stderr, NULL, _IONBF, 0);

        if (!status) {
            update_status(desk_id,1);
        }else{
            update_status(desk_id,-1);
        }



    }
}

