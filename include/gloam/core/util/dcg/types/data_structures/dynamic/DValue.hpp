/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_D_VALUE_INCLUDED
#define DCG_D_VALUE_INCLUDED

//#include "Chunk.hpp"

namespace dcg{

//be very carefull.
/*class DValue{
public:
	const size_t size;
	void *const p;

public:
	DValue(size_t size, void* p) : size(size), p(p) {}
	//DValue(const DValue& other) = delete;
	
	void operator=(const DValue& other){
		assert(size == other.size);
		memmove(p, other.p, size);
	}
	bool operator==(const DValue& other){
		return(memcmp(p, other.p, size) != 0);
	}
	bool operator!=(const DValue& other){
		return(! (*this == other));
	}
};*/

}

#endif
