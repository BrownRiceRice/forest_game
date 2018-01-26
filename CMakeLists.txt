# CMake entry point.

# For an introduction to CMake, see
# http://www.cmake.org/cmake/help/cmake_tutorial.html (at least steps 1 and 2)
cmake_minimum_required (VERSION 3.1.0 FATAL_ERROR)
project (ForestMacPort)

add_compile_options(-std=c++11)

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.1.2 REQUIRED)
find_package(Freetype REQUIRED)
find_package(YAML-CPP REQUIRED)

# In order to build GLFW on Mac, you need to include these libraries.
# See http://www.glfw.org/docs/3.0/build.html#build_link_xcode
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    Find_LIBRARY(COCOA_LIBRARY Cocoa)
    Find_LIBRARY(IOKIT_LIBRARY IOKit)
    Find_LIBRARY(COREVIDEO_LIBRARY CoreVideo)

    # On mac, installing via brew did not work, must install from the source.
    # (that created the libglfw3.a).
    set(EXTRA_LIBS ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})

    set(GLFW_INCLUDE_DIRS "/usr/local/include/" CACHE PATH "Directory containing GL/glfw.h" )
    set(GLFW_LIBRARIES "/usr/local/lib/libglfw3.a" CACHE FILEPATH "libglfw.a" )

    set(GLEW_INCLUDE_DIRS "/usr/local/Cellar/glew/2.0.0/include" CACHE PATH "Directory containing GL/glew.h" )
    set(GLEW_LIBRARIES "/usr/local/Cellar/glew/2.0.0/lib/libGLEW.a" CACHE FILEPATH "libglew.a" )

    set(GLM_INCLUDE_DIRS "/usr/local/Cellar/glm/0.9.8.3/include" CACHE PATH "Directory containing glm/glm.hpp" )
ENDIF (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

# Automatically find GLFW and GLEW.
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    find_package(PkgConfig REQUIRED)
    pkg_search_module(GLFW REQUIRED glfw3)
    # GLFW_INCLUDE_DIRS should now be defined.
    find_package(GLEW REQUIRED)
    find_package(GLUT REQUIRED)
ENDIF (${CMAKE_SYSTEM_NAME} MATCHES "Linux")

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}/include
	${GLFW_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIRS}
	${GLM_INCLUDE_DIRS}
    ${FREETYPE_INCLUDE_DIRS}
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add a checkbox in CMakeGUI :
set(PERFORMANCE_TOOLS ON BOOL "Check this to print out performance data.")

# Add a preprocessor define :
if(PERFORMANCE_TOOLS)
    message("Compiling with performance tools...")
	add_definitions(
		-DCOMPILE_WITH_PERFORMANCE_TOOLS
	)
endif(PERFORMANCE_TOOLS)

set(CMAKE_BUILD_TYPE RELEASE)
file(COPY config DESTINATION ${CMAKE_BINARY_DIR})

# Build the actual code.
add_subdirectory(src)
add_subdirectory(Resources)

enable_testing()
add_subdirectory(test)
