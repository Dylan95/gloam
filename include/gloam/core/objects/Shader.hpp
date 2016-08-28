/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_SHADER_OBJECT_INCLUDED
#define DCG_SHADER_OBJECT_INCLUDED

//#include "glErrors.hpp"

#include "gloam/core/util/util.hpp"

//#include "Glew.hpp"

#include "gloam/core/objects/GLObject.hpp"

namespace gloam{

class Shader : GLObjectGLSL{
public:
	enum Type : GLenum{
		COMPUTE_SHADER = GL_COMPUTE_SHADER, 
		VERTEX_SHADER = GL_VERTEX_SHADER, 
		TESS_CONTROL_SHADER = GL_TESS_CONTROL_SHADER, 
		TESS_EVALUATION_SHADER = GL_TESS_EVALUATION_SHADER, 
		GEOMETRY_SHADER = GL_GEOMETRY_SHADER, 
		FRAGMENT_SHADER = GL_FRAGMENT_SHADER
	};

public:
	Shader(string code, GLenum type) : 
		GLObjectGLSL(glCreateShader(type), glDeleteShader) 
	{
		compile(code);
	}

	virtual ~Shader() {} 
	
	void attach(GLuint program){
		glAttachShader(program, GLObject::id);
	}

	void detach(GLuint program){
		glDetachShader(program, GLObject::id);
	}

private:
	void compile(const std::string& text){
		const GLchar *src = text.c_str();
		GLint srcLen = text.length();
		//
		glShaderSource(GLObject::id, 1, &src, &srcLen);
		glCompileShader(GLObject::id);
		//
		checkError(GL_COMPILE_STATUS, "shader compilation failed");
	}

	void checkError(GLenum flag, std::string shaderErrorMessage){
		GLint success = 0;
		GLchar error[1024] = { 0 };
		//
		glGetShaderiv(GLObject::id, flag, &success);
		if(success == GL_FALSE){
			glGetShaderInfoLog(GLObject::id, sizeof(error), NULL, error);
			std::cerr << shaderErrorMessage << ": '" << error << "'" << endl;
		}
	}
};

}

#endif
