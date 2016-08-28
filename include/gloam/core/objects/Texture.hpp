/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#include <algorithm> //min/max

#include "gloam/core/objects/GLObject.hpp"

#include "gloam/core/GLImage.hpp"

#include "gloam/core/objects/Framebuffer.hpp"

//using namespace stb;

namespace gloam{

//class FramebufferAttachment;//Defined in Framebuffer.hpp

//pretty much everything here is untested.
class Texture : 
	public GLObjectStandard, 
	public Binding
{
public:
	enum WrapParam : GLenum{
		REPEAT = GL_REPEAT,
		MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
		CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
		CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER
	};

	enum FilterParam : GLenum{
		NEAREST = GL_NEAREST,
		LINEAR = GL_LINEAR,
		NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
		LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
		NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
		LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
	};

private:
	int width, height, numComponents;

public:
	Texture(
		s_ptr<TextureTarget> target
	) : 
		GLObjectStandard(glGenTextures, glDeleteTextures),
		Binding(GLObject::id, target)
	{
		//bind();
		//
	}
	virtual ~Texture() {}

	//related to mipmapping.
	void setParam_filters(FilterParam min, FilterParam mag){
		Binding::push();
		glTexParameteri(Binding::getTarget()->name, GL_TEXTURE_MIN_FILTER, min);
		glTexParameteri(Binding::getTarget()->name, GL_TEXTURE_MAG_FILTER, mag);
		Binding::pop();
	}
	
	void setParam_wrap(WrapParam s){
		Binding::push();
		glTexParameteri(Binding::getTarget()->name, GL_TEXTURE_WRAP_S, s);
		Binding::pop();
	}
	void setParam_wrap(WrapParam s, WrapParam t){
		Binding::push();
		glTexParameteri(Binding::getTarget()->name, GL_TEXTURE_WRAP_S, s);
		glTexParameteri(Binding::getTarget()->name, GL_TEXTURE_WRAP_T, t);
		Binding::pop();
	}
	void setParam_wrap(WrapParam s, WrapParam t, WrapParam r){
		Binding::push();
		glTexParameteri(Binding::getTarget()->name, GL_TEXTURE_WRAP_S, s);
		glTexParameteri(Binding::getTarget()->name, GL_TEXTURE_WRAP_T, t);
		glTexParameteri(Binding::getTarget()->name, GL_TEXTURE_WRAP_R, r);
		Binding::pop();
	}

	void image1D(s_ptr<GLImage> image, SizedInternalFormat_t internalFormat){
		Binding::push();
		glTexImage1D(
			Binding::getTarget()->name, 
			0, 
			internalFormat, 
			image->dims[0], 
			0, 
			image->format, 
			image->pixelType, 
			image->getData()
		);
		Binding::pop();
	}
	void image2D(s_ptr<GLImage> image, SizedInternalFormat_t internalFormat){
		Binding::push();
		glTexImage2D(
			Binding::getTarget()->name, 
			0, 
			internalFormat, 
			image->dims[0], 
			image->dims[1], 
			0, 
			image->format, 
			image->pixelType, 
			image->getData()
		);
		Binding::pop();
	}
	void image3D(s_ptr<GLImage> image, SizedInternalFormat_t internalFormat){
		Binding::push();
		glTexImage3D(
			Binding::getTarget()->name, 
			0, 
			internalFormat, 
			image->dims[0], 
			image->dims[1], 
			image->dims[2], 
			0, 
			image->format, 
			image->pixelType, 
			image->getData()
		);
		Binding::pop();
	}

	void subImage1D(s_ptr<GLImage> image, GLsizei x){
		Binding::push();
		glTexSubImage1D(
			Binding::getTarget()->name,
			0,
			x,
			image->dims[0],
			image->format,
			image->pixelType,
			image->getData()
		);
		Binding::pop();
	}
	void subImage2D(s_ptr<GLImage> image, GLsizei x, GLsizei y){
		Binding::push();
		glTexSubImage2D(
			Binding::getTarget()->name,
			0,
			x,
			y,
			image->dims[0],
			image->dims[1],
			image->format,
			image->pixelType,
			image->getData()
		);
		Binding::pop();
	}
	void subImage3D(s_ptr<GLImage> image, GLsizei x, GLsizei y, GLsizei z){
		Binding::push();
		glTexSubImage3D(
			Binding::getTarget()->name,
			0,
			x,
			y,
			z,
			image->dims[0],
			image->dims[1],
			image->dims[2],
			image->format,
			image->pixelType,
			image->getData()
		);
		Binding::pop();
	}

	void bind(){ Binding::bind(); }
	bool isBound(){ return(Binding::isBound()); }

	void genMipmap(){
		Binding::push();
		glGenerateMipmap(Binding::getTarget()->name);
		Binding::pop();
	}
};

}

#endif



























/*

glTexParameteri(target, GL_TEXTURE_WRAP_S, wrapS);
glTexParameteri(target, GL_TEXTURE_WRAP_T, wrapT);
//
glTexParameterf(target, GL_TEXTURE_MIN_FILTER, filterMin);
glTexParameterf(target, GL_TEXTURE_MAG_FILTER, filterMax);
//
//glTexImage2D(target, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);


	//tex is repeated to fill the entire space.
	Texture(int width, int height, Texture tex);

	~Texture() {}
	
	//
	
	//releases just the non-gpu memory.
	void releaseData();

	//

	//void drawRect(Rect<int> rect, byte_t* image);
	void drawSingleTexture(Texture tex, int x, int y);
	
	void drawRepeatingTexture(Texture tex, Rect<int> area);

	void drawColor(Rect<int> area, byte_t r, byte_t g, byte_t b, byte_t a);

	//r0 is the bottom color, r1 is the top.
	void drawColorGradiant(Rect<int> area, byte_t r0, byte_t g0, byte_t b0, 
		byte_t r1, byte_t g1, byte_t b1, byte_t a);

	//

	byte_t* getData(){ return(data); }

//private:

	//void brightenColor(float brightness);

//data
private:
	//int numComponents;
	//int width, height;
	//byte_t* data;
	//int elementSize;*/
