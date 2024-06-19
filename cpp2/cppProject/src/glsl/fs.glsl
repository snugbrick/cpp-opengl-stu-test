#version 330 core
out vec4 FragColor;

in vec3 objColor;// 1.0f, 0.5f, 0.31f
in vec2 TexCoord;
in vec3 Normal;// 法向量
in vec3 FragPos;// 片段的位置
in vec3 viewPost;

vec3 lightColor = vec3(1.0);

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 lightPos;

void main() {
	//FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.1);
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	//vec3 result = (ambient + diffuse) * objColor;
	//FragColor = vec4(result, 1.0);

	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPost - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;
	vec3 result = (ambient + diffuse + specular) * objColor;

	FragColor = vec4(result, 1.0);
}