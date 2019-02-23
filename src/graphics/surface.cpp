#include "surface.h"

namespace LavaEngine { namespace Graphics {

	Surface::Surface(const VulkanInstance& instance, GLFWwindow* window)
		: m_instance(instance)
	{
		if(glfwCreateWindowSurface(m_instance.handle(), window, nullptr, &m_surface))
			throw std::runtime_error("failed to create window surface");
	}

	Surface::~Surface()
	{
		vkDestroySurfaceKHR(m_instance.handle(), m_surface, nullptr);
	}

	VkSurfaceKHR Surface::handle() const
	{
		return m_surface;
	}
}}
