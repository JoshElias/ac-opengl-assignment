#include "Common.h"


GameEngine::GameEngine()
{
	InitializeInput();
}


void GameEngine::InitializeInput()
{
		// Ensure we can capture the escape key being pressed below
		glfwEnable( GLFW_STICKY_KEYS );
}

void GameEngine::StartGameLoop()
{
	do{
			// Draw nothing, see you in tutorial 2 !

			// Swap buffers
			glfwSwapBuffers();

		} // Check if the ESC key was pressed or the window was closed
		while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
			glfwGetWindowParam( GLFW_OPENED ) );
}


void GameEngine::InitTestData()
{
	// An array of 3 vectors which represents 3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

}
