/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_BINDING_INCLUDED
#define DCG_BINDING_INCLUDED

#include "gloam/core/util/util.hpp"

#include "gloam/core/context/targets/Target.hpp"
#include "gloam/core/context/Context.hpp"

namespace gloam{


//opengl is a state machine.  
//Each state is a "target".
//objects identified by their "id"s are bound to targets.
//objects will usually be used to bind to only one target.
class Binding{
private:
	const GLuint id;
	std::shared_ptr<Target> target;
	//
	dcg::c_ptr<GLuint> restoreID;

public:
	Binding(GLuint id, s_ptr<Target> target) : 
		id(id), 
		target(target)
	{}

	void bind(){ 
		target->bind(id);
	}
	void clear(){ 
		target->bind(0);
	}

	//temporarily bind to target.
	void push(){ 
		assert(restoreID.isNull());
		restoreID.reset(target->getVal());
		target->bind(id);
	}
	void pop(){
		assert(! restoreID.isNull());
		target->bind(*restoreID);
		restoreID.reset();
	}

	bool isBound(){
		return(target->getVal() == id);
	}

	s_ptr<Target> getTarget(){ return(target); }
	//GLenum getTargetName(){ return(target->getName()); }
	
	//it's perfectly legal to bind an object to multiple targets.
	void setTarget(s_ptr<Target> target){
		assert(restoreID.isNull());
		this->target = target;
	}
};

}

#endif
