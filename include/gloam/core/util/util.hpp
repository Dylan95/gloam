/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef GLOAM_UTIL_INCLUDED
#define GLOAM_UTIL_INCLUDED

#include <memory>
#include <vector>

//dcg.hpp"/dcg.hpp"
#include "gloam/core/util/dcg/dcg.hpp"

#include <GL/glew.h>
//#include <freeglut/freeglut.h>
//#include <GL/freeglut.h>
//
//#define GLFW_INCLUDE_GLU //for GLU
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

//sheild namespace dcg inside gloam to prevent 
//global namespace pollution.
namespace gloam{
	using namespace dcg;
}


//error detection:
namespace gloam{

static void checkError(){
	switch (glGetError()){
	case GL_INVALID_ENUM:
		dcg::cout << "GL_INVALID_ENUM: A function has been called with an inappropriate enum.\n";
		break;
	case GL_INVALID_VALUE:
		cout << "GL_INVALID_VALUE: A function has been called with a out of range numeric value.\n";
		break;
	case GL_INVALID_OPERATION:
		cout << "GL_INVALID_OPERATION: An operation has been performed out of context, or not allowed in the current state.\n";
		break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		cout << "GL_INVALID_FRAMEBUFFER_OPERATION: vThe framebuffer object is not complete yet.\n";
		break;
	case GL_OUT_OF_MEMORY:
		cout << "GL_OUT_OF_MEMORY: Gl is out of memory.\n";
		break;
	default:
		cout << "no error\n";
	}
}

static void checkError(string preMessage){
	cout << preMessage + ": ";
	checkError();
}

}



#endif










































/*

namespace gloam{
   
using std::vector;
using std::string;

using std::endl;
using std::cout;
using std::cin;


typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned long ulong;

typedef unsigned char byte_t;

template<class T>
using s_ptr = std::shared_ptr<T>;

template<class T>
using u_ptr = std::unique_ptr<T>;

using std::make_shared;
using std::make_unique;


template<class T>
using c_ptr = dcg::c_ptr<T>;

using dcg::c_vector;

using dcg::make_c;

using dcg::Chunk;

using dcg::DIter;
using dcg::DVector;
using dcg::InterleavedArray;
using dcg::DStructType;

}

*/






/*


static void getFirstNMessages(GLuint numMsgs){
	GLint maxMsgLen = 0;
	//int tempMaxDebugMessageLength = 200;//because GL_MAX_DE
	glGetIntegerv(GL_MAX_DEBUG_MESSAGE_LENGTH, &maxMsgLen);
	cout << maxMsgLen << endl;
	//
	std::vector<GLchar> msgData(numMsgs * maxMsgLen);
	std::vector<GLenum> sources(numMsgs);
	std::vector<GLenum> types(numMsgs);
	std::vector<GLenum> severities(numMsgs);
	std::vector<GLuint> ids(numMsgs);
	std::vector<GLsizei> lengths(numMsgs);
	//
	pause();
	GLuint numFound = glGetDebugMessageLog(numMsgs, msgData.size(), &sources[0], &types[0], &ids[0], &severities[0], &lengths[0], &msgData[0]);
	pause();
	//
	sources.resize(numFound);
	types.resize(numFound);
	severities.resize(numFound);
	ids.resize(numFound);
	lengths.resize(numFound);
	//
	std::vector<std::string> messages;
	messages.reserve(numFound);
	//
	std::vector<GLchar>::iterator currPos = msgData.begin();
	for(size_t msg = 0; msg < lengths.size(); ++msg)
	{
		messages.push_back(std::string(currPos, currPos + lengths[msg] - 1));
		currPos = currPos + lengths[msg];
	}
	//
	for (uint i = 0; i < messages.size(); i++){
		cout << messages[i] << endl;
	}
}






*/
