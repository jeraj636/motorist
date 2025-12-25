#include "call_back.h"

int akcija[KOLIKO_AKCIJ] = {0};

void velikost_okna_callback(GLFWwindow *window, int dolzina, int visina)
{
    glViewport(0, 0, dolzina, visina);
}

void pritisk_tipke(GLFWwindow *okno, int kljuc, int scan_code, int kaj_se_je_zgodilo, int mods)
{
    for (int i = 0; i < KOLIKO_AKCIJ; i++)
    {
        akcija[i] = 0;
    }

    switch (kljuc)
    {
    case GLFW_KEY_W:
    case GLFW_KEY_UP:
        akcija[A_NAPREJ] = kaj_se_je_zgodilo;
    }
}