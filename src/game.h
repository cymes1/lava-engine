#ifndef GAME_H
#define GAME_H

#include "graphics/window.h"
#include "graphics/vulkaninstance.h"

namespace LavaEngine {

	class Game
	{
	private:
		Graphics::Window m_window;
		Graphics::VulkanInstance m_instance;

	public:
		Game();
		void run();
		void clean();
	};
}

#endif
