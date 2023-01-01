#include <database.h>
#include <helper.h>
#include <stdio.h>
#include <locale.h>
#include <ncurses.h>

int main() {
    setlocale(LC_ALL, "");
    printf("Restoran Giriş Sistemi\n");
    init();
    //Buradan itibaren yazılacak
    while (1){
        printf("Kullanıcı adı giriniz: ");
        char username[250];
        scanf("%s", username);
        printf("Şifre giriniz: ");
        char password[250];
        scanf("%s", password);
        if (login(username, password)) {
            printf("Başarıyla giriş yapıldı\n");
            break;
        } else {
            printf("Giriş başarısız\n");
            continue;
        }
    }

    while (1){
        initscr();
        printw("Siparişlere erişmek için 1 e bas.\n");
        int keyboard = getcha();
        if(keyboard == 49){ // 1
            show_orders(0);
        }
    }
}
