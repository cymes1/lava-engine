#ifndef DEVICE_H
#define DEVICE_H

#include <vulkan/vulkan.h>
#include "../utils/log.h"
#include "vulkaninstance.h"
#include "physicaldevice.h"

namespace LavaEngine { namespace Graphics {

	class Device
	{
	private:
		VkDevice m_device;

	public:
		Device(const VulkanInstance& instance, const PhysicalDevice& physicalDevice);
		~Device();

		VkDevice handle() const;
	};

}}

#endif
