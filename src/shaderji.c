#include "shaderji.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

unsigned int nalozi_shader(const char *koda, char tip)
{
    unsigned int shader;
    int uspeh;
    char informacije[512];

    switch (tip)
    {
    case 'v':
        shader = glCreateShader(GL_VERTEX_SHADER);
        break;
    case 'f':
        shader = glCreateShader(GL_FRAGMENT_SHADER);
        break;
    }

    glShaderSource(shader, 1, &koda, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &uspeh);
    if (!uspeh)
    {
        glGetShaderInfoLog(shader, 512, NULL, informacije);
        printf("Napakica pri shaderjuh!\n%s", informacije);
    }
    return shader;
}

unsigned int naredi_program(const char *vertex_shader_p, const char *fragment_shader_p)
{
    unsigned int vertrx_shader = nalozi_shader(vertex_shader_p, 'v');
    unsigned int fragment_shader = nalozi_shader(fragment_shader_p, 'f');
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertrx_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    int uspeh;
    glGetProgramiv(program, GL_LINK_STATUS, &uspeh);
    if (!uspeh)
    {
        char infomacije[512];
        glGetProgramInfoLog(program, 512, NULL, infomacije);
        printf("tezava pri linkanju\n%s", infomacije);
    }
    glDeleteShader(vertrx_shader);
    glDeleteShader(fragment_shader);
    return program;
}