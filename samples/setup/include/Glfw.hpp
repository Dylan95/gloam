#ifndef DCG_GLFW_INCLUDED
#define DCG_GLFW_INCLUDED

//#include "util.hpp"

#include <GLFW/glfw3.h>

namespace glob{

class Glfw{
	//vector<GLFWmonitor*> monitors;

public:
	static void init(){
		if (!glfwInit())
			exit(-1);
		glfwSetErrorCallback(
			[](int i, const char* s){
				cout 
					<< "a fatal glfw error occured: " 
					<< "code: " << i << endl
					<< "description: " << s << endl
				;
				cout.flush();
				std::exit(-1);
			}
		);
		//
		/*int count;
		GLFWmonitor** ms = glfwGetMonitors(&count);
		for(int i = 0; i < count; i++){
			monitors.push_back(ms[i]);
		}*/
	}

	//const vector<GLFWmonitor*>& getMonitors(){ return(monitors); }
};

}

#endif
