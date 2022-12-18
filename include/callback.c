//
// Created by ramazan akbal on 14.12.2022.
//
#include <stdio.h>
#include "callback.h"
#include "helper.h"

int callback_desk(void *NotUsed, int argc, char **argv, char **azColName) {
    NotUsed = 0;
    printf("\n----------------------------------------------------\n");
    printf("|\tBaşlık: %s\tAçıklama: %s\tDurum: %s\t|\n",
           argv[0] ? argv[0] : "NULL",
           argv[1] ? argv[1] : "NULL",
           argv[2] ? argv[2] : "NULL"
    );
    printf("----------------------------------------------------\n");

    printf("\n");

    return 1;
}

int callback_all_desk(void *NotUsed, int argc, char **argv, char **azColName) {
    NotUsed = 0;
    printf("\n----------------------------------------------------\n");
    for (int i = 0; i < argc; i++) {
        printf("%s\t\t", azColName[i]);
    }
    printf("\n");
    for (int i = 0; i < argc; i++) {
        printf("%s\t\t", argv[i] ? argv[i] : "NULL");
    }
    printf("\n----------------------------------------------------\n");

    printf("\n");

    return 1;
}

int callback_menu(void *NotUsed, int argc, char **argv, char **azColName) {
    NotUsed = 0;
    printf("\n----------------------------------------------------\n");
    printf("\tAd\t\tFiyat");
    printf("\n");
    for (int i = 0; i < argc; i++) {
        printf("%s\n",argv[i]);
        printf("%c\n",argv[i][i]);
        //printf("%s      \t", argv[i] ? argv[i] : "NULL");
    }
    printf("\n----------------------------------------------------\n");

    printf("\n");

    return 1;
}