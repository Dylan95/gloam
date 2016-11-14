
//AUTOGENERATED_TEXT_E6585F83424849_START
#ifndef INCLUDE_GAURD_E6585F83424849_INCLUDE_GLOAM_CORE_CONTEXT_DEFAULTFRAMEBUFFER_HPP
#define INCLUDE_GAURD_E6585F83424849_INCLUDE_GLOAM_CORE_CONTEXT_DEFAULTFRAMEBUFFER_HPP
//AUTOGENERATED_TEXT_E6585F83424849_END

//#include "gloam/core/util/util.hpp"
//#include "gloam/core/objects/Framebuffer.hpp"

//AUTOGENERATED_TEXT_E6585F83424849_START
namespace gloam{
//AUTOGENERATED_TEXT_E6585F83424849_END

//the framebuffer that opengl is initialized with.
//todo: add more functionality, access attachments.
//	derive from Framebuffer
class DefaultFramebuffer{
public:
	DefaultFramebuffer() {}

	//clear everything.
	void clear(){
		glClear(
			GL_COLOR_BUFFER_BIT |
			GL_DEPTH_BUFFER_BIT |
			GL_STENCIL_BUFFER_BIT
		);
	}

	void setClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a){
		glClearColor(r, g, b, a);
	}
};














/*class DefaultFramebufferClone : public Framebuffer{
public:
	DefaultFramebuffer(Context& context) : 
		Framebuffer(context.targets.framebuffers.DRAW_FRAMEBUFFER)
	{
		Framebuffer::COLOR_ATTACHMENT_v.push_back();
	}

	virtual ~Framebuffer_Draw(){}
};*/



//AUTOGENERATED_TEXT_E6585F83424849_START
}
#endif
/*Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
//AUTOGENERATED_TEXT_E6585F83424849_END