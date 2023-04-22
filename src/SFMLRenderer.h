//
// Created by Dan on 14/04/2023.
//

#ifndef GAMEENGINESKELETON_SRC_SFMLRENDERER_H_
#define GAMEENGINESKELETON_SRC_SFMLRENDERER_H_

#include "SFML/Graphics.hpp"
#include "Renderer.h"
#include "Mesh.h"

namespace rts
{

  class SFMLRenderer
  {
	  rts::Renderer<SFMLRenderer> &m_Parent;
	  sf::RenderWindow &m_Window;

  public:
	  explicit SFMLRenderer(rts::Renderer<SFMLRenderer> &parent, sf::RenderWindow &window) : m_Parent(parent), m_Window(window) {}

	  template <typename IteratorType>
	  void draw(IteratorType begin, IteratorType end)
	  {
		  m_Window.clear(sf::Color::Black);

		  sf::VertexArray va(sf::PrimitiveType::Triangles);
		  while(begin != end)
		  {
			  const auto [x, y, uvX, uvY, rgb] = *(begin++);
			  const auto [r, g, b] = rgb;
			  va.append(sf::Vertex{{x, y}, sf::Color(r, g, b), {uvX, uvY}});
		  }

		  m_Window.draw(va);

		  m_Window.display();
	  }
  };

} // rts

#endif //GAMEENGINESKELETON_SRC_SFMLRENDERER_H_
