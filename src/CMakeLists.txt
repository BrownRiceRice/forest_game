
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

set(VERTEX_SHADER SimpleVertexShader.glsl)
set(FRAGMENT_SHADER SimpleFragmentShader.glsl)
set(FONT_VERTEX_SHADER FontVertexShader.glsl)
set(FONT_FRAGMENT_SHADER FontFragmentShader.glsl) 

add_library(Forest_Lib
    ${MY_HEADER_FILES}
    ${MY_SOURCE_FILES}
)

target_compile_features(Forest_Lib PRIVATE cxx_nonstatic_member_init)
target_include_directories(Forest_Lib INTERFACE ${MY_HEADER_FILES})

add_executable(Forest
    ${APPLICATION_MAIN}
)

add_executable(Font text.cpp shader.cpp)
target_include_directories(Font INTERFACE ${MY_HEADER_FILES})
target_link_libraries(Font
    ${OPENGL_LIBRARY}
    ${GLFW_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GLUT_LIBRARIES}
    ${FREETYPE_LIBRARY}
)

target_compile_features(Forest PRIVATE cxx_nonstatic_member_init)

target_link_libraries(Forest
    # filled by "find_package(OpenGL REQUIRED)" and other defs in root dir.
	${OPENGL_LIBRARY}
	${GLFW_LIBRARIES}
	${GLEW_LIBRARIES}
    ${FREETYPE_LIBRARY}
    ${YAML_CPP_LIBRARIES}
    ${EXTRA_LIBS}
    Forest_Lib
)

# TODO: Put all shaders into a single folder.
configure_file(${VERTEX_SHADER} ${VERTEX_SHADER} COPYONLY)
configure_file(${FRAGMENT_SHADER} ${FRAGMENT_SHADER} COPYONLY)
configure_file(${FONT_VERTEX_SHADER} ${FONT_VERTEX_SHADER} COPYONLY)
configure_file(${FONT_FRAGMENT_SHADER} ${FONT_FRAGMENT_SHADER} COPYONLY)