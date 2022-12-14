#ifndef VKLUTILS_H_
#define VKLUTILS_H_

#include <deque>
#include <algorithm>
#include <array>
#include <cassert>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <type_traits>
#include <unordered_map>
#include <vector>
#include <vulkan/vulkan.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <spirv_reflect/spirv_reflect.h>

#include <stb_image.h>

// Custom define for better code readability
#define VK_FLAGS_NONE 0
// Default fence timeout in nanoseconds
#define DEFAULT_FENCE_TIMEOUT 100000000000

#define VK_CHECK_RESULT(f)                                                                                \
    {                                                                                                     \
        VkResult res = (f);                                                                               \
        if (res != VK_SUCCESS) {                                                                          \
            std::cout << "Fatal : VkResult is \"" << vkl::utils::errorString(res) << "\" in " << __FILE__ \
                      << " at line " << __LINE__ << "\n";                                                 \
            assert(res == VK_SUCCESS);                                                                    \
        }                                                                                                 \
    }

namespace vkl::utils {
std::string        errorString(VkResult errorCode);
std::vector<char>  loadSpvFromFile(const std::string &filename);
VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
VkPresentModeKHR   chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
VkExtent2D         chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities, GLFWwindow *window);
} // namespace vkl::utils

#endif // VKLUTILS_H_
