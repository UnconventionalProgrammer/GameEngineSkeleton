#include <thread>
#include "Example/Pong/Pong.h"

int main()
{
	PongGame myGame;
	while(myGame.run())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}


	return 0;
}
