#include "Common.h"


GLWindow::GLWindow()
{

}

void GLWindow::Initialize(int _width, int _height)
{
	try {
		// Initialise GLFW
		if( !glfwInit() )
			throw std::runtime_error("Failed to initialize GLFW");

		//glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
		glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3); 
		glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
		glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Open a window and create its OpenGL context
		if( !glfwOpenWindow( _width, _height, 0,0,0,0, 32,0, GLFW_WINDOW ) ) 
			throw std::runtime_error("Failed to initialize GLFW");


		glfwSetWindowTitle( "Tutorial 01" );

		// Initialize GLEW
		if(glewInit()) 
			throw std::runtime_error("Failed to initialize GLEW");

	} catch( std::exception const& err) {
		fprintf(stderr, "Exception Found: %s", err.what());
	} catch ( ... ) {
		fprintf(stderr,"Unknown Exception Occured");
	}
}