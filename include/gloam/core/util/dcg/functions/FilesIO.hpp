/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_FUNCTIONS_FILES_IO_INCLUDED
#define DCG_FUNCTIONS_FILES_IO_INCLUDED

#include <fstream>
#include <memory>

#include "dcg/stl/common.hpp"
#include "dcg/stl/smartPtrs.hpp"
#include "dcg/types/Chunk.hpp"

namespace dcg{

class FilesIO{
public:
	//string fileToString(const std::string& filename);
	static string fileToString(const std::string& filename){
		std::ifstream in(filename);
		std::stringstream buff;
		buff << in.rdbuf();
		return(buff.str());
	}

	static s_ptr<Chunk> fileToChunk(const std::string& filename){
		s_ptr<Chunk> result;
		//
		std::ifstream in(filename, std::ios::binary | std::ios::ate);
		std::streamsize size = in.tellg();
		result = make_shared<Chunk>(size);
		in.seekg(0, std::ios::beg);
		assert(in.read((char*) result->data(), size));
	}
};

}

#endif
