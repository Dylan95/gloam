#ifndef DCG_GLEW_INCLUDED
#define DCG_GLEW_INCLUDED

//#include "util.hpp"

#include <GL/glew.h>

#include <GLFW/glfw3.h>

namespace glob{

class Glew{
	//a hidden window needed before glew can be initialized.
	//static GLFWwindow* context;

public:
	//creates context and initializes opengl with it.
	static void init(GLFWwindow* context){
		glfwMakeContextCurrent(context);
		initializeGlew();
	}

	//to spawn new windows with.
	//static GLFWwindow* getContext(){ return(context); }

private:
	static void initializeGlew(){
		GLenum error = glGetError();
		if (error != GL_NO_ERROR){
			std::cout << "OpenGL Error: " << error << std::endl;
			//checkError();
			exit(66);
		}
		//
		//GL versions newer than or equal to 3.3 are considered experimental, 
		//and glewInit() will fail if glewExperimental has the wrong value.
		glewExperimental=GL_TRUE;
		//glewExperimental=GL_FALSE;
		int e = glewInit();
		if(e != GLEW_OK){
			std::cerr << "glew error: " << e << std::endl;
			exit(67);
		}
	}
};

}

#endif







//void initializeGlew();

