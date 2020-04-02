cmake_minimum_required(VERSION 3.17)
project(ogl_chess)

set(CMAKE_CXX_STANDARD 20)

add_executable(ogl_chess main.cpp LOpenGL.h GLUtils.cpp GLUtils.h Texture.cpp Texture.h Chessboard.cpp Chessboard.h ObjModel.cpp ObjModel.h Color.h Color.cpp)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
include_directories(ogl_chess GLM_INCLUDE_DIR)

target_link_libraries(ogl_chess OpenGL::OpenGL OpenGL::GLU GLUT::GLUT GLEW::GLEW)
