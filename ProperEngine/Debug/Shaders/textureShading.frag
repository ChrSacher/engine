#version 330
//The fragment shader operates on each pixel in a given polygon

in vec4 color;
out vec4 fragColor;

void main()
{
	fragColor = color;
}