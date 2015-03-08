#version 330
//The fragment shader operates on each pixel in a given polygon


varying vec2 uv0;

uniform sampler2D diffuse;
uniform vec3 baseColor;

void main()
{
	vec4 color = vec4(baseColor,1);
	vec4 textureColor = texture2D(diffuse,uv0);
	color*=textureColor;
	gl_FragColor = color;
	
}