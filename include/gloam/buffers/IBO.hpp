/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_ELEM_ARRAY_BUFF_INCLUDED
#define DCG_ELEM_ARRAY_BUFF_INCLUDED

#include "gloam/core/util/util.hpp"

#include "gloam/core/core.hpp"

namespace gloam{

//index buffer object, stores trianges.
class IBO : protected Buffer_Mutable{
	s_ptr<vector<uint>> indices;

public:
	/*IBO(Context& context, s_ptr<vector<uint>> indices, Usage::Frequency freq) : 
		Buffer_Mutable(context.targets.bufferTargets.ELEMENT_ARRAY_BUFFER), 
		indices(indices)
	{
		buffer(freq);
	}*/
	IBO(Context& context, s_ptr<vector<uint>> indices) : 
		Buffer_Mutable(context.targets.bufferTargets.ELEMENT_ARRAY_BUFFER), 
		indices(indices)
	{
		//buffer(freq);
	}
	virtual ~IBO() {}

	void draw(DrawMode_t mode = DrawMode::TRIANGLES){
		Buffer::bind();
		//glDrawElementsBaseVertex(GL_TRIANGLES, id, GL_UNSIGNED_INT, 0, 0);
		glDrawElements(GL_TRIANGLES, indices->size(), GL_UNSIGNED_INT, 0);
	}

//private:
	void buffer(Usage::Frequency freq){
		Buffer_Mutable::bufferData(
			indices->size() * sizeof(uint),
			indices->data(),
			make_c<Usage>(freq, Usage::Nature::DRAW)
		);
	}
};

}

#endif
