//
// Created by Dan on 13/04/2023.
//

#include "Window.h"
#include "SFMLWindow.h"

namespace rts
{
  SFMLWindow::SFMLWindow(Window<SFMLWindow> &parent,
						 unsigned int width,
						 unsigned int height,
						 std::string_view title) : m_Parent(parent), m_Handle(sf::VideoMode({width, height}), std::string{title})
  {
	  m_Parent.getEvent<rts::WindowEvents::Closed>() += [this](const rts::WindowEvents::Closed &) { m_Handle.close(); };
  }

  bool SFMLWindow::Update() noexcept
  {
  	while (const std::optional event = m_Parent.getHandle().pollEvent())
  	{

  		if (event->is<sf::Event::Closed>())
  			m_Parent.getEvent<rts::WindowEvents::Closed>()({});

  		if (const auto* resize = event->getIf<sf::Event::Resized>())
  			m_Parent.getEvent<rts::WindowEvents::Resized>()({resize->size.x, resize->size.y});

  		if (event->is<sf::Event::FocusLost>())
  			m_Parent.getEvent<rts::WindowEvents::LostFocus>()({});

  		if (event->is<sf::Event::FocusGained>())
  			m_Parent.getEvent<rts::WindowEvents::GainedFocus>()({});

  		if (const auto*textEntered = event->getIf<sf::Event::TextEntered>())
  			m_Parent.getEvent<rts::WindowEvents::TextEntered>()({textEntered->unicode});

  		if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
  			m_Parent.getEvent<rts::WindowEvents::KeyPressed>()({keyPressed->shift, keyPressed->control, keyPressed->alt, keyPressed->system, static_cast<uint8_t>(keyPressed->code)});

  		if (const auto *keyReleased = event->getIf<sf::Event::KeyReleased>())
  			m_Parent.getEvent<rts::WindowEvents::KeyReleased>()({keyReleased->shift, keyReleased->control, keyReleased->alt, keyReleased->system, static_cast<uint8_t>(keyReleased->code)});

  		if (const auto *mouseWheelMoved = event->getIf<sf::Event::MouseWheelScrolled>())
  			m_Parent.getEvent<rts::WindowEvents::MouseWheelMoved>()({mouseWheelMoved->delta});

  		if (const auto *mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
  			m_Parent.getEvent<rts::WindowEvents::MouseButtonPressed>()({static_cast<uint8_t>(mouseButtonPressed->button)});

  		if (const auto *mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
  			m_Parent.getEvent<rts::WindowEvents::MouseButtonReleased>()({static_cast<uint8_t>(mouseButtonReleased->button)});

  		if (const auto *mouseMoved = event->getIf<sf::Event::MouseMoved>())
  			m_Parent.getEvent<rts::WindowEvents::MouseMoved>()({mouseMoved->position.x, mouseMoved->position.y});

  		if (event->is<sf::Event::MouseEntered>())
  			m_Parent.getEvent<rts::WindowEvents::MouseEntered>()({});

  		if (event->is<sf::Event::MouseLeft>())
  			m_Parent.getEvent<rts::WindowEvents::MouseLeft>()({});

  	}

  	return m_Handle.isOpen();
  }
} // rts