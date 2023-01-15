cmake_minimum_required(VERSION 3.12)
project(libre)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

if(WIN32)
    set(MATH "")
else()
    set(MATH "m")
endif()

file(GLOB SOURCES "src/*.c")
add_library(re STATIC ${SOURCES})
target_include_directories(re PUBLIC "include")
target_link_libraries(re PUBLIC glfw OpenGL::GL GLEW::GLEW ${MATH})

file(GLOB TEST_OPENGL_SOURCES "tests/test_opengl.c")
add_executable(test_opengl ${TEST_OPENGL_SOURCES})
target_include_directories(test_opengl PRIVATE "include")
target_link_libraries(test_opengl re glfw OpenGL::GL GLEW::GLEW ${MATH})

file(GLOB TEST_MATRIX_SOURCES "tests/test_matrix.c")
add_executable(test_matrix ${TEST_MATRIX_SOURCES})
target_include_directories(test_matrix PRIVATE "include")
target_link_libraries(test_matrix re glfw OpenGL::GL GLEW::GLEW ${MATH})
