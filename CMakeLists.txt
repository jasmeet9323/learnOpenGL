cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(learnOpenGL)

add_executable(triangle triangle.cpp glad.c)
add_executable(rectangle rectangle.cpp glad.c)

SET(OpenGL_GL_PREFERENCE "LEGACY")

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS} ${GLFW3_INCLUDE_DIRS})

target_link_libraries(triangle ${OPENGL_LIBRARIES} glfw)
target_link_libraries(rectangle ${OPENGL_LIBRARIES} glfw)

