#version 120

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;

varying vec2 texCoord0;
varying vec3 normal0;

uniform mat4 MVP;
uniform mat4 Normal;

mat4 MVP2 = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
mat4 Normal2 = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

void main()
{
	gl_Position = vec4(position.x, position.y, 0.0, 1.0);
	//
	//gl_Position = vec4(position, 1.0);
	texCoord0 = texCoord;
	normal0 = vec4(normal, 0.0);
	//
	//gl_Position = MVP * vec4(position, 1.0);
	//texCoord0 = texCoord;
	//normal0 = (Normal * vec4(normal, 0.0)).xyz;
}
