#version 330 core
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor; //1.0f, 0.5f, 0.31f
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 NormalVec;

out vec3 objColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
out vec3 viewPost;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 viewPos;

uniform Material material;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    objColor = aColor;
    Normal = mat3(transpose(inverse(model))) * NormalVec;
    TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);

    viewPost = viewPos;

    FragPos = vec3(model * vec4(aPos, 1.0));
}