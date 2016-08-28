/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_TYPES_BASIC_TYPES_INCLUDED
#define DCG_TYPES_BASIC_TYPES_INCLUDED

//renaming some basic data types
namespace dcg{

//typedef std::uint32_t uint;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned long ulong;

//typedef unsigned __int8 byte_t;				//I find this easyer to remember
typedef unsigned char byte_t;				//I find this easyer to remember

//a chunk of memory.
//typedef vector<byte_t> 				Bytes;
//typedef vector<byte_t>::iterator 	BytesIter;

}

#endif
