#version 430

layout (location = 0) in vec3 aVertexPos;
layout (location = 1) in vec3 aVertexNormal;

uniform mat4 uModelViewMatrix;
uniform mat4 uMVP;
uniform mat3 uNormalMatrix;

out vec3 Position;
out vec3 Normal;

void main()
{
	Normal = normalize(uNormalMatrix * aVertexNormal);
	Position = vec3(uModelViewMatrix * vec4(aVertexPos, 1.0));

	gl_Position = uMVP * vec4(aVertexPos, 1.0);
}

