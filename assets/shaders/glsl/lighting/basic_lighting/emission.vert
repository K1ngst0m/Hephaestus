#version 450

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

layout(set = 0, binding = 0) uniform cameraUB{
    mat4 view;
    mat4 proj;
    mat4 viewProj;
} cameraData;

//push constants block
layout( push_constant ) uniform constants
{
    mat4 modelMatrix;
} objectData;

void main() {
    gl_Position = cameraData.viewProj * objectData.modelMatrix * vec4(inPosition, 1.0f);
}
