cmake_minimum_required(VERSION 3.17)
project(ogl_chess)

set(CMAKE_CXX_STANDARD 20)

add_executable(ogl_chess main.cpp LOpenGL.h LUtil.cpp LUtil.h LTexture.cpp LTexture.h)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

target_link_libraries(ogl_chess OpenGL::OpenGL OpenGL::GLU GLUT::GLUT)
