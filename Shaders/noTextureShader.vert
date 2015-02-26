#version 330

attribute vec3 position;
attribute vec2 uv;
attribute vec3 normal;

varying vec3 normal0;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

void main()
{
	gl_Position = viewMatrix * modelMatrix * vec4(position,1);
	normal0 = (modelMatrix * vec4(normal,0)).xyz;
}