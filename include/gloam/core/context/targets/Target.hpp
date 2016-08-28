/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_TARGET_INCLUDED
#define DCG_TARGET_INCLUDED

#include "gloam/core/context/State.hpp"


namespace gloam{



class Target : public State<GLuint>{
public:
	Target(GLenum name) : State(name) {}
	virtual void bind(GLuint id){ assert(false); } //NOP
};


class Target_Standard : public Target{
public:
	typedef void (*glBindFunc) (GLenum name, GLuint);

private:
	const glBindFunc bindFunc;

public:
	Target_Standard(glBindFunc bindFunc, GLenum name) : 
		Target(name),
		bindFunc(bindFunc) 
	{}
	virtual ~Target_Standard() {}

	virtual void bind(GLuint id){
		State<GLuint>::val = id;
		bindFunc(Target::name, id);
	}
};


class Target_Single : public Target{
public:
	typedef void (*glBindFunc) (GLuint);

private:
	const glBindFunc bindFunc;

public:
	//Target_Single(glBindFunc bindFunc, GLenum name) : 
	Target_Single(glBindFunc bindFunc, GLenum name) : 
		Target(name),
		bindFunc(bindFunc) 
	{}
	virtual ~Target_Single() {}

	virtual void bind(GLuint id){
		State<GLuint>::val = id;
		bindFunc(id);
	}
};


}

#endif