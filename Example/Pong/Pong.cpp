
#include "Pong.h"

PongGame::PongGame()
{
	m_Window.getEvent<rts::WindowEvents::MouseMoved>() += [this](const rts::WindowEvents::MouseMoved &mouse)
	{
		std::visit([&mouse](rts::Drawable<rts::DrawableRectangle> &position)
	  		{
				auto [oldX, oldY] = position.getPosition();
				position.setPosition({oldX, static_cast<float>(mouse.y)});
			},
			m_Sprites[1] );
	};
}


bool PongGame::run()
{
	m_Renderer.GenerateMesh(m_Sprites.begin(), m_Sprites.end());
	m_Renderer.draw();

	return m_Window.Update();
}
