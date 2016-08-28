/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_PIXEL_STORE_CONTEXT_INCLUDED
#define DCG_PIXEL_STORE_CONTEXT_INCLUDED

#include "gloam/core/context/State.hpp"

#include "gloam/core/util/util.hpp"

namespace gloam{



class PixelStoreParam : State<float>{
private:
	float f;

public:
	PixelStoreParam(GLenum name) : State(name) {}
	virtual ~PixelStoreParam() {}

	void set(float f){
		State<float>::val = f;
		glPixelStoref(State<float>::name, f);
	}
};



class PixelStoreContext_Unpack{
public:
	PixelStoreContext_Unpack() {}

public:
	std::shared_ptr<PixelStoreParam> SWAP_BYTES = std::make_shared<PixelStoreParam>(GL_PACK_SWAP_BYTES);
	std::shared_ptr<PixelStoreParam> LSB_FIRST = std::make_shared<PixelStoreParam>(GL_PACK_LSB_FIRST);
	std::shared_ptr<PixelStoreParam> ROW_LENGTH = std::make_shared<PixelStoreParam>(GL_PACK_ROW_LENGTH);
	std::shared_ptr<PixelStoreParam> IMAGE_HEIGHT = std::make_shared<PixelStoreParam>(GL_PACK_IMAGE_HEIGHT);
	std::shared_ptr<PixelStoreParam> SKIP_ROWS = std::make_shared<PixelStoreParam>(GL_PACK_SKIP_ROWS);
	std::shared_ptr<PixelStoreParam> SKIP_PIXELS = std::make_shared<PixelStoreParam>(GL_PACK_SKIP_PIXELS);
	std::shared_ptr<PixelStoreParam> SKIP_IMAGES = std::make_shared<PixelStoreParam>(GL_PACK_SKIP_IMAGES);
	std::shared_ptr<PixelStoreParam> ALIGNMENT = std::make_shared<PixelStoreParam>(GL_PACK_ALIGNMENT);
};


class PixelStoreContext_Pack{
public:
	PixelStoreContext_Pack() {}

public:
	std::shared_ptr<PixelStoreParam> SWAP_BYTES = std::make_shared<PixelStoreParam>(GL_UNPACK_SWAP_BYTES);
	std::shared_ptr<PixelStoreParam> LSB_FIRST = std::make_shared<PixelStoreParam>(GL_UNPACK_LSB_FIRST);
	std::shared_ptr<PixelStoreParam> ROW_LENGTH = std::make_shared<PixelStoreParam>(GL_UNPACK_ROW_LENGTH);
	std::shared_ptr<PixelStoreParam> IMAGE_HEIGHT = std::make_shared<PixelStoreParam>(GL_UNPACK_IMAGE_HEIGHT);
	std::shared_ptr<PixelStoreParam> SKIP_ROWS = std::make_shared<PixelStoreParam>(GL_UNPACK_SKIP_ROWS);
	std::shared_ptr<PixelStoreParam> SKIP_PIXELS = std::make_shared<PixelStoreParam>(GL_UNPACK_SKIP_PIXELS);
	std::shared_ptr<PixelStoreParam> SKIP_IMAGES = std::make_shared<PixelStoreParam>(GL_UNPACK_SKIP_IMAGES);
	std::shared_ptr<PixelStoreParam> ALIGNMENT = std::make_shared<PixelStoreParam>(GL_UNPACK_ALIGNMENT);
};


}

#endif