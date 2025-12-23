#include "call_back.h"
void velikost_okna_callback(GLFWwindow *window, int dolzina, int visina)
{
    glViewport(0, 0, dolzina, visina);
}