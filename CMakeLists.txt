cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(learnOpenGL)

# Version Number
set (learOpenGL_VERSION_MAJOR 1)
set (learOpenGL_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
# configure_file (
# )

add_executable(window window.cpp glad.c)

#SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /usr/local/lib/cmake/glfw3)
SET(OpenGL_GL_PREFERENCE "LEGACY")

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
# find_package(Libdl REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS} ${GLFW3_INCLUDE_DIRS})

#target_link_libraries(window ${OPENGL_LIBRARIES} ${GLFW3_LIBRARIES})
target_link_libraries(window ${OPENGL_LIBRARIES} glfw)
#message("GLFW3_LIBRARIES: ${GLFW3_LIBRARIES}")
