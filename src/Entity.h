//
// Created by Dan on 16/04/2023.
//

#ifndef GAMEENGINESKELETON_SRC_ENTITY_H_
#define GAMEENGINESKELETON_SRC_ENTITY_H_

#include <tuple>
#include "Event.h"

namespace rts
{

  namespace EntityEvents
  {
	struct PositionChanged
	{
		std::tuple<float, float> oldPosition;
		std::tuple<float, float> newPosition;
	};

  }

  template <typename GameObjectHandler>
  class Entity
  {
	  GameObjectHandler m_Handler;

  public:
	  template <typename ...Args>
	  requires (!std::is_same_v<GameObjectHandler, Entity>)
	  explicit Entity(Args&&... args) : m_Handler(*this, std::forward<Args>(args)...) {}

	  template <typename ComponentType>
	  ComponentType &getComponent() noexcept
	  {
		  return m_Handler.template getComponent<ComponentType>();
	  }

	  [[nodiscard]] GameObjectHandler &getGameObject() noexcept
	  {
		  return m_Handler;
	  }
  };
} // rts

#endif //GAMEENGINESKELETON_SRC_ENTITY_H_
