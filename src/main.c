#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "call_back.h"
#include "interpolacija.h"
#include "matrika.h"
#include "shaderji.h"
#include "igra.h"
const char *vertex_shader_crte_p =
    "#version 330 core\n"
    "layout (location = 0) in vec2 aPos;\n"
    "uniform mat3 projekcija;\n"
    "uniform mat3 kamera;\n"
    "uniform mat3 velikost;\n"
    "uniform mat3 pozicija;\n"
    "uniform mat3 rotacija;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(projekcija * kamera*pozicija *rotacija*velikost* vec3(aPos,1.0),1.0);\n"
    "}\n\0";

const char *fragment_shader_crte_p =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = vec4(1.0);\n"
    "}\n\0";

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *okno = glfwCreateWindow(1920, 1080, "Motorist", NULL, NULL);

    if (okno == NULL)
    {
        printf("Okno ne dela\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(okno);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Ni ratal zrihtat GLAD\n");
        return -1;
    }
    glViewport(0, 0, 1920, 1080);

    glfwSetFramebufferSizeCallback(okno, velikost_okna_callback);
    glfwSetKeyCallback(okno, pritisk_tipke);

    int vel_tock = 90;
    srand(time(NULL));
    double tocke_za_interpolacijo[vel_tock][2];
    for (int i = 0; i < vel_tock; i++)
    {
        tocke_za_interpolacijo[i][0] = i * 500 - 500 * 45;
        tocke_za_interpolacijo[i][1] = nova_tocka();
    }
    float tockice[192 * 2 * 2 * 2];
    float pozicija_igralca = 1920 / 2;
    float lokalni_premik = 0;
    nastavi_tocke(tockice, tocke_za_interpolacijo, vel_tock, 192 * 8, pozicija_igralca);

    float tocke_kvadrat[6 * 2] = {
        -0.5, 0.5,
        0.5, 0.5,
        -0.5, -0.5,
        -0.5, -0.5,
        0.5, 0.5,
        0.5, -0.5};

    float projekcija[3][3];
    float kamera[3][3];
    float velikost[3][3];
    float pozicija[3][3];
    float roatacija[3][3];

    unsigned int vao_crte, vbo_crte;
    glGenVertexArrays(1, &vao_crte);
    glGenBuffers(1, &vbo_crte);

    glBindVertexArray(vao_crte);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_crte);

    glBufferData(GL_ARRAY_BUFFER, sizeof(tockice), tockice, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    unsigned int vao_kvadrat, vbo_kvadrat;
    glGenVertexArrays(1, &vao_kvadrat);
    glGenBuffers(1, &vbo_kvadrat);

    glBindVertexArray(vao_kvadrat);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_kvadrat);

    glBufferData(GL_ARRAY_BUFFER, sizeof(tocke_kvadrat), tocke_kvadrat, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    unsigned int program_za_crte = naredi_program(vertex_shader_crte_p, fragment_shader_crte_p);

    double zac_okna, delta_t;
    kamera3(kamera, pozicija_igralca);
    float pospesek = 100;
    float hitrost = 0;
    float omejitve = 0;
    int zacatek = 1;
    while (!glfwWindowShouldClose(okno))
    {
        zac_okna = glfwGetTime();
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        if (akcija[A_NAPREJ] != 0 || 1)
        {
            hitrost += (pospesek + omejitve) * delta_t;
            zacatek = 0;
        }
        else
        {
            hitrost += -omejitve * delta_t;
        }
        if (hitrost > 500)
            hitrost = 500 * hitrost / abs(hitrost);

        hitrost = 2000;
        pozicija_igralca += hitrost * delta_t;
        lokalni_premik += hitrost * delta_t;
        while (lokalni_premik >= 500)
        {
            lokalni_premik -= 500;
            nova_tocka_interpolacije(tocke_za_interpolacijo, vel_tock, lokalni_premik);
        }
        nastavi_tocke(tockice, tocke_za_interpolacijo, vel_tock, 192 * 8, pozicija_igralca);
        kamera3(kamera, pozicija_igralca - 1920);
        orto3(projekcija, 0, 1920, 1080, 0);
        enotska(velikost);
        enotska(pozicija);
        enotska(roatacija);
        // Risanje črt

        glUseProgram(program_za_crte);

        glBindVertexArray(vao_crte);

        glBindBuffer(GL_ARRAY_BUFFER, vbo_crte);
        glBufferData(GL_ARRAY_BUFFER, sizeof(tockice), tockice, GL_DYNAMIC_DRAW);

        glUniformMatrix3fv(glGetUniformLocation(program_za_crte, "projekcija"), 1, GL_TRUE, &projekcija[0][0]);
        glUniformMatrix3fv(glGetUniformLocation(program_za_crte, "kamera"), 1, GL_TRUE, &kamera[0][0]);
        glUniformMatrix3fv(glGetUniformLocation(program_za_crte, "velikost"), 1, GL_TRUE, &velikost[0][0]);
        glUniformMatrix3fv(glGetUniformLocation(program_za_crte, "pozicija"), 1, GL_TRUE, &pozicija[0][0]);
        glUniformMatrix3fv(glGetUniformLocation(program_za_crte, "rotacija"), 1, GL_TRUE, &roatacija[0][0]);

        glDrawArrays(GL_LINES, 0, sizeof(tockice) / sizeof(float));

        // Risanje kvadrata
        glBindVertexArray(vao_kvadrat);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_kvadrat);
        vel3(velikost, 40, 20);
        float k_t = (f(pozicija_igralca - 1920 / 2 + 20, tocke_za_interpolacijo, vel_tock) - f(pozicija_igralca - 1920 / 2 - 20, tocke_za_interpolacijo, vel_tock)) / 40;
        omejitve = 140 * k_t;
        poz3(pozicija, pozicija_igralca - 1920 / 2, f(pozicija_igralca - 1920 / 2, tocke_za_interpolacijo, vel_tock) + 15);
        rot3(roatacija, atan(k_t));
        glUniformMatrix3fv(glGetUniformLocation(program_za_crte, "projekcija"), 1, GL_TRUE, &projekcija[0][0]);
        glUniformMatrix3fv(glGetUniformLocation(program_za_crte, "kamera"), 1, GL_TRUE, &kamera[0][0]);
        glUniformMatrix3fv(glGetUniformLocation(program_za_crte, "velikost"), 1, GL_TRUE, &velikost[0][0]);
        glUniformMatrix3fv(glGetUniformLocation(program_za_crte, "pozicija"), 1, GL_TRUE, &pozicija[0][0]);
        glUniformMatrix3fv(glGetUniformLocation(program_za_crte, "rotacija"), 1, GL_TRUE, &roatacija[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(okno);
        glfwPollEvents();
        delta_t = glfwGetTime() - zac_okna;
    }

    glfwTerminate();
    return 0;
}
