
set(MY_HEADER_FILES
	# put all your .h here. Right now we have none.
	# Example :
    Params/SceneParams.h
    Params/SParam.hpp
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
    Params/SParam.cpp
    Params/SceneParams.cpp
    SceneObjects/Model.cpp
    SceneObjects/TreeObject.cpp
    SceneObjects/RockObject.cpp
    SceneObjects/SkyObject.cpp
    shader.cpp
    Player.cpp
    World.cpp
)

set(APPLICATION_MAIN forestMain.cpp)

set (VERTEX_SHADER SimpleVertexShader.glsl)
set (FRAGMENT_SHADER SimpleFragmentShader.glsl)

include_directories(
	${GLFW_INCLUDE_PATH}
	${GLEW_INCLUDE_PATH}
	${GLM_INCLUDE_PATH}
    ${FREETYPE_INCLUDE_DIRS}
)

add_library(Forest_Lib
    ${MY_HEADER_FILES}
    ${MY_SOURCE_FILES}
)

target_compile_features(Forest_Lib PRIVATE cxx_nonstatic_member_init)

add_executable(Forest
    ${APPLICATION_MAIN}
)

target_include_directories(Forest_Lib INTERFACE ${MY_HEADER_FILES})
target_compile_features(Forest PRIVATE cxx_nonstatic_member_init)

target_link_libraries(Forest
    # filled by "find_package(OpenGL REQUIRED)" and other defs in root dir.
	${OPENGL_LIBRARY}
	${GLFW_LIBRARY}
	${GLEW_LIBRARY}
    ${FREETYPE_LIBS}
    ${EXTRA_LIBS}
    Forest_Lib
)

configure_file(${VERTEX_SHADER} ${VERTEX_SHADER} COPYONLY)
configure_file(${FRAGMENT_SHADER} ${FRAGMENT_SHADER} COPYONLY)
