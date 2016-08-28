/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_FUNCTIONS_STRING_INCLUDED
#define DCG_FUNCTIONS_STRING_INCLUDED

#include "dcg/stl/common.hpp"

namespace dcg{

class String{
	std::vector<std::string> split(const std::string &s, char delim){
		vector<string> elems;
		//
		const char* cstr = s.c_str();
		uint strLength = s.length();
		uint start = 0;
		uint end = 0;
		//
		while(end <= strLength)
		{
			while(end <= strLength)
			{
				if(cstr[end] == delim)
				break;
				end++;
			}
			//
			elems.push_back(s.substr(start, end - start));
			start = end + 1;
			end = start;
		}
		//
		return elems;
	}

	//shorten string with ... if it's too short.
	string shortenString(string s, uint pixelWidth, uint fontSize){
		string result;
		uint maxCharCount = pixelWidth / fontSize;
		//
		assert(maxCharCount >= 4);
		if(s.size() > maxCharCount){
			result = s.substr(0, maxCharCount - 4) + "...";
		}
		return(result);
	}

	vector<char> makeCString(const string& s){
		return(vector<char>(s.c_str(), s.c_str() + s.size() + 1));
	}
};

}

#endif
