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
		rts::Entity<GameObject<Args...>> &m_Parent;

		std::tuple< rts::Event<EntityEvents::PositionChanged> > m_Events;
		std::tuple<Args...> m_Components;


	public:
		GameObject() = delete;
		explicit GameObject(rts::Entity<GameObject<Args...>> &parent) : m_Parent(parent) {}
		explicit GameObject(rts::Entity<GameObject<Args...>> &parent, std::tuple<Args...> &&components) : m_Parent(parent), m_Components(std::move(components)) {}

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

	  template <std::default_initializable ComponentType>
	  class Component
	  {
		  using OnWriteType = std::function<void(const ComponentType &, const ComponentType &)>;

		  ComponentType m_Component;
		  std::function<void(const ComponentType &, const ComponentType &)> m_onWrite{[](const auto &, const auto &) { /* do nothing */}};

	  public:
		  Component() = delete;
		  explicit Component(OnWriteType &&onWrite) : m_onWrite(std::move(onWrite)) {}
		  explicit Component(const ComponentType &component) : m_Component(component) {}
		  explicit Component(const ComponentType &&component) : m_Component(std::move(component)) {}
		  explicit Component(const ComponentType &component, OnWriteType &&onWrite) : m_Component(component), m_onWrite(std::move(onWrite)) {}
		  explicit Component(const ComponentType &&component, OnWriteType &&onWrite) : m_Component(std::move(component)), m_onWrite(std::move(onWrite)) {}

		  void write(const ComponentType &component) { m_onWrite(m_Component, component); m_Component = component; }

		  const ComponentType &read() { return m_Component; }

		  void operator <<(const ComponentType &component) { write(component); }
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

	struct Velocity
	{
		using value_type = std::tuple<float, float>;
		value_type m_Velocity;

		template <typename GameObjectType>
		void set(GameObjectType &parent, const value_type &newVelocity)
		{
			parent.getGameObject().template getEvent<rts::EntityEvents::VelocityChanged>().invoke({m_Velocity, newVelocity});
			m_Velocity = newVelocity;
		}
	};
  }

} // rts

#endif //GAMEENGINESKELETON_SRC_GAMEOBJECT_H_
