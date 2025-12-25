#ifndef MATRIKA_H
#define MATRIKA_H
void enotska(float mat[][3]);

void orto3(float mat[][3], float levo, float desno, float gor, float dol);
void kamera3(float mat[][3], float pozicija);
void poz3(float mat[][3], float x, float y);
void vel3(float mat[][3], float x, float y);
void rot3(float mat[][3], float kot);

#endif