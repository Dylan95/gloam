/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_GL_OBJECT_BASE_INCLUDED
#define DCG_GL_OBJECT_BASE_INCLUDED

//#include "Glew.hpp"
//#include "main.hpp"

#include "gloam/core/util/util.hpp"



namespace gloam{


//contains all opengl objects except sync objects because 
//they're very different from other opengl objects.
typedef GLuint (APIENTRY *GLCreateFunction)();
typedef void (APIENTRY *GLDeleteFunction)(GLuint);
//
typedef void (APIENTRY *GLGenFunction)(GLsizei, GLuint *);
typedef void (APIENTRY *GLDelFunction)(GLsizei, const GLuint *);
//
//typedef void (APIENTRY *GLBindFunction)(GLenum target, GLuint id);


class GLObject{
public:
	const GLuint id;
public:
	GLObject(GLuint id) : id(id) {}
};

class GLObjectStandard : public GLObject{
	GLDelFunction delFunc;
public:
	GLObjectStandard(GLGenFunction genFunc, GLDelFunction delFunc)
		: GLObject(createID(genFunc)), delFunc(delFunc)
	{}
	//
	GLObjectStandard(const GLObjectStandard& other) = delete;
	//
	~GLObjectStandard(){
		delFunc(1, &id);
	}
private:
	GLuint createID(GLGenFunction genFunc){
		GLuint id;
		genFunc(1, &id);
		return(id);
	}
};

class GLObjectGLSL : public GLObject{
	GLDeleteFunction deleteFunc;
public:
	GLObjectGLSL(GLCreateFunction createFunc, GLDeleteFunction deleteFunc)
		: GLObject(createFunc()), deleteFunc(deleteFunc)
	{}
	GLObjectGLSL(GLuint id, GLDeleteFunction deleteFunc)
		: GLObject(id), deleteFunc(deleteFunc)
	{}
	//
	GLObjectGLSL(const GLObjectStandard& other) = delete;
	//
	~GLObjectGLSL(){
		deleteFunc(id);
	}
};


}

#endif





















/*template<class T>
class GLBindable{
	const GLBindFunction func;
	const GLuint id;
	T target;
	//GLenum target;
public:
	GLBindable(GLBindFunction func, GLuint id, GLenum target) : 
		func(func), id(id), target(target) 
	{}
	//
	void bind(){ func((GLenum) target, id); }
	void unbind(){ func((GLenum) target, 0); }
	//void bindTarget(GLenum target){
	void bindTarget(T target){
		this->target = target;
		bind();
	}
};*/

/*public:

	//regular objects:
	class GLBuffer : public GLBindableObject{
	public:
		GLBuffer() : GLObjectStandard(glGenBuffers, glDeleteBuffers) {}
	};

	class GLQuery : public GLObjectStandard{
	public:
		GLQuery() : GLObjectStandard(glGenQueries, glDeleteQueries) {}
	};

	class GLRenderbuffer : public GLObjectStandard{
	public:
		GLRenderbuffer() : 
			GLObjectStandard(
				glGenRenderbuffers, glDeleteRenderbuffers
				glBindRenderbuffer, GL_RENDERBUFFER
			) 
		{}
	};

	class GLSampler : public GLObjectStandard{
	public:
		GLSampler() : GLObjectStandard(glGenSamplers, glDeleteSamplers) {}
	};

	class GLTexture : public GLObjectStandard{
	public:
		GLTexture() : GLObjectStandard(glGenTextures, glDeleteTextures) {}
	};

	//container objects:

	class GLFrameBuffer : public GLObjectStandard{
	public:
		GLFrameBuffer() : GLObjectStandard(glGenFramebuffers, glDeleteFramebuffers) {}
	};

	class GLProgramPipeline : public GLObjectStandard{
	public:
		GLProgramPipeline() : GLObjectStandard(glGenProgramPipelines, glDeleteProgramPipelines) {}
	};

	class GLTransformFeedback : public GLObjectStandard{
	public:
		GLTransformFeedback() : GLObjectStandard(glGenTransformFeedbacks, glDeleteTransformFeedbacks) {}
	};

	class GLVertexArray : public GLObjectStandard{
	public:
		GLVertexArray() : GLObjectStandard(glGenVertexArrays, glDeleteVertexArrays) {}
	};

	//non-standard:
	//objects that don't follow the standard conventions for OpenGL objects.

	//GLSL objects:

	class GLShader : public GLObjectGLSL{
	public:
		enum Type : GLenum{
			VERTEX = GL_VERTEX_SHADER,
			TESS_CONTROL = GL_TESS_CONTROL_SHADER,
			// (requires GL 4.0 or ARB_tessellation_shader)
			TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
			GEOMETRY = GL_GEOMETRY_SHADER,
			FRAGMENT = GL_FRAGMENT_SHADER,
			// (requires GL 4.3 or ARB_compute_shader)
			COMPUTE = GL_COMPUTE_SHADER
		};
		//
		GLShader(Type shaderType) : GLObjectGLSL(glCreateShader(shaderType), glDeleteShader) {}
	};

	class GLProgram : public GLObjectGLSL{
	public:
		GLProgram() : GLObjectGLSL(glCreateProgram(), glDeleteProgram) {}
	};

	//other:

	class GLSync{};
};*/


/*
   
   
   
template <GLGenFunction glGenFunction, GLDelFunction glDelFunction>
class GLObject
{
    GLuint m_name;
public:
    GLObject() 
    {  
        glGenFunction(1, &m_name);
    }

    ~GLObject()
    {
        glDelFunction(1, &m_name);
    }

    GLuint getName() {return m_name;}
};

typedef GLObject<glGenTextures, glDeleteTextures> 			GLTexture;
typedef GLObject<glGenFramebuffers, glDeleteFramebuffers> 	GLFramebuffer;











*/
