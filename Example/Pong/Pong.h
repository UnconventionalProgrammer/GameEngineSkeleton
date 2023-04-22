#ifndef MYRTS_EXAMPLE_PONG_PONG_H_
#define MYRTS_EXAMPLE_PONG_PONG_H_

#include "../../src/SFMLWindow.h"
#include "../../src/SFMLRenderer.h"
#include "../../src/GameObject.h"
#include "../../src/DrawableRectangle.h"

class PongGame
{
	rts::Window<rts::SFMLWindow> m_Window{800, 800, "Pong Game Example"};

	std::vector<std::variant<rts::Drawable<rts::DrawableRectangle>>> m_Sprites{rts::Drawable<rts::DrawableRectangle>{std::make_tuple(20.0f, 20.0f), std::make_tuple(400.0f, 400.0f), rts::Colour::White}, //ball
																			   rts::Drawable<rts::DrawableRectangle>{std::make_tuple(20.0f, 100.0f), std::make_tuple(10.0f, 400.0f), rts::Colour::White}, //player paddle
																			   rts::Drawable<rts::DrawableRectangle>{std::make_tuple(20.0f, 100.0f), std::make_tuple(770.0f, 400.0f), rts::Colour::White} }; //computer paddle

	rts::Entity<rts::GameObject<rts::Component<rts::GameObjectComponents::Position>>> m_PlayerPaddle{
		(std::make_tuple(rts::Component<rts::GameObjectComponents::Position>(
			[this] (const rts::GameObjectComponents::Position &, const rts::GameObjectComponents::Position &newPosition)
			{
			  std::visit([&newPosition](auto &sprite) { sprite.setPosition(newPosition.m_Position); }, this->m_Sprites[1]);
			})))
	};

	rts::Entity<rts::GameObject<rts::Component<rts::GameObjectComponents::Position>>> m_ComputerPaddle{
		(std::make_tuple(rts::Component<rts::GameObjectComponents::Position>(
			[this] (const rts::GameObjectComponents::Position &, const rts::GameObjectComponents::Position &newPosition)
			{
			  std::visit([&newPosition](auto &sprite) { sprite.setPosition(newPosition.m_Position); }, this->m_Sprites[2]);
			})))
	};

	rts::Renderer<rts::SFMLRenderer> m_Renderer{m_Window.getHandle()};

public:
	PongGame();
	bool run();
};

#endif