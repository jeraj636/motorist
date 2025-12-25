#include "matrika.h"
#include <stdio.h>
#include <math.h>

void enotska(float mat[][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (j == i)
                mat[i][j] = 1.0;
            else
                mat[i][j] = 0.0;
}
void orto3(float mat[][3], float levo, float desno, float gor, float dol)
{
    mat[0][0] = 2 / (desno - levo);
    mat[1][1] = 2 / (gor - dol);
    mat[0][2] = -(desno + levo) / (desno - levo);
    mat[1][2] = -(gor + dol) / (gor - dol);
}

void kamera3(float mat[][3], float pozicija)
{
    enotska(mat);
    mat[0][2] = -pozicija;
}
void vel3(float mat[][3], float x, float y)
{
    enotska(mat);
    mat[0][0] = x;
    mat[1][1] = y;
}

void poz3(float mat[][3], float x, float y)
{
    enotska(mat);
    mat[0][2] = x;
    mat[1][2] = y;
}

void rot3(float mat[][3], float kot)
{
    enotska(mat);
    mat[0][0] = cos(kot);
    mat[0][1] = -sin(kot);
    mat[1][0] = sin(kot);
    mat[1][1] = cos(kot);
}