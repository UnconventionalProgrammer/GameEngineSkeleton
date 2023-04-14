//
// Created by Dan on 13/04/2023.
//

#ifndef MYRTS_SRC_WINDOWEVENT_H_
#define MYRTS_SRC_WINDOWEVENT_H_

#include <functional>

namespace rts
{
  template <typename EventType>
  class WindowEvent
  {
	  std::function<void(const EventType &)> callback{};
  public:

	  template <typename CallbackType>
	  WindowEvent& operator+=(const CallbackType &&cb) noexcept
	  {
		  callback = std::move(cb);
		  return *this;
	  }

	  void operator ()(const EventType &args)
	  {
		  if(callback)
		  {
			  callback(std::move(args));
		  }
	  }
  };



} // rts

#endif //MYRTS_SRC_WINDOWEVENT_H_
