#ifndef VULKANINSTANCE_H
#define VULKANINSTANCE_H

#include <stdexcept>
#include <string>
#include <cstring>
#include <vector>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include "../utils/log.h"

namespace LavaEngine { namespace Graphics {

	class VulkanInstance
	{
	public:
#ifdef NDEBUG
		const static bool ENABLE_VALIDATION_LAYERS = false;
#else
		const static bool ENABLE_VALIDATION_LAYERS = true;
#endif

	private:
		VkInstance m_instance;
		VkDebugReportCallbackEXT m_debugCallback;
		std::vector<const char*>* m_requiredLayers;

	public:
		VulkanInstance(const char* title);
		~VulkanInstance();

		VkInstance handle() const;
		std::vector<const char*>* requiredLayers() const;

	private:
		void checkLayers();
		std::vector<const char*> getExtensions();
		void setupDebugCallback();
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
				VkDebugReportFlagsEXT flags,
				VkDebugReportObjectTypeEXT objType,
				uint64_t obj,
				size_t location,
				int32_t code,
				const char* layerPrefix,
				const char* msg,
				void* userData);
	};
}}

#endif
