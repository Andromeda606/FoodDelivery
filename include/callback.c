//
// Created by ramazan akbal on 14.12.2022.
//
#include <stdio.h>
#include "callback.h"
int callback_desk(void *NotUsed, int argc, char **argv, char **azColName) {
    NotUsed = 0;
    printf("----------------------------------------------------\n");
    printf("|   Başlık: %s     Açıklama: %s     Durum: %s   |\n", argv[0] ? argv[0] : "NULL",argv[1] ? argv[1] : "NULL",argv[2] ? argv[2] : "NULL");
    printf("----------------------------------------------------\n");

    printf("\n");

    return 1;
}