#version 430

layout (location = 0) in vec3 aVertexPos;
layout (location = 1) in vec3 aVertexNormal;
layout (location = 2) in vec2 aVertexTexCoord;

uniform mat4 uModelViewMatrix;
uniform mat4 uMVP;
uniform mat3 uNormalMatrix;

out vec3 Position;
out vec3 Normal;
out vec2 TexCoord;

void main()
{
	Position = vec3(uModelViewMatrix * vec4(aVertexPos, 1.0));
	Normal = normalize(uNormalMatrix * aVertexNormal);
	TexCoord = aVertexTexCoord;

	gl_Position = uMVP * vec4(aVertexPos, 1.0);
}