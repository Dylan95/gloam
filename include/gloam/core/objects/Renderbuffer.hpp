/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_RENDERBUFFER_INCLUDED
#define DCG_RENDERBUFFER_INCLUDED

#include "gloam/core/objects/GLObject.hpp"
#include "gloam/core/Binding.hpp"
#include "Framebuffer.hpp"

namespace gloam{

class Renderbuffer : 
	public GLObjectStandard, 
	public Binding
{
private:
	//internalformat
	//Specifies the color-renderable, depth-renderable, or 
	//stencil-renderable format of the renderbuffer. 
	//Must be one of the following symbolic constants: 
	//GL_RGBA4, GL_RGB565, GL_RGB5_A1, GL_DEPTH_COMPONENT16, or GL_STENCIL_INDEX8.
	GLenum format;
	uint W, H;
	
public:
	Renderbuffer(s_ptr<RenderbufferTarget> target, uint W, uint H, GLenum format) : 
		GLObjectStandard(glGenRenderbuffers, glDeleteRenderbuffers),
		Binding(GLObject::id, target),
		W(W), 
		H(H), 
		format(format)
	{
		Binding::push();
		glRenderbufferStorage(GL_RENDERBUFFER, format, W, H);
		Binding::pop();
	}

	virtual ~Renderbuffer() {}
	
	vector<byte_t> read(){
		/*glReadBuffer(GL_COLOR_ATTACHMENT0);
		//CHECK
		//glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		//glReadPixels(0, 0, W, H, GL_BGRA, GL_UNSIGNED_BYTE, pixelData);
		//
		glReadPixels(0, 0, W, H, GL_BGR, GL_UNSIGNED_BYTE, pixelData);
		//CHECK
		//
		return(pixelData);*/
	}
};

}

#endif
