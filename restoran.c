#include "database.h"
#include <stdio.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Turkish");
    printf("Restoran Giriş Sistemi\n");
    init();
    //Buradan itibaren yazılacak

    //get_desks();
    print_desk("1");
    return 0;
}
