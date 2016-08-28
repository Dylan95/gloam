/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_GL_ENUMS_INCLUDED
#define DCG_GL_ENUMS_INCLUDED

namespace gloam{


typedef GLint SizedInternalFormat_t;
namespace SizedInternalFormat{
	//for color attachments
	const GLint R8 = GL_R8;
	const GLint R8UI = GL_R8UI;
	const GLint R8I = GL_R8I;
	const GLint R16UI = GL_R16UI;
	const GLint R16I = GL_R16I;
	const GLint R32UI = GL_R32UI;
	const GLint R32I = GL_R32I;
	const GLint RG8 = GL_RG8;
	const GLint RG8UI = GL_RG8UI;
	const GLint RG8I = GL_RG8I;
	const GLint RG16UI = GL_RG16UI;
	const GLint RG16I = GL_RG16I;
	const GLint RG32UI = GL_RG32UI;
	const GLint RG32I = GL_RG32I;
	const GLint RGB8 = GL_RGB8;
	const GLint RGB565 = GL_RGB565;
	const GLint RGBA8 = GL_RGBA8;
	const GLint SRGB8_ALPHA8 = GL_SRGB8_ALPHA8;
	const GLint RGB5_A1 = GL_RGB5_A1;
	const GLint RGBA4 = GL_RGBA4;
	const GLint RGB10_A2 = GL_RGB10_A2;
	const GLint RGBA8UI = GL_RGBA8UI;
	const GLint RGBA8I = GL_RGBA8I;
	const GLint RGB10_A2UI = GL_RGB10_A2UI;
	const GLint RGBA16UI = GL_RGBA16UI;
	const GLint RGBA16I = GL_RGBA16I;
	const GLint RGBA32I = GL_RGBA32I;
	const GLint RGBA32UI = GL_RGBA32UI;
	//for depth attachments
	const GLint DEPTH_COMPONENT16 = GL_DEPTH_COMPONENT16;
	const GLint DEPTH_COMPONENT24 = GL_DEPTH_COMPONENT24;
	const GLint DEPTH_COMPONENT32F = GL_DEPTH_COMPONENT32F;
	//for stencil attachments
	const GLint DEPTH24_STENCIL8 = GL_DEPTH24_STENCIL8;
	const GLint DEPTH32F_STENCIL8 = GL_DEPTH32F_STENCIL8;
	const GLint STENCIL_INDEX = GL_STENCIL_INDEX;
}


typedef GLint ImageFormat_t;
namespace ImageFormat{
	const GLint RED = GL_RED;
	const GLint RG = GL_RG;
	const GLint RGB = GL_RGB;
	const GLint BGR = GL_BGR;
	const GLint RGBA = GL_RGBA;
	const GLint BGRA = GL_BGRA;
	const GLint RED_INTEGER = GL_RED_INTEGER;
	const GLint RG_INTEGER = GL_RG_INTEGER;
	const GLint RGB_INTEGER = GL_RGB_INTEGER;
	const GLint BGR_INTEGER = GL_BGR_INTEGER;
	const GLint RGBA_INTEGER = GL_RGBA_INTEGER;
	const GLint BGRA_INTEGER = GL_BGRA_INTEGER;
	const GLint STENCIL_INDEX = GL_STENCIL_INDEX;
	const GLint DEPTH_COMPONENT = GL_DEPTH_COMPONENT;
	const GLint DEPTH_STENCIL = GL_DEPTH_STENCIL;
}


typedef GLint ReadPixelsFormat_t;
namespace ReadPixelsFormat{
	const GLint STENCIL_INDEX = GL_STENCIL_INDEX;
	const GLint DEPTH_COMPONENT = GL_DEPTH_COMPONENT;
	const GLint DEPTH_STENCIL = GL_DEPTH_STENCIL;
	const GLint RED = GL_RED;
	const GLint GREEN = GL_GREEN;
	const GLint BLUE = GL_BLUE;
	const GLint RGB = GL_RGB;
	const GLint BGR = GL_BGR;
	const GLint RGBA = GL_RGBA;
	const GLint BGRA = GL_BGRA;
}


typedef GLint PixelDataType_t;
namespace PixelDataType{
	const GLint UNSIGNED_BYTE = GL_UNSIGNED_BYTE;
	const GLint BYTE = GL_BYTE;
	const GLint UNSIGNED_SHORT = GL_UNSIGNED_SHORT;
	const GLint SHORT = GL_SHORT;
	const GLint UNSIGNED_INT = GL_UNSIGNED_INT;
	const GLint INT = GL_INT;
	const GLint FLOAT = GL_FLOAT;
	const GLint UNSIGNED_BYTE_3_3_2 = GL_UNSIGNED_BYTE_3_3_2;
	const GLint UNSIGNED_BYTE_2_3_3_REV = GL_UNSIGNED_BYTE_2_3_3_REV;
	const GLint UNSIGNED_SHORT_5_6_5 = GL_UNSIGNED_SHORT_5_6_5;
	const GLint UNSIGNED_SHORT_5_6_5_REV = GL_UNSIGNED_SHORT_5_6_5_REV;
	const GLint UNSIGNED_SHORT_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4;
	const GLint UNSIGNED_SHORT_4_4_4_4_REV = GL_UNSIGNED_SHORT_4_4_4_4_REV;
	const GLint UNSIGNED_SHORT_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1;
	const GLint UNSIGNED_SHORT_1_5_5_5_REV = GL_UNSIGNED_SHORT_1_5_5_5_REV;
	const GLint UNSIGNED_INT_8_8_8_8 = GL_UNSIGNED_INT_8_8_8_8;
	const GLint UNSIGNED_INT_8_8_8_8_REV = GL_UNSIGNED_INT_8_8_8_8_REV;
	const GLint UNSIGNED_INT_10_10_10_2 = GL_UNSIGNED_INT_10_10_10_2;
	const GLint UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV;
}


typedef GLenum DrawMode_t;
namespace DrawMode{
	const GLenum POINTS = GL_POINTS;
	const GLenum LINE_STRIP = GL_LINE_STRIP;
	const GLenum LINE_LOOP = GL_LINE_LOOP;
	const GLenum LINES = GL_LINES;
	const GLenum LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY;
	const GLenum LINES_ADJACENCY = GL_LINES_ADJACENCY;
	const GLenum TRIANGLE_STRIP = GL_TRIANGLE_STRIP;
	const GLenum TRIANGLE_FAN = GL_TRIANGLE_FAN;
	const GLenum TRIANGLES = GL_TRIANGLES;
	const GLenum TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY;
	const GLenum TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY;
	const GLenum PATCHES = GL_PATCHES;
}

}

#endif
