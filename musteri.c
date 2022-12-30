#include "database.h"
#include "helper.h"
#include <stdio.h>
#include <locale.h>
#include <unistd.h>

void show_menu_data(int desk_id){
    show_menu(desk_id);

    setvbuf(stdout, NULL, _IOLBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
   //end();
    while(1){
        sleep(9);
        clear_screen();
        init();
        int desk_status = get_desk_status(desk_id);
        end();
        switch (desk_status) {
            case -1:
                printf("Sipariş Daha Onaylanmadı...\n");
                continue;
            case 1:
                printf("Sipariş Onaylandı, hazırlanıyor..\n");
                continue;
            case 2:
                printf("Sipariş Hazırlandı, Getiriliyor..\n");
                continue;
            case 3:
                printf("Sipariş Getirildi, Afiyet olsun.\n");
                return;
        }
    }
}
void show_menu_data(int desk_id);


int main(){
    setlocale(LC_ALL, "");
    init();
    int masa;
    printf("Restoranımıza Hoş Geldiniz \n \n");
    printf("Şuanda 1,4 ve 7 numaralı masalarımız boştadır. \n \n");

    printf("\nLütfen Oturmak Istediginiz Masa Numarasini Giriniz:  ");
    scanf("%d", &masa);
    printf("\n%d numaralı masaya oturuyorsunuz.\n", masa);
    sleep(1);

    show_menu_data(masa);


    return 0;
}

