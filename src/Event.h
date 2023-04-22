//
// Created by Dan on 13/04/2023.
//

#ifndef MYRTS_SRC_WINDOWEVENT_H_
#define MYRTS_SRC_WINDOWEVENT_H_

#include <functional>

namespace rts
{
  template <typename EventType>
  class Event
  {
	  std::function<void(const EventType &)> callback{};
  public:

	  template <typename CallbackType>
	  Event& operator+=(const CallbackType &&cb) noexcept
	  {
		  callback = std::move(cb);
		  return *this;
	  }

	  void invoke(const EventType &args) const noexcept
	  {
		  if(callback)
			  callback(std::move(args));
	  }

	  void operator ()(const EventType &args) const noexcept
	  {
		  invoke(args);
	  }
  };
} // rts

#endif //MYRTS_SRC_WINDOWEVENT_H_
