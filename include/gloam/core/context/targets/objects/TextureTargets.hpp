/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_TEXTURE_TARGETS_INCLUDED
#define DCG_TEXTURE_TARGETS_INCLUDED

#include "gloam/core/context/targets/Target.hpp"


namespace gloam{



class TextureTarget : public Target_Standard{
public:
	TextureTarget(GLenum name) : Target_Standard(glBindTexture, name) {}
};


class TextureTargetsContext{
public:
	TextureTargetsContext() {}

public:
	std::shared_ptr<TextureTarget> TEXTURE_1D = std::make_shared<TextureTarget>(GL_TEXTURE_1D); 
	std::shared_ptr<TextureTarget> TEXTURE_2D = std::make_shared<TextureTarget>(GL_TEXTURE_2D); 
	std::shared_ptr<TextureTarget> TEXTURE_3D = std::make_shared<TextureTarget>(GL_TEXTURE_3D); 
	std::shared_ptr<TextureTarget> TEXTURE_1D_ARRAY = std::make_shared<TextureTarget>(GL_TEXTURE_1D_ARRAY); 
	std::shared_ptr<TextureTarget> TEXTURE_2D_ARRAY = std::make_shared<TextureTarget>(GL_TEXTURE_2D_ARRAY); 
	std::shared_ptr<TextureTarget> TEXTURE_RECTANGLE = std::make_shared<TextureTarget>(GL_TEXTURE_RECTANGLE); 
	std::shared_ptr<TextureTarget> TEXTURE_CUBE_MAP = std::make_shared<TextureTarget>(GL_TEXTURE_CUBE_MAP); 
	std::shared_ptr<TextureTarget> TEXTURE_CUBE_MAP_ARRAY = std::make_shared<TextureTarget>(GL_TEXTURE_CUBE_MAP_ARRAY); 
	std::shared_ptr<TextureTarget> TEXTURE_BUFFER = std::make_shared<TextureTarget>(GL_TEXTURE_BUFFER); 
	std::shared_ptr<TextureTarget> TEXTURE_2D_MULTISAMPLE = std::make_shared<TextureTarget>(GL_TEXTURE_2D_MULTISAMPLE); 
	std::shared_ptr<TextureTarget> TEXTURE_2D_MULTISAMPLE_ARRAY = std::make_shared<TextureTarget>(GL_TEXTURE_2D_MULTISAMPLE_ARRAY);
};


}

#endif
