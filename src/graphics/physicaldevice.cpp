#include "physicaldevice.h"

namespace LavaEngine { namespace Graphics {

#ifndef NDEBUG
	std::string deviceTypeToString(VkPhysicalDeviceType deviceType);
#endif

	PhysicalDevice::PhysicalDevice(const VkInstance& vulkanInstance, const Surface& surface)
		: m_surface(surface)
	{
		uint32_t physicalDeviceCount;
		vkEnumeratePhysicalDevices(vulkanInstance, &physicalDeviceCount, nullptr);
		if(physicalDeviceCount == 0)
			throw std::runtime_error("failed to find GPU's with Vulkan support");
		std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
		vkEnumeratePhysicalDevices(vulkanInstance, &physicalDeviceCount, physicalDevices.data());

		m_physicalDevice = pickPhysicalDevice(physicalDevices);
	}

	PhysicalDevice::~PhysicalDevice() {}

	VkPhysicalDevice PhysicalDevice::handle() const
	{
		return m_physicalDevice;
	}

	int PhysicalDevice::presentationQueueIndex() const
	{
		return m_presentationQueueIndex;
	}

	int PhysicalDevice::graphicalQueueIndex() const
	{
		return m_graphicalQueueIndex;
	}

	VkPhysicalDevice PhysicalDevice::pickPhysicalDevice(const std::vector<VkPhysicalDevice>& devices)
	{
		std::multimap<int, VkPhysicalDevice> ratedDevices;

		for(VkPhysicalDevice device : devices)
		{
			int score = ratePhysicalDevice(device);
			if(!isDeviceSuitable(device))
				score = 0;
			ratedDevices.insert(std::make_pair(score, device));
		}

		if(ratedDevices.rbegin()->first == 0)
			throw std::runtime_error("failed to find suitable GPU");

		return ratedDevices.rbegin()->second;
	}

	int PhysicalDevice::ratePhysicalDevice(VkPhysicalDevice device)
	{
		VkPhysicalDeviceProperties deviceProperties;
	   	vkGetPhysicalDeviceProperties(device, &deviceProperties);

		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

#ifndef NDEBUG
		std::string deviceName = std::string("device: ") + deviceProperties.deviceName;
		std::string deviceId = std::string("device id: ") + std::to_string(deviceProperties.deviceID);
		std::string deviceVendorId = std::string("device vendor id: ") + std::to_string(deviceProperties.vendorID);
		std::string deviceType = std::string("device type: ") + deviceTypeToString(deviceProperties.deviceType);
		std::string deviceDriverVersion = std::string("device driver version: ") + Utils::versionIntToString(deviceProperties.driverVersion);
		std::string deviceSupportedApiVersion = std::string("device supported api version: ") + Utils::versionIntToString(deviceProperties.apiVersion);
		std::string devicePipelineCacheUUID = std::string("device pipeline cahe UUID: ") + std::string(reinterpret_cast<char*>(deviceProperties.pipelineCacheUUID));
		// TODO: VkPhysicalDeviceLimits, VkPhysicalDeviceSparseProperties
		
		std::string deviceLimitsMaxImageDimension2D = std::string("max image dimension 2D: ") + std::to_string(deviceProperties.limits.maxImageDimension2D);

		Utils::Log::info("");
		Utils::Log::info(deviceName.c_str());
		Utils::Log::info(deviceId.c_str());
		Utils::Log::info(deviceVendorId.c_str());
		Utils::Log::info(deviceType.c_str());
		Utils::Log::info(deviceDriverVersion.c_str());
		Utils::Log::info(deviceSupportedApiVersion.c_str());
		Utils::Log::info(devicePipelineCacheUUID.c_str());
		Utils::Log::info("device limits:");
		Utils::Log::info(deviceLimitsMaxImageDimension2D.c_str());
#endif

		int score = 1;

		if(deviceProperties.apiVersion < MINIMUM_API_VERSION)
		{
			Utils::Log::error("minimal required api version is not supported");
			return 0;
		}
		if(!deviceFeatures.geometryShader)
		{
			Utils::Log::error("the device does not support geometry shader");
			return 0;
		}
		
		if(deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
			score += 1000;
		else
			Utils::Log::warn("the device is not discrete GPU");

		score += deviceProperties.limits.maxImageDimension2D;

		return score;
	}

	bool PhysicalDevice::isDeviceSuitable(VkPhysicalDevice device)
	{
		uint32_t queueFamilyPropertiesCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyPropertiesCount, nullptr);
		std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyPropertiesCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyPropertiesCount, queueFamilyProperties.data());

		bool isGraphicalQueueFound;
		bool isPresentationQueueFound;

		int i = 0;
		for(VkQueueFamilyProperties queueFamily : queueFamilyProperties)
		{
			// graphical queue
			if(queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				m_graphicalQueueIndex = i;
				isGraphicalQueueFound = true;
			}
			// presentational queue
			VkBool32 isPresentationSupported;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_surface.handle(), &isPresentationSupported);
			if(queueFamily.queueCount > 0 && isPresentationSupported)
			{
				m_presentationQueueIndex = i;
				isPresentationQueueFound = true;
			}
			++i;
		}

		return isGraphicalQueueFound && isPresentationQueueFound;
	}

#ifndef NDEBUG
	std::string deviceTypeToString(VkPhysicalDeviceType deviceType)
	{
		switch(deviceType)
		{
			case 0:
				return std::string("VK_PHYSICAL_DEVICE_TYPE_OTHER");

			case 1:
				return std::string("VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU");

			case 2:
				return std::string("VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU");

			case 3:
				return std::string("VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU");

			case 4:
				return std::string("VK_PHYSICAL_DEVICE_TYPE_CPU");

			default:
				return std::string("unknown device type");
		}
	}
#endif
}}
