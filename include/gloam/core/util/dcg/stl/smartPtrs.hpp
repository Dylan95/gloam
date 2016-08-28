/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_STL_SMART_PTRS_INCLUDED
#define DCG_STL_SMART_PTRS_INCLUDED

#include "dcg/stl/range_t.hpp"
#include "dcg/stl/c_vector.hpp"

#include <memory>
#include <string>

//common types and functions from the standard template library.
//and clean_stl_vector::vector in place of std::vector.

namespace dcg{

using std::string;

template<typename T>
using u_ptr = std::unique_ptr<T>;
//
template<typename T>
using s_ptr = std::shared_ptr<T>;
template<typename T>
using w_ptr = std::weak_ptr<T>;

using std::make_unique;
using std::make_shared;

//typedef std::make_unique make_u;
//typedef std::make_shared make_s;

}

#endif