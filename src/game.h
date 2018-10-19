#ifndef GAME_H
#define GAME_H

#include "graphics/window.h"
#include "graphics/vulkaninstance.h"
#include "graphics/physicaldevice.h"

namespace LavaEngine {

	class Game
	{
	private:
		Graphics::Window m_window;
		Graphics::VulkanInstance m_instance;
		Graphics::PhysicalDevice m_physicalDevice;

	public:
		Game();
		void run();
		void clean();
	};
}

#endif
