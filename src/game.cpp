#include "game.h"
#include "utils/log.h"

namespace LavaEngine {

	Game::Game()
		: m_window(800, 600, "lava"), m_instance("lava-engine")
	{
	}

	void Game::run()
	{
		while(!glfwWindowShouldClose(m_window.handler()))
		{
			glfwPollEvents();
		}
	}

	void Game::clean()
	{}
}
