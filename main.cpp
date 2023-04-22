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
{/*
	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::package);
	lua.safe_script("print(\"[Lua]: Hello, world!\")");*/

	rts::Window<rts::SFMLWindow> myWindow(800, 800, "Hello, world!");



	std::vector<std::variant<rts::Drawable<rts::DrawableSprite>, rts::Drawable<rts::DrawableGridTerrain>>> mySprites;
	mySprites.reserve(4);

	mySprites.emplace_back(rts::Drawable<rts::DrawableGridTerrain>{60, 60});
	mySprites.emplace_back(rts::Drawable<rts::DrawableSprite>{std::make_tuple(0.0f, 0.0f, 0.0f, 0.0f), std::make_tuple(10.0f, 10.0f), std::make_tuple(10.0f, 10.0f)});
	auto mouseSprite = mySprites.rbegin();
		mySprites.emplace_back(rts::Drawable<rts::DrawableSprite>{std::make_tuple(0.0f, 0.0f, 0.0f, 0.0f), std::make_tuple(30.0f, 15.0f), std::make_tuple(100.0f, 10.0f)});
	mySprites.emplace_back(rts::Drawable<rts::DrawableSprite>{std::make_tuple(0.0f, 0.0f, 0.0f, 0.0f), std::make_tuple(50.0f, 40.0f), std::make_tuple(200.0f, 200.0f)});

	rts::Entity<rts::GameObject<rts::Component<rts::GameObjectComponents::Position>>> myObject
	(std::make_tuple(rts::Component<rts::GameObjectComponents::Position>(
			[&mouseSprite] (const rts::GameObjectComponents::Position &, const rts::GameObjectComponents::Position &newPosition)
			{
			  std::visit([&newPosition](auto &sprite) { sprite.setPosition(newPosition.m_Position); }, *mouseSprite);
			})));

	myWindow.getEvent<rts::WindowEvents::MouseMoved>() += [&myObject](const rts::WindowEvents::MouseMoved &mouse)
	    {
			myObject.getComponent<rts::Component<rts::GameObjectComponents::Position>>().write({std::make_tuple<float, float>(static_cast<float>(mouse.x), static_cast<float>(mouse.y))});
		};


	myWindow.getEvent<rts::WindowEvents::MouseEntered>() += [](const rts::WindowEvents::MouseEntered &) { fmt::print("[Mouse] Entered\n"); };
	myWindow.getEvent<rts::WindowEvents::MouseLeft>() += [](const rts::WindowEvents::MouseLeft &) { fmt::print("[Mouse] Left\n"); };
	myWindow.getEvent<rts::WindowEvents::LostFocus>() += [](const rts::WindowEvents::LostFocus &) { fmt::print("[Focus] Lost\n"); };
	myWindow.getEvent<rts::WindowEvents::GainedFocus>() += [](const rts::WindowEvents::GainedFocus &) { fmt::print("[Focus] Gained\n"); };
	myWindow.getEvent<rts::WindowEvents::MouseButtonPressed>() += [](const rts::WindowEvents::MouseButtonPressed &mouse) { fmt::print("[Mouse] Pressed {0}\n", mouse.button); };
	myWindow.getEvent<rts::WindowEvents::MouseButtonReleased>() += [](const rts::WindowEvents::MouseButtonReleased &mouse) { fmt::print("[Mouse] Released {0}\n", mouse.button); };


	rts::Renderer<rts::SFMLRenderer> myRenderer(myWindow.getHandle());


	PongGame myGame;
	while(myGame.run())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}


	return 0;
}
