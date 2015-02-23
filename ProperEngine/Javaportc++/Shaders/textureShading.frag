#version 330
//The fragment shader operates on each pixel in a given polygon


varying vec2 uv0;
uniform sampler2D diffuse;

void main()
{
	gl_FragColor = texture2D(diffuse,uv0);
}