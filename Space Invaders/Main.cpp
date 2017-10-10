#include <VirtualGameConsole/VGCVirtualGameConsole.h>

#include "Game.hpp"

static const int WINDOW_SIZE_X = 512;
static const int WINDOW_SIZE_Y = 512;

void Start_Game();

int VGCMain(const std::vector<std::string> &arguments) {
	VGCVirtualGameConsole::initialize("Space Invaders", WINDOW_SIZE_X, WINDOW_SIZE_Y);

	Start_Game();

	VGCVirtualGameConsole::finalize();
	return 0;
}

// Need separate scope for initialization of game so destructor can run before finalization.
void Start_Game() {
	Game game(WINDOW_SIZE_X, WINDOW_SIZE_Y);

	while (!game.gameOver && VGCVirtualGameConsole::beginLoop()) {
		if (VGCDisplay::beginFrame()) {
			game.RunFrame();
			VGCDisplay::endFrame();
		}

		VGCVirtualGameConsole::endLoop();
	}
}
