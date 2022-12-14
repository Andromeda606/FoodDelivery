cmake_minimum_required(VERSION 3.24)
project(Restoran)
project(Musteri)

set(CMAKE_CXX_STANDARD 14)

include_directories(sqlite)
include_directories(include)

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