/*

Copyright (c) 2016, Dylan Carleton Gundlach

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/




#ifndef GLOAM_CAPABILITIES_INCLUDED
#define GLOAM_CAPABILITIES_INCLUDED

#include "gloam/core/util/util.hpp"
#include "State.hpp"

namespace gloam{

enum GlCapability : GLenum{
	//indexed
	BLEND = GL_BLEND,
	SCISSOR_TEST = GL_SCISSOR_TEST,
	//
	//multiple
	CLIP_DISTANCE0 = GL_CLIP_DISTANCE0,
	//
	//single
	COLOR_LOGIC_OP = GL_COLOR_LOGIC_OP,
	CULL_FACE = GL_CULL_FACE,
	DEBUG_OUTPUT = GL_DEBUG_OUTPUT,
	DEBUG_OUTPUT_SYNCHRONOUS = GL_DEBUG_OUTPUT_SYNCHRONOUS,
	DEPTH_CLAMP = GL_DEPTH_CLAMP,
	DEPTH_TEST = GL_DEPTH_TEST,
	DITHER = GL_DITHER,
	FRAMEBUFFER_SRGB = GL_FRAMEBUFFER_SRGB,
	LINE_SMOOTH = GL_LINE_SMOOTH,
	MULTISAMPLE = GL_MULTISAMPLE,
	POLYGON_OFFSET_FILL = GL_POLYGON_OFFSET_FILL,
	POLYGON_OFFSET_LINE = GL_POLYGON_OFFSET_LINE,
	POLYGON_OFFSET_POINT = GL_POLYGON_OFFSET_POINT,
	POLYGON_SMOOTH = GL_POLYGON_SMOOTH,
	PRIMITIVE_RESTART = GL_PRIMITIVE_RESTART,
	PRIMITIVE_RESTART_FIXED_INDEX = GL_PRIMITIVE_RESTART_FIXED_INDEX,
	RASTERIZER_DISCARD = GL_RASTERIZER_DISCARD,
	SAMPLE_ALPHA_TO_COVERAGE = GL_SAMPLE_ALPHA_TO_COVERAGE,
	SAMPLE_ALPHA_TO_ONE = GL_SAMPLE_ALPHA_TO_ONE,
	SAMPLE_COVERAGE = GL_SAMPLE_COVERAGE,
	SAMPLE_SHADING = GL_SAMPLE_SHADING,
	SAMPLE_MASK = GL_SAMPLE_MASK,
	STENCIL_TEST = GL_STENCIL_TEST,
	TEXTURE_CUBE_MAP_SEAMLESS = GL_TEXTURE_CUBE_MAP_SEAMLESS,
	PROGRAM_POINT_SIZE = GL_PROGRAM_POINT_SIZE
};

class Capability{
	const GlCapability e;
	bool b_enabled;
public:
	Capability(GlCapability e) : 
		e(e),
		b_enabled(glIsEnabled(e) == GL_TRUE)
	{}

	Capability(const Capability& other) = delete;

	bool set(bool b_enabled){
		if(this->b_enabled != b_enabled){
			this->b_enabled = b_enabled; 
			if(b_enabled){
				glEnable(e);
			}
			else{
				glDisable(e);
			}
		}
	}
	bool get(){ return(b_enabled); }
};

//see:
//https://www.opengl.org/wiki/GLAPI/glEnable#Indexed_Capabilities
class CapabilityN{
	const GlCapability e;
	const size_t MAX_INDEX;
public:
	CapabilityN(GlCapability e, size_t MAX_INDEX) : 
		e(e),
		MAX_INDEX(MAX_INDEX)
	{}

	CapabilityN(const CapabilityN& other) = delete;

	bool set(size_t index, bool b_enabled){
		assert(index <= MAX_INDEX);
		if(b_enabled){
			glEnablei(e, index);
		}
		else{
			glDisablei(e, index);
		}
	}
	bool get(size_t index){ 
		assert(index <= MAX_INDEX);
		return(glIsEnabledi(e, index) == GL_TRUE); 
	}
};


class Capabilities{
public:
	Capabilities(){
		GLint m;
		glGetIntegerv(GL_MAX_CLIP_PLANES, &m);
		for(GLint i = 0; i < m; i++){
			CLIP_DISTANCE_v.emplace_back(new Capability(
				//glew stores names like (GL_VARIABLEi) as (GL_VARIABLE0 + i)
				//(GLenum)(GL_CLIP_DISTANCE0 + i)
				(GlCapability)(GL_CLIP_DISTANCE0 + i)
			));
		}
	}

	//indexed capabilities

	//If enabled, blend the computed fragment color values with the values in the color buffers. See glBlendFunc.
	s_ptr<CapabilityN> BLEND = make_shared<CapabilityN>(
		//GL_BLEND,
		GlCapability::BLEND,
		GL_MAX_DRAW_BUFFERS
	);

	//If enabled, discard fragments that are outside the scissor rectangle. See glScissor.
	s_ptr<CapabilityN> SCISSOR_TEST = make_shared<CapabilityN>(
		GlCapability::SCISSOR_TEST,
		GL_MAX_VIEWPORTS
	);

	//vectors of capabilites

	//If enabled, clip geometry against user-defined half space i.
	vector<s_ptr<Capability>> CLIP_DISTANCE_v;

	//single capabilities

	//If enabled, apply the currently selected logical operation to the computed fragment color and color buffer values. See glLogicOp.
	s_ptr<Capability> COLOR_LOGIC_OP = make_shared<Capability>(
		GlCapability::COLOR_LOGIC_OP
	);

	//If enabled, cull polygons based on their winding in window coordinates. See glCullFace.
	s_ptr<Capability> CULL_FACE = make_shared<Capability>(
		GlCapability::CULL_FACE
	);

	//If enabled, debug messages are produced by a debug context. When disabled, the debug message log is silenced. Note that in a non-debug context, very few, if any messages might be produced, even when GL_DEBUG_OUTPUT is enabled.
	s_ptr<Capability> DEBUG_OUTPUT = make_shared<Capability>(
		GlCapability::DEBUG_OUTPUT
	);

	//If enabled, debug messages are produced synchronously by a debug context. If disabled, debug messages may be produced asynchronously. In particular, they may be delayed relative to the execution of GL commands, and the debug callback function may be called from a thread other than that in which the commands are executed. See glDebugMessageCallback.
	s_ptr<Capability> DEBUG_OUTPUT_SYNCHRONOUS = make_shared<Capability>(
		GlCapability::DEBUG_OUTPUT_SYNCHRONOUS
	);

	//If enabled, the −wc≤zc≤wc-wc≤zc≤wc plane equation is ignored by view volume clipping (effectively, there is no near or far plane clipping). See glDepthRange.
	s_ptr<Capability> DEPTH_CLAMP = make_shared<Capability>(
		GlCapability::DEPTH_CLAMP
	);

	//If enabled, do depth comparisons and update the depth buffer. Note that even if the depth buffer exists and the depth mask is non-zero, the depth buffer is not updated if the depth test is disabled. See glDepthFunc and glDepthRange.
	s_ptr<Capability> DEPTH_TEST = make_shared<Capability>(
		GlCapability::DEPTH_TEST
	);

	//If enabled, dither color components or indices before they are written to the color buffer.
	s_ptr<Capability> DITHER = make_shared<Capability>(
		GlCapability::DITHER
	);

	//If enabled and the value of GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING for the framebuffer attachment corresponding to the destination buffer is GL_SRGB, the R, G, and B destination color values (after conversion from fixed-point to floating-point) are considered to be encoded for the sRGB color space and hence are linearized prior to their use in blending.
	s_ptr<Capability> FRAMEBUFFER_SRGB = make_shared<Capability>(
		GlCapability::FRAMEBUFFER_SRGB
	);

	//If enabled, draw lines with correct filtering. Otherwise, draw aliased lines. See glLineWidth.
	s_ptr<Capability> LINE_SMOOTH = make_shared<Capability>(
		GlCapability::LINE_SMOOTH
	);

	//If enabled, use multiple fragment samples in computing the final color of a pixel. See glSampleCoverage.
	s_ptr<Capability> MULTISAMPLE = make_shared<Capability>(
		GlCapability::MULTISAMPLE
	);

	//If enabled, and if the polygon is rendered in GL_FILL mode, an offset is added to depth values of a polygon's fragments before the depth comparison is performed. See glPolygonOffset.
	s_ptr<Capability> POLYGON_OFFSET_FILL = make_shared<Capability>(
		GlCapability::POLYGON_OFFSET_FILL
	);

	//If enabled, and if the polygon is rendered in GL_LINE mode, an offset is added to depth values of a polygon's fragments before the depth comparison is performed. See glPolygonOffset.
	s_ptr<Capability> POLYGON_OFFSET_LINE = make_shared<Capability>(
		GlCapability::POLYGON_OFFSET_LINE
	);

	//If enabled, an offset is added to depth values of a polygon's fragments before the depth comparison is performed, if the polygon is rendered in GL_POINT mode. See glPolygonOffset.
	s_ptr<Capability> POLYGON_OFFSET_POINT = make_shared<Capability>(
		GlCapability::POLYGON_OFFSET_POINT
	);

	//If enabled, draw polygons with proper filtering. Otherwise, draw aliased polygons. For correct antialiased polygons, an alpha buffer is needed and the polygons must be sorted front to back.
	s_ptr<Capability> POLYGON_SMOOTH = make_shared<Capability>(
		GlCapability::POLYGON_SMOOTH
	);

	//Enables primitive restarting. If enabled, any one of the draw commands which transfers a set of generic attribute array elements to the GL will restart the primitive when the index of the vertex is equal to the primitive restart index. See glPrimitiveRestartIndex.
	s_ptr<Capability> PRIMITIVE_RESTART = make_shared<Capability>(
		GlCapability::PRIMITIVE_RESTART
	);

	//Enables primitive restarting with a fixed index. If enabled, any one of the draw commands which transfers a set of generic attribute array elements to the GL will restart the primitive when the index of the vertex is equal to the fixed primitive index for the specified index type. The fixed index is equal to 2n−12n−1 where n is equal to 8 for GL_UNSIGNED_BYTE, 16 for GL_UNSIGNED_SHORT and 32 for GL_UNSIGNED_INT.
	s_ptr<Capability> PRIMITIVE_RESTART_FIXED_INDEX = make_shared<Capability>(
		GlCapability::PRIMITIVE_RESTART_FIXED_INDEX
	);

	//If enabled, primitives are discarded after the optional transform feedback stage, but before rasterization. Furthermore, when enabled, glClear, glClearBufferData, glClearBufferSubData, glClearTexImage, and glClearTexSubImage are ignored.
	s_ptr<Capability> RASTERIZER_DISCARD = make_shared<Capability>(
		GlCapability::RASTERIZER_DISCARD
	);

	//If enabled, compute a temporary coverage value where each bit is determined by the alpha value at the corresponding sample location. The temporary coverage value is then ANDed with the fragment coverage value.
	s_ptr<Capability> SAMPLE_ALPHA_TO_COVERAGE = make_shared<Capability>(
		GlCapability::SAMPLE_ALPHA_TO_COVERAGE
	);

	//If enabled, each sample alpha value is replaced by the maximum representable alpha value.
	s_ptr<Capability> SAMPLE_ALPHA_TO_ONE = make_shared<Capability>(
		GlCapability::SAMPLE_ALPHA_TO_ONE
	);

	//If enabled, the fragment's coverage is ANDed with the temporary coverage value. If GL_SAMPLE_COVERAGE_INVERT is set to GL_TRUE, invert the coverage value. See glSampleCoverage.
	s_ptr<Capability> SAMPLE_COVERAGE = make_shared<Capability>(
		GlCapability::SAMPLE_COVERAGE
	);

	//If enabled, the active fragment shader is run once for each covered sample, or at fraction of this rate as determined by the current value of GL_MIN_SAMPLE_SHADING_VALUE. See glMinSampleShading.
	s_ptr<Capability> SAMPLE_SHADING = make_shared<Capability>(
		GlCapability::SAMPLE_SHADING
	);

	//If enabled, the sample coverage mask generated for a fragment during rasterization will be ANDed with the value of GL_SAMPLE_MASK_VALUE before shading occurs. See glSampleMaski.
	s_ptr<Capability> SAMPLE_MASK = make_shared<Capability>(
		GlCapability::SAMPLE_MASK
	);

	//If enabled, do stencil testing and update the stencil buffer. See glStencilFunc and glStencilOp.
	s_ptr<Capability> STENCIL_TEST = make_shared<Capability>(
		GlCapability::STENCIL_TEST
	);

	//If enabled, cubemap textures are sampled such that when linearly sampling from the border between two adjacent faces, texels from both faces are used to generate the final sample value. When disabled, texels from only a single face are used to construct the final sample value.
	s_ptr<Capability> TEXTURE_CUBE_MAP_SEAMLESS = make_shared<Capability>(
		GlCapability::TEXTURE_CUBE_MAP_SEAMLESS
	);

	//If enabled and a vertex or geometry shader is active, then the derived point size is taken from the (potentially clipped) shader builtin gl_PointSize and clamped to the implementation-dependent point size range.
	s_ptr<Capability> PROGRAM_POINT_SIZE = make_shared<Capability>(
		GlCapability::PROGRAM_POINT_SIZE
	);
};

}

#endif
