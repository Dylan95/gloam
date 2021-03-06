
//AUTOGENERATED_TEXT_E6585F83424849_START
#ifndef INCLUDE_GAURD_E6585F83424849_INCLUDE_GLOAM_BUFFERS_VBOS_VBO_SINGLE_HPP
#define INCLUDE_GAURD_E6585F83424849_INCLUDE_GLOAM_BUFFERS_VBOS_VBO_SINGLE_HPP
//AUTOGENERATED_TEXT_E6585F83424849_END

#include "gloam/core/core.hpp"

//AUTOGENERATED_TEXT_E6585F83424849_START
namespace gloam{
//AUTOGENERATED_TEXT_E6585F83424849_END

template<class T>
class VBO_Single : public VBO{
private:
	//c_vector to avoid std::vector<bool> specialization.
	s_ptr<c_vector<T>> data;

public:
	VBO_Single(
		Context& context, 
		s_ptr<c_vector<T>> data
	)
		: VBO(context), data(data)
	{}

	virtual ~VBO_Single(){}

	virtual void bufferData(Usage::Frequency freq = Buffer_Mutable::Usage::Frequency::STATIC){
		VBO::bufferData(
			data->data(),
			data->size() * sizeof(T),
			freq
		);
	}

	virtual vector<Access> getArrayAccessors() { 
		return(vector<Access>({Access(
			sizeof(T),
			0
		)})); 
	}
	
	s_ptr<c_vector<T>> getData(){ return(data); }
	//virtual void* data(){ return(data->data()); }
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
