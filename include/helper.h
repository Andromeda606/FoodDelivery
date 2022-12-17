//
// Created by Ramazan AKBAL on 15.12.2022.
//

#ifndef MUSTERI_HELPER_H
#define MUSTERI_HELPER_H
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define BLUE(string) ANSI_COLOR_BLUE string ANSI_COLOR_RESET
#define RED(string) ANSI_COLOR_RED string ANSI_COLOR_RESET
#define CYAN(string) ANSI_COLOR_CYAN string ANSI_COLOR_RESET
#define MAGENTA(string) ANSI_COLOR_MAGENTA string ANSI_COLOR_RESET
#define YELLOW(string) ANSI_COLOR_YELLOW string ANSI_COLOR_RESET
#define GREEN(string) ANSI_COLOR_GREEN string ANSI_COLOR_RESET


#endif //MUSTERI_HELPER_H
