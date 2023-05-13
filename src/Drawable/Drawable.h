//
// Created by Dan on 14/04/2023.
//

#ifndef GAMEENGINESKELETON_SRC_DRAWABLE_H_
#define GAMEENGINESKELETON_SRC_DRAWABLE_H_

#include <iterator>
#include "../Mesh.h"

namespace rts
{
  template <typename DrawableObject>
  class Drawable
  {
	  DrawableObject m_Object;
  public:
	  template <typename ...Args>
	  requires (!std::is_same_v<DrawableObject, Drawable>)
	  explicit Drawable(Args&&... args) : m_Object(*this, std::forward<Args>(args)...) {}


	  template <std::output_iterator<rts::Vertex> IteratorType>
	  void draw(IteratorType outputBegin)
	  {
		  m_Object.draw(outputBegin);
	  }

	  void setPosition(const std::tuple<float, float> &newPosition)
	  {
		  m_Object.setPosition(newPosition);
	  }

	  [[nodiscard]] const std::tuple<float, float> &getPosition()
	  {
		  return m_Object.getPosition();
	  }
  };

  namespace Colour
  {
	using ColourType = std::tuple<uint8_t, uint8_t, uint8_t>;
	constexpr static ColourType Red{255, 0, 0};
	constexpr static ColourType Green{0, 255, 0};
	constexpr static ColourType Blue{0, 0, 255};
	constexpr static ColourType White{255, 255, 255};
	constexpr static ColourType Black{255, 255, 255};
  }



} // rts

#endif //GAMEENGINESKELETON_SRC_DRAWABLE_H_
