//
// Created by ramoi on 17.12.2022.
//

#ifndef LIBRARYTEST_STRUCT_C
#define LIBRARYTEST_STRUCT_C
struct Food;
struct Card;
struct Category;
struct Order;

typedef struct Food {
    int id, category, price, defined;
    char name[20];
} Food;

typedef struct Card {
    int id, quantity, defined, price;
    char name[20];

} Card;

typedef struct Category {
    int id;
    char text[20];
} Category;

typedef struct DeskData {
    int status, type_id, quantity, defined;
    char name[20];
} DeskData;

typedef struct Order {
    int status, desk_id;
} Order;

#endif //LIBRARYTEST_STRUCT_C
