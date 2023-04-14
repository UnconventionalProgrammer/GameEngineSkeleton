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
						 std::string_view title) : m_Parent(parent), m_Handle(sf::VideoMode(width, height), std::string{title})
  {
	  m_Parent.getEvent<rts::WindowEvents::Closed>() += [this](const rts::WindowEvents::Closed &) { m_Handle.close(); };
  }

  bool SFMLWindow::Update() noexcept
  {
	  sf::Event event{};
	  while (m_Handle.pollEvent(event))
	  {
		  switch(event.type)
		  {
			  case sf::Event::Closed:
				  m_Parent.getEvent<rts::WindowEvents::Closed>()({});
				  break;
			  case sf::Event::Resized:
				  m_Parent.getEvent<rts::WindowEvents::Resized>()({event.size.width, event.size.height});
				  break;
			  case sf::Event::LostFocus:
				  m_Parent.getEvent<rts::WindowEvents::LostFocus>()({});
				  break;
			  case sf::Event::GainedFocus:
				  m_Parent.getEvent<rts::WindowEvents::GainedFocus>()({});
				  break;
			  case sf::Event::TextEntered:
				  m_Parent.getEvent<rts::WindowEvents::TextEntered>()({event.text.unicode});
				  break;
			  case sf::Event::KeyPressed:
				  m_Parent.getEvent<rts::WindowEvents::KeyPressed>()({event.key.shift, event.key.control, event.key.alt, event.key.system, static_cast<uint8_t>(event.key.code)});
				  break;
			  case sf::Event::KeyReleased:
				  m_Parent.getEvent<rts::WindowEvents::KeyReleased>()({event.key.shift, event.key.control, event.key.alt, event.key.system, static_cast<uint8_t>(event.key.code)});
				  break;
			  case sf::Event::MouseWheelMoved:
				  m_Parent.getEvent<rts::WindowEvents::MouseWheelMoved>()({event.mouseWheel.delta});
				  break;
			  case sf::Event::MouseWheelScrolled:
				  m_Parent.getEvent<rts::WindowEvents::MouseWheelScrolled>()({static_cast<int>(event.mouseWheelScroll.delta)});
				  break;
			  case sf::Event::MouseButtonPressed:
				  m_Parent.getEvent<rts::WindowEvents::MouseButtonPressed>()({static_cast<uint8_t>(event.mouseButton.button)});
				  break;
			  case sf::Event::MouseButtonReleased:
				  m_Parent.getEvent<rts::WindowEvents::MouseButtonReleased>()({static_cast<uint8_t>(event.mouseButton.button)});
				  break;
			  case sf::Event::MouseMoved:
				  m_Parent.getEvent<rts::WindowEvents::MouseMoved>()({event.mouseMove.x, event.mouseMove.y});
				  break;
			  case sf::Event::MouseEntered:
				  m_Parent.getEvent<rts::WindowEvents::MouseEntered>()({});
				  break;
			  case sf::Event::MouseLeft:
				  m_Parent.getEvent<rts::WindowEvents::MouseLeft>()({});
				  break;
			  default: break;
		  }
	  }

	  return m_Handle.isOpen();
  }
} // rts