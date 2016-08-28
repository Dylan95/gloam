/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_CONTEXT_INCLUDED
#define DCG_CONTEXT_INCLUDED

#include "gloam/core/context/pixel_store/PixelStoreContext.hpp"
#include "gloam/core/context/targets/TargetsContext.hpp"
#include "gloam/core/context/Capabilities.hpp"

#include "gloam/core/context/DefaultFramebuffer.hpp"

namespace gloam{

class Context{
	float version;

public:
	Context() :
		version(getVersion())
	{
		assert(version >= 3.2f);
		setErrorCallback();
	}

public:
	const TargetsContext targets;
	const PixelStoreContext_Pack pixelStore_pack;
	const PixelStoreContext_Unpack pixelStore_unpack;
	const Capabilities capabilities;
	DefaultFramebuffer defaultFramebuffer;

private:
	float getVersion(){
		GLint minor, major;
		glGetIntegerv(GL_MAJOR_VERSION, &major); 
		glGetIntegerv(GL_MINOR_VERSION, &minor);
		return((float)major + (0.1f * (float)minor));
	}

	void setErrorCallback(){
		//requires version 4.3 or greater.
		//glDebugMessageCallback(
		glDebugMessageCallbackARB(
			[](
				GLenum source,
				GLenum type,
				GLuint id,
				GLenum severity,
				GLsizei length,
				const GLchar* message,
				void* userParam
			){
				//if anything should go wrong, KA-BOOM, crash!
				cout 
					<< "an opengl error occured:\n" 
					<< "\t" << "   source: " << source << endl
					<< "\t" << "     type: " << type << endl
					<< "\t" << "       id: " << id << endl
					<< "\t" << " severity: " << source << endl
					<< "\t" << "   length: " << length << endl
					<< "\t" << "  message: \n\t\t\"" << source << "\"" << endl
				;
				cout.flush();
				std::exit(-1);
			},
			NULL
		);
	}
};

}

#endif
