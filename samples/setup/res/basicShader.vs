#version 120

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;

varying vec2 texCoordVar;
varying vec3 normalVar;

uniform mat4 MVP;
uniform mat4 Model;

void main()
{
	gl_Position = (MVP * vec4(position, 1.0));
	texCoordVar = texCoord;
	normalVar = (Model * vec4(normal, 0.0)).xyz;
}
