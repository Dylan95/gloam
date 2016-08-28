#version 120

varying vec2 texCoordVar;
varying vec3 normalVar;

//samples texture whose name is bound to GL_TEXTURE_2D
uniform sampler2D sampler;

uniform vec3 lightDirection;

void main()
{
	//gl_FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	//gl_FragColor = vec4(1.0f, texCoordVar.x, 0.0f, 1.0f) * 
	gl_FragColor = texture2D(sampler, texCoordVar) * 
		clamp(dot(-lightDirection, normalVar), 0.25, 1.0);
}
