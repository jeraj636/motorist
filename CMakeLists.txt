set(CMAKE_CXX_STANDARD 20)
cmake_minimum_required(VERSION 3.20)

project(Motorist)
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
    src/call_back.c
    src/interpolacija.c
    src/matrika.c
    src/shaderji.c
)

target_include_directories(${PROJECT_NAME} PUBLIC
lib/glad/include/
lib/glad/
lib/glfw/include/
)

target_link_libraries(${PROJECT_NAME}
glfw
${OPEN_GL_LIB}
)
