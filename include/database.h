//
// Created by ramazan akbal on 14.12.2022.
//

#ifndef RESTORANTAKIP_DATABASE_H
#define RESTORANTAKIP_DATABASE_H
#define TEST            1
#define MAX_FOOD_LENGTH 20
#include "struct.h"


/**
 * Veritabanını başlatır. İşlemler için öncelikle bunu kullanmak gerekli!
 */
void init();

/**
 * Bütün masaları ekrana yazdırır
 */
void get_desks();


/**
 * @param desk_id
 * Desk id listesi verildiğinde bu listeyi sunucuda aratır ve ekrana masaları yazar.
 */
void print_desk(char desk_id[]);

/**
 * @param username
 * @param password
 * @return başarılıysa 1, başarısızsa 0
 *
 * Giriş yapar, 0 veya 1 döner.
 */
int login(char username[], char password[]); // Giriş yapar

/**
 * @param desk_id
 * @return masa durumu
 *
 * Masa verisini alır. int olarak sipariş durumunu döndürür.
 */
int get_desk_status(int desk_id);


/**
 * @param desk_id
 * Menüyü gösterir. Verilen desk id ye siparişleri onaylatır.
 */
void show_menu(int desk_id);

void buy_products(int desk_id, struct Card *cards);

/*
 * Geliştirme İçin hazırlanan kodlar
 */

#endif
