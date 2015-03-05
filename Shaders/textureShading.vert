#version 330

attribute vec3 position;
attribute vec2 uv;
attribute vec3 normal;

varying vec2 uv0;
varying vec3 normal0;
varying vec3 worldPos0;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

void main()
{
	gl_Position = viewMatrix * modelMatrix * vec4(position,1);
	uv0=uv;
	normal0 = (modelMatrix * vec4(normal,0)).xyz;
	worldPos0 = (modelMatrix * vec4(position,1)).xyz;
}