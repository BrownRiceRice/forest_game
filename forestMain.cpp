#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC // Depending on how you built/installed GLEW, you may want to change this
#include <GL/glew.h>

// #define GLFW_DLL // Depending on how you built/installed GLFW, you may want to change this
#include "/usr/local/include/GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.hpp"
#include "controls.hpp"
#include "SceneObject.hpp"
#include "TreeObject.h"
#include "RockObject.h"
#include "World.hpp"

using namespace glm;
using namespace ParamWorld;

GLFWwindow *window;

int main( void )
{
#ifdef COMPILE_WITH_PERFORMANCE_TOOLS
    printf("You opted into showing performanec and debug tools. Printing average ms per frame.\n");
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
    window = glfwCreateWindow( 1024, 768, "Playgroud" , NULL, NULL); //0,0,0,0, 32,0);
  	if(window == NULL) {
	    fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
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
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    GLuint programID = LoadShaders("SimpleVertexShader.glsl", "SimpleFragmentShader.glsl");

    GLuint MatrixID = glGetUniformLocation(programID, "MVP");

    mat4 Projection = glm::perspective(glm::radians(45.0f), 1024.0f/768.0f, 0.1f, 100.0f);
    mat4 View = lookAt(vec3(2, 3, 3), // Camera location in world space
         vec3(0, 0, 0), // camera looks at this point
         vec3(0, 1, 0)   // Up direction
    );

    mat4 Model = mat4(1.0f);
    mat4 mvp = Projection * View * Model;

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    //TestCube cube(glm::vec3(-5, 0, 0));
    World w(800.0, MatrixID);

    //TreeObject tree(glm::vec3(0.0f, 0.0f, 0.0f), 3, 2.0f, .3f, .8f, 3.14159f/4.0f, Color(0.0f, 1.0, 0.0f), Color(1.0f, 0.0f, 0.0f), 1.0f);
    //RockObject rock(3, Color(0.8f, 0.0f, 0.0f), glm::vec3(4.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec2(0.0f, -1.0f), glm::vec2(-0.6f, 0.5f), 1.0f);
    //TestCube cube2(glm::vec3(5, 0, 0));
    //cube.init();
    //cube2.init();
    //tree.init();
    //rock.init();
    //cube.vertexbuffer = vertexbuffer;
    //cube.colorbuffer = colorbuffer;
    Player player(glm::vec3(0, 1.7, 5));

    #ifdef COMPILE_WITH_PERFORMANCE_TOOLS
    double lastTime = glfwGetTime();
    int nbFrames = 0;
    #endif

	  do{

          // Measure speed
          #ifdef COMPILE_WITH_PERFORMANCE_TOOLS
       double currentTime = glfwGetTime();
       nbFrames++;
       if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1 sec ago
           // printf and reset timer
           printf("%f ms/frame\n", 1000.0/double(nbFrames));
           nbFrames = 0;
           lastTime += 1.0;
       }
       #endif

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);

        player.computeMatricesFromInputs(window);
        w.updateExploredSquares(player.position, player.horizontalAngle);
        glm::mat4 ProjectionMatrix = player.getProjectionMatrix();
        glm::mat4 ViewMatrix = player.getViewMatrix();
        glm::mat4 PVMatrix = ProjectionMatrix * ViewMatrix;

        w.Render(ProjectionMatrix, ViewMatrix);
        //glm::mat4 ModelMatrix = cube.calcModelMatrix();
        //glm::mat4 mvp = PVMatrix * ModelMatrix;

        //glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

        //cube.draw();

        //ModelMatrix = cube2.calcModelMatrix();
        //mvp = PVMatrix * ModelMatrix;

        //glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
        //cube2.draw();

        //glm::mat4 ModelMatrix = tree.calcModelMatrix();
        //glm::mat4 mvp = PVMatrix * ModelMatrix;

        //glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
        //tree.draw();

        //ModelMatrix = rock.calcModelMatrix();
        //mvp = PVMatrix * ModelMatrix;

        //glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
        //rock.draw();

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
