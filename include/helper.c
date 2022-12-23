//
// Created by ramoi on 14.12.2022.
//
#include <stdlib.h>
#include <curses.h>
#include "helper.h"


void clear_screen(){
    //if (_WIN32){
        //system("cls");
    //}else{
    clear();
    //initscr();
    //}

}

int getcha(){
    int c = -1;
    while(c == -1){
        c = getch();
    }
    return c;
}