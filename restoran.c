#include "database.h"
#include <stdio.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "");
    printf("Restoran Giriş Sistemi\n");
    init();
    //Buradan itibaren yazılacak
    if(login("admin","admin")){
        printf("Başarıyla giriş yapıldı\n");
    }else{
        printf("Giriş başarısız\n");
    }
    show_orders(0);
    return 0;
}
