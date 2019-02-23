#ifndef GAME_H
#define GAME_H

#include "graphics/window.h"
#include "graphics/vulkaninstance.h"
#include "graphics/physicaldevice.h"
#include "graphics/device.h"

namespace LavaEngine {

	class Game
	{
	private:
		Graphics::Window m_window;
		Graphics::VulkanInstance m_instance;
		Graphics::Surface m_surface;
		Graphics::PhysicalDevice m_physicalDevice;
		Graphics::Device m_device;

	public:
		Game();
		void run();
		void clean();
	};
}

#endif
