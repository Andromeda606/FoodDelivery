cmake_minimum_required(VERSION 3.22)
project(Restoran)
project(Musteri)
project(LibraryTest)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(include/app)
include_directories(include/system)
#include_directories(/usr/lib/x86_64-linux-gnu/)
#link_libraries(/usr/lib/x86_64-linux-gnu/)
#link_directories(/usr/lib/x86_64-linux-gnu)
find_library (libsqlite3.so SHARED)
add_executable(
        Restoran
        restoran.c
        include/callback.c
        include/callback.h
        include/database.h
        include/database.c
        include/helper.c)

add_executable(
        Musteri
        musteri.c
        include/callback.c
        include/callback.h
        include/database.h
        include/database.c
        include/helper.c)

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
)


target_link_libraries(LibraryTest sqlite3)
target_link_libraries(LibraryTest ncurses)
target_link_libraries(Musteri sqlite3)
target_link_libraries(Musteri ncurses)
target_link_libraries(Restoran sqlite3)
target_link_libraries(Restoran ncurses)
