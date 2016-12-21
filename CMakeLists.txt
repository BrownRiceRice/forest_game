# CMake entry point.

# For an introduction to CMake, see
# http://www.cmake.org/cmake/help/cmake_tutorial.html (at least steps 1 and 2)

cmake_minimum_required (VERSION 3.1.0 FATAL_ERROR)
project (ForestMacPort)

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.2 REQUIRED)
find_package(freetype REQUIRED)

# In order to build GLFW on Mac, you need to include these libraries.
# See http://www.glfw.org/docs/3.0/build.html#build_link_xcode
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    FIND_LIBRARY(COCOA_LIBRARY Cocoa)
    Find_LIBRARY(IOKIT_LIBRARY IOKit)
    Find_LIBRARY(COREVIDEO_LIBRARY CoreVideo)
    SET(EXTRA_LIBS ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
ENDIF (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

# Ask the user to give the paths to GLFW, GLEW and GLM.
# On Linux this can be found automatically with pkg-config;
# see http://stackoverflow.com/questions/6889264/cmake-flags-for-opengl-using-glew-and-glfw, for instance.
# On mac, installing via brew did not work, must install from the source.
# (that created the libglfw3.a).
set(GLFW_INCLUDE_PATH "/usr/local/include/" CACHE PATH "Directory containing GL/glfw.h" )
set(GLFW_LIBRARY "/usr/local/lib/libglfw3.a" CACHE FILEPATH "libglfw.a" )

set(GLEW_INCLUDE_PATH "/usr/local/Cellar/glew/2.0.0/include" CACHE PATH "Directory containing GL/glew.h" )
set(GLEW_LIBRARY "/usr/local/Cellar/glew/2.0.0/lib/libGLEW.a" CACHE FILEPATH "libglew.a" )

set(GLM_INCLUDE_PATH "/usr/local/Cellar/glm/0.9.8.3/include" CACHE PATH "Directory containing glm/glm.hpp" )

set(MY_HEADER_FILES
	# put all your .h here. Right now we have none.
	# Example :
    Params/SceneParams.h
    Params/SParam.h
    Params/AvailableParameters.h
	shader.hpp
    Player.hpp
    SceneObjects/SceneObject.hpp
    SceneObjects/Model.hpp
    SceneObjects/TreeObject.hpp
    SceneObjects/RockObject.hpp
    SceneObjects/SkyObject.hpp
    World.hpp
)

set(MY_SOURCE_FILES
	# put all your .c/.cpp here.
    SceneObjects/Model.cpp
    SceneObjects/TreeObject.cpp
    SceneObjects/RockObject.cpp
    SceneObjects/SkyObject.cpp
    shader.cpp
    Player.cpp
    World.cpp
	forestMain.cpp
)

set (VERTEX_SHADER SimpleVertexShader.glsl)
set (FRAGMENT_SHADER SimpleFragmentShader.glsl)


include_directories(
	${GLFW_INCLUDE_PATH}
	${GLEW_INCLUDE_PATH}
	${GLM_INCLUDE_PATH}
    ${FREETYPE_INCLUDE_DIRS}
)
add_executable(Forest
	${MY_HEADER_FILES}
	${MY_SOURCE_FILES}
)

target_compile_features(Forest PRIVATE cxx_nonstatic_member_init)

target_link_libraries(Forest
	${OPENGL_LIBRARY} # filled by "find_package(OpenGL REQUIRED)"
	${GLFW_LIBRARY}
	${GLEW_LIBRARY}
    ${FREETYPE_LIBS}
    ${EXTRA_LIBS}
)

configure_file(${VERTEX_SHADER} ${VERTEX_SHADER} COPYONLY)
configure_file(${FRAGMENT_SHADER} ${FRAGMENT_SHADER} COPYONLY)

# test if linux, mac or windows :

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	message("You're on Mac OS !")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	message("You're on Linux !")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    message ("You're on Windowns!")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

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
