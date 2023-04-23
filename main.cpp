#include <thread>

#include <fmt/core.h>
#include "sol/sol.hpp"

#include "Example/Pong/Pong.h"

#include "src/SFMLWindow.h"
#include "src/SFMLRenderer.h"
#include "src/DrawableSprite.h"
#include "src/DrawableGridTerrain.h"
#include "src/Entity.h"
#include "src/GameObject.h"

int main()
{
	PongGame myGame;
	while(myGame.run())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}


	return 0;
}
