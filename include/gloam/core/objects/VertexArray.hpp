/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_VAO_INCLUDED
#define DCG_VAO_INCLUDED

#include <assimp/scene.h>           // Output data structure
//#include "obj_loader.h"
#include "gloam/core/util/util.hpp"
//
#include <tuple>
#include <memory>

#include "gloam/core/objects/GLObject.hpp"

#include "Program.hpp"


namespace gloam{



class BufferAccessor{
	s_ptr<Buffer> vbo;
	size_t stride;
	void* offset;
	
public:
	BufferAccessor(s_ptr<Buffer> vbo, size_t stride, void* offset) : 
		vbo(vbo), stride(stride), offset(offset)
	{
		assert(vbo->getTarget()->name == GL_ARRAY_BUFFER);
	}
	
	s_ptr<Buffer> getVBO(){ return(vbo); }
	size_t getStride(){ return(stride); }
	void* getOffset(){ return(offset); }
};



class VertexArray : protected GLObjectStandard, protected Binding{
public:
	struct Attachment{
		const Attrib attrib;
		const BufferAccessor accessor;
		Attachment(Attrib attrib, BufferAccessor accessor) :
			attrib(attrib),
			accessor(accessor)
		{}
	};

private:
	const vector<Attachment> attachments;

public:
	VertexArray(Context& context, vector<Attachment> attachments) : 
		GLObjectStandard(glGenVertexArrays, glDeleteVertexArrays),
		Binding(GLObject::id, context.targets.vertexArrayTarget),
		attachments(attachments) 
	{
		Binding::push();
		for(auto attachment : attachments){ 
			enable(attachment.attrib, attachment.accessor);
		}
		Binding::pop();
	}

	virtual ~VertexArray(){
		Binding::push();
		for(auto a : attachments){ 
			disable(a.attrib); 
		}
		Binding::pop();
	}

	void bind(){ Binding::bind(); }

	void drawArrays(DrawMode_t mode, size_t start, size_t numElems){
		assert(Binding::isBound());
		//assert((start+numElems) < this->numElems);
		//
		//bind();
		glDrawArrays(mode, start, numElems);
		//unbind();
	}
	void drawArrays(size_t numElems){ 
		drawArrays(DrawMode::TRIANGLES, 0, numElems); 
	}

private:
	void enable(Attrib attrib, BufferAccessor accessor){
		if(attrib.attribIndex != -1){
			//Binding::push();
			accessor.getVBO()->bind();
			glEnableVertexAttribArray(attrib.attribIndex);
			glVertexAttribPointer(
				//(GLuint) attrib.attribIndex, 
				attrib.attribIndex,
				attrib.numSubtypes, 
				attrib.attribType, 
				attrib.isNormalized, 
				accessor.getStride(),
				accessor.getOffset()
			);
			//Binding::pop();
		}
	}
	void disable(Attrib attrib){
		if(attrib.attribIndex != -1){
			//Binding::push();
			glDisableVertexAttribArray(attrib.attribIndex);
			//Binding::pop();
		}
	}
};

}

#endif












































/*



//start: starting index
	void drawArrays(DrawMode mode, size_t start, size_t numElems){
		assert((numElems+start) < this->numElems);
		//
		bind();
		glDrawArrays(mode, start, numElems);
		unbind();
	}
	void drawArrays(){ 
		drawArrays(DrawMode::Triangles, 0, numElems); 
	}


//a VertexArray with no more than one interleaved VBO, which
//is usually best for performance.
class SplitVAO : private VAO{

public:
	struct BuildGroup{
		DArray arr;
		bool b_interleave;

		BuildGroup(DArray arr, bool b_interleave)
		: arr(arr), b_interleave(b_interleave) {}
	};

	SplitVAO(vector<BuildGroup> groups, ElemArrayBuff indices) : VAO(indices) {
		vector<DArray> interleaved;
		vector<DArray> seperate;
		for(auto group : groups){
			if(group.b_interleave){ 
				interleaved.push_back(group.arr); 
			}
			else{
				seperate.push_back(group.arr);
			}
		}
		init(interleaved, seperate);
	}

	void enable(){ VAO::enable(); }
	void draw(){ VAO::draw(); }


private:
	void init(vector<DArray>& interleaved, vector<DArray>& singleGroups){
		assert(vbos.size() == 0);
		for(auto buff : singleGroups){
			vbos.push_back(make_shared<VBO_Single>(buff.first, buff.second));
		}
		if(interleavedGroups.size() != 0){
			vbos.push_back(make_shared<VBO_Interleaved>(interleavedGroups));
		}
		VAO::bufferAll();
	}
};*/


/*
//modifies the BOT (buffer object type) of an attribute array in GPU memory.
//means moving it to a different area of memory that may suit performance better.
//for example if a solid object instantaniously becomes liquid, changing to an area of
//memory for static drawing, GL_STATIC_DRAW, to streaming GL_STREAM_DRAW
//void setBufferAttribBOT(vector<unsigned short> attribIndices, BOT newBot)
//todo: implement GL_STREAM_DRAW better.

//non-interleaved buffer attribs become interleaved.
void bufferAttribs_interleave(vector<unsigned short>& attribIndices){
	vector<GLuint> bufferIndicesRemoved(attribIndices.getSize());
	//
	interleavedAttribs->reserve(interleavedAttribs->getSize() + attribIndices.getSize());
	//
	for (unsigned short* index = attribIndices.begin(); index < attribIndices.end(); index++){
		AttribBuffer *addr = seperateAttribs->findSubData<unsigned short>(*index, (byte_t*)0);
		assert(addr != NULL);
		glDeleteBuffers(1, &(*seperateBuffers)[addr->bufferIndex]);
		bufferIndicesRemoved.add(addr->bufferIndex);
		interleavedAttribs->add(addr->attrib);
		seperateAttribs->removeAt(addr);
	}
	
	seperateBuffers->removeAll(bufferIndicesRemoved);
	//
	buildInterleaved();
	//
	bufferIndicesRemoved.release();
}

//interleaved attribs become non-interleaved
void bufferAttribs_seperate(vector<unsigned short>& attribIndices){
	int bufferIndex = seperateBuffers->getSize();
	//
	seperateAttribs->reserve(seperateAttribs->getSize() + attribIndices.getSize());
	seperateBuffers->resize(seperateAttribs->getCapacity());
	//
	for (unsigned short* index = attribIndices.begin(); index < attribIndices.end(); index++){
		Attrib *addr = interleavedAttribs->findSubData<unsigned short>(*index, 
			(byte_t*)(offsetof(AttribBuffer, attrib) + offsetof(Attrib, attribIndex)));
		assert(addr != NULL);
		glGenBuffers(1, seperateBuffers->getData() + bufferIndex);
		seperateAttribs->add(AttribBuffer(*addr, bufferIndex));
		interleavedAttribs->removeAt(addr);
		//
		bufferIndex++;
	}
	//
	buildInterleaved();
	//
	for (	AttribBuffer* attrib = seperateAttribs->end() - attribIndices.getSize(); 
			attrib < seperateAttribs->end(); attrib++)
	{
		attrib->build(numVerts, seperateBuffers[attrib->bufferIndex]);
	}
}

//dynamic to streaming or vice versa.
void bufferAttribs_streaming_Dynamic(unsigned short attribIndex, BOT newBot){
	AttribBuffer *addr = seperateAttribs->findSubData<unsigned short>(attribIndex, 
		(byte_t*)(offsetof(AttribBuffer, attrib) + offsetof(Attrib, attribIndex)));
	assert(addr != NULL);
	addr->attrib->bot = newBot;
	addr->build(numVerts, seperateBuffers[addr->bufferIndex]);
}
//dynamic to streaming or vice versa.
void bufferAttribs_streaming_Dynamic(vector<pair<unsigned short, BOT>>& changes){
	for(auto change : changes){
		bufferAttribs_streaming_Dynamic(change.first, change.second);
	}
}

void updateBufferData_seperate(unsigned short attribIndex, uint offset, byte_t* newData, 
uint newDataSize){
	AttribBuffer *addr = seperateAttribs->findSubData<unsigned short>(attribIndex, 
		(byte_t*)(offsetof(AttribBuffer, attrib) + offsetof(Attrib, attribIndex)));
	//
	assert(addr != NULL);
	assert(offset >= 0);
	assert(offset + newData < addr->attrib->end(numVerts));
	glBindBuffer(GL_ARRAY_BUFFER, addr->bufferIndex);
	glBufferSubData(GL_ARRAY_BUFFER, offset, newDataSize, newData);
}

*/










