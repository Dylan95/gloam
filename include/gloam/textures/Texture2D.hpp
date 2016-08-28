/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_TEXTURE_2D_INCLUDED
#define DCG_TEXTURE_2D_INCLUDED

#include "gloam/core/core.hpp"

namespace gloam{

class GLImage2D : public GLImage{
public:
	GLImage2D(
		GLsizei W, 
		GLsizei H, 
		ImageFormat_t format,
		PixelDataType_t pixelType
	) :
		GLImage(
			vector<GLsizei>({W, H}),
			format, 
			pixelType
		)
	{}
};


class Texture2D : private Texture{
	SizedInternalFormat_t internalFormat;

public:
	Texture2D(
		Context& context,
		SizedInternalFormat_t internalFormat,
		WrapParam wrapS,
		WrapParam wrapT,
		FilterParam filterMin,
		FilterParam filterMag
	) : 
		Texture(context.targets.textureTargets.TEXTURE_2D),
		internalFormat(internalFormat)
	{
		Texture::setParam_wrap(wrapS, wrapT);
		Texture::setParam_filters(filterMin, filterMag);
	}
	
	Texture2D(
		Context& context,
		SizedInternalFormat_t internalFormat
	) : 
		Texture2D(
			context,
			internalFormat,
			WrapParam::CLAMP_TO_EDGE,
			WrapParam::CLAMP_TO_EDGE,
			FilterParam::NEAREST,
			FilterParam::NEAREST
		)
	{}

	virtual ~Texture2D() {}

	void image(s_ptr<GLImage2D> image){ 
		Texture::image2D(image, internalFormat); 
	}
	void subImage(s_ptr<GLImage2D> image, GLsizei x, GLsizei y){
		Texture::subImage2D(image, x, y);
	}

	void mipmap(){ Texture::genMipmap(); }
	
	bool isBound(){ return(Texture::isBound()); }
	void bind(){ Texture::bind(); }
	//void unbind(){ Texture::unbind(); }
};

}


#endif
