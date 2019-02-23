#include "vulkaninstance.h"

namespace LavaEngine { namespace Graphics {

	VkResult createDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackCreateInfoEXT* createInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback);
	void destroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT pCallback, const VkAllocationCallbacks* pAllocator);

	VulkanInstance::VulkanInstance(const char* title)
	{
		// application info
		VkApplicationInfo appInfo;
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pNext = nullptr;
		appInfo.pApplicationName = title;
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = nullptr;
		appInfo.engineVersion = 0;
		appInfo.apiVersion = VK_API_VERSION_1_0;
		
		#ifndef NDEBUG
			// print vulkan requested version
			std::string requestedVersion = std::string("Vulkan requested version: ")
				+ std::to_string(appInfo.applicationVersion >> 22) + std::string(".")
				+ std::to_string((appInfo.applicationVersion >> 11) & 0x000003ff) + std::string(".")
				+ std::to_string((appInfo.applicationVersion >> 0) & 0x000003ff);
			Utils::Log::info(requestedVersion.c_str());
			

			// print all available vulkan extensions
			uint32_t vulkanExtensionCount = 0;
			vkEnumerateInstanceExtensionProperties(nullptr, &vulkanExtensionCount, nullptr);
			std::vector<VkExtensionProperties> vulkanExtensions(vulkanExtensionCount);
			vkEnumerateInstanceExtensionProperties(nullptr, &vulkanExtensionCount, vulkanExtensions.data());

			Utils::Log::info("available vulkan extensions:");
			for(const auto& vulkanExtension : vulkanExtensions)
			{
				std::string extension = std::string("\t") + std::string(vulkanExtension.extensionName)
					+ std::string("\t") + std::to_string(vulkanExtension.specVersion);
				Utils::Log::info(extension.c_str());
			}
		#endif

		// required layers
		m_requiredLayers = new std::vector<const char*>(1);
		(*m_requiredLayers)[0] = "VK_LAYER_LUNARG_standard_validation";
		checkLayers();

		// get extensions
		std::vector<const char*> extensions = getExtensions();

		// instance create info
		VkInstanceCreateInfo createInfo;
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pNext = nullptr;
		createInfo.flags = 0;
		createInfo.pApplicationInfo = &appInfo;
		createInfo.enabledLayerCount = static_cast<uint32_t>(m_requiredLayers->size());
		createInfo.ppEnabledLayerNames = m_requiredLayers->data();
		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();

		// create instance
		if(vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS)
			throw std::runtime_error("failed to create vulkan instance");
		else
			Utils::Log::info("instance created successfully");

		// setup debug report callback
		setupDebugCallback();
	}

	VulkanInstance::~VulkanInstance()
	{
		delete m_requiredLayers;
		if(ENABLE_VALIDATION_LAYERS)
			destroyDebugReportCallbackEXT(m_instance, m_debugCallback, nullptr);
		vkDestroyInstance(m_instance, nullptr);
	}

	VkInstance VulkanInstance::handle() const
	{
		return m_instance;
	}

	std::vector<const char*>* VulkanInstance::requiredLayers() const
	{
		return m_requiredLayers;
	}

	void VulkanInstance::checkLayers()
	{
		// querying supported layers
		uint32_t supportedLayersCount;
		vkEnumerateInstanceLayerProperties(&supportedLayersCount, nullptr);
		std::vector<VkLayerProperties> supportedLayers(supportedLayersCount);
		vkEnumerateInstanceLayerProperties(&supportedLayersCount, supportedLayers.data());

#ifndef NDEBUG
		Utils::Log::info("available vulkan layers:");
		for(const VkLayerProperties& supportedLayerProperties: supportedLayers)
		{
			std::string extension = std::string("\t") + std::string(supportedLayerProperties.layerName)
				+ std::string("\t") + std::string(supportedLayerProperties.description);
			Utils::Log::info(extension.c_str());
		}
#endif

		// check if supported
		int layersToFind = m_requiredLayers->size();
		for(const char* layer : *m_requiredLayers)
			for(const VkLayerProperties& supportedLayerProperties : supportedLayers)
				if(!strcmp(layer, supportedLayerProperties.layerName))
				{
					--layersToFind;
					break;
				}
		if(layersToFind)
			throw std::runtime_error("requested layers are not supported");
	}

	std::vector<const char*> VulkanInstance::getExtensions()
	{
		// glfw extensions
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
		
		// add validation layers extension
		if(ENABLE_VALIDATION_LAYERS)
			extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);

		return extensions;
	}

	void VulkanInstance::setupDebugCallback()
	{
		if(!ENABLE_VALIDATION_LAYERS)
			return;

		VkDebugReportCallbackCreateInfoEXT createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT | VK_DEBUG_REPORT_INFORMATION_BIT_EXT;
		createInfo.pfnCallback = debugCallback;

		if(createDebugReportCallbackEXT(m_instance, &createInfo, nullptr, &m_debugCallback) != VK_SUCCESS)
			throw std::runtime_error("failed to setup debug callback");
	}

	VKAPI_ATTR VkBool32 VKAPI_CALL VulkanInstance::debugCallback(
			VkDebugReportFlagsEXT flags,
			VkDebugReportObjectTypeEXT objType,
			uint64_t obj,
			size_t location,
			int32_t code,
			const char* layerPrefix,
			const char* msg,
			void* userData)
	{
		std::string message = "[VALIDATION LAYER]: " + std::string(msg);
		// TODO: extend callback message

		// check type of message
		if(flags & VK_DEBUG_REPORT_ERROR_BIT_EXT)
			Utils::Log::error(message.c_str());
		else if(flags & VK_DEBUG_REPORT_WARNING_BIT_EXT)
			Utils::Log::warn(message.c_str());
		else if(flags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT)
			Utils::Log::warn(message.c_str());
		else if(flags & VK_DEBUG_REPORT_DEBUG_BIT_EXT)
			Utils::Log::info(message.c_str());
		else if(flags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT)
			Utils::Log::info(message.c_str());
		return VK_FALSE;
	}

	VkResult createDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackCreateInfoEXT* createInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback)
	{
		auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
		if(func != nullptr)
			return func(instance, createInfo, pAllocator, pCallback);
		else
			return VK_ERROR_EXTENSION_NOT_PRESENT;
	}

	void destroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT pCallback, const VkAllocationCallbacks* pAllocator)
	{
		auto func = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
		if(func != nullptr)
			func(instance, pCallback, pAllocator);
	}
}}
