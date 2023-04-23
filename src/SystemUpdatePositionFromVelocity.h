//
// Created by Dan on 23/04/2023.
//

#ifndef GAMEENGINESKELETON_SRC_SYSTEMUPDATEPOSITIONFROMVELOCITY_H_
#define GAMEENGINESKELETON_SRC_SYSTEMUPDATEPOSITIONFROMVELOCITY_H_

#include "System.h"
#include "GameObject.h"

namespace rts
{

  class SystemUpdatePositionFromVelocity
  {
	  [[maybe_unused]] System<SystemUpdatePositionFromVelocity> &m_Parent;

  public:
	  explicit SystemUpdatePositionFromVelocity(System<SystemUpdatePositionFromVelocity> &parent);

	  template <typename EntityType>
	  void Update(EntityType &entity, const float deltaTimeSeconds) const noexcept
	  {
		  auto [xVel, yVel] = entity.template getComponent<rts::Component<rts::GameObjectComponents::Velocity>>().read().m_Velocity;
		  auto &position = entity.template getComponent<rts::Component<rts::GameObjectComponents::Position>>();

		  auto [x, y] = position.read().m_Position;
		  position.write(rts::GameObjectComponents::Position{std::make_tuple(x + (xVel * deltaTimeSeconds), y + (yVel * deltaTimeSeconds))});
	  }

	  template <std::input_iterator IteratorType>
	  void Update(IteratorType begin, IteratorType end, const float deltaTimeSeconds) const noexcept
	  {
		  while(begin != end)
		  {
			  Update(*(begin++), deltaTimeSeconds);
		  }
	  }


  };

} // rts

#endif //GAMEENGINESKELETON_SRC_SYSTEMUPDATEPOSITIONFROMVELOCITY_H_
