#version 330
//The fragment shader operates on each pixel in a given polygon



struct Baselight
{
	vec3 color;
	float intensity;
};
struct DirectionalLight
{
	Baselight base;
	vec3 direction;
};

varying vec2 uv0;
varying vec3 normal0;
varying vec3 worldPos0;

uniform sampler2D diffuse;
uniform vec3 baseColor;
uniform vec3 ambientLight;
uniform DirectionalLight directionalLight;
uniform float specularIntensity;
uniform float specularPower;
uniform vec3 eyePos;

vec4 calcLight(Baselight base,vec3 direction,vec3 normal)
{
	float diffuseFactor = dot(normal,-direction);
	vec4 diffuseColor = vec4(0,0,0,0);
	vec4 specularColor = vec4(0,0,0,0);
	if(diffuseFactor >0)
	{

		diffuseColor = vec4(base.color,1) * base.intensity * diffuseFactor;

		vec3 directionToEye = normalize(eyePos - worldPos0);
		vec3 reflectionDirection = normalize(reflect(direction,normal));

		float specularFactor = dot(directionToEye,reflectionDirection);
		specularFactor = pow(specularFactor,specularPower);

		if(specularFactor > 0 )
		{
			specularColor = vec4(base.color,1) * specularIntensity * specularFactor;
		}
	}
	return diffuseColor + specularColor;
}

vec4 calcDirectionalLight(DirectionalLight light,vec3 normal)
{
	return calcLight(light.base,-light.direction,normal);
}

void main()
{
	vec4 totalLight = vec4(ambientLight,1);
	vec4 color = vec4(baseColor,1);
	vec4 textureColor = texture2D(diffuse,uv0);
	color*=textureColor;
	vec3 normal = normalize(normal0);
	totalLight += calcDirectionalLight(directionalLight,normal);
	gl_FragColor = color * totalLight;
}