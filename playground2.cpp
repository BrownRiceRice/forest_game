#include <stdio.h>
#include <stdlib.h>


#define GLEW_STATIC // Depending on how you built/installed GLEW, you may want to change this
#include <GL/glew.h>

// #define GLFW_DLL // Depending on how you built/installed GLFW, you may want to change this
#include "/usr/local/include/GLFW/glfw3.h"

#include <glm/glm.hpp>
using namespace glm;

GLFWwindow *window;


int main( void )
{
#ifdef COMPILE_WITH_SOME_PREPROCESSOR_DIRECTIVE
	printf("You checked the SOME_STUFF button in CMake !"); 
#endif


	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE,GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For Mac stuff
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
    window = glfwCreateWindow( 1024, 768, "Playgroud" , NULL, NULL); //0,0,0,0, 32,0);
	if(window == NULL)
	{
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}

    glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glfwSetWindowTitle( window, "Playground" );

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode( window, GLFW_STICKY_KEYS, GL_TRUE );

	// Dark blue background
	glClearColor(0.0f, 0.4f, 0.4f, 0.0f);

	do{
		// Draw nothing, see you in tutorial 2 !

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey( window, GLFW_KEY_ESCAPE ) != GLFW_PRESS); // &&
		   //glfwGetWindowParam( window, GLFW_OPENED ) );

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

