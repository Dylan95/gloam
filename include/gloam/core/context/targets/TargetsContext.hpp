/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_TARGETS_CONTEXT_INCLUDED
#define DCG_TARGETS_CONTEXT_INCLUDED

#include "gloam/core/context/targets/objects/BufferTargets.hpp"
#include "gloam/core/context/targets/objects/FramebufferTargets.hpp"
#include "gloam/core/context/targets/objects/ProgramTarget.hpp"
#include "gloam/core/context/targets/objects/RenderbufferTarget.hpp"
#include "gloam/core/context/targets/objects/TextureTargets.hpp"
#include "gloam/core/context/targets/objects/VertexArrayTarget.hpp"

#include "gloam/core/util/util.hpp"

namespace gloam{



class TargetsContext{
public:
	TargetsContext() {}

public:
	const BufferTargetsContext 					bufferTargets;
	const FramebufferTargetsContext 			framebufferTarget;
	const std::shared_ptr<ProgramTarget> 		programTarget = std::make_shared<ProgramTarget>();
	const std::shared_ptr<RenderbufferTarget> 	renderbufferTarget = std::make_shared<RenderbufferTarget>();
	const TextureTargetsContext 				textureTargets;
	const std::shared_ptr<VertexArrayTarget> 	vertexArrayTarget = 	std::make_shared<VertexArrayTarget>();
};

}

#endif
