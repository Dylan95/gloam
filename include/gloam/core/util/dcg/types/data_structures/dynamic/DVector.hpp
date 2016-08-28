/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_D_VECTOR_INCLUDED
#define DCG_D_VECTOR_INCLUDED

#include "dcg/types/data_structures/dynamic/DValue.hpp"

#include "dcg/types/data_structures/dynamic/DIter.hpp"

namespace dcg{

class DVector : public Chunk{
public:
	const size_t typeSize;

public:
	class Iter{
	public:
		DVector& vec;
		const size_t offset;
	public: 
		Iter(DVector& vec, size_t offset) : vec(vec), offset(offset){
			assert(offset + vec.typeSize <= vec.size());
		}
		//
		void* get(){ return((byte_t*)vec.data() + offset); }
		void set(void* from){ vec.move((byte_t*)vec.data(), (byte_t*) get(), vec.typeSize); }
		Iter operator+(size_t n){
			return(Iter(vec, offset + (n*vec.typeSize)));
		}
		bool operator==(const Iter& other){
			return(&vec==&other.vec && offset==other.offset);
		}
		bool operator!=(const Iter& other){
			return(! (*this==other));
		}
	};

public:
	DVector(size_t typeSize) : Chunk(0), typeSize(typeSize) {}

	Iter begin(){return(Iter(*this, 0));}
	Iter end(){return(Iter(*this, 0));}

	template<class IterType>
	void assign(Iter it, IterType begin, size_t n){
		assert(&(it.vec) == this);
		assert(begin.it->typeSize == typeSize);
		for(auto in = begin; in != begin+n; in++){ 
			it.set(&(*in)); it=it+1;
		}
	}

	template<class IterType>
	void insert(Iter it, IterType begin, size_t n){
		reserve(it, n*typeSize);
		assign(it, begin, n);
	}

	void remove(Iter it, size_t n){
		Chunk::remove((byte_t*) it.get(), n*typeSize);
	}

	//n: number of elements to reserve
	void reserve(Iter it, size_t n){
		Chunk::reserve((byte_t*) it.get(), n*typeSize);
	}

	void* data(){ return(Chunk::data()); }
	size_t getTypeSize(){ return(typeSize); }
	size_t getNumElems(){ return(Chunk::size() / typeSize); }
	size_t getByteSize(){ return(Chunk::size()); }
};

}

#endif






























/*
   
   //std::copy(it, begin, begin + n);
	//DIter end = begin + n;
	//for(VoidPtrIter in = data.begin; in != data.end; in++){
	//	it.set(in.get());
	//	it++;
	//}
   
class Iter{
	public:
		DVector& vec;
		const size_t offset;
	public: 
		Iter(DVector& vec, size_t offset) : vec(vec), offset(offset){
			assert(offset + vec.typeSize <= vec.size());
		}
		//
		DValue operator*(){
			return(DValue(vec.typeSize, vec.data() + offset));
		}
		Iter operator+(size_t n){
			return(Iter(vec, offset + (n*vec.typeSize)));
		}
		bool operator==(const Iter& other){
			return(offset==other.offset);
		}
		bool operator!=(const Iter& other){
			return(offset!=other.offset);
		}
	};
   
   
   
   
   
   
   
   template<class T>
class DVector_t{
	vector<T> data;
};*/
