#version 450

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inColor;

layout(location = 0) out vec3 fragPosition;
layout(location = 1) out vec3 fragNormal;
layout(location = 2) out vec2 fragTexCoord;
layout(location = 3) out vec3 fragColor;

layout (set = 0, binding = 0) uniform SceneUB{
    mat4 view;
    mat4 proj;
    mat4 viewProj;
    vec4 viewPos;
} sceneData;

//push constants block
layout( push_constant ) uniform constants
{
    mat4 modelMatrix;
} objectData;

void main() {
    gl_Position = sceneData.viewProj * objectData.modelMatrix * vec4(inPosition, 1.0f);
    fragPosition = vec3(objectData.modelMatrix * vec4(inPosition, 1.0f));
    fragTexCoord = inTexCoord;
    fragNormal = inNormal;
    fragColor = inColor;
}
