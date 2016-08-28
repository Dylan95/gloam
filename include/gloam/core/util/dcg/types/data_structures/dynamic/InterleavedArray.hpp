/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_INTERLEAVED_ARRAY_INCLUDED
#define DCG_INTERLEAVED_ARRAY_INCLUDED

//#include "main.hpp"
//
#include <memory>
#include <iterator>
#include <tuple>

//#include "util.hpp"

#include "dcg/types/data_structures/dynamic/DVector.hpp"
#include "dcg/types/data_structures/dynamic/DStructType.hpp"


namespace dcg{

class InterleavedArray : public DVector{
public:
	class FieldIter{
	public:
		InterleavedArray& arr;
		DStructType::Field field;
		Iter it;
	public:
		FieldIter(InterleavedArray& arr, DStructType::Field field, Iter it) : 
			arr(arr),
			field(field),
			it(it)
		{}
		void* get(){
			return((byte_t*)it.get() + field.getOffset());
		}
		void set(void* from){
			arr.move((byte_t*) get(), (byte_t*) from, field.getSize());
		}
		FieldIter operator+(size_t n){ 
			return(FieldIter(arr, field, it + n));
		}
		/*bool operator==(FieldIter& other){ 
			return(
				(other.field == field) &&
				(other.it == it)
			); 
		}
		bool operator!=(Iter& other){ 
			return(!(*this == other)); 
		}*/
	};

private:
	DStructType structType;

public:
	InterleavedArray(DStructType structType) : 
		DVector(structType.getSize()),
		structType(structType)
	{}

	DStructType getStructType(){ return(structType); }

public:
	FieldIter begin(DStructType::Field field){
		return(FieldIter(*this, field, DVector::begin()));
	}
	FieldIter end(DStructType::Field field){
		return(begin(field) + getNumElems());
	}

	template<class IterType>
	void assign(Iter it, vector<IterType> inputIters, size_t numElems){
		verifyIters<IterType>(inputIters);
		auto fieldIt = structType.getFields().begin();
		for(IterType inBegin : inputIters){
			FieldIter out(*this, *fieldIt, it);
			for(auto in = inBegin; in != inBegin+numElems; in++){
				out.set(&*in);
				out=out+1;
			}
			fieldIt++;
		}
	}

	template<class IterType>
	void insert(Iter it, vector<IterType> inputIters, size_t numElems){
		DVector::reserve(it, numElems);
		assign<IterType>(it, inputIters);
	}

	/*Iter begin(){ return(DVector::begin()); }
	Iter end(){ return(DVector::end()); }

	void* data(){ return(DVector::data()); }
	size_t getNumElems(){ return(DVector::getNumElems()); }
	size_t getByteSize(){ return(DVector::getByteSize()); }*/

private:
	template<class IterType>
	void verifyIters(vector<IterType> iters){
		assert(iters.size() == structType.getFields().size());
		vector<DStructType::Field>::iterator fieldIt = structType.getFields().begin();
		for(auto it : iters){
			assert(sizeof(*it) == fieldIt->getSize());
			fieldIt++;
		}
	}
};

}

#endif


















/*

class FieldIter{
	public:
		const vector<Field>::iterator field;
		const Iter it;
	public:
		FieldIter(vector<Field>::iterator field, Iter it) : 
			field(field),
			it(it)
		{}
		DValue& operator*(){
			return(DValue(field.size, (*it).p + field.offset));
		}
		FieldIter operator+(size_t n){ 
			return(Iter(field, it + n));
		}
		bool operator==(const Iter& other){ 
			return(
				(other.field == field) &&
				(other.it == it)
			); 
		}
		bool operator!=(const Iter& other){ 
			return(!(*this == other)); 
		}
	};



   
   void verifyArrays(vector<DArray> arrays){
		assert(arrays.size() == 0);
		size_t numElems = arrays[0].size();
		for(auto arr : arrays){
			assert(arr.getNumElems() == numElems);
		}
	}
   
   
   
   
   void assign(InterleavedIter<byte_t> pos, vector<DArray> arrays){
		verifyArrays(arrays);
		for(size_t i = 0; i < arrays.size(); i++){
			byte_t* out = starts[i];
			for(auto in : arrays){
				chunk->move(out, *in, sizes[i]);
				out += structSize;
			}
		}
	}

	void insert(InterleavedIter<byte_t> pos, vector<DArray> arrays){
		verifyArrays(arrays);
		reserve(pos, numInsert);
		assign(pos, arrays);
	}

	//use with care, this does not call any destructors.
	void remove(InterleavedIter<byte_t> begin, size_t numElems){
		chunk->remove(*begin, numElems);
	}*/

/*

using namespace dcg::range;
using namespace util;

template<struct T>
class InterleavedArray{
public:
	struct FieldInfo{
		const size_t offset;
		const size_t size;
		FieldInfo(size_t offset, size_t size) : offset(offset), size(size) {}
	};

private:
	vector<FieldInfo> fields;
	vector<T> data;

public:
	//example:
	//struct Vertex{vec3 position; vec2 texCoord; vec3 normal;};
	//vector<Vertex> verts; verts.resize(numVerts);
	//for(int i = 0; i < numVertx; i++){ 
	//	verts[i].position = positions[i];
	//	verts[i].texCoord = texCoords[i];
	//	verts[i].normal = normals[i];
	//}
	//InterleavedArray<Vertex> verts(
	//	InterleavedArray::DArray::make<vec3>(positions)
	//	InterleavedArray::DArray::make<vec2>(texCoords)
	//	InterleavedArray::DArray::make<vec3>(colors)
	//}));
	InterleavedArray(vector<FieldInfo> fields, vector<T> data) : 
		fields(fields), 
		data(data)
	{}

	InterleavedArray(vector<FieldInfo> fields, vector<DArray> arrays){
		verifyArrays();
		numElems = arrays[0].getNumElems();
		for(auto arr : arrays){
			starts.push_back(chunk->data() + structSize);
			sizes.push_back(arr.getTypeSize());
			structSize += arr.getTypeSize();
		}
		//
		chunk = s_ptr<Chunk>(new Chunk(structSize * numElems));
	}

	byte_t* getData(){ return(chunk->data()); }
	size_t getTypeSize(size_t index){ return(sizes[index]); }
	size_t getOffset(size_t index){ return(offsets[index]); }
	
	size_t getStructSize(){ return(structSize); }
	size_t getNumElems(){ return(numElems); }

public:
	InterleavedIter<byte_t> begin(){
		return(InterleavedIter<byte_t>(chunk->data(), structSize));
	}
	InterleavedIter<byte_t> end(){
		return(begin() + numElems);
	}

	void assign(InterleavedIter<byte_t> pos, vector<DArray> arrays){
		verifyArrays(arrays);
		for(size_t i = 0; i < arrays.size(); i++){
			byte_t* out = starts[i];
			for(auto in : arrays){
				chunk->move(out, *in, sizes[i]);
				out += structSize;
			}
		}
	}

	void insert(InterleavedIter<byte_t> pos, vector<DArray> arrays){
		verifyArrays(arrays);
		reserve(pos, numInsert);
		assign(pos, arrays);
	}

	//use with care, this does not call any destructors.
	void remove(InterleavedIter<byte_t> begin, size_t numElems){
		chunk->remove(*begin, numElems);
	}

private:
	void reserve(InterleavedIter<byte_t> start, size_t numElems){
		chunk->reserve(*start, numElems * structSize);
	}

	void verifyArrays(vector<DArray> arrays){
		assert(arrays.size() == 0);
		size_t numElems = arrays[0].size();
		for(auto arr : arrays){
			assert(arr.getNumElems() == numElems);
		}
	}
};


*/

























//MyIterator operator++(int) {
//	MyIterator tmp(*this); operator++(); return tmp;
//}
