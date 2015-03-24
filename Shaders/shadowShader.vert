#version 330

uniform mat4 depthMVP;

layout (location = 0) in vec4 position;

void main(void)
{
    gl_Position =  depthMVP * position;
}