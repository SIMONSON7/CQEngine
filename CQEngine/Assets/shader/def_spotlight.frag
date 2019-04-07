#version 430

layout (early_fragment_tests) in;

in vec3 Position;
in vec3 Normal;


layout( location = 0 ) out vec4 FragColor;

struct Light
{
	vec4 pos;	// at eye space.
	vec3 intensity; // of amb diffuse and specular.
	vec3 dir; // at eye space.
	float exponent; // similar to the exponent of specular. 
	float cutoff; // 0 ~ 90
};

uniform Light uLight;

uniform vec3 uD;
uniform vec3 uA;
uniform vec3 uS;
uniform float uShininess;

vec3 adsSpotLight()
{
	vec3 n = normalize(Normal);
	vec3 lightDir = normalize(vec3(uLight.pos) - Position);
	vec3 spotDir = normalize(uLight.dir);
	float angle = acos(dot(-lightDir, spotDir));
	float cutoff = radians(clamp(uLight.cutoff, 0.0, 9.0));
	vec3 ambient = uLight.intensity * uA;

	// light.
	if (angle < cutoff)
	{
		float spotFactor = pow( dot(-lightDir, spotDir), uLight.exponent );
		vec3 vert2viewer = normalize(vec3(-Position));
		vec3 hightDir = normalize( vert2viewer + lightDir );

		vec3 diffuse = spotFactor * uLight.intensity * ( uD * max(dot(lightDir, n), 0.0) );
		vec3 specular = spotFactor * uLight.intensity * ( uS * pow(max(dot(hightDir, n), 0.0), uShininess) );
		return ambient + diffuse + specular;
	}
	// dark.
	else
	{
		return ambient;
	}

}

void main() 
{
    FragColor = vec4(adsSpotLight(), 1.0);
}




