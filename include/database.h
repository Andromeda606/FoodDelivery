//
// Created by ramazan akbal on 14.12.2022.
//

#ifndef RESTORANTAKIP_DATABASE_H
#define RESTORANTAKIP_DATABASE_H
#define TEST            1
#define MAX_FOOD_LENGTH 20

void init(); // Veritabanı Başlatır
void print_desk(char desk_id[]); // Seçili masayı ekrana yazdırır
void get_desks(); // Bütün masaları ekrana yazdırır
int login(char username[], char password[]); // Giriş yapar
void show_menu(int desk_id); //Menüyü gösterir. Sipariş tamamlandığında bitirir.
struct DeskData *get_desk_data(int desk_id); // Masa verisini verir, çıktı DeskData olduğundan istediğiniz yemeğe bakabilirsiniz.
#endif
