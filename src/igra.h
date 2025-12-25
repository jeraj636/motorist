#ifndef IGRA_H
#define IGRA_H
void nastavi_tocke(float tocke_funkcije[], double tocke_interpolacije[][2], int ni, int n, float pozicija);
void premik(float tocke_funkcije[], double tocke_interpolacije[][2], int ni, int n, float delta);
void nova_tocka_interpolacije(double tocke_interpolacije[][2], int n, float delta);
float nova_tocka();

#endif