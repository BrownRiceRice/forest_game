#ifndef HEADERS_HPP
#define HEADERS_HPP

/// Due to the "#error gl.h included before glew.h" issue, it's probably easier
/// to have an entirely seperate header file that all files can include once.
/// This is that file.

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#endif