//
// Created by Dan on 15/04/2023.
//

#ifndef GAMEENGINESKELETON_SRC_DRAWABLEGRIDTERRAIN_H_
#define GAMEENGINESKELETON_SRC_DRAWABLEGRIDTERRAIN_H_

#include <array>
#include <tuple>
#include "Drawable.h"

namespace rts
{

  class DrawableGridTerrain
  {
	  static constexpr std::array<std::tuple<float, float>, 6> m_BoxCoords{std::make_tuple(1.0f, 0.0f), std::make_tuple(0.0f, 0.0f), std::make_tuple(1.0f, 1.0f),
																		   std::make_tuple(1.0f, 1.0f), std::make_tuple(0.0f, 0.0f), std::make_tuple(0.0f, 1.0f)};

	  [[maybe_unused]] Drawable<DrawableGridTerrain> &m_Parent;
	  size_t m_Width;
	  size_t m_Height;

  public:
	  explicit DrawableGridTerrain(Drawable<DrawableGridTerrain> &parent, size_t width, size_t height) : m_Parent(parent), m_Width(width), m_Height(height) {}

	  template <std::output_iterator<rts::Vertex> IteratorType>
	  void draw(IteratorType outputBegin) const noexcept
	  {
		  constexpr float width{10.0f};
		  constexpr float height{10.0f};
		  constexpr float uvWidth{10.0f};
		  constexpr float uvHeight{10.0f};

		  for(size_t x{0}; x < m_Width; x++)
		  {
			  for(size_t y{0}; y < m_Height; y++)
			  {
				  for(auto &[boxX, boxY] : m_BoxCoords)
				  {
					  *(outputBegin++) = std::make_tuple((static_cast<float>(x) * width * 1.2f) + (width * boxX), (static_cast<float>(y) * height * 1.2f) + (height * boxY), 0 + (uvWidth * boxX), 0 + (uvHeight * boxY));
				  }
			  }
		  }
	  }

	  void setPosition(const std::tuple<float, float> &) const
	  {
		  /*do nothing*/
	  }
  };

} // rts

#endif //GAMEENGINESKELETON_SRC_DRAWABLEGRIDTERRAIN_H_
