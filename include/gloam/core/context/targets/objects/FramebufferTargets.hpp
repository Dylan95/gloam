/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_FRAMEBUFFER_TARGETS_INCLUDED
#define DCG_FRAMEBUFFER_TARGETS_INCLUDED

#include "gloam/core/context/targets/Target.hpp"

namespace gloam{



class FramebufferTarget : public Target_Standard{
public:
	FramebufferTarget(GLenum name) : Target_Standard(glBindFramebuffer, name) {}
};


class FramebufferTargetsContext{
public:
	FramebufferTargetsContext() {}

public:
	std::shared_ptr<FramebufferTarget> READ_FRAMEBUFFER = std::make_shared<FramebufferTarget>(GL_READ_FRAMEBUFFER); 
	std::shared_ptr<FramebufferTarget> DRAW_FRAMEBUFFER = std::make_shared<FramebufferTarget>(GL_DRAW_FRAMEBUFFER); 
	//both reading and drawing
	std::shared_ptr<FramebufferTarget> FRAMEBUFFER = std::make_shared<FramebufferTarget>(GL_FRAMEBUFFER);
};

}

#endif
