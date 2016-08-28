/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef DCG_FRAMEBUFFER_INCLUDED
#define DCG_FRAMEBUFFER_INCLUDED

#include "gloam/core/util/util.hpp"
//
#include "gloam/core/objects/GLObject.hpp"
#include "gloam/core/context/Context.hpp"
#include "gloam/core/Binding.hpp"
//
#include "gloam/core/objects/Texture.hpp" 
#include "gloam/core/objects/Renderbuffer.hpp" 

namespace gloam{

//a place for opengl to render to.  An opengl context still needs to be created before hand for this to work.
//This can be used for rendering offscreen.
//
//to use it: bind, do your rendering, and then unbind.
class Framebuffer : protected GLObjectStandard, public Binding {
private:
	//I'm pretty sure that only one texture or renderbuffer object may be attached to
	//a framebuffer image attachment at any one time.
	class ImageAttachment{
		bool b_attached = false;
	public:
		const GLenum e;
		Framebuffer& fb;
		
	public:
		ImageAttachment(Framebuffer& fb, GLenum e) : fb(fb), e(e) {}

		bool isAttached(){ return(b_attached); }

		void attachTex(s_ptr<Texture> tex){
			tex->push();
			glFramebufferTexture(
				fb.getTarget()->name,
				e,
				tex->GLObject::id,
				0 
			);
			tex->pop();
			b_attached = true;
			fb._setDirty();
		}
		void attachTex1D(s_ptr<Texture> tex){
			assert(tex->getTarget()->name == GL_TEXTURE_1D);
			tex->push();
			glFramebufferTexture1D(
				fb.getTarget()->name,
				e,
				GL_TEXTURE_1D,
				tex->GLObject::id,
				0 
			);
			tex->pop();
			b_attached = true;
			fb._setDirty();
		}
		void attachTex2D(s_ptr<Texture> tex){
			assert(tex->getTarget()->name == GL_TEXTURE_2D);
			tex->push();
			glFramebufferTexture2D(
				fb.getTarget()->name,
				e,
				GL_TEXTURE_2D,
				tex->GLObject::id,
				0 
			);
			tex->pop();
			b_attached = true;
			fb._setDirty();
		}
		void attachTex3D(s_ptr<Texture> tex, GLint layer){
			assert(tex->getTarget()->name == GL_TEXTURE_3D);
			tex->push();
			glFramebufferTexture3D(
				fb.getTarget()->name,
				e,
				GL_TEXTURE_3D,
				tex->GLObject::id,
				0,
				layer
			);
			tex->pop();
			b_attached = true;
			fb._setDirty();
		}
		void attachRenderbuffer(s_ptr<Renderbuffer> r){
			assert(r->getTarget()->name == GL_RENDERBUFFER);
			assert(fb.getTarget()->name == GL_FRAMEBUFFER);
			glFramebufferRenderbuffer(
				GL_FRAMEBUFFER, 
				e, 
				GL_RENDERBUFFER, 
				r->GLObject::id
			);
			b_attached = true;
			fb._setDirty();
		}

		virtual void clear() = 0;
	};

	//an image attachment that only textures can attach to.
	class TexImageAttachment : public ImageAttachment{
	public:
		using ImageAttachment::ImageAttachment;

		virtual void clear() = 0;

	private:
		//hides to prevent attaching renderbuffer.
		void attachRenderbuffer(s_ptr<Renderbuffer> r){}
	};

	class ColorAttachment : public ImageAttachment{
	private:
		//rgba
		GLfloat clearColor[4]{0.0f, 0.0f, 0.0f, 0.0f};
		GLint n;
	public:
		ColorAttachment(Framebuffer& fb, GLint n) : 
			ImageAttachment(fb, GL_COLOR_ATTACHMENT0 + n),
			n(n)
		{}
		virtual void clear(){
			glClearBufferfv(ImageAttachment::e, n, clearColor);
		}
		void clear(GLint r, GLint g, GLint b, GLint a){
			clearColor[0] = r;
			clearColor[1] = g;
			clearColor[2] = b;
			clearColor[3] = a;
			clear();
		}
	};

	class DepthAttachment : public ImageAttachment{
	public:
		DepthAttachment(Framebuffer& fb) : 
			ImageAttachment(fb, GL_DEPTH_ATTACHMENT)
		{}
		virtual void clear(){
			glClear(GL_DEPTH_BUFFER_BIT);
		}
		void clear(double depth){
			glClearDepth(depth);
			clear();
		}
		void clear(float depth){
			glClearDepthf(depth);
			clear();
		}
	};

	class StencilAttachment : public ImageAttachment{
	public:
		StencilAttachment(Framebuffer& fb) : 
			ImageAttachment(fb, GL_STENCIL_ATTACHMENT)
		{}
		virtual void clear(){
			glClear(GL_STENCIL_BUFFER_BIT);
		}
		virtual void clear(GLint s){
			glClearStencil(s);
			clear();
		}
	};

	class DepthStencilAttachment : public ImageAttachment{
	public:
		DepthStencilAttachment(Framebuffer& fb) : 
			ImageAttachment(fb, GL_DEPTH_STENCIL_ATTACHMENT)
		{}
		virtual void clear(){
			glClear(GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		void clear(double depth, GLint s){
			glClearDepthf(depth);
			glClearStencil(s);
			glClear(GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
	};

private:
	bool b_dirty = false;
public:
	vector<ColorAttachment> COLOR_ATTACHMENT_v;
	DepthAttachment DEPTH;
	StencilAttachment STENCIL;
	DepthStencilAttachment DEPTH_STENCIL;

public:
	Framebuffer(
		s_ptr<FramebufferTarget> target
	) :
		GLObjectStandard(glGenFramebuffers, glDeleteFramebuffers),
		Binding(GLObject::id, target),
		DEPTH(*this),
		STENCIL(*this),
		DEPTH_STENCIL(*this)
	{
		GLint m;
		glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &m);
		for(GLint i = 0; i < m; i++){ 
			COLOR_ATTACHMENT_v.emplace_back(*this, i);
		}
	}

	//this function should only be called by image attachments.
	void _setDirty(){ this->b_dirty = true; }

	virtual ~Framebuffer();

	void bind(){
		buffer();//makes sure it's ready before it's bound
		Binding::bind(); 
	}
	void clear(){ Binding::clear(); }

private:
	//should only be called by ImageAttachment objects.
	void buffer(){
		if(b_dirty){
			Binding::push();
			//
			vector<GLenum> enums;
			for(auto attachment : COLOR_ATTACHMENT_v){
				if(attachment.isAttached()){
					enums.push_back(attachment.e);
				}
			}
			if(DEPTH.isAttached()){
				enums.push_back(DEPTH.e);
			}
			if(STENCIL.isAttached()){
				enums.push_back(STENCIL.e);
			}
			if(DEPTH_STENCIL.isAttached()){
				enums.push_back(DEPTH_STENCIL.e);
			}
			//
			//Specifies a list of color buffers to be drawn into
			glDrawBuffers(enums.size(), enums.data());
			//
			Binding::pop();
			//
			checkStatus();
		}
	}

	void checkStatus(){
		//Does the GPU support current FBO configuration?
		GLenum status;
		status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		switch(status)
		{
		case GL_FRAMEBUFFER_COMPLETE_EXT:
			//cout<<"good";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			std::cout << "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT\n";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			std::cout << "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT\n";
			break;
		case GL_FRAMEBUFFER_UNSUPPORTED:
			std::cout << "GL_FRAMEBUFFER_UNSUPPORTED\n";
			break;
		default:
			std::cout << "unknown error.\n";
		}
	}
};

}

#endif








































/*s_ptr<vector<byte_t>> readPixels(
		size_t attachmentIndex, 
		size_t x, 
		size_t y, 
		size_t W, 
		size_t H
	){
		s_ptr<vector<byte_t>> result = make_shared<vector<byte_t>>();
		result->resize(W*H);
		//
		glReadBuffer(GL_COLOR_ATTACHMENT0);
		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		glReadPixels(x, y, W, H, GL_BGR, GL_UNSIGNED_BYTE, result->data());
	}*/

	





/*

	void draw(){
		bind();
		//glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		//CHECK
		//glDrawBuffer(GL_COLOR_ATTACHMENT0);
		bind();
		for(auto attachment : attachments){
			attachment->draw();
		}
		//CHECK
		//
		checkStatus();
	}

byte_t* read(){
		glReadBuffer(GL_COLOR_ATTACHMENT0);
		//CHECK
		//glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		//glReadPixels(0, 0, W, H, GL_BGRA, GL_UNSIGNED_BYTE, pixelData);
		glReadPixels(0, 0, W, H, GL_BGR, GL_UNSIGNED_BYTE, pixelData);
		//CHECK
		//
		return(pixelData);
	}

	void resize(uint W, uint H){
		this->W = W;
		this->H = H;
		//
		glBindRenderbuffer(GL_RENDERBUFFER, renderBuff);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, W, H);
		//
		glBindRenderbuffer(GL_RENDERBUFFER, depthBuff);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, W, H);
		//
		if(W*H > MAX_IMAGE_PIXELS){
			cout << "frame buffer image is too large";
			system("pause");
			exit(67);
		}
	}

//pixelData.resize(W*H*4);
		//
		glGenRenderbuffers(1, &renderBuff);
		glBindRenderbuffer(GL_RENDERBUFFER, renderBuff);
		//glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB32F, W, H);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, W, H);
		//CHECK
		//
		glGenRenderbuffers(1, &depthBuff);
		glBindRenderbuffer(GL_RENDERBUFFER, depthBuff);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, W, H);
		//CHECK
		//
		//glGenFramebuffers(1, &fbo);
		//glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		for(auto renderbuffer : renderbuffers){
			renderbuffer->framebufferRenderbuffer();
		}
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderBuff);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuff);
		//CHECK
		//
		//glBindFramebuffer( GL_FRAMEBUFFER, 0 );


//multiple buffers reduce the chance of (blocking due to trying to read a buffer that is currently being rendered to.	
GLuint* PBOs;//pixel buffer objects
*/
