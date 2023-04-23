//
// Created by Dan on 14/04/2023.
//

#ifndef GAMEENGINESKELETON_SRC_MESH_H_
#define GAMEENGINESKELETON_SRC_MESH_H_

#include <vector>
#include <tuple>
#include <concepts>
#include <cstdint>

namespace rts
{
  using Vertex = std::tuple<float, float, float, float, std::tuple<uint8_t, uint8_t, uint8_t>>;

  class Mesh
  {
	  std::vector<Vertex> m_Verticies;

  public:
	  template <std::input_iterator IteratorType>
	  void append(IteratorType begin, IteratorType end)
	  {
		  m_Verticies.insert(m_Verticies.cend(), begin, end);
	  }

	  void clear() noexcept
	  {
		  m_Verticies.clear();
	  }

	  [[nodiscard]] auto outputBegin() noexcept
	  {
		  return std::back_inserter(m_Verticies);
	  }

	  [[nodiscard]] auto begin() const noexcept
	  {
		  return m_Verticies.cbegin();
	  }

	  [[nodiscard]] auto end() const noexcept
	  {
		  return m_Verticies.cend();
	  }
  };

} // rts

#endif //GAMEENGINESKELETON_SRC_MESH_H_
