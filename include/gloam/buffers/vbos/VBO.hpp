/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_VBO_INCLUDED
#define DCG_VBO_INCLUDED

#include "gloam/core/core.hpp"

namespace gloam{

class VBO : public Buffer_Mutable{
public:
	//to access an array stored in the VBO
	class Access{
		size_t stride;
		void* offset;
	public:
		Access(size_t stride, void* offset) : 
			stride(stride), 
			offset(offset)
		{}
		size_t getStride(){ return(stride); }
		void* getOffset(){ return(offset); }
	};

protected:
	VBO(Context& context)
		: Buffer_Mutable(context.targets.bufferTargets.ARRAY_BUFFER)
	{}

public:
	virtual ~VBO(){}

	virtual void assign(size_t index, vector<DIter> inputIters, size_t numElems){
		assert(false);//NOP
	}

	virtual void insert(size_t index, vector<DIter> inputIters, size_t numElems){
		assert(false);//NOP
	}

	virtual void remove(size_t index, size_t numElems){
		assert(false);//NOP
	}

	virtual void reserve(size_t index, size_t numElems){
		assert(false);//NOP
	}

	virtual void bufferData(Usage::Frequency freq){
		assert(false);//NOP
	}

	void bind(){ Buffer::bind(); }

	virtual vector<Access> getArrayAccessors() { 
		//NOP
		assert(false);
		return(vector<Access>());
	}

protected:
	void bufferData(void* data, size_t size, Usage::Frequency freq){
		Buffer_Mutable::bufferData(
			size, 
			data,
			dcg::make_c<Usage>(freq, Usage::Nature::DRAW)
		);
	}
};

}

#endif
