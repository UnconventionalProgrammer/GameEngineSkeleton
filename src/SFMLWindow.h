//
// Created by Dan on 13/04/2023.
//

#ifndef MYRTS_SRC_SFMLWINDOW_H_
#define MYRTS_SRC_SFMLWINDOW_H_

#include "SFML/Window.hpp"
#include "Window.h"

namespace rts
{
  class SFMLWindow
  {
	  rts::Window<SFMLWindow> &m_Parent;
	  sf::Window m_Handle;
  public:
	  explicit SFMLWindow(rts::Window<SFMLWindow> &parent, unsigned int width, unsigned int height, std::string_view title);

	  bool Update();
  };

} // rts

#endif //MYRTS_SRC_SFMLWINDOW_H_
