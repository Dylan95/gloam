/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_STL_VECTOR_INCLUDED
#define DCG_STL_VECTOR_INCLUDED

#include <vector>


namespace dcg{


//the std::vector class has what many programmers, including myself, consider a design flaw:
//std::vector<bool> is specified differently than other vector types:
//the bools are stored in bits by default, so it cannot be used as a collection.  
//This can be obnoxious to deal with.
//
//this adaptation of std::vector is just like std::vector, except that 
//vector<bool> is a normal collection of bools, just like any other type.
//
//the 'c' in c_vector is short for "collection".


template<class T, class Alloc = std::allocator<T>>
class c_vector : public std::vector<T, Alloc>{
	typedef std::vector<T, Alloc> base;
	using base::base;
};


namespace detail{
	class BoolWrapper{
	private:
		bool b;
	public:
		//implicitly construct
		BoolWrapper(bool b) : b(b) {}
		//implicit convert
		operator bool(){ return(b); }
	};
}


template<>
class c_vector<bool> : public c_vector<detail::BoolWrapper>{
	typedef vector<detail::BoolWrapper> base;
	using base::base;
};


}

#endif
