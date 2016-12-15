# CMake entry point.
# Note that this CMakeLists.txt in fully independent from the one in the parent directory
# (since that's the goal of this tutorial !)

# For an introduction to CMake, see
# http://www.cmake.org/cmake/help/cmake_tutorial.html (at least steps 1 and 2)

cmake_minimum_required (VERSION 2.6)
project (BuildingYourOwnOpenglApp)

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
#pkg_search_module(GLFW REQUIRED glfw3)
find_package(glfw3 3.2 REQUIRED)


# Ask the user to give the paths to GLFW, GLEW and GLM.
# On Linux this can be found automatically with pkg-config; 
# see http://stackoverflow.com/questions/6889264/cmake-flags-for-opengl-using-glew-and-glfw, for instance.

IF(APPLE)
    FIND_LIBRARY(COCOA_LIBRARY Cocoa)
    Find_LIBRARY(IOKIT_LIBRARY IOKit) 
    Find_LIBRARY(COREVIDEO_LIBRARY CoreVideo)
    SET(EXTRA_LIBS ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
ENDIF (APPLE)

set(GLFW_INCLUDE_PATH "/usr/local/include/" CACHE PATH "The directory that contains GL/glfw.h" )
set(GLFW_LIBRARY "/usr/local/lib/libglfw3.a" CACHE FILEPATH "libglfw.a or glfw.lib" )

set(GLEW_INCLUDE_PATH "/usr/local/Cellar/glew/2.0.0/include" CACHE PATH "The directory that contains GL/glew.h" )
set(GLEW_LIBRARY "/usr/local/Cellar/glew/2.0.0/lib/libGLEW.a" CACHE FILEPATH "libglew.a or glew.lib" )

set(GLM_INCLUDE_PATH "/usr/local/Cellar/glm/0.9.8.3/include" CACHE PATH "The directory that contains glm/glm.hpp" )

set(MY_HEADER_FILES
	# put all your .h here. Right now we have none.
	# Example : 
	# ../common/shader.hpp
)

set(MY_SOURCE_FILES
	# put all your .c/.cpp here.
	playground2.cpp
	# ../common/shader.cpp
)



include_directories(
	${GLFW_INCLUDE_PATH}
	${GLEW_INCLUDE_PATH}
	${GLM_INCLUDE_PATH}
)
add_executable(BuildingYourOwnOpenglApp
	${MY_HEADER_FILES}
	${MY_SOURCE_FILES}
)
message("GLFW3 lib is" ${GLFW_LIBRARY})
message("Test stuff: " ${glfw3_FOUND})
message("w " ${GLFW_INCLUDE_DIRS})
# or <NAME>_INCLUDES
#<NAME>_LIBRARIES or <NAME>_LIBRARIES or <NAME>_LIBS
#<NAME>_DEFINITIONS

target_link_libraries(BuildingYourOwnOpenglApp
	${OPENGL_LIBRARY} # filled by "find_package(OpenGL REQUIRED)"
	${GLFW_LIBRARY}
	${GLEW_LIBRARY}
    ${EXTRA_LIBS}
)




# HOW-TO. You can safely remove anything below.  

# test if linux, mac or windows : 

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	message("You're on Mac OS !")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	message("You're on Linux !")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	message("You're on Windows !")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") # Yes this is weird but you have to repeat the "if" here.


# Add a checkbox in CMakeGUI : 

set(SOME_STUFF OFF CACHE BOOL "Check this to print an extra message at the beginning of main()")

# Add a preprocessor define : 

if(SOME_STUFF)
	add_definitions(
		-DCOMPILE_WITH_SOME_PREPROCESSOR_DIRECTIVE
	)
endif(SOME_STUFF)
