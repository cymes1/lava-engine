#ifndef SURFACE_H
#define SURFACE_H

#include <stdexcept>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include "vulkaninstance.h"

namespace LavaEngine { namespace Graphics {

	class Surface
	{
	private:
		VkSurfaceKHR m_surface;
		const VulkanInstance& m_instance;

	public:
		Surface(const VulkanInstance& instance, GLFWwindow* window);
		~Surface();

		VkSurfaceKHR handle() const;
	};
}}

#endif
