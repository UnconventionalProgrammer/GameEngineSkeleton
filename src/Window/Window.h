//
// Created by Dan on 13/04/2023.
//

#ifndef MYRTS_SRC_WINDOW_H_
#define MYRTS_SRC_WINDOW_H_

#include <utility>
#include <tuple>
#include <cstdint>
#include "../Event.h"


namespace rts
{
  namespace WindowEvents
  {
	struct Closed {};
	struct Resized{ size_t width{0}; size_t height{0}; };
	struct LostFocus{};
	struct GainedFocus{};
	struct TextEntered{ uint32_t character{0}; };
	struct KeyPressed{bool shift{false}; bool control{false}; bool alt{false}; bool system{false}; uint8_t key{0}; };
	struct KeyReleased{bool shift{false}; bool control{false}; bool alt{false}; bool system{false}; uint8_t key{0}; };
	struct MouseWheelMoved{int amount{0}; };
	struct MouseWheelScrolled{int amount{0}; };
	struct MouseButtonPressed{uint8_t button{0}; };
	struct MouseButtonReleased{uint8_t button{0}; };
	struct MouseMoved{int x{0}; int y{0}; };
	struct MouseEntered{};
	struct MouseLeft{};
  }

  template <typename WindowHandler>
  class Window
  {
	  std::tuple<rts::Event<WindowEvents::Closed>,
				   rts::Event<WindowEvents::Resized>,
				   rts::Event<WindowEvents::LostFocus>,
				   rts::Event<WindowEvents::GainedFocus>,
				   rts::Event<WindowEvents::TextEntered>,
				   rts::Event<WindowEvents::KeyPressed>,
				   rts::Event<WindowEvents::KeyReleased>,
				   rts::Event<WindowEvents::MouseWheelMoved>,
				   rts::Event<WindowEvents::MouseWheelScrolled>,
				   rts::Event<WindowEvents::MouseButtonPressed>,
				   rts::Event<WindowEvents::MouseButtonReleased>,
				   rts::Event<WindowEvents::MouseMoved>,
				   rts::Event<WindowEvents::MouseEntered>,
				   rts::Event<WindowEvents::MouseLeft>       > m_Events;

	  WindowHandler m_Handler;
  public:
	  template <typename ...Args>
	  requires (!std::is_same_v<WindowHandler, Window>)
	  explicit Window(Args&&... args) : m_Handler(*this, std::forward<Args>(args)...) {}

	  template <typename EventType>
	  rts::Event<EventType> &getEvent() noexcept
	  {
		  return std::get<rts::Event<EventType>>(m_Events);
	  }

	  [[nodiscard]]bool Update() noexcept { return m_Handler.Update(); }
	  [[nodiscard]] auto &getHandle() noexcept { return m_Handler.getHandle(); }
  };
} // rts

#endif //MYRTS_SRC_WINDOW_H_
