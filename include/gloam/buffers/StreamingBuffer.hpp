/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_STREAMING_BUFFER_INCLUDED
#define DCG_STREAMING_BUFFER_INCLUDED

#include "gloam/core/core.hpp"

namespace gloam{

class StreamingBuffer : public Buffer_Mutable{
private:
	size_t size = 0;

public:
	StreamingBuffer(Context& context)
		: Buffer_Mutable(context.targets.bufferTargets.ARRAY_BUFFER)
	{}

	virtual ~StreamingBuffer(){}

	void bind(){ Buffer::bind(); }

	void update(void* data, size_t size){
		orphan();
		bufferData(data, size);
	}

protected:
	void bufferData(void* data, size_t size){
		/*Buffer_Mutable::bufferData(
			size, 
			data,
			Usage(Usage::Frequency::STREAM, Usage::Nature::DRAW)
		);
		this->size = size;*/
	}
};

}

#endif
