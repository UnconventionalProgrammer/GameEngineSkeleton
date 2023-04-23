//
// Created by Dan on 16/04/2023.
//

#ifndef GAMEENGINESKELETON_SRC_SYSTEM_H_
#define GAMEENGINESKELETON_SRC_SYSTEM_H_

#include <utility>
#include <iterator>

namespace rts
{

  template <typename SystemType>
  class System
  {
	  SystemType m_System;

  public:
	  template <typename ...Args>
	  requires (!std::is_same_v<SystemType, System>)
	  explicit System(Args&&... args) : m_System(*this, std::forward<Args>(args)...) {}

	  template <std::input_iterator IteratorType>
	  void Update(IteratorType begin, IteratorType end, const float deltaTimeSeconds) const noexcept
	  {
		  m_System.Update(begin, end, deltaTimeSeconds);
	  }

	  template <typename EntityType>
	  void Update(EntityType &entity, const float deltaTimeSeconds) const noexcept
	  {
		  m_System.Update(entity, deltaTimeSeconds);
	  }

  };

} // rts

#endif //GAMEENGINESKELETON_SRC_SYSTEM_H_
