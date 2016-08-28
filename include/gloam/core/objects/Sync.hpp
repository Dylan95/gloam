/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_SYNC_INCLUDED
#define DCG_SYNC_INCLUDED

#include "gloam/core/objects/GLObject.hpp"

namespace gloam{

class Sync{
public:
	enum WaitResult : GLenum{
		ALREADY_SIGNALED = GL_ALREADY_SIGNALED,
		TIMEOUT_EXPIRED = GL_TIMEOUT_EXPIRED,
		CONDITION_SATISFIED = GL_CONDITION_SATISFIED,
		WAIT_FAILED = GL_WAIT_FAILED
	};

	enum Param : GLenum{
		OBJECT_TYPE = GL_OBJECT_TYPE, 
		SYNC_STATUS = GL_SYNC_STATUS,
		SYNC_CONDITION = GL_SYNC_CONDITION,
		SYNC_FLAGS = GL_SYNC_FLAGS,
	};

public:
	GLsync sync;

public:
	Sync() {
		sync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
	}

	virtual ~Sync(){
		glDeleteSync(sync);
	}

	void clientWait(GLuint64 timeout = 0){
		glClientWaitSync(sync, GL_SYNC_FLUSH_COMMANDS_BIT, timeout);
	}
	void wait(){
		glWaitSync(sync, 0, GL_TIMEOUT_IGNORED);
	}

	bool isSignaled(){
		return(get(Param::SYNC_STATUS) == GL_SIGNALED);
	}

private: 
	GLint get(Param param){
		vector<GLint> values; values.resize(1);
		GLsizei length;
		glGetSynciv(
			sync,
			param,
			values.size() * sizeof(GLint),
			&length,
			values.data()
		);
		return(values[0]);
	}
};

}

#endif