#include "igra.h"
#include "interpolacija.h"

#include <stdlib.h>
#include <stdio.h>
float nova_tocka()
{
    return (rand() % 160) + 100;
}
void nova_tocka_interpolacije(double tocke_interpolacije[][2], int n, float delta)
{
    double nove_tocke[n][2];
    for (int i = 0; i < 10; i++)
    {
        nove_tocke[i][0] = tocke_interpolacije[i + 1][0] + delta;
        nove_tocke[i][1] = -10000;
    }
    for (int i = 10; i < n - 1; i++)
    {
        nove_tocke[i][0] = tocke_interpolacije[i + 1][0] + delta;
        nove_tocke[i][1] = tocke_interpolacije[i + 1][1];
    }

    for (int i = 0; i < n - 1; i++)
    {
        tocke_interpolacije[i][0] = nove_tocke[i][0];
        tocke_interpolacije[i][1] = nove_tocke[i][1];
    }
    tocke_interpolacije[n - 1][0] = tocke_interpolacije[n - 2][0] + 500;
    tocke_interpolacije[n - 1][1] = nova_tocka();
}

void premik(float tocke_funkcije[], double tocke_interpolacije[][2], int ni, int n, float delta)
{
    if (tocke_funkcije[n - 2] + 300 >= tocke_interpolacije[ni - 1][0])
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

void nastavi_tocke(float tocke_funkcije[], double tocke_interpolacije[][2], int ni, int n, float pozicija)
{

    int st_crt = n / 4;
    float delta = 1920 / st_crt;

    while (tocke_funkcije[n - 2] >= tocke_interpolacije[ni - 1][0])
        nova_tocka_interpolacije(tocke_interpolacije, ni, 1);

    tocke_funkcije[0] = pozicija - st_crt * 5;
    tocke_funkcije[1] = f(tocke_funkcije[0], tocke_interpolacije, ni);
    tocke_funkcije[2] = pozicija - st_crt * 5 + delta;
    tocke_funkcije[3] = f(tocke_funkcije[2], tocke_interpolacije, ni);

    for (int i = 4; i < st_crt * 4; i += 4)
    {
        tocke_funkcije[i] = tocke_funkcije[i - 2];
        tocke_funkcije[i + 1] = tocke_funkcije[i - 1];

        tocke_funkcije[i + 2] = tocke_funkcije[i] + delta;
        tocke_funkcije[i + 3] = f(tocke_funkcije[i + 2], tocke_interpolacije, ni);
    }
}