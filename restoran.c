#include "database.h"
#include <stdio.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Turkish");
    printf("Restoran Giriş Sistemi\n");
    init();
    //Buradan itibaren yazılacak
    if(login("admin","admin")){
        printf("Başarıyla giriş yapıldı\n");
    }else{
        printf("Giriş başarısız\n");
    }
    //get_desks();
    print_desk("1");
    return 0;
}
