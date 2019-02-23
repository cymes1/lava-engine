#ifndef PHYSICALDEVICE_H
#define PHYSICALDEVICE_H

#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <vulkan/vulkan.h>

#include "surface.h"
#include "../utils/log.h"
#include "../utils/utils.h"

namespace LavaEngine { namespace Graphics {

	class PhysicalDevice
	{
	private:
		const uint32_t MINIMUM_API_VERSION = VK_API_VERSION_1_0;

		VkPhysicalDevice m_physicalDevice;
		const Surface& m_surface;
		int m_graphicalQueueIndex;
		int m_presentationQueueIndex;

	public:
		PhysicalDevice(const VkInstance& vulkanInstance, const Surface& surface);
		~PhysicalDevice();

		VkPhysicalDevice handle() const;
		int graphicalQueueIndex() const;
		int presentationQueueIndex() const;

	private:
		VkPhysicalDevice pickPhysicalDevice(const std::vector<VkPhysicalDevice>& physicalDevices);
		int ratePhysicalDevice(VkPhysicalDevice device);
		bool isDeviceSuitable(VkPhysicalDevice device);
	};

}}

#endif
