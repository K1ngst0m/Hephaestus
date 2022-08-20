#ifndef BASIC_LIGHTING_H_
#define BASIC_LIGHTING_H_
#include "vklBase.h"
/*
** - https://learnopengl.com/Lighting/Basic-Lighting
 */

struct DescriptorSetLayouts {
    VkDescriptorSetLayout scene;
    VkDescriptorSetLayout material;
};


// per scene data
// general scene data
struct SceneDataLayout {
    alignas(16) glm::vec3 viewPosition;
    alignas(16) glm::vec3 ambientColor;
};

// point light scene data
struct PointLightDataLayout {
    alignas(16) glm::vec3 position;
    alignas(16) glm::vec3 color;
};

// mvp matrix data layout
struct CameraDataLayout {
    glm::mat4 view;
    glm::mat4 proj;
    glm::mat4 viewProj;
};

// per material data
struct MaterialDataLayout {
    glm::vec3 basicColor;
};

// per object data
struct ObjectDataLayout {
    glm::mat4 modelMatrix;
};

// vertex data layout
struct VertexDataLayout {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 texCoord;

    static VkVertexInputBindingDescription getBindingDescription()
    {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(VertexDataLayout);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions()
    {
        std::vector<VkVertexInputAttributeDescription> attributeDescriptions(3);

        attributeDescriptions[0] = {
            .location = 0,
            .binding = 0,
            .format = VK_FORMAT_R32G32B32_SFLOAT,
            .offset = offsetof(VertexDataLayout, pos),
        };

        attributeDescriptions[1] = {
            .location = 1,
            .binding = 0,
            .format = VK_FORMAT_R32G32B32_SFLOAT,
            .offset = offsetof(VertexDataLayout, normal),
        };

        attributeDescriptions[2] = {
            .location = 2,
            .binding = 0,
            .format = VK_FORMAT_R32G32_SFLOAT,
            .offset = offsetof(VertexDataLayout, texCoord),
        };

        return attributeDescriptions;
    }
};


class basic_lighting : public vkl::vklBase {
public:
    ~basic_lighting() override = default;

private:
    void initDerive() override
    {
        createVertexBuffers();
        createUniformBuffers();
        createTextures();
        setupDescriptors();
        createSyncObjects();
        createGraphicsPipeline();
    }

    void drawFrame() override;

    // enable anisotropic filtering features
    void getEnabledFeatures() override;

    void cleanupDerive() override;

private:
    void setupDescriptors()
    {
        createDescriptorSetLayout();
        createDescriptorPool();
        createDescriptorSets();
        createPipelineLayout();
    }
    void createVertexBuffers();
    void createUniformBuffers();
    void createDescriptorSets();
    void createDescriptorSetLayout();
    void createGraphicsPipeline();
    void createSyncObjects();
    void createDescriptorPool();
    void updateUniformBuffer(uint32_t currentFrameIndex);
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    void createTextures();
    void createPipelineLayout();

private:
    vkl::Buffer m_cubeVB;

    vkl::Buffer m_sceneUB;
    vkl::Buffer m_pointLightUB;
    vkl::Buffer m_materialUB;

    std::vector<vkl::Buffer> m_mvpUBs;

    vkl::Texture m_containerTexture;
    vkl::Texture m_awesomeFaceTexture;

    DescriptorSetLayouts m_descriptorSetLayouts;

    std::vector<VkDescriptorSet> m_perFrameDescriptorSets;
    VkDescriptorSet m_cubeMaterialDescriptorSets;

    VkPipelineLayout m_cubePipelineLayout;
    VkPipeline m_cubeGraphicsPipeline;

    VkPipelineLayout m_emissionPipelineLayout;
    VkPipeline m_emissionGraphicsPipeline;
};


#endif // BASIC_LIGHTING_H_
