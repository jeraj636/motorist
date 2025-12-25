#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    "void main()\n"
    "{\n"
    "gl_Position = vec4(projekcija * kamera * vec3(aPos,1.0),1.0);\n"
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

    int vel_tock = 20;
    srand(time(NULL));
    double tocke_za_interpolacijo[vel_tock][2];
    for (int i = 0; i < vel_tock; i++)
    {
        tocke_za_interpolacijo[i][0] = i * 192 - 192 * 4;
        tocke_za_interpolacijo[i][1] = (rand() % 150) + 100;
    }
    float tockice[192 * 2 * 2];

    tockice[0] = 0;
    tockice[1] = f(tockice[0], tocke_za_interpolacijo, vel_tock);
    tockice[2] = 10;
    tockice[3] = f(tockice[2], tocke_za_interpolacijo, vel_tock);
    for (int i = 4; i < 192 * 4; i += 4)
    {
        tockice[i] = tockice[i - 2];
        tockice[i + 1] = tockice[i - 1];

        tockice[i + 2] = tockice[i] + 10;
        tockice[i + 3] = f(tockice[i + 2], tocke_za_interpolacijo, vel_tock);
        if (tockice[i + 3] < 20)
            tockice[i + 3] = 20;
    }

    float projekcija[3][3];
    float kamera[3][3];

    unsigned int vao_crte, vbo_crte;
    glGenVertexArrays(1, &vao_crte);
    glGenBuffers(1, &vbo_crte);

    glBindVertexArray(vao_crte);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_crte);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tockice), tockice, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    unsigned int program_za_crte = naredi_program(vertex_shader_crte_p, fragment_shader_crte_p);

    double zac_okna, delta_t;
    float pozicija_igralca = -1920 / 2;
    kamera3(kamera, pozicija_igralca);

    while (!glfwWindowShouldClose(okno))
    {
        zac_okna = glfwGetTime();
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        if (akcija[A_NAPREJ] != 0)
        {
            premik(tockice, tocke_za_interpolacijo, 20, 192 * 4, 100 * delta_t);
            pozicija_igralca += 100 * delta_t;
            kamera3(kamera, pozicija_igralca);
            glBufferData(GL_ARRAY_BUFFER, sizeof(tockice), tockice, GL_DYNAMIC_DRAW);
        }
        // Risanje črt
        orto3(projekcija, 0, 1920, 1080, 0);

        glUseProgram(program_za_crte);
        glUniformMatrix3fv(glGetUniformLocation(program_za_crte, "projekcija"), 1, GL_TRUE, &projekcija[0][0]);
        glUniformMatrix3fv(glGetUniformLocation(program_za_crte, "kamera"), 1, GL_TRUE, &kamera[0][0]);

        glDrawArrays(GL_LINES, 0, sizeof(tockice) / sizeof(float));

        glfwSwapBuffers(okno);
        glfwPollEvents();
        delta_t = glfwGetTime() - zac_okna;
    }

    glfwTerminate();
    return 0;
}
