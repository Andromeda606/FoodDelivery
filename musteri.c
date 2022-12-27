#include "database.h"
#include <stdio.h>
#include <locale.h>

int main(){
    setlocale(LC_ALL, "Turkish");
    int masa;
    printf("Restoranımıza Hoş Geldiniz \n \n");
    printf("Şuanda 1,4 ve 7 numaralı masalarımız boştadır. \n \n");

    do {
        printf("\nLütfen Oturmak Istediginiz Masa Numarasini Giriniz:  ");
        scanf("%d", &masa);
        if (masa != 1 && masa != 4 && masa != 7) {
            printf("\nYanlış veya dolu masa tercihi yaptınız. Lütfen tekrar deneyin.\n");
        }
    } while (masa != 1 && masa != 4 && masa != 7);
    printf("\n%d numaralı masaya oturuyorsunuz.\n", masa);

    printf(" \nMenumuzde Bulunan Ana Yemekler; \n \n");
    printf("********Ana Yemekler******** \n \n");
    printf("Lahmacun --- Kıymalı Pide --- İskender\n");

    int anayemek;
    printf("\nLütfen Sipariş Etmek İstediğiniz Yemeği Seçiniz\n");
    printf("1. Lahmacun (15 TL)\n");
    printf("2. Kıymalı Pide (38 TL)\n");
    printf("3. İskender (45 TL)\n");
    printf("Seçtiğiniz Yemek: ");
    scanf("%d", &anayemek);

    int fiyat = 0;
    if (anayemek == 1) {
        fiyat = 15;
        printf("Seçtiğiniz Yemek: Lahmacun\n");
    }
    else if (anayemek == 2) {
        fiyat = 38;
        printf("Seçtiğiniz Yemek: Kıymalı Pide\n");
    }
    else if (anayemek == 3) {
        fiyat = 45;
        printf("Seçtiğiniz Yemek: İskender\n");
    }

    printf("Toplam tutar: %d TL\n", fiyat);

    char onay;
    int yontem;
    int kredikarti1;
    int kredikarti2;
    int kredikarti3;
    printf("Siparişinizi onaylıyor musunuz? (E veya H) ");
    scanf(" %c", &onay);
    if (onay == 'E' || onay == 'e') {
        printf("Sipariş onaylandı.\n");
        printf("Lütfen ödeme yöntemini seçin:\n");
        printf("1. Nakit\n");
        printf("2. Kredi Kartı\n");
        scanf("%d", &yontem);
        if(yontem == 1) {
        	printf("Ödeme Yöntemi Kabul Edildi.");
            printf("Garson Siparişinizi Birazdan Getirecek.");
        }
        else if (yontem == 2) {
        	printf("Lütfen Kredi Kartı Bilgilerini Giriniz.\n");
        	printf("Kredi Kartınızın 16 Hanesini Giriniz: ");
        	scanf("%d", &kredikarti1);
        	printf("Kredi Kartınızın Son Kullanım Tarihini Yazınız: (10/25 Şeklinde)");
        	scanf("%d", &kredikarti2);
        	printf("Kredi Kartınızın Arka Kısmında Bulunan CVV Kodunu Yazınız: ");
        	scanf("%d", &kredikarti3);
        	printf("Ödeme Yöntemi Kabul Edildi.\n");
        	printf("Garson Siparişinizi Birazdan Getirecek.");
            printf("denemedenemedeneme")
		}
    } else {
        printf("Sipariş iptal edildi.\n");
    }


    return 0;
}