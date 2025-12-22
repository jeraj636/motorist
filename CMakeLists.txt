set(CMAKE_CXX_STANDARD 20)
cmake_minimum_required(VERSION 3.20)

project(VSSR)
set(CMAKE_CXX_STANDARD 20)
option(JE_WIN "Gradim za windows?" OFF)

if(JE_WIN)
    set(OPEN_GL_LIB opengl32 ws2_32)
else()
    set(OPEN_GL_LIB GL)
endif()

add_subdirectory(lib/glfw)


add_executable(${PROJECT_NAME}
    lib/glad/src/glad.c
    src/main.c
)

