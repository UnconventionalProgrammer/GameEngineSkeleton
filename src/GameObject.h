//
// Created by Dan on 16/04/2023.
//

#ifndef GAMEENGINESKELETON_SRC_GAMEOBJECT_H_
#define GAMEENGINESKELETON_SRC_GAMEOBJECT_H_

#include <tuple>
#include "Entity.h"

namespace rts
{

  	template <typename ...Args>
	class GameObject
	{
		std::tuple< rts::Event<EntityEvents::PositionChanged> > m_Events;

		std::tuple<Args...> m_Components{};
		rts::Entity<GameObject<Args...>> &m_Parent;

	public:
		explicit GameObject(rts::Entity<GameObject<Args...>> &parent) : m_Parent(parent) {}

		template <typename EventType>
		rts::Event<EventType> &getEvent() noexcept
		{
			return std::get<rts::Event<EventType>>(m_Events);
		}

		template <typename ComponentType>
		ComponentType &getComponent() noexcept
		{
			return std::get<ComponentType>(m_Components);
		}

		rts::Entity<GameObject<Args...>> &getParent()
		{
			return m_Parent;
		}
	};

  namespace GameObjectComponents
  {
	struct Position
	{
		using value_type = std::tuple<float, float>;
		value_type m_Position;

		template <typename GameObjectType>
		void set(GameObjectType &parent, const value_type &newPosition)
		{
			parent.getGameObject().template getEvent<rts::EntityEvents::PositionChanged>().invoke({m_Position, newPosition});
			m_Position = newPosition;
		}
	};
  }

} // rts

#endif //GAMEENGINESKELETON_SRC_GAMEOBJECT_H_
