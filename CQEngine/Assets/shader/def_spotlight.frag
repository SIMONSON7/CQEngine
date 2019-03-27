#version 400

in vec3 Position;
in vec3 Normal;

layout( location = 0 ) out vec4 FragColor;

struct Light
{
	vec4 pos;
	vec3 intensity;
	vec3 dir;
	float exponent;
	float cutoff; // 0 ~ 90
};

uniform Light uLight;

uniform vec3 uD;
uniform vec3 uA;
uniform vec3 uS;
uniform float shininess;

vec3 adsSpotLight()
{

}

void main() 
{
    FragColor = vec4(adsSpotLight(), 1.0);
}




