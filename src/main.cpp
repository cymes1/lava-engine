#include <iostream>
#include <stdexcept>
#include "utils/log.h"
#include "game.h"

int main()
{
	LavaEngine::Game game;

	try
	{
		game.run();
	}
	catch(const std::runtime_error& e)
	{
		LavaEngine::Utils::Log::error(e.what());
		return -1;
	}

	game.clean();

	return 0;
}
