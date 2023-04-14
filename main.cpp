#include <fmt/core.h>
#include "sol/sol.hpp"

#include "src/SFMLWindow.h"
#include "src/SFMLRenderer.h"
#include "src/DrawableSprite.h"

int main()
{
	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::package);
	lua.safe_script("print(\"[Lua]: Hello, world!\")");

	rts::Window<rts::SFMLWindow> myWindow(800, 800, "Hello, world!");

	myWindow.getEvent<rts::WindowEvents::MouseEntered>() += [](const rts::WindowEvents::MouseEntered &) { fmt::print("[Mouse] Entered\n"); };
	myWindow.getEvent<rts::WindowEvents::MouseLeft>() += [](const rts::WindowEvents::MouseLeft &) { fmt::print("[Mouse] Left\n"); };
	myWindow.getEvent<rts::WindowEvents::LostFocus>() += [](const rts::WindowEvents::LostFocus &) { fmt::print("[Focus] Lost\n"); };
	myWindow.getEvent<rts::WindowEvents::GainedFocus>() += [](const rts::WindowEvents::GainedFocus &) { fmt::print("[Focus] Gained\n"); };
	myWindow.getEvent<rts::WindowEvents::MouseButtonPressed>() += [](const rts::WindowEvents::MouseButtonPressed &mouse) { fmt::print("[Mouse] Pressed {0}\n", mouse.button); };
	myWindow.getEvent<rts::WindowEvents::MouseButtonReleased>() += [](const rts::WindowEvents::MouseButtonReleased &mouse) { fmt::print("[Mouse] Released {0}\n", mouse.button); };


	rts::Renderer<rts::SFMLRenderer> myRenderer(myWindow.getHandle());

	std::vector<rts::Drawable<rts::DrawableSprite>> mySprites;
	mySprites.emplace_back(std::make_tuple(0.0f, 0.0f, 0.0f, 0.0f), std::make_tuple(10.0f, 10.0f), std::make_tuple(10.0f, 10.0f));


	myRenderer.GenerateMesh(mySprites.begin(), mySprites.end());


	while(myWindow.Update())
	{
		myRenderer.draw();
		/* game  loop  */
	}


	return 0;
}
