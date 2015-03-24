#version 330

uniform mat4 depthMVP;

layout(location = 0) in vec3 position;

void main(void)
{
    gl_Position =  depthMVP * vec4(position,1);
}