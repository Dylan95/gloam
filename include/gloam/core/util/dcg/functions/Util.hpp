/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_FUNCTIONS_UTIL_INCLUDED
#define DCG_FUNCTIONS_UTIL_INCLUDED

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

#include <cassert>

//#include "dcg/types/types.hpp"

namespace dcg{

class Util{
public:
	template <typename T>
	vector<size_t> sort_indexes(const vector<T> &v) {
		vector<size_t> results(v.size(), 0);
		sort(
			results.begin(), 
			results.end(),
			[&v](size_t i0, size_t i1) {return v[i0] < v[i1];}
		);
	}

	void b_assert(bool b){
		assert(b);
	}

	void pause(){
		cout << "press any key to continue";
		cin.get();
	}

	template<class T, class ... Args>
	void emplaceAt(void* addr, Args... args){
		new(addr) T(args...);
	}

	//http://stackoverflow.com/questions/500493/c-equivalent-of-instanceof
	template<typename Base, typename T>
	//inline bool instanceof(const T*) {
	bool instanceof() {
		return std::is_base_of<Base, T>::value;
	}

	template<class T>
	static bool inRange(T val, T min, T max) {return((val >= min) && (val <= max));}

	template<class T>
	T intDivisionRound(T numerator, T denominator){
		T result = numerator / denominator;
		if((numerator % denominator) > (denominator / 2)){
			result++;
		}
		return(result);
	}
	int intDivisionRound(int numerator, int denominator){
		return(intDivisionRound<int>(numerator, denominator));
	}

	template<class T>
	T clampNum(T target, T min, T max){
		if(target < min)		{	return(min);	}
		else if(target > max)	{	return(max);	}
		else					{	return(target); }
	}
};

}

#endif




















































//inline int round(float num){	return((int) floor(num + 0.5f));	}
//inline int round(double num){	return((int) floor(num + 0.5));		}



/*template<class T, class U>
struct Iterable
{
	T _begin;
	U _end;

	Iterable(T begin, U end);

	T begin();

	U end();
};*/
