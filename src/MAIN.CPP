#include <iostream>

#include "GAME.HPP"

#define G_WIDTH 960
#define G_HEIGHT 480
#define G_FPS 60

int main()
{
   if (!GAME::Init(G_WIDTH, G_HEIGHT)) {
	std::cout << "Failed to initialize game. Terminating." << std::endl;
	return 1;
   }
   GAME::Run(G_FPS);

   GAME::Terminate();
   return 0;
}