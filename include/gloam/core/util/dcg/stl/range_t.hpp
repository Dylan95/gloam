/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_STL_RANGE_T_INCLUDED
#define DCG_STL_RANGE_T_INCLUDED

#include <iterator>
#include <vector>

namespace dcg{



//forward iterator
template<class T>
using ForwardIterator = std::iterator<std::forward_iterator_tag, T>;
template<class T>
using RangeIterator = ForwardIterator<T>;

//the most complicated type of iterator
template<class T>
using RandomAccessIter = std::iterator<std::random_access_iterator_tag, T>;

//range based for loop: for(item : container){ ... }

//'It' should be derived from RangeIter
template<class It>
class range_t{
public:
	virtual It begin() = 0;
	virtual It end() = 0;
};

//'It' should be derived from RangeIter
template<class T>
class PtrRange : range_t<T*>{
	T* mBegin;
	T* mEnd;
public:
	PtrRange(T* mBegin, T* mEnd) : mBegin(mBegin), mEnd(mEnd) {}
	PtrRange(T* mBegin, size_t n) : mBegin(mBegin), mEnd(mBegin + n) {}

	virtual T* begin(){ return(mBegin); }
	virtual T* end(){ return(mEnd); }
};

//'It' should be derived from RangeIter
template<class T>
class NumRange{
	T mBegin;
	T mEnd;
public:
	NumRange(T mBegin, T mEnd) : mBegin(mBegin), mEnd(mEnd) {}
	NumRange(T mBegin, size_t n) : mBegin(mBegin), mEnd(mBegin + n) {}

	virtual T begin(){ return(mBegin); }
	virtual T end(){ return(mEnd); }
};

}

#endif

































/*

template<class T>
using range_t_vector = range_t<typename std::vector<T>::iterator>;

template<class T>
using range_t_ptr = range_t<T*>;

*/



//for converting between smart pointers
//using std::dynamic_pointer_cast;


/*IterOut begin(range_t v){
	return(v.begin());
}

IterOut end(range_t v){
	return(v.end());
}*/

/*iterator begin(range_t r){
	return(r.begin());
}
iterator end(range_t r){
	return(r.end());
}*/






/*
example implementation:
class MyIterator : public std::iterator<std::input_iterator_tag, int>
{
  int* p;
public:
  MyIterator(int* x) :p(x) {}
  MyIterator(const MyIterator& mit) : p(mit.p) {}
  MyIterator& operator++() {++p;return *this;}
  MyIterator operator++(int) {MyIterator tmp(*this); operator++(); return tmp;}
  bool operator==(const MyIterator& rhs) {return p==rhs.p;}
  bool operator!=(const MyIterator& rhs) {return p!=rhs.p;}
  int& operator*() {return *p;}
};

template<class Tag, class T>
using Iter = std::iterator<Tag,T>;
*/
