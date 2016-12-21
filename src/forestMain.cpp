#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC // Depending on how you built/installed GLEW, you may want to change this
#include <GL/glew.h>

// #define GLFW_DLL // Depending on how you built/installed GLFW, you may want to change this
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.hpp"
#include "Player.hpp"
#include "SceneObjects/SceneObject.hpp"
#include "World.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <unistd.h>

// TODO: finish adding 2d text on the screen.

using namespace ParamWorld;

GLFWwindow *window;

int main(void) {
    int windowWidth = 1024;
    int windowHeight = 768;

    // Initialise GLFW
    if( !glfwInit() ) {
	    fprintf( stderr, "Failed to initialize GLFW\n" );
  	    getchar();
  	    return -1;
  	}

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_RESIZABLE,GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For Mac stuff
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // new OpenGL

  	// Open a window and create its OpenGL context
    window = glfwCreateWindow(windowWidth, windowHeight, "Forest" , NULL, NULL);
  	if(window == NULL) {
	    fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU,"
                " they are not 3.3 compatible.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}

    glfwMakeContextCurrent(window);
    glewExperimental=true;

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
	    fprintf(stderr, "Failed to initialize GLEW\n");
	    getchar();
	    glfwTerminate();
	    return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetCursorPos(window, windowWidth/2, windowHeight/2);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(window, windowWidth/2, windowHeight/2);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.2f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    GLuint programID = LoadShaders("SimpleVertexShader.glsl", "SimpleFragmentShader.glsl");

    GLuint MatrixID = glGetUniformLocation(programID, "MVP");

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    World w(299.0, MatrixID);

    Player player(glm::vec3(0, 1.7, 0));

    #ifdef COMPILE_WITH_PERFORMANCE_TOOLS
        double lastTime = glfwGetTime();
        int nbFrames = 0;
        printf("Showing performance and debug tools. Printing average ms per frame.\n");
        fflush(stdout);
    #endif

    do{
        // Measure speed
        #ifdef COMPILE_WITH_PERFORMANCE_TOOLS
            double currentTime = glfwGetTime();
            nbFrames++;
            if (currentTime - lastTime >= 1.0 ){ // If last print was more than 1s ago
                // printf and reset timer
                printf("%f ms/frame\n", 1000.0/double(nbFrames));
                nbFrames = 0;
                lastTime += 1.0;
            }
        #endif

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);

        player.computeMatricesFromInputs(window);
        w.updateExploredSquares(window, player.getPosition(), player.horizontalAngle);
        glm::mat4 ProjectionMatrix = player.getProjectionMatrix();
        glm::mat4 ViewMatrix = player.getViewMatrix();

        w.Render(ProjectionMatrix, player.getPosition(), player.getDirection(), player.getUp());

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey( window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) ==  0);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    return 0;
}
