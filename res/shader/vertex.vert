#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;

uniform mat4 mvpMatrix;
uniform mat4 modelMatrix;

out vec3 pos;
out vec2 tex;
out vec3 nrm;

out mat3 TBN;

void main(){
	gl_Position = mvpMatrix * vec4(position, 1.0);
	pos = vec3(modelMatrix * vec4(position, 1.0));
	tex = texCoord;
	nrm = vec3(modelMatrix * vec4(normal, 0.0));

	vec3 T = normalize(vec3(modelMatrix * vec4(tangent,   0.0)));
	vec3 B = normalize(vec3(modelMatrix * vec4(bitangent, 0.0)));
	vec3 N = normalize(vec3(modelMatrix * vec4(normal,    0.0)));
	TBN = mat3(T, B, N);
}