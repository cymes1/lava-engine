#ifndef PHYSICALDEVICE_H
#define PHYSICALDEVICE_H

#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <vulkan/vulkan.h>

#include "../utils/log.h"
#include "../utils/utils.h"

namespace LavaEngine { namespace Graphics {

	class PhysicalDevice
	{
	private:
		const uint32_t MINIMUM_API_VERSION = VK_API_VERSION_1_0;

		VkPhysicalDevice m_physicalDevice;
		int m_graphicalQueueIndex;

	public:
		PhysicalDevice(const VkInstance& vulkanInstance);
		~PhysicalDevice();

		VkPhysicalDevice handle();
		int graphicalQueueIndex() const;

	private:
		VkPhysicalDevice pickPhysicalDevice(const std::vector<VkPhysicalDevice>& physicalDevices);
		int ratePhysicalDevice(VkPhysicalDevice device);
		bool isDeviceSuitable(VkPhysicalDevice device);
	};

}}

#endif
