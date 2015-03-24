#version 330

attribute vec3 position;
attribute vec2 uv;
attribute vec3 normal;

varying vec2 uv0;
varying vec3 normal0;
varying vec4 worldPos0;
varying vec4 viewworldPos0;
varying vec4 shadowCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 depthMVP;

void main()
{
	gl_Position = viewMatrix * modelMatrix * vec4(position,1);
	viewworldPos0 = gl_Position;
	uv0=vec2(uv.x, 1.0f - uv.y); //uv;
	normal0 = (modelMatrix * vec4(normal,0)).xyz;
	worldPos0 = (modelMatrix * vec4(position,1));
	//shadowCoord = depthMVP * vec4(position,1);
}