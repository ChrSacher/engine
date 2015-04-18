#version 330 core

attribute vec3 position;
attribute vec2 uv;
attribute vec3 normal;

varying vec2 uv0;
varying vec3 normal0;
varying vec4 worldPos0;
varying vec4 viewworldPos0;

uniform mat4 modelMatrix;
uniform mat4 MVP[100];
void main()
{
	gl_Position = MVP[gl_InstanceID] * vec4(position,1);
	viewworldPos0 = gl_Position;
	uv0=vec2(uv.x, 1.0f - uv.y); //uv;
	normal0 = (modelMatrix * vec4(normal,0)).xyz;
	worldPos0 = (modelMatrix * vec4(position,1));
}