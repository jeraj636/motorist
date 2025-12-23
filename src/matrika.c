#include "matrika.h"
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