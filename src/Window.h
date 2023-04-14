//
// Created by Dan on 13/04/2023.
//

#ifndef MYRTS_SRC_WINDOW_H_
#define MYRTS_SRC_WINDOW_H_

#include <utility>
#include <tuple>
#include <cstdint>
#include "WindowEvent.h"


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

  class IWindow
  {
  public:
	  virtual bool Update() = 0;
	  virtual ~IWindow() = default;
  };

  template <typename WindowHandler>
  class Window : private IWindow
  {
	  std::tuple<rts::WindowEvent<WindowEvents::Closed>,
				   rts::WindowEvent<WindowEvents::Resized>,
				   rts::WindowEvent<WindowEvents::LostFocus>,
				   rts::WindowEvent<WindowEvents::GainedFocus>,
				   rts::WindowEvent<WindowEvents::TextEntered>,
				   rts::WindowEvent<WindowEvents::KeyPressed>,
				   rts::WindowEvent<WindowEvents::KeyReleased>,
				   rts::WindowEvent<WindowEvents::MouseWheelMoved>,
				   rts::WindowEvent<WindowEvents::MouseWheelScrolled>,
				   rts::WindowEvent<WindowEvents::MouseButtonPressed>,
				   rts::WindowEvent<WindowEvents::MouseButtonReleased>,
				   rts::WindowEvent<WindowEvents::MouseMoved>,
				   rts::WindowEvent<WindowEvents::MouseEntered>,
				   rts::WindowEvent<WindowEvents::MouseLeft>       > m_Events;

	  WindowHandler m_Handler;
  public:
	  template <typename ...Args>
	  requires (!std::is_same_v<WindowHandler, Window>)
	  explicit Window(Args&&... args) : m_Handler(*this, std::forward<Args>(args)...) {}
	  ~Window() override = default;

	  template <typename EventType>
	  rts::WindowEvent<EventType> &getEvent() noexcept
	  {
		  return std::get<rts::WindowEvent<EventType>>(m_Events);
	  }

	  bool Update() noexcept override { return m_Handler.Update(); }
  };
} // rts

#endif //MYRTS_SRC_WINDOW_H_
