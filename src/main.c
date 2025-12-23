#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "call_back.h"
#include "interpolacija.h"
#include "matrika.h"
#include "shaderji.h"

const char *vertex_shader_crte_p =
    "#version 330 core\n"
    "layout (location = 0) in vec2 aPos;\n"
    "uniform mat3 projekcija;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(projekcija * vec3(aPos,1.0),1.0);\n"
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

    float tockice[] = {
        0.0, 0.0,
        100.0, 200.0,
        100.0, 200.0,
        300.0, 100.0};

    float projekcija[3][3];

    unsigned int vao_crte, vbo_crte;
    glGenVertexArrays(1, &vao_crte);
    glGenBuffers(1, &vbo_crte);

    glBindVertexArray(vao_crte);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_crte);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tockice), tockice, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    unsigned int program_za_crte = naredi_program(vertex_shader_crte_p, fragment_shader_crte_p);

    while (!glfwWindowShouldClose(okno))
    {
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        // Risanje črt
        orto3(projekcija, 0, 1920, 1080, 0);

        glUseProgram(program_za_crte);
        glUniformMatrix3fv(glGetUniformLocation(program_za_crte, "projekcija"), 1, GL_FALSE, &projekcija[0][0]);

        glDrawArrays(GL_LINE_STRIP, 0, 4);

        glfwSwapBuffers(okno);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
