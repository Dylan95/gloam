/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_QUERY_INCLUDED
#define DCG_QUERY_INCLUDED

#include "gloam/core/objects/GLObject.hpp"

namespace gloam{

class Query : public GLObjectStandard{
public:
	enum Target : GLenum{
		//The number of samples that pass the depth test 
		//for all drawing commands within the scope of the query.
		SAMPLES_PASSED = GL_SAMPLES_PASSED,
		//GL_FALSE if none of the scoped drawing commands 
		//generate samples that pass the depth test; 
		//otherwise, the value is GL_TRUE. This requires 
		//OpenGL 3.3 or ARB_occlusion_query2.
		ANY_SAMPLES_PASSED = GL_ANY_SAMPLES_PASSED,
		//As GL_ANY_SAMPLES_PASSED, except that the 
		//implementation may use a less accurate algorithm, 
		//which may be faster, but at the cost of more more 
		//false positives. This requires OpenGL 4.3 or 
		//ARB_ES3_compatibility.
		ANY_SAMPLES_PASSED_CONSERVATIVE = GL_ANY_SAMPLES_PASSED_CONSERVATIVE,
		//Records the number of primitives sent to a particular 
		//Geometry Shader output stream (or by stream 0 if no 
		//GS is active) by the scoped drawing commands. This 
		//requires OpenGL 3.0; multiple streams requires OpenGL 
		//4.0 or ARB_transform_feedback3.
		PRIMITIVES_GENERATED = GL_PRIMITIVES_GENERATED,
		//Records the number of primitives written by a 
		//Geometry Shader stream to a Transform Feedback 
		//object (or by stream 0 if no GS is active) by the 
		//scoped drawing commands. This requires OpenGL 3.0; 
		//multiple streams requires OpenGL 4.0 or ARB_transform_feedback3.
		TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN = GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN,
		//Records the time that it takes for the GPU to execute 
		//all of the scoped commands. The timer starts when 
		//all commands before the scope have completed, and 
		//the timer ends when the last scoped command has completed. 
		//Requires OpenGL 3.3 or ARB_timer_query.
		TIME_ELAPSED = GL_TIME_ELAPSED,
		//Records the current time of the GPU. Requires 
		//OpenGL 3.3 or ARB_timer_query.
		TIMESTAMP = GL_TIMESTAMP
	};

	enum Param : GLenum{
		QUERY_RESULT_AVAILABLE = GL_QUERY_RESULT_AVAILABLE,
		QUERY_RESULT = GL_QUERY_RESULT,
		//(requires OpenGL 4.4 or ARB_query_buffer_object)
		//GL_QUERY_RESULT_NO_WAIT 
	};

public:
	Query() : GLObjectStandard(glGenQueries, glDeleteQueries) {}

	void begin(Target target){
		glBeginQuery(target, GLObject::id);
	}

	void end(Target target){
		glEndQuery(target);
	}

	GLint get_int(Param p){
		GLint value;
		glGetQueryObjectiv(
			GLObject::id,
			p,
			&value
		);
		return(value);
	}
	GLuint get_uint(Param p){
		GLuint value;
		glGetQueryObjectuiv(
			GLObject::id,
			p,
			&value
		);
		return(value);
	}
	GLint64 get_int64(Param p){
		GLint64 value;
		glGetQueryObjecti64v(
			GLObject::id,
			p,
			&value
		);
		return(value);
	}
	GLuint64 get_uint64(Param p){
		GLuint64 value;
		glGetQueryObjectui64v(
			GLObject::id,
			p,
			&value
		);
		return(value);
	}
};

}

#endif