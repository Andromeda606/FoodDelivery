cmake_minimum_required(VERSION 3.22)
project(Restoran)
project(Musteri)
project(LibraryTest)
project(RestoranOku)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(include/app)
include_directories(include/system)

find_library (libsqlite3.so SHARED)
add_executable(
        Restoran
        restoran.c
        include/callback.h
        include/database.h
        include/helper.h
        include/struct.h
        include/app/menu.h
        include/callback.c
        include/database.c
        include/helper.c
        include/app/menu.c
        include/app/orders.c)

add_executable(
        Musteri
        musteri.c
        include/callback.h
        include/database.h
        include/helper.h
        include/struct.h
        include/app/menu.h
        include/callback.c
        include/database.c
        include/helper.c
        include/app/menu.c
        include/app/orders.c)

add_executable(
        LibraryTest
        librarytest.c
        include/callback.h
        include/database.h
        include/helper.h
        include/struct.h
        include/app/menu.h
        include/callback.c
        include/database.c
        include/helper.c
        include/app/menu.c
        include/app/orders.c
)

add_executable(
        RestoranOku
        restoranoku.c
        include/callback.h
        include/database.h
        include/helper.h
        include/struct.h
        include/app/menu.h
        include/callback.c
        include/database.c
        include/helper.c
        include/app/menu.c
        include/app/orders.c
)


target_link_libraries(LibraryTest sqlite3)
target_link_libraries(LibraryTest ncurses)

target_link_libraries(Musteri sqlite3)
target_link_libraries(Musteri ncurses)

target_link_libraries(Restoran sqlite3)
target_link_libraries(Restoran ncurses)

target_link_libraries(RestoranOku sqlite3)
target_link_libraries(RestoranOku ncurses)
