/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_M_VECTOR_INCLUDED
#define DCG_M_VECTOR_INCLUDED

#include "dcg/stl/common.hpp"

namespace dcg{

//multidimentional vector
/*template<class T>
class MVector : public vector<T>{
	size_t W = 0;
	size_t H = 0;

public:
	MVector() : vector<T>(), W(0), H(0) {}
	MVector(size_t W, size_t H) : vector<T>(), W(0), H(0) {}

	vector();
	explicit MVector(const allocator_type& alloc) :
		vector<T>(alloc) {}
	//fill (2)	
	explicit MVector (size_type n, const allocator_type& alloc = allocator_type()) :
		vector<T>(n, alloc) {}
	vector (size_type n, const value_type& val, const allocator_type& alloc = allocator_type());
		vector<T>(n, alloc) {}
	//range (3)	
	template <class InputIterator>
	  vector (InputIterator first, InputIterator last,
			  const allocator_type& alloc = allocator_type());
	//copy (4)	
	vector (const vector& x);
	vector (const vector& x, const allocator_type& alloc);
	//move (5)	
	vector (vector&& x);
	vector (vector&& x, const allocator_type& alloc);
	//initializer list (6)	
	vector (initializer_list<value_type> il,
		   const allocator_type& alloc = allocator_type());
};*/

}

#endif
