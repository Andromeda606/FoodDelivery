cmake_minimum_required(VERSION 3.24)
project(RestoranTakip)

set(CMAKE_CXX_STANDARD 14)

include_directories(sqlite)
include_directories(include)

add_executable(
        RestoranTakip
        main.c
        include/callback.c
        include/callback.h
        include/database.h
        include/database.c
        )
