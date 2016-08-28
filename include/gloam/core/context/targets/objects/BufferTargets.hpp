/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_BUFFER_TARGETS_INCLUDED
#define DCG_BUFFER_TARGETS_INCLUDED

#include "gloam/core/context/targets/Target.hpp"

namespace gloam{



class BufferTarget : public Target_Standard{
public:
	BufferTarget(GLenum name) : Target_Standard(glBindBuffer, name) {}
};


class BufferTargetsContext{
public:
	BufferTargetsContext() {}
public:
	//Vertex attributes
	std::shared_ptr<BufferTarget> ARRAY_BUFFER = std::make_shared<BufferTarget>(GL_ARRAY_BUFFER);
	//Atomic counter storage
	std::shared_ptr<BufferTarget> ATOMIC_COUNTER_BUFFER = std::make_shared<BufferTarget>(GL_ATOMIC_COUNTER_BUFFER);
	//Buffer copy source
	std::shared_ptr<BufferTarget> COPY_READ_BUFFER = std::make_shared<BufferTarget>(GL_COPY_READ_BUFFER);
	//Buffer copy destination
	std::shared_ptr<BufferTarget> COPY_WRITE_BUFFER = std::make_shared<BufferTarget>(GL_COPY_WRITE_BUFFER);
	//Indirect compute dispatch commands
	std::shared_ptr<BufferTarget> DISPATCH_INDIRECT_BUFFER = std::make_shared<BufferTarget>(GL_DISPATCH_INDIRECT_BUFFER);
	//Indirect command arguments
	std::shared_ptr<BufferTarget> DRAW_INDIRECT_BUFFER = std::make_shared<BufferTarget>(GL_DRAW_INDIRECT_BUFFER);
	//Vertex array indices
	std::shared_ptr<BufferTarget> ELEMENT_ARRAY_BUFFER = std::make_shared<BufferTarget>(GL_ELEMENT_ARRAY_BUFFER);
	//Pixel read target
	std::shared_ptr<BufferTarget> PIXEL_PACK_BUFFER = std::make_shared<BufferTarget>(GL_PIXEL_PACK_BUFFER);
	//Texture data source
	std::shared_ptr<BufferTarget> PIXEL_UNPACK_BUFFER = std::make_shared<BufferTarget>(GL_PIXEL_UNPACK_BUFFER);
	//Query result buffer
	std::shared_ptr<BufferTarget> QUERY_BUFFER = std::make_shared<BufferTarget>(GL_QUERY_BUFFER);
	//Read-write storage for shaders
	std::shared_ptr<BufferTarget> SHADER_STORAGE_BUFFER = std::make_shared<BufferTarget>(GL_SHADER_STORAGE_BUFFER);
	//Texture data buffer
	std::shared_ptr<BufferTarget> TEXTURE_BUFFER = std::make_shared<BufferTarget>(GL_TEXTURE_BUFFER);
	//Transform feedback buffer
	std::shared_ptr<BufferTarget> TRANSFORM_FEEDBACK_BUFFER = std::make_shared<BufferTarget>(GL_TRANSFORM_FEEDBACK_BUFFER);
	//Uniform block storage
	std::shared_ptr<BufferTarget> UNIFORM_BUFFER = std::make_shared<BufferTarget>(GL_UNIFORM_BUFFER);
};

}

#endif
