#version 400

layout (location = 0) in vec3 aVertexPos;
layout (location = 1) in vec3 aVertexNormal;

struct Light
{
	vec4 pos;
	vec3 a;
	vec3 d;
	vec3 s;
};

struct Material
{
	vec3 a;
	vec3 d;
	vec3 s;
	float shineFactor;
};

uniform Light uLight;
uniform Material uMat;

uniform mat4 uModelViewMatrix;
uniform mat4 uMVP;
uniform mat3 uNormalMatrix;

//flat out vec3 LightIntensity;
out vec3 LightIntensity;

vec3 phongModel()
{
	vec3 normEyeSpace = normalize( uNormalMatrix * aVertexNormal );
	vec4 vertPosEyeSpace =  uModelViewMatrix * vec4(aVertexPos, 1.0);
	vec3 dir = normalize(vec3(uLight.pos - vertPosEyeSpace));
	vec3 vert2viewer = normalize(-vertPosEyeSpace.xyz);
	vec3 ref = reflect(-dir, normEyeSpace);
	float dirDotNorm = max(dot(dir, normEyeSpace), 0.0);

	vec3 ambient = uLight.a * uMat.a;
	vec3 diffuse = uLight.d * uMat.d * dirDotNorm;
	vec3 spec = vec3(0.0);
	if (dirDotNorm > 0.0)
	{
		spec = uLight.s * uMat.s * pow(max(dot(ref, vert2viewer), 0.0), uMat.shineFactor);
	}

	return ambient + diffuse + spec;
}

void main()
{
	LightIntensity = phongModel();

	gl_Position = uMVP * vec4(aVertexPos, 1.0);
}