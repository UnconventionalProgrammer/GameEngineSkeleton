//
// Created by Dan on 13/04/2023.
//

#ifndef MYRTS_SRC_SFMLWINDOW_H_
#define MYRTS_SRC_SFMLWINDOW_H_

#include "SFML/Graphics.hpp"
#include "Window.h"

namespace rts
{
  class SFMLWindow
  {
	  rts::Window<SFMLWindow> &m_Parent;
	  sf::RenderWindow m_Handle;
  public:
	  explicit SFMLWindow(rts::Window<SFMLWindow> &parent, unsigned int width, unsigned int height, std::string_view title);

	  [[nodiscard]] bool Update() noexcept;
	  [[nodiscard]] sf::RenderWindow &getHandle() noexcept { return m_Handle; }
  };

} // rts

#endif //MYRTS_SRC_SFMLWINDOW_H_
