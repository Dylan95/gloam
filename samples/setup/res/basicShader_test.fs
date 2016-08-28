#version 120

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D sampler; //samples texture whose name is bound to GL_TEXTURE_2D
uniform vec3 lightDirection;

void main()
{
	//gl_FragColor = texture2D(sampler, texCoord0);
	//gl_FragColor = texture2D(sampler, texCoord0) * 
	//	clamp(dot(-lightDirection, normal0), 0.25, 1.0);
	gl_FragColor = vec3(.5, .5, 0);
}
