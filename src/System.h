//
// Created by Dan on 16/04/2023.
//

#ifndef GAMEENGINESKELETON_SRC_SYSTEM_H_
#define GAMEENGINESKELETON_SRC_SYSTEM_H_

#include <utility>

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
  };

} // rts

#endif //GAMEENGINESKELETON_SRC_SYSTEM_H_
