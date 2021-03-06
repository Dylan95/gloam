
//AUTOGENERATED_TEXT_E6585F83424849_START
#ifndef INCLUDE_GAURD_E6585F83424849_INCLUDE_GLOAM_CORE_UTIL_DCG_FUNCTIONS_PARAMPACK_HPP
#define INCLUDE_GAURD_E6585F83424849_INCLUDE_GLOAM_CORE_UTIL_DCG_FUNCTIONS_PARAMPACK_HPP
//AUTOGENERATED_TEXT_E6585F83424849_END

#include <tuple>
#include <memory>

//AUTOGENERATED_TEXT_E6585F83424849_START
namespace gloam{
//AUTOGENERATED_TEXT_E6585F83424849_END

//utility functions for parameter packs, aka variadic templates.
class ParamPack{
	//example:
	//	getType<0, Ts>* first(){ return((getType<0, Ts>*) data); }
	template<size_t index, class ... Ts>
	using getType = std::tuple_element<index, std::tuple<Ts ...>>;

	template<class ... Ts>
	size_t numTypes(){ return(std::tuple_size<std::tuple<Ts ...>>::value); }
};

//AUTOGENERATED_TEXT_E6585F83424849_START
}
#endif
/*Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
//AUTOGENERATED_TEXT_E6585F83424849_END
