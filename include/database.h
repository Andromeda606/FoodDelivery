//
// Created by ramazan akbal on 14.12.2022.
//

#ifndef RESTORANTAKIP_DATABASE_H
#define RESTORANTAKIP_DATABASE_H
#define TEST    1
void init(); // Veritabanı Başlatır
void print_desk(char desk_id[]); // Seçili masayı ekrana yazdırır
void get_desks(); // Bütün masaları ekrana yazdırır
int login(char username[], char password[]); // Giriş yapar
#endif
