#include "igra.h"
#include "interpolacija.h"

#include <stdlib.h>
#include <stdio.h>

void nova_tocka_interpolacije(double tocke_interpolacije[][2], int n, int smer)
{
    if (smer == 1)
    {
        for (int i = 1; i < n; i++)
        {
            tocke_interpolacije[i - 1][0] = tocke_interpolacije[i][0];
            tocke_interpolacije[i - 1][1] = tocke_interpolacije[i][1];
        }
        tocke_interpolacije[n - 1][0] = tocke_interpolacije[n - 2][0] + 192;
        tocke_interpolacije[n - 1][1] = (rand() % 150) + 100;
    }
    for (int i = 0; i < n; i++)
    {
        printf("(%i  %i)", (int)tocke_interpolacije[i][0], (int)tocke_interpolacije[i][1]);
    }
    printf("\n");
}

void premik(float tocke_funkcije[], double tocke_interpolacije[][2], int ni, int n, float delta)
{
    if (tocke_funkcije[n - 2] >= tocke_interpolacije[ni - 1][0])
    {
        nova_tocka_interpolacije(tocke_interpolacije, ni, 1);
        printf("%f\n", tocke_funkcije[n - 2]);
    }
    for (int i = 0; i < n; i += 2)
    {
        tocke_funkcije[i] += delta;
        tocke_funkcije[i + 1] = f(tocke_funkcije[i], tocke_interpolacije, ni);
    }
}
