//
// Created by Dan on 14/04/2023.
//

#ifndef GAMEENGINESKELETON_SRC_DRAWABLE_H_
#define GAMEENGINESKELETON_SRC_DRAWABLE_H_

#include <iterator>
#include "Mesh.h"

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
  };



} // rts

#endif //GAMEENGINESKELETON_SRC_DRAWABLE_H_
