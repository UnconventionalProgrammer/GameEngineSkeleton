#include <fmt/core.h>
#include "sol/sol.hpp"

#include "src/SFMLWindow.h"

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
	while(myWindow.Update())
	{
		/* game  loop  */
	}


	return 0;
}
