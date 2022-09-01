#ifndef VKLSCENEMANGER_H_
#define VKLSCENEMANGER_H_

#include "vklObject.h"

namespace vkl{
enum NodeTypeEnum{
    SCENE_NODE_UNDEFINED,
    SCENE_NODE_LIGHT,
    SCENE_NODE_SKYBOX,
    SCENE_NODE_RENDER_OPAQUE,
    SCENE_NODE_RENDER_TRANSPARENCY,
};

class Scene{
public:
    Scene& pushUniform(UniformBufferObject *ubo);
    Scene& pushObject(MeshObject *object, ShaderPass *pass, glm::mat4 transform = glm::mat4(1.0f));
    void drawScene(VkCommandBuffer commandBuffer);
    void setupDescriptor(VkDevice device);

    void destroy(VkDevice device);
private:
    struct SceneNode{
        NodeTypeEnum _nodeType = SCENE_NODE_UNDEFINED;
        std::vector<SceneNode*> _children;
    };

    struct SceneRenderNode: SceneNode{
        vkl::RenderObject * _object;
        vkl::ShaderPass * _pass;
        vkl::Mesh * _mesh;

        glm::mat4 _transform;

        VkDescriptorSet _globalDescriptorSet;

        SceneRenderNode(vkl::RenderObject * object, vkl::ShaderPass * pass, vkl::Mesh * mesh, glm::mat4 transform)
            : _object(object), _pass(pass), _mesh(mesh), _transform(transform)
        {}

        void draw(VkCommandBuffer commandBuffer, DrawContextDirtyBits dirtyBits = DRAWCONTEXT_ALL) const{
            _object->draw(commandBuffer, _pass, _transform, dirtyBits);
        }
    };

    struct SceneLightNode: SceneNode{
        vkl::UniformBufferObject * _object = nullptr;

        SceneLightNode(vkl::UniformBufferObject * object)
            :_object(object)
        {}
    };

    std::vector<SceneRenderNode*> _renderNodeList;
    std::vector<SceneLightNode*> _lightNodeList;

    VkDescriptorPool _descriptorPool;
};
}

#endif // VKLSCENEMANGER_H_
