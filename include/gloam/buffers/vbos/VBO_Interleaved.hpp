/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_VBO_INTERLEAVED_INCLUDED
#define DCG_VBO_INTERLEAVED_INCLUDED

#include "gloam/core/core.hpp"

namespace gloam{

class VBO_Interleaved : public VBO, public InterleavedArray{
private:
	vector<Access> arrayAccessors;

public:
	VBO_Interleaved(Context& context, dcg::DStructType type) : 
		VBO(context),
		InterleavedArray(type)
	{
		for(DStructType::Field field : type.getFields()){
			arrayAccessors.push_back(Access(
				field.getOffset(),
				(void*) field.getSize()
			));
		}
	}
	virtual ~VBO_Interleaved(){}
	
	virtual vector<Access> getArrayAccessors() { return(arrayAccessors); }

	virtual void bufferData(Usage::Frequency freq){
		VBO::bufferData(
			InterleavedArray::data(),
			InterleavedArray::getByteSize(),
			freq
		);
	}
};

}

#endif
