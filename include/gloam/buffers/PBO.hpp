/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_PBO_INCLUDED
#define DCG_PBO_INCLUDED

//#include "main.hpp"
#include "gloam/core/core.hpp"

namespace gloam{

//const unsigned short NUM_RENDER_BUFFERS = 3;

//Every function that performs a pixel transfer operation can use 
//buffer objects instead of client memory. Functions that perform
//an upload operation, a pixel unpack, will use the buffer 
//object bound to the target GL_PIXEL_UNPACK_BUFFER. Functions that 
//perform a download operation, a pixel pack, will use the buffer 
//object bound to the GL_PIXEL_PACK_BUFFER.
//
//These functions only use buffer objects if one is bound to
//that particular binding point when the function is called. 
//If a buffer is bound, then the pointer value that those functions
//take is not a pointer, but an offset from the beginning of that buffer.

//used for rendering data offscreen and getting it into system memory.
class PBO : private Buffer_Mutable{
private:
	uint W, H;

public:
	PBO(Context& context, uint W, uint H, bool b_upload) : 
		Buffer_Mutable(
			b_upload ? 
				context.targets.bufferTargets.PIXEL_PACK_BUFFER :
				context.targets.bufferTargets.PIXEL_UNPACK_BUFFER
		),
		W(W), 
		H(H)
	{
		//b_upload ? GL_PIXEL_PACK_BUFFER : GL_PIXEL_UNPACK_BUFFER
		//glBindBuffer(GL_PIXEL_PACK_BUFFER, pbo);
		//glBufferData(GL_PIXEL_PACK_BUFFER, W*H*4, NULL, GL_DYNAMIC_READ);
	}
	virtual ~PBO() {}

	void bind(){ Buffer_Mutable::bind(); }

	//void unbind(){ Buffer_Mutable::unbind(); }

	void* map(){
		return(Buffer::mapBufferRange(
			0,
			W*H*4,
			Buffer::MapAccess::MAP_READ_BIT
		));
	}
};

/*class PBO_Download : PBO{
public:
	PBO_Download(uint W, uint H) : PBO(W, H, false){
		
	}
};

class PBO_Upload : PBO{
public:
	PBO_Upload(uint W, uint H) : PBO(W, H, true){
		
	}
};*/

}

#endif
