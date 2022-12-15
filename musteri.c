#include "database.h"
#include <stdio.h>
#include <locale.h>

int main(){
    setlocale(LC_ALL, "Turkish");
    printf("Restoran Kayıt Sistemi - Müşteri\n");
    init();


    return 0;
}