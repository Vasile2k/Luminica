#version 330 core

uniform sampler2D textureColor;
uniform sampler2D textureNormal;

out vec3 color;

in vec3 pos;
in vec2 tex;
in vec3 nrm;

in mat3 TBN;

uniform vec3 viewPos;
uniform int lightCount;
uniform vec3 lightPos[16];
uniform vec3 lightCol[16];


vec3 lighting(vec3 objectColor, vec3 pos, vec3 normal, vec3 lightPos, vec3 viewPos, vec3 ambient, vec3 lightColor, vec3 specular, float specPower){
	vec3 L = normalize(lightPos - pos);
	vec3 V = normalize(viewPos - pos);
	vec3 N = normalize(normal);
	vec3 R = normalize(reflect(-L, N));
	float cosTheta = dot(R, V);

	float diffCoef = dot(L, N);
	float specCoef = pow(clamp(cosTheta, 0.0, 1.0), specPower);

	vec3 ambientColor = ambient * lightColor;
	vec3 diffuseColor = diffCoef * lightColor;
	vec3 specularColor = specCoef * specular * lightColor;
	vec3 col = ( ambientColor + diffuseColor + specularColor ) * objectColor; 

	return clamp(col, 0, 1);
}

void main(){
	vec3 objectColor = texture2D(textureColor, tex).rgb;
	vec3 ambient = vec3(0.1);
	vec3 specular = vec3(0.8);
	float specPower = 16;
	
	vec3 normalFromMap = texture2D(textureNormal, tex).rgb;
	//normalFromMap.y = 1.0 - normalFromMap.y;
	normalFromMap = normalFromMap * 2.0 - 1.0;
	vec3 normal = normalize(TBN * normalFromMap);

	color = vec3(0.0);

	for(int i = 0; i < lightCount; ++i){
		color += lighting(objectColor, pos, normal, lightPos[i], viewPos, ambient, lightCol[i], specular, specPower);
	}

}