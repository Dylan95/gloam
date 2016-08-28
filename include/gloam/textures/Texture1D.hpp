/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_TEXTURE_1D_INCLUDED
#define DCG_TEXTURE_1D_INCLUDED

#include "gloam/core/core.hpp"

namespace gloam{

class GLImage1D : public GLImage{
public:
	GLImage1D(
		GLsizei W, 
		ImageFormat_t format,
		PixelDataType_t pixelType
	) :
		GLImage(
			vector<GLsizei>(W),
			format, 
			pixelType
		)
	{}
};



class Texture1D : private Texture{
	SizedInternalFormat_t internalFormat;

public:
	Texture1D(
		Context& context,
		SizedInternalFormat_t internalFormat,
		WrapParam wrapS,
		FilterParam filterMin,
		FilterParam filterMag
	) : 
		Texture(context.targets.textureTargets.TEXTURE_1D),
		internalFormat(internalFormat)
	{
		Texture::setParam_wrap(wrapS);
		Texture::setParam_filters(filterMin, filterMag);
	}
	
	Texture1D(
		Context& context,
		SizedInternalFormat_t internalFormat
	) : 
		Texture1D(
			context,
			internalFormat,
			WrapParam::CLAMP_TO_EDGE,
			FilterParam::NEAREST,
			FilterParam::NEAREST
		)
	{}

	virtual ~Texture1D() {}

	void image(s_ptr<GLImage1D> image){ 
		Texture::image1D(image, internalFormat); 
	}
	void subImage(s_ptr<GLImage1D> image, GLsizei x){
		Texture::subImage1D(image, x);
	}

	void mipmap(){ Texture::genMipmap(); }
	
	bool isBound(){ return(Texture::isBound()); }
	void bind(){ Texture::bind(); }
	//void unbind(){ Texture::unbind(); }
};

}

#endif