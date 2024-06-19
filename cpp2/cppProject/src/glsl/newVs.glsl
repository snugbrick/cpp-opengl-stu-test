#version 330 core
layout(location = 0) in vec3 surfacePos;

out vec4 Color;

void main() {
    gl_Position = vec4(surfacePos, 1.0);
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
}