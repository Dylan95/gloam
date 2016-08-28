/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_BUFFER_OBJECT_INCLUDED
#define DCG_BUFFER_OBJECT_INCLUDED

#include "gloam/core/util/util.hpp"

#include "gloam/core/objects/GLObject.hpp"
#include "gloam/core/Binding.hpp"

namespace gloam{



class Buffer : protected GLObjectStandard, protected Binding{
public:
	enum MapAccess : GLbitfield{
		MAP_READ_BIT = GL_MAP_READ_BIT,
		MAP_WRITE_BIT = GL_MAP_WRITE_BIT,
		MAP_PERSISTENT_BIT = GL_MAP_PERSISTENT_BIT,
		MAP_COHERENT_BIT = GL_MAP_COHERENT_BIT,
		//The following optional flag bits in access may be used to modify the mapping:
		MAP_INVALIDATE_RANGE_BIT = GL_MAP_INVALIDATE_RANGE_BIT,
		MAP_INVALIDATE_BUFFER_BIT = GL_MAP_INVALIDATE_BUFFER_BIT,
		MAP_FLUSH_EXPLICIT_BIT = GL_MAP_FLUSH_EXPLICIT_BIT,
		MAP_UNSYNCHRONIZED_BIT = GL_MAP_UNSYNCHRONIZED_BIT
	};

protected:
	size_t size = 0;//number of bytes

public:
	Buffer(s_ptr<BufferTarget> target) : 
		GLObjectStandard(glGenBuffers, glDeleteBuffers), 
		Binding(GLObject::id, target)
	{}

	virtual ~Buffer() {}
	
	void bufferSubData(size_t offset, void* data, size_t numBytes){
		assert(
			(Binding::getTarget()->name == GL_ARRAY_BUFFER) ||
			(Binding::getTarget()->name == GL_ELEMENT_ARRAY_BUFFER) ||
			(Binding::getTarget()->name == GL_PIXEL_PACK_BUFFER) ||
			(Binding::getTarget()->name == GL_PIXEL_UNPACK_BUFFER)
		);
		//
		Binding::push();
		glBufferSubData(
			Binding::getTarget()->name,
			offset, 
			numBytes, 
			data
		);
		Binding::pop();
	}

	void* mapBuffer(MapAccess access){
		Binding::push();
		void* result = glMapBuffer(Binding::getTarget()->name, access);
		Binding::pop();
		return(result);
	}
	void* mapBufferRange(size_t offset, size_t length, MapAccess access){
		Binding::push();
		void* result = glMapBufferRange(Binding::getTarget()->name, offset, length, access);
		Binding::pop();
		return(result);
	}
	
	//Data can be copied from one buffer object to another, or from one region
	//to another (non-overlapping) region of the same buffer. To do this, 
	//first bind the source and destination buffers to different target​s. 
	//These could be any target, but GL_COPY_READ_BUFFER​ and GL_COPY_WRITE_BUFFER
	//have no special semantics, so they make useful targets for this purpose. 
	//When copying within a buffer, bind the same buffer object to both.
	void copyFrom(Buffer readTarget, size_t writeOffset, size_t readOffset, size_t size){
		Binding::push();
		glCopyBufferSubData(
			Binding::getTarget()->name, 
			readTarget.getTarget()->name, 
			readOffset, 
			writeOffset, 
			size
		);
		Binding::pop();
	}

	void bind(){ Binding::bind(); }

	s_ptr<Target> getTarget(){ return(Binding::getTarget()); }

	size_t getSize(){ return(size); }
};


//mutable vs immutable:
//
//see: http://stackoverflow.com/questions/27810542/what-is-the-difference-between-glbufferstorage-and-glbufferdata
//
//With glBufferData (...), you can call that command multiple times 
//on the same object and it will orphan the old memory and allocate 
//new storage. With glBufferStorage (...), the buffer's size is set
//for the lifetime of the object (immutable) and it is an 
//error (GL_INVALID_OPERATION) to call glBufferStorage (...) again once 
//it has been allocated immutably.


class Buffer_Mutable : public Buffer{
public:
	class Usage{
	public:
		enum class Frequency{ STREAM, STATIC, DYNAMIC };
		enum class Nature{ DRAW, READ, COPY };

	private:
		GLenum e;
		Frequency f;
		Nature n;

	public:
		Usage(Frequency f, Nature n) : f(f), n(n){
			switch(f){
			case Frequency::STREAM:
				switch(n){
				case Nature::DRAW:
					e = GL_STREAM_DRAW;
					break;
				case Nature::READ:
					e = GL_STREAM_READ;
					break;
				case Nature::COPY:
					e = GL_STREAM_COPY;
					break;
				};
				break;
			case Frequency::STATIC:
				switch(n){
				case Nature::DRAW:
					e = GL_STATIC_DRAW;
					break;
				case Nature::READ:
					e = GL_STATIC_READ;
					break;
				case Nature::COPY:
					e = GL_STATIC_COPY;
					break;
				};
				break;
			 case Frequency::DYNAMIC:
				switch(n){
				case Nature::DRAW:
					e = GL_DYNAMIC_DRAW;
					break;
				case Nature::READ:
					e = GL_DYNAMIC_READ;
					break;
				case Nature::COPY:
					e = GL_DYNAMIC_COPY;
					break;
				};
				break;
			}
		}

		GLenum getEnum(){ return(e); }
		Frequency getF(){ return(f); }
		Nature getN(){ return(n); }
	};

private:
	c_ptr<Usage> usage;
	//c_ptr<Usage> usage = nullptr;

public:
	Buffer_Mutable(s_ptr<BufferTarget> target)
		: Buffer(target)
	{}
	
	virtual ~Buffer_Mutable(){}

	void orphan(){
		//assert(usage != nullptr);
		assert(Buffer::size != 0);
		bufferData(Buffer::size, NULL, usage);
	}

	//creates a mutable buffer
	//size: number of bytes
	void bufferData(size_t size, void* data, c_ptr<Usage> usage){
		Binding::push();
		Buffer::size = size;
		//this->usage.reset(usage);
		//this->usage = new Usage(Usage::Frequency::STATIC, Usage::Nature::DRAW);
		this->usage = usage;
		//glBufferData(target, numBytes, data, bot);
		glBufferData(Binding::getTarget()->name, size, data, usage->getEnum());
		Binding::pop();
	}

	//1. detach the old block of storage and 
	//2. give you a new block of storage to work with, 
	//all behind the same buffer handle
	//
	//The old block of storage will be put on a free 
	//list by OpenGL and reused once there can be 
	//no draw commands in the queue which might 
	//be referring to it (e.g. once all queued GL 
	//commands have finished executing).
	//
	//only practical if there is no further need to read or update this specific block of storage from the GL client side.
	Usage getUsage(){ return(*usage); }
};


//can't be resized or de-allocate it, but you can write/read data in it.
class Buffer_Immutable : public Buffer{
public:
	enum Flag : GLbitfield{
		DYNAMIC_STORAGE_BIT = GL_DYNAMIC_STORAGE_BIT,
		MAP_READ_BIT = GL_MAP_READ_BIT,
		MAP_WRITE_BIT = GL_MAP_WRITE_BIT,
		MAP_PERSISTENT_BIT = GL_MAP_PERSISTENT_BIT,
		MAP_COHERENT_BIT = GL_MAP_COHERENT_BIT,
		CLIENT_STORAGE_BIT = GL_CLIENT_STORAGE_BIT
	};

private:
	Flag fs;

public:
	Buffer_Immutable(s_ptr<BufferTarget> target, Flag fs, void* data, size_t size)
		: Buffer(target), fs(fs)
	{
		Binding::push();
		//creates an imutable buffer
		glBufferStorage(
			Binding::getTarget()->name,
			size,
			data,
			fs
		);
		Binding::pop();
	}

	virtual ~Buffer_Immutable(){}

	Flag getFlags(){ return(fs); }
};

}

#endif




















/*



enum class Usage : GLuint{
		GLuint STREAM_DRAW = GL_STREAM_DRAW;
		GLuint STREAM_READ = GL_STREAM_DRAW;
		GLuint STREAM_COPY = GL_STREAM_DRAW;
		GLuint STATIC_DRAW = GL_STREAM_DRAW;
		GLuint STATIC_READ = GL_STATIC_READ;
		GLuint STATIC_COPY = GL_STATIC_COPY;
		GLuint DYNAMIC_DRAW = GL_DYNAMIC_DRAW;
		GLuint DYNAMIC_READ = GL_DYNAMIC_READ;
		GLuint DYNAMIC_COPY = GL_DYNAMIC_COPY;
	}



*/
