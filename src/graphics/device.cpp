#include "device.h"

namespace LavaEngine { namespace Graphics {

	Device::Device(const PhysicalDevice& physicalDevice)
   	{
		// specify queues to be created
		float queuePriority = 1.0f;

		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = physicalDevice.graphicalQueueIndex();
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;

		// set device features
		VkPhysicalDeviceFeatures deviceFeatures = {};

		// create logical device
		VkDeviceCreateInfo createInfo;
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos = &queueCreateInfo;
		createInfo.queueCreateInfoCount = 1;
		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = 0;
	}

	Device::~Device() {}

	VkDevice Device::handle()
	{
		return m_device;
	}

}}
