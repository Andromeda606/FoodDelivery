//
// Created by ramoi on 17.12.2022.
//
#include "database.h"
#include "helper.h"
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

int main() {
    setlocale(LC_ALL, "tr-TR");
    init();
    //printf("Deneme\n");
    //printf("Adasd: %d\n", getcha());
    show_menu(4);
    system("PAUSE");
}