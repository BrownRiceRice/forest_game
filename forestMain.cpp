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

// TODO: finish adding 2d text on the screen.

using namespace ParamWorld;

GLFWwindow *window;

int main(void) {
#ifdef COMPILE_WITH_PERFORMANCE_TOOLS
    printf("Showing performance and debug tools. Printing average ms per frame.\n");
    fflush(stdout);
#endif

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
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We want new open GL

  	// Open a window and create its OpenGL context
    window = glfwCreateWindow( 1024, 768, "Playgroud" , NULL, NULL);
  	if(window == NULL) {
	    fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, "
                "they are not 3.3 compatible.\n" );
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
    glfwSetInputMode( window, GLFW_STICKY_KEYS, GL_TRUE );

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.2f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    GLuint programID = LoadShaders("SimpleVertexShader.glsl", "SimpleFragmentShader.glsl");

    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    GLuint ModelMatrixID = glGetUniformLocation(programID, "M");
    GLuint ViewMatrixID = glGetUniformLocation(programID, "V");

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    glUseProgram(programID);
    GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

    //TestCube cube(glm::vec3(-5, 0, 0));
    World w(299.0, MatrixID, ModelMatrixID, ViewMatrixID, LightID);

    Player player(glm::vec3(0, 1.7, 0));

    #ifdef COMPILE_WITH_PERFORMANCE_TOOLS
        double lastTime = glfwGetTime();
        int nbFrames = 0;
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

        #ifdef COMPILE_WITH_PERFORMANCE_TOOLS
            /*glm::vec3 dirFacing(
                sin(player.horizontalAngle),
                0,
                cos(player.horizontalAngle)
            );*/
            //glm::vec3 reference = player.getPosition() + dirFacing;
            //glm::mat4 localRef = glm::translate(10.0f);
            //glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &localRef);
            //glEnableVertexAttribArray(0);
        #endif

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
