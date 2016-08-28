/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_D_STRUCT_TYPE_INCLUDED
#define DCG_D_STRUCT_TYPE_INCLUDED

#include <algorithm>
#include <type_traits>
#include <cmath>

namespace dcg{

class DStructType{
public:
	class FieldInfo{
	public:
		const size_t size;
		const size_t alignment;
	private:
		FieldInfo(size_t size, size_t alignment) : 
			size(size), alignment(alignment) {}
	public:
		template<class T>
		FieldInfo make(){ 
			size_t al = std::alignment_of<T>::value;
			return(FieldInfo(
				sizeof(T),
				al
			));
		}
	};

	class Field{
		const FieldInfo info;
		const size_t offset;
	public:
		Field(FieldInfo info, size_t offset) : 
			info(info), 
			offset(offset) 
		{}
		size_t getSize(){ return(info.size); }
		size_t getOffset(){ return(offset); }
	};

private:
	size_t size;
	vector<Field> fields;

public:
	DStructType(vector<FieldInfo> infos) {
		vector<size_t> indices(fields.size(), 0);
		std::sort(
			indices.begin(),
			indices.end(),
			[&infos](size_t i0, size_t i1) {
				return(infos[i0].size <= infos[i1].size);
			}
		);
		size_t s = 0;
		for(auto index : indices){
			FieldInfo info = infos[index];
			size_t align = info.alignment;
			fields.push_back(Field(
				info,
				std::ceil<size_t>(s + align - (s % align))
			));
		}
	};

	const vector<Field>& getFields(){ return(fields); }
	size_t getSize(){ return(size); }
};

}

#endif























/*



class DStructType{
public:
	class FieldInfo{
	public:
		const size_t size;
		const size_t alignment;
	public:
		template<class T>
		FieldInfo make(){
			return(FieldInfo(
				sizeof(T), 
				std::alignment_of<T>()::value
			);
		}
	private:
		FieldInfo(size_t size, size_t alignment) : 
			size(size), alignment(alignment) {}
	};

	class Field{
		const FieldInfo info;
		const size_t offset;
	public:
		Field(FieldInfo info, size_t offset) : 
			info(info), 
			offset(offset) 
		{}
		void getSize(){ return(info.size); }
		void getOffset(){ return(offset); }
	};

public:
	const size_t size;
private:
	vector<Field> fields;

public:
	DStructType(vector<FieldInfo> fields) : fields(fields) {
		vector<size_t> indices(fields.size(), 0);
		std::sort(
			indices.begin(),
			indices.end(),
			[&v](size_t i0, size_t i1) {
				return(v[i0].size <= v[i1].size);
			}
		);
		size_t s = 0;
		for(auto index : indices){
			FieldInfo info = fields[index];
			size_t align = info.alignment;
			fields.push_back(Field(
				info,
				ceil<size_t>(s + align - (s % align))
			));
		}
	};

	size_t numFields(){ return(fields.size()); }
	vector<Field>::iterator fieldsBegin(){ return(fields.begin()); }
	vector<Field>::iterator fieldsEnd(){ return(fields.end()); }
};




*/