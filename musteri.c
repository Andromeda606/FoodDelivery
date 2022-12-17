#include "database.h"
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

int main() {
    setlocale(LC_ALL, "Turkish");
    printf("Restoran Kayıt Sistemi - Müşteri\n");
    init();
    printf("Restoranımıza Hoşgeldiniz!\n");
    int masa;
    while(1){
        printf("Lütfen masa seçimi yapınız.\n");
        scanf("%d", &masa);
        if (masa > 12) {
            printf("Masa maksimum 12 olabilir!\n");
        }
        break;
    }



    return 0;
}