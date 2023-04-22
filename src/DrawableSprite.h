//
// Created by Dan on 14/04/2023.
//

#ifndef GAMEENGINESKELETON_SRC_DRAWABLESPRITE_H_
#define GAMEENGINESKELETON_SRC_DRAWABLESPRITE_H_

#include <array>
#include "Drawable.h"

namespace rts
{
  class DrawableSprite
  {
	  static constexpr std::array<std::tuple<float, float>, 6> m_BoxCoords{std::make_tuple(1.0f, 0.0f), std::make_tuple(0.0f, 0.0f), std::make_tuple(1.0f, 1.0f),
																		   std::make_tuple(1.0f, 1.0f), std::make_tuple(0.0f, 0.0f), std::make_tuple(0.0f, 1.0f)};

	  Drawable<DrawableSprite> &m_Parent;

	  std::tuple<float, float, float, float> m_UVCoords{};
	  std::tuple<float, float> m_Size{};
	  std::tuple<float, float> m_Position{};

  public:
	  explicit DrawableSprite(Drawable<DrawableSprite> &parent, const std::tuple<float, float, float, float> &uv, const std::tuple<float, float> &size, const std::tuple<float, float> &position)
	  															: m_Parent(parent), m_UVCoords(uv), m_Size(size), m_Position(position) {}


	  template <std::output_iterator<rts::Vertex> IteratorType>
	  void draw(IteratorType outputBegin) const noexcept
	  {
		  const auto &[uvX, uvY, uvWidth, uvHeight] = m_UVCoords;
		  const auto &[width, height] = m_Size;
		  const auto &[posX, posY] = m_Position;

		  for(auto &[boxX, boxY] : m_BoxCoords)
		  {
			  *(outputBegin++) = std::make_tuple(posX + (width * boxX), posY + (height * boxY), uvX + (uvWidth * boxX), uvY + (uvHeight * boxY));
		  }
	  }

	  void setPosition(const std::tuple<float, float> &newPosition) noexcept
	  {
		  m_Position = newPosition;
	  }
  };

} // rts

#endif //GAMEENGINESKELETON_SRC_DRAWABLESPRITE_H_
