#include "device.h"

namespace LavaEngine { namespace Graphics {

	Device::Device(const VulkanInstance& instance, const PhysicalDevice& physicalDevice)
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
		VkDeviceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos = &queueCreateInfo;
		createInfo.queueCreateInfoCount = 1;
		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = 0;
		createInfo.flags = 0;

		if(VulkanInstance::ENABLE_VALIDATION_LAYERS)
		{
			std::vector<const char*>* layers = instance.requiredLayers();
			createInfo.enabledLayerCount = static_cast<uint32_t>(layers->size());
			createInfo.ppEnabledLayerNames = layers->data();
		}
		else
			createInfo.enabledLayerCount = 0;

		if(vkCreateDevice(physicalDevice.handle(), &createInfo, nullptr, &m_device) != VK_SUCCESS)
			throw std::runtime_error("failed to create logical device");
	}

	Device::~Device()
	{
		vkDestroyDevice(m_device, nullptr);
	}

	VkDevice Device::handle() const
	{
		return m_device;
	}

}}
