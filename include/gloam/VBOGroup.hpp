/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_VBO_GROUP_INCLUDED
#define DCG_VBO_GROUP_INCLUDED

#include "gloam/core/core.hpp"
#include "gloam/buffers/vbos/VBO.hpp"

namespace gloam{

class VBOGroup{
	vector<s_ptr<VBO>> vbos;
	vector<size_t> vboSizes;//number of arrays in each vbo.
	vector<BufferAccessor> accessors;
	
public:
	VBOGroup(){}
	VBOGroup(vector<s_ptr<VBO>> vbos){
		for(auto vbo : vbos){ addVBO(vbo); }
	}

	void addVBO(s_ptr<VBO> vbo){
		vbos.push_back(vbo);
		vector<VBO::Access> accesses = vbo->getArrayAccessors();
		vboSizes.push_back(accesses.size());
		for(auto a : accesses){
			accessors.push_back(BufferAccessor(vbo, a.getStride(), a.getOffset()));
		}
	}

	size_t getNumAccessors(){ return(accessors.size()); }
	BufferAccessor getAccessor(size_t i){ return(accessors[i]); }
	vector<BufferAccessor> getAccessors(){ return(accessors); }

	void assign(size_t index, vector<DIter> inputIters, size_t numElems){
		auto it = inputIters.begin();
		for(size_t i = 0; i < vbos.size(); i++){
			vbos[i]->assign(index, vector<DIter>(it, it + vboSizes[i]), numElems);
			it += vboSizes[i];
		}
	}

	void insert(size_t index, vector<DIter> inputIters, size_t numElems){
		auto it = inputIters.begin();
		for(size_t i = 0; i < vbos.size(); i++){
			vbos[i]->insert(index, vector<DIter>(it, it + vboSizes[i]), numElems);
			it += vboSizes[i];
		}
	}

	void remove(size_t index, size_t n){
		for(size_t i = 0; i < vbos.size(); i++){
			vbos[i]->remove(index, n);
		}
	}

	void buffer(vector<Buffer_Mutable::Usage::Frequency> freqs){
		assert(freqs.size() == vbos.size());
		auto freq = freqs.begin();
		for(auto vbo : vbos){
			vbo->bufferData(*freq);
			freq++;
		}
	}
};

}

#endif
