#include "interpolacija.h"

#include <stdio.h>

double f(double x, double tabela[][2], int n)
{
    double vrednost = 0;
    for (int i = 0; i < n; i++)
    {
        double zmnozek = tabela[i][1];
        for (int j = 0; j < n; j++)
            if (j != i)
            {
                zmnozek *= (x - tabela[j][0]) / (tabela[i][0] - tabela[j][0]);
            }
        vrednost += zmnozek;
    }
    return vrednost;
}