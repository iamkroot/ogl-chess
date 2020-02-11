cmake_minimum_required(VERSION 3.16)
project(learn_ogl)
set(OpenGlLinkers -lGL -lGLU -lglut)

set(CMAKE_CXX_STANDARD 20)

add_executable(learn_ogl main.cpp LOpenGL.h LUtil.cpp LUtil.h)
target_link_libraries(learn_ogl ${OpenGlLinkers})
