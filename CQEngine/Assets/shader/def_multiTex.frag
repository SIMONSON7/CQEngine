#version 430

layout (early_fragment_tests) in;

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;

layout(binding = 0) uniform sampler2D Tex1;
layout(binding = 1) uniform sampler2D Tex2;
layout(location = 0) out vec4 FragColor;

struct Light
{
	vec4 eyePos;
	vec3 Intensity;
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

void phongModel(vec3 pos, vec3 normal, out vec3 ambAndDiff, out vec3 spec)
{
	vec3 dir = normalize(vec3(uLight.eyePos) - pos);
	vec3 vert2viewer = normalize(-pos.xyz);
	vec3 reflect = reflect(dir, normal);
	float dirDotNorm = max(dot(dir, normal), 0.0);

	vec3 ambient = uLight.Intensity * uMat.a;
	vec3 diffuse = uLight.Intensity * uMat.d * dirDotNorm;
	ambAndDiff = ambient + diffuse;

	spec = vec3(0.0);
	if (dirDotNorm > 0.0)
	{
		spec = uLight.Intensity * uMat.s * 
			pow( max( dot(reflect,vert2viewer),0.0 ), uMat.shineFactor );
	}
}

void main()
{
    vec4 texColor1 = texture( Tex1, TexCoord );
	vec4 texColor2 = texture( Tex2, TexCoord );

	vec3 ambAndDiff, spec;
    phongModel( Position, Normal, ambAndDiff, spec );

	vec4 texColor = mix(texColor1, texColor2, texColor2.a);
    FragColor = (vec4( ambAndDiff, 1.0 ) * texColor) + vec4(spec,1.0);
}
