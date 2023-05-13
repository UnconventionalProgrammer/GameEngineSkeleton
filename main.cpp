#include <thread>

#include <fmt/core.h>
#include "sol/sol.hpp"

#include "Example/Pong/Pong.h"

#include "src/Window/SFMLWindow.h"
#include "src/Renderer/SFMLRenderer.h"
#include "src/Drawable/DrawableSprite.h"
#include "src/Drawable/DrawableGridTerrain.h"
#include "src/ECS/Entity.h"
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
