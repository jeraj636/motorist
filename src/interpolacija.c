#include "interpolacija.h"

#include <stdio.h>

double f(double x, double tabela_y[], int tabela_x[], int n)
{
    double vrednost = 0;
    for (int i = 0; i < n; i++)
    {
        double zmnozek = tabela_y[i];
        for (int j = 0; j < n; j++)
            if (j != i)
            {
                zmnozek *= (x - tabela_x[j]) / (tabela_x[i] - tabela_x[j]);
            }
        vrednost += zmnozek;
    }
    return vrednost;
}