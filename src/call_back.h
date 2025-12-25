#ifndef CALLBACK_H
#define CALLBACK_H

#include <GLFW/glfw3.h>

#define A_NAPREJ 0
#define A_POSPESEK 1
#define A_BREMZA 2

#define KOLIKO_AKCIJ 3
extern int akcija[KOLIKO_AKCIJ];

void velikost_okna_callback(GLFWwindow *window, int dolzina, int visina);
void pritisk_tipke(GLFWwindow *okno, int kljuc, int scan_code, int kaj_se_je_zgodilo, int mods);
#endif