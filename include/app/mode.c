//
// Created by ramoi on 18.12.2022.
//
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>
#include <stdio.h>

void enable_raw_mode() {
    DWORD my_id = GetCurrentProcessId();
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("%d\n", SetConsoleMode(hStdOut, 0));
}