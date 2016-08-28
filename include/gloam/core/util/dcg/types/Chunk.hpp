/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_CHUNK_INCLUDED
#define DCG_CHUNK_INCLUDED

#include "dcg/types/basicTypes.hpp"
#include "dcg/functions/Util.hpp"

#include <memory>
#include <vector>
#include <cstring>

namespace dcg{

class Chunk : private std::vector<byte_t>{
public:
	Chunk(size_t size) : vector<byte_t>(size) {
		vector<byte_t>::resize(size);
	}

	//

	void resize(size_t size){
		bool shrink = size < this->size();
		vector<byte_t>::resize(size);
		if(shrink){ vector<byte_t>::shrink_to_fit(); }
	}

	byte_t* data(){ return(vector<byte_t>::data()); }
	size_t size(){ return(vector<byte_t>::size()); }

public:
	//if your sure the memory your copying from and copying to don't overlap,
	//use this instead of the 'move' method.
	void copy(byte_t* to, byte_t* from, size_t size){
		assert(b_validRange(to, size));
		std::memcpy(to, from, size);
	}
	//if your not sure wether the memory your copying from and copying to 
	//overlap, use this instead of the 'copy' method.
	void move(byte_t* to, byte_t* from, size_t size){
		assert(b_validRange(to, size));
		std::memmove(to, from, size);
	}

public:
	void remove(byte_t* start, byte_t* end){
		size_t moveSize = (size_t) (data() + size() - end);
		//
		move(start, end, moveSize);
		resize(size() - (size_t)(end - start));
	}
	void remove(byte_t* start, size_t size){
		remove(start, start + size);
	}

	void reserve(byte_t* start, size_t size){
		byte_t* end = start + size;
		size_t moveSize = (size_t) (data() + this->size() - start);
		//
		resize(this->size() + size);
		move(end, start, moveSize);
	}

public:
	template<class T, class... Args>
	void emplaceAt(byte_t* to, Args... args){
		assert(b_validRange(to, sizeof(T)));
		Util::emplaceAt<T, Args...>(to, args...);
	}

private:
	bool b_validRange(byte_t* start, size_t size){
		byte_t* d = data();
		byte_t* max = d + this->size();
		byte_t* u = start + size;
		return(
			Util::inRange<byte_t*>(start, data(), data() + this->size()) &&
			((start + size) <= (data() + this->size()))
		);
	}
};

}

#endif
