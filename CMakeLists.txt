cmake_minimum_required(VERSION 3.23)
project(Restoran)
project(Musteri)
project(LibraryTest)

set(CMAKE_CXX_STANDARD 14)

include_directories(sqlite)
include_directories(include)
include_directories(include/app)
include_directories(include/system)

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

        include/app/mode.c include/app/mode.h)