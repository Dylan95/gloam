/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_PROGRAM_OBJECT_INCLUDED
#define DCG_PROGRAM_OBJECT_INCLUDED

#include <vector>

#include "gloam/core/objects/GLObject.hpp"

#include "gloam/core/objects/Shader.hpp"

#include "gloam/core/context/Context.hpp"
#include "gloam/core/Binding.hpp"

namespace gloam{

struct Attrib{
	const GLint attribIndex;			//like 0 for positions, 1 for texCoords, etc.
	//const size_t attribIndex;			//like 0 for positions, 1 for texCoords, etc.
	const size_t numSubtypes;			//ex: sizeof(vec3) / sizeof(float) == 3
	//
	const GLenum attribType;			//like GL_FLOAT, for positions
	const GLboolean isNormalized;

	Attrib(
		size_t attribIndex, size_t numSubtypes,
		GLenum attribType, GLboolean isNormalized
	) : 
		attribIndex(attribIndex),
		numSubtypes(numSubtypes),
		attribType(attribType),
		isNormalized(isNormalized)
	{}
};

class Uniform{
	GLint loc;

public:
	Uniform(GLuint programID, string name){
		loc = glGetUniformLocation(programID, name.c_str());
		if(loc == -1){
			cout << "WARNING: uniform name '" + name + "' doesn't exist, is unused, or starts with 'gl_'.  This may have happened because you used a layout specifier in the GLSL code: like 'layout(location = 0) uniform vec3 lightDirection;'.  For ease of use, the engine will use the uniform anyways, but it will have no effect on the shader program\n\n" << endl;
		}
	}

	void setUniform(int value){
		if(loc != -1){
			glUniform1i(loc, value);
		}
	}
	void setUniform(float value){
		if(loc != -1){
			glUniform1f(loc, value);
		}
	}
	void setUniform(glm::vec2 value){
		if(loc != -1){
			glUniform2f(loc, value.x, value.y);
		}
	}
	void setUniform(glm::vec3 value){
		if(loc != -1){
			glUniform3f(loc, value.x, value.y, value.z);
		}
	}
	void setUniform(glm::vec4 value){
		if(loc != -1){
			glUniform4f(loc, value.x, value.y, value.z, value.w);
		}
	}
	void setUniform(vector<float> values){
		if(loc != -1){
			glUniform1fv(loc, values.size(), (GLfloat*) values.data());
		}
	}
	void setUniform(vector<glm::vec2> values){
		if(loc != -1){
			glUniform2fv(loc, values.size(), (GLfloat*) values.data());
		}
	}
	void setUniform(vector<glm::vec3> values){
		if(loc != -1){
			glUniform3fv(loc, values.size(), (GLfloat*) values.data());
		}
	}
	void setUniform(vector<glm::vec4> values){
		if(loc != -1){
			glUniform4fv(loc, values.size(), (GLfloat*) values.data());
		}
	}
	void setUniform(glm::mat2 value){
		if(loc != -1){
			glUniformMatrix3fv(loc, 1, GL_FALSE, &value[0][0]);
		}
	}
	void setUniform(glm::mat3 value){
		if(loc != -1){
			glUniformMatrix3fv(loc, 1, GL_FALSE, &value[0][0]);
		}
	}
	void setUniform(glm::mat4 value){
		if(loc != -1){
			glUniformMatrix4fv(loc, 1, GL_FALSE, &value[0][0]);
		}
	}
};



class Program : public GLObjectGLSL, protected Binding {
public:
	struct NamedAttrib{
		const string name;
		//
		const size_t numSubtypes;			//ex: sizeof(vec3) / sizeof(float) == 3
		const GLenum attribType;			//like GL_FLOAT, for positions
		const GLboolean isNormalized;

		NamedAttrib(
			string name, 
			size_t numSubtypes, 
			GLenum attribType, 
			GLboolean isNormalized
		) : 
			name(name), 
			numSubtypes(numSubtypes),
			attribType(attribType),
			isNormalized(isNormalized) 
		{}
	};

private:
	vector<s_ptr<Shader>> shaders;
	vector<Attrib> attribs;
protected:
	vector<Uniform> uniforms;

public:
	Program(
		s_ptr<ProgramTarget> target,
		vector<s_ptr<Shader>> shaders, 
		vector<NamedAttrib> namedAttribs, 
		vector<string> uniformNames
	) : 
		GLObjectGLSL(glCreateProgram, glDeleteProgram),
		Binding(GLObject::id, target),
		shaders(shaders)
	{
		//assert(glfwGetCurrentContext() != NULL);
		//
		linkProgram();
		//
		for(auto namedAttrib : namedAttribs){
			GLint attribIndex = getAttribLocation(namedAttrib.name);
			attribs.push_back(Attrib(
				attribIndex, 
				namedAttrib.numSubtypes, 
				namedAttrib.attribType,
				namedAttrib.isNormalized
			));
		}
		for(string name : uniformNames){
			uniforms.push_back(Uniform(GLObject::id, name));
		}
	}

	virtual ~Program(){
		for(auto s : shaders){ s->detach(GLObject::id); }
	}

	void bind(){ Binding::bind(); }
	bool isBound(){ return(Binding::isBound()); }

	Attrib getAttrib(size_t index){ return(attribs[index]); }

	//if you update 1 uniform, then you'll need to update all of them,
	//otherwise they'll be set to their default values.
	void setUniform(size_t index, int value){ setUniform<int>(index, value); }
	void setUniform(size_t index, float value){ setUniform<float>(index, value); }
	void setUniform(size_t index, glm::vec2 value){ setUniform<glm::vec2>(index, value); }
	void setUniform(size_t index, glm::vec3 value){ setUniform<glm::vec3>(index, value); }
	void setUniform(size_t index, glm::vec4 value){ setUniform<glm::vec4>(index, value); }
	void setUniform(size_t index, vector<float> values){ setUniform<vector<float>>(index, values); }
	void setUniform(size_t index, vector<glm::vec2> values){ setUniform<vector<glm::vec2>>(index, values); }
	void setUniform(size_t index, vector<glm::vec3> values){ setUniform<vector<glm::vec3>>(index, values); }
	void setUniform(size_t index, vector<glm::vec4> values){ setUniform<vector<glm::vec4>>(index, values); }
	void setUniform(size_t index, glm::mat2 value){ setUniform<glm::mat2>(index, value); }
	void setUniform(size_t index, glm::mat3 value){ setUniform<glm::mat3>(index, value); }
	void setUniform(size_t index, glm::mat4 value){ setUniform<glm::mat4>(index, value); }

private:
	template<class T>
	void setUniform(size_t index, T value){
		assert(Binding::isBound());
		uniforms[index].setUniform(value);
	}

	GLint getAttribLocation(string name){
		GLint result = glGetAttribLocation(GLObject::id, name.c_str());
		if(result == -1){
			cout << "WARNING: attrib name '" + name + "' doesn't exist, is unused, or starts with 'gl_'.  This may have happened because you used a layout specifier in the GLSL code: like 'layout(location = 0) attribute vec3 position;'.  For ease of use, the engine will use the attribute anyways, but it will have no effect on the shader program\n\n" << endl;
		}
	}

	void linkProgram(/*GLuint *shaders, size_t shadersCount*/){
		for(auto s : shaders){
			s->attach(GLObject::id);
			//glAttachShader(GLObject::id, s->id);
		}
		glLinkProgram(GLObject::id);
		//
		checkProgramError(GL_LINK_STATUS, "program linking failed");
	}
	
	void checkProgramError(GLenum flag, std::string shaderErrorMessage){
		GLint success = 0;
		GLchar error[1024] = { 0 };
		//
		glGetProgramiv(GLObject::id, flag, &success);
		if(success == GL_FALSE){
			glGetProgramInfoLog(GLObject::id, sizeof(error), NULL, error);
			std::cerr << shaderErrorMessage << ": " << error << endl;
		}
	}
};

}

#endif


