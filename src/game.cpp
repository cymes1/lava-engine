#include "game.h"
#include "utils/log.h"

namespace LavaEngine {

	Game::Game()
		: m_window(800, 600, "lava"),
		m_instance("lava-engine"),
		m_surface(m_instance, m_window.handle()),
		m_physicalDevice(m_instance.handle(), m_surface),
		m_device(m_instance, m_physicalDevice)
	{
	}

	void Game::run()
	{
		while(!glfwWindowShouldClose(m_window.handle()))
		{
			glfwPollEvents();
		}
	}

	void Game::clean()
	{}
}
