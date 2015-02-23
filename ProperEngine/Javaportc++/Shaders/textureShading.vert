#version 330

attribute vec3 position;
attribute vec2 uv;
varying vec2 uv0;

uniform mat4 modelMatrix;
void main()
{
	gl_Position = modelMatrix * vec4(position,1);
	uv0=uv;
}