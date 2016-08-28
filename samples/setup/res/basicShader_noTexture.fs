#version 120

varying vec3 normalVar;

uniform vec3 lightDirection;

void main()
{
	gl_FragColor = (vec4(1.0, 0.0, 0.0, 1.0)) * 
		clamp(dot(-lightDirection, normalVar), 0.25, 1.0);
}
