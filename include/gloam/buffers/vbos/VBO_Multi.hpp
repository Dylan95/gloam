/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_VBO_MULTI_INCLUDED
#define DCG_VBO_MULTI_INCLUDED

#include "gloam/core/core.hpp"

namespace gloam{

/*class VBO_Multi : public VBO{
private:
	s_ptr<Chunk> data;
	vector<Access> arrayAccesors;

public:
	VBO_Multi(Context& context, vector<DArray> arrays, Usage::Frequency freq) : 
		VBO(context)
	{
		assert(arrays.size() != 0);
		size_t numElems = arrays.typeSize();
		size_t totalSize = 0;
		for(auto arr : arrays){
			assert(arr.size() == numElems);
			arrayAccessors.push_back(Access(
				arr.getTypeSize(),
				(void*) totalSize
			));
			totalSize += (arr.typeSize() * numElems);
		}
		bufferData(freq);
	}
	VBO_Multi(Context& context, DArray arr, Usage::Frequency bot)
		: VBO_Multi(context, make_shared<DVector>(arr), bot) 
	{}

	virtual ~VBO_Multi(){}

	virtual void bufferData(Usage::Frequency freq){
		VBO::bufferData(
			*(data->begin()),
			data->getByteSize(),
			freq
		);
	}

	s_ptr<DVector> getData(){ return(data); }
};*/

}

#endif
